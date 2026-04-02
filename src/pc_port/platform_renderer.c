#include "pc_port/platform_renderer.h"

// In a real PC port, this uses OpenGL headers (<GL/glew.h>, <SDL.h>).
// The macro PC_BUILD should be defined in the PC target Makefile.

#ifdef PC_BUILD
// #include <GL/glew.h>
// #include <SDL2/SDL.h>
#endif

// GLSL Shader Source Skeletons (Targeting OpenGL 3.3 Core)
static const char* sVertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTexCoord;\n"
    "layout (location = 2) in vec4 aColor;\n"
    "out vec2 TexCoord;\n"
    "out vec4 VertexColor;\n"
    "uniform mat4 uProjection;\n"
    "void main() {\n"
    "   gl_Position = uProjection * vec4(aPos, 1.0);\n"
    "   TexCoord = aTexCoord;\n"
    "   VertexColor = aColor;\n"
    "}\n";

static const char* sFragmentShaderSource =
    "#version 330 core\n"
    "in vec2 TexCoord;\n"
    "in vec4 VertexColor;\n"
    "out vec4 FragColor;\n"
    "uniform sampler2D uTexture;\n"
    "uniform bool uUseTexture;\n"
    "void main() {\n"
    "   if (uUseTexture) {\n"
    "       FragColor = texture(uTexture, TexCoord) * VertexColor;\n"
    "   } else {\n"
    "       FragColor = VertexColor;\n"
    "   }\n"
    "}\n";

// Internal PC Vertex Format (Translates N64 Vtx_t to Floats)
typedef struct {
    f32 x, y, z;
    f32 s, t; // TexCoords
    f32 r, g, b, a;
} PCVertex;

#define MAX_VTX_BUFFER 32 // F3DEX standard max vertices
static PCVertex sVertexBuffer[MAX_VTX_BUFFER];

// Texture State Tracking
typedef struct {
    u32 physicalAddr;
    u8 format;  // e.g., G_IM_FMT_RGBA, G_IM_FMT_CI
    u8 size;    // e.g., G_IM_SIZ_16b, G_IM_SIZ_32b
    u16 width;
    u16 height;
    u32 glTextureId; // Bound OpenGL Texture
} PCTextureState;

static PCTextureState sCurrentTexture = {0, 0, 0, 0, 0, 0};

// Global GL state identifiers
static u32 sShaderProgram = 0;
static u32 sVAO = 0;
static u32 sVBO = 0;

void PC_RendererInit(void) {
#ifdef PC_BUILD
    // Initialize OpenGL Context (e.g., glViewport)
    // Compile and link sVertexShaderSource and sFragmentShaderSource into sShaderProgram
    // glGenVertexArrays(1, &sVAO);
    // glGenBuffers(1, &sVBO);
    // ... setup attributes for Pos, TexCoord, Color
#endif
}

void PC_RenderDisplayList(Gfx* displayList) {
#ifdef PC_BUILD
    if (!displayList) return;

    Gfx* cmd = displayList;
    s32 isRendering = 1;

    // Fast3DEX Command Parsing Loop
    while (isRendering) {
        // Opcode is stored in the high byte of word 0
        u8 opcode = (u8)(cmd->words.w0 >> 24);

        switch (opcode) {
            case G_VTX: {
                // Decode G_VTX command
                // w0 = opcode(8) | num_vertices(8) | dest_index(8) (varies slightly by ucode)
                // w1 = pointer to Vtx array
                // Note: IDO/F3DEX encoding for G_VTX varies, but generally:
                s32 numVertices = (cmd->words.w0 >> 12) & 0xFF; // Usually number of vertices
                s32 destIndex = (cmd->words.w0 >> 1) & 0x7F; // Usually destination index in RSP buffer

                // The address in w1 is usually a physical address or segment address
                // We assume the OS translates this to a virtual pointer in the PC port
                Vtx* vtxArray = (Vtx*)(uintptr_t)cmd->words.w1;

                if (vtxArray && numVertices <= MAX_VTX_BUFFER) {
                    for (s32 i = 0; i < numVertices; i++) {
                        s32 idx = destIndex + i;
                        if (idx >= MAX_VTX_BUFFER) break;

                        // N64 vertices are 16-bit integers.
                        sVertexBuffer[idx].x = (f32)vtxArray[i].v.ob[0];
                        sVertexBuffer[idx].y = (f32)vtxArray[i].v.ob[1];
                        sVertexBuffer[idx].z = (f32)vtxArray[i].v.ob[2];

                        // N64 texture coordinates are s10.5 fixed point, usually scaled later.
                        // We translate to generic float, shader will apply scaling.
                        sVertexBuffer[idx].s = (f32)vtxArray[i].v.tc[0] / 32.0f;
                        sVertexBuffer[idx].t = (f32)vtxArray[i].v.tc[1] / 32.0f;

                        // Color
                        sVertexBuffer[idx].r = (f32)vtxArray[i].v.cn[0] / 255.0f;
                        sVertexBuffer[idx].g = (f32)vtxArray[i].v.cn[1] / 255.0f;
                        sVertexBuffer[idx].b = (f32)vtxArray[i].v.cn[2] / 255.0f;
                        sVertexBuffer[idx].a = (f32)vtxArray[i].v.cn[3] / 255.0f;
                    }

                    // In OpenGL, we'd update the VBO with sVertexBuffer here via glBufferSubData
                }
                break;
            }

            case G_TRI1: {
                // Decode F3DEX G_TRI1
                s32 v0 = ((cmd->words.w0 >> 16) & 0xFF) / 2;
                s32 v1 = ((cmd->words.w0 >> 8) & 0xFF) / 2;
                s32 v2 = ((cmd->words.w0 >> 0) & 0xFF) / 2;

                // OpenGL Element Buffer Array population (stubbed)
                // e.g., glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, indices);
                // where indices = { v0, v1, v2 }
                break;
            }

            case G_TRI2: {
                // Decode F3DEX G_TRI2
                s32 v0 = ((cmd->words.w0 >> 16) & 0xFF) / 2;
                s32 v1 = ((cmd->words.w0 >> 8) & 0xFF) / 2;
                s32 v2 = ((cmd->words.w0 >> 0) & 0xFF) / 2;

                s32 v3 = ((cmd->words.w1 >> 16) & 0xFF) / 2;
                s32 v4 = ((cmd->words.w1 >> 8) & 0xFF) / 2;
                s32 v5 = ((cmd->words.w1 >> 0) & 0xFF) / 2;

                // e.g., glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
                // where indices = { v0, v1, v2, v3, v4, v5 }
                break;
            }

            case G_SETTIMG: {
                // Set Texture Image (Format, Size, Address)
                // w0 = opcode(8) | format(3) | size(2) | width(12)
                // w1 = physical memory address
                u8 format = (cmd->words.w0 >> 21) & 0x7;
                u8 size = (cmd->words.w0 >> 19) & 0x3;
                // N64 width is typically w0 & 0xFFF, but it can be (w0 & 0xFFF) + 1 depending on ucode
                u32 physAddr = cmd->words.w1;

                sCurrentTexture.format = format;
                sCurrentTexture.size = size;
                sCurrentTexture.physicalAddr = physAddr;
                // The actual width/height used for rendering is often set by G_SETTILESIZE.
                // We cache the format and address here. If this is a new address,
                // we might need to decode it to a GL texture immediately or wait for G_LOADBLOCK.
                break;
            }

            case G_SETTILE:
                // Sets TMEM offset, format, and other tile parameters.
                break;

            case G_SETTILESIZE: {
                // Defines the width and height of the texture tile being rendered.
                // w1 = uls(12) | ult(12) | lrs(12) | lrt(12)
                // Width = (lrs - uls) / 4 + 1
                // Height = (lrt - ult) / 4 + 1
                u32 uls = (cmd->words.w0 >> 12) & 0xFFF;
                u32 ult = (cmd->words.w0 >> 0)  & 0xFFF;
                u32 lrs = (cmd->words.w1 >> 12) & 0xFFF;
                u32 lrt = (cmd->words.w1 >> 0)  & 0xFFF;

                sCurrentTexture.width  = ((lrs - uls) >> 2) + 1;
                sCurrentTexture.height = ((lrt - ult) >> 2) + 1;

                // Now we have Format, Size, Width, Height, and Address.
                // If this is a standard RGBA16 texture, we would decode it here:
                // e.g. decode_rgba16(sCurrentTexture.physicalAddr, sCurrentTexture.width, sCurrentTexture.height)
                // and upload via glTexImage2D.
                break;
            }

            case G_LOADBLOCK:
            case G_LOADTLUT:
                // Handle TMEM loading and texture parameter setups (Palettes)
                // If it's a CI4 or CI8 texture, G_LOADTLUT loads the palette.
                // We must cache the palette colors here to decode the CI texture later.
                break;

            case G_SETCOMBINE:
                // Parse Color Combiner logic to update Shader Uniforms
                break;

            case G_ENDDL:
                isRendering = 0; // Terminate loop
                break;

            default:
                // Unhandled or unimplemented opcode
                break;
        }

        cmd++; // Advance to next 8-byte instruction
    }
#endif
}

void PC_RendererShutdown(void) {
#ifdef PC_BUILD
    // glDeleteVertexArrays(1, &sVAO);
    // glDeleteBuffers(1, &sVBO);
    // glDeleteProgram(sShaderProgram);
#endif
}

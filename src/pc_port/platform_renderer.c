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

            case G_SETTIMG:
                // Set Texture Image (Format, Size, Address)
                // If address changes, we may need to decode N64 CI/RGBA formats to GL textures
                break;

            case G_SETTILE:
            case G_SETTILESIZE:
            case G_LOADBLOCK:
            case G_LOADTLUT:
                // Handle TMEM loading and texture parameter setups
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

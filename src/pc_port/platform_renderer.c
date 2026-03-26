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
            case G_VTX:
                // Extract number of vertices and dest index
                // Fetch vertices from physical memory address in w1
                // Translate N64 Vtx struct (x,y,z, s,t, r,g,b,a) into GL floats
                // Upload to VBO
                break;

            case G_TRI1:
                // Extract 3 vertex indices
                // glDrawArrays or queue to an element buffer
                break;

            case G_TRI2:
                // Extract 6 vertex indices
                // Draw two triangles
                break;

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

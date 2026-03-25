#include "pc_port/platform_renderer.h"

// This file serves as a stub for the future PC SDL/OpenGL/Vulkan Renderer backend.
// In the current N64 target environment, these functions do nothing.
// Once a native PC target is configured via the Makefile, this file
// will be replaced or #ifdef'd to include OpenGL gl* logic.
// This is the core of the PC Port's graphical translation layer.

void PC_RendererInit(void) {
    // e.g. glViewport(0, 0, width, height);
    // glEnable(GL_DEPTH_TEST);
    // ... setup shaders etc.
}

void PC_RenderDisplayList(Gfx* displayList) {
    // Loop through the Gfx array.
    // Gfx* cmd = displayList;
    // while(true) {
    //    switch (cmd->words.w0 >> 24) { // Get Opcode
    //       case G_VTX:
    //           // Parse vertices and upload to VBO
    //           break;
    //       case G_TRI1:
    //       case G_TRI2:
    //           // Queue triangles for glDrawElements
    //           break;
    //       case G_SETTIMG:
    //           // Load/bind texture
    //           break;
    //       case G_ENDDL:
    //           return; // Stop parsing
    //       // ... handle all Fast3DEX macros
    //    }
    //    cmd++;
    // }
}

void PC_RendererShutdown(void) {
    // Clean up VBOs, Shaders, etc.
}

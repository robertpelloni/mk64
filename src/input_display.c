#include <ultra64.h>
#include <PR/ultratypes.h>
#include "main.h"
#include "menu_items.h"
#include "input_display.h"

// Helper to draw a rect (x, y, w, h)
static void draw_rect(Gfx **dlist, s32 x, s32 y, s32 w, s32 h, u8 r, u8 g, u8 b, u8 a) {
    *dlist = draw_box_fill(*dlist, x, y, x + w, y + h, r, g, b, a);
}

void render_input_display(void) {
    if (!gEnableInputDisplay) {
        return;
    }

    // Use Controller 1 for now
    struct Controller *cont = &gControllers[0];

    // Position (Bottom Right)
    s32 baseX = 260;
    s32 baseY = 180;

    // Analog Stick (Background)
    draw_rect(&gDisplayListHead, baseX, baseY, 40, 40, 0, 0, 0, 100);

    // Analog Stick (Dot)
    s32 stickX = (cont->rawStickX * 20) / 80; // Scale to +/- 20
    s32 stickY = -(cont->rawStickY * 20) / 80; // Invert Y

    // Clamp
    if (stickX < -20) stickX = -20;
    if (stickX > 20) stickX = 20;
    if (stickY < -20) stickY = -20;
    if (stickY > 20) stickY = 20;

    draw_rect(&gDisplayListHead, baseX + 18 + stickX, baseY + 18 + stickY, 4, 4, 255, 255, 255, 200);

    // Buttons
    // A (Right)
    if (cont->button & A_BUTTON)
        draw_rect(&gDisplayListHead, baseX + 45, baseY + 15, 8, 8, 0, 0, 255, 255); // Blue
    else
        draw_rect(&gDisplayListHead, baseX + 45, baseY + 15, 8, 8, 0, 0, 100, 100); // Dim Blue

    // B (Left)
    if (cont->button & B_BUTTON)
        draw_rect(&gDisplayListHead, baseX + 35, baseY + 25, 8, 8, 0, 255, 0, 255); // Green
    else
        draw_rect(&gDisplayListHead, baseX + 35, baseY + 25, 8, 8, 0, 100, 0, 100); // Dim Green

    // Z (Bottom Left Trigger)
    if (cont->button & Z_TRIG)
        draw_rect(&gDisplayListHead, baseX + 10, baseY + 45, 20, 6, 150, 150, 150, 255); // Grey

    // R (Shoulder)
    if (cont->button & R_TRIG)
        draw_rect(&gDisplayListHead, baseX + 45, baseY - 5, 10, 6, 150, 150, 150, 255);

    // Start (Center)
    if (cont->button & START_BUTTON)
        draw_rect(&gDisplayListHead, baseX + 20, baseY - 10, 8, 4, 255, 0, 0, 255); // Red
}

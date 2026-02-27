#include <ultra64.h>
#include <PR/ultratypes.h>
#include "main.h"
#include "menu_items.h"
#include "speedometer.h"
#include "math_util.h"

// Helper to draw a rect (x, y, w, h)
static void draw_rect(Gfx **dlist, s32 x, s32 y, s32 w, s32 h, u8 r, u8 g, u8 b, u8 a) {
    *dlist = draw_box_fill(*dlist, x, y, x + w, y + h, r, g, b, a);
}

void render_speedometer(void) {
    if (!gEnableSpeedometer) {
        return;
    }

    // Only draw for Player 1 in non-split screen or 2P split
    // (Simpler for now)
    if (gPlayerCountSelection1 > 2) return;

    struct Player *player = &gPlayers[0];

    // Position (Bottom Left)
    s32 baseX = 30;
    s32 baseY = 200;

    // Bar dimensions
    s32 barWidth = 100;
    s32 barHeight = 8;

    // Calculate speed ratio
    // Max normal speed is around 300.0f?
    // Star/Mushroom can go higher. Let's cap visual bar at 320.
    f32 maxSpeed = 320.0f;
    f32 currentSpeed = player->speed;
    if (currentSpeed < 0) currentSpeed = -currentSpeed; // Absolute speed

    s32 fillWidth = (s32)((currentSpeed / maxSpeed) * barWidth);
    if (fillWidth > barWidth) fillWidth = barWidth;

    // Draw Background
    draw_rect(&gDisplayListHead, baseX, baseY, barWidth, barHeight, 0, 0, 0, 150);

    // Draw Fill
    u8 r = 0, g = 255, b = 0;

    // Color gradient based on speed
    if (fillWidth > barWidth * 0.8) {
        r = 255; g = 0; // Red at high speed
    } else if (fillWidth > barWidth * 0.5) {
        r = 255; g = 255; // Yellow at medium
    }

    if (fillWidth > 0) {
        draw_rect(&gDisplayListHead, baseX, baseY, fillWidth, barHeight, r, g, b, 200);
    }

    // Optional: Draw text "km/h" or just speed value?
    // MK64 font rendering is complex, simple bar is safer for now.
    // Ideally we'd use print_text_mode_1 but that requires setup.
}

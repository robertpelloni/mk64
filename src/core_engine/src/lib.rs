#![no_std]
#![allow(non_camel_case_types)]

use core::panic::PanicInfo;

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

// C-compatible Vec3f structure (f32[3])
#[repr(C)]
pub struct Vec3f {
    pub x: f32,
    pub y: f32,
    pub z: f32,
}

// C-compatible minimal Actor struct representation for collision bounds
#[repr(C)]
pub struct ActorBounds {
    pub pos: Vec3f,
    pub bounding_box_size: f32,
}

/// Zero-Latency Rust Bridge: High performance bounding box collision logic.
/// Returns 1 for collision, 0 for no collision.
#[no_mangle]
pub extern "C" fn rust_query_collision_actor_vs_actor(
    actor1: *const ActorBounds,
    actor2: *const ActorBounds,
) -> i32 {
    unsafe {
        if actor1.is_null() || actor2.is_null() {
            return 0;
        }

        let a1 = &*actor1;
        let a2 = &*actor2;

        let dx = a1.pos.x - a2.pos.x;
        let dy = a1.pos.y - a2.pos.y;
        let dz = a1.pos.z - a2.pos.z;

        let dist_sq = (dx * dx) + (dy * dy) + (dz * dz);
        let combined_radius = a1.bounding_box_size + a2.bounding_box_size;

        if dist_sq < (combined_radius * combined_radius) {
            1
        } else {
            0
        }
    }
}

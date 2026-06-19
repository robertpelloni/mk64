# Testing Constraints

## The Integration Testing Dilemma

It is not currently possible to perform full CI/CD integration testing on the `mk64` C codebase without a valid N64 ROM file (`baserom.us.z64` or equivalent).

### Why is this the case?

The `mk64` decompilation project is not a standard C application that can be built independently. It relies heavily on a data-driven extraction pipeline:

1. **Asset Dependency:** The `make` command relies on `tools/extract_assets.py` to carve out level geometry, textures, display lists, and other binary blobs directly from the provided base ROM.
2. **Header Generation:** The extraction process generates crucial C headers (e.g., `<assets/common_data.h>`) containing macros, struct definitions, and memory offsets that the C source files (like `src/player_controller.c`) `#include` directly.
3. **Linker Constraints:** The C source files reference hundreds of global variables (`gModeSelection`, `gPlayers`, `gKartTopSpeedTable`, `D_801652C0`, etc.) and N64 SDK functions (`mtxf_transform_vec3f_mat3`) that are either extracted from the ROM, defined in assembly files (`.s`), or provided by the libultra N64 SDK.

### Consequence for Automated Testing

Because these assets and headers cannot be generated without the ROM, attempting to `#include` or link against core game files like `src/player_controller.c` in an isolated testing harness (e.g., `test_integration.c`) will result in hundreds of `undefined reference` and `fatal error: file not found` compilation errors.

Therefore, until the build pipeline is updated to provide a mocked testing environment or the ROM is supplied, testing is restricted to:
* Static analysis and syntax verification (`cc -fsyntax-only`).
* Visual logic inspection.
* Python-based simulation (which is an anti-pattern for integration testing, as it tests a copy of the logic rather than the source code itself).
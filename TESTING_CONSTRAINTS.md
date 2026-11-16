# Testing Constraints

Due to the fundamental architecture of this N64 decompilation repository, the build pipeline heavily relies on extracting binary assets (textures, models, course data, audio) from a proprietary, un-tracked base ROM file (`baserom.us.z64`).

The build pipeline cannot be fully executed (`make`) without this ROM, as crucial auto-generated header files (like `assets/common_data.h`) are built from the ROM extraction step.

Therefore, standard integration testing, execution, and Playwright frontend verification cannot be performed within this environment. All C-logic updates must be verified statically via `cc -fsyntax-only` compilation checks.

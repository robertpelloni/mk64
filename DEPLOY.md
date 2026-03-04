# Deployment & Build Instructions

## Environment Setup
The project requires a standard Linux build environment equipped with MIPS cross-compilers.

### Dependencies
*   `make`
*   `git`
*   `python3`
*   `mips-linux-gnu-binutils` (or similar cross-compiler prefix)
*   `qemu-irix` (for IDO compiler emulation, if building matching)

## ROM Extraction (Crucial Step)
You **must** supply an original `baserom.us.z64` (MD5: `20b854b239203baf6c961b850a4a51a2`) to extract game assets before compiling.
1. Place `baserom.us.z64` in the root repository directory.
2. Run `make extract` (or `make` which will automatically invoke it).

## Building the ROM
Execute the following to build the default US version:
```bash
make -j4
```
This will produce `build/us/mk64.us.z64`.

## Modding & PC Port Builds (Future)
When the SDL/OpenGL PC backend is finalized, an alternate `Makefile.pc` will be provided.
```bash
make -f Makefile.pc -j4
```

## Submodules
Ensure submodules are initialized:
```bash
git submodule update --init --recursive
```
*   `tools/ido5.3_compiler`: Required for compiling matching MIPS C code.
*   `tools/asm-differ`: For diffing compiled objects against the baserom.
# Deployment & Build Instructions

## Local Extraction & Build
1. Place a valid `baserom.us.z64` in the project root.
2. Initialize submodules: `git submodule update --init --recursive`
3. Build tools: `make -C tools -j`
4. Extract assets: `make assets -j`
5. Compile ROM: `make -j`

## Expected Output
The compilation outputs the matched roms (e.g. `mk64.us.z64`) into the `build/` directory.

## Testing Differences
To test modifications against the original ROM checksum:
```bash
python3 first-diff.py
```

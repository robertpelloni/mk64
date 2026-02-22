# TODO List

## Immediate Priorities (Current Session)
- [ ] **Item Control Feature:**
    - [ ] Add `gPracticeItemOption` to `src/main.c` / `include/main.h`.
    - [ ] Modify `src/update_objects.c` (`func_8007AFB0`) to override item generation.
    - [ ] Add "Item Options" submenu to `src/menus.c` (Practice Menu).
    - [ ] Verify "Force Item" and "Disable Items" functionality.
- [ ] **UI Descriptions:**
    - [ ] Implement text rendering for menu descriptions in `src/menus.c` / `src/menu_items.c`.
    - [ ] Add strings for all Extras/Practice options.
- [ ] **Documentation:**
    - [ ] Update `MANUAL.md` with new features.
    - [ ] Finalize `DASHBOARD.md` updates.

## Short Term
- [ ] **Lap Skip/Manipulation:** Add practice menu option to jump laps.
- [ ] **Timer Freeze:** Toggle to stop the race timer.
- [ ] **Refine Save States:** Save more state (items, current lap, etc.) to make it more robust.

## Long Term / Tech Debt
- [ ] **Code Cleanup:** Remove unused variables found during `src/racing/actors.c` analysis.
- [ ] **Submodule Sync:** Ensure all tools (`asm-differ`, `fast64`) are on stable commits.
- [ ] **Build System:** Improve `Makefile` dependency tracking for header changes.

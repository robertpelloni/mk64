# mk64 Roadmap

## Phase 1: Perfect Decompilation (Current)
- Complete matching decompilation of all MK64 functionality.
- Label all audio and rendering routines.
- Finalize documentation on basic mechanics, course structure, and actors.

## Phase 2: High-Performance Engine Port
- Implement the "Zero-Latency" Rust bridge for core item/collision physics.
- Cross-compile core loops to WASM.

## Phase 3: The Autonomous Sandbox
- Introduce RL-trained "TAS" agents.
- Expose course structures for AI auto-generation.

## Phase 4: Decentralized Racing Mesh
- Implement P2P Multiplayer using `libp2p`.
- Transition UI overlays to modern WebGL/WASM environments.

# Roadmap: MK64 Greatest Racing Game Mod

## Phase 1: Foundation (Completed v1.0.x)
- [x] **60 FPS Support**: Smooth gameplay at 60Hz.
- [x] **Widescreen (16:9)**: Native rendering support.
- [x] **Gameplay Fixes**: Removal of rubber banding for fair AI.
- [x] **Unlock Content**: All cups and modes available from start.
- [x] **Fast Boot**: Streamlined startup sequence.

## Phase 2: Visual Enhancements (Planned v1.1.0)
- [ ] **HD Texture Pack Support**: Integration with texture replacement tools.
- [ ] **Dynamic Lighting**: Improved lighting engine for courses.
- [ ] **Model Upgrades**: Higher polygon count for karts and characters.

## Phase 3: Content Expansion (Planned v1.2.0)
- [ ] **Custom Tracks**: Tooling pipeline for importing custom geometry.
- [ ] **New Characters**: Roster expansion.
- [ ] **Course Editor**: In-game or external tool for track design.

## Phase 4: Network & Multiplayer (Planned v2.0.0)
- [ ] **Online Multiplayer**: Netcode implementation for remote play.
- [ ] **Ghost Data Sharing**: Global leaderboards for time trials.
- [ ] **LAN Support**: Optimized local networking.


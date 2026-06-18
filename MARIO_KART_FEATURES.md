# Mario Kart Modern Features Roadmap

This document outlines all the major features and functionalities from every version of Mario Kart (Super Mario Kart, Double Dash, DS, Wii, 7, 8, etc.) to be re-implemented into this decompilation project, moving it towards "The Ultimate Racing Sandbox."

## Phase 1: Core Mechanics Enhancements
*   **[x] Drafting / Slipstream (MK64/DS/Wii+):** Following closely behind an opponent for a set duration grants a temporary speed boost. (Requires measuring relative distance, velocity, and angle).
*   **[x] Trick Jumps (MK Wii/7/8):** Pressing the hop button (R) at the peak of a jump or ramp gives a mini-turbo boost upon landing.
*   **[x] Mini-Turbo Revamp (MK DS/Wii+):** Implementing multi-stage mini-turbos (Blue -> Orange -> Purple) based on drift duration and steering angle.
*   **Snaking Mechanics (MK DS):** Formalizing the "snaking" mechanic with specific drift state counters and tight turn radii.

## Phase 2: Item & Combat Evolvations
*   **Item Holding (MK Double Dash+):** Allowing players to hold two items at once, or drag items behind them defensively while still holding another item in reserve.
*   **Special Items (MK Double Dash):** Character-specific special items (Bowser Shell, Chain Chomp, Giant Banana).
*   **Coin Mechanic (Super Mario Kart / MK 7 / 8):** Collecting coins to increase top speed, with a maximum of 10 coins. Losing coins when hit.
*   **The Crazy Eight (MK 8):** Orbiting 8 different items around the player.

## Phase 3: Vehicle & Physics Dynamics
*   **Bikes & Wheelies (MK Wii):** Implementing two-wheeled vehicles with tighter inside drifting and the ability to "wheelie" on straightaways for a speed boost (at the cost of handling).
*   **Gliders (MK 7 / 8):** Deploying a glider when launching off blue ramps, altering physics to allow aerial control, drafting in mid-air, and choosing different landing paths.
*   **Anti-Gravity (MK 8):** Driving on walls and ceilings with altered physics. Bumping into other racers or specific obstacles during anti-gravity triggers a "Spin Boost".
*   **Underwater Driving (MK 7 / 8):** Modified physics and handling when submerged, with unique propeller animations.

## Phase 4: Track & Environment Interaction
*   **Half-Pipes (MK Wii):** Driving up the side of half-pipes to execute tricks and gain boosts, seamlessly returning to the track.
*   **Dynamic Environments:** Objects that change state during the race (e.g., trains moving, water levels rising/falling).
*   **Multiple Routes:** Expanding course logic to handle completely divergent track paths dynamically.

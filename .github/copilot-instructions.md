Purpose
=======

This file gives concise, actionable guidance for AI coding agents working in this Arduino-focused workspace so they can be immediately productive.

Quick summary
-------------
- Repo is a collection of individual Arduino sketches. Each sketch is a folder containing a single `.ino` file named exactly like the folder (for example `Day1Exercise1/Day1Exercise1.ino`).
- Build/upload workflow uses `arduino-cli` or the Arduino IDE. There is no PlatformIO or CI config discovered.
- Helpful reference files: `README.md` (root) and `PracticalBoardTester/README.md`.

What to look for first
---------------------
- Open `README.md` at repo root for the canonical build/upload commands (uses `arduino-cli`).
- Look for the sketch directory you need. The canonical pattern is `SketchName/SketchName.ino`.
- For helper code, search for `.h` and `.cpp` files in the same sketch directory (for example `Day5Self1/SSD.h`, `Day8Exercise1/Player.cpp` + `Player.h`). These are compiled together with the `.ino`.

Build and upload (discovered commands)
-------------------------------------
- List boards and ports: `arduino-cli board list`
- List installed cores: `arduino-cli core list`
- Compile a sketch: `arduino-cli compile -b <FQBN> <Sketch/Path>`
  - Example: `arduino-cli compile -b arduino:avr:uno ./Day1Exercise1`
- Upload a sketch: `arduino-cli upload -p <PORT> -b <FQBN> <Sketch/Path>`
  - Example: `arduino-cli upload -p /dev/ttyUSB0 -b arduino:avr:uno ./Day1Exercise1`

Project-specific conventions and patterns
----------------------------------------
- One sketch per directory. The main `.ino` must match the directory name.
- Supporting C/C++ files (headers and `.cpp` files) live alongside the `.ino` and are compiled automatically. Example: `Day8Exercise1/Player.cpp` with `Player.h`.
- Sketches include `Arduino.h` explicitly in helper headers and `.ino` files (see `Day1Exercise1/Day1Exercise1.ino`, `Day5Self1/SSD.h`).
- Many sketches use simple global variables, arrays for pin mappings, and `delay()`-based control loops; watch for timing and debounce logic (see `Player::press` debounce in `Day8Exercise1`).
- Common pattern: helper modules implement small APIs (e.g., `SSDWrite`, `SSDSelect` in `Day5Self1/SSD.h`). Prefer to call those APIs rather than rewrite low-level pin sequences.

Integration & external dependencies
----------------------------------
- No `platformio.ini` or other build manifests present. The repo expects Arduino cores to be installed via `arduino-cli`.
- `esp32_works/` contains ESP32 examples that require the ESP32 core; agents should not assume AVR-only. Detect required core from `arduino-cli core list` or from `#include`/project folder name and ask if unsure.

Helpful files to reference while editing
---------------------------------------
- `README.md` (root): canonical `arduino-cli` commands and workflow.
- `PracticalBoardTester/README.md`: practical board pin mappings and schematic references used by `PracticalBoardTester.ino`.
- `Day5Self1/SSD.h`: example of a helper header with bitmask mapping for seven-seg displays.
- `Day8Exercise1/Player.cpp` + `Player.h`: example OOP-ish pattern in sketches, registration/array-based globals.

Agent behavior rules (practical, repository-specific)
--------------------------------------------------
- Do not rename a sketch `.ino` file or its directory; keep `SketchName/SketchName.ino` parity.
- When adding C++ files, keep them in the same sketch directory (Arduino build rule). Avoid creating cross-folder source references unless adding a library.
- If a change requires installing a new Arduino core or library, add brief setup notes to `README.md` and confirm with the user before making environmental changes.
- Prefer small, minimally-invasive edits. Many examples are educational; preserve sample structure and comments.

If you need more
---------------
- Ask the user whether they want me to: run `arduino-cli` commands locally, add a `platformio.ini`, or scaffold a reusable library for shared helpers.
- If unsure which FQBN to use for a board in `esp32_works/`, ask for the target board model or run `arduino-cli board list` on the machine that has the board connected.

End
===

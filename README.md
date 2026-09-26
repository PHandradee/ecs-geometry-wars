# SFML Shape Shooter
**Assignment 2 – Game Programming (Memorial University of Newfoundland)**

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat&logo=c%2B%2B&logoColor=white) ![SFML](https://img.shields.io/badge/SFML-FF6600?style=flat&logo=sfml&logoColor=white) ![ImGui](https://img.shields.io/badge/ImGui-3796EF?style=flat&logo=github&logoColor=white)

A C++/SFML application implementing a top-down shooter game where the player controls a shape, shoots projectiles at spawning enemies, and manages resources via a custom Entity Component System (ECS). Includes a real-time **ImGui debugger** for system monitoring and entity manipulation.

---

## Description

This program implements a complete game loop with the following features:
- **Player Control**: WASD movement with normalized diagonal speed; shooting towards mouse cursor.
- **Enemy AI**: Random spawning polygons that bounce off walls and split into smaller entities upon destruction.
- **Special Ability**: A unique weapon triggered by right-click with a visual cooldown timer (non-ImGui).
- **Scoring System**: Dynamic score calculation based on enemy complexity (vertices), displayed on screen.
- **Visual Effects**: Entity rotation, alpha fading based on lifespan, and custom rendering pipeline.
- **Interactive ImGui GUI**:
  - Toggle individual systems (Movement, Collision, Spawner, etc.);
  - Inspect all entities (ID, Tag, Position);
  - Destroy specific entities via UI;
  - Adjust spawn intervals and manually spawn enemies.

The architecture relies on a custom **Entity-Component-System (ECS)** pattern, reading all balance parameters from a `config.txt` file.

---

## Dependencies

- **C++23** or higher
- **SFML 3.0.2** (Simple and Fast Multimedia Library)
- **Dear ImGui v1.91.2** (integrated with SFML)
- **imgui-sfml v3.0** (to integrate SFML and ImGui)
- A compatible compiler (`g++`, `clang++`, etc.)
- **CMAKE 4.2.3**

---

## Building and Running with CMake

This project uses **CMake** for easy and portable builds.

### Build steps

```bash
# Create a build directory
mkdir build

# Configure the project with CMake
cmake -S . -B build/ 

# Compile the executable
cmake --build build

# Run the program (ensure config.txt and fonts/ are in the working directory)
(cd bin && ./ecs-geometry-wars)
```
**Note:** The application requires `config.txt` and the font file specified within it (e.g., `fonts/tech.ttf`) to be present in the execution directory.

## Controls

| Key / Action | Function |
| :--- | :--- |
| **W, A, S, D** | Move Player |
| **Left Click** | Shoot Bullet |
| **Right Click** | Activate Special Ability |
| **P** | Pause Game |
| **ESC** | Close Game |
| **Mouse** | Aim & Interact with ImGui |

##  Configuration File Format (`config.txt`)

The game is fully data-driven. Example configuration:

```txt
Window 1920 1080 60 0
Font fonts/tech.ttf 24 255 255 255
Player 32 32 5 5 5 255 0 0 4 8
Enemy 32 32 3 3 255 255 255 2 3 8 90 60
Bullet 10 10 8 255 255 255 255 255 255 2 20 90
```

### Syntax Reference:
- **Window**: `Width Height FrameLimit Fullscreen(0/1)`
- **Font**: `FilePath Size R G B`
- **Player**: `ShapeRadius ColRadius Speed Fill(RGB) Outline(RGB) Thickness Vertices`
- **Enemy**: `ShapeRadius ColRadius SpeedMin SpeedMax Outline(RGB) Thickness VertMin VertMax Lifespan SpawnInterval`
- **Bullet**: `ShapeRadius ColRadius Speed Fill(RGB) Outline(RGB) Thickness Vertices Lifespan`

## Recommended Tests
- Verify diagonal movement speed normalization (should not be faster than cardinal movement);
- Test enemy splitting mechanics (large enemy → N small enemies traveling at 360/N degrees);
- Check alpha fading on bullets/enemies near end of lifespan;
- Use ImGui to toggle off "Collision" system and verify entities pass through each other;
- Validate score doubling for small enemies compared to large ones.

## Course Information
- **Course:** Game Programming
- **Institution:** Memorial University of Newfoundland
- **Instructor:** [Dr. David Churchill](https://www.cs.mun.ca/~dchurchill/)
- **Assignment:** 2

##  Learning Resources
This assignment builds upon concepts taught in the official course lecture series:
[Game Programming – Memorial University (YouTube Playlist)](https://www.youtube.com/watch?v=tOHqMDlG9S0&list=PL_xRyXins848Mfiv4hIgiMZgLpzFT7ohv&index=22&t=8s)
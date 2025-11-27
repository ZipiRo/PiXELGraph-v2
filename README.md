# PiXELGraph-v2

PiXELGraph-v2 is a **retro-style Windows console graphics engine** written in C++.  
It lets you build simple 2D games, visual experiments, and tools directly in the console window using:
- Scenes and a basic game loop
- Shapes, text rendering, and a virtual camera
- Keyboard and mouse input
- Basic audio playback (via `miniaudio`)
- A small math layer (`Vector2`, `Transform`, etc.)

The library is distributed as a precompiled static library (`Library/PiXELGraph-v2.a`) plus headers in `Include/`.

---

## Features

- ✅ **Scene system** (`Scene`, `SceneManager`) with `Start`, `Update`, `Draw`, etc.
- ✅ **Console window control** (`Window`, `Screen`, `View`)
- ✅ **2D drawing API**:
  - Shapes (`Shape`, `Rectangle`, `Elipse`, `Vertex`, `BoundingBox`)
  - Text rendering (`Text`, `Font`)
  - Colors (`Color`)
- ✅ **Input handling** (`Input`, `Event`) for keyboard and mouse
- ✅ **Time utilities** (`Time::deltaTime`, `Time::Tick()`)
- ✅ **Audio playback** (`AudioClip`, `AudioSource`)
- ✅ **Debug utilities** (`Debug::Log`, custom `Error` exception)

---

## Directory Layout

```text
PiXELGraph-v2/
├─ Include/              # Public headers for the engine
│  ├─ Core/              # Core engine types (PiXELGraph, Screen, SceneManager, Time, View)
│  ├─ Console/           # Window, Input, Events, Debug, Error
│  ├─ Graphics/          # Shapes, Text, Transform, Font, Vertex, BoundingBox
│  └─ Audio/             # AudioClip, AudioSource
├─ Library/
│  ├─ *.o                # Precompiled object files
│  └─ PiXELGraph-v2.a    # Static library
├─ Resources/
│  └─ font.cf           # Bitmap font data
├─ main.cpp              # Example / demo entry point
└─ DebugWindow.cpp       # Optional debug console helper
```

---

## Getting Started

### 1. Requirements

- **Platform:** Windows (uses `windows.h` and the Win32 console)
- **Compiler:** Any modern C++ compiler (C++17 recommended)
  - MinGW / g++
  - MSVC (Visual Studio)
- **Audio:** `miniaudio` is already included as a single-header library (`Include/miniaudio.h`).

### 2. Include the headers

Add the `Include/` directory to your compiler's include paths.

Example (g++):

```bash
g++ -std=c++17 -IInclude main.cpp Library/PiXELGraph-v2.a -o Demo
```

Example (MSVC from Developer Command Prompt):

```bat
cl /std:c++17 /I Include main.cpp Library\PiXELGraph-v2.a /Fe:Demo.exe
```

> 💡 Adjust paths and library flags depending on your toolchain / project setup.

---

## Minimal Example

Here is a **beginner-friendly** example of a moving rectangle in a custom scene:

```cpp
#include "Core/PiXELGraph.h"

class MyScene : public Scene
{
private:
    Shapes::Rectangle rect;

    void Start() override
    {
        // Create a rectangle shape 20x10 units in size
        rect = Shapes::Rectangle(20.0f, 10.0f);
        rect.SetColor(Color::Green);

        // Place it somewhere on screen
        rect.transform.SetPosition(40.0f, 12.0f);

        // Optional: set background color
        Screen::BackgroundColor = Color::Black;
    }

    void Update() override
    {
        // Move using arrow keys
        if (Input::IsKeyDown(Key::Right))
            rect.transform.Move(1.0f, 0.0f);
        if (Input::IsKeyDown(Key::Left))
            rect.transform.Move(-1.0f, 0.0f);
        if (Input::IsKeyDown(Key::Up))
            rect.transform.Move(0.0f, -1.0f);
        if (Input::IsKeyDown(Key::Down))
            rect.transform.Move(0.0f, 1.0f);
    }

    void Draw() override
    {
        // Ask the engine to draw this shape
        Screen::DrawShape(rect);
    }
};

int main()
{
    // Register scenes
    SceneManager::AddScene<MyScene>("Game");

    // Load the initial scene
    SceneManager::LoadScene("Game");

    // Start the engine main loop
    PiXELGraph::GetInstance().Run();

    return 0;
}
```

---

## Core Concepts & Types

### Core Engine

- **PiXELGraph**
- **Scene**
- **SceneManager**
- **Screen**
- **Time**
- **View**

### Graphics

- **Color**
- **Vector2**
- **Transform**
- **Vertex**
- **Shape**
- **Rectangle**
- **Elipse**
- **Text**
- **BoundingBox**
- **Font**

### Input & Window

- **Window**
- **Input**
- **Event**

### Audio

- **AudioClip**
- **AudioSource**

### Debugging & Errors

- **Debug**
- **Error**

Each of these classes is documented in more detail in the **generated API website** under `docs/`.

---

## Building Your Own Project

1. **Copy** the `Include/` and `Library/` folders into your project, or reference them from your build system.
2. **Link** against `PiXELGraph-v2.a`.
3. **Create scenes** by deriving from `Scene` and overriding:
   - `Start()` — initialization
   - `Event()` — raw input events (optional)
   - `Update()` — per-frame logic
   - `Draw()` — rendering
   - `Quit()` — cleanup (optional)
4. **Register scenes** using `SceneManager::AddScene<YourScene>("Name")`.
5. **Load a scene** with `SceneManager::LoadScene("Name")`.
6. **Start the engine** with `PiXELGraph::GetInstance().Run()`.

---

## Debugging

Use the `Debug` class to log information to a debug buffer:

```cpp
Debug::Log("Hello from PiXELGraph!\n");
```

Errors inside the engine throw an `Error` exception with a message you can catch:

```cpp
try
{
    PiXELGraph::GetInstance().Run();
}
catch (const Error& e)
{
    Debug::Log(std::string("Engine error: ") + e.what() + "\n");
}
```

---

## License

> Add your license information here (MIT, GPL, proprietary, etc.).

---

## Generated Documentation Site

This repo comes with a static **HTML documentation site** in the `docs/` folder:

- `docs/index.html` — overview & navigation
- `docs/classes/*.html` — one page per engine class, with:
  - Method list (signatures)
  - Header include path
  - **Beginner-friendly usage example**

You can host it locally or publish it via GitHub Pages.

```text
# For GitHub Pages
# Put 'docs/' in the repository and enable Pages → "Deploy from /docs"
```


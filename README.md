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
## ⚠ Important Build Note

### 🔹 You **must also compile** `DebugWindow.cpp`

This file provides a secondary output console used for logging (`Debug::Log`) and engine messages.  
If you build without it, the program will run, but debug output will not appear.
The compiled DebugWindow.exe should be in the same folder as the main program.

### 🔹 The resource `font.cf` **should be in the same folder as the main program** 
This file is the main font used in the Font class.
If you don't add it the program will give an exception that there is no font.cf file.

---

## Features

- ✅ **Scene system** (`Scene`, `SceneManager`) with `Start`, `Update`, `Draw`, `Event`, `Quit`
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
│  └─ PiXELGraph-v2.a    # Static library
├─ Resources/
│  └─ font.cf           # Bitmap font data
├─ main.cpp              # Example / demo entry point
└─ DebugWindow.cpp       #  Debug console helper
```

---

## Getting Started

### 1. Requirements

- **Platform:** Windows (uses `windows.h` and the Win32 console)
- **Compiler:** Any modern C++ compiler (C++17 recommended)
  - MinGW / g++
- **Audio:** `miniaudio` is already included as a single-header library (`Include/miniaudio.h`).
- **Font:** `nlohmann/json.hpp` is included for JSON font.cf parsing.

### 2. Include the headers

Add the `Include/` directory to your compiler's include paths.

```bash
g++ -std=c++17 -IInclude main.cpp Library/PiXELGraph-v2.a -o Demo
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

// Initialize the Engine as a derived class
class Engine : public PiXELGraph
{
public:
    Engine()
    {
        Init(800, 600, 2, L"Demo");
        MaxFramesPerSecond = MaxFPS;
    }
};

int main()
{
    // Register scenes
    SceneManager::AddScene<MyScene>("Game");

    // Load the initial scene
    SceneManager::LoadScene("Game");

    // Start the engine main loop
    Engine engine;
    engine.Run();
  
    return 0;
}

```
## 🔥 Running WITHOUT Scenes (manual mode)

If you prefer a raw engine loop like SDL/DirectX style:

1. Open:

```
Include/EngineSettings.h
```

2. Set:

```cpp
#define USE_SCENES false
```

Then you control:

```cpp
void Start();
void Event();
void Update();
void Draw();
void Quit();
```

### Example Manual Mode

```cpp
#include "Core/PiXELGraph.h"

class Engine : public PiXELGraph
{
private:
    void Start() override   { Screen::BackgroundColor = Color::Black; }
    void Update() override { /* logic here */ }
    void Draw() override   { /* DrawShape(...); */ }

public:
    Engine()
    {
        Init(800, 600, 2, L"Demo");
        MaxFramesPerSecond = 120;
    }
};


int main(){
    Engine engine;
    engine.Run();
}

```

When to use manual mode:

| Use case | Reason |
|---|---|
| Single-screen tools/games | Simple workflow |
| Custom game architecture | No scene manager overhead |
| You need pure control | Update/Draw just like SDL |

---

## 🔧 EngineSettings.h options

Located at:

```
Include/EngineSettings.h
```

| Setting | Description |
|---|---|
| `USE_SCENES` | true = scene framework / false = manual engine mode |
| `USE_AUDIO` | true = will allow you to use AudioSource & AudioClip classes / false = IT WILL NOT BE USED |
| `USE_DEBUGER` | true = will open a debug window and alow you to use Debug::Log / false = IT WILL NOT BE USED |
| `MaxFPS` | you can use this to set a limit the max frames per second then asign it to MaxFramesPerSecond in the constructor |

---

## 🖥 Event Function (Correct Input Handling)

PiXELGraph separates input event polling from rendering and updating.
Because of this, all input should be processed inside Event(), not Update().

Event() is tied to OS input polling (independent of framerate),
while Update() runs based on the engine's frame speed.
If input is only checked in Update(), fast key or mouse actions may be missed.

### Why this matters

| Function | Runs When? | Used For |
|---|---|---|
| Event()  | Whenever the system sends input (NOT FPS dependent) | Keyboard + mouse input (correct place) |
| Update() | Runs every frame | Movement, gameplay logic, physics |
| Draw()   | Runs every frame | Rendering only |

### Correct usage pattern

```cpp
void Event() override
{
    if(Input::IsKeyPressed(Key::Space))
        Debug::Log("Space pressed\n");

    if(Event::GetEvent() == EventType::EVENT_MOUSE_LCLICK)
        Debug::Log("Left mouse click pressed\n");
}

void Update() override
{
    // Logic and movement here
}

void Draw() override
{
    // Only rendering
}
```

**This applies to both Scene mode and Manual Engine mode.**


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
6. **Initialize the engine** by deriving PiXELGraph to a class.
7. **Make the class constructor** and use `Init(WIDTH, HEIGHT, PIXEL_SIZE, TITLE_NAME)`.

---

## Debugging & Errors

Use the `Debug` class to log information to a debug buffer:

```cpp
Debug::Log("Hello from PiXELGraph!\n");
```

The engine has a built-in error handler and will **catch `Error` exceptions automatically**.  
If something goes wrong internally, the engine will capture it and forward the message to the debug output window (from `DebugWindow.cpp`).

If you want to trigger your own controlled failures, you can throw an error manually:

```cpp
throw Error("Player health is below zero!");
```

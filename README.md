# PiXELGraph v2

PiXELGraph v2 is a lightweight C++ framework for building **2D console-based games and graphical applications**.  
It provides:

- A simple **scene system**
- A 2D **drawing API** (pixels, lines, rectangles, ellipses, shapes, text)
- **Input handling** (keyboard + mouse)
- **Audio playback** (via miniaudio)
- A configurable **console window** and **frame timing**

---

## 📂 Project Structure

```text
PiXELGraph-v2-main
│ main.cpp                 → Example entry point
│ DebugWindow.cpp          → Optional debug UI
│
├─ Include                 → Public API headers
│  ├─ Core                 → Engine, scenes, screen, view, time, colors
│  ├─ Graphics             → Shapes, text, font, vertices, transforms
│  ├─ Audio                → AudioClip & AudioSource
│  ├─ Console              → Input, window, debug, events, errors
│  ├─ nlohmann             → json.hpp (3rd party JSON lib)
│  ├─ UMath.h              → Math utilities
│  ├─ Vector2.h            → 2D vector class
│  └─ EngineSettings.h     → Engine compile-time configuration
│
├─ Source                  → Internal engine implementations
├─ Library/PiXELGraph-v2.a → Precompiled static library
└─ Resources/font.cf       → Default font resource
```

---

## ⚙ Engine Configuration

### `EngineSettings.h`

```cpp
// Enable SceneManager & Scene system
#define USE_SCENE

// Enable audio system
#define USE_AUDIO

// Engine Max FPS
#define MaxFramesPerSecond 99999
constexpr int FPS = MaxFramesPerSecond;
```

- `USE_SCENE` – enables the `Scene` / `SceneManager` model.
- `USE_AUDIO` – enables `AudioSource` & `AudioClip`.
- `FPS` – global frame rate cap.

---

## 🚀 Getting Started

### 1. Basic Engine Setup

```cpp
#include "Core/PiXELGraph.h"
#include "Core/SceneManager.h"
#include "Graphics/Elipse.h"
#include "Core/Screen.h"

class DemoScene : public Scene
{
    Shapes::Elipse e;

    void Start() override
    {
        e = Shapes::Elipse(10, 10);
        e.SetColor(Color::Black);
        e.transform.SetPosition(50, 100);

        Screen::BackgroundColor = Color::Red;
    }

    void Update() override
    {
        // game logic here
    }

    void Draw() override
    {
        DrawShape(e);
    }
};

class Engine : public PiXELGraph
{
public:
    Engine()
    {
        Init(800, 600, 3, L"My Game");
    }
};

int main()
{
    SceneManager::AddScene<DemoScene>("MainScene");
    SceneManager::LoadScene("MainScene");

    Engine engine;
    engine.Run();

    return 0;
}
```

---

### 2. Building

Example (g++, using static library):

```bash
g++ main.cpp -I Include -L Library -lPiXELGraph-v2 -o GameApp
```

Make sure:
- `Include/` is on your include path
- `Library/PiXELGraph-v2.a` is linked
- `Resources/` is in the working directory (for fonts, etc.)

---

## 🧠 Core Module (`Include/Core`)

### `PiXELGraph` – Engine Singleton

**Header:** `Core/PiXELGraph.h`

```cpp
class PiXELGraph
{
public:
    PiXELGraph(const PiXELGraph&) = delete;
    PiXELGraph& operator=(const PiXELGraph&) = delete;

    static PiXELGraph &GetInstance();

    void Init(int WindowWidth, int WindowHeight, int PixelSize, const std::wstring &title);
    void Run();

private:
    static PiXELGraph* activeInstance;

    std::atomic<bool> RUNNING;
    std::thread InputThread;
    std::thread EventThread;

    void InputLoop();
    void EventLoop();
    void HandleError(const std::string &message);
    void Exit();

    PiXELGraph();
};
```

**Responsibilities:**

- Creates and configures the console window
- Runs the main loop
- Starts input & event threads
- Integrates `SceneManager`, `Screen`, `Time`, `Input`, `Event`

**Key methods:**

- `Init(width, height, pixelSize, title)` – initialize engine.
- `Run()` – start main loop.
- `GetInstance()` – access singleton.

---

### `Scene` & `SceneManager`

**Header:** `Core/SceneManager.h`

#### `Scene`

```cpp
class Scene
{
private:
    friend class PiXELGraph;
    friend class SceneManager;

    virtual void Start() {}
    virtual void Event() {}
    virtual void Update() {}
    virtual void Draw() {}
    virtual void Quit() {}

public:
    std::string name;
    int buildIndex;
};
```

Override these callbacks in your scenes:

- `Start()` – called once when scene is loaded
- `Event()` – event handling (keys, mouse, etc.)
- `Update()` – game logic
- `Draw()` – all rendering
- `Quit()` – called before scene is destroyed

#### `SceneInfo`

```cpp
struct SceneInfo
{
    std::string name;
    int buildIndex;
    std::function<std::unique_ptr<Scene>()> createFunction;
};
```

#### `SceneManager`

```cpp
class SceneManager
{
public:
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    static SceneManager &GetInstance();

    template <typename T>
    static void AddScene(const std::string &sceneName);

    static void LoadScene(int buildIndex);
    static void LoadScene(const std::string &name);
    static Scene* GetActiveScene();

private:
    std::unique_ptr<Scene> currentScene;
    std::vector<SceneInfo> scenes;
    bool changeScene;

    SceneManager();
    static void RunScene();

    friend class PiXELGraph;
};
```

**Usage:**

```cpp
SceneManager::AddScene<MyScene>("Menu");
SceneManager::AddScene<GameScene>("Game");

SceneManager::LoadScene("Menu");
// or
SceneManager::LoadScene(0);
```

---

### `Screen` – Frame Buffer & Drawing

**Header:** `Core/Screen.h`

```cpp
class Screen
{
public:
    static void Display();
    static void Clear();

    Screen(const Screen &) = delete;
    void operator=(const Screen &) = delete;

    static Screen &GetInstance();
    static void SetView(const View& view);
    static View& GetView();

    static int Width();
    static int Height();

    static Color BackgroundColor;

private:
    Screen() {}

    static int ScreenWidth, ScreenHeight;
    std::vector<Color> ScreenBuffer;
    std::vector<Color> PreviosBuffer;
    View viewPort;

    void SetParameters(int WindowWidth, int WindowHeight);

    friend class PiXELGraph;
    friend class SceneManager;
    friend void PlotPixel(int, int, Color);
};
```

- `Display()` – flushes buffer to window.
- `Clear()` – clears buffer with `BackgroundColor`.
- `SetView(view)` / `GetView()` – camera control.
- `Width()` / `Height()` – current screen resolution in logical pixels.

#### Global drawing helpers (from `Screen.h`)

```cpp
void PlotPixel(int x, int y, Color color);

void DrawLine(int x1, int y1, int x2, int y2, Color color);
void DrawRectangle(int x, int y, int width, int height, Color color);
void FillRectangle(int x, int y, int width, int height, Color color);
void DrawElipse(int x, int y, int width, int height, Color color, int point_count = 30);
void FillElipse(int x, int y, int width, int height, Color color, int point_count = 30);

void DrawLines(const std::vector<Vertex> &vertices, bool closed = true);
void DrawShape(Shape &shape);
void DrawTEXT(Text &text);

void Fill(const std::vector<Vector2> &vertices, const BoundingBox &boundingBox, const Color &color);
void FillShape(const std::vector<Vertex> &vertices, const BoundingBox& boundingBox, Color color);
```

---

### `View` – Camera / Viewport

**Header:** `Core/ViewPort.h`

```cpp
class View 
{
public:
    bool update;

    View();
    View(Vector2 position, Vector2 screenCenter);
    View(float positionX, float positionY, float screeCenterX, float screeCenterY);

    void SetScreenCenter(const Vector2& center);
    void SetPosition(const Vector2& newPosition);
    void Move(const Vector2& delta);

    void SetAngle(float newAngle);
    void Rotate(float amount);

    void SetZoom(float newZoom);
    void Zoom(float amount);

    Vector2 WorldToScreen(const Vector2& worldPosition);
    Vector2 ScreenToWorld(const Vector2& screenPosition);

    float GetZoom();
    Vector2 GetPosition();
    float GetAngle();

private:
    Vector2 screenCenter;
    Vector2 position;
    float angle;
    float zoom;
    float sin0;
    float cos0;
};
```

Example:

```cpp
View camera({0,0}, {Screen::Width()/2.0f, Screen::Height()/2.0f});
camera.SetZoom(1.5f);
camera.SetAngle(0.5f);
Screen::SetView(camera);
```

---

### `Time` – Frame Timing

**Header:** `Core/Timer.h`

```cpp
class Time
{
public:
    static float TimeScale;
    static double deltaTime;

    Time(const Time &) = delete;
    void operator=(const Time &) = delete;

    static Time &GetInstance();

    static void Tick();
    static void Reset();

private:
    Time();

    std::chrono::steady_clock::time_point StartTime;
    std::chrono::duration<double> DeltaTime;
};
```

- `deltaTime` – seconds between frames.
- `TimeScale` – multiplier for time (e.g. 0.5 = slow motion).
- `Tick()` – called each frame internally by the engine.

Use in code:

```cpp
position += velocity * (float)Time::deltaTime;
```

---

### `Color`

**Header:** `Core/Color.h`

```cpp
class Color
{
public:
    int r, g, b;
    float a;

    Color();
    Color(int r, int g, int b);
    Color(int r, int g, int b, float a);

    static Color RandomColor();

    bool operator!=(const Color &other) const;
    bool operator==(const Color &other) const;

    Color operator*(float factor) const;
    Color operator/(float factor) const;
    Color operator*(const Color &other) const;
    Color operator/(const Color &other) const;
    Color operator+(float amount) const;
    Color operator-(float amount) const;
    Color operator+(const Color &other) const;
    Color operator-(const Color &other) const;

    static const Color Transparent;
    static const Color White;
    static const Color Black;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Cyan;
    static const Color Purple;
    static const Color Gray;
};
```

Presets: `Transparent, White, Black, Red, Green, Blue, Yellow, Cyan, Purple, Gray`.

---

## 📐 Math & Utilities

### `Vector2`

**Header:** `Vector2.h`

```cpp
class Vector2
{
public:
    float x, y;

    Vector2();
    Vector2(float x, float y);

    Vector2 &operator=(const Vector2 vector);
    bool operator!() const;
    bool operator==(const Vector2 &vector);
    bool operator!=(const Vector2 &vector);

    Vector2 operator-() const;
    Vector2 operator+(const Vector2 &vector) const;
    Vector2 operator-(const Vector2 &vector) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;
    Vector2 operator*(const Vector2 &vector) const;
    Vector2 operator/(const Vector2 &vector) const;

    Vector2 &operator+=(const Vector2 &vector);
    Vector2 &operator-=(const Vector2 &vector);
    Vector2 &operator*=(float scalar);
    Vector2 &operator/=(float scalar);

    static float Length(const Vector2 &vector);
    static Vector2 Normalize(Vector2 &vector);
    static float Distance(const Vector2 &a, const Vector2 &b);
    static float DotProduct(const Vector2 &a, const Vector2 &b);
    static float CrossProduct(const Vector2 &a, const Vector2 &b);

    const static Vector2 ZERO;
    const static Vector2 UP;
    const static Vector2 DOWN;
    const static Vector2 RIGHT;
    const static Vector2 LEFT;
};
```

---

### `UMath`

**Header:** `UMath.h`

```cpp
const double PI = 3.1415926535897932384;

const float DEG_TO_RAD = PI / 180.0f;
const float RAD_TO_DEG = 180.0f / PI;

float NormalizeAngle(float &angle);
```

---

## 🎨 Graphics Module (`Include/Graphics`)

### `Vertex`

**Header:** `Graphics/Vertex.h`

```cpp
class Vertex
{
public:
    Vector2 position;
    Color color;

    Vertex();
    Vertex(float x, float y, Color color = Color::Transparent);
    Vertex(Vector2 position, Color color = Color::Transparent);
};
```

---

### `BoundingBox`

**Header:** `Graphics/BoundingBox.h`

```cpp
class BoundingBox
{
public:
    float left, right, top, bottom;

    BoundingBox();
    BoundingBox(int left, int top, int right, int bottom);
};
```

---

### `Transform`

**Header:** `Graphics/Transform.h`

```cpp
class Transform
{
public:
    bool update;

    Transform();
    Transform(Vector2 position, Vector2 scale, float angle);
    Transform(float x, float y, float scaleX, float scaleY, float angle);

    void SetPosition(float x, float y);
    void SetScale(float factorX, float factorY);
    void SetAngle(float angle);

    void SetPosition(Vector2 position);
    void SetScale(Vector2 scale);

    Vector2 GetPosition();
    Vector2 GetScale();
    float GetAngle();

    Vector2 Right();
    Vector2 Up();

    void Move(Vector2 amount);
    void Scale(Vector2 amount);
    void Rotate(float amount);
    void Move(float amountX, float amountY);
    void Scale(float amountX, float amountY);

    Vector2 SinCosUpdate();

private:
    Vector2 position;
    Vector2 scale;
    float angle;

    float sin0;
    float cos0;

    Vector2 right;
    Vector2 up;

    friend Vector2 TransformVertex(const Transform &transform, Vector2 vertex);
};

Vector2 TransformVertex(const Transform &transform, Vector2 vertex);
```

---

### `Shape`

**Header:** `Graphics/Shape.h`

```cpp
class Shape
{
protected:
    std::vector<Vertex> vertices;

private:
    std::vector<Vertex> Tvertices;
    std::vector<Vertex> VTvertices;
    BoundingBox boundingBox;
    BoundingBox VBoundingBox;
    Color color;
    Color fillColor;

    friend void DrawShape(Shape &shape);
    Shape() {}

public:
    Transform transform;

    Shape(const std::vector<Vertex> &vertices);

    std::vector<Vertex> GetTvertices();
    BoundingBox GetBoundingBox();

    void SetColor(Color color);
    void SetFillColor(Color color);
};

std::vector<Vertex> UpdateVertices(Transform &transform, const std::vector<Vertex> &vertices);
BoundingBox UpdateAABB(const std::vector<Vertex> &vertices);
```

---

### Rectangle & Ellipse

**Header:** `Graphics/Rectangle.h`

```cpp
namespace Shapes
{
    class Rectangle : public Shape
    {
    private:
        float width, height;

    public:
        Rectangle();
        Rectangle(float width, float height);
    };
}
```

**Header:** `Graphics/Elipse.h`

```cpp
namespace Shapes
{
    class Elipse : public Shape
    {
    private:
        float radiusX, radiusY;
        int point_count;

    public:
        Elipse();
        Elipse(float radiusX, float radiusY, const int point_count = 30);
    };   
}
```

**Example:**

```cpp
Shapes::Rectangle rect(100, 50);
rect.SetColor(Color::Green);
rect.transform.SetPosition(200, 150);
DrawShape(rect);
```

---

### `Text` & `Font`

**Header:** `Graphics/Text.h`

```cpp
class Text
{
protected:
    std::vector<Vertex> vertices;

private:
    std::vector<Vertex> Tvertices;
    std::vector<int> indices;
    BoundingBox boundingBox;
    Color color;
    Color fillColor;
    std::string string;

    friend void DrawTEXT(Text& text);

public:
    Text();

    Transform transform;

    std::vector<Vertex> GetTvertices();
    BoundingBox GetBoundingBox();

    void SetString(const std::string &text);

    void SetColor(Color color);
};
```

**Header:** `Graphics/Font.h`

```cpp
struct Character
{
    std::vector<Vertex> vertices;
    std::vector<int> indices;
    float devance;
    float advance;
};

class Font
{
private:
    static std::map<char, Character> characters;
    Font();

public:
    Font(const Font &) = delete;
    void operator=(const Font &) = delete;

    static Font &GetInstance();
    static Character GetC(char character);
};
```

**Example:**

```cpp
Text fpsText;
fpsText.SetString("Hello, PiXELGraph!");
fpsText.SetColor(Color::White);
fpsText.transform.SetPosition(5, 5);

DrawTEXT(fpsText);
```

---

## 🔊 Audio Module (`Include/Audio`)

### `AudioClip`

**Header:** `Audio/AudioClip.h`

```cpp
class AudioClip
{
private:
    std::string audioFilePath;
    float volume;

    friend class AudioSource;

public:
    AudioClip();
    AudioClip(const std::string &audioFile, float volume = 1.0f);

    void SetVolume(float newVolume);
    float GetVolume();
    void SetAudioFile(const std::string &audioFile);
};
```

---

### `AudioSource`

**Header:** `Audio/AudioSource.h`

```cpp
class AudioSource
{
private:
    AudioSource();

    ma_engine audio_engine;
    float masterVolume;

    friend class PiXELGraph;

    static void Dispose();

public:
    AudioSource(const AudioSource &) = delete;
    void operator=(const AudioSource &) = delete;

    static AudioSource &GetInstance();

    static void PlaySound(const AudioClip &clip);

    static void SetVolume(float newVolume);
    static float GetVolume();
};
```

**Example:**

```cpp
AudioClip jump("Resources/jump.wav", 0.8f);
AudioSource::PlaySound(jump);

AudioSource::SetVolume(0.5f);  // master volume
```

---

## ⌨ Console / Input Module (`Include/Console`)

### `Debug`

**Header:** `Console/Debug.h`

```cpp
class Debug
{
private:
    Debug() {};
    static std::ofstream debugBuffer;

public:
    Debug(const Debug &) = delete;
    void operator=(const Debug &) = delete;

    static Debug &GetDebug();
    static void Log(std::string log);
    static void KillDebuger();
};
```

Example:

```cpp
Debug::Log("Scene started");
```

---

### `Error`

**Header:** `Console/ErrorSystem.h`

```cpp
class Error : public std::exception
{
private:
    std::string message;

public:
    explicit Error(const std::string &msg);
    const char *what() const noexcept override;
};
```

---

### Events

**Header:** `Console/EventSystem.h`

```cpp
enum EventType
{
    EVENT_NONE,
    EVENT_KEY_PRESS,
    EVENT_KEY_RELEASE,
    EVENT_MOUSE_MOVE,
    EVENT_MOUSE_LCLICK,
    EVENT_MOUSE_RCLICK,
    EVENT_MOUSE_MCLICK,
    EVENT_MOUSE_SCROLL_UP,
    EVENT_MOUSE_SCROLL_DOWN,
};

class Event
{
private:
    friend class PiXELGraph;

    static void FetchEventData();
    static EventType event;

public:
    Event(const Event &) = delete;
    void operator=(const Event &) = delete;

    static char UChar;

    static EventType GetEvent();

    static Event &GetInstance();
};
```

---

### Input

**Header:** `Console/InputSystem.h`

```cpp
enum Key
{
    Key_None = 0,
    Key_Backspace = VK_BACK,
    Key_Tab = VK_TAB,
    Key_Enter = VK_RETURN,
    Key_CapsLock = VK_CAPITAL,
    Key_Delete = VK_DELETE,
    Key_Escape = VK_ESCAPE,
    // many more: all VK_* mapped to readable names
    Key_Space = VK_SPACE,
    // ...
};

enum MouseButton
{
    Left   = 0,
    Right  = 1,
    Middle = 2,
    Back   = 3,
    Forward= 4
};

struct KeyState
{
    bool pressed = false;
    bool wasPressed = false;
};

struct MouseButtonState
{
    bool pressed = false;
    bool wasPressed = false;
};

class Input
{
private:
    friend class PiXELGraph;

    std::unordered_map<Key, KeyState> Keyboard;
    std::unordered_map<MouseButton, MouseButtonState> Mouse;

    static Vector2 MousePosition;

    static void FetchInputData();

public:
    Input(const Input &) = delete;
    void operator=(const Input &) = delete;

    static bool IsKeyDown(Key key);
    static bool IsKeyUp(Key key);
    static bool IsKey(Key key);

    static bool IsMouseButtonDown(MouseButton button);
    static bool IsMouseButtonUp(MouseButton button);
    static bool IsMouseButton(MouseButton button);

    static Input &GetInstance();

    static Vector2 MousePosition;
};
```

**Usage:**

```cpp
if (Input::IsKeyDown(Key_Space))
{
    Debug::Log("Space pressed this frame");
}

if (Input::IsKey(Key_A))
{
    // A is being held
}

Vector2 mousePos = Input::MousePosition;
```

---

### Window

**Header:** `Console/Window.h`

```cpp
class Window
{
private:
    Window() {}

    static HWND CONSOLE_WINDOW;
    HANDLE ConsoleOutputH;
    static HANDLE ConsoleInputtH;

    static int WIDTH;
    static int HEIGHT;
    static int FONT_SIZE;
    static std::wstring TITLE;

    void ConstructWindow();

public:
    Window(const Window &) = delete;
    void operator=(const Window &) = delete;

    void SetParameters(int width, int height, int fontSize, const std::wstring &title);

    static Window &GetInstance();

    static void SetTitle(const std::wstring &title);

    static bool Focused();

    static int WindowWidth();
    static int WindowHeight();
    static int WindowFontSize();
    static std::wstring WindowTitle();
    static HWND &ConsoleWindow();
    static HANDLE &ConsoleInputHandle();
};
```

Most of the time you don’t need to call this directly—`PiXELGraph::Init` does it.

---

## 📦 Third-Party & Extras

- `Include/nlohmann/json.hpp` – [nlohmann/json](https://github.com/nlohmann/json) single-header JSON library.
- `Include/miniaudio.h` – [miniaudio](https://miniaud.io/) single-header audio library.
- `Resources/font.cf` – default font used by the text system.

---

## ✅ Summary

PiXELGraph v2 gives you:

- A **scene-based engine loop**
- Simple **vector-based 2D drawing** on a console window
- **Input**, **events**, and **audio** in a compact API

You write:

- Your own scenes by deriving from `Scene`
- Use `Screen`, `Shape`, `Text`, `Input`, `AudioSource` etc.
- Let `PiXELGraph` and `SceneManager` handle the rest.

Enjoy building stuff. 🙂

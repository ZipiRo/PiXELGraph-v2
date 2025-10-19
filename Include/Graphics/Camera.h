#pragma once

#include "Vector2.h"

class Camera 
{
private:
    static Vector2 screenCenter;
    static Vector2 position;
    static float zoom;

    Camera() {}

public:
    static Camera& GetInstance();

    static void SetScreenCenter(const Vector2& center);
    
    static void SetPosition(const Vector2& newPosition);
    static void Move(const Vector2& delta);

    static void SetZoom(float newZoom);
    static void Zoom(float amount);

    static Vector2 WorldToScreen(const Vector2& worldPosition);
    static Vector2 ScreenToWorld(const Vector2& screenPosition);

    static float GetZoom();
    static Vector2 GetPosition();
};
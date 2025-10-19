#include "Vector2.h"
#include "Graphics/Camera.h"

Vector2 Camera::position = Vector2::ZERO;
Vector2 Camera::screenCenter = Vector2::ZERO;
float Camera::zoom = 1;

Camera& Camera::GetInstance()
{
    static Camera instance;
    return instance;
}

void Camera::SetPosition(const Vector2 &newPosition) 
{
    position = newPosition;
}

void Camera::SetScreenCenter(const Vector2 &center)
{
    screenCenter = center;
}

void Camera::Move(const Vector2& delta)
{
    position += delta;
}

void Camera::SetZoom(float newZoom)
{
    zoom = newZoom;
}

void Camera::Zoom(float amount)
{
    zoom += amount;
    if (zoom < 0.1f) zoom = 0.1f;
}

Vector2 Camera::WorldToScreen(const Vector2& worldPosition)
{
    return (worldPosition - position) * zoom + screenCenter;
}

Vector2 Camera::ScreenToWorld(const Vector2& screenPosition)
{
    return (screenPosition - screenCenter) / zoom + position;
}

float Camera::GetZoom() { return zoom; }
Vector2 Camera::GetPosition() { return position; }
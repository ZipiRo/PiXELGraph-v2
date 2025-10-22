#include "Vector2.h"
#include "Core/ViewPort.h"

View::View()
{
    this->position = Vector2::ZERO;
    this->screenCenter = Vector2::ZERO;
    zoom = 1;
    update = true;
}

View::View(Vector2 position, Vector2 screenCenter)
{
    this->position = position;
    this->screenCenter = screenCenter;
    zoom = 1;
    update = true;
}

View::View(float positionX, float positionY, float screeCenterX, float screeCenterY)
{
    this->position = Vector2(positionX, positionY);
    this->screenCenter = Vector2(screeCenterX, screeCenterY);
    zoom = 1;
    update = true;
}

void View::Move(const Vector2 &delta)
{
    position += delta;
    update = true;
}

void View::SetZoom(float newZoom)
{
    zoom = newZoom;
    update = true;
}

void View::Zoom(float amount)
{
    zoom += amount;
    if (zoom < 0.1f)
        zoom = 0.1f;
    update = true;
}

void View::SetPosition(const Vector2 &newPosition)
{
    position = newPosition;
    update = true;
}

void View::SetScreenCenter(const Vector2 &center)
{
    screenCenter = center;
    update = true;
}

Vector2 View::WorldToScreen(const Vector2 &worldPosition)
{
    return (worldPosition - position) * zoom + screenCenter;
}

Vector2 View::ScreenToWorld(const Vector2 &screenPosition)
{
    return (screenPosition - screenCenter) / zoom + position;
}

float View::GetZoom() { return zoom; }
Vector2 View::GetPosition() { return position; }
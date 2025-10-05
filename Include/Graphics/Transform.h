#pragma once

#include "Vector2.h"

class Transform
{
private:
    Vector2 position;
    Vector2 scale;
    float angle;
    float sin0;
    float cos0;

    Vector2 right;
    Vector2 up;

    friend Vector2 TransformVertex(const Transform &transform, Vector2 vertex);
public:
    Transform();
    Transform(Vector2 position, Vector2 scale, float angle);

    void SetPosition(float x, float y);
    void SetScale(float factorX, float factorY);
    void SetAngle(float angle);

    Vector2 GetPosition();
    Vector2 GetScale();
    float GetAngle();

    void Move(Vector2 amount);
    void Scale(Vector2 amount);
    void Rotate(float amount);

    Vector2 SinCosUpdate();
    bool update;
};
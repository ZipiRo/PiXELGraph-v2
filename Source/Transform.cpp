#include "Graphics/Transform.h"
#include "UMath.h"

Transform::Transform()
{
    position = Vector2::ZERO;
    scale = Vector2(1, 1);
    angle = 0;
    sin0 = 0;
    cos0 = 1;
    right = Vector2::RIGHT;
    up = Vector2::UP;
    update = true;
}

Transform::Transform(Vector2 position, Vector2 scale, float angle)
{
    this->position = position;
    this->scale = scale;
    this->angle = angle;
    sin0 = sin(angle);
    cos0 = cos(angle);
    right = Vector2(cos0, sin0);
    up = Vector2(sin0, -cos0);
    update = true;
}

void Transform::SetPosition(float x, float y)
{
    position = Vector2(x, y);
    update = true;
}

void Transform::SetScale(float factorX, float factorY)
{
    scale = Vector2(factorX, factorY); 
    update = true;
}

void Transform::SetAngle(float angle)
{
    NormalizeAngle(this->angle);
    this->angle = angle;     
    update = true;
}

Vector2 Transform::GetPosition()
{
    return position;
}

Vector2 Transform::GetScale()
{
    return scale;
}

float Transform::GetAngle()
{
    return angle;
}

void Transform::Move(Vector2 amount)
{
    position += amount;
    update = true;
}

void Transform::Scale(Vector2 amount)
{
    scale += amount;
    update = true;
}

void Transform::Rotate(float amount)
{
    angle += amount;
    NormalizeAngle(angle);
    update = true;
}

Vector2 Transform::SinCosUpdate()
{
    cos0 = cos(angle);
    sin0 = sin(angle);

    right = Vector2(cos0, sin0);
    up = Vector2(sin0, -cos0);

    return Vector2(cos0, sin0);
}

Vector2 TransformVertex(const Transform &transform, Vector2 vertex)
{
    float sx = vertex.x * transform.scale.x;
    float sy = vertex.y * transform.scale.y;

    float rx = transform.cos0 * sx - transform.sin0 * sy;
    float ry = transform.sin0 * sx + transform.cos0 * sy;

    float tx = rx + transform.position.x;
    float ty = ry + transform.position.y;


    return Vector2(tx, ty);
}

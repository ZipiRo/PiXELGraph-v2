#include "UMath.h"

float NormalizeAngle(float &angle)
{
    float new_angle = angle - floor(angle / (2.0f * PI)) * (2.0f * PI);
    
    if (new_angle < 0)
        new_angle += 2.0f * PI;
    
    angle = new_angle;

    return new_angle;
}
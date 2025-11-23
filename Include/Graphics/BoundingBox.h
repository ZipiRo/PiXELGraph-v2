#pragma once

class BoundingBox
{
public:
    float left, right, top, bottom;

    BoundingBox();
    BoundingBox(int left, int top, int right, int bottom);
};
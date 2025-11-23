#include "Graphics/BoundingBox.h"

BoundingBox::BoundingBox()
{
    this->left = 0;
    this->top = 0;
    this->right = 0;
    this->bottom = 0;
}

BoundingBox::BoundingBox(int left, int top, int right, int bottom)
{
    this->left = left;
    this->top = top;
    this->right = right;
    this->bottom = bottom;
}
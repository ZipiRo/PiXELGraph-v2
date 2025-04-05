#pragma once

class Color
{
public:
    int r, g, b, a; 

    Color();
    Color(int r, int g, int b);
    Color(int r, int g, int b, int a);

    bool operator!= (const Color &other) const;
    bool operator== (const Color &other) const;

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
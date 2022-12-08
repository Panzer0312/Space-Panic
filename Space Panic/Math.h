#pragma once

enum objectType
{
    ENEMY, PLAYER, BRICK, LADDER
};

struct Vector2f
{
    union {
        float x;
        float u;
    };

    union {
        float y;
        float v;
    };

    Vector2f()
    {
        x = 0;
        y = 0;
    }

    Vector2f(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
};


inline Vector2f operator*(const Vector2f& l, float f)
{
    Vector2f Ret(l.x * f, l.y * f);

    return Ret;
}

inline Vector2f operator+(const Vector2f& l, const Vector2f& f)
{
    Vector2f Ret(l.x + f.x, l.y * f.y);

    return Ret;
}
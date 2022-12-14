#pragma once

/** object Types to differenciate the GameObjects */
enum objectType
{
    ENEMY, PLAYER, BRICK, LADDER
};

/** Vector for 2D float operations */
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
/** Vector for 2D int operations */
struct Vector2i
{
    union {
        int x;
        int u;
    };

    union {
        int y;
        int v;
    };

    Vector2i()
    {
        x = 0;
        y = 0;
    }

    Vector2i(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
};


/** Multiplication of a float Vector */
inline Vector2f operator*(const Vector2f& l, float f)
{
    Vector2f Ret(l.x * f, l.y * f);

    return Ret;
}
/** Addition of two float Vector */
inline Vector2f operator+(const Vector2f& l, const Vector2f& f)
{
    Vector2f Ret(l.x + f.x, l.y + f.y);

    return Ret;
}
/** Subtraction of two float Vector */
inline Vector2f operator-(const Vector2f& l, const Vector2f& f)
{
    Vector2f Ret(l.x - f.x, l.y - f.y);

    return Ret;
}
/** Division of a float Vector */
inline Vector2f operator/(const Vector2f& l, const float i)
{
    Vector2f Ret(l.x / float(i), l.y / float(i ));

    return Ret;
}
/** Greater than operation of two float Vectors */
inline bool operator>(const Vector2f& l, const Vector2f& f)
{
    bool out = false;
    if (l.x > f.x && l.y > f.y) {
        out = true;
    }

    return out;
}
/** Less than operation of two float Vectors */
inline bool operator<(const Vector2f& l, const Vector2f& f)
{
    bool out = false;
    if (l.x < f.x && l.y < f.y) {
        out = true;
    }
    return out;
}
/** Equal operation of two float Vectors */
inline bool operator==(const Vector2f& l, const Vector2f& f)
{
    bool out = false;
    if (l.x == f.x && l.y == f.y) {
        out = true;
    }

    return out;
}
/** Equal operation of two int Vectors */
inline bool operator==(const Vector2i& l, const Vector2i& f)
{
    bool out = false;
    if (l.x == f.x && l.y == f.y) {
        out = true;
    }

    return out;
}
/** Addition of two int Vector */
inline Vector2f operator+(const Vector2f& l, const Vector2i& f)
{
    Vector2f Ret(l.x + f.x, l.y + f.y);

    return Ret;
}
/** Addition of one float with one int Vector */
inline Vector2i operator+(const Vector2i& l, const Vector2i& f)
{
    Vector2i Ret(l.x + f.x, l.y + f.y);

    return Ret;
}
/** Multiplication of an int Vector */
inline Vector2i operator*(const Vector2i& l, int f)
{
    Vector2i Ret(l.x * f, l.y * f);

    return Ret;
}
#pragma once

/** Object Types to differenciate between the GameObjects */
enum objectType
{
    ENEMY, PLAYER, BRICK, LADDER, TIMER, LIFE
};
/** The possibilities an alien is allowed to make */
enum enemyDecision
{
    LADDERUP,LADDERDOWN,LEFT,RIGHT
};

/** Vector for 2D float operations */
struct Vector2f
{
    float x, y;

    Vector2f()
    {
        x = 0;
        y = 0;
    }
    /**
     * .
     * Constructor of this Vector
     * \param _x New integer x value of the Vector2f
     * \param _y New integer y value of the Vector2f
     */
    Vector2f(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
};
/** Vector for 2D integer operations */
struct Vector2i
{
    int x, y;

    Vector2i()
    {
        x = 0;
        y = 0;
    }
    /**
     * .
     * Constructor of this Vector
     * \param _x New integer x value of the Vector2i
     * \param _y New integer y value of the Vector2i
     */
    Vector2i(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
};


/** Multiplication of a Vector2f with a float number  */
inline Vector2f operator*(const Vector2f& l, float f)
{
    Vector2f Ret(l.x * f, l.y * f);

    return Ret;
}
/** Addition of two Vector2f*/
inline Vector2f operator+(const Vector2f& l, const Vector2f& f)
{
    Vector2f Ret(l.x + f.x, l.y + f.y);

    return Ret;
}
/** Subtraction of two Vector2f*/
inline Vector2f operator-(const Vector2f& l, const Vector2f& f)
{
    Vector2f Ret(l.x - f.x, l.y - f.y);

    return Ret;
}
/** Division of a Vector2f and a float number */
inline Vector2f operator/(const Vector2f& l, const float i)
{
    Vector2f Ret(l.x / float(i), l.y / float(i ));

    return Ret;
}
/** Greater than operation of two Vector2f */
inline bool operator>(const Vector2f& l, const Vector2f& f)
{
    bool out = false;
    if (l.x > f.x && l.y > f.y) {
        out = true;
    }

    return out;
}
/** Less than operation of two Vector2f */
inline bool operator<(const Vector2f& l, const Vector2f& f)
{
    bool out = false;
    if (l.x < f.x && l.y < f.y) {
        out = true;
    }
    return out;
}
/** Equal operation of two Vector2f */
inline bool operator==(const Vector2f& l, const Vector2f& f)
{
    bool out = false;
    if (l.x == f.x && l.y == f.y) {
        out = true;
    }

    return out;
}
/** Equal operation of two Vector2i */
inline bool operator==(const Vector2i& l, const Vector2i& f)
{
    bool out = false;
    if (l.x == f.x && l.y == f.y) {
        out = true;
    }

    return out;
}
/** Addition of a Vector2i and a Vector2f*/
inline Vector2f operator+(const Vector2f& l, const Vector2i& f)
{
    Vector2f Ret(l.x + f.x, l.y + f.y);

    return Ret;
}
/** Addition of two Vector2i */
inline Vector2i operator+(const Vector2i& l, const Vector2i& f)
{
    Vector2i Ret(l.x + f.x, l.y + f.y);

    return Ret;
}
/** Multiplication of an Vector2i with a integer number */
inline Vector2i operator*(const Vector2i& l, int f)
{
    Vector2i Ret(l.x * f, l.y * f);

    return Ret;
}
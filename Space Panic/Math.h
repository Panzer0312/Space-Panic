#pragma once
/** Object Types to differenciate between the GameObjects */
enum ObjectType
{
    ENEMY, PLAYER, BRICK, LADDER, TIMER, LIFE
};
/** The possibilities an alien is allowed to make */
enum ControlledObjectDecision
{
    NOTHING,LADDERUP,LADDERDOWN,LEFT,RIGHT,DIGLEFT,DIGRIGHT,FALLING,HANGING,PUSHUP
};

enum EnemyType {
    NORMENEMY, BIGENEMY
};
enum BrickType {
    BRICK0, BRICK1
};
enum TimerType {
    TIMER0, TIMER1
};

enum GameObjectState {
    ALIVE,VISABLE,AIRLESS,VANISHED,DEAD,DIGSTART
};

struct ObjectProps {
    int id;
    ObjectType type;
    char closerType;
    ObjectProps() {
        id = 0;
        type = BRICK;
        closerType = '-';
    }
    ObjectProps(int _id, ObjectType _type, char _closerType) {
        id = _id;
        type = _type;
        closerType = _closerType;
    }
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

struct DrawingObjectProps {
    ObjectProps objP;
    ControlledObjectDecision dec;
    Vector2f position;
    int scale;
    GameObjectState state;
    int counter;

    DrawingObjectProps() {
        objP = ObjectProps();
        dec = NOTHING;
        position = Vector2f(0, 0);
        scale = 0;
        state = ALIVE;
        counter = 0;
    }
    DrawingObjectProps(ObjectProps _objP, ControlledObjectDecision _dec, Vector2f _position, int _scale, GameObjectState _state, int _counter) {
        objP = _objP;
        dec = _dec;
        position = _position;
        scale = _scale;
        state = _state;
        counter = _counter;
    }
    DrawingObjectProps(ObjectProps _objP,Vector2f _position, int _scale, GameObjectState _state, int _counter) {
        dec = NOTHING;
        objP = _objP;
        position = _position;
        scale = _scale;
        state = _state;
        counter = _counter;
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
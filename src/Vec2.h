#ifndef _VEC2_H
#define _VEC2_H

class Vec2{
    public:
        Vec2();
        Vec2(int x, int y);
        float x, y;
        Vec2 GetRotated(float angle);
        friend Vec2 operator + (Vec2 const &, Vec2 const &);

};

#endif
#ifndef _VECTOR2D_HPP
#define _VECTOR2D_HPP

#include <cmath>
#include <iostream>

class Vector2D
{
public:
    Vector2D(float x, float y) : xPos(x), yPos(y) {}

    Vector2D operator+(const Vector2D &v) const;
    friend Vector2D& operator+=(Vector2D &v1, const Vector2D &v2);

    Vector2D operator*(float number) const;
    Vector2D& operator*=(float number);

    Vector2D operator-(const Vector2D &v) const;
    friend Vector2D& operator-=(Vector2D &v1, const Vector2D &v2);

    Vector2D operator/(float number) const;
    Vector2D& operator/=(float number);

    void normalize();

    float getLength() {return sqrt(xPos*xPos + yPos*yPos);}

    float getX() {return xPos;}
    float getY() {return yPos;}
    
    void setX(float x) {this->xPos = x;}
    void setY(float y) {this->yPos = y;}

private:
    float xPos;
    float yPos;
};



#endif
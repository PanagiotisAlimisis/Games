#include "Vector2D.hpp"


Vector2D Vector2D::operator+(const Vector2D &v) const
{
    return Vector2D(xPos + v.xPos, yPos +v.yPos);
}


Vector2D& operator+=(Vector2D &v1, const Vector2D &v2)
{
    v1.xPos += v2.xPos;
    v1.yPos += v2.yPos;

    return v1;
}


Vector2D Vector2D::operator*(float number) const
{
    return Vector2D(xPos*number, yPos*number);
}


Vector2D& Vector2D::operator*=(float number)
{
    xPos *= number;
    yPos *= number;
    
    return *this;
}


Vector2D Vector2D::operator-(const Vector2D &v) const
{
    return Vector2D(xPos - v.xPos, yPos - v.yPos);
}


Vector2D& operator-=(Vector2D &v1, const Vector2D &v2)
{
    v1.xPos -= v2.xPos;
    v1.yPos -= v2.yPos;
    
    return v1;
}


Vector2D Vector2D::operator/(float number) const
{
    return Vector2D(xPos/number, yPos/number);
}


Vector2D& Vector2D::operator/=(float number)
{
    xPos /= number;
    yPos /= number;
    
    return *this;
}


void Vector2D::normalize()
{
    float l = getLength();

    if (l > 0)
    {
        (*this) *= (1 / l); 
    }
}
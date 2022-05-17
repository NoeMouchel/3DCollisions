#include <cmath>

#include "../Include/Vector2.h"
#include "../Include/Range2.h"
#include "../Include/Utils.h"


ToolBox::Vector2f::Vector2f()
{
    this->x = 0;
    this->y = 0;
}

ToolBox::Vector2f::Vector2f(float value)
{
    this->x = value;
    this->y = value;
}

ToolBox::Vector2f::Vector2f(float x_value,float y_value)
{
    this->x = x_value;
    this->y = y_value;
}

ToolBox::Vector2f::Vector2f(Vector2f vectA, Vector2f vectB)
{
    this->x = vectB.x - vectA.x;
    this->y = vectB.y - vectA.y;
}

float ToolBox::Vector2f::length()
{
    return sqrt(this->x*this->x + this->y*this->y);
}

float ToolBox::Vector2f::squareLength() const
{
    return (this->x * this->x + this->y * this->y);
}
    
ToolBox::Vector2f ToolBox::Vector2f::normalized()
{
    Vector2f unit_vector;
    float length = this->length();
    if (length != 0)
    {
        unit_vector = { this->x / length, this->y / length };
        return unit_vector;
    }
    return unit_vector;
}

float ToolBox::Vector2f::dot(Vector2f vect)
{
    return  vect.x * this->x + vect.y * this->y;
}


ToolBox::Vector2f ToolBox::Vector2f::opposite()
{
    return (*this)*(-1.f);
}

float ToolBox::Vector2f::distance(Vector2f pos)
{
    Vector2f result(pos.x - this->x, pos.y - this->y);
    return result.length();
}

double ToolBox::Vector2f::angle(Vector2f vect)
{
    return acos(this->dot(vect.normalized()));
}

bool ToolBox::Vector2f::compare(Vector2f vect)
{
    return (this->distance(vect) < EPSILON);
}


//ANGLE APPLICATIONS

ToolBox::Vector2f    ToolBox::Vector2f::rotate(float angle)
{
    float x_result = cos(angle) * this->x - sin(angle) * this->y;
    float y_result = sin(angle) * this->x + cos(angle) * this->y;

    this->x = x_result;
    this->y = y_result;

    return *this;
}

ToolBox::Vector2f    ToolBox::Vector2f::rotatePoint(Vector2f center, float angle)
{
    Vector2f vect = *this - center; 
    return vect.rotate(angle) + center;
}

ToolBox::Vector2f    ToolBox::Vector2f::rotate90()
{
    Vector2f vect(-(this->y), this->x);
    return vect;
}

ToolBox::Vector2f   ToolBox::Vector2f::normalVector()
{
    Vector2f vect = this->normalized();
    return vect.rotate90();
}
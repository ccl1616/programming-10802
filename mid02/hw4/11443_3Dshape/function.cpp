// 3D shape
#include <iostream>
#include <string>
#include "function.h"
using namespace oj; //this is necessary

//remark for this question
// 1. filter out the inreasonable case, for which length<0 || pi < 0
//      the volume of it would be 0
// 2. the type of volume is double.  4/3=1 (int),  so it should be 4.0/3.0
// 3. Cube inherited Cuboid not Shape3D. !!!

Sphere::Sphere(double r,double p)
{
    this->radius = r;
    this->pi = p;
    if(r <= 0 || p <= 0)
        setVolume(0);
    else setVolume( (4.0/3.0) * r *r *r * p);
}

Cone::Cone(double r, double h,double p)
{
    this->radius = r;
    this->height = h;
    this->pi = p;
    if(r <= 0 || h <= 0 || p <= 0)
        setVolume(0);
    else setVolume( (1.0/3.0) * p * r * r * h);
}

Cuboid::Cuboid(double l, double w, double h)
{
    this->length = l;
    this->width = w;
    this->height = h;
    if(l <= 0 || w <= 0 || h <= 0)
        setVolume(0);
    else setVolume(l * w * h);
}

// !!
Cube::Cube(double l)
    : Cuboid::Cuboid(l, l, l) //calling dad, cause it's inherited from cuboid
{
    if(l <= 0)
        setVolume(0);
    else setVolume(l * l * l);
}
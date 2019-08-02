#include "stdafx.h"
#include "oepVector.h"

using namespace gEarthPack;

oepVec3f::oepVec3f(float xval, float yval, float zval) : x(xval),y(yval),z(zval)
{

}

oepVec3f::oepVec3f(const osg::Vec3f& v):x(v.x()),y(v.y()),z(v.z())
{

}

oepVec4f::oepVec4f(float xval, float yval, float zval, float aval) : x(xval), y(yval), z(zval),a(aval)
{

}

oepVec4f::oepVec4f(const osg::Vec4f& v) : x(v.x()), y(v.y()), z(v.z()),a(v.a())
{

}

oepVec2f::oepVec2f(float xval, float yval) : x(xval), y(yval)
{

}

oepVec2f::oepVec2f(const osg::Vec2f& v):x(v.x()), y(v.y())
{

}

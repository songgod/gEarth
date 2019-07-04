#pragma once
#include <osg/Vec2f>
#include <osg/Vec3f>
#include <osg/Vec4f>

namespace gEarthPack
{
	public value struct oepVec2f
	{
		oepVec2f(float xval, float yval);
		oepVec2f(const osg::Vec2f& v);
		float x;
		float y;
	};

	public value struct oepVec3f
	{
		oepVec3f(float xval, float yval, float zval);
		oepVec3f(const osg::Vec3f& v);
		float x;
		float y;
		float z;
	};

	public value struct oepVec4f
	{
		oepVec4f(float xval, float yval, float zval, float aval);
		oepVec4f(const osg::Vec4f& v);
		float x;
		float y;
		float z;
		float a;
	};
}


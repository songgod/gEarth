#pragma once

namespace gEarthPack
{
	public value struct oepVec2f
	{
		oepVec2f(float xval, float yval);
		float x;
		float y;

	internal:

		oepVec2f(const osg::Vec2f& v);
		osg::Vec2f as() { return osg::Vec2f(x, y); }
	};

	public value struct oepVec3f
	{
		oepVec3f(float xval, float yval, float zval);
		float x;
		float y;
		float z;

	internal:

		oepVec3f(const osg::Vec3f& v);
		osg::Vec3f as() { return osg::Vec3f(x, y,z); }
	};

	public value struct oepVec4f
	{
		oepVec4f(float xval, float yval, float zval, float aval);
		float x;
		float y;
		float z;
		float a;

	internal:

		oepVec4f(const osg::Vec4f& v);
		osg::Vec4f as() { return osg::Vec4f(x, y, z, a); }
	};
}


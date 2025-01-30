#pragma once

#include <afx/Math/Vector3.h>

///////////////////////////////////////////////////////////////////////////////////////

namespace arc {

///////////////////////////////////////////////////////////////////////////////////////

template<typename _Ty>
class Triangle
{

public:

	Vector3<_Ty> v0, v1, v2;

	Triangle( void ) : v0{}, v1{}, v2{} { }
	Triangle( const Vector3<_Ty>& _a,
			  const Vector3<_Ty>& _b,
			  const Vector3<_Ty>& _c )
		: v0{ _a }, v1{ _b }, v2{ _c }
	{
	}

	Vector3<_Ty> edge1() const { return v1 - v0; }
	Vector3<_Ty> edge2() const { return v2 - v0; }

	Vector3<_Ty> getNormal() const { return edge1().cross( edge2() ).normalized(); }

	Vector3<_Ty> barycentricToCartesian( const _Ty& _u, const _Ty& _v ) const;

};

///////////////////////////////////////////////////////////////////////////////////////

typedef Triangle<float>  Triangle3f;
typedef Triangle<double> Triangle3d;

///////////////////////////////////////////////////////////////////////////////////////

template<typename _Ty>
inline Vector3<_Ty> Triangle<_Ty>::barycentricToCartesian( const _Ty& _u, const _Ty& _v ) const
{
	// https://alexpolt.github.io/barycentric.html
	return v0 + edge1() * _u +
		edge2() * _v;
}

}
#pragma once

#include <afx/Math/Triangle.h>
//#include <afx/Mesh/MeshResource.h>

#include <afx/Math/Matrix.h>

///////////////////////////////////////////////////////////////////////////////////////

namespace arc {

///////////////////////////////////////////////////////////////////////////////////////

struct RayIntersection
{
	bool hit = false;
	Vector3f point;
	Vector3f planeProjectedPoint;

	float depth;
	float planeProjectedDepth;

	Triangle3f triangle;
};

///////////////////////////////////////////////////////////////////////////////////////

class Ray
{

public:

	Ray( void ) : start{ }, end{ } { }
	Ray( const Vector3f& _start, const Vector3f& _end ) : start{ _start }, end{ _end } { }

	Vector3f start;
	Vector3f end;

	template<typename _Ty>
	RayIntersection intersect( _Ty* _t );

	float length() { return ( end - start ).length(); }

};

///////////////////////////////////////////////////////////////////////////////////////

template<typename _Ty>
inline RayIntersection Ray::intersect( _Ty* _t ) { return {}; }

// https://fileadmin.cs.lth.se/cs/Personal/Tomas_Akenine-Moller/code/raytri_tam.pdf
template<>
inline RayIntersection Ray::intersect<Triangle3f>( Triangle3f* _t )
{
	if ( start == end )
		return {};

	Vector3f dir = end - start;
	dir.normalize();

	float u, v, t;

	Vector3f edge1 = _t->edge1();
	Vector3f edge2 = _t->edge2();
	Vector3f pvec = dir.cross( edge2 );
	float det = edge1.dot( pvec );

#ifndef TEST_CULL
	if ( det < arc::Const::Float::EPSILON )
		return {};

	Vector3f tvec = start - _t->v0;

	u = tvec.dot( pvec );
	if ( u < 0.0f || u > det )
		return {};

	Vector3f qvec = tvec.cross( edge1 );

	v = dir.dot( qvec );
	if ( v < 0.0f || u + v > det )
		return {};

	t = edge2.dot( qvec );
	float invDet = 1.0f / det;
	t *= invDet;
	u *= invDet;
	v *= invDet;

#else
	if ( det > -wv::Const::Float::EPSILON && det < wv::Const::Float::EPSILON )
		return {};
	float invDet = 1.0f / det;

	Vector3f tvec = start - _t->v0;
	u = tvec.dot( pvec ) * invDet;
	if ( u < 0.0f || u > 1.0f )
		return {};

	Vector3f qvec = tvec.cross( edge1 );
	v = dir.dot( qvec ) * invDet;
	if ( v < 0.0f || u + v > 1.0f )
		return {};

	t = edge2.dot( qvec ) * invDet;
#endif

	RayIntersection result;
	result.depth = t;
	result.hit = true;
	result.point = _t->barycentricToCartesian( u, v );
	result.triangle = *_t;

	Vector3f n = _t->getNormal();
	Vector3f pto = end - result.point;
	result.planeProjectedPoint = end - n * ( pto.x * n.x + pto.y * n.y + pto.z * n.z );
	result.planeProjectedDepth = pto.x * n.x +
		pto.y * n.y +
		pto.z * n.z;

	return result;
}

	/*
template<>
inline RayIntersection Ray::intersect<sMesh>( sMesh* _t )
{
	cVector4f s{ start.x, start.y, start.z, 1.0f };
	cVector4f e{   end.x,   end.y,   end.z, 1.0f };
	s = Matrix::inverse( _t->transform.getMatrix() ) * s;
	e = Matrix::inverse( _t->transform.getMatrix() ) * e;

	wv::Ray ray{
		wv::cVector3f{ s.x, s.y, s.z },
		wv::cVector3f{ e.x, e.y, e.z }
	};

	float rayLen = ray.length();
	RayIntersection finalResult;

	for ( int i = 0; i < _t->triangles.size(); i++ )
	{
		wv::RayIntersection result = ray.intersect( &_t->triangles[ i ] );// intersects2( ray, _t->triangles[ i ] );
		if ( result.hit )
		{
			if ( result.depth < 0.0 || result.depth > rayLen )
				continue;

			if ( !finalResult.hit || result.depth < finalResult.depth )
				finalResult = result;
		}
	}

	return finalResult;
	return {};
}
	*/

}
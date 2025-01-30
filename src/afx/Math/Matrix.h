#pragma once

#include <afx/Math/Vector3.h>
#include <afx/Math/Vector4.h>

#include <stdint.h>
#include <type_traits>
#include <array>

///////////////////////////////////////////////////////////////////////////////////////

namespace arc {

///////////////////////////////////////////////////////////////////////////////////////

template<typename _Ty, size_t _Rows, size_t _Cols>
class Matrix
{
public:

	typedef std::enable_if<_Rows == 4 && _Cols == 4> if_4x4;
	typedef std::enable_if<_Rows == 3 && _Cols == 3> if_3x3;
	typedef std::enable_if<_Rows == _Cols> if_square;

///////////////////////////////////////////////////////////////////////////////////////

	_Ty m[ _Rows ][ _Cols ];

///////////////////////////////////////////////////////////////////////////////////////

	Matrix( void ) : m{ 0 } { }
	Matrix( const _Ty& _val ) :
		m{ 0 }
	{
		static_assert( _Rows == _Cols, "Cannot create identity matrix from non-square matrix. See output" );
		for ( size_t i = 0; i < _Rows; i++ )
			m[ i ][ i ] = _val;
	}

///////////////////////////////////////////////////////////////////////////////////////

	_Ty* operator []( const size_t& _index ) const { return (_Ty*)m[ _index ]; }
	Matrix<_Ty, _Rows, _Cols>& operator = ( const Matrix<_Ty, _Rows, _Cols>& _o );
	template<size_t _Cols2> Matrix<_Ty, _Rows, _Cols2> operator * ( const Matrix<_Ty, _Cols, _Cols2>& _o ) const;
	template<size_t _Cols2> Matrix<_Ty, _Rows, _Cols>& operator *=( const Matrix<_Ty, _Rows, _Cols2>& _o );

///////////////////////////////////////////////////////////////////////////////////////

	static Matrix<_Ty, _Rows, _Rows> identity( const _Ty& _val )
	{
		return Matrix<_Ty, _Rows, _Rows>( _val );
	}

///////////////////////////////////////////////////////////////////////////////////////

	void setRow( const size_t& _r, std::array<_Ty, _Cols> _v );

#ifndef AFX_PLATFORM_PSVITA
	template<typename = if_4x4::type>
#endif
	Vector4<_Ty>& right( void ) { return *reinterpret_cast<Vector4<_Ty>*>( m[ 0 ] ); }

#ifndef AFX_PLATFORM_PSVITA
	template<typename = if_4x4::type>
#endif
	Vector4<_Ty>& up( void ) { return *reinterpret_cast<Vector4<_Ty>*>( m[ 1 ] ); }

#ifndef AFX_PLATFORM_PSVITA
	template<typename = if_4x4::type>
#endif
	Vector4<_Ty>& at( void ) { return *reinterpret_cast<Vector4<_Ty>*>( m[ 2 ] ); }

#ifndef AFX_PLATFORM_PSVITA
	template<typename = if_4x4::type>
#endif
	Vector4<_Ty>& pos( void ) { return *reinterpret_cast<Vector4<_Ty>*>( m[ 3 ] ); }

};

///////////////////////////////////////////////////////////////////////////////////////

template<typename _Ty>
Vector4<_Ty> operator * ( const Matrix<_Ty, 4, 4>& _mat, const Vector4<_Ty>& _vec )
{
	Matrix<_Ty, 4, 1> tmpMat{};
	tmpMat[ 0 ][ 0 ] = _vec.x;
	tmpMat[ 1 ][ 0 ] = _vec.y;
	tmpMat[ 2 ][ 0 ] = _vec.z;
	tmpMat[ 3 ][ 0 ] = _vec.w;

	auto res = _mat * tmpMat;

	return { res[ 1 ][ 0 ], res[ 1 ][ 0 ], res[ 2 ][ 0 ], res[ 3 ][ 0 ] };
}

template<typename _Ty>
Vector4<_Ty> operator * ( const Vector4<_Ty>& _vec, const Matrix<_Ty, 4, 4>& _mat )
{
	Matrix<_Ty, 1, 4> tmpMat{};
	tmpMat.setRow( 0, { _vec.x, _vec.y, _vec.z, _vec.z } );

	auto res = tmpMat * _mat;

	return { res[ 0 ][ 0 ], res[ 0 ][ 1 ], res[ 0 ][ 2 ], res[ 0 ][ 3 ] };
}

///////////////////////////////////////////////////////////////////////////////////////

namespace MatrixUtil
{

///////////////////////////////////////////////////////////////////////////////////////

template<typename _Ty, size_t _RowA, size_t ColA_RowB, size_t _ColB>
Matrix<_Ty, _RowA, _ColB> multiply( const Matrix<_Ty, _RowA, ColA_RowB>& _a, const Matrix<_Ty, ColA_RowB, _ColB>& _b )
{
	Matrix<_Ty, _RowA, _ColB> res;
	for ( size_t row = 0; row < _RowA; row++ )
	{
		for ( size_t column = 0; column < _ColB; column++ )
		{
			_Ty v = 0;

			for ( int inner = 0; inner < ColA_RowB; inner++ )
				v += _a.m[ row ][ inner ] * _b.m[ inner ][ column ];

			res[ row ][ column ] = v;
		}
	}
	return res;
}

template<typename _Ty>
static inline Matrix<_Ty, 4, 4> inverse( const Matrix<_Ty, 4, 4>& _m )
{
	double A2323 = _m[ 2 ][ 2 ] * _m[ 3 ][ 3 ] - _m[ 2 ][ 3 ] * _m[ 3 ][ 2 ];
	double A1323 = _m[ 2 ][ 1 ] * _m[ 3 ][ 3 ] - _m[ 2 ][ 3 ] * _m[ 3 ][ 1 ];
	double A1223 = _m[ 2 ][ 1 ] * _m[ 3 ][ 2 ] - _m[ 2 ][ 2 ] * _m[ 3 ][ 1 ];
	double A0323 = _m[ 2 ][ 0 ] * _m[ 3 ][ 3 ] - _m[ 2 ][ 3 ] * _m[ 3 ][ 0 ];
	double A0223 = _m[ 2 ][ 0 ] * _m[ 3 ][ 2 ] - _m[ 2 ][ 2 ] * _m[ 3 ][ 0 ];
	double A0123 = _m[ 2 ][ 0 ] * _m[ 3 ][ 1 ] - _m[ 2 ][ 1 ] * _m[ 3 ][ 0 ];
	double A2313 = _m[ 1 ][ 2 ] * _m[ 3 ][ 3 ] - _m[ 1 ][ 3 ] * _m[ 3 ][ 2 ];
	double A1313 = _m[ 1 ][ 1 ] * _m[ 3 ][ 3 ] - _m[ 1 ][ 3 ] * _m[ 3 ][ 1 ];
	double A1213 = _m[ 1 ][ 1 ] * _m[ 3 ][ 2 ] - _m[ 1 ][ 2 ] * _m[ 3 ][ 1 ];
	double A2312 = _m[ 1 ][ 2 ] * _m[ 2 ][ 3 ] - _m[ 1 ][ 3 ] * _m[ 2 ][ 2 ];
	double A1312 = _m[ 1 ][ 1 ] * _m[ 2 ][ 3 ] - _m[ 1 ][ 3 ] * _m[ 2 ][ 1 ];
	double A1212 = _m[ 1 ][ 1 ] * _m[ 2 ][ 2 ] - _m[ 1 ][ 2 ] * _m[ 2 ][ 1 ];
	double A0313 = _m[ 1 ][ 0 ] * _m[ 3 ][ 3 ] - _m[ 1 ][ 3 ] * _m[ 3 ][ 0 ];
	double A0213 = _m[ 1 ][ 0 ] * _m[ 3 ][ 2 ] - _m[ 1 ][ 2 ] * _m[ 3 ][ 0 ];
	double A0312 = _m[ 1 ][ 0 ] * _m[ 2 ][ 3 ] - _m[ 1 ][ 3 ] * _m[ 2 ][ 0 ];
	double A0212 = _m[ 1 ][ 0 ] * _m[ 2 ][ 2 ] - _m[ 1 ][ 2 ] * _m[ 2 ][ 0 ];
	double A0113 = _m[ 1 ][ 0 ] * _m[ 3 ][ 1 ] - _m[ 1 ][ 1 ] * _m[ 3 ][ 0 ];
	double A0112 = _m[ 1 ][ 0 ] * _m[ 2 ][ 1 ] - _m[ 1 ][ 1 ] * _m[ 2 ][ 0 ];

	_Ty det = _m[ 0 ][ 0 ] * ( _m[ 1 ][ 1 ] * A2323 - _m[ 1 ][ 2 ] * A1323 + _m[ 1 ][ 3 ] * A1223 )
		- _m[ 0 ][ 1 ] * ( _m[ 1 ][ 0 ] * A2323 - _m[ 1 ][ 2 ] * A0323 + _m[ 1 ][ 3 ] * A0223 )
		+ _m[ 0 ][ 2 ] * ( _m[ 1 ][ 0 ] * A1323 - _m[ 1 ][ 1 ] * A0323 + _m[ 1 ][ 3 ] * A0123 )
		- _m[ 0 ][ 3 ] * ( _m[ 1 ][ 0 ] * A1223 - _m[ 1 ][ 1 ] * A0223 + _m[ 1 ][ 2 ] * A0123 );

	if ( det == 0.0 ) // determinant is zero, inverse matrix does not exist
		return Matrix<_Ty, 4, 4>{};

	det = 1 / det;

	Matrix<_Ty, 4, 4> im;

	im[ 0 ][ 0 ] = det * ( _m[ 1 ][ 1 ] * A2323 - _m[ 1 ][ 2 ] * A1323 + _m[ 1 ][ 3 ] * A1223 );
	im[ 0 ][ 1 ] = det * -( _m[ 0 ][ 1 ] * A2323 - _m[ 0 ][ 2 ] * A1323 + _m[ 0 ][ 3 ] * A1223 );
	im[ 0 ][ 2 ] = det * ( _m[ 0 ][ 1 ] * A2313 - _m[ 0 ][ 2 ] * A1313 + _m[ 0 ][ 3 ] * A1213 );
	im[ 0 ][ 3 ] = det * -( _m[ 0 ][ 1 ] * A2312 - _m[ 0 ][ 2 ] * A1312 + _m[ 0 ][ 3 ] * A1212 );
	im[ 1 ][ 0 ] = det * -( _m[ 1 ][ 0 ] * A2323 - _m[ 1 ][ 2 ] * A0323 + _m[ 1 ][ 3 ] * A0223 );
	im[ 1 ][ 1 ] = det * ( _m[ 0 ][ 0 ] * A2323 - _m[ 0 ][ 2 ] * A0323 + _m[ 0 ][ 3 ] * A0223 );
	im[ 1 ][ 2 ] = det * -( _m[ 0 ][ 0 ] * A2313 - _m[ 0 ][ 2 ] * A0313 + _m[ 0 ][ 3 ] * A0213 );
	im[ 1 ][ 3 ] = det * ( _m[ 0 ][ 0 ] * A2312 - _m[ 0 ][ 2 ] * A0312 + _m[ 0 ][ 3 ] * A0212 );
	im[ 2 ][ 0 ] = det * ( _m[ 1 ][ 0 ] * A1323 - _m[ 1 ][ 1 ] * A0323 + _m[ 1 ][ 3 ] * A0123 );
	im[ 2 ][ 1 ] = det * -( _m[ 0 ][ 0 ] * A1323 - _m[ 0 ][ 1 ] * A0323 + _m[ 0 ][ 3 ] * A0123 );
	im[ 2 ][ 2 ] = det * ( _m[ 0 ][ 0 ] * A1313 - _m[ 0 ][ 1 ] * A0313 + _m[ 0 ][ 3 ] * A0113 );
	im[ 2 ][ 3 ] = det * -( _m[ 0 ][ 0 ] * A1312 - _m[ 0 ][ 1 ] * A0312 + _m[ 0 ][ 3 ] * A0112 );
	im[ 3 ][ 0 ] = det * -( _m[ 1 ][ 0 ] * A1223 - _m[ 1 ][ 1 ] * A0223 + _m[ 1 ][ 2 ] * A0123 );
	im[ 3 ][ 1 ] = det * ( _m[ 0 ][ 0 ] * A1223 - _m[ 0 ][ 1 ] * A0223 + _m[ 0 ][ 2 ] * A0123 );
	im[ 3 ][ 2 ] = det * -( _m[ 0 ][ 0 ] * A1213 - _m[ 0 ][ 1 ] * A0213 + _m[ 0 ][ 2 ] * A0113 );
	im[ 3 ][ 3 ] = det * ( _m[ 0 ][ 0 ] * A1212 - _m[ 0 ][ 1 ] * A0212 + _m[ 0 ][ 2 ] * A0112 );

	return im;
}

template<typename _Ty, size_t _Rows, size_t _Cols>
Matrix<_Ty, _Cols, _Rows> transpose( const Matrix<_Ty, _Rows, _Cols>& _m )
{
	Matrix<_Ty, _Cols, _Rows> res;

	/// naive approach
	/// TODO: optimize
	for ( size_t row = 0; row < _Rows; row++ )
		for ( size_t col = 0; col < _Cols; col++ )
			res[ col ][ row ] = _m[ row ][ col ];

	return res;
}

template<typename _Ty>
Matrix<_Ty, 4, 4> translate( const Matrix<_Ty, 4, 4>& _m, const arc::Vector3<_Ty>& _pos )
{
	Matrix<_Ty, 4, 4> mat( _Ty( 1 ) );

	mat.pos() = { _pos.x, _pos.y, _pos.z, _Ty( 1 ) };

	return mat * _m;
}

template<typename _Ty>
Matrix<_Ty, 4, 4> scale( const Matrix<_Ty, 4, 4>& _m, const arc::Vector3<_Ty>& _scale )
{
	Matrix<_Ty, 4, 4> mat( 1.0 );

	mat.setRow( 0, { _scale.x,      0.0,      0.0 } );
	mat.setRow( 1, { 0.0, _scale.y,      0.0 } );
	mat.setRow( 2, { 0.0,      0.0, _scale.z } );

	return mat * _m;
}

template<typename _Ty>
Matrix<_Ty, 4, 4> rotateX( const Matrix<_Ty, 4, 4>& _m, _Ty _angle )
{
	Matrix<_Ty, 4, 4> mat( 1.0 );

	mat.setRow( 0, { 1.0,                0.0,                 0.0 } );
	mat.setRow( 1, { 0.0,  std::cos( _angle ), std::sin( _angle ) } );
	mat.setRow( 2, { 0.0, -std::sin( _angle ), std::cos( _angle ) } );

	return mat * _m;
}

template<typename _Ty>
Matrix<_Ty, 4, 4> rotateY( const Matrix<_Ty, 4, 4>& _m, _Ty _angle )
{
	Matrix<_Ty, 4, 4> mat( 1.0 );

	mat.setRow( 0, { std::cos( _angle ), 0.0, -std::sin( _angle ) } );
	mat.setRow( 1, { 0.0, 1.0,                 0.0 } );
	mat.setRow( 2, { std::sin( _angle ), 0.0,  std::cos( _angle ) } );

	return mat * _m;
}

template<typename _Ty>
Matrix<_Ty, 4, 4> rotateZ( const Matrix<_Ty, 4, 4>& _m, _Ty _angle )
{
	Matrix<_Ty, 4, 4> mat( 1.0 );

	mat.setRow( 0, { std::cos( _angle ), std::sin( _angle ), 0.0 } );
	mat.setRow( 1, { -std::sin( _angle ), std::cos( _angle ), 0.0 } );
	mat.setRow( 2, { 0.0,                0.0, 1.0 } );

	return mat * _m;
}

// https://jsantell.com/3d-projection/#field-of-view
template<typename _Ty>
Matrix<_Ty, 4, 4> perspective( const _Ty& _aspect, const _Ty& _fov, const _Ty& _near, const _Ty& _far )
{
	Matrix<_Ty, 4, 4> res{ 0 };

	const _Ty e = 1.0 / std::tan( _fov / 2.0 );
	const _Ty m00 = e / _aspect;
	const _Ty m22 = ( _far + _near ) / ( _near - _far );
	const _Ty m32 = ( 2 * _far * _near ) / ( _near - _far );

	res.setRow( 0, { m00, 0,   0,  0 } );
	res.setRow( 1, { 0, e,   0,  0 } );
	res.setRow( 2, { 0, 0, m22, -1 } );
	res.setRow( 3, { 0, 0, m32,  0 } );

	return res;
}

template<typename _Ty>
Matrix<_Ty, 4, 4> orthographic( const _Ty& _halfWidth, const _Ty& _halfHeight, const _Ty& _far, const _Ty& _near )
{
	Matrix<_Ty, 4, 4> res{ 0 };

	_Ty m00 = 1.0 / _halfWidth;
	_Ty m11 = 1.0 / _halfHeight;
	_Ty m22 = ( -2.0 ) / ( _far - _near );
	_Ty m32 = -( ( _far + _near ) / ( _far - _near ) );

	res.setRow( 0, { m00,   0,   0, 0 } );
	res.setRow( 1, { 0, m11,   0, 0 } );
	res.setRow( 2, { 0,   0, m22, 0 } );
	res.setRow( 3, { 0,   0, m32, 1 } );

	return res;
}

/// TODO: focal length camera https://paulbourke.net/miscellaneous/lens/

template<typename _Ty>
Matrix<_Ty, 1, 4> fromVector( const Vector4<_Ty>& _vec )
{
	Matrix<_Ty, 1, 4> m;
	m.setRow( 0, { _vec.x, _vec.y, _vec.z, _vec.w } );
	return m;
}

template<typename _Ty>
Matrix<_Ty, 1, 3> fromVector( Vector3<_Ty> _vec )
{
	Matrix<_Ty, 1, 3> m;
	m.setRow( 0, { _vec.x, _vec.y, _vec.z } );
	return m;
}

}

///////////////////////////////////////////////////////////////////////////////////////

typedef Matrix<float, 4, 4> Matrix4x4f;
typedef Matrix<float, 3, 3> Matrix3x3f;

///////////////////////////////////////////////////////////////////////////////////////

template<typename _Ty, size_t _Rows, size_t _Cols>
inline Matrix<_Ty, _Rows, _Cols>& Matrix<_Ty, _Rows, _Cols>::operator=( const Matrix<_Ty, _Rows, _Cols>& _o )
{
	std::memcpy( &m, &_o.m, sizeof( m ) );
	return ( *this );
}

template<typename _Ty, size_t _Rows, size_t _Cols>
template<size_t _Cols2>
inline Matrix<_Ty, _Rows, _Cols2> Matrix<_Ty, _Rows, _Cols>::operator*( const Matrix<_Ty, _Cols, _Cols2>& _o ) const
{
	return MatrixUtil::multiply( *this, _o );
}

template<typename _Ty, size_t _Rows, size_t _Cols>
template<size_t _Cols2>
inline Matrix<_Ty, _Rows, _Cols>& Matrix<_Ty, _Rows, _Cols>::operator*=( const Matrix<_Ty, _Rows, _Cols2>& _o )
{
	( *this ) = ( *this ) * _o;
	return ( *this );
}

///////////////////////////////////////////////////////////////////////////////////////

template<typename _Ty, size_t _Rows, size_t _Cols>
inline void Matrix<_Ty, _Rows, _Cols>::setRow( const size_t& _r, std::array<_Ty, _Cols> _v )
{
	size_t id = 0;
	for ( auto& v : _v )
	{
		m[ _r ][ id ] = v;
		id++;
	}
}

}
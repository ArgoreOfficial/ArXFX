#pragma once

#include <afx/Math/Vector3.h>

///////////////////////////////////////////////////////////////////////////////////////

namespace arc {

///////////////////////////////////////////////////////////////////////////////////////

template<typename _Ty>
class Quaternion
{

public:

	Vector3<_Ty> v;
	_Ty s;

///////////////////////////////////////////////////////////////////////////////////////

	Quaternion( void ) : v( {} ), s( 1.0 ) { }
	Quaternion( const Vector3<_Ty>& _v, const _Ty& _s ) : v( _v ), s( _s ) { }
	Quaternion( const _Ty& _x, const _Ty& _y, const _Ty& _z, const _Ty& _s ) : v( _x, _y, _z ), s( _s ) { }

	static Vector3<_Ty> rotateVector( const Vector3<_Ty>& _v, const Vector3<_Ty>& _axis, const _Ty& _angle );

	static Quaternion<_Ty> fromAxisAngle( const Vector3<_Ty>& _axis, const _Ty& _angle );

	void normalize( void );
	void toUnitNorm( void );

	void rotate( const Vector3<_Ty>& _axis, const _Ty& _angle );

	_Ty norm( void );

	Quaternion<_Ty> normalized( void );
	Quaternion<_Ty> conjugate( void );
	Quaternion<_Ty> inverse( void );


	Quaternion<_Ty>& operator = ( const Quaternion<_Ty>& _other );
	Quaternion<_Ty>  operator + ( const Quaternion<_Ty>& _other ) const;
	Quaternion<_Ty>  operator - ( const Quaternion<_Ty>& _other ) const;
	Quaternion<_Ty>& operator +=( const Quaternion<_Ty>& _other );
	Quaternion<_Ty>& operator -=( const Quaternion<_Ty>& _other );
	Quaternion<_Ty>  operator * ( const Quaternion<_Ty>& _other ) const;
	Quaternion<_Ty>& operator *=( const Quaternion<_Ty>& _other );
	Quaternion<_Ty>  operator * ( const _Ty& _scalar ) const;
	Quaternion<_Ty>& operator *=( const _Ty& _scalar );
};

///////////////////////////////////////////////////////////////////////////////////////

typedef Quaternion<float>  cQuaternionf;
typedef Quaternion<double> cQuaterniond;
typedef Quaternion<int>    cQuaternioni;

///////////////////////////////////////////////////////////////////////////////////////

template<typename _Ty>
inline Vector3<_Ty> Quaternion<_Ty>::rotateVector( const Vector3<_Ty>& _v, const Vector3<_Ty>& _axis, const _Ty& _angle )
{
	Quaternion<_Ty> pure{ _v, 0 };
	Vector3<_Ty> axis = _axis;

	axis.normalize();

	Quaternion<_Ty> q{ axis, _angle };
	q.toUnitNorm();

	Quaternion<_Ty> qInv = q.inverse();
	Quaternion<_Ty> rotated = q * pure * qInv;

	return rotated.v;
}

template<typename _Ty>
inline Quaternion<_Ty> Quaternion<_Ty>::fromAxisAngle( const Vector3<_Ty>& _axis, const _Ty& _angle )
{
	_Ty factor = std::sin( _angle / 2.0 );

	_Ty x = _axis.x * factor;
	_Ty y = _axis.y * factor;
	_Ty z = _axis.z * factor;

	_Ty w = std::cos( _angle / 2.0 );

	return Quaternion<_Ty>( x, y, z, w ).normalized();
}

template<typename _Ty>
inline void Quaternion<_Ty>::normalize()
{
	_Ty n = norm();

	if ( n == _Ty{ 0 } )
		return;

	_Ty normValue = _Ty{ 1 } / n;
	s *= normValue;
	v *= normValue;
}

template<typename _Ty>
inline void Quaternion<_Ty>::toUnitNorm()
{
	_Ty angle = Math::radians( s );
	v.normalize();
	s = std::cos( angle / _Ty{ 2 } );
	v = v * std::sin( angle / _Ty{ 2 } );
}

template<typename _Ty>
inline void Quaternion<_Ty>::rotate( const Vector3<_Ty>& _axis, const _Ty& _angle )
{
	Quaternion<_Ty> _other = Quaternion<_Ty>::fromAxisAngle( _axis, _angle );
	( *this ) *= _other;
}

template<typename _Ty>
inline _Ty Quaternion<_Ty>::norm()
{
	_Ty imaginary = v.dot( v );
	_Ty scale = s * s;

	return sqrt( imaginary + scale );
}

template<typename _Ty>
inline Quaternion<_Ty> Quaternion<_Ty>::normalized()
{
	Quaternion<_Ty> quat = ( *this );
	quat.normalize();
	return quat;
}

template<typename _Ty>
inline Quaternion<_Ty> Quaternion<_Ty>::conjugate()
{
	return Quaternion<_Ty>( -v, s );
}

template<typename _Ty>
inline Quaternion<_Ty> Quaternion<_Ty>::inverse()
{
	_Ty absoluteValue = norm();
	absoluteValue *= absoluteValue;
	absoluteValue = _Ty{ 1 } / absoluteValue;

	Quaternion<_Ty> conjugateValue = conjugate();
	_Ty scale = conjugateValue.s * absoluteValue;

	Vector3<_Ty> imaginary = conjugateValue.v * absoluteValue;
	return Quaternion<_Ty>( imaginary, scale );
}

///////////////////////////////////////////////////////////////////////////////////////

template<typename _Ty>
inline Quaternion<_Ty>& Quaternion<_Ty>::operator=( const Quaternion<_Ty>& _other )
{
	v = _other.v;
	s = _other.s;

	return ( *this );
}

template<typename _Ty>
inline Quaternion<_Ty> Quaternion<_Ty>::operator+( const Quaternion<_Ty>& _other ) const
{
	Vector3<_Ty> imaginary = v + _other.v;
	_Ty scale = s + _other.s;

	return Quaternion<_Ty>{ imaginary, scale };
}

template<typename _Ty>
inline Quaternion<_Ty> Quaternion<_Ty>::operator-( const Quaternion<_Ty>& _other ) const
{
	Vector3<_Ty> imaginary = v - _other.v;
	_Ty scale = s - _other.s;

	return Quaternion<_Ty>{ imaginary, scale };
}

template<typename _Ty>
inline Quaternion<_Ty>& Quaternion<_Ty>::operator+=( const Quaternion<_Ty>& _other )
{
	v += _other.v;
	s += _other.s;

	return ( *this );
}

template<typename _Ty>
inline Quaternion<_Ty>& Quaternion<_Ty>::operator-=( const Quaternion<_Ty>& _other )
{
	v -= _other.v;
	s -= _other.s;

	return ( *this );
}

template<typename _Ty>
inline Quaternion<_Ty> Quaternion<_Ty>::operator*( const Quaternion<_Ty>& _other ) const
{
	Vector3<_Ty> imaginary = ( _other.v * s ) + ( v * _other.s ) + v.cross( _other.v );
	_Ty scale = ( s * _other.s ) - v.dot( _other.v );

	return Quaternion<_Ty>{ imaginary, scale };
}

template<typename _Ty>
inline Quaternion<_Ty>& Quaternion<_Ty>::operator*=( const Quaternion<_Ty>& _other )
{
	( *this ) = ( *this ) * _other;

	return ( *this );
}

template<typename _Ty>
inline Quaternion<_Ty> Quaternion<_Ty>::operator*( const _Ty& _scalar ) const
{
	Vector3<_Ty> imaginary = v * _scalar;
	_Ty scale = s * _scalar;

	return Quaternion<_Ty>( imaginary, scale );
}

template<typename _Ty>
inline Quaternion<_Ty>& Quaternion<_Ty>::operator*=( const _Ty& _scalar )
{
	v *= _scalar;
	s *= _scalar;

	return ( *this );
}

///////////////////////////////////////////////////////////////////////////////////////

}
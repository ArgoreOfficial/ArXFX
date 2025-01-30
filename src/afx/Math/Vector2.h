#pragma once

namespace afx {

///////////////////////////////////////////////////////////////////////////////////////

template< typename _Ty >
class Vector2
{

public:

	_Ty x, y;

///////////////////////////////////////////////////////////////////////////////////////

	Vector2( void ) : x( 0 ), y( 0 ) { }
	Vector2( const _Ty& _t ) : x( _t ), y( _t ) { }
	Vector2( const _Ty& _x, const _Ty& _y ) : x( _x ), y( _y ) { }

	Vector2<_Ty>& operator = ( const Vector2<_Ty>& _other );
	Vector2<_Ty>& operator +=( const Vector2<_Ty>& _other );
	Vector2<_Ty>& operator -=( const Vector2<_Ty>& _other );
	Vector2<_Ty>  operator + ( const Vector2<_Ty>& _other );
	Vector2<_Ty>  operator - ( const Vector2<_Ty>& _other );
	Vector2<_Ty>  operator * ( const float& _scalar );
	Vector2<_Ty>& operator *=( const float& _scalar );
	Vector2<_Ty>  operator / ( const float& _scalar );
	Vector2<_Ty>& operator /=( const float& _scalar );
};

///////////////////////////////////////////////////////////////////////////////////////

typedef Vector2<float> Vector2f;
typedef Vector2<int>   Vector2i;

///////////////////////////////////////////////////////////////////////////////////////

template<typename _Ty>
inline Vector2<_Ty>& Vector2<_Ty>::operator=( const Vector2<_Ty>& _other )
{
	x = _other.x;
	y = _other.y;
	return *this;
}

template< typename _Ty >
inline Vector2<_Ty>& Vector2<_Ty>::operator+=( const Vector2<_Ty>& _other )
{
	x += _other.x;
	y += _other.y;
	return *this;
}

template< typename _Ty >
inline Vector2<_Ty>& Vector2<_Ty>::operator-=( const Vector2<_Ty>& _other )
{
	x -= _other.x;
	y -= _other.y;
	return *this;
}

template< typename _Ty >
inline Vector2<_Ty> Vector2<_Ty>::operator+( const Vector2<_Ty>& _other )
{
	return Vector2<_Ty>( x + _other.x, y + _other.y );
}

template< typename _Ty >
inline Vector2<_Ty> Vector2<_Ty>::operator-( const Vector2<_Ty>& _other )
{
	return Vector2<_Ty>( x - _other.x, y - _other.y );
}

template< typename _Ty >
inline Vector2<_Ty> afx::Vector2<_Ty>::operator*( const float& _scalar )
{
	return Vector2<_Ty>( x * _scalar, y * _scalar );
}

template< typename _Ty >
inline Vector2<_Ty>& Vector2<_Ty>::operator*=( const float& _scalar )
{
	x *= _scalar;
	y *= _scalar;
	return *this;
}

template< typename _Ty >
inline Vector2<_Ty> afx::Vector2<_Ty>::operator/( const float& _scalar )
{
	return Vector2<_Ty>( x / _scalar, y / _scalar );
}

template< typename _Ty >
inline Vector2<_Ty>& Vector2<_Ty>::operator/=( const float& _scalar )
{
	x /= _scalar;
	y /= _scalar;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////

}
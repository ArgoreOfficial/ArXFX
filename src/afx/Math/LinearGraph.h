#pragma once

#include <vector>

///////////////////////////////////////////////////////////////////////////////////////

namespace arc
{

///////////////////////////////////////////////////////////////////////////////////////

template<typename _Ty>
struct GraphPoint
{
	_Ty x, y;
};

///////////////////////////////////////////////////////////////////////////////////////

template<typename _Ty>
struct LinearEquation
{
	_Ty min, max;
	_Ty m, b;

	LinearEquation() : m{ 0 }, b{ 0 }, min{ 0 }, max{ 0 } { }
	LinearEquation( const GraphPoint<_Ty>& _a, const GraphPoint<_Ty>& _b ) :
		m{ ( _b.y - _a.y ) / ( _b.x - _a.x ) },
		b{ _a.y },
		min{ _a.x },
		max{ _b.x }
	{
	}

 // remember, y = mx + b
	_Ty valueAt( const _Ty& _x ) { return m * ( _x - min ) + b; }
};

///////////////////////////////////////////////////////////////////////////////////////

template<typename _Ty>
class LinearGraph
{
public:

	LinearGraph( const std::vector<GraphPoint<_Ty>>& _points );

	_Ty getValue( const _Ty& _x );
	LinearEquation<_Ty> getLinearEquation( const _Ty& _x );

private:

	std::vector<LinearEquation<_Ty>> m_linearEquations;

};

///////////////////////////////////////////////////////////////////////////////////////

template<typename _Ty>
inline arc::LinearGraph<_Ty>::LinearGraph( const std::vector<GraphPoint<_Ty>>& _points )
{
	m_linearEquations.resize( _points.size() );

	for ( size_t i = 0; i < _points.size(); i++ )
	{
		if ( i >= _points.size() - 1 )
			continue;

		m_linearEquations[ i ] = LinearEquation<_Ty>( _points[ i ], _points[ i + 1 ] );
	}
}

template<typename _Ty>
inline _Ty arc::LinearGraph<_Ty>::getValue( const _Ty& _x )
{
	for ( size_t i = 0; i < m_linearEquations.size(); i++ )
	{
		LinearEquation<_Ty>& line = m_linearEquations[ i ];

		if ( _x < line.min || _x >= line.max )
			continue;

		return line.valueAt( _x );
	}

	return _Ty{ 0 };
}

template<typename _Ty>
inline LinearEquation<_Ty> LinearGraph<_Ty>::getLinearEquation( const _Ty& _x )
{
	for ( size_t i = 0; i < m_linearEquations.size(); i++ )
	{
		LinearEquation<_Ty>& line = m_linearEquations[ i ];

		if ( _x < line.min || _x >= line.max )
			continue;

		return line;
	}

	return LinearEquation<_Ty>{};
}

}


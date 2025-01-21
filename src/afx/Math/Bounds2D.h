#pragma once

namespace afx {

template<typename _Ty>
struct Bounds2D
{
	_Ty x;
	_Ty y;
	_Ty width;
	_Ty height;
};

typedef Bounds2D<float> Bounds2Df;
typedef Bounds2D<int>   Bounds2Di;

}

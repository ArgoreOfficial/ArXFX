#pragma once

namespace arc {

template<typename _Ty>
struct Bounds2D
{
	_Ty x;
	_Ty y;
	_Ty width;
	_Ty height;
};

typedef Bounds2D<float> Bounds2Df;
typedef Bounds2D<int32_t>   Bounds2Di;
typedef Bounds2D<uint32_t>   Bounds2Du32;

}

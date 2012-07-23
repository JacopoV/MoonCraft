#pragma once

#include "Vector2.h"
#include "Vector3.h"

namespace phynet{
namespace math{

template<int Dim> struct Vector{};
template<> struct Vector<1>{typedef Real Type;};
template<> struct Vector<2>{typedef Vector2 Type;};
template<> struct Vector<3>{typedef Vector3 Type;};

}} // namespaces


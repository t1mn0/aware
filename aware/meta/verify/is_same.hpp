#pragma once

#include "../constants/bool.hpp"

namespace awr::meta {

template <typename T, typename U>
struct IsSame : BoolConstant<false> {};

template <typename T>
struct IsSame<T, T> : BoolConstant<true> {};

}  // namespace awr::meta

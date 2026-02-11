#pragma once

#include "../decorate/remove_cv.hpp"
#include "is_same.hpp"

namespace awr::meta {

template <class T>
struct IsVoid : IsSame<void, typename RemoveCV<T>::type> {};

}  // namespace awr::meta

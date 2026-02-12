/**
 * @file is_void.hpp
 * @brief Trait-structure to check if a type is void.
 */

#pragma once

#include "../decorating/remove_cv.hpp"
#include "is_same.hpp"

namespace awr::meta {

/**
 * @brief Checks if type T is void, const void, volatile void, or const volatile void.
 */
template <class T>
struct IsVoid : IsSame<void, typename RemoveCV<T>::type> {};

}  // namespace awr::meta

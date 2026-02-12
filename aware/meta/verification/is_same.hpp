/**
 * @file is_same.hpp
 * @brief Trait-structure to check if two types are identical.
 */

#pragma once

#include "../constants/bool.hpp"

namespace awr::meta {

/**
 * @brief Checks if type T and type U are the same.
 * @details Inherits from BoolConstant<true> if types match, otherwise BoolConstant<false>.
 */

template <typename T, typename U>
struct IsSame : BoolConstant<false> {};

template <typename T>
struct IsSame<T, T> : BoolConstant<true> {};

}  // namespace awr::meta

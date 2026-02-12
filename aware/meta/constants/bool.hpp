/**
 * @file bool.hpp
 * @brief Specialization of IntegralConstant for boolean values.
 */

#pragma once

#include "integral.hpp"

namespace awr::meta {

/**
 * @brief Alias for boolean constants.
 * @tparam bval The boolean value.
 */
template <bool bval>
using BoolConstant = IntegralConstant<bool, bval>;

};  // namespace awr::meta

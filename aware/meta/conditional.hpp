/**
 * @file conditional.hpp
 * @brief Provides a mechanism for compile-time type selection.
 */

#pragma once

namespace awr::meta {

/**
 * @brief Selects one of two types based on a boolean condition.
 * @tparam B The condition.
 * @tparam U Type to select if B is true.
 * @tparam V Type to select if B is false.
 */
template <bool B, typename U, typename V>
struct Conditional {
    using type = V;
};

/**
 * @brief Specialization for the true condition.
 */
template <typename U, typename V>
struct Conditional<true, U, V> {
    using type = U;
};

}  // namespace awr::meta

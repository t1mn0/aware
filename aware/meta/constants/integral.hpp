/**
 * @file integral.hpp
 * @brief Base class for compile-time constants of a specific type.
 */

#pragma once

namespace awr::meta {

/**
 * @brief Wrapper for an integral literals as a compile-time constant.
 * @tparam T The type of the value.
 * @tparam v The value of type T.
 */
template <class T, T v>
struct IntegralConstant {
  public:  // data members:
    static constexpr T val = v;  ///< The stored constant value.

  public:  // nested types:
    using ValType = T;  ///< The type of the stored value.

  public:  // member functions:
    /**
     * @brief Conversion operator to the underlying value type.
     * @return The stored constant value.
     */
    constexpr operator ValType() const noexcept {
        return val;
    }
};

};  // namespace awr::meta

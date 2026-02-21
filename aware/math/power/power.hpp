#pragma once

#include <aware/math/concepts/multiplicative.hpp>

namespace awr::math {

template <typename T>
requires std::copyable<T> && concepts::Multiplicative<T>
T power(T x, T acc, unsigned n) {
    while (n > 0) {
        if ((n & 0x1) == 0x1) {
            acc *= x;
            n -= 1;
        } else {
            x *= x;
            n /= 2;
        }
    }
    return acc;
}

template <typename T>
requires std::is_arithmetic_v<T>
inline T power(T x, unsigned n) {
    if ((x == T{1}) || (x == T{0}) || (n == 1u)) return x;
    return power(x, T{1}, n);
}

}  // namespace awr::math

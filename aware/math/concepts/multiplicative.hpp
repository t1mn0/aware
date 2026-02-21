#pragma once

#include <concepts>

namespace awr::math::concepts {

template <typename T>
concept Multiplicative = requires(T t) {
    { t *= t } -> std::convertible_to<T>;
};

}  // namespace awr::math::concepts

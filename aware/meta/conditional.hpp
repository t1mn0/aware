#pragma once

namespace awr::meta {

template <bool B, typename U, typename V>
struct Conditional {
    using type = V;
};

template <typename U, typename V>
struct Conditional<true, U, V> {
    using type = U;
};

}  // namespace awr::meta

/**
 * @file remove_cv.hpp
 * @brief Utilities for removing the const and volatile qualifiers from a type if it contains.
 */

#pragma once

namespace awr::meta {

/**
 * @brief Removes both const and volatile qualifiers from type T.
 * @tparam T The original type.
 */
template <class T>
struct RemoveCV {
    typedef T type;
};

template <class T>
struct RemoveCV<const T> {
    typedef T type;
};

template <class T>
struct RemoveCV<volatile T> {
    typedef T type;
};

template <class T>
struct RemoveCV<const volatile T> {
    typedef T type;
};

/**
 * @brief Removes only the const qualifier from type T.
 */
template <class T>
struct RemoveConst {
    typedef T type;
};

template <class T>
struct RemoveConst<const T> {
    typedef T type;
};

/**
 * @brief Removes only the volatile qualifier from type T.
 */
template <class T>
struct RemoveVolatile {
    typedef T type;
};

template <class T>
struct RemoveVolatile<volatile T> {
    typedef T type;
};

}  // namespace awr::meta

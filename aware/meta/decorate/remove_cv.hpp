#pragma once

namespace awr::meta {

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

template <class T>
struct RemoveConst {
    typedef T type;
};

template <class T>
struct RemoveConst<const T> {
    typedef T type;
};

template <class T>
struct remove_volatile {
    typedef T type;
};

template <class T>
struct remove_volatile<volatile T> {
    typedef T type;
};

}  // namespace awr::meta

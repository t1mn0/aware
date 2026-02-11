#pragma once

namespace awr::meta {

template <class T, T v>
struct IntegralConstant {
  public:  // data members:
    static constexpr T value = v;

  public:  // nested types:
    using ValType = T;

  public:  // member functions:
    constexpr operator ValType() const noexcept {
        return value;
    }
};

};  // namespace awr::meta

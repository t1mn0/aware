#pragma once

#include "integral.hpp"

namespace awr::meta {

template <bool B>
using BoolConstant = IntegralConstant<bool, B>;

};  // namespace awr::meta

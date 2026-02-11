#pragma once

#include <aware/meta/verify/is_same.hpp>

namespace awr::iter {

namespace tag {

struct InputIterator {};

struct OutputIterator {};

struct ForwardIterator : InputIterator {};

struct BidirectionalIterator : ForwardIterator {};

struct RandomAccessIterator : BidirectionalIterator {};

struct ContiguousIterator : RandomAccessIterator {};

}  // namespace tag

namespace trait {

template <typename MaybeIteratorTag>
concept IterTag =
    meta::IsSame<MaybeIteratorTag, tag::InputIterator>::value ||
    meta::IsSame<MaybeIteratorTag, tag::OutputIterator>::value ||
    meta::IsSame<MaybeIteratorTag, tag::ForwardIterator>::value ||
    meta::IsSame<MaybeIteratorTag, tag::BidirectionalIterator>::value ||
    meta::IsSame<MaybeIteratorTag, tag::RandomAccessIterator>::value ||
    meta::IsSame<MaybeIteratorTag, tag::ContiguousIterator>::value;

}  // namespace trait

}  // namespace awr::iter

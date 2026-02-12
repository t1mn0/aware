/**
 * @file tag.hpp
 * @brief Iterator category tags and verification concept.
 */

#pragma once

#include <aware/meta/verification.hpp>

/**
 * @namespace tag
 * @brief Empty classes used as markers for iterator categories.
 */
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

/**
 * @brief Concept to verify if a type is one of the valid iterator tags.
 */
template <typename MaybeIteratorTag>
concept IterTag = meta::IsSame<MaybeIteratorTag, tag::InputIterator>::val ||
                  meta::IsSame<MaybeIteratorTag, tag::OutputIterator>::val ||
                  meta::IsSame<MaybeIteratorTag, tag::ForwardIterator>::val ||
                  meta::IsSame<MaybeIteratorTag, tag::BidirectionalIterator>::val ||
                  meta::IsSame<MaybeIteratorTag, tag::RandomAccessIterator>::val ||
                  meta::IsSame<MaybeIteratorTag, tag::ContiguousIterator>::val;

}  // namespace trait

}  // namespace awr::iter

#pragma once

// std
#include "std.h"

// Streamable
#include "Streamable/Streamable.hpp"

// JSPN
#include "JSON/json.hpp"

// let's shadow the std::move with our own
#define move(...) move_ex<decltype(__VA_ARGS__)>(__VA_ARGS__)

namespace std
{
template <typename DeclType, typename Type>
constexpr std::remove_reference_t<Type> && move_ex(Type && aObject)
{
  // prevent const
  static_assert(!std::is_const_v<std::remove_reference_t<Type>>);

  // prevent non-owning
  static_assert(!std::is_lvalue_reference_v<DeclType>);

  return static_cast<std::remove_reference_t<Type> &&>(aObject);
}
}  // namespace std

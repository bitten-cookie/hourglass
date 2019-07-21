#pragma once

#include <memory>
#include <type_traits>

template<typename T>
struct is_unique_pointer : std::false_type {};

template<class T>
struct is_unique_pointer<std::unique_ptr<T>> : std::true_type {};

template< class T >
inline constexpr bool is_unique_pointer_v = is_unique_pointer<T>::value;
// #ifndef VOLT_MATHHELPER_HPP
// #define VOLT_MATHHELPER_HPP

// #include <cstdint>
// #include <Core/Specification.hpp>

// using namespace VoltLang;

// template<Type>
// struct type_to_type;

// template<> struct type_to_type<Type::DoublePointer> { using type = double; };
// template<> struct type_to_type<Type::UInt64Pointer> { using type = uint64_t; };

// template<Type T>
// using type_to_type_t = typename type_to_type<T>::type;

// template<template<typename> class T>
// auto transform_tag(Type type_tag){
//     switch (type_tag)
//     {
//     case Type::DoublePointer: return T<type_to_type_t<Type::DoublePointer>>::value;
//     case Type::Double: return T<type_to_type_t<Type::Double>>::value;
//     case Type::UInt64Pointer:    return T<type_to_type_t<Type::UInt64Pointer>>::value;
//     }
// }

// // guts
// template<template<typename, typename> class Base>
// struct type_proxy {
//     template<typename T>
//     struct partial_base_proxy {
//         template<typename U>
//         using partial_base_l = Base<U, T>;
//         template<typename U>
//         using partial_base_r = Base<T, U>;
//     };

//     template<typename Type_T>
//     struct partial_proxy {
//         static auto value(Object* l, Object* r) {
//             return transform_tag<partial_base_proxy<Type_T>::template partial_base_r>(r->type)(l, r);
//         }
//     };

//     static auto call_obj_obj(Object* l, Object* r) {
//         return transform_tag<partial_proxy>(l->type)(l, r);
//     }

//     template<typename T>
//     static auto call_obj_v(Object* l, T value) {
//         return transform_tag<partial_base_proxy<T>::template partial_base_r>(l->type)(l, value);
//     }
// };

// template<template <typename, typename> class Base>
// struct op_wrapper {
//     template<typename T, typename U>
//     struct obj_obj {
//         static auto value(Object* l, Object* r) {
//             return Base<T, U>::value(*reinterpret_cast<T*>(l->as_void_pointer), *reinterpret_cast<U*>(r->as_void_pointer));
//         }
//     };

//     template<typename T, typename U>
//     struct obj_v {
//         static auto value(Object* l, T r) {
//             return Base<T, U>::value(*reinterpret_cast<T*>(l->as_void_pointer), r);
//         }
//     };
// };

// // operations, added on new features
// struct type_callable {
//     using fun_ptr = void (*)(Object*, Object*);

//     fun_ptr add;
//     fun_ptr sub;
// };

// template<typename T, typename U>
// struct do_add {
//     static void value(T& l, const U& r) {
//         l += r;
//     }
// };

// template<typename T, typename U>
// struct do_sub {
//     static void value(T& l, const U& r) {
//         l -= r;
//     }
// };

// // actual functions
// void add(Object* l, Object* r) {
//     type_proxy<op_wrapper<do_add>::obj_obj>::call_obj_obj(l, r);
// }

// template<typename T>
// void add(Object* l, T r) {
//     type_proxy<op_wrapper<do_add>::obj_v>::call_obj_v(l, r);
// }

// #endif
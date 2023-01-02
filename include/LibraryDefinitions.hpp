#ifndef LIBRARYDEFINITIONS_HPP
#define LIBRARYDEFINITIONS_HPP

#if defined(_MSC_VER)
    //  Microsoft 
    #define VOLT_API_EXPORT __declspec(dllexport)
    #define VOLT_API_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC
    #define VOLT_API_EXPORT __attribute__((visibility("default")))
    #define VOLT_API_IMPORT
#else
    //  do nothing and hope for the best?
    #define VOLT_API_EXPORT
    #define VOLT_API_IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

#endif
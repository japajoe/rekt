#include <ConversionUtility.hpp>
#include <cstring>

namespace REKT
{
    //Yep this is some retarded shit right here. If you have a better way let me know.
    //And yes the naming schemes are backwards -_-
    ConvertCallbackPtr ConversionUtility::convertFunctions[][18] =
    {
        {ConvertInt8PointerInt8Pointer, ConvertInt8PointerUInt8Pointer, ConvertInt8PointerInt16Pointer, ConvertInt8PointerUInt16Pointer, ConvertInt8PointerInt32Pointer, ConvertInt8PointerUInt32Pointer, ConvertInt8PointerInt64Pointer, ConvertInt8PointerUInt64Pointer, ConvertInt8PointerDoublePointer, ConvertInt8PointerInt8, ConvertInt8PointerUInt8, ConvertInt8PointerInt16, ConvertInt8PointerUInt16, ConvertInt8PointerInt32, ConvertInt8PointerUInt32, ConvertInt8PointerInt64, ConvertInt8PointerUInt64, ConvertInt8PointerDouble},
        {ConvertUInt8PointerInt8Pointer, ConvertUInt8PointerUInt8Pointer, ConvertUInt8PointerInt16Pointer, ConvertUInt8PointerUInt16Pointer, ConvertUInt8PointerInt32Pointer, ConvertUInt8PointerUInt32Pointer, ConvertUInt8PointerInt64Pointer, ConvertUInt8PointerUInt64Pointer, ConvertUInt8PointerDoublePointer, ConvertUInt8PointerInt8, ConvertUInt8PointerUInt8, ConvertUInt8PointerInt16, ConvertUInt8PointerUInt16, ConvertUInt8PointerInt32, ConvertUInt8PointerUInt32, ConvertUInt8PointerInt64, ConvertUInt8PointerUInt64, ConvertUInt8PointerDouble},
        {ConvertInt16PointerInt8Pointer, ConvertInt16PointerUInt8Pointer, ConvertInt16PointerInt16Pointer, ConvertInt16PointerUInt16Pointer, ConvertInt16PointerInt32Pointer, ConvertInt16PointerUInt32Pointer, ConvertInt16PointerInt64Pointer, ConvertInt16PointerUInt64Pointer, ConvertInt16PointerDoublePointer, ConvertInt16PointerInt8, ConvertInt16PointerUInt8, ConvertInt16PointerInt16, ConvertInt16PointerUInt16, ConvertInt16PointerInt32, ConvertInt16PointerUInt32, ConvertInt16PointerInt64, ConvertInt16PointerUInt64, ConvertInt16PointerDouble},
        {ConvertUInt16PointerInt8Pointer, ConvertUInt16PointerUInt8Pointer, ConvertUInt16PointerInt16Pointer, ConvertUInt16PointerUInt16Pointer, ConvertUInt16PointerInt32Pointer, ConvertUInt16PointerUInt32Pointer, ConvertUInt16PointerInt64Pointer, ConvertUInt16PointerUInt64Pointer, ConvertUInt16PointerDoublePointer, ConvertUInt16PointerInt8, ConvertUInt16PointerUInt8, ConvertUInt16PointerInt16, ConvertUInt16PointerUInt16, ConvertUInt16PointerInt32, ConvertUInt16PointerUInt32, ConvertUInt16PointerInt64, ConvertUInt16PointerUInt64, ConvertUInt16PointerDouble},
        {ConvertInt32PointerInt8Pointer, ConvertInt32PointerUInt8Pointer, ConvertInt32PointerInt16Pointer, ConvertInt32PointerUInt16Pointer, ConvertInt32PointerInt32Pointer, ConvertInt32PointerUInt32Pointer, ConvertInt32PointerInt64Pointer, ConvertInt32PointerUInt64Pointer, ConvertInt32PointerDoublePointer, ConvertInt32PointerInt8, ConvertInt32PointerUInt8, ConvertInt32PointerInt16, ConvertInt32PointerUInt16, ConvertInt32PointerInt32, ConvertInt32PointerUInt32, ConvertInt32PointerInt64, ConvertInt32PointerUInt64, ConvertInt32PointerDouble},
        {ConvertUInt32PointerInt8Pointer, ConvertUInt32PointerUInt8Pointer, ConvertUInt32PointerInt16Pointer, ConvertUInt32PointerUInt16Pointer, ConvertUInt32PointerInt32Pointer, ConvertUInt32PointerUInt32Pointer, ConvertUInt32PointerInt64Pointer, ConvertUInt32PointerUInt64Pointer, ConvertUInt32PointerDoublePointer, ConvertUInt32PointerInt8, ConvertUInt32PointerUInt8, ConvertUInt32PointerInt16, ConvertUInt32PointerUInt16, ConvertUInt32PointerInt32, ConvertUInt32PointerUInt32, ConvertUInt32PointerInt64, ConvertUInt32PointerUInt64, ConvertUInt32PointerDouble},
        {ConvertInt64PointerInt8Pointer, ConvertInt64PointerUInt8Pointer, ConvertInt64PointerInt16Pointer, ConvertInt64PointerUInt16Pointer, ConvertInt64PointerInt32Pointer, ConvertInt64PointerUInt32Pointer, ConvertInt64PointerInt64Pointer, ConvertInt64PointerUInt64Pointer, ConvertInt64PointerDoublePointer, ConvertInt64PointerInt8, ConvertInt64PointerUInt8, ConvertInt64PointerInt16, ConvertInt64PointerUInt16, ConvertInt64PointerInt32, ConvertInt64PointerUInt32, ConvertInt64PointerInt64, ConvertInt64PointerUInt64, ConvertInt64PointerDouble},
        {ConvertUInt64PointerInt8Pointer, ConvertUInt64PointerUInt8Pointer, ConvertUInt64PointerInt16Pointer, ConvertUInt64PointerUInt16Pointer, ConvertUInt64PointerInt32Pointer, ConvertUInt64PointerUInt32Pointer, ConvertUInt64PointerInt64Pointer, ConvertUInt64PointerUInt64Pointer, ConvertUInt64PointerDoublePointer, ConvertUInt64PointerInt8, ConvertUInt64PointerUInt8, ConvertUInt64PointerInt16, ConvertUInt64PointerUInt16, ConvertUInt64PointerInt32, ConvertUInt64PointerUInt32, ConvertUInt64PointerInt64, ConvertUInt64PointerUInt64, ConvertUInt64PointerDouble},
        {ConvertDoublePointerInt8Pointer, ConvertDoublePointerUInt8Pointer, ConvertDoublePointerInt16Pointer, ConvertDoublePointerUInt16Pointer, ConvertDoublePointerInt32Pointer, ConvertDoublePointerUInt32Pointer, ConvertDoublePointerInt64Pointer, ConvertDoublePointerUInt64Pointer, ConvertDoublePointerDoublePointer, ConvertDoublePointerInt8, ConvertDoublePointerUInt8, ConvertDoublePointerInt16, ConvertDoublePointerUInt16, ConvertDoublePointerInt32, ConvertDoublePointerUInt32, ConvertDoublePointerInt64, ConvertDoublePointerUInt64, ConvertDoublePointerDouble},
        {ConvertInt8Int8Pointer, ConvertInt8UInt8Pointer, ConvertInt8Int16Pointer, ConvertInt8UInt16Pointer, ConvertInt8Int32Pointer, ConvertInt8UInt32Pointer, ConvertInt8Int64Pointer, ConvertInt8UInt64Pointer, ConvertInt8DoublePointer, ConvertInt8Int8, ConvertInt8UInt8, ConvertInt8Int16, ConvertInt8UInt16, ConvertInt8Int32, ConvertInt8UInt32, ConvertInt8Int64, ConvertInt8UInt64, ConvertInt8Double},
        {ConvertUInt8Int8Pointer, ConvertUInt8UInt8Pointer, ConvertUInt8Int16Pointer, ConvertUInt8UInt16Pointer, ConvertUInt8Int32Pointer, ConvertUInt8UInt32Pointer, ConvertUInt8Int64Pointer, ConvertUInt8UInt64Pointer, ConvertUInt8DoublePointer, ConvertUInt8Int8, ConvertUInt8UInt8, ConvertUInt8Int16, ConvertUInt8UInt16, ConvertUInt8Int32, ConvertUInt8UInt32, ConvertUInt8Int64, ConvertUInt8UInt64, ConvertUInt8Double},
        {ConvertInt16Int8Pointer, ConvertInt16UInt8Pointer, ConvertInt16Int16Pointer, ConvertInt16UInt16Pointer, ConvertInt16Int32Pointer, ConvertInt16UInt32Pointer, ConvertInt16Int64Pointer, ConvertInt16UInt64Pointer, ConvertInt16DoublePointer, ConvertInt16Int8, ConvertInt16UInt8, ConvertInt16Int16, ConvertInt16UInt16, ConvertInt16Int32, ConvertInt16UInt32, ConvertInt16Int64, ConvertInt16UInt64, ConvertInt16Double},
        {ConvertUInt16Int8Pointer, ConvertUInt16UInt8Pointer, ConvertUInt16Int16Pointer, ConvertUInt16UInt16Pointer, ConvertUInt16Int32Pointer, ConvertUInt16UInt32Pointer, ConvertUInt16Int64Pointer, ConvertUInt16UInt64Pointer, ConvertUInt16DoublePointer, ConvertUInt16Int8, ConvertUInt16UInt8, ConvertUInt16Int16, ConvertUInt16UInt16, ConvertUInt16Int32, ConvertUInt16UInt32, ConvertUInt16Int64, ConvertUInt16UInt64, ConvertUInt16Double},
        {ConvertInt32Int8Pointer, ConvertInt32UInt8Pointer, ConvertInt32Int16Pointer, ConvertInt32UInt16Pointer, ConvertInt32Int32Pointer, ConvertInt32UInt32Pointer, ConvertInt32Int64Pointer, ConvertInt32UInt64Pointer, ConvertInt32DoublePointer, ConvertInt32Int8, ConvertInt32UInt8, ConvertInt32Int16, ConvertInt32UInt16, ConvertInt32Int32, ConvertInt32UInt32, ConvertInt32Int64, ConvertInt32UInt64, ConvertInt32Double},
        {ConvertUInt32Int8Pointer, ConvertUInt32UInt8Pointer, ConvertUInt32Int16Pointer, ConvertUInt32UInt16Pointer, ConvertUInt32Int32Pointer, ConvertUInt32UInt32Pointer, ConvertUInt32Int64Pointer, ConvertUInt32UInt64Pointer, ConvertUInt32DoublePointer, ConvertUInt32Int8, ConvertUInt32UInt8, ConvertUInt32Int16, ConvertUInt32UInt16, ConvertUInt32Int32, ConvertUInt32UInt32, ConvertUInt32Int64, ConvertUInt32UInt64, ConvertUInt32Double},
        {ConvertInt64Int8Pointer, ConvertInt64UInt8Pointer, ConvertInt64Int16Pointer, ConvertInt64UInt16Pointer, ConvertInt64Int32Pointer, ConvertInt64UInt32Pointer, ConvertInt64Int64Pointer, ConvertInt64UInt64Pointer, ConvertInt64DoublePointer, ConvertInt64Int8, ConvertInt64UInt8, ConvertInt64Int16, ConvertInt64UInt16, ConvertInt64Int32, ConvertInt64UInt32, ConvertInt64Int64, ConvertInt64UInt64, ConvertInt64Double},
        {ConvertUInt64Int8Pointer, ConvertUInt64UInt8Pointer, ConvertUInt64Int16Pointer, ConvertUInt64UInt16Pointer, ConvertUInt64Int32Pointer, ConvertUInt64UInt32Pointer, ConvertUInt64Int64Pointer, ConvertUInt64UInt64Pointer, ConvertUInt64DoublePointer, ConvertUInt64Int8, ConvertUInt64UInt8, ConvertUInt64Int16, ConvertUInt64UInt16, ConvertUInt64Int32, ConvertUInt64UInt32, ConvertUInt64Int64, ConvertUInt64UInt64, ConvertUInt64Double},
        {ConvertDoubleInt8Pointer, ConvertDoubleUInt8Pointer, ConvertDoubleInt16Pointer, ConvertDoubleUInt16Pointer, ConvertDoubleInt32Pointer, ConvertDoubleUInt32Pointer, ConvertDoubleInt64Pointer, ConvertDoubleUInt64Pointer, ConvertDoubleDoublePointer, ConvertDoubleInt8, ConvertDoubleUInt8, ConvertDoubleInt16, ConvertDoubleUInt16, ConvertDoubleInt32, ConvertDoubleUInt32, ConvertDoubleInt64, ConvertDoubleUInt64, ConvertDoubleDouble}
    };

    void ConversionUtility::CastSourceToDestinationType(Object* src, Object* dst, Type srcType, Type dstType)
    {
        switch(srcType)
        {
            case Type::CharPointer:
            {
                switch(dstType)
                {
                    case Type::CharPointer:
                    case Type::VoidPointer:
                        dst->as_void_pointer = src->as_void_pointer;
                        dst->type = Type::CharPointer;
                        break;                        
                }
                break;
            }             
            case Type::VoidPointer:
            {
                switch(dstType)
                {
                    case Type::CharPointer:
                    case Type::VoidPointer:
                        dst->as_void_pointer = src->as_void_pointer;
                        dst->type = Type::VoidPointer;
                        break;                        
                }
                break;
            }
            default:
                convertFunctions[dstType][srcType](dst, src);
                break;
        }

        //Keep this around for a while just in case
        // switch(srcType)
        // {
        //     case Type::CharPointer:
        //     {
        //         switch(dstType)
        //         {
        //             case Type::CharPointer:
        //             case Type::VoidPointer:
        //                 dst->as_void_pointer = src->as_void_pointer;
        //                 dst->type = Type::CharPointer;
        //                 break;                        
        //         }
        //         break;
        //     }             
        //     case Type::VoidPointer:
        //     {
        //         switch(dstType)
        //         {
        //             case Type::CharPointer:
        //             case Type::VoidPointer:
        //                 dst->as_void_pointer = src->as_void_pointer;
        //                 dst->type = Type::VoidPointer;
        //                 break;                        
        //         }
        //         break;
        //     }            
        //     case Type::DoublePointer:
        //     {
        //         switch(dstType)
        //         {
        //             case Type::Double:
        //             {
        //                 *dst->as_double_pointer = src->as_double;
        //                 break;
        //             }
        //             case Type::Int16:
        //             {
        //                 *dst->as_double_pointer = src->as_int16;
        //                 break;
        //             }
        //             case Type::Int32:
        //             {
        //                 *dst->as_double_pointer = src->as_int32;
        //                 break;
        //             }
        //             case Type::Int64:
        //             {
        //                 *dst->as_double_pointer = src->as_int64;
        //                 break;       
        //             }
        //             case Type::Int8:
        //             {
        //                 *dst->as_double_pointer = src->as_int8;
        //                 break;
        //             }
        //             case Type::UInt16:
        //             {
        //                 *dst->as_double_pointer = src->as_uint16;
        //                 break;       
        //             }
        //             case Type::UInt32:
        //             {
        //                 *dst->as_double_pointer = src->as_uint32;
        //                 break;        
        //             }
        //             case Type::UInt64:
        //             {
        //                 *dst->as_double_pointer = src->as_uint64;
        //                 break;                            
        //             }
        //             case Type::UInt8:
        //             {
        //                 *dst->as_double_pointer = src->as_uint8;
        //                 break;                                    
        //             }


        //             case Type::DoublePointer:
        //             {
        //                 *dst->as_double_pointer = *src->as_double_pointer;
        //                 break;
        //             }
        //             case Type::Int16Pointer:
        //             {
        //                 *dst->as_double_pointer = *src->as_int16_pointer;
        //                 break;
        //             }
        //             case Type::Int32Pointer:
        //             {
        //                 *dst->as_double_pointer = *src->as_int32_pointer;
        //                 break;
        //             }
        //             case Type::Int64Pointer:
        //             {
        //                 *dst->as_double_pointer = *src->as_int64_pointer;
        //                 break;       
        //             }
        //             case Type::Int8Pointer:
        //             {
        //                 *dst->as_double_pointer = *src->as_int8_pointer;
        //                 break;
        //             }
        //             case Type::UInt16Pointer:
        //             {
        //                 *dst->as_double_pointer = *src->as_uint16_pointer;
        //                 break;       
        //             }
        //             case Type::UInt32Pointer:
        //             {
        //                 *dst->as_double_pointer = *src->as_uint32_pointer;
        //                 break;        
        //             }
        //             case Type::UInt64Pointer:
        //             {
        //                 *dst->as_double_pointer = *src->as_uint64_pointer;
        //                 break;                            
        //             }
        //             case Type::UInt8Pointer:
        //             {
        //                 *dst->as_double_pointer = *src->as_uint8_pointer;
        //                 break;                                    
        //             }
        //         }
        //         break;
        //     }
        //     case Type::Int16Pointer:
        //     {
        //         switch(dstType)
        //         {
        //             case Type::Double:
        //             {
        //                 *dst->as_int16_pointer = src->as_double;
        //                 break;
        //             }
        //             case Type::Int16:
        //             {
        //                 *dst->as_int16_pointer = src->as_int16;
        //                 break;
        //             }
        //             case Type::Int32:
        //             {
        //                 *dst->as_int16_pointer = src->as_int32;
        //                 break;
        //             }
        //             case Type::Int64:
        //             {
        //                 *dst->as_int16_pointer = src->as_int64;
        //                 break;       
        //             }
        //             case Type::Int8:
        //             {
        //                 *dst->as_int16_pointer = src->as_int8;
        //                 break;
        //             }
        //             case Type::UInt16:
        //             {
        //                 *dst->as_int16_pointer = src->as_uint16;
        //                 break;       
        //             }
        //             case Type::UInt32:
        //             {
        //                 *dst->as_int16_pointer = src->as_uint32;
        //                 break;        
        //             }
        //             case Type::UInt64:
        //             {
        //                 *dst->as_int16_pointer = src->as_uint64;
        //                 break;                            
        //             }
        //             case Type::UInt8:
        //             {
        //                 *dst->as_int16_pointer = src->as_uint8;
        //                 break;                                    
        //             }


        //             case Type::DoublePointer:
        //             {
        //                 *dst->as_int16_pointer = *src->as_double_pointer;
        //                 break;
        //             }
        //             case Type::Int16Pointer:
        //             {
        //                 *dst->as_int16_pointer = *src->as_int16_pointer;
        //                 break;
        //             }
        //             case Type::Int32Pointer:
        //             {
        //                 *dst->as_int16_pointer = *src->as_int32_pointer;
        //                 break;
        //             }
        //             case Type::Int64Pointer:
        //             {
        //                 *dst->as_int16_pointer = *src->as_int64_pointer;
        //                 break;       
        //             }
        //             case Type::Int8Pointer:
        //             {
        //                 *dst->as_int16_pointer = *src->as_int8_pointer;
        //                 break;
        //             }
        //             case Type::UInt16Pointer:
        //             {
        //                 *dst->as_int16_pointer = *src->as_uint16_pointer;
        //                 break;       
        //             }
        //             case Type::UInt32Pointer:
        //             {
        //                 *dst->as_int16_pointer = *src->as_uint32_pointer;
        //                 break;        
        //             }
        //             case Type::UInt64Pointer:
        //             {
        //                 *dst->as_int16_pointer = *src->as_uint64_pointer;
        //                 break;                            
        //             }
        //             case Type::UInt8Pointer:
        //             {
        //                 *dst->as_int16_pointer = *src->as_uint8_pointer;
        //                 break;                                    
        //             }
        //         }
        //         break;
        //     }
        //     case Type::Int32Pointer:
        //     {
        //         switch(dstType)
        //         {
        //             case Type::Double:
        //             {
        //                 *dst->as_int32_pointer = src->as_double;
        //                 break;
        //             }
        //             case Type::Int16:
        //             {
        //                 *dst->as_int32_pointer = src->as_int16;
        //                 break;
        //             }
        //             case Type::Int32:
        //             {
        //                 *dst->as_int32_pointer = src->as_int32;
        //                 break;
        //             }
        //             case Type::Int64:
        //             {
        //                 *dst->as_int32_pointer = src->as_int64;
        //                 break;       
        //             }
        //             case Type::Int8:
        //             {
        //                 *dst->as_int32_pointer = src->as_int8;
        //                 break;
        //             }
        //             case Type::UInt16:
        //             {
        //                 *dst->as_int32_pointer = src->as_uint16;
        //                 break;       
        //             }
        //             case Type::UInt32:
        //             {
        //                 *dst->as_int32_pointer = src->as_uint32;
        //                 break;        
        //             }
        //             case Type::UInt64:
        //             {
        //                 *dst->as_int32_pointer = src->as_uint64;
        //                 break;                            
        //             }
        //             case Type::UInt8:
        //             {
        //                 *dst->as_int32_pointer = src->as_uint8;
        //                 break;                                    
        //             }


        //             case Type::DoublePointer:
        //             {
        //                 *dst->as_int32_pointer = *src->as_double_pointer;
        //                 break;
        //             }
        //             case Type::Int16Pointer:
        //             {
        //                 *dst->as_int32_pointer = *src->as_int16_pointer;
        //                 break;
        //             }
        //             case Type::Int32Pointer:
        //             {
        //                 *dst->as_int32_pointer = *src->as_int32_pointer;
        //                 break;
        //             }
        //             case Type::Int64Pointer:
        //             {
        //                 *dst->as_int32_pointer = *src->as_int64_pointer;
        //                 break;       
        //             }
        //             case Type::Int8Pointer:
        //             {
        //                 *dst->as_int32_pointer = *src->as_int8_pointer;
        //                 break;
        //             }
        //             case Type::UInt16Pointer:
        //             {
        //                 *dst->as_int32_pointer = *src->as_uint16_pointer;
        //                 break;       
        //             }
        //             case Type::UInt32Pointer:
        //             {
        //                 *dst->as_int32_pointer = *src->as_uint32_pointer;
        //                 break;        
        //             }
        //             case Type::UInt64Pointer:
        //             {
        //                 *dst->as_int32_pointer = *src->as_uint64_pointer;
        //                 break;                            
        //             }
        //             case Type::UInt8Pointer:
        //             {
        //                 *dst->as_int32_pointer = *src->as_uint8_pointer;
        //                 break;                                    
        //             }
        //         }
        //         break;
        //     }                                                                           
        //     case Type::Int64Pointer:
        //     {
        //         switch(dstType)
        //         {
        //             case Type::Double:
        //             {
        //                 *dst->as_int64_pointer = src->as_double;
        //                 break;
        //             }
        //             case Type::Int16:
        //             {
        //                 *dst->as_int64_pointer = src->as_int16;
        //                 break;
        //             }
        //             case Type::Int32:
        //             {
        //                 *dst->as_int64_pointer = src->as_int32;
        //                 break;
        //             }
        //             case Type::Int64:
        //             {
        //                 *dst->as_int64_pointer = src->as_int64;
        //                 break;       
        //             }
        //             case Type::Int8:
        //             {
        //                 *dst->as_int64_pointer = src->as_int8;
        //                 break;
        //             }
        //             case Type::UInt16:
        //             {
        //                 *dst->as_int64_pointer = src->as_uint16;
        //                 break;       
        //             }
        //             case Type::UInt32:
        //             {
        //                 *dst->as_int64_pointer = src->as_uint32;
        //                 break;        
        //             }
        //             case Type::UInt64:
        //             {
        //                 *dst->as_int64_pointer = src->as_uint64;
        //                 break;                            
        //             }
        //             case Type::UInt8:
        //             {
        //                 *dst->as_int64_pointer = src->as_uint8;
        //                 break;                                    
        //             }


        //             case Type::DoublePointer:
        //             {
        //                 *dst->as_int64_pointer = *src->as_double_pointer;
        //                 break;
        //             }
        //             case Type::Int16Pointer:
        //             {
        //                 *dst->as_int64_pointer = *src->as_int16_pointer;
        //                 break;
        //             }
        //             case Type::Int32Pointer:
        //             {
        //                 *dst->as_int64_pointer = *src->as_int32_pointer;
        //                 break;
        //             }
        //             case Type::Int64Pointer:
        //             {
        //                 *dst->as_int64_pointer = *src->as_int64_pointer;
        //                 break;       
        //             }
        //             case Type::Int8Pointer:
        //             {
        //                 *dst->as_int64_pointer = *src->as_int8_pointer;
        //                 break;
        //             }
        //             case Type::UInt16Pointer:
        //             {
        //                 *dst->as_int64_pointer = *src->as_uint16_pointer;
        //                 break;       
        //             }
        //             case Type::UInt32Pointer:
        //             {
        //                 *dst->as_int64_pointer = *src->as_uint32_pointer;
        //                 break;        
        //             }
        //             case Type::UInt64Pointer:
        //             {
        //                 *dst->as_int64_pointer = *src->as_uint64_pointer;
        //                 break;                            
        //             }
        //             case Type::UInt8Pointer:
        //             {
        //                 *dst->as_int64_pointer = *src->as_uint8_pointer;
        //                 break;                                    
        //             }
        //         }
        //         break;
        //     }
        //     case Type::Int8Pointer:
        //     {
        //         switch(dstType)
        //         {
        //             case Type::Double:
        //             {
        //                 *dst->as_int8_pointer = src->as_double;
        //                 break;
        //             }
        //             case Type::Int16:
        //             {
        //                 *dst->as_int8_pointer = src->as_int16;
        //                 break;
        //             }
        //             case Type::Int32:
        //             {
        //                 *dst->as_int8_pointer = src->as_int32;
        //                 break;
        //             }
        //             case Type::Int64:
        //             {
        //                 *dst->as_int8_pointer = src->as_int64;
        //                 break;       
        //             }
        //             case Type::Int8:
        //             {
        //                 *dst->as_int8_pointer = src->as_int8;
        //                 break;
        //             }
        //             case Type::UInt16:
        //             {
        //                 *dst->as_int8_pointer = src->as_uint16;
        //                 break;       
        //             }
        //             case Type::UInt32:
        //             {
        //                 *dst->as_int8_pointer = src->as_uint32;
        //                 break;        
        //             }
        //             case Type::UInt64:
        //             {
        //                 *dst->as_int8_pointer = src->as_uint64;
        //                 break;                            
        //             }
        //             case Type::UInt8:
        //             {
        //                 *dst->as_int8_pointer = src->as_uint8;
        //                 break;                                    
        //             }



        //             case Type::DoublePointer:
        //             {
        //                 *dst->as_int8_pointer = *src->as_double_pointer;
        //                 break;
        //             }
        //             case Type::Int16Pointer:
        //             {
        //                 *dst->as_int8_pointer = *src->as_int16_pointer;
        //                 break;
        //             }
        //             case Type::Int32Pointer:
        //             {
        //                 *dst->as_int8_pointer = *src->as_int32_pointer;
        //                 break;
        //             }
        //             case Type::Int64Pointer:
        //             {
        //                 *dst->as_int8_pointer = *src->as_int64_pointer;
        //                 break;       
        //             }
        //             case Type::Int8Pointer:
        //             {
        //                 *dst->as_int8_pointer = *src->as_int8_pointer;
        //                 break;
        //             }
        //             case Type::UInt16Pointer:
        //             {
        //                 *dst->as_int8_pointer = *src->as_uint16_pointer;
        //                 break;       
        //             }
        //             case Type::UInt32Pointer:
        //             {
        //                 *dst->as_int8_pointer = *src->as_uint32_pointer;
        //                 break;        
        //             }
        //             case Type::UInt64Pointer:
        //             {
        //                 *dst->as_int8_pointer = *src->as_uint64_pointer;
        //                 break;                            
        //             }
        //             case Type::UInt8Pointer:
        //             {
        //                 *dst->as_int8_pointer = *src->as_uint8_pointer;
        //                 break;                                    
        //             }
        //         }
        //         break;
        //     }
        //     case Type::UInt16Pointer:
        //     {
        //         switch(dstType)
        //         {
        //             case Type::Double:
        //             {
        //                 *dst->as_uint16_pointer = src->as_double;
        //                 break;
        //             }
        //             case Type::Int16:
        //             {
        //                 *dst->as_uint16_pointer = src->as_int16;
        //                 break;
        //             }
        //             case Type::Int32:
        //             {
        //                 *dst->as_uint16_pointer = src->as_int32;
        //                 break;
        //             }
        //             case Type::Int64:
        //             {
        //                 *dst->as_uint16_pointer = src->as_int64;
        //                 break;       
        //             }
        //             case Type::Int8:
        //             {
        //                 *dst->as_uint16_pointer = src->as_int8;
        //                 break;
        //             }
        //             case Type::UInt16:
        //             {
        //                 *dst->as_uint16_pointer = src->as_uint16;
        //                 break;       
        //             }
        //             case Type::UInt32:
        //             {
        //                 *dst->as_uint16_pointer = src->as_uint32;
        //                 break;        
        //             }
        //             case Type::UInt64:
        //             {
        //                 *dst->as_uint16_pointer = src->as_uint64;
        //                 break;                            
        //             }
        //             case Type::UInt8:
        //             {
        //                 *dst->as_uint16_pointer = src->as_uint8;
        //                 break;                                    
        //             }


        //             case Type::DoublePointer:
        //             {
        //                 *dst->as_uint16_pointer = *src->as_double_pointer;
        //                 break;
        //             }
        //             case Type::Int16Pointer:
        //             {
        //                 *dst->as_uint16_pointer = *src->as_int16_pointer;
        //                 break;
        //             }
        //             case Type::Int32Pointer:
        //             {
        //                 *dst->as_uint16_pointer = *src->as_int32_pointer;
        //                 break;
        //             }
        //             case Type::Int64Pointer:
        //             {
        //                 *dst->as_uint16_pointer = *src->as_int64_pointer;
        //                 break;       
        //             }
        //             case Type::Int8Pointer:
        //             {
        //                 *dst->as_uint16_pointer = *src->as_int8_pointer;
        //                 break;
        //             }
        //             case Type::UInt16Pointer:
        //             {
        //                 *dst->as_uint16_pointer = *src->as_uint16_pointer;
        //                 break;       
        //             }
        //             case Type::UInt32Pointer:
        //             {
        //                 *dst->as_uint16_pointer = *src->as_uint32_pointer;
        //                 break;        
        //             }
        //             case Type::UInt64Pointer:
        //             {
        //                 *dst->as_uint16_pointer = *src->as_uint64_pointer;
        //                 break;                            
        //             }
        //             case Type::UInt8Pointer:
        //             {
        //                 *dst->as_uint16_pointer = *src->as_uint8_pointer;
        //                 break;                                    
        //             }
        //         }
        //         break;
        //     }               
        //     case Type::UInt32Pointer:
        //     {
        //         switch(dstType)
        //         {
        //             case Type::Double:
        //             {
        //                 *dst->as_uint32_pointer = src->as_double;
        //                 break;
        //             }
        //             case Type::Int16:
        //             {
        //                 *dst->as_uint32_pointer = src->as_int16;
        //                 break;
        //             }
        //             case Type::Int32:
        //             {
        //                 *dst->as_uint32_pointer = src->as_int32;
        //                 break;
        //             }
        //             case Type::Int64:
        //             {
        //                 *dst->as_uint32_pointer = src->as_int64;
        //                 break;       
        //             }
        //             case Type::Int8:
        //             {
        //                 *dst->as_uint32_pointer = src->as_int8;
        //                 break;
        //             }
        //             case Type::UInt16:
        //             {
        //                 *dst->as_uint32_pointer = src->as_uint16;
        //                 break;       
        //             }
        //             case Type::UInt32:
        //             {
        //                 *dst->as_uint32_pointer = src->as_uint32;
        //                 break;        
        //             }
        //             case Type::UInt64:
        //             {
        //                 *dst->as_uint32_pointer = src->as_uint64;
        //                 break;                            
        //             }
        //             case Type::UInt8:
        //             {
        //                 *dst->as_uint32_pointer = src->as_uint8;
        //                 break;                                    
        //             }


        //             case Type::DoublePointer:
        //             {
        //                 *dst->as_uint32_pointer = *src->as_double_pointer;
        //                 break;
        //             }
        //             case Type::Int16Pointer:
        //             {
        //                 *dst->as_uint32_pointer = *src->as_int16_pointer;
        //                 break;
        //             }
        //             case Type::Int32Pointer:
        //             {
        //                 *dst->as_uint32_pointer = *src->as_int32_pointer;
        //                 break;
        //             }
        //             case Type::Int64Pointer:
        //             {
        //                 *dst->as_uint32_pointer = *src->as_int64_pointer;
        //                 break;       
        //             }
        //             case Type::Int8Pointer:
        //             {
        //                 *src->as_uint32_pointer = *src->as_int8_pointer;
        //                 break;
        //             }
        //             case Type::UInt16Pointer:
        //             {
        //                 *dst->as_uint32_pointer = *src->as_uint16_pointer;
        //                 break;       
        //             }
        //             case Type::UInt32Pointer:
        //             {
        //                 *dst->as_uint32_pointer = *src->as_uint32_pointer;
        //                 break;        
        //             }
        //             case Type::UInt64Pointer:
        //             {
        //                 *dst->as_uint32_pointer = *src->as_uint64_pointer;
        //                 break;                            
        //             }
        //             case Type::UInt8Pointer:
        //             {
        //                 *dst->as_uint32_pointer = *src->as_uint8_pointer;
        //                 break;                                    
        //             }
        //         }
        //         break;
        //     }               
        //     case Type::UInt64Pointer:
        //     {
        //         switch(dstType)
        //         {
        //             case Type::Double:
        //             {
        //                 *dst->as_uint64_pointer = src->as_double;
        //                 break;
        //             }
        //             case Type::Int16:
        //             {
        //                 *dst->as_uint64_pointer = src->as_int16;
        //                 break;
        //             }
        //             case Type::Int32:
        //             {
        //                 *dst->as_uint64_pointer = src->as_int32;
        //                 break;
        //             }
        //             case Type::Int64:
        //             {
        //                 *dst->as_uint64_pointer = src->as_int64;
        //                 break;       
        //             }
        //             case Type::Int8:
        //             {
        //                 *dst->as_uint64_pointer = src->as_int8;
        //                 break;
        //             }
        //             case Type::UInt16:
        //             {
        //                 *dst->as_uint64_pointer = src->as_uint16;
        //                 break;       
        //             }
        //             case Type::UInt32:
        //             {
        //                 *dst->as_uint64_pointer = src->as_uint32;
        //                 break;        
        //             }
        //             case Type::UInt64:
        //             {
        //                 *dst->as_uint64_pointer = src->as_uint64;
        //                 break;                            
        //             }
        //             case Type::UInt8:
        //             {
        //                 *dst->as_uint64_pointer = src->as_uint8;
        //                 break;                                    
        //             }


        //             case Type::DoublePointer:
        //             {
        //                 *dst->as_uint64_pointer = *src->as_double_pointer;
        //                 break;
        //             }
        //             case Type::Int16Pointer:
        //             {
        //                 *dst->as_uint64_pointer = *src->as_int16_pointer;
        //                 break;
        //             }
        //             case Type::Int32Pointer:
        //             {
        //                 *dst->as_uint64_pointer = *src->as_int32_pointer;
        //                 break;
        //             }
        //             case Type::Int64Pointer:
        //             {
        //                 *dst->as_uint64_pointer = *src->as_int64_pointer;
        //                 break;       
        //             }
        //             case Type::Int8Pointer:
        //             {
        //                 *dst->as_uint64_pointer = *src->as_int8_pointer;
        //                 break;
        //             }
        //             case Type::UInt16Pointer:
        //             {
        //                 *dst->as_uint64_pointer = *src->as_uint16_pointer;
        //                 break;       
        //             }
        //             case Type::UInt32Pointer:
        //             {
        //                 *dst->as_uint64_pointer = *src->as_uint32_pointer;
        //                 break;        
        //             }
        //             case Type::UInt64Pointer:
        //             {
        //                 *dst->as_uint64_pointer = *src->as_uint64_pointer;
        //                 break;                            
        //             }
        //             case Type::UInt8Pointer:
        //             {
        //                 *dst->as_uint64_pointer = *src->as_uint8_pointer;
        //                 break;                                    
        //             }
        //         }
        //         break;
        //     }               
        //     case Type::UInt8Pointer:
        //     {
        //         switch(dstType)
        //         {
        //             case Type::Double:
        //             {
        //                 *dst->as_uint8_pointer = src->as_double;
        //                 break;
        //             }
        //             case Type::Int16:
        //             {
        //                 *dst->as_uint8_pointer = src->as_int16;
        //                 break;
        //             }
        //             case Type::Int32:
        //             {
        //                 *dst->as_uint8_pointer = src->as_int32;
        //                 break;
        //             }
        //             case Type::Int64:
        //             {
        //                 *dst->as_uint8_pointer = src->as_int64;
        //                 break;       
        //             }
        //             case Type::Int8:
        //             {
        //                 *dst->as_uint8_pointer = src->as_int8;
        //                 break;
        //             }
        //             case Type::UInt16:
        //             {
        //                 *dst->as_uint8_pointer = src->as_uint16;
        //                 break;       
        //             }
        //             case Type::UInt32:
        //             {
        //                 *dst->as_uint8_pointer = src->as_uint32;
        //                 break;        
        //             }
        //             case Type::UInt64:
        //             {
        //                 *dst->as_uint8_pointer = src->as_uint64;
        //                 break;                            
        //             }
        //             case Type::UInt8:
        //             {
        //                 *dst->as_uint8_pointer = src->as_uint8;
        //                 break;                                    
        //             }


        //             case Type::DoublePointer:
        //             {
        //                 *dst->as_uint8_pointer = *src->as_double_pointer;
        //                 break;
        //             }
        //             case Type::Int16Pointer:
        //             {
        //                 *dst->as_uint8_pointer = *src->as_int16_pointer;
        //                 break;
        //             }
        //             case Type::Int32Pointer:
        //             {
        //                 *dst->as_uint8_pointer = *src->as_int32_pointer;
        //                 break;
        //             }
        //             case Type::Int64Pointer:
        //             {
        //                 *dst->as_uint8_pointer = *src->as_int64_pointer;
        //                 break;       
        //             }
        //             case Type::Int8Pointer:
        //             {
        //                 *dst->as_uint8_pointer = *src->as_int8_pointer;
        //                 break;
        //             }
        //             case Type::UInt16Pointer:
        //             {
        //                 *dst->as_uint8_pointer = *src->as_uint16_pointer;
        //                 break;       
        //             }
        //             case Type::UInt32Pointer:
        //             {
        //                 *dst->as_uint8_pointer = *src->as_uint32_pointer;
        //                 break;        
        //             }
        //             case Type::UInt64Pointer:
        //             {
        //                 *dst->as_uint8_pointer = *src->as_uint64_pointer;
        //                 break;                            
        //             }
        //             case Type::UInt8Pointer:
        //             {
        //                 *dst->as_uint8_pointer = *src->as_uint8_pointer;
        //                 break;                                    
        //             }
        //         }
        //         break;
        //     }

        //     case Type::Double:
        //     {
        //         switch(dstType)
        //         {
        //             case Type::Double:
        //             {                        
        //                 *dst->as_double_pointer = src->as_double;
        //                 break;
        //             }
        //             case Type::Int16:
        //             {
        //                 *dst->as_double_pointer = src->as_int16;
        //                 break;
        //             }
        //             case Type::Int32:
        //             {
        //                 *dst->as_double_pointer = src->as_int32;
        //                 break;
        //             }
        //             case Type::Int64:
        //             {
        //                 *dst->as_double_pointer = src->as_int64;
        //                 break;       
        //             }
        //             case Type::Int8:
        //             {
        //                 *dst->as_double_pointer = src->as_int8;
        //                 break;
        //             }
        //             case Type::UInt16:
        //             {
        //                 *dst->as_double_pointer = src->as_uint16;
        //                 break;       
        //             }
        //             case Type::UInt32:
        //             {
        //                 *dst->as_double_pointer = src->as_uint32;
        //                 break;        
        //             }
        //             case Type::UInt64:
        //             {
        //                 *dst->as_double_pointer = src->as_uint64;
        //                 break;                            
        //             }
        //             case Type::UInt8:
        //             {
        //                 *dst->as_double_pointer = src->as_uint8;
        //                 break;                                    
        //             }


        //             case Type::DoublePointer:
        //             {
        //                 *dst->as_double_pointer = src->as_double;
        //                 break;
        //             }
        //             case Type::Int16Pointer:
        //             {
        //                 *dst->as_double_pointer = *src->as_int16_pointer;
        //                 break;
        //             }
        //             case Type::Int32Pointer:
        //             {
        //                 *dst->as_double_pointer = *src->as_int32_pointer;
        //                 break;
        //             }
        //             case Type::Int64Pointer:
        //             {
        //                 *dst->as_double_pointer = *src->as_int64_pointer;
        //                 break;       
        //             }
        //             case Type::Int8Pointer:
        //             {
        //                 *dst->as_double_pointer = *src->as_int8_pointer;
        //                 break;
        //             }
        //             case Type::UInt16Pointer:
        //             {
        //                 *dst->as_double_pointer = *src->as_uint16_pointer;
        //                 break;       
        //             }
        //             case Type::UInt32Pointer:
        //             {
        //                 *dst->as_double_pointer = *src->as_uint32_pointer;
        //                 break;        
        //             }
        //             case Type::UInt64Pointer:
        //             {
        //                 *dst->as_double_pointer = *src->as_uint64_pointer;
        //                 break;                            
        //             }
        //             case Type::UInt8Pointer:
        //             {
        //                 *dst->as_double_pointer = *src->as_uint8_pointer;
        //                 break;                                    
        //             }
        //         }
        //         break;
        //     }
        // }
    }

    void ConversionUtility::ConvertInt8PointerInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertInt8PointerUInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertInt8PointerInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertInt8PointerUInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertInt8PointerInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertInt8PointerUInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertInt8PointerInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertInt8PointerUInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertInt8PointerDoublePointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertInt8PointerInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = rhs->as_int8;
    }

    void ConversionUtility::ConvertInt8PointerUInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = rhs->as_uint8;
    }

    void ConversionUtility::ConvertInt8PointerInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = rhs->as_int16;
    }

    void ConversionUtility::ConvertInt8PointerUInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = rhs->as_uint16;
    }

    void ConversionUtility::ConvertInt8PointerInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = rhs->as_int32;
    }

    void ConversionUtility::ConvertInt8PointerUInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = rhs->as_uint32;
    }

    void ConversionUtility::ConvertInt8PointerInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = rhs->as_int64;
    }

    void ConversionUtility::ConvertInt8PointerUInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = rhs->as_uint64;
    }

    void ConversionUtility::ConvertInt8PointerDouble(Object* lhs, Object* rhs)
    {
        *lhs->as_int8_pointer = rhs->as_double;
    }

    void ConversionUtility::ConvertUInt8PointerInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertUInt8PointerUInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertUInt8PointerInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertUInt8PointerUInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertUInt8PointerInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertUInt8PointerUInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertUInt8PointerInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertUInt8PointerUInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertUInt8PointerDoublePointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertUInt8PointerInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = rhs->as_int8;
    }

    void ConversionUtility::ConvertUInt8PointerUInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = rhs->as_uint8;
    }

    void ConversionUtility::ConvertUInt8PointerInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = rhs->as_int16;
    }

    void ConversionUtility::ConvertUInt8PointerUInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = rhs->as_uint16;
    }

    void ConversionUtility::ConvertUInt8PointerInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = rhs->as_int32;
    }

    void ConversionUtility::ConvertUInt8PointerUInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = rhs->as_uint32;
    }

    void ConversionUtility::ConvertUInt8PointerInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = rhs->as_int64;
    }

    void ConversionUtility::ConvertUInt8PointerUInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = rhs->as_uint64;
    }

    void ConversionUtility::ConvertUInt8PointerDouble(Object* lhs, Object* rhs)
    {
        *lhs->as_uint8_pointer = rhs->as_double;
    }

    void ConversionUtility::ConvertInt16PointerInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertInt16PointerUInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertInt16PointerInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertInt16PointerUInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertInt16PointerInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertInt16PointerUInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertInt16PointerInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertInt16PointerUInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertInt16PointerDoublePointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertInt16PointerInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = rhs->as_int8;
    }

    void ConversionUtility::ConvertInt16PointerUInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = rhs->as_uint8;
    }

    void ConversionUtility::ConvertInt16PointerInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = rhs->as_int16;
    }

    void ConversionUtility::ConvertInt16PointerUInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = rhs->as_uint16;
    }

    void ConversionUtility::ConvertInt16PointerInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = rhs->as_int32;
    }

    void ConversionUtility::ConvertInt16PointerUInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = rhs->as_uint32;
    }

    void ConversionUtility::ConvertInt16PointerInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = rhs->as_int64;
    }

    void ConversionUtility::ConvertInt16PointerUInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = rhs->as_uint64;
    }

    void ConversionUtility::ConvertInt16PointerDouble(Object* lhs, Object* rhs)
    {
        *lhs->as_int16_pointer = rhs->as_double;
    }

    void ConversionUtility::ConvertUInt16PointerInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertUInt16PointerUInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertUInt16PointerInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertUInt16PointerUInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertUInt16PointerInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertUInt16PointerUInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertUInt16PointerInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertUInt16PointerUInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertUInt16PointerDoublePointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertUInt16PointerInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = rhs->as_int8;
    }

    void ConversionUtility::ConvertUInt16PointerUInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = rhs->as_uint8;
    }

    void ConversionUtility::ConvertUInt16PointerInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = rhs->as_int16;
    }

    void ConversionUtility::ConvertUInt16PointerUInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = rhs->as_uint16;
    }

    void ConversionUtility::ConvertUInt16PointerInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = rhs->as_int32;
    }

    void ConversionUtility::ConvertUInt16PointerUInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = rhs->as_uint32;
    }

    void ConversionUtility::ConvertUInt16PointerInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = rhs->as_int64;
    }

    void ConversionUtility::ConvertUInt16PointerUInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = rhs->as_uint64;
    }

    void ConversionUtility::ConvertUInt16PointerDouble(Object* lhs, Object* rhs)
    {
        *lhs->as_uint16_pointer = rhs->as_double;
    }

    void ConversionUtility::ConvertInt32PointerInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertInt32PointerUInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertInt32PointerInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertInt32PointerUInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertInt32PointerInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertInt32PointerUInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertInt32PointerInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertInt32PointerUInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertInt32PointerDoublePointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertInt32PointerInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = rhs->as_int8;
    }

    void ConversionUtility::ConvertInt32PointerUInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = rhs->as_uint8;
    }

    void ConversionUtility::ConvertInt32PointerInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = rhs->as_int16;
    }

    void ConversionUtility::ConvertInt32PointerUInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = rhs->as_uint16;
    }

    void ConversionUtility::ConvertInt32PointerInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = rhs->as_int32;
    }

    void ConversionUtility::ConvertInt32PointerUInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = rhs->as_uint32;
    }

    void ConversionUtility::ConvertInt32PointerInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = rhs->as_int64;
    }

    void ConversionUtility::ConvertInt32PointerUInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = rhs->as_uint64;
    }

    void ConversionUtility::ConvertInt32PointerDouble(Object* lhs, Object* rhs)
    {
        *lhs->as_int32_pointer = rhs->as_double;
    }

    void ConversionUtility::ConvertUInt32PointerInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertUInt32PointerUInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertUInt32PointerInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertUInt32PointerUInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertUInt32PointerInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertUInt32PointerUInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertUInt32PointerInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertUInt32PointerUInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertUInt32PointerDoublePointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertUInt32PointerInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = rhs->as_int8;
    }

    void ConversionUtility::ConvertUInt32PointerUInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = rhs->as_uint8;
    }

    void ConversionUtility::ConvertUInt32PointerInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = rhs->as_int16;
    }

    void ConversionUtility::ConvertUInt32PointerUInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = rhs->as_uint16;
    }

    void ConversionUtility::ConvertUInt32PointerInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = rhs->as_int32;
    }

    void ConversionUtility::ConvertUInt32PointerUInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = rhs->as_uint32;
    }

    void ConversionUtility::ConvertUInt32PointerInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = rhs->as_int64;
    }

    void ConversionUtility::ConvertUInt32PointerUInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = rhs->as_uint64;
    }

    void ConversionUtility::ConvertUInt32PointerDouble(Object* lhs, Object* rhs)
    {
        *lhs->as_uint32_pointer = rhs->as_double;
    }

    void ConversionUtility::ConvertInt64PointerInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertInt64PointerUInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertInt64PointerInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertInt64PointerUInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertInt64PointerInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertInt64PointerUInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertInt64PointerInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertInt64PointerUInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertInt64PointerDoublePointer(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertInt64PointerInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = rhs->as_int8;
    }

    void ConversionUtility::ConvertInt64PointerUInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = rhs->as_uint8;
    }

    void ConversionUtility::ConvertInt64PointerInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = rhs->as_int16;
    }

    void ConversionUtility::ConvertInt64PointerUInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = rhs->as_uint16;
    }

    void ConversionUtility::ConvertInt64PointerInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = rhs->as_int32;
    }

    void ConversionUtility::ConvertInt64PointerUInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = rhs->as_uint32;
    }

    void ConversionUtility::ConvertInt64PointerInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = rhs->as_int64;
    }

    void ConversionUtility::ConvertInt64PointerUInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = rhs->as_uint64;
    }

    void ConversionUtility::ConvertInt64PointerDouble(Object* lhs, Object* rhs)
    {
        *lhs->as_int64_pointer = rhs->as_double;
    }

    void ConversionUtility::ConvertUInt64PointerInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertUInt64PointerUInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertUInt64PointerInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertUInt64PointerUInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertUInt64PointerInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertUInt64PointerUInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertUInt64PointerInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertUInt64PointerUInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertUInt64PointerDoublePointer(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertUInt64PointerInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = rhs->as_int8;
    }

    void ConversionUtility::ConvertUInt64PointerUInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = rhs->as_uint8;
    }

    void ConversionUtility::ConvertUInt64PointerInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = rhs->as_int16;
    }

    void ConversionUtility::ConvertUInt64PointerUInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = rhs->as_uint16;
    }

    void ConversionUtility::ConvertUInt64PointerInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = rhs->as_int32;
    }

    void ConversionUtility::ConvertUInt64PointerUInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = rhs->as_uint32;
    }

    void ConversionUtility::ConvertUInt64PointerInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = rhs->as_int64;
    }

    void ConversionUtility::ConvertUInt64PointerUInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = rhs->as_uint64;
    }

    void ConversionUtility::ConvertUInt64PointerDouble(Object* lhs, Object* rhs)
    {
        *lhs->as_uint64_pointer = rhs->as_double;
    }

    void ConversionUtility::ConvertDoublePointerInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertDoublePointerUInt8Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertDoublePointerInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertDoublePointerUInt16Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertDoublePointerInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertDoublePointerUInt32Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertDoublePointerInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertDoublePointerUInt64Pointer(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertDoublePointerDoublePointer(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertDoublePointerInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = rhs->as_int8;
    }

    void ConversionUtility::ConvertDoublePointerUInt8(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = rhs->as_uint8;
    }

    void ConversionUtility::ConvertDoublePointerInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = rhs->as_int16;
    }

    void ConversionUtility::ConvertDoublePointerUInt16(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = rhs->as_uint16;
    }

    void ConversionUtility::ConvertDoublePointerInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = rhs->as_int32;
    }

    void ConversionUtility::ConvertDoublePointerUInt32(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = rhs->as_uint32;
    }

    void ConversionUtility::ConvertDoublePointerInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = rhs->as_int64;
    }

    void ConversionUtility::ConvertDoublePointerUInt64(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = rhs->as_uint64;
    }

    void ConversionUtility::ConvertDoublePointerDouble(Object* lhs, Object* rhs)
    {
        *lhs->as_double_pointer = rhs->as_double;
    }

    void ConversionUtility::ConvertInt8Int8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertInt8UInt8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertInt8Int16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertInt8UInt16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertInt8Int32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertInt8UInt32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertInt8Int64Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertInt8UInt64Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertInt8DoublePointer(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertInt8Int8(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = rhs->as_int8;
    }

    void ConversionUtility::ConvertInt8UInt8(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = rhs->as_uint8;
    }

    void ConversionUtility::ConvertInt8Int16(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = rhs->as_int16;
    }

    void ConversionUtility::ConvertInt8UInt16(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = rhs->as_uint16;
    }

    void ConversionUtility::ConvertInt8Int32(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = rhs->as_int32;
    }

    void ConversionUtility::ConvertInt8UInt32(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = rhs->as_uint32;
    }

    void ConversionUtility::ConvertInt8Int64(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = rhs->as_int64;
    }

    void ConversionUtility::ConvertInt8UInt64(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = rhs->as_uint64;
    }

    void ConversionUtility::ConvertInt8Double(Object* lhs, Object* rhs)
    {
        lhs->as_int8 = rhs->as_double;
    }

    void ConversionUtility::ConvertUInt8Int8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertUInt8UInt8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertUInt8Int16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertUInt8UInt16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertUInt8Int32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertUInt8UInt32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertUInt8Int64Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertUInt8UInt64Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertUInt8DoublePointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertUInt8Int8(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = rhs->as_int8;
    }

    void ConversionUtility::ConvertUInt8UInt8(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = rhs->as_uint8;
    }

    void ConversionUtility::ConvertUInt8Int16(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = rhs->as_int16;
    }

    void ConversionUtility::ConvertUInt8UInt16(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = rhs->as_uint16;
    }

    void ConversionUtility::ConvertUInt8Int32(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = rhs->as_int32;
    }

    void ConversionUtility::ConvertUInt8UInt32(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = rhs->as_uint32;
    }

    void ConversionUtility::ConvertUInt8Int64(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = rhs->as_int64;
    }

    void ConversionUtility::ConvertUInt8UInt64(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = rhs->as_uint64;
    }

    void ConversionUtility::ConvertUInt8Double(Object* lhs, Object* rhs)
    {
        lhs->as_uint8 = rhs->as_double;
    }

    void ConversionUtility::ConvertInt16Int8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertInt16UInt8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertInt16Int16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertInt16UInt16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertInt16Int32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertInt16UInt32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertInt16Int64Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertInt16UInt64Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertInt16DoublePointer(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertInt16Int8(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = rhs->as_int8;
    }

    void ConversionUtility::ConvertInt16UInt8(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = rhs->as_uint8;
    }

    void ConversionUtility::ConvertInt16Int16(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = rhs->as_int16;
    }

    void ConversionUtility::ConvertInt16UInt16(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = rhs->as_uint16;
    }

    void ConversionUtility::ConvertInt16Int32(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = rhs->as_int32;
    }

    void ConversionUtility::ConvertInt16UInt32(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = rhs->as_uint32;
    }

    void ConversionUtility::ConvertInt16Int64(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = rhs->as_int64;
    }

    void ConversionUtility::ConvertInt16UInt64(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = rhs->as_uint64;
    }

    void ConversionUtility::ConvertInt16Double(Object* lhs, Object* rhs)
    {
        lhs->as_int16 = rhs->as_double;
    }

    void ConversionUtility::ConvertUInt16Int8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertUInt16UInt8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertUInt16Int16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertUInt16UInt16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertUInt16Int32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertUInt16UInt32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertUInt16Int64Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertUInt16UInt64Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertUInt16DoublePointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertUInt16Int8(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = rhs->as_int8;
    }

    void ConversionUtility::ConvertUInt16UInt8(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = rhs->as_uint8;
    }

    void ConversionUtility::ConvertUInt16Int16(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = rhs->as_int16;
    }

    void ConversionUtility::ConvertUInt16UInt16(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = rhs->as_uint16;
    }

    void ConversionUtility::ConvertUInt16Int32(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = rhs->as_int32;
    }

    void ConversionUtility::ConvertUInt16UInt32(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = rhs->as_uint32;
    }

    void ConversionUtility::ConvertUInt16Int64(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = rhs->as_int64;
    }

    void ConversionUtility::ConvertUInt16UInt64(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = rhs->as_uint64;
    }

    void ConversionUtility::ConvertUInt16Double(Object* lhs, Object* rhs)
    {
        lhs->as_uint16 = rhs->as_double;
    }

    void ConversionUtility::ConvertInt32Int8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertInt32UInt8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertInt32Int16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertInt32UInt16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertInt32Int32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertInt32UInt32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertInt32Int64Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertInt32UInt64Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertInt32DoublePointer(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertInt32Int8(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = rhs->as_int8;
    }

    void ConversionUtility::ConvertInt32UInt8(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = rhs->as_uint8;
    }

    void ConversionUtility::ConvertInt32Int16(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = rhs->as_int16;
    }

    void ConversionUtility::ConvertInt32UInt16(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = rhs->as_uint16;
    }

    void ConversionUtility::ConvertInt32Int32(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = rhs->as_int32;
    }

    void ConversionUtility::ConvertInt32UInt32(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = rhs->as_uint32;
    }

    void ConversionUtility::ConvertInt32Int64(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = rhs->as_int64;
    }

    void ConversionUtility::ConvertInt32UInt64(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = rhs->as_uint64;
    }

    void ConversionUtility::ConvertInt32Double(Object* lhs, Object* rhs)
    {
        lhs->as_int32 = rhs->as_double;
    }

    void ConversionUtility::ConvertUInt32Int8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertUInt32UInt8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertUInt32Int16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertUInt32UInt16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertUInt32Int32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertUInt32UInt32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertUInt32Int64Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertUInt32UInt64Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertUInt32DoublePointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertUInt32Int8(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = rhs->as_int8;
    }

    void ConversionUtility::ConvertUInt32UInt8(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = rhs->as_uint8;
    }

    void ConversionUtility::ConvertUInt32Int16(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = rhs->as_int16;
    }

    void ConversionUtility::ConvertUInt32UInt16(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = rhs->as_uint16;
    }

    void ConversionUtility::ConvertUInt32Int32(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = rhs->as_int32;
    }

    void ConversionUtility::ConvertUInt32UInt32(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = rhs->as_uint32;
    }

    void ConversionUtility::ConvertUInt32Int64(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = rhs->as_int64;
    }

    void ConversionUtility::ConvertUInt32UInt64(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = rhs->as_uint64;
    }

    void ConversionUtility::ConvertUInt32Double(Object* lhs, Object* rhs)
    {
        lhs->as_uint32 = rhs->as_double;
    }

    void ConversionUtility::ConvertInt64Int8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertInt64UInt8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertInt64Int16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertInt64UInt16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertInt64Int32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertInt64UInt32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertInt64Int64Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertInt64UInt64Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertInt64DoublePointer(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertInt64Int8(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = rhs->as_int8;
    }

    void ConversionUtility::ConvertInt64UInt8(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = rhs->as_uint8;
    }

    void ConversionUtility::ConvertInt64Int16(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = rhs->as_int16;
    }

    void ConversionUtility::ConvertInt64UInt16(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = rhs->as_uint16;
    }

    void ConversionUtility::ConvertInt64Int32(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = rhs->as_int32;
    }

    void ConversionUtility::ConvertInt64UInt32(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = rhs->as_uint32;
    }

    void ConversionUtility::ConvertInt64Int64(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = rhs->as_int64;
    }

    void ConversionUtility::ConvertInt64UInt64(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = rhs->as_uint64;
    }

    void ConversionUtility::ConvertInt64Double(Object* lhs, Object* rhs)
    {
        lhs->as_int64 = rhs->as_double;
    }

    void ConversionUtility::ConvertUInt64Int8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertUInt64UInt8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertUInt64Int16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertUInt64UInt16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertUInt64Int32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertUInt64UInt32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertUInt64Int64Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertUInt64UInt64Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertUInt64DoublePointer(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertUInt64Int8(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = rhs->as_int8;
    }

    void ConversionUtility::ConvertUInt64UInt8(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = rhs->as_uint8;
    }

    void ConversionUtility::ConvertUInt64Int16(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = rhs->as_int16;
    }

    void ConversionUtility::ConvertUInt64UInt16(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = rhs->as_uint16;
    }

    void ConversionUtility::ConvertUInt64Int32(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = rhs->as_int32;
    }

    void ConversionUtility::ConvertUInt64UInt32(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = rhs->as_uint32;
    }

    void ConversionUtility::ConvertUInt64Int64(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = rhs->as_int64;
    }

    void ConversionUtility::ConvertUInt64UInt64(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = rhs->as_uint64;
    }

    void ConversionUtility::ConvertUInt64Double(Object* lhs, Object* rhs)
    {
        lhs->as_uint64 = rhs->as_double;
    }

    void ConversionUtility::ConvertDoubleInt8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_double = *rhs->as_int8_pointer;
    }

    void ConversionUtility::ConvertDoubleUInt8Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_double = *rhs->as_uint8_pointer;
    }

    void ConversionUtility::ConvertDoubleInt16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_double = *rhs->as_int16_pointer;
    }

    void ConversionUtility::ConvertDoubleUInt16Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_double = *rhs->as_uint16_pointer;
    }

    void ConversionUtility::ConvertDoubleInt32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_double = *rhs->as_int32_pointer;
    }

    void ConversionUtility::ConvertDoubleUInt32Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_double = *rhs->as_uint32_pointer;
    }

    void ConversionUtility::ConvertDoubleInt64Pointer(Object* lhs, Object* rhs)
    {        
        lhs->as_double = *rhs->as_int64_pointer;
    }

    void ConversionUtility::ConvertDoubleUInt64Pointer(Object* lhs, Object* rhs)
    {
        lhs->as_double = *rhs->as_uint64_pointer;
    }

    void ConversionUtility::ConvertDoubleDoublePointer(Object* lhs, Object* rhs)
    {
        lhs->as_double = *rhs->as_double_pointer;
    }

    void ConversionUtility::ConvertDoubleInt8(Object* lhs, Object* rhs)
    {
        lhs->as_double = rhs->as_int8;
    }

    void ConversionUtility::ConvertDoubleUInt8(Object* lhs, Object* rhs)
    {
        lhs->as_double = rhs->as_uint8;
    }

    void ConversionUtility::ConvertDoubleInt16(Object* lhs, Object* rhs)
    {
        lhs->as_double = rhs->as_int16;
    }

    void ConversionUtility::ConvertDoubleUInt16(Object* lhs, Object* rhs)
    {
        lhs->as_double = rhs->as_uint16;
    }

    void ConversionUtility::ConvertDoubleInt32(Object* lhs, Object* rhs)
    {
        lhs->as_double = rhs->as_int32;
    }

    void ConversionUtility::ConvertDoubleUInt32(Object* lhs, Object* rhs)
    {
        lhs->as_double = rhs->as_uint32;
    }

    void ConversionUtility::ConvertDoubleInt64(Object* lhs, Object* rhs)
    {
        lhs->as_double = rhs->as_int64;
    }

    void ConversionUtility::ConvertDoubleUInt64(Object* lhs, Object* rhs)
    {
        lhs->as_double = rhs->as_uint64;
    }

    void ConversionUtility::ConvertDoubleDouble(Object* lhs, Object* rhs)
    {
        lhs->as_double = rhs->as_double;
    }    
}
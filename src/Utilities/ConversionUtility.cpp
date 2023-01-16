#include <ConversionUtility.hpp>
#include <cstring>

namespace VoltLang
{
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
            case Type::DoublePointer:
            {
                switch(dstType)
                {
                    case Type::Double:
                    {
                        *dst->as_double_pointer = src->as_double;
                        break;
                    }
                    case Type::Int16:
                    {
                        *dst->as_double_pointer = src->as_int16;
                        break;
                    }
                    case Type::Int32:
                    {
                        *dst->as_double_pointer = src->as_int32;
                        break;
                    }
                    case Type::Int64:
                    {
                        *dst->as_double_pointer = src->as_int64;
                        break;       
                    }
                    case Type::Int8:
                    {
                        *dst->as_double_pointer = src->as_int8;
                        break;
                    }
                    case Type::UInt16:
                    {
                        *dst->as_double_pointer = src->as_uint16;
                        break;       
                    }
                    case Type::UInt32:
                    {
                        *dst->as_double_pointer = src->as_uint32;
                        break;        
                    }
                    case Type::UInt64:
                    {
                        *dst->as_double_pointer = src->as_uint64;
                        break;                            
                    }
                    case Type::UInt8:
                    {
                        *dst->as_double_pointer = src->as_uint8;
                        break;                                    
                    }


                    case Type::DoublePointer:
                    {
                        *dst->as_double_pointer = *src->as_double_pointer;
                        break;
                    }
                    case Type::Int16Pointer:
                    {
                        *dst->as_double_pointer = *src->as_int16_pointer;
                        break;
                    }
                    case Type::Int32Pointer:
                    {
                        *dst->as_double_pointer = *src->as_int32_pointer;
                        break;
                    }
                    case Type::Int64Pointer:
                    {
                        *dst->as_double_pointer = *src->as_int64_pointer;
                        break;       
                    }
                    case Type::Int8Pointer:
                    {
                        *dst->as_double_pointer = *src->as_int8_pointer;
                        break;
                    }
                    case Type::UInt16Pointer:
                    {
                        *dst->as_double_pointer = *src->as_uint16_pointer;
                        break;       
                    }
                    case Type::UInt32Pointer:
                    {
                        *dst->as_double_pointer = *src->as_uint32_pointer;
                        break;        
                    }
                    case Type::UInt64Pointer:
                    {
                        *dst->as_double_pointer = *src->as_uint64_pointer;
                        break;                            
                    }
                    case Type::UInt8Pointer:
                    {
                        *dst->as_double_pointer = *src->as_uint8_pointer;
                        break;                                    
                    }
                }
                break;
            }
            case Type::Int16Pointer:
            {
                switch(dstType)
                {
                    case Type::Double:
                    {
                        *dst->as_int16_pointer = src->as_double;
                        break;
                    }
                    case Type::Int16:
                    {
                        *dst->as_int16_pointer = src->as_int16;
                        break;
                    }
                    case Type::Int32:
                    {
                        *dst->as_int16_pointer = src->as_int32;
                        break;
                    }
                    case Type::Int64:
                    {
                        *dst->as_int16_pointer = src->as_int64;
                        break;       
                    }
                    case Type::Int8:
                    {
                        *dst->as_int16_pointer = src->as_int8;
                        break;
                    }
                    case Type::UInt16:
                    {
                        *dst->as_int16_pointer = src->as_uint16;
                        break;       
                    }
                    case Type::UInt32:
                    {
                        *dst->as_int16_pointer = src->as_uint32;
                        break;        
                    }
                    case Type::UInt64:
                    {
                        *dst->as_int16_pointer = src->as_uint64;
                        break;                            
                    }
                    case Type::UInt8:
                    {
                        *dst->as_int16_pointer = src->as_uint8;
                        break;                                    
                    }


                    case Type::DoublePointer:
                    {
                        *dst->as_int16_pointer = *src->as_double_pointer;
                        break;
                    }
                    case Type::Int16Pointer:
                    {
                        *dst->as_int16_pointer = *src->as_int16_pointer;
                        break;
                    }
                    case Type::Int32Pointer:
                    {
                        *dst->as_int16_pointer = *src->as_int32_pointer;
                        break;
                    }
                    case Type::Int64Pointer:
                    {
                        *dst->as_int16_pointer = *src->as_int64_pointer;
                        break;       
                    }
                    case Type::Int8Pointer:
                    {
                        *dst->as_int16_pointer = *src->as_int8_pointer;
                        break;
                    }
                    case Type::UInt16Pointer:
                    {
                        *dst->as_int16_pointer = *src->as_uint16_pointer;
                        break;       
                    }
                    case Type::UInt32Pointer:
                    {
                        *dst->as_int16_pointer = *src->as_uint32_pointer;
                        break;        
                    }
                    case Type::UInt64Pointer:
                    {
                        *dst->as_int16_pointer = *src->as_uint64_pointer;
                        break;                            
                    }
                    case Type::UInt8Pointer:
                    {
                        *dst->as_int16_pointer = *src->as_uint8_pointer;
                        break;                                    
                    }
                }
                break;
            }
            case Type::Int32Pointer:
            {
                switch(dstType)
                {
                    case Type::Double:
                    {
                        *dst->as_int32_pointer = src->as_double;
                        break;
                    }
                    case Type::Int16:
                    {
                        *dst->as_int32_pointer = src->as_int16;
                        break;
                    }
                    case Type::Int32:
                    {
                        *dst->as_int32_pointer = src->as_int32;
                        break;
                    }
                    case Type::Int64:
                    {
                        *dst->as_int32_pointer = src->as_int64;
                        break;       
                    }
                    case Type::Int8:
                    {
                        *dst->as_int32_pointer = src->as_int8;
                        break;
                    }
                    case Type::UInt16:
                    {
                        *dst->as_int32_pointer = src->as_uint16;
                        break;       
                    }
                    case Type::UInt32:
                    {
                        *dst->as_int32_pointer = src->as_uint32;
                        break;        
                    }
                    case Type::UInt64:
                    {
                        *dst->as_int32_pointer = src->as_uint64;
                        break;                            
                    }
                    case Type::UInt8:
                    {
                        *dst->as_int32_pointer = src->as_uint8;
                        break;                                    
                    }


                    case Type::DoublePointer:
                    {
                        *dst->as_int32_pointer = *src->as_double_pointer;
                        break;
                    }
                    case Type::Int16Pointer:
                    {
                        *dst->as_int32_pointer = *src->as_int16_pointer;
                        break;
                    }
                    case Type::Int32Pointer:
                    {
                        *dst->as_int32_pointer = *src->as_int32_pointer;
                        break;
                    }
                    case Type::Int64Pointer:
                    {
                        *dst->as_int32_pointer = *src->as_int64_pointer;
                        break;       
                    }
                    case Type::Int8Pointer:
                    {
                        *dst->as_int32_pointer = *src->as_int8_pointer;
                        break;
                    }
                    case Type::UInt16Pointer:
                    {
                        *dst->as_int32_pointer = *src->as_uint16_pointer;
                        break;       
                    }
                    case Type::UInt32Pointer:
                    {
                        *dst->as_int32_pointer = *src->as_uint32_pointer;
                        break;        
                    }
                    case Type::UInt64Pointer:
                    {
                        *dst->as_int32_pointer = *src->as_uint64_pointer;
                        break;                            
                    }
                    case Type::UInt8Pointer:
                    {
                        *dst->as_int32_pointer = *src->as_uint8_pointer;
                        break;                                    
                    }
                }
                break;
            }                                                                           
            case Type::Int64Pointer:
            {
                switch(dstType)
                {
                    case Type::Double:
                    {
                        *dst->as_int64_pointer = src->as_double;
                        break;
                    }
                    case Type::Int16:
                    {
                        *dst->as_int64_pointer = src->as_int16;
                        break;
                    }
                    case Type::Int32:
                    {
                        *dst->as_int64_pointer = src->as_int32;
                        break;
                    }
                    case Type::Int64:
                    {
                        *dst->as_int64_pointer = src->as_int64;
                        break;       
                    }
                    case Type::Int8:
                    {
                        *dst->as_int64_pointer = src->as_int8;
                        break;
                    }
                    case Type::UInt16:
                    {
                        *dst->as_int64_pointer = src->as_uint16;
                        break;       
                    }
                    case Type::UInt32:
                    {
                        *dst->as_int64_pointer = src->as_uint32;
                        break;        
                    }
                    case Type::UInt64:
                    {
                        *dst->as_int64_pointer = src->as_uint64;
                        break;                            
                    }
                    case Type::UInt8:
                    {
                        *dst->as_int64_pointer = src->as_uint8;
                        break;                                    
                    }


                    case Type::DoublePointer:
                    {
                        *dst->as_int64_pointer = *src->as_double_pointer;
                        break;
                    }
                    case Type::Int16Pointer:
                    {
                        *dst->as_int64_pointer = *src->as_int16_pointer;
                        break;
                    }
                    case Type::Int32Pointer:
                    {
                        *dst->as_int64_pointer = *src->as_int32_pointer;
                        break;
                    }
                    case Type::Int64Pointer:
                    {
                        *dst->as_int64_pointer = *src->as_int64_pointer;
                        break;       
                    }
                    case Type::Int8Pointer:
                    {
                        *dst->as_int64_pointer = *src->as_int8_pointer;
                        break;
                    }
                    case Type::UInt16Pointer:
                    {
                        *dst->as_int64_pointer = *src->as_uint16_pointer;
                        break;       
                    }
                    case Type::UInt32Pointer:
                    {
                        *dst->as_int64_pointer = *src->as_uint32_pointer;
                        break;        
                    }
                    case Type::UInt64Pointer:
                    {
                        *dst->as_int64_pointer = *src->as_uint64_pointer;
                        break;                            
                    }
                    case Type::UInt8Pointer:
                    {
                        *dst->as_int64_pointer = *src->as_uint8_pointer;
                        break;                                    
                    }
                }
                break;
            }
            case Type::Int8Pointer:
            {
                switch(dstType)
                {
                    case Type::Double:
                    {
                        *dst->as_int8_pointer = src->as_double;
                        break;
                    }
                    case Type::Int16:
                    {
                        *dst->as_int8_pointer = src->as_int16;
                        break;
                    }
                    case Type::Int32:
                    {
                        *dst->as_int8_pointer = src->as_int32;
                        break;
                    }
                    case Type::Int64:
                    {
                        *dst->as_int8_pointer = src->as_int64;
                        break;       
                    }
                    case Type::Int8:
                    {
                        *dst->as_int8_pointer = src->as_int8;
                        break;
                    }
                    case Type::UInt16:
                    {
                        *dst->as_int8_pointer = src->as_uint16;
                        break;       
                    }
                    case Type::UInt32:
                    {
                        *dst->as_int8_pointer = src->as_uint32;
                        break;        
                    }
                    case Type::UInt64:
                    {
                        *dst->as_int8_pointer = src->as_uint64;
                        break;                            
                    }
                    case Type::UInt8:
                    {
                        *dst->as_int8_pointer = src->as_uint8;
                        break;                                    
                    }



                    case Type::DoublePointer:
                    {
                        *dst->as_int8_pointer = *src->as_double_pointer;
                        break;
                    }
                    case Type::Int16Pointer:
                    {
                        *dst->as_int8_pointer = *src->as_int16_pointer;
                        break;
                    }
                    case Type::Int32Pointer:
                    {
                        *dst->as_int8_pointer = *src->as_int32_pointer;
                        break;
                    }
                    case Type::Int64Pointer:
                    {
                        *dst->as_int8_pointer = *src->as_int64_pointer;
                        break;       
                    }
                    case Type::Int8Pointer:
                    {
                        *dst->as_int8_pointer = *src->as_int8_pointer;
                        break;
                    }
                    case Type::UInt16Pointer:
                    {
                        *dst->as_int8_pointer = *src->as_uint16_pointer;
                        break;       
                    }
                    case Type::UInt32Pointer:
                    {
                        *dst->as_int8_pointer = *src->as_uint32_pointer;
                        break;        
                    }
                    case Type::UInt64Pointer:
                    {
                        *dst->as_int8_pointer = *src->as_uint64_pointer;
                        break;                            
                    }
                    case Type::UInt8Pointer:
                    {
                        *dst->as_int8_pointer = *src->as_uint8_pointer;
                        break;                                    
                    }
                }
                break;
            }
            case Type::UInt16Pointer:
            {
                switch(dstType)
                {
                    case Type::Double:
                    {
                        *dst->as_uint16_pointer = src->as_double;
                        break;
                    }
                    case Type::Int16:
                    {
                        *dst->as_uint16_pointer = src->as_int16;
                        break;
                    }
                    case Type::Int32:
                    {
                        *dst->as_uint16_pointer = src->as_int32;
                        break;
                    }
                    case Type::Int64:
                    {
                        *dst->as_uint16_pointer = src->as_int64;
                        break;       
                    }
                    case Type::Int8:
                    {
                        *dst->as_uint16_pointer = src->as_int8;
                        break;
                    }
                    case Type::UInt16:
                    {
                        *dst->as_uint16_pointer = src->as_uint16;
                        break;       
                    }
                    case Type::UInt32:
                    {
                        *dst->as_uint16_pointer = src->as_uint32;
                        break;        
                    }
                    case Type::UInt64:
                    {
                        *dst->as_uint16_pointer = src->as_uint64;
                        break;                            
                    }
                    case Type::UInt8:
                    {
                        *dst->as_uint16_pointer = src->as_uint8;
                        break;                                    
                    }


                    case Type::DoublePointer:
                    {
                        *dst->as_uint16_pointer = *src->as_double_pointer;
                        break;
                    }
                    case Type::Int16Pointer:
                    {
                        *dst->as_uint16_pointer = *src->as_int16_pointer;
                        break;
                    }
                    case Type::Int32Pointer:
                    {
                        *dst->as_uint16_pointer = *src->as_int32_pointer;
                        break;
                    }
                    case Type::Int64Pointer:
                    {
                        *dst->as_uint16_pointer = *src->as_int64_pointer;
                        break;       
                    }
                    case Type::Int8Pointer:
                    {
                        *dst->as_uint16_pointer = *src->as_int8_pointer;
                        break;
                    }
                    case Type::UInt16Pointer:
                    {
                        *dst->as_uint16_pointer = *src->as_uint16_pointer;
                        break;       
                    }
                    case Type::UInt32Pointer:
                    {
                        *dst->as_uint16_pointer = *src->as_uint32_pointer;
                        break;        
                    }
                    case Type::UInt64Pointer:
                    {
                        *dst->as_uint16_pointer = *src->as_uint64_pointer;
                        break;                            
                    }
                    case Type::UInt8Pointer:
                    {
                        *dst->as_uint16_pointer = *src->as_uint8_pointer;
                        break;                                    
                    }
                }
                break;
            }               
            case Type::UInt32Pointer:
            {
                switch(dstType)
                {
                    case Type::Double:
                    {
                        *dst->as_uint32_pointer = src->as_double;
                        break;
                    }
                    case Type::Int16:
                    {
                        *dst->as_uint32_pointer = src->as_int16;
                        break;
                    }
                    case Type::Int32:
                    {
                        *dst->as_uint32_pointer = src->as_int32;
                        break;
                    }
                    case Type::Int64:
                    {
                        *dst->as_uint32_pointer = src->as_int64;
                        break;       
                    }
                    case Type::Int8:
                    {
                        *dst->as_uint32_pointer = src->as_int8;
                        break;
                    }
                    case Type::UInt16:
                    {
                        *dst->as_uint32_pointer = src->as_uint16;
                        break;       
                    }
                    case Type::UInt32:
                    {
                        *dst->as_uint32_pointer = src->as_uint32;
                        break;        
                    }
                    case Type::UInt64:
                    {
                        *dst->as_uint32_pointer = src->as_uint64;
                        break;                            
                    }
                    case Type::UInt8:
                    {
                        *dst->as_uint32_pointer = src->as_uint8;
                        break;                                    
                    }


                    case Type::DoublePointer:
                    {
                        *dst->as_uint32_pointer = *src->as_double_pointer;
                        break;
                    }
                    case Type::Int16Pointer:
                    {
                        *dst->as_uint32_pointer = *src->as_int16_pointer;
                        break;
                    }
                    case Type::Int32Pointer:
                    {
                        *dst->as_uint32_pointer = *src->as_int32_pointer;
                        break;
                    }
                    case Type::Int64Pointer:
                    {
                        *dst->as_uint32_pointer = *src->as_int64_pointer;
                        break;       
                    }
                    case Type::Int8Pointer:
                    {
                        *src->as_uint32_pointer = *src->as_int8_pointer;
                        break;
                    }
                    case Type::UInt16Pointer:
                    {
                        *dst->as_uint32_pointer = *src->as_uint16_pointer;
                        break;       
                    }
                    case Type::UInt32Pointer:
                    {
                        *dst->as_uint32_pointer = *src->as_uint32_pointer;
                        break;        
                    }
                    case Type::UInt64Pointer:
                    {
                        *dst->as_uint32_pointer = *src->as_uint64_pointer;
                        break;                            
                    }
                    case Type::UInt8Pointer:
                    {
                        *dst->as_uint32_pointer = *src->as_uint8_pointer;
                        break;                                    
                    }
                }
                break;
            }               
            case Type::UInt64Pointer:
            {
                switch(dstType)
                {
                    case Type::Double:
                    {
                        *dst->as_uint64_pointer = src->as_double;
                        break;
                    }
                    case Type::Int16:
                    {
                        *dst->as_uint64_pointer = src->as_int16;
                        break;
                    }
                    case Type::Int32:
                    {
                        *dst->as_uint64_pointer = src->as_int32;
                        break;
                    }
                    case Type::Int64:
                    {
                        *dst->as_uint64_pointer = src->as_int64;
                        break;       
                    }
                    case Type::Int8:
                    {
                        *dst->as_uint64_pointer = src->as_int8;
                        break;
                    }
                    case Type::UInt16:
                    {
                        *dst->as_uint64_pointer = src->as_uint16;
                        break;       
                    }
                    case Type::UInt32:
                    {
                        *dst->as_uint64_pointer = src->as_uint32;
                        break;        
                    }
                    case Type::UInt64:
                    {
                        *dst->as_uint64_pointer = src->as_uint64;
                        break;                            
                    }
                    case Type::UInt8:
                    {
                        *dst->as_uint64_pointer = src->as_uint8;
                        break;                                    
                    }


                    case Type::DoublePointer:
                    {
                        *dst->as_uint64_pointer = *src->as_double_pointer;
                        break;
                    }
                    case Type::Int16Pointer:
                    {
                        *dst->as_uint64_pointer = *src->as_int16_pointer;
                        break;
                    }
                    case Type::Int32Pointer:
                    {
                        *dst->as_uint64_pointer = *src->as_int32_pointer;
                        break;
                    }
                    case Type::Int64Pointer:
                    {
                        *dst->as_uint64_pointer = *src->as_int64_pointer;
                        break;       
                    }
                    case Type::Int8Pointer:
                    {
                        *dst->as_uint64_pointer = *src->as_int8_pointer;
                        break;
                    }
                    case Type::UInt16Pointer:
                    {
                        *dst->as_uint64_pointer = *src->as_uint16_pointer;
                        break;       
                    }
                    case Type::UInt32Pointer:
                    {
                        *dst->as_uint64_pointer = *src->as_uint32_pointer;
                        break;        
                    }
                    case Type::UInt64Pointer:
                    {
                        *dst->as_uint64_pointer = *src->as_uint64_pointer;
                        break;                            
                    }
                    case Type::UInt8Pointer:
                    {
                        *dst->as_uint64_pointer = *src->as_uint8_pointer;
                        break;                                    
                    }
                }
                break;
            }               
            case Type::UInt8Pointer:
            {
                switch(dstType)
                {
                    case Type::Double:
                    {
                        *dst->as_uint8_pointer = src->as_double;
                        break;
                    }
                    case Type::Int16:
                    {
                        *dst->as_uint8_pointer = src->as_int16;
                        break;
                    }
                    case Type::Int32:
                    {
                        *dst->as_uint8_pointer = src->as_int32;
                        break;
                    }
                    case Type::Int64:
                    {
                        *dst->as_uint8_pointer = src->as_int64;
                        break;       
                    }
                    case Type::Int8:
                    {
                        *dst->as_uint8_pointer = src->as_int8;
                        break;
                    }
                    case Type::UInt16:
                    {
                        *dst->as_uint8_pointer = src->as_uint16;
                        break;       
                    }
                    case Type::UInt32:
                    {
                        *dst->as_uint8_pointer = src->as_uint32;
                        break;        
                    }
                    case Type::UInt64:
                    {
                        *dst->as_uint8_pointer = src->as_uint64;
                        break;                            
                    }
                    case Type::UInt8:
                    {
                        *dst->as_uint8_pointer = src->as_uint8;
                        break;                                    
                    }


                    case Type::DoublePointer:
                    {
                        *dst->as_uint8_pointer = *src->as_double_pointer;
                        break;
                    }
                    case Type::Int16Pointer:
                    {
                        *dst->as_uint8_pointer = *src->as_int16_pointer;
                        break;
                    }
                    case Type::Int32Pointer:
                    {
                        *dst->as_uint8_pointer = *src->as_int32_pointer;
                        break;
                    }
                    case Type::Int64Pointer:
                    {
                        *dst->as_uint8_pointer = *src->as_int64_pointer;
                        break;       
                    }
                    case Type::Int8Pointer:
                    {
                        *dst->as_uint8_pointer = *src->as_int8_pointer;
                        break;
                    }
                    case Type::UInt16Pointer:
                    {
                        *dst->as_uint8_pointer = *src->as_uint16_pointer;
                        break;       
                    }
                    case Type::UInt32Pointer:
                    {
                        *dst->as_uint8_pointer = *src->as_uint32_pointer;
                        break;        
                    }
                    case Type::UInt64Pointer:
                    {
                        *dst->as_uint8_pointer = *src->as_uint64_pointer;
                        break;                            
                    }
                    case Type::UInt8Pointer:
                    {
                        *dst->as_uint8_pointer = *src->as_uint8_pointer;
                        break;                                    
                    }
                }
                break;
            }
        }
    }
}
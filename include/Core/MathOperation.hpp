#ifndef STACKVM_MATHOPERATION_HPP
#define STACKVM_MATHOPERATION_HPP

#include <Specification.hpp>
#include <iostream>

namespace VoltLang
{
    //WARNING: This class contains generated code, so it's not recommend to casually start changing things
    typedef int64_t (*CmpCallbackPtr)(byte* lhs, byte* rhs);
    typedef int64_t (*AddCallbackPtr)(byte* lhs, byte* rhs);
    typedef int64_t (*SubCallbackPtr)(byte* lhs, byte* rhs);
    typedef int64_t (*MulCallbackPtr)(byte* lhs, byte* rhs);
    typedef int64_t (*DivCallbackPtr)(byte* lhs, byte* rhs);

    class MathOperation
    {
    public:
        static int64_t Compare(byte* lhs, byte* rhs, Type lhsDataType, Type rhsDataType);
        static int64_t Add(byte* lhs, byte* rhs, Type lhsDataType, Type rhsDataType);
        static int64_t Subtract(byte* lhs, byte* rhs, Type lhsDataType, Type rhsDataType);
        static int64_t Multiply(byte* lhs, byte* rhs, Type lhsDataType, Type rhsDataType);
        static int64_t Divide(byte* lhs, byte* rhs, Type lhsDataType, Type rhsDataType);
    private:
        static CmpCallbackPtr cmpFunctions[][10];
        static AddCallbackPtr addFunctions[][10];
        static SubCallbackPtr subFunctions[][10];
        static MulCallbackPtr mulFunctions[][10];
        static DivCallbackPtr divFunctions[][10];

        template<typename T1, typename T2>
        static int64_t CompareTypeWithType(T1 lhs, T2 rhs)
        {
            if(lhs > rhs)
            {
                return 1;
            }
            else if(lhs < rhs)
            {
                return -1;
            }
            else
            {
                return 0;
            }
        }

        //Compare--------------------------
        //---------------------------------
        //---------------------------------
        //---------------------------------

        static int64_t CompareUInt8UInt8(byte* lhs, byte* rhs);
        static int64_t CompareUInt8Int8(byte* lhs, byte* rhs);
        static int64_t CompareUInt8UInt16(byte* lhs, byte* rhs);
        static int64_t CompareUInt8Int16(byte* lhs, byte* rhs);
        static int64_t CompareUInt8UInt32(byte* lhs, byte* rhs);
        static int64_t CompareUInt8Int32(byte* lhs, byte* rhs);
        static int64_t CompareUInt8UInt64(byte* lhs, byte* rhs);
        static int64_t CompareUInt8Int64(byte* lhs, byte* rhs);
        static int64_t CompareUInt8Single(byte* lhs, byte* rhs);
        static int64_t CompareUInt8Double(byte* lhs, byte* rhs);
        static int64_t CompareInt8UInt8(byte* lhs, byte* rhs);
        static int64_t CompareInt8Int8(byte* lhs, byte* rhs);
        static int64_t CompareInt8UInt16(byte* lhs, byte* rhs);
        static int64_t CompareInt8Int16(byte* lhs, byte* rhs);
        static int64_t CompareInt8UInt32(byte* lhs, byte* rhs);
        static int64_t CompareInt8Int32(byte* lhs, byte* rhs);
        static int64_t CompareInt8UInt64(byte* lhs, byte* rhs);
        static int64_t CompareInt8Int64(byte* lhs, byte* rhs);
        static int64_t CompareInt8Single(byte* lhs, byte* rhs);
        static int64_t CompareInt8Double(byte* lhs, byte* rhs);
        static int64_t CompareUInt16UInt8(byte* lhs, byte* rhs);
        static int64_t CompareUInt16Int8(byte* lhs, byte* rhs);
        static int64_t CompareUInt16UInt16(byte* lhs, byte* rhs);
        static int64_t CompareUInt16Int16(byte* lhs, byte* rhs);
        static int64_t CompareUInt16UInt32(byte* lhs, byte* rhs);
        static int64_t CompareUInt16Int32(byte* lhs, byte* rhs);
        static int64_t CompareUInt16UInt64(byte* lhs, byte* rhs);
        static int64_t CompareUInt16Int64(byte* lhs, byte* rhs);
        static int64_t CompareUInt16Single(byte* lhs, byte* rhs);
        static int64_t CompareUInt16Double(byte* lhs, byte* rhs);
        static int64_t CompareInt16UInt8(byte* lhs, byte* rhs);
        static int64_t CompareInt16Int8(byte* lhs, byte* rhs);
        static int64_t CompareInt16UInt16(byte* lhs, byte* rhs);
        static int64_t CompareInt16Int16(byte* lhs, byte* rhs);
        static int64_t CompareInt16UInt32(byte* lhs, byte* rhs);
        static int64_t CompareInt16Int32(byte* lhs, byte* rhs);
        static int64_t CompareInt16UInt64(byte* lhs, byte* rhs);
        static int64_t CompareInt16Int64(byte* lhs, byte* rhs);
        static int64_t CompareInt16Single(byte* lhs, byte* rhs);
        static int64_t CompareInt16Double(byte* lhs, byte* rhs);
        static int64_t CompareUInt32UInt8(byte* lhs, byte* rhs);
        static int64_t CompareUInt32Int8(byte* lhs, byte* rhs);
        static int64_t CompareUInt32UInt16(byte* lhs, byte* rhs);
        static int64_t CompareUInt32Int16(byte* lhs, byte* rhs);
        static int64_t CompareUInt32UInt32(byte* lhs, byte* rhs);
        static int64_t CompareUInt32Int32(byte* lhs, byte* rhs);
        static int64_t CompareUInt32UInt64(byte* lhs, byte* rhs);
        static int64_t CompareUInt32Int64(byte* lhs, byte* rhs);
        static int64_t CompareUInt32Single(byte* lhs, byte* rhs);
        static int64_t CompareUInt32Double(byte* lhs, byte* rhs);
        static int64_t CompareInt32UInt8(byte* lhs, byte* rhs);
        static int64_t CompareInt32Int8(byte* lhs, byte* rhs);
        static int64_t CompareInt32UInt16(byte* lhs, byte* rhs);
        static int64_t CompareInt32Int16(byte* lhs, byte* rhs);
        static int64_t CompareInt32UInt32(byte* lhs, byte* rhs);
        static int64_t CompareInt32Int32(byte* lhs, byte* rhs);
        static int64_t CompareInt32UInt64(byte* lhs, byte* rhs);
        static int64_t CompareInt32Int64(byte* lhs, byte* rhs);
        static int64_t CompareInt32Single(byte* lhs, byte* rhs);
        static int64_t CompareInt32Double(byte* lhs, byte* rhs);
        static int64_t CompareUInt64UInt8(byte* lhs, byte* rhs);
        static int64_t CompareUInt64Int8(byte* lhs, byte* rhs);
        static int64_t CompareUInt64UInt16(byte* lhs, byte* rhs);
        static int64_t CompareUInt64Int16(byte* lhs, byte* rhs);
        static int64_t CompareUInt64UInt32(byte* lhs, byte* rhs);
        static int64_t CompareUInt64Int32(byte* lhs, byte* rhs);
        static int64_t CompareUInt64UInt64(byte* lhs, byte* rhs);
        static int64_t CompareUInt64Int64(byte* lhs, byte* rhs);
        static int64_t CompareUInt64Single(byte* lhs, byte* rhs);
        static int64_t CompareUInt64Double(byte* lhs, byte* rhs);
        static int64_t CompareInt64UInt8(byte* lhs, byte* rhs);
        static int64_t CompareInt64Int8(byte* lhs, byte* rhs);
        static int64_t CompareInt64UInt16(byte* lhs, byte* rhs);
        static int64_t CompareInt64Int16(byte* lhs, byte* rhs);
        static int64_t CompareInt64UInt32(byte* lhs, byte* rhs);
        static int64_t CompareInt64Int32(byte* lhs, byte* rhs);
        static int64_t CompareInt64UInt64(byte* lhs, byte* rhs);
        static int64_t CompareInt64Int64(byte* lhs, byte* rhs);
        static int64_t CompareInt64Single(byte* lhs, byte* rhs);
        static int64_t CompareInt64Double(byte* lhs, byte* rhs);
        static int64_t CompareSingleUInt8(byte* lhs, byte* rhs);
        static int64_t CompareSingleInt8(byte* lhs, byte* rhs);
        static int64_t CompareSingleUInt16(byte* lhs, byte* rhs);
        static int64_t CompareSingleInt16(byte* lhs, byte* rhs);
        static int64_t CompareSingleUInt32(byte* lhs, byte* rhs);
        static int64_t CompareSingleInt32(byte* lhs, byte* rhs);
        static int64_t CompareSingleUInt64(byte* lhs, byte* rhs);
        static int64_t CompareSingleInt64(byte* lhs, byte* rhs);
        static int64_t CompareSingleSingle(byte* lhs, byte* rhs);
        static int64_t CompareSingleDouble(byte* lhs, byte* rhs);
        static int64_t CompareDoubleUInt8(byte* lhs, byte* rhs);
        static int64_t CompareDoubleInt8(byte* lhs, byte* rhs);
        static int64_t CompareDoubleUInt16(byte* lhs, byte* rhs);
        static int64_t CompareDoubleInt16(byte* lhs, byte* rhs);
        static int64_t CompareDoubleUInt32(byte* lhs, byte* rhs);
        static int64_t CompareDoubleInt32(byte* lhs, byte* rhs);
        static int64_t CompareDoubleUInt64(byte* lhs, byte* rhs);
        static int64_t CompareDoubleInt64(byte* lhs, byte* rhs);
        static int64_t CompareDoubleSingle(byte* lhs, byte* rhs);
        static int64_t CompareDoubleDouble(byte* lhs, byte* rhs);

        //Add------------------------------
        //---------------------------------
        //---------------------------------
        //---------------------------------

        static int64_t AddUInt8UInt8(byte* lhs, byte* rhs);
        static int64_t AddUInt8Int8(byte* lhs, byte* rhs);
        static int64_t AddUInt8UInt16(byte* lhs, byte* rhs);
        static int64_t AddUInt8Int16(byte* lhs, byte* rhs);
        static int64_t AddUInt8UInt32(byte* lhs, byte* rhs);
        static int64_t AddUInt8Int32(byte* lhs, byte* rhs);
        static int64_t AddUInt8UInt64(byte* lhs, byte* rhs);
        static int64_t AddUInt8Int64(byte* lhs, byte* rhs);
        static int64_t AddUInt8Single(byte* lhs, byte* rhs);
        static int64_t AddUInt8Double(byte* lhs, byte* rhs);
        static int64_t AddInt8UInt8(byte* lhs, byte* rhs);
        static int64_t AddInt8Int8(byte* lhs, byte* rhs);
        static int64_t AddInt8UInt16(byte* lhs, byte* rhs);
        static int64_t AddInt8Int16(byte* lhs, byte* rhs);
        static int64_t AddInt8UInt32(byte* lhs, byte* rhs);
        static int64_t AddInt8Int32(byte* lhs, byte* rhs);
        static int64_t AddInt8UInt64(byte* lhs, byte* rhs);
        static int64_t AddInt8Int64(byte* lhs, byte* rhs);
        static int64_t AddInt8Single(byte* lhs, byte* rhs);
        static int64_t AddInt8Double(byte* lhs, byte* rhs);
        static int64_t AddUInt16UInt8(byte* lhs, byte* rhs);
        static int64_t AddUInt16Int8(byte* lhs, byte* rhs);
        static int64_t AddUInt16UInt16(byte* lhs, byte* rhs);
        static int64_t AddUInt16Int16(byte* lhs, byte* rhs);
        static int64_t AddUInt16UInt32(byte* lhs, byte* rhs);
        static int64_t AddUInt16Int32(byte* lhs, byte* rhs);
        static int64_t AddUInt16UInt64(byte* lhs, byte* rhs);
        static int64_t AddUInt16Int64(byte* lhs, byte* rhs);
        static int64_t AddUInt16Single(byte* lhs, byte* rhs);
        static int64_t AddUInt16Double(byte* lhs, byte* rhs);
        static int64_t AddInt16UInt8(byte* lhs, byte* rhs);
        static int64_t AddInt16Int8(byte* lhs, byte* rhs);
        static int64_t AddInt16UInt16(byte* lhs, byte* rhs);
        static int64_t AddInt16Int16(byte* lhs, byte* rhs);
        static int64_t AddInt16UInt32(byte* lhs, byte* rhs);
        static int64_t AddInt16Int32(byte* lhs, byte* rhs);
        static int64_t AddInt16UInt64(byte* lhs, byte* rhs);
        static int64_t AddInt16Int64(byte* lhs, byte* rhs);
        static int64_t AddInt16Single(byte* lhs, byte* rhs);
        static int64_t AddInt16Double(byte* lhs, byte* rhs);
        static int64_t AddUInt32UInt8(byte* lhs, byte* rhs);
        static int64_t AddUInt32Int8(byte* lhs, byte* rhs);
        static int64_t AddUInt32UInt16(byte* lhs, byte* rhs);
        static int64_t AddUInt32Int16(byte* lhs, byte* rhs);
        static int64_t AddUInt32UInt32(byte* lhs, byte* rhs);
        static int64_t AddUInt32Int32(byte* lhs, byte* rhs);
        static int64_t AddUInt32UInt64(byte* lhs, byte* rhs);
        static int64_t AddUInt32Int64(byte* lhs, byte* rhs);
        static int64_t AddUInt32Single(byte* lhs, byte* rhs);
        static int64_t AddUInt32Double(byte* lhs, byte* rhs);
        static int64_t AddInt32UInt8(byte* lhs, byte* rhs);
        static int64_t AddInt32Int8(byte* lhs, byte* rhs);
        static int64_t AddInt32UInt16(byte* lhs, byte* rhs);
        static int64_t AddInt32Int16(byte* lhs, byte* rhs);
        static int64_t AddInt32UInt32(byte* lhs, byte* rhs);
        static int64_t AddInt32Int32(byte* lhs, byte* rhs);
        static int64_t AddInt32UInt64(byte* lhs, byte* rhs);
        static int64_t AddInt32Int64(byte* lhs, byte* rhs);
        static int64_t AddInt32Single(byte* lhs, byte* rhs);
        static int64_t AddInt32Double(byte* lhs, byte* rhs);
        static int64_t AddUInt64UInt8(byte* lhs, byte* rhs);
        static int64_t AddUInt64Int8(byte* lhs, byte* rhs);
        static int64_t AddUInt64UInt16(byte* lhs, byte* rhs);
        static int64_t AddUInt64Int16(byte* lhs, byte* rhs);
        static int64_t AddUInt64UInt32(byte* lhs, byte* rhs);
        static int64_t AddUInt64Int32(byte* lhs, byte* rhs);
        static int64_t AddUInt64UInt64(byte* lhs, byte* rhs);
        static int64_t AddUInt64Int64(byte* lhs, byte* rhs);
        static int64_t AddUInt64Single(byte* lhs, byte* rhs);
        static int64_t AddUInt64Double(byte* lhs, byte* rhs);
        static int64_t AddInt64UInt8(byte* lhs, byte* rhs);
        static int64_t AddInt64Int8(byte* lhs, byte* rhs);
        static int64_t AddInt64UInt16(byte* lhs, byte* rhs);
        static int64_t AddInt64Int16(byte* lhs, byte* rhs);
        static int64_t AddInt64UInt32(byte* lhs, byte* rhs);
        static int64_t AddInt64Int32(byte* lhs, byte* rhs);
        static int64_t AddInt64UInt64(byte* lhs, byte* rhs);
        static int64_t AddInt64Int64(byte* lhs, byte* rhs);
        static int64_t AddInt64Single(byte* lhs, byte* rhs);
        static int64_t AddInt64Double(byte* lhs, byte* rhs);
        static int64_t AddSingleUInt8(byte* lhs, byte* rhs);
        static int64_t AddSingleInt8(byte* lhs, byte* rhs);
        static int64_t AddSingleUInt16(byte* lhs, byte* rhs);
        static int64_t AddSingleInt16(byte* lhs, byte* rhs);
        static int64_t AddSingleUInt32(byte* lhs, byte* rhs);
        static int64_t AddSingleInt32(byte* lhs, byte* rhs);
        static int64_t AddSingleUInt64(byte* lhs, byte* rhs);
        static int64_t AddSingleInt64(byte* lhs, byte* rhs);
        static int64_t AddSingleSingle(byte* lhs, byte* rhs);
        static int64_t AddSingleDouble(byte* lhs, byte* rhs);
        static int64_t AddDoubleUInt8(byte* lhs, byte* rhs);
        static int64_t AddDoubleInt8(byte* lhs, byte* rhs);
        static int64_t AddDoubleUInt16(byte* lhs, byte* rhs);
        static int64_t AddDoubleInt16(byte* lhs, byte* rhs);
        static int64_t AddDoubleUInt32(byte* lhs, byte* rhs);
        static int64_t AddDoubleInt32(byte* lhs, byte* rhs);
        static int64_t AddDoubleUInt64(byte* lhs, byte* rhs);
        static int64_t AddDoubleInt64(byte* lhs, byte* rhs);
        static int64_t AddDoubleSingle(byte* lhs, byte* rhs);
        static int64_t AddDoubleDouble(byte* lhs, byte* rhs);

        //Subtract-------------------------
        //---------------------------------
        //---------------------------------
        //---------------------------------

        static int64_t SubtractUInt8UInt8(byte* lhs, byte* rhs);
        static int64_t SubtractUInt8Int8(byte* lhs, byte* rhs);
        static int64_t SubtractUInt8UInt16(byte* lhs, byte* rhs);
        static int64_t SubtractUInt8Int16(byte* lhs, byte* rhs);
        static int64_t SubtractUInt8UInt32(byte* lhs, byte* rhs);
        static int64_t SubtractUInt8Int32(byte* lhs, byte* rhs);
        static int64_t SubtractUInt8UInt64(byte* lhs, byte* rhs);
        static int64_t SubtractUInt8Int64(byte* lhs, byte* rhs);
        static int64_t SubtractUInt8Single(byte* lhs, byte* rhs);
        static int64_t SubtractUInt8Double(byte* lhs, byte* rhs);
        static int64_t SubtractInt8UInt8(byte* lhs, byte* rhs);
        static int64_t SubtractInt8Int8(byte* lhs, byte* rhs);
        static int64_t SubtractInt8UInt16(byte* lhs, byte* rhs);
        static int64_t SubtractInt8Int16(byte* lhs, byte* rhs);
        static int64_t SubtractInt8UInt32(byte* lhs, byte* rhs);
        static int64_t SubtractInt8Int32(byte* lhs, byte* rhs);
        static int64_t SubtractInt8UInt64(byte* lhs, byte* rhs);
        static int64_t SubtractInt8Int64(byte* lhs, byte* rhs);
        static int64_t SubtractInt8Single(byte* lhs, byte* rhs);
        static int64_t SubtractInt8Double(byte* lhs, byte* rhs);
        static int64_t SubtractUInt16UInt8(byte* lhs, byte* rhs);
        static int64_t SubtractUInt16Int8(byte* lhs, byte* rhs);
        static int64_t SubtractUInt16UInt16(byte* lhs, byte* rhs);
        static int64_t SubtractUInt16Int16(byte* lhs, byte* rhs);
        static int64_t SubtractUInt16UInt32(byte* lhs, byte* rhs);
        static int64_t SubtractUInt16Int32(byte* lhs, byte* rhs);
        static int64_t SubtractUInt16UInt64(byte* lhs, byte* rhs);
        static int64_t SubtractUInt16Int64(byte* lhs, byte* rhs);
        static int64_t SubtractUInt16Single(byte* lhs, byte* rhs);
        static int64_t SubtractUInt16Double(byte* lhs, byte* rhs);
        static int64_t SubtractInt16UInt8(byte* lhs, byte* rhs);
        static int64_t SubtractInt16Int8(byte* lhs, byte* rhs);
        static int64_t SubtractInt16UInt16(byte* lhs, byte* rhs);
        static int64_t SubtractInt16Int16(byte* lhs, byte* rhs);
        static int64_t SubtractInt16UInt32(byte* lhs, byte* rhs);
        static int64_t SubtractInt16Int32(byte* lhs, byte* rhs);
        static int64_t SubtractInt16UInt64(byte* lhs, byte* rhs);
        static int64_t SubtractInt16Int64(byte* lhs, byte* rhs);
        static int64_t SubtractInt16Single(byte* lhs, byte* rhs);
        static int64_t SubtractInt16Double(byte* lhs, byte* rhs);
        static int64_t SubtractUInt32UInt8(byte* lhs, byte* rhs);
        static int64_t SubtractUInt32Int8(byte* lhs, byte* rhs);
        static int64_t SubtractUInt32UInt16(byte* lhs, byte* rhs);
        static int64_t SubtractUInt32Int16(byte* lhs, byte* rhs);
        static int64_t SubtractUInt32UInt32(byte* lhs, byte* rhs);
        static int64_t SubtractUInt32Int32(byte* lhs, byte* rhs);
        static int64_t SubtractUInt32UInt64(byte* lhs, byte* rhs);
        static int64_t SubtractUInt32Int64(byte* lhs, byte* rhs);
        static int64_t SubtractUInt32Single(byte* lhs, byte* rhs);
        static int64_t SubtractUInt32Double(byte* lhs, byte* rhs);
        static int64_t SubtractInt32UInt8(byte* lhs, byte* rhs);
        static int64_t SubtractInt32Int8(byte* lhs, byte* rhs);
        static int64_t SubtractInt32UInt16(byte* lhs, byte* rhs);
        static int64_t SubtractInt32Int16(byte* lhs, byte* rhs);
        static int64_t SubtractInt32UInt32(byte* lhs, byte* rhs);
        static int64_t SubtractInt32Int32(byte* lhs, byte* rhs);
        static int64_t SubtractInt32UInt64(byte* lhs, byte* rhs);
        static int64_t SubtractInt32Int64(byte* lhs, byte* rhs);
        static int64_t SubtractInt32Single(byte* lhs, byte* rhs);
        static int64_t SubtractInt32Double(byte* lhs, byte* rhs);
        static int64_t SubtractUInt64UInt8(byte* lhs, byte* rhs);
        static int64_t SubtractUInt64Int8(byte* lhs, byte* rhs);
        static int64_t SubtractUInt64UInt16(byte* lhs, byte* rhs);
        static int64_t SubtractUInt64Int16(byte* lhs, byte* rhs);
        static int64_t SubtractUInt64UInt32(byte* lhs, byte* rhs);
        static int64_t SubtractUInt64Int32(byte* lhs, byte* rhs);
        static int64_t SubtractUInt64UInt64(byte* lhs, byte* rhs);
        static int64_t SubtractUInt64Int64(byte* lhs, byte* rhs);
        static int64_t SubtractUInt64Single(byte* lhs, byte* rhs);
        static int64_t SubtractUInt64Double(byte* lhs, byte* rhs);
        static int64_t SubtractInt64UInt8(byte* lhs, byte* rhs);
        static int64_t SubtractInt64Int8(byte* lhs, byte* rhs);
        static int64_t SubtractInt64UInt16(byte* lhs, byte* rhs);
        static int64_t SubtractInt64Int16(byte* lhs, byte* rhs);
        static int64_t SubtractInt64UInt32(byte* lhs, byte* rhs);
        static int64_t SubtractInt64Int32(byte* lhs, byte* rhs);
        static int64_t SubtractInt64UInt64(byte* lhs, byte* rhs);
        static int64_t SubtractInt64Int64(byte* lhs, byte* rhs);
        static int64_t SubtractInt64Single(byte* lhs, byte* rhs);
        static int64_t SubtractInt64Double(byte* lhs, byte* rhs);
        static int64_t SubtractSingleUInt8(byte* lhs, byte* rhs);
        static int64_t SubtractSingleInt8(byte* lhs, byte* rhs);
        static int64_t SubtractSingleUInt16(byte* lhs, byte* rhs);
        static int64_t SubtractSingleInt16(byte* lhs, byte* rhs);
        static int64_t SubtractSingleUInt32(byte* lhs, byte* rhs);
        static int64_t SubtractSingleInt32(byte* lhs, byte* rhs);
        static int64_t SubtractSingleUInt64(byte* lhs, byte* rhs);
        static int64_t SubtractSingleInt64(byte* lhs, byte* rhs);
        static int64_t SubtractSingleSingle(byte* lhs, byte* rhs);
        static int64_t SubtractSingleDouble(byte* lhs, byte* rhs);
        static int64_t SubtractDoubleUInt8(byte* lhs, byte* rhs);
        static int64_t SubtractDoubleInt8(byte* lhs, byte* rhs);
        static int64_t SubtractDoubleUInt16(byte* lhs, byte* rhs);
        static int64_t SubtractDoubleInt16(byte* lhs, byte* rhs);
        static int64_t SubtractDoubleUInt32(byte* lhs, byte* rhs);
        static int64_t SubtractDoubleInt32(byte* lhs, byte* rhs);
        static int64_t SubtractDoubleUInt64(byte* lhs, byte* rhs);
        static int64_t SubtractDoubleInt64(byte* lhs, byte* rhs);
        static int64_t SubtractDoubleSingle(byte* lhs, byte* rhs);
        static int64_t SubtractDoubleDouble(byte* lhs, byte* rhs);

        //Multiply-------------------------
        //---------------------------------
        //---------------------------------
        //---------------------------------

        static int64_t MultiplyUInt8UInt8(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt8Int8(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt8UInt16(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt8Int16(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt8UInt32(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt8Int32(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt8UInt64(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt8Int64(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt8Single(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt8Double(byte* lhs, byte* rhs);
        static int64_t MultiplyInt8UInt8(byte* lhs, byte* rhs);
        static int64_t MultiplyInt8Int8(byte* lhs, byte* rhs);
        static int64_t MultiplyInt8UInt16(byte* lhs, byte* rhs);
        static int64_t MultiplyInt8Int16(byte* lhs, byte* rhs);
        static int64_t MultiplyInt8UInt32(byte* lhs, byte* rhs);
        static int64_t MultiplyInt8Int32(byte* lhs, byte* rhs);
        static int64_t MultiplyInt8UInt64(byte* lhs, byte* rhs);
        static int64_t MultiplyInt8Int64(byte* lhs, byte* rhs);
        static int64_t MultiplyInt8Single(byte* lhs, byte* rhs);
        static int64_t MultiplyInt8Double(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt16UInt8(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt16Int8(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt16UInt16(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt16Int16(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt16UInt32(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt16Int32(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt16UInt64(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt16Int64(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt16Single(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt16Double(byte* lhs, byte* rhs);
        static int64_t MultiplyInt16UInt8(byte* lhs, byte* rhs);
        static int64_t MultiplyInt16Int8(byte* lhs, byte* rhs);
        static int64_t MultiplyInt16UInt16(byte* lhs, byte* rhs);
        static int64_t MultiplyInt16Int16(byte* lhs, byte* rhs);
        static int64_t MultiplyInt16UInt32(byte* lhs, byte* rhs);
        static int64_t MultiplyInt16Int32(byte* lhs, byte* rhs);
        static int64_t MultiplyInt16UInt64(byte* lhs, byte* rhs);
        static int64_t MultiplyInt16Int64(byte* lhs, byte* rhs);
        static int64_t MultiplyInt16Single(byte* lhs, byte* rhs);
        static int64_t MultiplyInt16Double(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt32UInt8(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt32Int8(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt32UInt16(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt32Int16(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt32UInt32(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt32Int32(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt32UInt64(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt32Int64(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt32Single(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt32Double(byte* lhs, byte* rhs);
        static int64_t MultiplyInt32UInt8(byte* lhs, byte* rhs);
        static int64_t MultiplyInt32Int8(byte* lhs, byte* rhs);
        static int64_t MultiplyInt32UInt16(byte* lhs, byte* rhs);
        static int64_t MultiplyInt32Int16(byte* lhs, byte* rhs);
        static int64_t MultiplyInt32UInt32(byte* lhs, byte* rhs);
        static int64_t MultiplyInt32Int32(byte* lhs, byte* rhs);
        static int64_t MultiplyInt32UInt64(byte* lhs, byte* rhs);
        static int64_t MultiplyInt32Int64(byte* lhs, byte* rhs);
        static int64_t MultiplyInt32Single(byte* lhs, byte* rhs);
        static int64_t MultiplyInt32Double(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt64UInt8(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt64Int8(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt64UInt16(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt64Int16(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt64UInt32(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt64Int32(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt64UInt64(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt64Int64(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt64Single(byte* lhs, byte* rhs);
        static int64_t MultiplyUInt64Double(byte* lhs, byte* rhs);
        static int64_t MultiplyInt64UInt8(byte* lhs, byte* rhs);
        static int64_t MultiplyInt64Int8(byte* lhs, byte* rhs);
        static int64_t MultiplyInt64UInt16(byte* lhs, byte* rhs);
        static int64_t MultiplyInt64Int16(byte* lhs, byte* rhs);
        static int64_t MultiplyInt64UInt32(byte* lhs, byte* rhs);
        static int64_t MultiplyInt64Int32(byte* lhs, byte* rhs);
        static int64_t MultiplyInt64UInt64(byte* lhs, byte* rhs);
        static int64_t MultiplyInt64Int64(byte* lhs, byte* rhs);
        static int64_t MultiplyInt64Single(byte* lhs, byte* rhs);
        static int64_t MultiplyInt64Double(byte* lhs, byte* rhs);
        static int64_t MultiplySingleUInt8(byte* lhs, byte* rhs);
        static int64_t MultiplySingleInt8(byte* lhs, byte* rhs);
        static int64_t MultiplySingleUInt16(byte* lhs, byte* rhs);
        static int64_t MultiplySingleInt16(byte* lhs, byte* rhs);
        static int64_t MultiplySingleUInt32(byte* lhs, byte* rhs);
        static int64_t MultiplySingleInt32(byte* lhs, byte* rhs);
        static int64_t MultiplySingleUInt64(byte* lhs, byte* rhs);
        static int64_t MultiplySingleInt64(byte* lhs, byte* rhs);
        static int64_t MultiplySingleSingle(byte* lhs, byte* rhs);
        static int64_t MultiplySingleDouble(byte* lhs, byte* rhs);
        static int64_t MultiplyDoubleUInt8(byte* lhs, byte* rhs);
        static int64_t MultiplyDoubleInt8(byte* lhs, byte* rhs);
        static int64_t MultiplyDoubleUInt16(byte* lhs, byte* rhs);
        static int64_t MultiplyDoubleInt16(byte* lhs, byte* rhs);
        static int64_t MultiplyDoubleUInt32(byte* lhs, byte* rhs);
        static int64_t MultiplyDoubleInt32(byte* lhs, byte* rhs);
        static int64_t MultiplyDoubleUInt64(byte* lhs, byte* rhs);
        static int64_t MultiplyDoubleInt64(byte* lhs, byte* rhs);
        static int64_t MultiplyDoubleSingle(byte* lhs, byte* rhs);
        static int64_t MultiplyDoubleDouble(byte* lhs, byte* rhs);

        //Divide---------------------------
        //---------------------------------
        //---------------------------------
        //---------------------------------

        static int64_t DivideUInt8UInt8(byte* lhs, byte* rhs);
        static int64_t DivideUInt8Int8(byte* lhs, byte* rhs);
        static int64_t DivideUInt8UInt16(byte* lhs, byte* rhs);
        static int64_t DivideUInt8Int16(byte* lhs, byte* rhs);
        static int64_t DivideUInt8UInt32(byte* lhs, byte* rhs);
        static int64_t DivideUInt8Int32(byte* lhs, byte* rhs);
        static int64_t DivideUInt8UInt64(byte* lhs, byte* rhs);
        static int64_t DivideUInt8Int64(byte* lhs, byte* rhs);
        static int64_t DivideUInt8Single(byte* lhs, byte* rhs);
        static int64_t DivideUInt8Double(byte* lhs, byte* rhs);
        static int64_t DivideInt8UInt8(byte* lhs, byte* rhs);
        static int64_t DivideInt8Int8(byte* lhs, byte* rhs);
        static int64_t DivideInt8UInt16(byte* lhs, byte* rhs);
        static int64_t DivideInt8Int16(byte* lhs, byte* rhs);
        static int64_t DivideInt8UInt32(byte* lhs, byte* rhs);
        static int64_t DivideInt8Int32(byte* lhs, byte* rhs);
        static int64_t DivideInt8UInt64(byte* lhs, byte* rhs);
        static int64_t DivideInt8Int64(byte* lhs, byte* rhs);
        static int64_t DivideInt8Single(byte* lhs, byte* rhs);
        static int64_t DivideInt8Double(byte* lhs, byte* rhs);
        static int64_t DivideUInt16UInt8(byte* lhs, byte* rhs);
        static int64_t DivideUInt16Int8(byte* lhs, byte* rhs);
        static int64_t DivideUInt16UInt16(byte* lhs, byte* rhs);
        static int64_t DivideUInt16Int16(byte* lhs, byte* rhs);
        static int64_t DivideUInt16UInt32(byte* lhs, byte* rhs);
        static int64_t DivideUInt16Int32(byte* lhs, byte* rhs);
        static int64_t DivideUInt16UInt64(byte* lhs, byte* rhs);
        static int64_t DivideUInt16Int64(byte* lhs, byte* rhs);
        static int64_t DivideUInt16Single(byte* lhs, byte* rhs);
        static int64_t DivideUInt16Double(byte* lhs, byte* rhs);
        static int64_t DivideInt16UInt8(byte* lhs, byte* rhs);
        static int64_t DivideInt16Int8(byte* lhs, byte* rhs);
        static int64_t DivideInt16UInt16(byte* lhs, byte* rhs);
        static int64_t DivideInt16Int16(byte* lhs, byte* rhs);
        static int64_t DivideInt16UInt32(byte* lhs, byte* rhs);
        static int64_t DivideInt16Int32(byte* lhs, byte* rhs);
        static int64_t DivideInt16UInt64(byte* lhs, byte* rhs);
        static int64_t DivideInt16Int64(byte* lhs, byte* rhs);
        static int64_t DivideInt16Single(byte* lhs, byte* rhs);
        static int64_t DivideInt16Double(byte* lhs, byte* rhs);
        static int64_t DivideUInt32UInt8(byte* lhs, byte* rhs);
        static int64_t DivideUInt32Int8(byte* lhs, byte* rhs);
        static int64_t DivideUInt32UInt16(byte* lhs, byte* rhs);
        static int64_t DivideUInt32Int16(byte* lhs, byte* rhs);
        static int64_t DivideUInt32UInt32(byte* lhs, byte* rhs);
        static int64_t DivideUInt32Int32(byte* lhs, byte* rhs);
        static int64_t DivideUInt32UInt64(byte* lhs, byte* rhs);
        static int64_t DivideUInt32Int64(byte* lhs, byte* rhs);
        static int64_t DivideUInt32Single(byte* lhs, byte* rhs);
        static int64_t DivideUInt32Double(byte* lhs, byte* rhs);
        static int64_t DivideInt32UInt8(byte* lhs, byte* rhs);
        static int64_t DivideInt32Int8(byte* lhs, byte* rhs);
        static int64_t DivideInt32UInt16(byte* lhs, byte* rhs);
        static int64_t DivideInt32Int16(byte* lhs, byte* rhs);
        static int64_t DivideInt32UInt32(byte* lhs, byte* rhs);
        static int64_t DivideInt32Int32(byte* lhs, byte* rhs);
        static int64_t DivideInt32UInt64(byte* lhs, byte* rhs);
        static int64_t DivideInt32Int64(byte* lhs, byte* rhs);
        static int64_t DivideInt32Single(byte* lhs, byte* rhs);
        static int64_t DivideInt32Double(byte* lhs, byte* rhs);
        static int64_t DivideUInt64UInt8(byte* lhs, byte* rhs);
        static int64_t DivideUInt64Int8(byte* lhs, byte* rhs);
        static int64_t DivideUInt64UInt16(byte* lhs, byte* rhs);
        static int64_t DivideUInt64Int16(byte* lhs, byte* rhs);
        static int64_t DivideUInt64UInt32(byte* lhs, byte* rhs);
        static int64_t DivideUInt64Int32(byte* lhs, byte* rhs);
        static int64_t DivideUInt64UInt64(byte* lhs, byte* rhs);
        static int64_t DivideUInt64Int64(byte* lhs, byte* rhs);
        static int64_t DivideUInt64Single(byte* lhs, byte* rhs);
        static int64_t DivideUInt64Double(byte* lhs, byte* rhs);
        static int64_t DivideInt64UInt8(byte* lhs, byte* rhs);
        static int64_t DivideInt64Int8(byte* lhs, byte* rhs);
        static int64_t DivideInt64UInt16(byte* lhs, byte* rhs);
        static int64_t DivideInt64Int16(byte* lhs, byte* rhs);
        static int64_t DivideInt64UInt32(byte* lhs, byte* rhs);
        static int64_t DivideInt64Int32(byte* lhs, byte* rhs);
        static int64_t DivideInt64UInt64(byte* lhs, byte* rhs);
        static int64_t DivideInt64Int64(byte* lhs, byte* rhs);
        static int64_t DivideInt64Single(byte* lhs, byte* rhs);
        static int64_t DivideInt64Double(byte* lhs, byte* rhs);
        static int64_t DivideSingleUInt8(byte* lhs, byte* rhs);
        static int64_t DivideSingleInt8(byte* lhs, byte* rhs);
        static int64_t DivideSingleUInt16(byte* lhs, byte* rhs);
        static int64_t DivideSingleInt16(byte* lhs, byte* rhs);
        static int64_t DivideSingleUInt32(byte* lhs, byte* rhs);
        static int64_t DivideSingleInt32(byte* lhs, byte* rhs);
        static int64_t DivideSingleUInt64(byte* lhs, byte* rhs);
        static int64_t DivideSingleInt64(byte* lhs, byte* rhs);
        static int64_t DivideSingleSingle(byte* lhs, byte* rhs);
        static int64_t DivideSingleDouble(byte* lhs, byte* rhs);
        static int64_t DivideDoubleUInt8(byte* lhs, byte* rhs);
        static int64_t DivideDoubleInt8(byte* lhs, byte* rhs);
        static int64_t DivideDoubleUInt16(byte* lhs, byte* rhs);
        static int64_t DivideDoubleInt16(byte* lhs, byte* rhs);
        static int64_t DivideDoubleUInt32(byte* lhs, byte* rhs);
        static int64_t DivideDoubleInt32(byte* lhs, byte* rhs);
        static int64_t DivideDoubleUInt64(byte* lhs, byte* rhs);
        static int64_t DivideDoubleInt64(byte* lhs, byte* rhs);
        static int64_t DivideDoubleSingle(byte* lhs, byte* rhs);
        static int64_t DivideDoubleDouble(byte* lhs, byte* rhs);
    };
}
#endif

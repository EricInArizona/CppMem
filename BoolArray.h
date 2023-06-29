// Copyright Eric Chauvin 2022 - 2023.



// This is licensed under the GNU General
// Public License (GPL), version 2.  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once


#include "../CppBase/BasicTypes.h"
#include "../CppBase/RangeC.h"
#include "../CppBase/Casting.h"



// -Wno-unsafe-buffer-usage

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"


class BoolArray
  {
  private:
  bool testForCopy = false;
  Int32 arraySize = 1;
  bool* bArray;

  public:
  inline BoolArray( void )
    {
    arraySize = 1;
    bArray = new bool[Casting::i32ToU64(
                                  arraySize )];
    }


  inline BoolArray( const BoolArray &in )
    {
    if( in.testForCopy )
      return;

    throw "BoolArray copy constructor.";
    }

  inline ~BoolArray( void )
    {
    delete[] bArray;
    }

  inline void setSize( const Int32 howBig )
    {
    if( howBig < 1 )
      throw "BoolArray array size < 1.";

    arraySize = howBig;

    delete[] bArray;
    bArray = new bool[Casting::i32ToU64(
                                arraySize )];
    }

  inline Int32 getSize( void ) const
    {
    return arraySize;
    }

  inline bool getVal( const Int32 where ) const
    {
    RangeC::test2( where, 0, arraySize - 1,
           "BoolArray.getVal() where range." );

    return bArray[where];
    }

  inline void setVal( const Int32 where,
                      const bool toSet )
    {
    RangeC::test2( where, 0, arraySize - 1,
             "BoolArray.setVal() where range." );

    bArray[where] = toSet;
    }


  };

#pragma clang diagnostic pop

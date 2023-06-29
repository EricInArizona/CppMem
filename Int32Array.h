// Copyright Eric Chauvin 2022 - 2023.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once


#include "../CppBase/BasicTypes.h"
#include "../CppBase/RangeC.h"
#include "../CppBase/Casting.h"


// -Wno-unsafe-buffer-usage

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"


class Int32Array
  {
  private:
  bool testForCopy = false;
  Int32 arraySize = 1;
  Int32* iArray;

  public:
  inline Int32Array( void )
    {
    arraySize = 1;
    iArray = new Int32[
                  Casting::i32ToU64( arraySize )];
    }


  inline Int32Array( const Int32Array& in )
    {
    arraySize = 1;
    iArray = new Int32[
               Casting::i32ToU64( arraySize )];

    if( in.testForCopy )
      return;

    throw "Int32Array copy constructor.";
    }


  inline ~Int32Array( void )
    {
    delete[] iArray;
    }

  inline void setSize( const Int32 howBig )
    {
    if( howBig == arraySize )
      return;

    arraySize = howBig;
    delete[] iArray;
    iArray = new Int32[
                 Casting::i32ToU64( arraySize )];
    }


  inline Int32 getSize( void ) const
    {
    return arraySize;
    }

  inline Int32 getVal( const Int32 where ) const
    {
    RangeC::test2( where, 0, arraySize - 1,
      "Int32Array.getVal arraySize range." );

    return iArray[where];
    }

  inline void setVal( const Int32 where,
                      const Int32 toSet )
    {
    RangeC::test2( where, 0, arraySize - 1,
           "Int32Array.setVal where range." );

    iArray[where] = toSet;
    }


  inline void copy( const Int32Array& in )
    {
    setSize( in.arraySize );

    const Int32 max = arraySize;
    for( Int32 count = 0; count < max; count++ )
      iArray[count] = in.iArray[count];

    }

  };

#pragma clang diagnostic pop

// Copyright Eric Chauvin 2022


// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once


#include "BasicTypes.h"
#include "RangeC.h"


class Int64Array
  {
  private:
  bool testForCopy = false;
  Int32 arraySize = 0;
  Int64* iArray;

  public:
  inline Int64Array( void )
    {
    arraySize = 1;
    iArray = new Int64[
               Casting::i32ToU64( arraySize )];
    }

  inline Int64Array( const Int64Array& in )
    {
    arraySize = 1;
    iArray = new Int64[
              Casting::i32ToU64( arraySize )];

    if( in.testForCopy )
      return;

    throw "Int64Array copy constructor.";
    }

  inline ~Int64Array( void )
    {
    delete[] iArray;
    }


  inline void setSize( const Int32 howBig )
    {
    arraySize = howBig;

    delete[] iArray;
    iArray = new Int64[
                Casting::i32ToU64( arraySize )];
    }

  inline Int32 getArraySize( void ) const
    {
    return arraySize;
    }

  inline Int64 getVal( const Int32 where ) const
    {
    RangeC::test2( where, 0, arraySize - 1,
      "Int64Array.getVal arraySize range." );

    return iArray[where];
    }

  inline void setVal( const Int32 where,
                      const Int64 toSet )
    {
    RangeC::test2( where, 0, arraySize - 1,
           "Int64Array.setVal where range." );

    iArray[where] = toSet;
    }


  inline void copy( const Int64Array& in )
    {
    setSize( in.arraySize );
    const Int32 max = arraySize;
    for( Int32 count = 0; count < max; count++ )
      iArray[count] = in.iArray[count];

    }

  };

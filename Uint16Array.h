// Copyright Eric Chauvin 2022


// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once


#include "BasicTypes.h"
#include "RangeC.h"
#include "Casting.h"


class Uint16Array
  {
  private:
  Uint16* cArray;
  Int32 arraySize = 1;
  bool testForCopy = false;

  public:
  inline Uint16Array( void )
    {
    arraySize = 1;
    cArray = new Uint16[
                  Casting::i32ToU64( arraySize )];
    }

  inline Uint16Array( const Uint16Array &in )
    {
    arraySize = 1;
    cArray = new Uint16[
                  Casting::i32ToU64( arraySize )];

    if( in.testForCopy )
      return;

    throw "Uint16Array copy constructor";
    }


  inline ~Uint16Array( void )
    {
    delete[] cArray;
    }

  inline void setSize( Int32 howBig )
    {
    if( arraySize == howBig )
      return;

    arraySize = howBig;
    delete[] cArray;
    cArray = new Uint16[
                  Casting::i32ToU64( arraySize )];

    }

  inline Int32 getSize( void ) const
    {
    return arraySize;
    }

  inline Uint16 getVal( const Int32 where ) const
    {
    RangeC::test2( where, 0, arraySize - 1,
                  "UTF16Array.getVal() range." );

    return cArray[where];
    }

  inline void setVal( const Int32 where,
                      const Uint16 setTo )
    {
    RangeC::test2( where, 0, arraySize - 1,
                  "UTF16Array.setVal() range." );

    cArray[where] = setTo;
    }

  inline void copy( const Uint16Array& in )
    {
    setSize( in.arraySize );

    const Int32 max = arraySize;
    for( Int32 count = 0; count < max; count++ )
      cArray[count] = in.cArray[count];

    }

  };

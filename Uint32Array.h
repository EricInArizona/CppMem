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


class Uint32Array
  {
  private:
  Uint32* uArray;
  Int32 arraySize = 1;
  bool testForCopy = false;

  public:
  inline Uint32Array( void )
    {
    arraySize = 1;
    uArray = new Uint32[
                  Casting::i32ToU64( arraySize )];
    }

  inline Uint32Array( const Uint32Array &in )
    {
    arraySize = 1;
    uArray = new Uint32[
                  Casting::i32ToU64( arraySize )];

    if( in.testForCopy )
      return;

    throw "Uint32Array copy constructor";
    }


  inline ~Uint32Array( void )
    {
    delete[] uArray;
    }

  inline void setSize( Int32 howBig )
    {
    if( arraySize == howBig )
      return;

    arraySize = howBig;
    delete[] uArray;
    uArray = new Uint32[
                  Casting::i32ToU64( arraySize )];

    }


  inline Int32 getSize( void ) const
    {
    return arraySize;
    }

  inline Uint32 getVal( const Int32 where ) const
    {
    RangeC::test2( where, 0, arraySize - 1,
                  "Uint32Array.getVal() range." );

    return uArray[where];
    }

  inline void setVal( const Int32 where,
                      const Uint32 setTo )
    {
    RangeC::test2( where, 0, arraySize - 1,
                  "Uint32Array.setVal() range." );

    uArray[where] = setTo;
    }

  inline void copy( const Uint32Array& in )
    {
    setSize( in.arraySize );

    const Int32 max = arraySize;
    for( Int32 count = 0; count < max; count++ )
      uArray[count] = in.uArray[count];

    }


  };

#pragma clang diagnostic pop

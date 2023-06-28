// Copyright Eric Chauvin 2022 - 2023.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#pragma once


#include "../CppBase/BasicTypes.h"
#include "../CppBase/RangeC.h"
#include "../CppBase/Casting.h"


// This is only used for things that have to
// be compatible with antiquated APIs.

// -Wno-unsafe-buffer-usage


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"


class OpenCharArray
  {
  private:
  bool testForCopy = false;
  Int32 arraySize = 1;

  public:
  char* cArray; // public and open.

  inline OpenCharArray( void )
    {
    arraySize = 1;
    cArray = new char[Casting::i32ToU64(
                                 arraySize )];
    }

  inline OpenCharArray( const OpenCharArray& in )
    {
    arraySize = 1;
    cArray = new char[Casting::i32ToU64(
                                arraySize )];

    if( in.testForCopy )
      return;

    const char* showS = "The OpenCharArray copy"
        " constructor should not get called.";

    throw showS;
    }

  inline ~OpenCharArray( void )
    {
    delete[] cArray;
    }

  inline void setSize( const Int32 howBig )
    {
    if( howBig == arraySize )
      return;

    if( howBig < 1 )
      throw "OpenCharArray.setSize howBig.";

    arraySize = howBig;
    delete[] cArray;
    // Casting.h is meant to throw exceptions
    // when it has something like a negative
    // number being cast to an unsigned number.
    cArray = new char[Casting::i32ToU64(
                                    arraySize )];
    }

  inline Int32 getSize() const
    {
    return arraySize;
    }

  inline char getC( const Int32 where ) const
    {
    RangeC::test2( where, 0, arraySize - 1,
             "OpenCharArray.getC() arraySize." );

    return cArray[where];
    }

  inline void setC( const Int32 where,
                    const char toSet )
    {
    RangeC::test2( where, 0, arraySize - 1,
             "OpenCharArray.setC() arraySize." );

    cArray[where] = toSet;
    }

  };

#pragma clang diagnostic pop

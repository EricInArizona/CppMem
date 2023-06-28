// Copyright Eric Chauvin 2022 - 2023.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html




#pragma once



#include "../CppBase/BasicTypes.h"
#include "../CppBase/Casting.h"
#include "../CppBase/RangeC.h"


// In the future clang might want you to use
// std::array and things like that.

// -Wno-unsafe-buffer-usage


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"

class ByteArray
  {
  private:
  bool testForCopy = false;

  char* cArray;

  Int32 arraySize = 1;

  public:
  inline ByteArray( void )
    {
    arraySize = 1;
    cArray = new char[Casting::i32ToU64(
                                 arraySize )];
    }

  inline ByteArray( const ByteArray& in )
    {
    arraySize = 1;
    cArray = new char[Casting::i32ToU64(
                                arraySize )];

    if( in.testForCopy )
      return;

    const char* showS = "The ByteArray copy"
        " constructor should not get called.";

    throw showS;
    }

  inline ~ByteArray( void )
    {
    delete[] cArray;
    }

  inline void setSize( const Int32 howBig )
    {
    if( howBig == arraySize )
      return;

    if( howBig < 1 )
      throw "ByteArray.setSize howBig.";

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


  inline void copy( const ByteArray& copyFrom,
                    const Int32 howMany,
                    const Int32 setToSize )
    {
    if( setToSize < howMany )
      throw
        "ByteArray.copy() setToSize < howMany";

    const Int32 thisSize = getSize();
    if( thisSize != setToSize )
      setSize( setToSize );

    const Int32 fromSize = copyFrom.getSize();
    if( fromSize < howMany )
      throw "ByteArray.copy() fromSize < howMany";

    // memcpy() in string.h.
    // std::memcpy()

    // Use inline assembly to copy a block
    // of memory.

    for( Int32 count = 0; count < howMany;
                                      count++ )
      cArray[count] = copyFrom.cArray[count];

    }


  inline void increaseSize( const Int32 howMuch )
    {
    if( howMuch < 1 )
      throw "ByteArray.increaseSize() howMuch.";

    if( ( Casting::i32ToU64( arraySize ) +
          Casting::i32ToU64( howMuch ) ) >=
        0x7FFFFFFF )
      throw "ByteArray.increaseSize too big.";

    const Int32 max = arraySize;
    arraySize = arraySize + howMuch;

    char* tempArray = new char[Casting::i32ToU64(
                                 arraySize )];

    for( Int32 count = 0; count < max; count++ )
      tempArray[count] = cArray[count];

    delete[] cArray;

    // Assign the pointer to the new array.
    cArray = tempArray;
    }


  inline char getC( const Int32 where ) const
    {
    RangeC::test2( where, 0, arraySize - 1,
             "ByteArray.getC() arraySize." );

    return cArray[where];
    }

  inline Uint8 getU8( const Int32 where ) const
    {
    RangeC::test2( where, 0, arraySize - 1,
             "ByteArray.getU8() arraySize." );

    return cArray[where] & 0xFF;
    }

  inline void setC( const Int32 where,
                    const char toSet )
    {
    RangeC::test2( where, 0, arraySize - 1,
             "ByteArray.setC() arraySize." );

    cArray[where] = toSet;
    }

  inline void setU8( const Int32 where,
                     const Uint8 toSet )
    {
    RangeC::test2( where, 0, arraySize - 1,
             "ByteArray.setU8() arraySize." );

    // char changeIt = toSet & 0x7F;
    // if( (toSet & 0x80) != 0 )
      // changeIt |= 0x80;

    // Avoid the warning about changing sign.

    // char change2 = toSet & 0x7F;
    // change2 |= toSet & 0x80;

    char change2 = 0;
    change2 |= toSet & 0xFF;


    // if( changeIt != change2 )
      // throw "ByteArray.setU8() changeIt.";

    cArray[where] = change2;
    }

  };

#pragma clang diagnostic pop

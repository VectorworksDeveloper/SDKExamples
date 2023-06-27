//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

// Set this flag to build VW without Quicktime on Windows
#define QUICKTIME_REMOVED 1

#define PRAGMA_STRUCT_ALIGN         0
#define PRAGMA_ONCE                 0
#define PRAGMA_STRUCT_PACK          1
#define PRAGMA_STRUCT_PACKPUSH      1

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

/********************************************************************************

    Special values in C
    
        NULL        The C standard for an impossible pointer value
        nil         A carry over from pascal, NULL is prefered for C
        
*********************************************************************************/
#ifndef NULL
    #define NULL 0L
#endif

#ifndef nil
    #define nil NULL
#endif

/********************************************************************************

    Base integer types for all target OS's and CPU's
    
        Uint8            8-bit unsigned integer 
        Sint8            8-bit signed integer
        Uint16          16-bit unsigned integer 
        Sint16          16-bit signed integer           
        Uint32          32-bit unsigned integer 
        Sint32          32-bit signed integer   
        Uint64          64-bit unsigned integer 
        Sint64          64-bit signed integer   

*********************************************************************************/


//	TARGET_RT_BIG_ENDIAN        0
//  TARGET_RT_LITTLE_ENDIAN     1
struct wide {
    Uint32                          lo;
    Sint32                          hi;
};
typedef struct wide                     wide;

struct UnsignedWide {
    Uint32                          lo;
    Uint32                          hi;
};
typedef struct UnsignedWide             UnsignedWide;

/********************************************************************************

    Base fixed point types 
    
        Fixed           16-bit signed integer plus 16-bit fraction
        UnsignedFixed   16-bit unsigned integer plus 16-bit fraction
        Fract           2-bit signed integer plus 30-bit fraction
        ShortFixed      8-bit signed integer plus 8-bit fraction
        
*********************************************************************************/
typedef Sint32                          Fixed;
typedef Fixed *                         FixedPtr;
typedef Sint32                          Fract;
typedef Fract *                         FractPtr;
typedef Uint32		                    UnsignedFixed;
typedef UnsignedFixed *                 UnsignedFixedPtr;
typedef short                           ShortFixed;
typedef ShortFixed *                    ShortFixedPtr;

/********************************************************************************

    Base floating point types 
    
        Float32         32 bit IEEE float:  1 sign bit, 8 exponent bits, 23 fraction bits
        Float64         64 bit IEEE float:  1 sign bit, 11 exponent bits, 52 fraction bits  
        Float80         80 bit MacOS float: 1 sign bit, 15 exponent bits, 1 integer bit, 63 fraction bits
        Float96         96 bit 68881 float: 1 sign bit, 15 exponent bits, 16 pad bits, 1 integer bit, 63 fraction bits
        
    Note: These are fixed size floating point types, useful when writing a floating
          point value to disk.  If your compiler does not support a particular size 
          float, a struct is used instead.
          Use of of the NCEG types (e.g. double_t) or an ANSI C type (e.g. double) if
          you want a floating point representation that is natural for any given
          compiler, but might be a different size on different compilers.

*********************************************************************************/
typedef float           Float32;

typedef double          Float64;


struct Float80 {
    Sint16  exp;
    Uint16  man[4];
};
typedef struct Float80 Float80;
    
    


/********************************************************************************

    MacOS Memory Manager types
    
        Ptr             Pointer to a non-relocatable block
        Handle          Pointer to a master pointer to a relocatable block
        GSSize            The number of bytes in a block (signed for historical reasons)
        
*********************************************************************************/
typedef char *                          Ptr;
typedef Ptr *                           Handle;
typedef size_t		                    GSSize;

/********************************************************************************

    Higher level basic types
    
        OSErr                   16-bit result error code
        OSStatus                32-bit result error code
        LogicalAddress          Address in the clients virtual address space
        ConstLogicalAddress     Address in the clients virtual address space that will only be read
        PhysicalAddress         Real address as used on the hardware bus
        BytePtr                 Pointer to an array of bytes
        ByteCount               The size of an array of bytes
        ByteOffset              An offset into an array of bytes
        ItemCount               32-bit iteration count
        OptionBits              Standard 32-bit set of bit flags
        PBVersion               ?
        Duration                32-bit millisecond timer for drivers
        AbsoluteTime            64-bit clock
        ScriptCode              A particular set of written characters (e.g. Roman vs Cyrillic) and their encoding
        LangCode                A particular language (e.g. English), as represented using a particular ScriptCode
        RegionCode              Designates a language as used in a particular region (e.g. British vs American
                                English) together with other region-dependent characteristics (e.g. date format)
        FourCharCode            A 32-bit value made by packing four 1 byte characters together
        OSType                  A FourCharCode used in the OS and file system (e.g. creator)
        ResType                 A FourCharCode used to tag resources (e.g. 'DLOG')
        
*********************************************************************************/
typedef Sint16                          OSErr;
typedef Sint32                          OSStatus;
typedef void *                          LogicalAddress;
typedef const void *                    ConstLogicalAddress;
typedef void *                          PhysicalAddress;
typedef Uint8 *                         BytePtr;
typedef Uint32                          ByteCount;
typedef Uint32                          ByteOffset;
typedef Sint32                          Duration;
typedef UnsignedWide                    AbsoluteTime;
typedef Uint32                          OptionBits;
typedef Uint32                          ItemCount;
typedef Uint32                          PBVersion;
typedef Sint16                          ScriptCode;
typedef Sint16                          LangCode;
typedef Sint16                          RegionCode;
typedef Uint32							FourCharCode;
typedef FourCharCode                    OSType;
typedef FourCharCode                    ResType;
typedef OSType *                        OSTypePtr;
typedef ResType *                       ResTypePtr;



/********************************************************************************

    Common Constants
    
        noErr                   OSErr: function performed properly - no error
        kNilOptions             OptionBits: all flags false
        kInvalidID              KernelID: NULL is for pointers as kInvalidID is for ID's
        kVariableLengthArray    array bounds: variable length array

    Note: kVariableLengthArray is used in array bounds to specify a variable length array.
          It is ususally used in variable length structs when the last field is an array
          of any size.  Before ANSI C, we used zero as the bounds of variable length 
          array, but zero length array are illegal in ANSI C.  Example usage:
    
        struct FooList 
        {
            short   listLength;
            Foo     elements[kVariableLengthArray];
        };
        
*********************************************************************************/
enum {
    noErr                       = 0
};

enum {
    kNilOptions                 = 0
};

#define kInvalidID   0
enum {
    kVariableLengthArray        = 1
};

enum {
    kUnknownType                = 0x3F3F3F3F                    /* '????' QuickTime 3.0: default unknown ResType or OSType */
};


/********************************************************************************

    Quickdraw Types
    
        Point               2D Quickdraw coordinate, range: -32K to +32K
        Rect                Rectangluar Quickdraw area
        Style               Quickdraw font rendering styles
        StyleParameter      Style when used as a parameter (historical 68K convention)
        StyleField          Style when used as a field (historical 68K convention)
        CharParameter       Char when used as a parameter (historical 68K convention)
        
    Note:   The original Macintosh toolbox in 68K Pascal defined Style as a SET.  
            Both Style and CHAR occupy 8-bits in packed records or 16-bits when 
            used as fields in non-packed records or as parameters. 
        
*********************************************************************************/

struct Point {
    short                           v;
    short                           h;
};
typedef struct Point                    Point;
typedef Point *                         PointPtr;

typedef Point                           Cell; // added from Lists.h

struct Rect {
    short                           top;
    short                           left;
    short                           bottom;
    short                           right;
};
typedef struct Rect                     Rect;
typedef Rect *                          RectPtr;

struct FixedPoint {
    Fixed                           x;
    Fixed                           y;
};
typedef struct FixedPoint               FixedPoint;

struct FixedRect {
    Fixed                           left;
    Fixed                           top;
    Fixed                           right;
    Fixed                           bottom;
};
typedef struct FixedRect                FixedRect;

typedef short                           CharParameter;
enum {
    normal                      = 0,
    bold                        = 1,
    italic                      = 2,
    underline                   = 4,
    outline                     = 8,
    shadow                      = 0x10,
    condense                    = 0x20,
    extend                      = 0x40
};

typedef unsigned char                   Style;
typedef short                           StyleParameter;
typedef Style                           StyleField;


/********************************************************************************

    MacOS versioning structures
        
*********************************************************************************/

enum {
                                                                /* Version Release Stage Codes */
    developStage                = 0x20,
    alphaStage                  = 0x40,
    betaStage                   = 0x60,
    finalStage                  = 0x80
};

/*********************************************************************************

    Old names for types
        
*********************************************************************************/

typedef Uint8                           Byte;
typedef signed char                     SignedByte;
typedef wide *                          WidePtr;
typedef UnsignedWide *                  UnsignedWidePtr;
typedef Float80                         extended80;
typedef Sint8                           VHSelect;

/*********************************************************************************

    Debugger functions
    
*********************************************************************************/



#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

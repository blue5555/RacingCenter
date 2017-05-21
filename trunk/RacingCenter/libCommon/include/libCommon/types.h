#ifndef  BASE_TYPES_H
#define  BASE_TYPES_H

/*
#ifndef _WIN32
    // use stdint.h types on all platforms but windows
    #include <stdint.h>
    typedef int8_t   tInt8;   
    typedef uint8_t  tUInt8;  
    typedef int16_t  tInt16;  
    typedef uint16_t tUInt16; 
    typedef int32_t  tInt32;  
    typedef uint32_t tUInt32; 
    typedef int64_t  tInt64;  
    typedef uint64_t tUInt64; 
#else
*/

//#endif



//typedef false				tFalse;
//typedef true				tTrue;

typedef signed char			tInt8;
typedef short int           tInt16;
typedef int                 tInt32;
typedef long long			tInt64; // int

typedef unsigned char       tUInt8;
typedef unsigned short int  tUInt16;
typedef unsigned int        tUInt32;
typedef unsigned long long	tUInt64; // int

typedef unsigned int tUInt; /* n */

typedef float tFloat32; /* f32 */
typedef double tFloat64; /* f64 */
typedef long double tFloat128; /* f80 */
//typedef int tInt; /* n */
typedef double tFloat; /* f */
//typedef int tInt32;
//typedef int tInt64;
typedef tInt32 tResult; /* n */
typedef tUInt64 tTimeStamp; /* n */
typedef size_t tSize; /* sz */

typedef void tVoid; /* v */
//typedef bool tBool; /* b */
typedef tInt8 tBool;
typedef char tChar; /* c */
typedef signed short int tWChar; /* wc */

#ifndef WIN32
    typedef char TCHAR;
#endif // WIN32

#endif /* BASE_TYPES_H */

#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>
#include <string.h>

/**
 * @brief   Embedded user type declaration from 8-bit up to 64-bit
 *          include integers, float and double point types.
 */
typedef signed char             s8_t; //!<  8-bit signed   integer type.
typedef unsigned char           u8_t; //!<  8-bit unsigned integer type.
typedef signed short int       s16_t; //!< 16-bit signed   integer type.
typedef unsigned short int     u16_t; //!< 16-bit unsigned integer type.
typedef signed int             s32_t; //!< 32-bit signed   integer type.
typedef unsigned int           u32_t; //!< 32-bit unsigned integer type.
typedef signed long long int   s64_t; //!< 64-bit signed   integer type.
typedef unsigned long long int u64_t; //!< 64-bit unsigned integer type.
typedef float                  f32_t; //!< 32-bit floating point   type.
typedef double                 f64_t; //!< 64-bit floating point   type.

/**
 * @brief   Friendly user type declaration, for specific and intuitive use.
 */
typedef unsigned char           BYTE;  //!<  8-bit unsigned integer type.
typedef unsigned short int      WORD;  //!< 16-bit unsigned integer type.
typedef unsigned long int      DWORD;  //!< 32-bit unsigned integer type.
typedef unsigned long long int QWORD;  //!< 64-bit unsigned integer type.

typedef enum bool_t
{
   FALSE = 0,  //!< 8-bit for false
   TRUE  = 1,  //!< 8-bit for true
} __attribute__((__packed__)) bool_t;  //!< Generic boolean type

typedef enum
{
   sf_FALSE = 0xAA, //!< 8-bit for false
   sf_TRUE  = 0x55  //!< 8-bit for true
} __attribute__((__packed__)) sf_bool_t;  //!< Safety boolean type


#ifndef NULL
#define NULL ((void*)0) //!< NULL pointer
#endif

#define UNUSED(var) (void)var //!< Unused variable

/**
 * @brief Macros used to define structures and buffers.
 */
#define DEF_VAR(type, var) type var; memset(&var, (BYTE)0, sizeof(var))                                     //!< Declare a variable or structure on memory and clear the memory space.
#define DEF_BUFFER(type, buffer, elements) type buffer[elements]; memset(buffer, (BYTE)0, sizeof(buffer))   //!< Declare a buffer (vector) on memory and clear the memory space.

/**
 * @brief Macros used to alloc block memory or release them.
 */
#define CALLOC(size) calloc(size, sizeof(BYTE))                //!< Alloc memory for data size and clear itself.
#define FREE(ptr) if(ptr != NULL) { free(ptr); ptr = NULL; }   //!< Check valid pointer, release memory block and set pointer to NULL;

/**
 * @brief Macro to calc maximum value of an integer type (8, 16, 32, 64 bits).
 */
#define MIN_SIGNED_VALUE(var) (-((2 ^ (sizeof( var ) * 8)) / 2))     //!< Calc minimum value of a signed integer variable.
#define MAX_SIGNED_VALUE(var)   ((2 ^ (sizeof( var ) * 8)) / 2 - 1)  //!< Calc maximum value of a signed integer variable.
#define MAX_UNSIGNED_VALUE(var) ((2 ^ (sizeof( var ) * 8)) - 1)      //!< Calc maximum value of an unsigned integer variable.

#endif //DEFS_H

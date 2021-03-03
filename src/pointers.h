#ifndef POINTERS_H
#define POINTERS_H
#include "defs.h"

/**
 * @brief   Structure to declare an array of entries points for memory management.
 */
#pragma pack(1)
typedef struct
{
   u16_t  size;   //!< Size of block memory, at 0 position it mean number of entries point.
   void  *ptr;    //!< Pointer to memory block, for index 0 it point to itself.
} ptr_t;          //!< Structure to manage memory allocation.
#pragma pack()


/**
 * @brief   Function to initialize pointer manager structure.
 * @param   numPointers Numbers of entries points to be allocated.
 * @return  TRUE        Successful execution and initialization.
 *          FALSE       An error happened or pointers manager can't be initialized.
 */
bool_t initPointerManager( u16_t numPointers );


/**
 * @brief   Function called at exit main program. Here we can
 *          put deinitialize pointer memory for recovery allocated
 *          memory at a fault or unexpected program stop.
 */
void exitPointerManager( void );


/**
 * @brief   Function to deinitialize pointers manager.
 * @return  TRUE     Successful end of pointers manager.
 *          FALSE    Error or pointers manager is not yet initialized.
 */
bool_t endPointerManager(void);


/**
 * @brief   Function to check and verify pointers manager initialization.
 * @return  TRUE     Pointers manager was initialized.
 *          FALSE    Deinitialization error or pointers manager is not yet initialized.
 */
bool_t isInitialized(void);


/**
 * @brief   Function to check and verify pointer manager initialization.
 * @return  TRUE     Pointers manager was not yet initialized or
 *                   happened an initialization failure on last attempt.
 *          FALSE    Pointers manager already initialized.
 */
bool_t isNotInitialized(void);


/**
 * @brief   Function to allocate a block of memory and return a handler number.
 * @param   size  Size of memory to be allocated into the first free handler found.
 * @return  1..N  For a valid handler number.
 *          0     For an error or pointers manager is not yet initialized.
 */
u16_t allocMemory(u16_t size);


/**
 * @brief   Function to release a specific handler position.
 * @param   hnd   Handle number to be released.
 * @return  TRUE  If successful on release handler position.
 *          FALSE For an error or pointers manager is not yet initialized.
 */
bool_t freeMemory(u16_t hnd);


/**
 * @brief   Function to check free handler position.
 * @param   hnd   Handler number.
 * @return  TRUE  Handler available.
 *          FALSE Handler not available or pointers manager is not yet initialized.
 */
bool_t isFree( u16_t hnd );


/**
 * @brief   Function to check free handler position.
 * @param   hnd   Handler number.
 * @return  TRUE  Handler number in use.
 *          FALSE Handler available or pointer manager is not yet initialized.
 */
bool_t isNotFree( u16_t hnd );


/**
 * @brief   Function to check handler number.
 * @param   hnd   Handler number.
 * @return  TRUE  Valid handler number.
 *          FALSE Invalid handler number.
 */
bool_t isValid( u16_t hnd );


/**
 * @brief   Function to check handler number.
 * @param   hnd   Handler number.
 * @return  TRUE  Invalid handler number.
 *          FALSE Valid handler number.
 */
bool_t isNotValid( u16_t hnd );


/**
 * @brief   Function to get an address pointer at handler structure entrie.
 * @param   **ptr	Pointer to pointer where the structure address will be stored.
 * @param   hnd	Handler to get address and store into ptr.
 * @return  TRUE	Successful.
 *          FALSE	Error or pointers manager is not yet initialized.
 */
bool_t getPointerTo( ptr_t **ptr, u16_t hnd );


/**
 * @brief   Function to get allocated memory by handlers.
 * @return  1..N  Allocated memory size in bytes.
 *          0     Error or pointers manager is not yet initialized.
 */
u32_t getUsedSize( void );


/**
 * @brief   Function to get all memory allocation size including pointers manager structure.
 * @return  1..N  Allocated memory size.
 *          0     Error or pointers manager is not yet initialized.
 */
u32_t getAllUsedMemorySize( void );


/**
 * @brief   Function to get number of free handlers on pointers manager structure.
 * @return  1..N  Free handlers count.
 *          0     No free handler or pointers manager is not yet initialized.
 */
u16_t getFreeHandles( void );


/**
 * @brief   Function to get number of used handlers.
 * @return  1..N  Used handlers count.
 *          0     No handlers used or pointers manager is not yet initialized.
 */
u16_t getUsedHandles( void );


/**
 * @brief Function to copy an amount of data bytes from a buffer memory to a
 *        buffer space handled by pointers manager.
 * @param *pdata        Pointer to origin data buffer.
 * @param size_orig     Origin data buffer size.
 * @param offset_orig   Offset into origin data buffer to start copy.
 * @param data_size     Amount of data to be copied.
 * @param hnd           Destination handler number.
 * @param offset_dest   Offset into destination buffer handled by handler hnd and
 *                      where data bytes will be copied.
 * @return TRUE         For successful.
 *         FALSE        For error.
 */
bool_t memCopyTo(u8_t  *pdata,
                 u16_t size_orig,
                 u16_t offset_orig,
                 u16_t data_size,
                 u16_t hnd,
                 u16_t offset_dest);

#endif /* POINTERS_H */



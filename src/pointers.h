#ifndef POINTERS_H
#define POINTERS_H
#include "defs.h"
/**
 * @brief				Function to initialize pointer manager structure.
 * @param	numPointers	Numbers of entrie points to be allocated.
 * @return	TRUE		Successful
 * 			FALSE		Error
 */
bool_t initPointerManager( u16_t numPointers );

void exitPointerManager( void );

/**
 * @brief			Function to deinitialize pointers manager.
 * @return	TRUE	Successful
 * 			FALSE	Error or pointer manager not initialized.
 */
bool_t endPointerManager(void);

/**
 * @brief			Function to check and verify pointer manager initialization.
 * @return	TRUE	If pointer manager was initialized.
 * 			FALSE	Error or pointer manager not initialized.
 */
bool_t isInitialized(void);

/**
 * @brief			Function to check and verify pointer manager initialization.
 * @return	TRUE	If pointer manager was not initialized.
 * 			FALSE	Error or pointer manager initialized.
 */
bool_t isNotInitialized(void);

/**
 * @brief			Function to allocate a block of memory and attribute to a handler index.
 * @param	size	Size of memory to be allocated into the first free handler found.
 * @return	u16_t	1..N for valid handler number.
 *					0 for error or pointer manager not initialized.
 */
u16_t allocMemory(u16_t size);

/**
 * @brief			Function to release a specific handler position.
 * @param	u32_t	Handle number to be released and make that position available.
 * @return	TRUE    Successful to release the handler position.
 * 			FALSE	Error or pointer manager not initialized.
 */
bool_t freeMemory(u16_t hnd);

/**
 * @brief			Function to check free handler position.
 * @param	hnd		Handler number.
 * @return	TRUE	Handler available.
 * 			FALSE	Handler not available or pointer manager not initialized.
 *
 */
bool_t isFree( u16_t hnd );

/**
 * @brief			Function to check free handler position.
 * @param	hnd		Handler number.
 * @return	TRUE	Handler unavailable.
 * 			FALSE	Handler used or pointer manager not initialized.
 *
 */
bool_t isNotFree( u16_t hnd );

/**
 * @brief			Function to check if handler is valid.
 * @param	hnd		Handler number.
 * @return	TRUE	Valid handler.
 * 			FALSE	Invalid handler or pointer manager not initialized.
 */
bool_t isValid( u16_t hnd );

/**
 * @brief			Function to check if handler is valid.
 * @param	hnd		Handler number.
 * @return	TRUE	invalid handler.
 * 			FALSE	Valid handler or pointer manager not initialized.
 */
bool_t isNotValid( u16_t hnd );

/**
 * @brief			Function to get pointer to handler structure entrie.
 * @param	**ptr	Pointer to pointer where the structure address will be stored.
 * @param	  hnd	Handler of  data to get address and store into ptr.
 * @return	TRUE	Successful.
 * 			FALSE	Error or pointer manager not initialized.
 */
bool_t getPointerTo( ptr_t **ptr, u16_t hnd );

/**
 * @brief	Function to get allocated memory by handlers.
 * @return	1..N Allocated memory size in bytes.
 * 			0 Error or pointer manager not initialized.
 */
u32_t getUsedSize( void );

/**
 * @brief	Function to get all memory allocation size included pointer manager struture.
 * @return	1..N Allocated memory size.
 * 			0 Error or pointer manager not initialized.
 */
u32_t getAllUsedMemorySize( void );

/**
 * @brief	Function to get number of free handlers on pointer manager structure.
 * @return	1..N Free handler count.
 * 			0 No free handler or pointer manager not initialized.
 */
u16_t getFreeHandles( void );

/**
 * @brief	Function to get number of used handlers.
 * @return	1..N Used handlers counter.
 * 			0 No handlers used or pointer manager not initialized.
 */
u16_t getUsedHandles( void );

#endif /* POINTERS_H */



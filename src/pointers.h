#ifndef POINTERS_H
#define POINTERS_H
#include "defs.h"
/**
 * @brief			Function to initialize pointer manager structure.
 * @param	size	Numbers of handlers to be allocated.
 * @return	TRUE	Successful
 * 			FALSE	Error
 */
bool_t initPointerManager(u32_t size);

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
bool_t isPointerManagerInitialized(void);

/**
 * @brief			Function to allocate a block of memory and attribute to a handler index.
 * @param	size	Size of memory to be allocated into the first free handler found.
 * @return	u32_t	1..N for valid handler number.
 *					0 for error or pointer manager not initialized.
 */
u32_t allocMemoryHandler(u32_t size);

/**
 * @brief			Function to release a specific handler position.
 * @param	u32_t	Handle number to be released and make that position available.
 * @return	TRUE    Successful to release the handler position.
 * 			FALSE	Error or pointer manager not initialized.
 */
bool_t freeMemoryHandler(u32_t hnd);

/**
 * @brief			Function to check free handler position.
 * @param	hnd		Handler number.
 * @return	TRUE	Handler available.
 * 			FALSE	Handler not available or pointer manager not initialized.
 *
 */
bool_t isHandlerFree( u32_t hnd );

/**
 * @brief			Function to check if handler is valid.
 * @param	hnd		Handler number.
 * @return	TRUE	Valid handler.
 * 			FALSE	Invalid handler or pointer manager not initialized.
 */
bool_t isHanlderValid( u32_t hnd );

/**
 * @brief			Function to get pointer to handler structure entrie.
 * @param	**ptr	Pointer to pointer where the structure address will be stored.
 * @param	  hnd	Handler of  data to get address and store into ptr.
 * @return	TRUE	Successful.
 * 			FALSE	Error or pointer manager not initialized.
 */
bool_t getMemoryReference( ptr_t **ptr, u32_t hnd );

/**
 * @brief	Function to get allocated memory by handlers.
 * @return	1..N Allocated memory size in bytes.
 * 			0 Error or pointer manager not initialized.
 */
u32_t getMemoryUsed( void );

/**
 * @brief	Function to get all memory allocation size included pointer manager struture.
 * @return	1..N Allocated memory size.
 * 			0 Error or pointer manager not initialized.
 */
u32_t getAllMemoryUsed( void );

/**
 * @brief	Function to get number of free handlers on pointer manager structure.
 * @return	1..N Free handler count.
 * 			0 No free handler or pointer manager not initialized.
 */
u32_t getNumHandlerFree( void );

/**
 * @brief	Function to get number of used handlers.
 * @return	1..N Used handlers counter.
 * 			0 No handlers used or pointer manager not initialized.
 */
u32_t getNumHandlerUsed( void );

#endif // POINTERS_H



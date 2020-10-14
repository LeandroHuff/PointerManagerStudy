#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "pointers.h"

int main()
{
	atexit ( exitPointerManager );

    u32_t hndPointer = 0;

    if (initPointerManager(1024))
    {
        printf("pointers manager initialized.\n");
    }

    if (isPointerManagerInitialized())
    {
        printf("Successful pointers manager initialization.\n");
    }

    printf("handlers free:%u\n", getNumHandlerFree());
    printf("handlers used:%u\n", getNumHandlerUsed());
    printf("total memory used by pointers manager structure:%u\n", getMemoryUsed());

    hndPointer = allocMemoryHandler( 128 );

    if (isHanlderValid(hndPointer))
    {
        printf("checked pointer handler (%u) is valid.\n", hndPointer);
    }

    ptr_t *ptr = NULL;

    if ( getMemoryReference( &ptr, hndPointer ) )
    {
        printf("checked get pointer structure by handler.\n");
        printf("ptr size: %u\n",ptr->size);
        printf("ptr used: %d\n",ptr->used);
    }
    
    printf("handlers free:%u\n", getNumHandlerFree());
    printf("handlers used:%u\n", getNumHandlerUsed());
    printf("total memory used:%u\n", getMemoryUsed());
    printf("all memory used by pointers manager structure:%u\n", getAllMemoryUsed());

    printf("main program is running...\n");

    //endPointerManager();
    printf("pointers manager deinitialized.\n");

    return 0;
}

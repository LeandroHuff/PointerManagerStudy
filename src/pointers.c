#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "defs.h"
#include "pointers.h"

static ptr_t *ptr = NULL;

void exitPointerManager( void )
{
	printf("Exit of Pointer Manager registered by atexit() function.\n");

	if (! endPointerManager() )
	{
		printf("End of Pointer Manager Failure!\n");
	}
}

bool_t initPointerManager( u32_t size )
{
	ASSERT(size > 0);

	bool_t res = FALSE;
   if ( size > 0 )
   {
      size++;

      ASSERT(ptr == NULL);

      if (ptr != NULL)
      {
         endPointerManager();
      }

      ptr = CALLOC(size * sizeof(ptr_t));

      ASSERT(ptr != NULL);

      if (ptr != NULL)
      {
         //Save pointer data at position 0.
         ptr[0].used = TRUE;
         ptr[0].size = size;
         ptr[0].ptr = ptr;
         res = TRUE;
      }
   }
   return (res);
}

bool_t endPointerManager( void )
{
   bool_t res = FALSE;

   ASSERT(ptr != NULL);
   ASSERT(ptr[0].size > 0);

   if ((ptr != NULL) && (ptr[0].size > 0))
   {
      for (u32_t hnd = 1; hnd < ptr[0].size; hnd++)
      {
         freeMemoryHandler( hnd );
      }
      FREE(ptr);
      res = TRUE;
   }
   return (res);
}

bool_t isPointerManagerInitialized(void)
{
   bool_t res = FALSE;

   ASSERT(ptr != NULL);

   if (ptr != NULL)
   {
      res |= (ptr[0].used != FALSE);
      res |= (ptr[0].size > 0);
      res |= (ptr[0].ptr == ptr);
   }
   return ( res );
}

u32_t allocMemoryHandler( const u32_t size )
{
   u32_t hnd = 0;

   ASSERT(size > 0);
   ASSERT(ptr != NULL);

   if ((size > 0) && (ptr != NULL))
    {
        for (u32_t i = 1; i < ptr[0].size; i++)
        {
            if ( isHandlerFree(i) )
            {
                ptr[i].used = TRUE;
                ptr[i].size = size;
                ptr[i].ptr = CALLOC(size);
                if (isHanlderValid(i))
                {
                    hnd = i;
                    break;
                }
                else
                {
                    freeMemoryHandler(i);
                }
            }
        }
    }
   return (hnd);
}

bool_t freeMemoryHandler( const u32_t hnd )
{
   bool_t res = FALSE;

   ASSERT(ptr != NULL);
   ASSERT(hnd > 0);
   ASSERT(hnd < ptr[0].size);

   if ((ptr != NULL) && (hnd > 0) && (hnd < ptr[0].size))
   {
      FREE(ptr[hnd].ptr);
      ptr[hnd].size = 0;
      ptr[hnd].used = FALSE;
      res = TRUE;
   }
   return (res);
}

bool_t isHandlerFree( const u32_t hnd )
{
   bool_t res = FALSE;

   ASSERT(ptr != NULL);
   ASSERT(hnd > 0);
   ASSERT(hnd < ptr[0].size);

   if ((ptr != NULL) && (hnd > 0) && (hnd < ptr[0].size))
   {
       res |= (ptr[hnd].used == FALSE);
       res |= (ptr[hnd].size == 0);
       res |= (ptr[hnd].ptr == NULL);
   }
   return ( res );
}

bool_t isHanlderValid( const u32_t hnd )
{
    bool_t res = FALSE;

    ASSERT(ptr != NULL);
    ASSERT(hnd > 0);
    ASSERT(hnd < ptr[0].size);

    if ((ptr != NULL) && (hnd > 0) && (hnd < ptr[0].size))
    {
        res |= (ptr[hnd].used != FALSE);
        res |= (ptr[hnd].size > 0);
        res |= (ptr[hnd].ptr != NULL);
    }
    return ( res );
}

bool_t getMemoryReference( ptr_t **p, const u32_t hnd )
{
   bool_t res = FALSE;
   if (isHanlderValid(hnd))
   {
      *p = (ptr_t *)&ptr[hnd];
      res = TRUE;
   }
   return (res);
}

u32_t getMemoryUsed( void )
{
    u32_t size = 0;

    ASSERT(ptr != NULL);
    ASSERT(ptr[0].size > 0);

    if ((ptr != NULL) && (ptr[0].size > 0))
    {
        for (u32_t i = 1; i < ptr[0].size; i++)
        {
            if(isHanlderValid(i))
            {
                size += ptr[i].size;
            }
        }
    }
    return (size);
}

u32_t getAllMemoryUsed( void )
{
    u32_t size = ((ptr[0].size * sizeof(ptr[0])) + getMemoryUsed());
    return (size);
}

u32_t getNumHandlerFree( void )
{
    u32_t hnd = 0;

    ASSERT(ptr != NULL);
    ASSERT(ptr[0].size > 0);

    if ((ptr != NULL) && (ptr[0].size > 0))
    {
        for (u32_t i = 1; i < ptr[0].size; i++)
        {
            if(isHandlerFree(i))
            {
                hnd++;
            }
        }
    }
    return (hnd);
}

u32_t getNumHandlerUsed( void )
{
    u32_t hnd = 0;

    ASSERT(ptr != NULL);
    ASSERT(ptr[0].size > 0);

    if ((ptr != NULL) && (ptr[0].size > 0))
    {
        for (u32_t i = 1; i < ptr[0].size; i++)
        {
            if(isHanlderValid(i))
            {
                hnd++;
            }
        }
    }
    return (hnd);
}

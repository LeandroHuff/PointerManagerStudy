#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "defs.h"
#include "pointers.h"
#include "debug.h"

static ptr_t *ptr = NULL;

void exitPointerManager(void)
{
   if (endPointerManager() == FALSE)
   {
      ERROR("Pointer manager couldn't be free!");
   }
   else
   {
      INFO("Successful pointer manager deallocation");
   }
}

bool_t initPointerManager(u16_t numPointers)
{
   ASSERT(ptr == NULL);
   ASSERT(numPointers > 0);

   if ((numPointers == 0) || (numPointers == MAX_UNSIGNED_VALUE(numPointers)))
   {
      return (FALSE);
   }

   if (ptr != NULL)
   {
      WARNING("Pointer manager isn't free!");

      if (endPointerManager() == FALSE)
      {
         ERROR("Pointer manager couldn't be free!");
      }
   }

   numPointers++;
   ptr = CALLOC(numPointers * sizeof(ptr_t));

   ASSERT(ptr != NULL);

   if (ptr == NULL)
   {
      ERROR("Memory allocation error.");
      return (FALSE);
   }

   /* Save data at position 0 */
   ptr[0].size = numPointers; //Store number of pointers.
   ptr[0].ptr = ptr; //Point to itself.

   return (TRUE);
}

bool_t endPointerManager(void)
{
   ASSERT(ptr != NULL);
   ASSERT(ptr[0].size > 0);

   if (isNotInitialized())
   {
      return (FALSE);
   }

   bool_t res = TRUE;

   for (u16_t hnd = 1; hnd < ptr[0].size; hnd++)
   {
      if (freeMemory(hnd) == FALSE)
      {
         ERROR("Memory couldn't be free.");
         res = FALSE;
      }
   }

   FREE(ptr);

   return (res);
}

bool_t isInitialized(void)
{
   return ((ptr != NULL) && (ptr[0].size > 0) && (ptr[0].ptr == ptr));
}

bool_t isNotInitialized(void)
{
   return (!isInitialized());
}

u16_t allocMemory(const u16_t size)
{
   ASSERT(size > 0);
   ASSERT(ptr != NULL);

   u16_t hnd = 0;	//!< start with an invalid handle number (0)

   if (isNotInitialized() || (size == 0))
   {
      return (hnd);
   }

   //Search for a free handle position
   for (u16_t hnd_pos = 1; hnd_pos < ptr[0].size; hnd_pos++)
   {
      if (isFree(hnd_pos))
      {
         //Found a free handle position.

         ptr[hnd_pos].ptr = CALLOC(size);
         ASSERT(ptr[hnd_pos].ptr != NULL);

         if (ptr[hnd_pos].ptr == NULL)
         {
            DEF_BUFFER(char, msg, 128);
            snprintf(msg,
                     sizeof(msg),
                     "Memory allocation failure for handle at position %u!",
                     hnd_pos);
            ERROR(msg);
            return (hnd);
         }

         //Sucessful allocation memory,
         //store size of allocated memory and save the handle position.
         ptr[hnd_pos].size = size;
         hnd = hnd_pos;

         //Stop looping iteration and return the index number as a handle position.
         break;
      }
   }

   return (hnd);
}

bool_t freeMemory(const u16_t hnd)
{
   if (isNotValid(hnd))
   {
      return (FALSE);
   }

   FREE(ptr[hnd].ptr);
   ptr[hnd].size = 0;

   return (isFree(hnd));
}

bool_t isFree(const u16_t hnd)
{
   ASSERT(hnd > 0);
   ASSERT(hnd < ptr[0].size);

   return ((ptr[hnd].size == 0) && (ptr[hnd].ptr == NULL));
}

bool_t isNotFree(const u16_t hnd)
{
   return (!isFree(hnd));
}

bool_t isValid(const u16_t hnd)
{
   return ((hnd > 0) && (hnd < ptr[0].size));
}

bool_t isNotValid(const u16_t hnd)
{
   return (!isValid(hnd));
}

bool_t getPointerTo(ptr_t **p2p, const u16_t hnd)
{
   if ((p2p == NULL) || isNotValid(hnd))
   {
      return (FALSE);
   }

   *p2p = (ptr_t*)&ptr[hnd];

   return (TRUE);
}

u32_t getUsedSize(void)
{
   ASSERT(ptr != NULL);
   ASSERT(ptr[0].size > 0);

   u32_t size = 0;

   if (isNotInitialized())
   {
      return (size);
   }

   for (u16_t idx = 1; idx < ptr[0].size; idx++)
   {
      if (isValid(idx))
      {
         size += ptr[idx].size;
      }
   }

   return (size);
}

bool_t isPointerValid(const u16_t hnd)
{
   ASSERT(ptr != NULL);
   ASSERT(hnd > 0);
   ASSERT(hnd < ptr[0].size);

   if (isNotInitialized() || isNotValid(hnd))
   {
      return (FALSE);
   }

   //Return true for memory size greater than zero and
   //memory allocation successful attempted.
   return ((ptr[hnd].size > 0) && (ptr[hnd].ptr != NULL));
}

u32_t getAllUsedMemorySize(void)
{
   u32_t size = ((ptr[0].size * sizeof(ptr[0])) + getUsedSize());

   return (size);
}

u16_t getFreeHandles(void)
{
   ASSERT(ptr != NULL);
   ASSERT(ptr[0].size > 0);

   u16_t numHandles = 0;

   if (isNotInitialized())
   {
      return (numHandles);
   }

   for (u16_t idx = 1; idx < ptr[0].size; idx++)
   {
      if (isFree(idx))
      {
         numHandles++;
      }
   }

   return (numHandles);
}

u16_t getUsedHandles(void)
{
   ASSERT(ptr != NULL);
   ASSERT(ptr[0].size > 0);

   u16_t numHandles = 0;

   if (isNotInitialized())
   {
      return (numHandles);
   }

   for (u16_t idx = 1; idx < ptr[0].size; idx++)
   {
      if (isNotFree(idx))
      {
         numHandles++;
      }
   }

   return (numHandles);
}

bool_t memCopyTo(u8_t  *pdata,
                 u16_t size_orig,
                 u16_t offset_orig,
                 u16_t data_size,
                 u16_t hnd,
                 u16_t offset_dest)
{
   if (isNotInitialized() || isNotValid(hnd) || (pdata == NULL))
   {
      ERROR("Invalid parameter.");
      return (FALSE);
   }

   ASSERT((offset_orig + data_size) <= size_orig);
   ASSERT((offset_dest + data_size) <= ptr[hnd].size);

   if ((offset_orig + data_size) > size_orig)
   {
      ERROR("Overflow on source buffer.");
      return (FALSE);
   }


   if ((offset_dest + data_size) > ptr[hnd].size)
   {
      ERROR("Overflow on destination buffer.");
      return (FALSE);
   }

   memcpy((void*)((u8_t*)ptr[hnd].ptr + offset_dest),
          (void*)(pdata + offset_orig), data_size);

   return (TRUE);
}

/**
 * @brief   Main function entrie point here we start the pointers manager,
 *          run its interface by function calling, check the function results and
 *          print messages to console and show the programming running results.
 */

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "pointers.h"
#include "debug.h"

/**
 * @brief   Main program entrie function, here the program start its execution.
 * @param   argc Not used.
 * @param   argv Not used.
 * @return  0    Sucessful.
 *
 */
int main(int argc, char **argv)
{
   UNUSED(argc);
   UNUSED(argv);

   int result = atexit(exitPointerManager);
   if (result)
   {
      ASSERT(result);
   }

   u32_t hndPointer = 0;

   if (initPointerManager(1024))
   {
      printf("pointers manager initialized.\n");
   }

   if (isInitialized())
   {
      printf("Successful pointers manager initialization.\n");
   }

   printf("handlers free:%u\n", getFreeHandles());
   printf("handlers used:%u\n", getUsedHandles());
   printf("total memory used:%u\n", getUsedSize());
   printf("total memory used by pointers manager structure:%u\n", getAllUsedMemorySize());

   hndPointer = allocMemory(128);

   if (isValid(hndPointer))
   {
      printf("checked pointer handler (%u) is valid.\n", hndPointer);
   }

   ptr_t *ptr = NULL;

   if (getPointerTo(&ptr, hndPointer))
   {
      printf("checked get pointer structure by handler.\n");
      printf("ptr size: %u\n", ptr->size);
   }

   printf("handlers free:%u\n", getFreeHandles());
   printf("handlers used:%u\n", getUsedHandles());
   printf("total memory used:%u\n", getUsedSize());
   printf("all memory used by pointers manager structure:%u\n", getAllUsedMemorySize());

   printf("main program is running...\n");


   DEF_BUFFER(u8_t, buf_origin, 512);

   //Fill buffer with letter 'c'
   memset(buf_origin, 'c', sizeof(buf_origin));

   result = memCopyTo(buf_origin,         /*Buffer from where data gonna be copied.*/
                      sizeof(buf_origin), /*Buffer size, note that it is greater than destine buffer (128) at line 48.*/
                      0,                  /*Offset of origin buffer.*/
                      sizeof(buf_origin), /*Amount data size to be copied, it is an error because is greater than destine.*/
                      hndPointer,         /*Handle number where the data gonna be copied.*/
                      0);                 /*Offset of destine buffer.*/

   ASSERT(result == TRUE);

   /*
    if (endPointerManager() == FALSE)
    {
       printf("End pointer manager failure.\n");
    }
    else
    {
       printf("Succesful end pointer manager.\n");
    }
    */
   printf("pointers manager deinitialized.\n");

   return 0;
}

/*
 * debug.h
 *
 *  Created on: 4 de nov de 2020
 *      Author: leandro
 */

#ifndef SRC_DEBUG_H_
#define SRC_DEBUG_H_

#include <stdio.h>
#include <assert.h>
#include "defs.h"

/**
 * @brief DEBUG macro is a set of debug levels that can be enabled for a
 *        specific debug assert and logger behavior to catch failures and trace
 *        program data execution.
 *
 *        Each debug level line should be enabled (uncommented) only one of them
 *        and remains the others disabled by doing them as a commented line.
 *
 *        if no one are enabled, only logger message are sent to console stderr or stdout.
 */
#ifdef DEBUG
//#define DEBUG0	1  //!< Assert send a log message to debug console and continue running program.
//#define DEBUG1	1  //!< Assert send a log message to debug console and stop running program.
#define DEBUG2	1  //!< Assert abort program execution and print programm trace information.
#endif

/**
 * Log information messages
 */
typedef enum
{
   LOG,
   INF,
   WRN,
   ERR,
   BAD
} eLog_t;

void Logger(const eLog_t type, const char *status, const char *text, const char *file, const int line, const char *function);

#define INFO(msg)    Logger(INF,    "INFO:", msg, __FILE__, __LINE__, __ASSERT_FUNCTION)
#define LOG(msg)     Logger(LOG,     "LOG:", msg, __FILE__, __LINE__, __ASSERT_FUNCTION)
#define WARNING(msg) Logger(WRN, "WARNING:", msg, __FILE__, __LINE__, __ASSERT_FUNCTION)
#define ERROR(msg)   Logger(ERR,   "ERROR:", msg, __FILE__, __LINE__, __ASSERT_FUNCTION)
#define FATAL(msg)   Logger(BAD,   "FATAL:", msg, __FILE__, __LINE__, __ASSERT_FUNCTION)

/**
 * @brief Macro to use assert diretive on debug mode.
 */
#if defined (DEBUG2)	//!< Enable assert trace fault

   #define ASSERT(x) assert(x)

#elif defined (DEBUG1)	//!< Print to console for debug and exit

   #define ASSERT(x) \
   if(!(x)) \
   { \
      ERROR(""); \
      exit (EXIT_FAILURE); \
   }

#elif defined (DEBUG0)	//!< Print to console for debug and continue running

   #define ASSERT(x) \
   if(!(x)) \
   { \
      ERROR(""); \
   }

#else //!< Do nothing

   #define ASSERT(x) (void)0

#endif

#endif /* SRC_DEBUG_H_ */

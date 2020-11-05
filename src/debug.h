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

#ifdef DEBUG
//#define DEBUG0	1	//!< Disabled debug check.
//#define DEBUG1	1	//!< Parameters check.
//#define DEBUG2	1	//!< Parameters and variable value check.
//#define DEBUG3	1	//!< Parameters and variable value check.
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
#if defined (DEBUG3)	//!< Enable assert directive

	#define ASSERT(x) assert(x)

#elif defined (DEBUG2)	//!< Send to stderr for debug and exit

	#define ASSERT(x) \
	if (!(x)) \
	{ \
		fprintf(stderr, "ERROR: File:%s  Line:%d  Function:%s\n", __FILE__, __LINE__, __ASSERT_FUNCTION ); \
		fflush( stderr ); \
		exit(EXIT_FAILURE); \
	}

#elif defined (DEBUG1)	//!< Print to console for debug and exit

	#define ASSERT(x) \
	if(! (x)) \
	{ \
		printf("ERROR: File:%s  Line:%d  Function:%s\n", __FILE__, __LINE__, __ASSERT_FUNCTION); \
		exit (EXIT_FAILURE); \
	}

#elif defined (DEBUG0)	//!< Print to console for debug and continue running

	#define ASSERT(x) \
	if(! (x)) \
	{ \
		printf("ERROR: File:%s  Line:%d  Function:%s\n", __FILE__, __LINE__, __ASSERT_FUNCTION); \
	}

#else

	#define ASSERT(x) (void)0

#endif

#endif /* SRC_DEBUG_H_ */

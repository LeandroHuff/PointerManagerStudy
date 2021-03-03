/*
 * debug.c
 *
 *  Created on: 4 de nov de 2020
 *      Author: leandro
 */
#include <stdio.h>
#include "defs.h"
#include "debug.h"

/**
 * @brief Macro to send a log debug message to stderr.
 */

void Logger(const eLog_t type,      //!< Log type can be LOG, INF, WRN, ERR or BAD.
            const char *status,     //!< Status "INFO", "LOG", "WARNING", "ERROR" or "FATAL" to be added to log message.
            const char *text,       //!< Log text message.
            const char *file,       //!< Source file name where the message log function was called.
            const int line,         //!< Source file line where the message log function was called.
            const char *function)   //!< Source code function where the message log function was called.
{
	fprintf((type == INF) ? stdout : stderr,
	      "%s %s - File:%s - Line:%d - Function:%s\n",
	      status, text, file, line, function);
}

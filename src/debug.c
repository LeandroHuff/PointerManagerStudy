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

void Logger(const eLog_t type, const char *status, const char *text, const char *file, const int line, const char *function)
{
	fprintf((type == INF) ? stdout : stderr, "%s %s - File:%s - Line:%d - Function:%s\n", status, text, file, line, function);
}

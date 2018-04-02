/*******************************************************************************
*  Copyright (c) 1998 MFC Forum
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* Module Name:
*
* Revision History:
*
* Date        Ver Name                    Description
* ----------  --- --------------------- -----------------------------------------
* 07-Jun-2016 0.1 Youngho Kim             Created
* ----------  --- --------------------- -----------------------------------------
*
* DESCRIPTION:
*
*  $Author:
*  $LastChangedBy:
*  $Date:
*  $Revision: 2949 $
*  $Id:
*  $HeadURL:
*******************************************************************************/
#ifndef LOG_UTILS_H_
#define LOG_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/**
 * This is a prototype of log handler function.
 * @param fmt Message format (used in the same way as with @a printf()).
 */
typedef void (*log_function)(char* fmt, ...);

/**@name Log handlers
 * Contain links to the current log handlers. Normally these links should not
 * be used directly.
 * @{
 */
/**
 * Contains link to the current handler of @a info log messages. Normally
 * #log_info() should be used instead.
 */
extern log_function log_rtspHandler;
/**
 * Contains link to the current handler of @a info log messages. Normally
 * #log_info() should be used instead.
 */
extern log_function log_infoHandler;
/**
 * Contains link to the current handler of @a debug log messages. Normally
 * #log_debug() should be used instead.
 */
extern log_function log_debugHandler;
/**
 * Contains link to the current handler of @a warning log messages. Normally
 * #log_warning() should be used instead.
 */
extern log_function log_warningHandler;
/**
 * Contains link to the current handler of @a error log messages. Normally
 * #log_error() should be used instead.
 */
extern log_function log_errorHandler;
/** @} */

/**@name Logging utilities
 * @{*/
// A trick with define is done in order to auto-add filename and line number
// into the log message.

/**
 * Prints @a info message to the configured output.
 * Automatically adds filename and string number of the place from where the log
 * was written.
 *
 * @param fmt Message format (used in the same way as with @a printf()).
 */
#define log_rtsp(fmt, ...) (*log_rtspHandler)((char*)"%s(%d): " fmt, __FILE__, \
 __LINE__, ## __VA_ARGS__)

/**
 * Prints @a info message to the configured output.
 * Automatically adds filename and string number of the place from where the log
 * was written.
 *
 * @param fmt Message format (used in the same way as with @a printf()).
 */
#define log_info(fmt, ...) (*log_infoHandler)((char*)"%s(%d): " fmt, __FILE__, \
 __LINE__, ## __VA_ARGS__)

/**
 * Prints @a debug message to the configured output.
 * Automatically adds filename and string number of the place from where the log
 * was written.
 *
 * @param fmt Message format (used in the same way as with @a printf()).
 */
#define log_debug(fmt, ...) (*log_debugHandler)((char*)"%s(%d): " fmt, __FILE__, \
 __LINE__, ## __VA_ARGS__)

/**
 * Prints @a warning message to the configured output.
 * Automatically adds filename and string number of the place from where the log
 * was written.
 *
 * @param fmt Message format (used in the same way as with @a printf()).
 */
#define log_warning(fmt, ...) (*log_warningHandler)((char*)"%s(%d): " fmt, __FILE__, \
 __LINE__, ## __VA_ARGS__)

/**
 * Prints @a error message to the configured output.
 * Automatically adds filename and string number of the place from where the log
 * was written.
 *
 * @param fmt Message format (used in the same way as with @a printf()).
 */
#define log_error(fmt, ...) (*log_errorHandler)((char*)"%s(%d): " fmt, __FILE__, \
 __LINE__, ## __VA_ARGS__)
/**@}*/

/**
 * Defines possible log levels.
 */
typedef enum
{
	/** Info log level. */
	LOG_LEVEL_INFO,
	/** Debug log level. */
	LOG_LEVEL_DEBUG,
	/** Warning log level. */
	LOG_LEVEL_WARNING,
	/** Error log level. */
	LOG_LEVEL_ERROR,
	/** Info log level. */
	LOG_LEVEL_RTSP,
	/** 'No' log level. */
	LOG_LEVEL_NO
} LOG_LEVEL;

/**
 * Switches library to use @a syslog for handling messages.
 *
 * @param facility Facility tells syslog who issued the message. See
 * documentation of @a syslog for more information.
 */
void log_useSyslog(int facility);

/**
 * Switches library to use @a printf for handling messages.
 */
void log_usePrintf();

void log_closeSyslog();

/**
 * Sets the minimum priority level of the messages which will be processed.
 *
 * @param level Priority level:
 *              - #LOG_LEVEL_DEBUG - All messages will be printed;
 *              - #LOG_LEVEL_WARNING - Only warning and error messages will be
 *                                     printed;
 *              - #LOG_LEVEL_ERROR - Only error messages are printed;
 *              - #LOG_LEVEL_NO - Nothing is printed at all.
 */
void log_setLevel(LOG_LEVEL level);

#ifdef __cplusplus
}
#endif

#endif /* LOG_UTILS_H_ */

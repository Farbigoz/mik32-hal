#ifndef HAL_TYPES_H
#define HAL_TYPES_H

#include <stdbool.h>
#include <inttypes.h>

#ifdef __cplusplus
#define __RO		volatile             /*!< Defines 'read only' permissions */
#else
#define __RO		volatile const       /*!< Defines 'read only' permissions */
#endif
#define __WO			volatile             /*!< Defines 'write only' permissions */
#define __RW			volatile             /*!< Defines 'read / write' permissions */


#ifndef __weak
#define __weak   __attribute__((weak))
#endif /* __weak */

#ifndef NULL
#define NULL ((void *)0)
#endif

#endif
#ifndef INC_TYPES_H
#define INC_TYPES_H

#include <stdint.h>
#include <stdlib.h>

#ifndef null_
#    define null_ 0
#endif

#ifndef TRUE
#    define TRUE 1U
#endif

#ifndef FALSE
#    define FALSE 0
#endif

typedef enum 
{
	un_init_ = -2,
	error_,
	ok_,
	failure_
}
status;

typedef enum
{
	false_,
	true_
} boolean;

#endif /* INC_TYPES_H */

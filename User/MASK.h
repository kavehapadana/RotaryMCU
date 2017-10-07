#include "stdint.h" 

#define setMask(data, index) 		(data |= 1 << index)
#define unsetMask(data, index) 	(data &= ~(1 << index))
#define ToggleMask(data, index) (data ^= 1 << index)
#define getMask(data, index) 		((data >> index) & 1)

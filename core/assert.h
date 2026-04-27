#ifndef _ASSERT_H_
#define _ASSERT_H_
#include "../defines.h"

void assert(b8 result,char* message_failure,char* message_success);

#define assert_failure(result,message) assert(result,message,NULL);

#endif

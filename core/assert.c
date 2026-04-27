#include "assert.h"

void assert(b8 result,char* message_failure,char* message_success)
{
  if(result!=true)
  {
    printf("%s \n",message_failure);
    exit(EXIT_FAILURE);
  }
  if(message_success!=NULL)
  {
    printf("%s \n",message_success);
  }
}

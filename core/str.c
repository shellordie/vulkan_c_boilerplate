#include "str.h"

u32 str_len(char* string)
{
  return strlen(string);
}

b8 str_cmp(char* str_1,char* str_2)
{
  return strcmp(str_1,str_2)==0;
}

void str_test()
{
  char* string="charles";
  assert_failure(str_len(string)==7,"string is not seven");
  printf("string len=%d \n",str_len(string));
  char* str="charles";
  assert_failure(str_cmp(string,str)==true,"string dont match");
  printf("string cmp=%d \n",str_cmp(string,str));

  assert_failure(1!=1,"break here for test");
}



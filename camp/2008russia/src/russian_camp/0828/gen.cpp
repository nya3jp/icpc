#include <stdio.h>
#include <stdlib.h>

int main() 
{
  for(int i = 0; i < 4000; i++)
    printf("%c", (char)(rand()%26+'a'));
  puts("");
  return 0;
}

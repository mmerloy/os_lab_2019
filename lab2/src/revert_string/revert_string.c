#include "revert_string.h"
#include <string.h>
#include <stdlib.h>
#include "revert_string.h"

void RevertString(char *str)
{
	// your code here
   char *c=malloc(sizeof(char)*(strlen(str)+1));
   for ( int i=0, j=strlen(str)-1;i<j;i++,j--)
    {
     *c=str[i];
     str[i]=str[j];
     str[j]=*c;
    }
}


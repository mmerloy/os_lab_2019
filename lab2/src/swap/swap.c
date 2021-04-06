#include "swap.h"

void Swap(char *left, char *right)
{
	
  // ваш код здесь
  char *c;
  *c=*right;
  right=left;
  *left=*c;
}

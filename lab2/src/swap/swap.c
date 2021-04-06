#include "swap.h"

void Swap(char *left, char *right)
{
	
  // ваш код здесь

  char temp =*right;
  *right=*left;
  *left=temp;
}

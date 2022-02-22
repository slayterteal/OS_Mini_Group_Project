#include <stdio.h>
#include "../WordServices.h"

//test for lowercase conversion
int main()
{
	char str[5] = "TeSt";
	toLowerStr(str, 5);
	printf("%s", str);
	return 0;
}

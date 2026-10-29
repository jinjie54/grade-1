#include<stdio.h>

int main(void) {
	int ch = getchar();
	while(getchar() != '\n');
	putchar(ch);
	putchar('\n');
	putchar(10);  			//10ÊÇ\n 
	putchar(32);
	putchar(66);
	printf("\nhahahdsh");
	putchar(11);
	putchar(-1);
	putchar(10);
	putchar(-1);
	
	return 0;
}

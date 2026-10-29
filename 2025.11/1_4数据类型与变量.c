#include<stdio.h>

int main(void)
{
	char ch1 = 'A';			//×Ö·û³£Á¿
	char ch2 = 65;			//ASCIIÖµ
	unsigned char uch = 200;//ÎÞ·ûºÅ×Ö·û
	
	printf("×Ö·û£º%c, ASCIIÖµ£º%d\n", ch1, ch1);
	printf("×Ö·û£º%c, ASCIIÖµ£º%d\n", ch2, ch2);
	printf("ÎÞ·ûºÅ×Ö·û£º%u\n", uch); 

	return 0;
}

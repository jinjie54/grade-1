#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

int main(void)
{
	FILE *file = fopen ("测试文件文本.txt", "r");
	if (file == NULL) {
		printf("\n打开文件夹失败！\n错误号:%d\n错误信息:%s\n", errno, strerror(errno));
		perror("fopen失败");
		return 1;
	} else {
		printf("\n文件打开成功!\n");
	}
	
//	SetConsoleOutputCP(65001);
//	char tiqu[256];
//	fgets(tiqu, sizeof(tiqu), file);				根据前面知识突然想到的读取 
//	
//	printf("%s", tiqu);
	
	system("notepad 测试文件文本.txt");
	
	fclose(file);

	return 0;
}

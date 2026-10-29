#include<stdio.h>
#include<string.h>//数组比较 
#include<stdlib.h>//malloc要用 

struct Contact {
	char name[20];
	char number[15];
};

//struct Contact book[100];//太low了 

int main(void)
{
	int length;//通讯录长度 
	int select;//用来选择的变量 
	int i;//用来输出的变量
	int j, k, l;//用来删除的变量 
	char name[20];//同上 
	int count = 0;//记录联系人数量 
	int ch;//好习惯！=EOF使程序结束且返回-1 
//	struct Contact book[1];//前面的已经创建了100个变量了，这里会改变变量数 
	struct Contact *book = NULL;
	
	printf("请输入通讯录长度：");
	scanf("%d", &length);//设置长度 
	
	book = /*(struct Contact *)//c语言可以不用转换这里的void可以转换成任意类型*/malloc(length * sizeof(struct Contact));
	
	while (book == NULL) {
		printf("内存申请失败！\n");
		printf("请重新输入通讯录长度：");
	scanf("%d", &length); 
	
	book = malloc(length * sizeof(struct Contact));
	}
	
	do {
		printf("\n\n""==== 通讯录 ====\n"
			"1. 添加联系人\n"
			"2. 查看所有联系人\n"
			"3. 删除联系人\n"
			"4. 退出\n"
			"请选择：");
//		while (getchar() != '\n');//清空缓存区，读取直到换行符 //这样的话第一次输入必须是回车才行 
		
		if (scanf("%d", &select) != 1/*主选择语句*/) {
			while ((ch = getchar()) != '\n' && ch != EOF);
			printf("请输入有效值！\n");
			continue;//跳到最后再进行下一轮循环 
		}
		
		switch (select)
		{
			case 1: {
				if (count == length) {
					int new_length;
					char choice[10] = {0};//选择扩容 
					printf("\n达到输入上限！\n\n请选择是否扩容（是/否）：");
					while (getchar() != '\n');
					scanf("%9s", choice);
					while (getchar() != '\n');
					if (strcmp(choice, "否") == 0) {
						break;
					}
					
					while (strcmp(choice, "否") != 0) {
						if (strcmp(choice, "是") == 0) {
							
							printf("\n请输入新长度：");
							scanf("%d", &new_length);
							if (new_length <= length) {
								break;
							}
							struct Contact *new_book = realloc(book, new_length * sizeof(struct Contact));
							if (new_book) {
								book = new_book;
								length = new_length;
								printf("\n扩容成功！\n");
								break;
							} else {
								printf("\n扩容失败！\n");
							}
							
						} else {
							printf("\n输入失败，请输入正确值：");
							scanf("%9s", choice);
						}
					}
					break;
				}
				printf("\n请输入姓名：");
				scanf("%19s", book[count].name);//简单的输入和计数 
				printf("\n请输入联系电话：");
				scanf("%14s", book[count].number);
				count++;
				break;
			}
			case 2: {
				i = 0;
				if (count == 0) {//特殊情况 
					printf("\n                 您还没有联系人，快去添加一个吧！\n");
					break;
				}
				while (i != count) {//遍历输出 
					printf("\n                 === 联系人%d ===\n", i + 1);
					printf("                 姓名：%s\n"
						"                 电话：%s\n", book[i].name, book[i].number);
					i++;
				}
				break;
			}
			case 3: {
				printf("\n请输入您要删除的连系人：");
				scanf("%s", name);
				l = 1;
				for (j = 0; j < count; ++j) {
					if (strcmp(book[j].name, name) == 0) {//指针指的值要用strcmp 
						l = 0;
						for (k = j; k < count - 1; ++k) {//交换count-1次 
							strcpy(book[k].name, book[k + 1].name);//数组名不是变量，是常量指针！！ 
							strcpy(book[k].number, book[k + 1].number);//头文件string 
						}
						if (k == count - 1) {
//							strcpy(book[k].name,NULL);//strcpy传入NULL会让程序会立即崩溃！！！ 
//							strcpy(book[k].number,NULL);
							book[k].name[0] = '\0';
							printf("删除成功！\n");
							count--;
							break;//删除一个就退出循环 
						}
					}
				}
				if (l != 0) {
							printf("\n未找到联系人！\n");
						}
				break;//case 3:用了一天的空余时间也是终于搞完了 
			}
			case 4: {
				break;//不会输出下面那一句了 
			}
			default : {
				printf("Are you kidding me ?\n");
				break;
			}
		}
	} while (select != 4);
	FILE *fp = fopen("通讯录.txt", "wb");
	if (fp == NULL) {
		perror("错误原因：");
	}
	unsigned char bom[] = {0xEF, 0xBB, 0xBF};
	fwrite(bom, 1, 3, fp);
	i = 0;
	if (count == 0) {//特殊情况 
		fprintf(fp, "\n                 No	one !\n");
	}
	while (i != count) {//遍历输出 
		fprintf(fp, "\n                 === link human%d ===\n", i + 1);
		fprintf(fp, "                 name: %s\n"
			"                 Telephone number: %s\n", book[i].name, book[i].number);
		i++;
	}//复制上面的 
	fclose(fp);
	free (book);
	system ("notepad 通讯录.txt");
	return 0;
}

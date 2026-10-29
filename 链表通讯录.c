#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Lu {
	char name[20];
	char number[12];
	struct Lu *next;
};

void Set (struct Lu **head, const char *name, const char *number);
void See (struct Lu **head, const char *name_see);
void See_all (struct Lu **head);
void Detele (struct Lu **head, const char *name);


int main(void)
{
	struct Lu *head = NULL;
	int choose;
	char name[20], number[12];
	char name_see[20];
	//加载之前的数据 
	FILE *fp_preve = fopen("链表通讯录.txt", "r");
	if (fp_preve == NULL) {
		perror("error:");
		return 1;
	} else {
		char preve_name[20], preve_number[12], line[100];
		printf("检测到历史数据，正在加载...\n");
		while (fgets(line, sizeof(line), fp_preve) != NULL) {
			if (strstr(line, "姓名:") != NULL) {
				sscanf(line, "姓名:%s", preve_name);
			} else if (strstr(line, "电话:") != NULL) {
			sscanf(line, "电话:%s", preve_number);
			
			Set (&head, preve_name, preve_number);
			}
		}
		printf("历史数据加载成功！\n");
	}
	
	do {// 选择
		printf("\n\n""==== 通讯录 ====\n"
			"1. 添加联系人\n"
			"2. 查看联系人\n"
			"3. 删除联系人\n"
			"4. 退出\n"
			"请选择：");
		scanf("%d", &choose);
		
		switch (choose) {
			case 1: {
				printf("\n请输入新建的姓名:");
				scanf("%s", name);
				printf("\n请输入新建的电话:");
				scanf("%s", number);
				Set (&head, name, number);
				break;
			}
			case 2: {
				char see[9];
				printf("您想要全部查看还是指定查看？\n");
				scanf("%8s", see);
				if (strcmp(see, "指定查看") == 0) {
					printf("\n请输要查看的入姓名:");
					scanf("%s", name_see);
					See (&head, name_see);
				} else if (strcmp(see, "全部查看") == 0) {
					See_all(&head);
				} else {
					printf("输入错误！\n");
				}
				break;
			}
			case 3: {
				char name_detele[20];
				printf("请输入要删除的姓名:");
				scanf("%s", name_detele);
				Detele (&head, name_detele);
				break;
			}
			case 4: {
				printf("退出程序！\n");
				break;
			}
			default : {
				printf("请输入有效值！\n");
				break;
			}
		}
	} while (choose != 4);
	//放到文件里去 
	FILE *fp = fopen("链表通讯录.txt", "w+");
	if (fp == NULL) {
		perror("创建失败！error:");
	} else {
		printf("创建成功！\n");
	}
	struct Lu *current_1 = head;//不会改变head
	while (current_1 != NULL) {
		fprintf(fp, "\n姓名:%s\n电话:%s", current_1->name, current_1->number);
		current_1 = current_1->next;
	}
	fclose(fp);
	
	//释放内存
	struct Lu *current = head;
	while (current != NULL) {
		struct Lu *temp = current;
		current = current->next;
		free(temp);
	}
	system("notepad 链表通讯录.txt");
	
	return 0;
}

//添加数据
void Set (struct Lu **head, const char *name, const char *number) {
	//创建新节点
	struct Lu *new_ = (struct Lu *)malloc(sizeof(struct Lu)); 
	if (new_ == NULL) {
		printf("创建失败！\n");
		return;
	}
	//复制数据
	strcpy(new_->name, name);
	strcpy(new_->number, number);
	new_->next = NULL;
	
	//链接上
	if(*head == NULL) {
		*head = new_;
	} else {
		struct Lu *current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
	current->next = new_;
	}
	printf("添加成功！\n");
}

//查看数据
void See (struct Lu **head, const char *name_see) {
	struct Lu *current = *head;
	while (current != NULL) {
		if (strcmp(current->name, name_see) == 0) {
			printf("\nname:%s\n"
					"number:%s\n", current->name, current->number);
		break;
		}
		current = current->next;
	}
}
void See_all (struct Lu **head) {
	struct Lu *current = *head;
	while (current != NULL) {
		printf("\n姓名:%s\n"
				"电话:%s\n", current->name, current->number);
		current = current->next;
	}
}

//删除数据
void Detele (struct Lu **head, const char *name_detele) {
	struct Lu *preve = NULL;
	struct Lu *current = *head;
	while (current != NULL) {
		if (strcmp(current->name, name_detele) == 0) {
			if (preve == NULL) {
				*head = current->next;
			} else {
				preve->next = current->next;
			}
			struct Lu *temp = current;
			current = current->next;
			free(temp);
			printf("删除成功！\n");
			break;
		} else {
		preve = current;
		current = current->next;
		}
	}
} 

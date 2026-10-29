//这个文件放所有的函数的具体实现代码

#include "contact_list.h" //包含你自己的头文件

//添加联系人
void Set(struct Lu **head, const char *name, const char *number) {
	//添加新节点
	struct Lu *new_point = (struct Lu *)malloc(sizeof(struct Lu));
	if (new_point == NULL) {
		printf("内存分配失败！\n");
		return;
	}
	strcpy(new_point->name, name);
	strcpy(new_point->number, number);
	new_point->next = NULL;
	
	//添加到链表里
	if (*head == NULL) {
		*head = new_point;
	} else {
		struct Lu *current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = new_point;
	}
	printf("添加成功！\n");
}

//查看联系人
void See(struct Lu **head) {
	char see_choice[15];
	printf("\n您想查看指定联系人还是查看全部联系人？\n");
	scanf("%14s", see_choice);
	if (strcmp(see_choice, "查看指定联系人") == 0) {
		if (*head == NULL) {
			printf("\n您还没有联系人，快去添加一个吧！\n");
		} else {
			int check = 0;
			char see_name[20];
			printf("\n请输入要查看的联系人姓名:");
			scanf("%19s", see_name);
			struct Lu *current = *head;
			while (current != NULL) {
				if (strcmp(current->name, see_name) == 0) {
				printf("\n姓名:%s\n"
						"电话:%s", current->name, current->number);
						check = 1;
						break;
				}
				current = current->next;
			}
			if (check) {
				printf("\n查找完成！\n");
			} else {
				printf("\n未找到联系人！\n");
			}
		}
	} else if(strcmp(see_choice, "查看全部联系人") == 0) {
		struct Lu *current = *head;
		if (current == NULL) {
			printf("\n您还没有联系人，快去添加一个吧！\n");
		} else {
			while (current != NULL) {
				printf("\n姓名:%s\n"
						"电话:%s\n", current->name, current->number);
				current = current->next;
			}
		}
	}
}

//删除联系人
void Delete(struct Lu **head, const char *name) {
	struct Lu *current = *head;
	struct Lu *preve = NULL;
	while (current != NULL) {
		if (strcmp(current->name, name) == 0) {
			if (preve  == NULL) {
				//删除的是头节点
				*head = current->next; 
			} else {
				preve->next = current->next;
			}
			free(current);
			printf("\n删除成功！\n");
			return;
		}
		preve = current;
		current = current->next;
	}
	printf("未找到要删除的联系人：%s", name);
}

// 保存到文件
void SaveToFile(struct Lu *head, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("文件保存失败！\n");
        return;
    }
    
    struct Lu *current = head;
    while (current != NULL) {
        fprintf(fp, "姓名:%s\n电话:%s\n", current->name, current->number);
        current = current->next;
    }
    
    fclose(fp);
    printf("数据已保存到文件！\n");
}

// 从文件加载
void LoadFromFile(struct Lu **head, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return;  // 文件不存在是正常的，第一次运行时会这样
    }
    
    char line[100];
    char name[20] = "", number[12] = "";
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, "姓名:") != NULL) {
            sscanf(line, "姓名:%19s", name);  // %19s防止缓冲区溢出
        } else if (strstr(line, "电话:") != NULL) {
            sscanf(line, "电话:%11s", number);
            // 当读取到电话时，一个完整联系人就读取完了
            Set(head, name, number);
        }
    }
    printf("\n加载完成！\n");
    
    fclose(fp);
}

// 释放链表内存
void FreeList(struct Lu *head) {
    struct Lu *current = head;
    while (current != NULL) {
        struct Lu *temp = current;
        current = current->next;
        free(temp);
    }
}

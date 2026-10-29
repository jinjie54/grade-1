//这个文件只放声明，像一本书的目录。

#ifndef CONTACT_LIST_H//防止头文件被重复包含 
#define CINTACT_LIST_H

//包含系统头文件
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//定义结构体 
struct Lu {
	char name[20];
	char number[12];
	struct Lu *next;
};

//函数申明 - 告诉编译器有那些函数可用
void Set(struct Lu **head, const char *name, const char *number);
void See(struct Lu **head);
void Delete(struct Lu **head, const char *name);
void SaveToFile(struct Lu *head, const char *filename);
void LoadFromFile(struct Lu **head, const char *filename);
void FreeList(struct Lu *head);

#endif

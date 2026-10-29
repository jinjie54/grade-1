#include "contact_list.h"//包含你自己的头文件
int main(void) {
	struct Lu *head = NULL;
	
	//程序启动时加载数据
	LoadFromFile(&head, "contact_list.txt");
	
	int choice;
	
	do {
		printf("\n==== 通讯录管理系统 ====\n");
        printf("1. 添加联系人\n");
        printf("2. 查看联系人\n");
        printf("3. 删除联系人\n");
        printf("4. 退出程序\n");
        printf("请选择：");
        scanf("%d", &choice);
        
		switch (choice) {
			case 1: {
                char name[20], number[12];
                printf("请输入姓名：");
                scanf("%19s", name);
                printf("请输入电话：");
                scanf("%11s", number);
                Set(&head, name, number);
                break;
            }
            case 2: {
                See(&head);
                break;
            }
            case 3: {
                char name_delete[20];
                printf("请输入要删除的姓名：");
                scanf("%19s", name_delete);
                Delete(&head, name_delete);
                break;
            }
            case 4: {
                // 退出前保存数据并释放内存
                SaveToFile(head, "contact_list.txt");
                FreeList(head);
                printf("谢谢使用！数据已保存。\n");
                break;
            }
            default: {
                printf("无效选择，请重新输入！\n");
                break;
            }
		}
	} while (choice != 4);
	system("notepad contact_list.txt");
	
	return 0;
}

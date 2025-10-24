#pragma once
#include <stdio.h>
#include <Windows.h>


#include "Headers/Student.h"
#include "Headers/file.h"
#include "Headers/stringTool.h"



const char* defaultPath = "students.b";

const char* logo = "Designed .\n"
"    ██████  ██    ██     ███████ ███████ ███████ ██   ██ ████████ ██████      \n"
"    ██   ██  ██  ██      ██      ██      ██      ██   ██    ██         ██      \n"
"    ██████    ████       █████   █████   ███████ ███████    ██     █████       \n"
"    ██   ██    ██        ██      ██           ██ ██   ██    ██         ██      \n"
"    ██████     ██        ██      ███████ ███████ ██   ██    ██    ██████      \n "
"                                                                              ";
            

//
//typedef struct{
//	char start[35];//行首字符串
//	char end[35];//行尾字符串
//	char side[5];//侧边字符串
//	char separator;//分隔符
//
//	int length;//整行最大长度
//} StrFormat;



void ShowList();//显示学生列表
void init();//初始化函数

char cmd[256];
//StrFormat mainFormat;

int main() {
	printf("\n\n");
	printf("%s\n", logo);
	Sleep(1000);
	printf("Welcome to the Student Information Management System!\n");

	//Sleep(10000);

	printf("%d \n", isExist(defaultPath));
	
	while (1)
	{
		scanf_s("%s", cmd, sizeof(cmd));//获取用户输入的命令

		if (startWith(cmd , "wt")) {
		

			Node node;

			//short id;//学号
			//char name[35];//姓名
			//int age;//年龄
			//char sex;
			//char address[50];//地址
			//char phone[12];//电话
			//char email[30];//邮箱
			//int Cscore[5];//c语言成绩
			Student student = {1,"牛逼", 20, 'M', "Some Address", "1234567890", "example@example.com", 50};
			node.student = student;
			node.next = NULL;

			writeStudentFile(defaultPath, &node);
			printf("write Test command recognized.\n");
		}

		if (startWith(cmd , "rl")) {
			Node* head = readStudentFile(defaultPath);
			if (head == NULL) {
				printf("No student records found.\n");
			}
			else {
				printf("Student records loaded successfully.\n");
			}
		}
		if (startWith(cmd , "sl")) {
			ShowList();
		}
		if (startWith(cmd , "exit")) {
			printf("Exiting the system. Goodbye!\n");
			break;
		}

		if (startWith(cmd, "add")) {
			char* token;
			char* ptr = NULL;
			char sep[] = ",";
			/* 获取第一个子字符串 */
			token = strtok_s(cmd, sep, &ptr);//相较于strtok()函数，strtok_s函数需要用户传入一个指针，用于函数内部判断从哪里开始处理字符串

			
			/* 继续获取其他的子字符串 */
			for (int i = 0; token != NULL; i++) {
				printf("%s\n", token);
				/*switch(i) {
					case 1:
						
						break;
					case 2:

						break;
					case 3:

						break;

					default:
						printf("Unknown argument: %s\n", token);
						break;
				}*/



				token = strtok_s(NULL, sep, &ptr);
			}



		}

	}

	return 0;
}







void ShowList() {
	// This function would typically display the list of students.
	// For now, it is left empty as a placeholder.
	printf("Displaying student list...\n");

	Node* head = readStudentFile(defaultPath);
	if (head) {
		Node* current = head;
		while (current) {
			printf("Name: %s, Age: %d, Sex: %c\n", current->student.name, current->student.age, current->student.sex);

			current = current->next;
		}
	}
	else {
		printf("No students found.\n");
	}

}


void init() {
	//setup the format
	//mainFormat.length = 50;
	//strcpy(mainFormat.start, "--------------------");
	//strcpy(mainFormat.end, "--------------------");
	//strcpy(mainFormat.side, "|");

	//mainFormat.separator = '-';




}
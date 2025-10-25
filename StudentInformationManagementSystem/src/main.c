#pragma once
#include <stdio.h>
#include <Windows.h>


#include "Headers/common.h"
#include "Headers/stringTool.h"
#include "Headers/time.h"



//const char* defaultPath = "students.b";

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


const char* welcomeMsg = "Welcome to the Student Information Management System!\n";
const char* helpMsg = "Available commands:\n"
"1. add,<id>,<name>,<age>,<sex>,<address>,<phone>,<email>,<Cscore>添加学生\n"
"2. del,<id>删除学生\n"
"3. modify,<id>,<field>,<value>修改学生信息\n"
"4. find,<id>查找学生\n"
"5. list列出所有学生\n"
"6. exit退出系统\n"
"All the data will save automatically.\n\n";




void init();//初始化函数

char cmd[256];
//StrFormat mainFormat;

Node* head = NULL;

int running = 1;

int main() {
	init();//初始化
	
	printf(helpMsg);
	
	
	while (running)
	{
		printf("User Input: ");
		scanf_s("%s", cmd, (int)sizeof(cmd));//获取用户输入的命令

		switch (parseCommand(cmd)) {
		case CMD_LIST:
			ShowList(&head);//read and update head ptr
			break;

		case CMD_ADD:
			addStudentByCmd(head, cmd);
			break;
		case CMD_DELETE:
			removeStudentByCmd(head, cmd);
			break;
		case CMD_MODIFY:

			break;

		case CMD_FIND:
			findStudentByCmd(head, cmd);
			break;
		case CMD_EXIT:
			printf("Exiting the system. Goodbye!\n");
			running = 0;
			break;

		case CMD_HELP:
			printf(helpMsg);
			break;

		
		default:
			printf("Unknown argument: %s\n", cmd);
			printf("\n");
			break;
		}

		printf("\n");
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
			addStudent(head, student);
			//writeStudentFile("students.b", &node);
			printf("write Test command recognized.\n");
		}

	}

	return 0;
}










void init() {
	//setup the format
	//mainFormat.length = 50;
	//strcpy(mainFormat.start, "--------------------");
	//strcpy(mainFormat.end, "--------------------");
	//strcpy(mainFormat.side, "|");

	//mainFormat.separator = '-';
	const char* defaultPath = DEFAULT_PATH;
	head = readStudentFile(defaultPath);
	if(head) {
		printf("Student records loaded successfully.\n");
	}
	else {
		//head = (Node*)malloc(sizeof(Node));//创建头节点
		//
		//head->next = NULL;
		printf("No student records found.\n");
		Sleep(2000);
	}
	
	system("cls");

	int lines = 0;
	for (int i = 0; i < strlen(logo);i++) {
		if (logo[i] == '\n') {
			Sleep(150);
			//MicroSleep(1000);
			lines++;	
			system("cls");
			
			for (int a = 0; a < lines; a++) {
				printf("\n");
			}
			
		}
		printf("%c", logo[i]);
	}
	system("cls");
	lines = 0;
	for (int i = 0; i < strlen(logo); i++) {
		if (logo[i] == '\n') {
			Sleep(70);
			//MicroSleep(1000);
			lines++;
			//system("cls");
			//for (int a = 0; a < lines; a++) {
			//	printf("\n");
			//}
			switch (lines % 5) {
			case 0: system("color 1"); break;
			case 1: system("color 2"); break;
			case 2: system("color 3"); break;
			case 3: system("color 4"); break;
			case 4: system("color 5"); break;
			}
		}
		
		printf("%c", logo[i]);
	}
	
	system("cls");
	system("color 07");
	//printf("\n");
	printf("%s\n", logo);
	Sleep(500);

	printf(welcomeMsg);
	Sleep(500);


}
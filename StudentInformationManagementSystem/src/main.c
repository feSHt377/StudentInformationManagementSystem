#pragma once
#include <stdio.h>
#include <Windows.h>


#include "Headers/Student.h"
#include "Headers/file.h"
#include "Headers/stringTool.h"
#include "Headers/time.h"



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


const char* welcomeMsg = "Welcome to the Student Information Management System!\n";
const char* helpMsg = "Available commands:\n"
"1. add,<id>,<name>,<age>,<sex>,<address>,<phone>,<email>,<Cscore>添加学生\n"
"2. del,<id>删除学生\n"
"3. modify,<id>,<field>,<value>修改学生信息\n"
"4. find,<id>查找学生\n"
"5. list列出所有学生\n"
"6. exit退出系统\n"
"All the data will save automatically.\n\n";



void ShowList();//显示学生列表
void init();//初始化函数

char cmd[256];
//StrFormat mainFormat;

Node* head = NULL;

int running = 1;

int main() {
	init();//初始化
	
	printf(helpMsg);


	char* token;//用于存储分割后的子字符串
	char* ptr = NULL;//用于strtok_s函数内部记录位置
	char* sep = ",";//分隔符
	int cmdLength = 0;
	Node tempStudentNode;
	Student student;
	Node* current = head;
	
	while (running)
	{
		printf("User Input: ");
		scanf_s("%s", cmd, (int)sizeof(cmd));//获取用户输入的命令

		switch (parseCommand(cmd)) {
		case CMD_LIST:
			ShowList();
			break;

		case CMD_ADD:
			/* 获取第一个子字符串 */
			token = strtok_s(cmd, sep, &ptr);//相较于strtok()函数，strtok_s函数需要用户传入一个指针，用于函数内部判断从哪里开始处理字符串
			
			/* 继续获取其他的子字符串 */
			for (int i = 0; token != NULL; i++) {
				printf("%d  %s\n", i, token);
				


				//"1. add,<id>,<name>,<age>,<sex>,<address>,<phone>,<email>,<Cscore>添加学生\n"
				switch (i) {
				case 1:// ID
					student.id = atoi(token);
					break;
				case 2: // Name
					strncpy_s(student.name, sizeof(student.name), token, _TRUNCATE);
					break;
				case 3: // Age
					student.age = atoi(token);
					break;
				case 4: // Sex
					student.sex = token[0];
					break;
				case 5: // Address
					strncpy_s(student.address, sizeof(student.address), token, _TRUNCATE);
					break;
				case 6: // Phone
					strncpy_s(student.phone, sizeof(student.phone), token, _TRUNCATE);
					break;
				case 7: // Email
					strncpy_s(student.email, sizeof(student.email), token, _TRUNCATE);
					break;
				case 8: // Cscore
					student.Cscore = atoi(token);
					break;
				}
				token = strtok_s(NULL, sep, &ptr);
				cmdLength = i+1;
			}
			
			if (cmdLength != 9) {
				printf("Invalid number of arguments for add command. Expected 8, got %d.\ncheck your cmd : %s", cmdLength , cmd);
				break;
			}
			//check for lawfulness here
			if(head == NULL) {
				printf("Error: head is NULL. Cannot add student.\n");
			}
			//else {
			//	tempStudentNode.student.id = head->student.id + 1;
			//}

			tempStudentNode.student = student;
			tempStudentNode.next = NULL;

			// Add the new student node to the linked list
			//init（）函数中会处理head为NULL这个错误，所以理论上不会出现head为空的情况
			
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = (Node*)malloc(sizeof(Node));
			*(current->next) = tempStudentNode;//将临时节点内容复制到新节点
			printf("New student added with ID: %d\n", tempStudentNode.student.id);
			
			// Save the updated list to the file
			writeStudentFile(defaultPath, head);

			break;
		case CMD_DELETE:

			break;
		case CMD_MODIFY:

			break;

		case CMD_FIND:
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

			writeStudentFile(defaultPath, &node);
			printf("write Test command recognized.\n");
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

	head = readStudentFile(defaultPath);
	if(head) {
		printf("Student records loaded successfully.\n");
	}
	else {
		head = (Node*)malloc(sizeof(Node));//创建头节点
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
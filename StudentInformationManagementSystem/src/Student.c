#pragma once




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <Windows.h>


//#include "Headers/Student.h"
#include "Headers/common.h"




const char* defaultPath = DEFAULT_PATH;

//选择排序
void SelectedSort(Node* head) {//此函数对链表进行选择排序，按C语言成绩从大到小排序
	Node* cur, * p = NULL, * q = NULL;//cur为当前节点，p为遍历节点，q为最小节点
	cur = head;//从头节点开始
	int score = 0, cscore = 0;//score为当前节点成绩，cscore为最小节点成绩
	if (cur == NULL || cur->next == NULL) {//链表为空或只有一个节点
		return;//直接返回
	}
	while (cur != NULL) {//遍历链表
		p = cur->next;//从当前节点的下一个节点开始遍历
		q = cur->next;//最大节点初始化为当前节点的下一个节点
		score = cur->student.Cscore;//当前节点成绩
		cscore = score;//最大节点成绩初始化为当前节点成绩
		while (p != NULL) {//遍历链表
			if (cscore < p->student.Cscore) {//如果当前最大节点成绩小于遍历节点成绩
				cscore = p->student.Cscore;//更新最大节点成绩
				q = p;//更新最大节点
			}
			p = p->next;//继续遍历
		}
		if (score != cscore) {//如果当前节点成绩不等于最大节点成绩，说明找到了更大的节点

			Student temp = q->student;//交换节点信息
			q->student = cur->student;//交换节点信息
			cur->student = temp;//交换节点信息

			//q->student.Cscore = score;//交换成绩
			//cur->student.Cscore = cscore;//交换成绩
			//long temp = cur->student.id;//交换学号
			//cur->student.id = q->student.id;//交换学号
			//q->student.id = temp;//交换学号

		}
		cur = cur->next;
	}
}


void show(Student* student) {
	if (student == NULL) {
		printf("Invalid student data.\n");
		return;
	}
	//printf("Name: %s, Age: %d, Id: %d\n", student->name, student->age, student->id);
	printf("ID Name       Age Sex  Address       Phone       Email               CScore\n");
	printf("%-2d %-10s %-3d %-4c %-11s %-12s %-20s %-6d\n",
		student->id,
		student->name,
		student->age,
		student->sex,
		student->address,
		student->phone,
		student->email,
		student->Cscore);
}



//typedef struct
//{
//	short id;//学号
//	char name[35];//姓名
//	int age;//年龄
//	char sex;
//	char address[50];//地址
//	char phone[12];//电话
//	char email[30];//邮箱
//	int Cscore;//c语言成绩
//} Student;



void ShowList(Node* headNow) {//指定数据顺序输出
	// This function would typically display the list of students.
	// For now, it is left empty as a placeholder.
	printf("Displaying student list...\n");

	//const char* defaultPath = DEFAULT_PATH;
	//Node* headNow = readStudentFile(defaultPath);
	if (headNow) {
		Node* current = headNow;

		printf("ID Name       Age Sex  Address       Phone       Email               CScore\n");
		while (current) {
			printf("%-2d %-10s %-3d %-4c %-11s %-12s %-20s %-6d\n",
				current->student.id,
				current->student.name,
				current->student.age,
				current->student.sex,
				current->student.address,
				current->student.phone,
				current->student.email,
				current->student.Cscore);
			current = current->next;
		}
	}
	else {
		printf("No students found.\n");
	}
	//*head = headNow;//update the main head ptr

}


void updateHead(Node** head) {//update the head pointer from file
	*head = readStudentFile(defaultPath);
}

Student* findStudent(Node* head, int id) {
	Node* current = head;
	while (current != NULL) {
		if (current->student.id == id) {
			return &current->student; // Return pointer to the found student
		}
		current = current->next;
	}
	printf("Student not found\n");
	return NULL; // Student not found
}




int addStudent(Node* head, Student student) {// Add student to the end of the list
	//const char* defaultPath = DEFAULT_PATH;
	Node* current = head;
	if (head != NULL) {
		if (current->student.id == student.id) {
			printf("Student with ID: %d already exists. Cannot add duplicate student.\n", student.id);
			return 0;//stop adding if duplicate ID found
		}//确认首项不与其相同

		while (current->next != NULL) {
			if (current->student.id == student.id) {
				printf("Student with ID: %d already exists. Cannot add duplicate student.\n", student.id);
				return 0;//stop adding if duplicate ID found
			}
			current = current->next;
		}

		if (current->student.id == student.id) {
			printf("Student with ID: %d already exists. Cannot add duplicate student.\n", student.id);
			return 0;//stop adding if duplicate ID found
		}//确认末项不与其相同



		Node* newNode = (Node*)malloc(sizeof(Node));
		if (newNode == NULL) {
			printf("Memory allocation failed. Cannot add student.\n");
			return 0;
		}
		newNode->student = student;
		newNode->next = NULL;
		current->next = newNode;
		
	}
	else {
		//head == NULL, empty list
		head = (Node*)malloc(sizeof(Node));
		head->student = student;
		head->next = NULL;
		
	}

	printf("New student added with ID: %d\n", student.id);
	writeStudentFile(defaultPath, head);
	// Save the updated list to the file
	
	return 1;
}

int removeStudent(Node* head, int id) {// Remove student by ID
	//const char* defaultPath = DEFAULT_PATH;
	if (head == NULL) {
		printf("Error: head is NULL. Cannot remove student.\n");
		return 0;
	}

	Node* current = head;// Start from the head node
	Node* previous = NULL;// To keep track of the previous node

	while (current != NULL) {
		if (current->student.id == id) {
			if (previous == NULL) {
				// Removing the head node
				if(current->next){
					head = current->next;
				}
				else {
					head = NULL;
				}
			}
			else {
				previous->next = current->next;
			}

			
			free(current);// Free the memory of the removed node
			printf("Student with ID: %d removed successfully.\n", id);
			// Save the updated list to the file
			writeStudentFile(defaultPath, head);
			return 1;
		}
		previous = current;// Move previous to current-
		current = current->next;
	}

	printf("Student with ID: %d not found.\n", id);
	return 0;
}

//
//int modifyStudent(Node* head, Student student) {// Modify student by ID
//	if (head == NULL) {
//		printf("Error: head is NULL. Cannot modify student.\n");
//		return 0;
//	}
//	Node* current = head;// Start from the head node
//	while (current != NULL) {
//		if (current->student.id == student.id) {
//			current->student = student;// Update student information
//			writeStudentFile(defaultPath, head);// Save the updated list to the file
//			printf("Student with ID: %d modified successfully.\n", student.id);
//			return 1;
//		}
//		current = current->next;
//	}
//	printf("Student with ID: %d not found.\n", student.id);
//	return 0;
//}

int modifyStudentByCmd(Node* head, char* cmd ) {
	// Implementation for modifying a student by command string

	//"3. modify,<id>,<field>,<value>修改学生信息\n"
	char* token;//用于存储分割后的子字符串
	char* ptr = NULL;//用于strtok_s函数内部记录位置
	const char* sep = DEFAULT_SEP;//分隔符
	int cmdLength = 0;
	int id;
	Node* current = head;
	/* 获取第一个子字符串 */
	token = strtok_s(cmd, sep, &ptr);//相较于strtok()函数，strtok_s函数需要用户传入一个指针，用于函数内部判断从哪里开始处理字符串


	char editName[35];
	char editValue[30];
	/* 继续获取其他的子字符串 */
	for (int i = 0; token != NULL; i++) {
		//printf("%d  %s\n", i, token);
		switch (i) {
		case 1:// ID
			id = atoi(token);
			break;
		case 2:// Name
			strncpy_s(editName, sizeof(editName), token, _TRUNCATE);
			break;
		case 3:// Value
			strncpy_s(editValue, sizeof(editValue), token, _TRUNCATE);
			break;
		}
		token = strtok_s(NULL, sep, &ptr);
		cmdLength = i + 1;
	}

	printf("Modifying student with ID: %d, Field: %s, New Value: %s\n", id, editName, editValue);

	if (cmdLength != 4) {
		printf("Invalid number of arguments for modify command. Expected 4, got %d.\ncheck your cmd : %s", cmdLength, cmd);
		return 0;
	}
	//check for lawfulness here
	if (head == NULL) {
		printf("Error: head is NULL. Cannot find student.\n");
	}


	//{
	//	int id;//学号
	//	char name[35];//姓名
	//	int age;//年龄
	//	char sex;
	//	char address[50];//地址
	//	char phone[12];//电话
	//	char email[30];//邮箱
	//	int Cscore;//c语言成绩
	while (current != NULL) {
		if (current->student.id == id) {
			//current->student = student;// Update student information

			//if (strcmp(editName , "id") == 0 ) {//id
			//	//strncpy_s(current->student.name, sizeof(current->student.name), editName, _TRUNCATE);
			//	int newId = atoi(editValue);
			//	if (current->student.id != newId) {
			//		current->student.id = newId;
			//	}
			//}
			//else 
			if(strcmp(editName, "name") == 0)
			{
				strncpy_s(current->student.name, sizeof(current->student.name), editValue, _TRUNCATE);
			}
			else if (strcmp(editName, "age") == 0)
			{
				int newAge = atoi(editValue);
				if (current->student.age != newAge) {
					current->student.age = newAge;
				}
			}
			else if (strcmp(editName, "sex") == 0)
			{
				current->student.sex = editValue[0];
			}
			else if (strcmp(editName, "address") == 0)
			{
				strncpy_s(current->student.address, sizeof(current->student.address), editValue, _TRUNCATE);
			}
			else if (strcmp(editName, "phone") == 0)
			{
				strncpy_s(current->student.phone, sizeof(current->student.phone), editValue, _TRUNCATE);
			}
			else if (strcmp(editName, "email") == 0)
			{
				strncpy_s(current->student.email, sizeof(current->student.email), editValue, _TRUNCATE);
			}
			else if (strcmp(editName, "Cscore") == 0)
			{
				int newCscore = atoi(editValue);
				if (current->student.Cscore != newCscore) {
					current->student.Cscore = newCscore;
				}
			}

			writeStudentFile(defaultPath, head);// Save the updated list to the file
			printf("Student with ID: %d modified successfully.\n", id);
			return 1;
		}
		current = current->next;
	}



	return 0;
}

Student* findStudentByCmd(Node* head,char* cmd ) {// Find student by ID
	char* token;//用于存储分割后的子字符串
	char* ptr = NULL;//用于strtok_s函数内部记录位置
	const char* sep = DEFAULT_SEP;//分隔符
	int cmdLength = 0;
	int id;
	Node* current = head;
	/* 获取第一个子字符串 */
	token = strtok_s(cmd, sep, &ptr);//相较于strtok()函数，strtok_s函数需要用户传入一个指针，用于函数内部判断从哪里开始处理字符串

	/* 继续获取其他的子字符串 */
	for (int i = 0; token != NULL; i++) {
		//printf("%d  %s\n", i, token);
		switch (i) {
		case 1:// ID
			id = atoi(token);
			break;
		}
		token = strtok_s(NULL, sep, &ptr);
		cmdLength = i + 1;
	}

	if (cmdLength != 2) {
		printf("Invalid number of arguments for find command. Expected 2, got %d.\ncheck your cmd : %s", cmdLength, cmd);
		return 0;
	}
	//check for lawfulness here
	if (head == NULL) {
		printf("Error: head is NULL. Cannot find student.\n");
	}
	Student* foundStudent = findStudent(head, id);
	if (foundStudent) {
		show(foundStudent);
		return foundStudent;
	}
	return NULL;

}


int addStudentByCmd(Node* head, char* cmd ) {
	char* token;//用于存储分割后的子字符串
	char* ptr = NULL;//用于strtok_s函数内部记录位置
	const char* sep = DEFAULT_SEP;//分隔符
	int cmdLength = 0;
	Student student;
	Node* current = head;
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
		cmdLength = i + 1;
	}

	if (cmdLength != 9) {
		printf("Invalid number of arguments for add command. Expected 8, got %d.\ncheck your cmd : %s", cmdLength, cmd);
		return 0;
	}

	//check for lawfulness here
	if (head == NULL) {
		printf("Error: head is NULL. Cannot add student.\n");
	}
	//else {
	//	tempStudentNode.student.id = head->student.id + 1;
	//}

	return addStudent(head, student);
}



int removeStudentByCmd(Node* head, char* cmd ) {
	char* token;//用于存储分割后的子字符串
	char* ptr = NULL;//用于strtok_s函数内部记录位置
	const char* sep = DEFAULT_SEP;//分隔符
	int cmdLength = 0;

	int id;
	/* 获取第一个子字符串 */
	token = strtok_s(cmd, sep, &ptr);//相较于strtok()函数，strtok_s函数需要用户传入一个指针，用于函数内部判断从哪里开始处理字符串

	/* 继续获取其他的子字符串 */
	for (int i = 0; token != NULL; i++) {
		printf("%d  %s\n", i, token);



		//"1. add,<id>,<name>,<age>,<sex>,<address>,<phone>,<email>,<Cscore>添加学生\n"
		switch (i) {
		case 1:// ID
			id = atoi(token);
			break;
		}
		token = strtok_s(NULL, sep, &ptr);
		cmdLength = i + 1;
	}

	if (cmdLength != 2) {
		printf("Invalid number of arguments for remove command. Expected 2, got %d.\ncheck your cmd : %s", cmdLength, cmd);
		return 0;
	}

	//check for lawfulness here
	if (head == NULL) {
		printf("Error: head is NULL. Cannot remove student.\n");
	}

	return removeStudent(head, id);
}



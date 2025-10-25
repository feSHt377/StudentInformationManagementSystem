#pragma once




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <Windows.h>


//#include "Headers/Student.h"
#include "Headers/common.h"




const char* defaultPath = DEFAULT_PATH;

//选择排序
void SelectedSort(Node* head) {//此函数对链表进行选择排序，按C语言成绩从小到大排序
	Node* cur, * p = NULL, * q = NULL;//cur为当前节点，p为遍历节点，q为最小节点
	cur = head;//从头节点开始
	int score = 0, cscore = 0;//score为当前节点成绩，cscore为最小节点成绩
	if (cur == NULL || cur->next == NULL) {//链表为空或只有一个节点
		return;//直接返回
	}
	while (cur != NULL) {//遍历链表
		p = cur->next;//从当前节点的下一个节点开始遍历
		q = cur->next;//最小节点初始化为当前节点的下一个节点
		score = cur->student.Cscore;//当前节点成绩
		cscore = score;//最小节点成绩初始化为当前节点成绩
		while (p != NULL) {//遍历链表
			if (cscore > p->student.Cscore) {//如果当前最小节点成绩大于遍历节点成绩
				cscore = p->student.Cscore;//更新最小节点成绩
				q = p;//更新最小节点
			}
			p = p->next;//继续遍历
		}
		if (score != cscore) {//如果当前节点成绩不等于最小节点成绩，说明找到了更小的节点

			Student temp = cur->student;//交换节点信息

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
	printf("Name: %s, Age: %d, Id: %d\n", student->name, student->age, student->id);
}

void ShowList(Node** head) {
	// This function would typically display the list of students.
	// For now, it is left empty as a placeholder.
	printf("Displaying student list...\n");

	//const char* defaultPath = DEFAULT_PATH;
	Node* headNow = readStudentFile(defaultPath);
	if (headNow) {
		Node* current = headNow;
		while (current) {
			//printf("Name: %s, Age: %d, Id: %d\n", current->student.name, current->student.age, current->student.id);
			show(&current->student);

			current = current->next;
		}
	}
	else {
		printf("No students found.\n");
	}
	*head = headNow;//update the main head ptr

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



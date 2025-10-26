#pragma once




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <Windows.h>


//#include "Headers/Student.h"
#include "Headers/common.h"




const char* defaultPath = DEFAULT_PATH;

//ѡ������
void SelectedSort(Node* head) {//�˺������������ѡ�����򣬰�C���Գɼ��Ӵ�С����
	Node* cur, * p = NULL, * q = NULL;//curΪ��ǰ�ڵ㣬pΪ�����ڵ㣬qΪ��С�ڵ�
	cur = head;//��ͷ�ڵ㿪ʼ
	int score = 0, cscore = 0;//scoreΪ��ǰ�ڵ�ɼ���cscoreΪ��С�ڵ�ɼ�
	if (cur == NULL || cur->next == NULL) {//����Ϊ�ջ�ֻ��һ���ڵ�
		return;//ֱ�ӷ���
	}
	while (cur != NULL) {//��������
		p = cur->next;//�ӵ�ǰ�ڵ����һ���ڵ㿪ʼ����
		q = cur->next;//���ڵ��ʼ��Ϊ��ǰ�ڵ����һ���ڵ�
		score = cur->student.Cscore;//��ǰ�ڵ�ɼ�
		cscore = score;//���ڵ�ɼ���ʼ��Ϊ��ǰ�ڵ�ɼ�
		while (p != NULL) {//��������
			if (cscore < p->student.Cscore) {//�����ǰ���ڵ�ɼ�С�ڱ����ڵ�ɼ�
				cscore = p->student.Cscore;//�������ڵ�ɼ�
				q = p;//�������ڵ�
			}
			p = p->next;//��������
		}
		if (score != cscore) {//�����ǰ�ڵ�ɼ����������ڵ�ɼ���˵���ҵ��˸���Ľڵ�

			Student temp = q->student;//�����ڵ���Ϣ
			q->student = cur->student;//�����ڵ���Ϣ
			cur->student = temp;//�����ڵ���Ϣ

			//q->student.Cscore = score;//�����ɼ�
			//cur->student.Cscore = cscore;//�����ɼ�
			//long temp = cur->student.id;//����ѧ��
			//cur->student.id = q->student.id;//����ѧ��
			//q->student.id = temp;//����ѧ��

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
//	short id;//ѧ��
//	char name[35];//����
//	int age;//����
//	char sex;
//	char address[50];//��ַ
//	char phone[12];//�绰
//	char email[30];//����
//	int Cscore;//c���Գɼ�
//} Student;



void ShowList(Node* headNow) {//ָ������˳�����
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
		}//ȷ�����������ͬ

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
		}//ȷ��ĩ�������ͬ



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

	//"3. modify,<id>,<field>,<value>�޸�ѧ����Ϣ\n"
	char* token;//���ڴ洢�ָ������ַ���
	char* ptr = NULL;//����strtok_s�����ڲ���¼λ��
	const char* sep = DEFAULT_SEP;//�ָ���
	int cmdLength = 0;
	int id;
	Node* current = head;
	/* ��ȡ��һ�����ַ��� */
	token = strtok_s(cmd, sep, &ptr);//�����strtok()������strtok_s������Ҫ�û�����һ��ָ�룬���ں����ڲ��жϴ����￪ʼ�����ַ���


	char editName[35];
	char editValue[30];
	/* ������ȡ���������ַ��� */
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
	//	int id;//ѧ��
	//	char name[35];//����
	//	int age;//����
	//	char sex;
	//	char address[50];//��ַ
	//	char phone[12];//�绰
	//	char email[30];//����
	//	int Cscore;//c���Գɼ�
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
	char* token;//���ڴ洢�ָ������ַ���
	char* ptr = NULL;//����strtok_s�����ڲ���¼λ��
	const char* sep = DEFAULT_SEP;//�ָ���
	int cmdLength = 0;
	int id;
	Node* current = head;
	/* ��ȡ��һ�����ַ��� */
	token = strtok_s(cmd, sep, &ptr);//�����strtok()������strtok_s������Ҫ�û�����һ��ָ�룬���ں����ڲ��жϴ����￪ʼ�����ַ���

	/* ������ȡ���������ַ��� */
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
	char* token;//���ڴ洢�ָ������ַ���
	char* ptr = NULL;//����strtok_s�����ڲ���¼λ��
	const char* sep = DEFAULT_SEP;//�ָ���
	int cmdLength = 0;
	Student student;
	Node* current = head;
	/* ��ȡ��һ�����ַ��� */
	token = strtok_s(cmd, sep, &ptr);//�����strtok()������strtok_s������Ҫ�û�����һ��ָ�룬���ں����ڲ��жϴ����￪ʼ�����ַ���

	/* ������ȡ���������ַ��� */
	for (int i = 0; token != NULL; i++) {
		printf("%d  %s\n", i, token);



		//"1. add,<id>,<name>,<age>,<sex>,<address>,<phone>,<email>,<Cscore>���ѧ��\n"
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
	char* token;//���ڴ洢�ָ������ַ���
	char* ptr = NULL;//����strtok_s�����ڲ���¼λ��
	const char* sep = DEFAULT_SEP;//�ָ���
	int cmdLength = 0;

	int id;
	/* ��ȡ��һ�����ַ��� */
	token = strtok_s(cmd, sep, &ptr);//�����strtok()������strtok_s������Ҫ�û�����һ��ָ�룬���ں����ڲ��жϴ����￪ʼ�����ַ���

	/* ������ȡ���������ַ��� */
	for (int i = 0; token != NULL; i++) {
		printf("%d  %s\n", i, token);



		//"1. add,<id>,<name>,<age>,<sex>,<address>,<phone>,<email>,<Cscore>���ѧ��\n"
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



#pragma once




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <Windows.h>


//#include "Headers/Student.h"
#include "Headers/common.h"




const char* defaultPath = DEFAULT_PATH;

//ѡ������
void SelectedSort(Node* head) {//�˺������������ѡ�����򣬰�C���Գɼ���С��������
	Node* cur, * p = NULL, * q = NULL;//curΪ��ǰ�ڵ㣬pΪ�����ڵ㣬qΪ��С�ڵ�
	cur = head;//��ͷ�ڵ㿪ʼ
	int score = 0, cscore = 0;//scoreΪ��ǰ�ڵ�ɼ���cscoreΪ��С�ڵ�ɼ�
	if (cur == NULL || cur->next == NULL) {//����Ϊ�ջ�ֻ��һ���ڵ�
		return;//ֱ�ӷ���
	}
	while (cur != NULL) {//��������
		p = cur->next;//�ӵ�ǰ�ڵ����һ���ڵ㿪ʼ����
		q = cur->next;//��С�ڵ��ʼ��Ϊ��ǰ�ڵ����һ���ڵ�
		score = cur->student.Cscore;//��ǰ�ڵ�ɼ�
		cscore = score;//��С�ڵ�ɼ���ʼ��Ϊ��ǰ�ڵ�ɼ�
		while (p != NULL) {//��������
			if (cscore > p->student.Cscore) {//�����ǰ��С�ڵ�ɼ����ڱ����ڵ�ɼ�
				cscore = p->student.Cscore;//������С�ڵ�ɼ�
				q = p;//������С�ڵ�
			}
			p = p->next;//��������
		}
		if (score != cscore) {//�����ǰ�ڵ�ɼ���������С�ڵ�ɼ���˵���ҵ��˸�С�Ľڵ�

			Student temp = cur->student;//�����ڵ���Ϣ

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
		}//ȷ�����������ͬ

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



#pragma once



#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <io.h>

#include "Headers/common.h"

//const char* defaultPath = "students.b";


int isExist(const char* filename) {//����ļ��Ƿ����
	//const char* file = "example.txt";
	if (_access(filename, 0) != -1) {//����0 ��F_OK��	ֻ�ж��Ƿ����
		//printf("�ļ� '%s' ����\n", file);
		return 1;
	}
	else {
		//printf("�ļ� '%s' ������\n", file);
		return 0;
	}
}



Node* readStudentFile(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (!file) {
		perror("Failed to open file");
		return NULL;
	}
	Node* head = NULL;
	Node* tail = NULL;
	while (1) {
		Node* newNode = (Node*)malloc(sizeof(Node));// Ϊ�¶�ȡ�Ľڵ�����ڴ�
		if (fread(&newNode->student, sizeof(Student), 1, file) != 1) {
			free(newNode);
			//printf("Error reading from file or end of file reached\n");
			break; // ��ȡ������ļ�����
		}
		newNode->next = NULL;
		if (!head) {// �������Ϊ�գ����½ڵ�Ϊͷ�ڵ�
			head = newNode;
			tail = newNode;
		}
		else {// �������Ϊ�գ����½ڵ���ӵ�����ĩβ
			tail->next = newNode;
			tail = newNode;
		}
	}
	fclose(file);
	return head;
}

int writeStudentFile(const char* filename, Node* head) {
	FILE* file = fopen(filename, "wb");
	if (!file) {
		perror("Failed to open file");
		return -1;
	}
	Node* current = head;
	while (current) {
		if (fwrite(&current->student, sizeof(Student), 1, file) != 1) {
			fclose(file);
			printf("Error writing to file\n");
			return 0; // Write error
		}
		current = current->next;
	}
	fclose(file);
	return 1; // Success
}

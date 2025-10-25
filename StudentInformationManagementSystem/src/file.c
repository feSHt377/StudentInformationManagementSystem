#pragma once



#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <io.h>

#include "Headers/common.h"

//const char* defaultPath = "students.b";


int isExist(const char* filename) {//检测文件是否存在
	//const char* file = "example.txt";
	if (_access(filename, 0) != -1) {//参数0 （F_OK）	只判断是否存在
		//printf("文件 '%s' 存在\n", file);
		return 1;
	}
	else {
		//printf("文件 '%s' 不存在\n", file);
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
		Node* newNode = (Node*)malloc(sizeof(Node));// 为新读取的节点分配内存
		if (fread(&newNode->student, sizeof(Student), 1, file) != 1) {
			free(newNode);
			//printf("Error reading from file or end of file reached\n");
			break; // 读取错误或文件结束
		}
		newNode->next = NULL;
		if (!head) {// 如果链表为空，则新节点为头节点
			head = newNode;
			tail = newNode;
		}
		else {// 如果链表不为空，则将新节点添加到链表末尾
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

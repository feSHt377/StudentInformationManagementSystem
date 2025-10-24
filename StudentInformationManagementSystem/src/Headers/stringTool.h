#pragma once
#include <string.h>
#include <stdio.h>


/**
* �ַ���originString���ַ���prefix��ͷ������0�����򷵻�1���쳣����-1
*/
int startWith(const char* originString, char* prefix) {
	// ����У��
	if (originString == NULL || prefix == NULL || strlen(prefix) > strlen(originString)) {
		//printf("�����쳣�����������룡\n");
		return 0;// �쳣����0
	}

	int n = strlen(prefix);
	int i;
	for (i = 0; i < n; i++) {
		if (originString[i] != prefix[i]) {
			return 0; // ��ƥ�䷵��0
		}
	}
	return 1;// ƥ�䷵��0
}


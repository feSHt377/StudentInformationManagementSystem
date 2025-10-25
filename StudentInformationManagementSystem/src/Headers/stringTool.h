#pragma once
#include <string.h>
#include <stdio.h>


enum cmdType {
	CMD_UNKNOWN,
	CMD_ADD,
	CMD_DELETE,
	CMD_MODIFY,
	CMD_FIND,
	CMD_LIST,
	CMD_EXIT,
	CMD_HELP
};


int parseCommand(const char* input) {
	if (startWith(input, "add")) {//ʶ��add����
		return CMD_ADD;
	}
	else if (startWith(input, "del")) {//ʶ��delete����
		return CMD_DELETE;
	}
	else if (startWith(input, "modify")) {//ʶ��modify����
		return CMD_MODIFY;
	}
	else if (startWith(input, "find")) {//ʶ��find����
		return CMD_FIND;
	}
	else if (startWith(input, "list")) {//ʶ��list����
		return CMD_LIST;
	}
	else if (startWith(input, "exit")) {//ʶ��exit����	
		return CMD_EXIT;
	}
	else if (startWith(input, "help")) {//ʶ��help����
		return CMD_HELP;
	}
	else {
		return CMD_UNKNOWN;
	}
}



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


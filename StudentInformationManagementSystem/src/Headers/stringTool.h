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
	if (startWith(input, "add")) {//识别add命令
		return CMD_ADD;
	}
	else if (startWith(input, "del")) {//识别delete命令
		return CMD_DELETE;
	}
	else if (startWith(input, "modify")) {//识别modify命令
		return CMD_MODIFY;
	}
	else if (startWith(input, "find")) {//识别find命令
		return CMD_FIND;
	}
	else if (startWith(input, "list")) {//识别list命令
		return CMD_LIST;
	}
	else if (startWith(input, "exit")) {//识别exit命令	
		return CMD_EXIT;
	}
	else if (startWith(input, "help")) {//识别help命令
		return CMD_HELP;
	}
	else {
		return CMD_UNKNOWN;
	}
}



/**
* 字符串originString以字符串prefix开头，返回0；否则返回1；异常返回-1
*/
int startWith(const char* originString, char* prefix) {
	// 参数校验
	if (originString == NULL || prefix == NULL || strlen(prefix) > strlen(originString)) {
		//printf("参数异常，请重新输入！\n");
		return 0;// 异常返回0
	}

	int n = strlen(prefix);
	int i;
	for (i = 0; i < n; i++) {
		if (originString[i] != prefix[i]) {
			return 0; // 不匹配返回0
		}
	}
	return 1;// 匹配返回0
}


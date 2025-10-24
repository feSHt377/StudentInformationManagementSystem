#pragma once
#include <string.h>
#include <stdio.h>


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


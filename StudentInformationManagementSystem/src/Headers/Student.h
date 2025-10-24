#pragma once






typedef struct
{
	short id;//学号
	char name[35];//姓名
	int age;//年龄
	char sex;
	char address[50];//地址
	char phone[12];//电话
	char email[30];//邮箱
	int Cscore;//c语言成绩
} Student;

// 2. 定义Node结构体（带标签+自引用指针）
typedef struct Node {  // 结构体标签为Node
	Student student;   // Student类型成员（需提前定义）
	struct Node* next;  // 指向自身类型的指针（用标签声明）
} Node;                // 将struct Node重命名为Node（typedef）






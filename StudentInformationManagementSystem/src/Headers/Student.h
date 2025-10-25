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



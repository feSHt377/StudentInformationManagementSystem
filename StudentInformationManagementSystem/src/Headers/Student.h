#pragma once






typedef struct
{
	short id;//ѧ��
	char name[35];//����
	int age;//����
	char sex;
	char address[50];//��ַ
	char phone[12];//�绰
	char email[30];//����
	int Cscore;//c���Գɼ�
} Student;

// 2. ����Node�ṹ�壨����ǩ+������ָ�룩
typedef struct Node {  // �ṹ���ǩΪNode
	Student student;   // Student���ͳ�Ա������ǰ���壩
	struct Node* next;  // ָ���������͵�ָ�루�ñ�ǩ������
} Node;                // ��struct Node������ΪNode��typedef��






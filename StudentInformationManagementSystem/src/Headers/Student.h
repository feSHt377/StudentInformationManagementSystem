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



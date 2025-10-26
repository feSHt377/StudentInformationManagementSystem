#pragma once
#define DEFAULT_PATH "students.b"
#define DEFAULT_SEP ","

typedef struct
{
	int id;//ѧ��
	char name[35];//����
	int age;//����
	char sex;
	char address[50];//��ַ
	char phone[12];//�绰
	char email[30];//����
	int Cscore;//c���Գɼ�
} Student;

// 2. ����Node�ṹ�壨����ǩ+������ָ�룩
typedef struct node {  // �ṹ���ǩΪNode
	Student student;   // Student���ͳ�Ա������ǰ���壩
	struct node* next;  // ָ���������͵�ָ�루�ñ�ǩ������
} Node;                // ��struct node������ΪNode��typedef��



//// ʹ�� extern ����ȫ�ֱ����������壩
//extern const char* defaultPath;


void SelectedSort(Node* head);//�˺������������ѡ�����򣬰�C���Գɼ���С��������
void ShowList(Node* head);//��ʾѧ���б�
int addStudent(Node* head, Student student);// Add student to the end of the list
int removeStudent(Node* head, int id);// Remove student by ID
int addStudentByCmd(Node* head, char* cmd);// Add student by command string
int removeStudentByCmd(Node* head, char* cmd);// Remove student by command string
Student* findStudentByCmd(Node* head, char* cmd);// Find student by ID
Student* findStudent(Node* head, int id);// Find student by ID
void show(Student* student);// Show student information
void updateHead(Node** head);//update the head pointer from file
int modifyStudentByCmd(Node* head, char* cmd);// Modify student by command string
//Student.c


int isExist(const char* filename);//����ļ��Ƿ����
Node* readStudentFile(const char* filename);//��ȡѧ���ļ�����������ͷָ��
int writeStudentFile(const char* filename, Node* head); //д��ѧ���ļ�������״̬��
//file.c



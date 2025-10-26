#pragma once
#define DEFAULT_PATH "students.b"
#define DEFAULT_SEP ","

typedef struct
{
	int id;//学号
	char name[35];//姓名
	int age;//年龄
	char sex;
	char address[50];//地址
	char phone[12];//电话
	char email[30];//邮箱
	int Cscore;//c语言成绩
} Student;

// 2. 定义Node结构体（带标签+自引用指针）
typedef struct node {  // 结构体标签为Node
	Student student;   // Student类型成员（需提前定义）
	struct node* next;  // 指向自身类型的指针（用标签声明）
} Node;                // 将struct node重命名为Node（typedef）



//// 使用 extern 声明全局变量（不定义）
//extern const char* defaultPath;


void SelectedSort(Node* head);//此函数对链表进行选择排序，按C语言成绩从小到大排序
void ShowList(Node* head);//显示学生列表
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


int isExist(const char* filename);//检测文件是否存在
Node* readStudentFile(const char* filename);//读取学生文件，返回链表头指针
int writeStudentFile(const char* filename, Node* head); //写入学生文件，返回状态码
//file.c



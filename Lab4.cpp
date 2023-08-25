#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<cmath>
#include<windows.h>
using namespace std;
#define MAXSIZE 1000
#define OK 1
#define ERROR 0
typedef int Status;
typedef int SElemType;
typedef char TElmType;
typedef TElmType SqBiTree[MAXSIZE];
//��ʽ�洢�ṹ
typedef struct BiNode {
	TElmType data;
	struct BiNode* lchild, * rchild;
}BiNode, * BiTree;

//ѭ�����еĻ�������
typedef struct {
	BiNode data[MAXSIZE];
	int front;
	int rear;
}ddd;

ddd Q;

//��ʼ��һ���ն���
void InitQueue(ddd &Q)
{
	Q.front = 0;
	Q.rear = 0;
}
//�ж϶����Ƿ�Ϊ��
Status QueueEmpty(ddd &Q) {
	if (Q.front == Q.rear) return OK;
	else
		return ERROR;
}

//���
void EnQueue(ddd &Q, BiTree e) {
	if ((Q.rear + 1) % MAXSIZE == Q.front) {//���������ж�
		cout << "����" << endl;
		return;
	}
	Q.data[Q.rear] = *e;  //��Ԫ��e��ֵ����β
	Q.rear = (Q.rear + 1) % MAXSIZE; //rearָ�������һ��λ�ã���ĩβ��ת������ͷ��
}

//����
void DeQueue(ddd &Q, BiTree e)
{
	if (Q.front == Q.rear) {
		cout << "�ӿ�" << endl;
		return;
	}
	*e = Q.data[Q.front]; //����ͷԪ�ظ�ֵ��e
	Q.front = (Q.front + 1) % MAXSIZE; //frontָ�������һλ�ã��������ת������ͷ��
}

//˳�������(�ʺ�����������ȱ���˷ѿռ䣩

//�������ı���

//�ݹ��㷨
void Pre(BiTree T) {//ǰ��
	if (T == NULL) return;
	else {
		cout << T->data;
		Pre(T->lchild);
		Pre(T->rchild);
	}
}

void InOrder(BiTree T) {//����
	if (T == NULL) return ;
	else {
		InOrder(T->lchild);
		cout << T->data;
		InOrder(T->rchild);
	}
}

void Post(BiTree T) {//����
	if (T == NULL) return;
	else {
		Post(T->lchild);
		Post(T->rchild);
		cout << T->data;
	}
}


//�������Ĳ�α����㷨�����ϵ��£������ң�
void LevelOrder(BiTree T) {
	BiTree p= (BiNode*)malloc(sizeof(BiNode));   ddd qu;
	InitQueue(qu);
	if(T!=NULL) EnQueue(qu, T);
	cout << "����=��";
	while (!QueueEmpty(qu)) {
		DeQueue(qu, p);  //���ӽ��p
		cout << p->data;  //���ʽ��p
		if (p->lchild != NULL)EnQueue(qu, p->lchild);
		if (p->rchild != NULL)EnQueue(qu, p->rchild);
	}
}

//�������Ľ���������
Status CreatBiTree(BiTree& T) {
	char c;
	cin >> c;
	if (c == '^')T = NULL;
	else {
		if (!(T = (BiNode*)malloc(sizeof(BiNode))))
			exit(OVERFLOW);
		T->data = c;
		CreatBiTree(T->lchild);  //��������������
		CreatBiTree(T->rchild);  //��������������
	}
	return OK;
}


//�������������ȣ����������Ϊm�����������Ϊn���������ģ�����һ��
int Depth(BiTree T) {
	int m, n;
	if (T == NULL) return 0;
	else {
		m = Depth(T->lchild);
		n = Depth(T->rchild);
		if (m > n) return (m + 1);
		else return (n + 1);
	}
}

//����������Ľڵ㣨�������������+1��
int NodeCount(BiTree T) {
	int m, n;
	if (T == NULL) return 0;
	else {
		m = NodeCount(T->lchild);
		n = NodeCount(T->rchild);
		return m + n + 1;
	}
}

//�����������Ҷ�ӽ�㣨������Ҷ�ӽ��ĸ���+������Ҷ�ӽ��ĸ�����
int LeadCount(BiTree T) {
	if (T == NULL) return 0;
	if (T->lchild == NULL && T->rchild == NULL)
		return 1;
	else {
		return LeadCount(T->lchild) + LeadCount(T->rchild);
	}
}

int main() {         //�������ABDH^^^E^^CF^^G^^
	BiTree T; cout << "����ǰ��ķ�ʽ�����ַ������ո��� ^ ����" << endl;
	CreatBiTree(T);
	cout << "ǰ��=��";Pre(T); cout << endl;
	cout << "����=��"; InOrder(T); cout << endl;
	cout << "����=��"; Post(T); cout << endl;
	LevelOrder(T); cout << endl;
	cout << "Ҷ����=��"; cout << LeadCount(T); cout << endl;
	cout << "���=��";   cout << Depth(T);     cout << endl;
	return 0;
}


#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<string>
using namespace std;

typedef struct {
	double weight;
	int parent, lch, rch;
}HTNode,*HuffmanTree;

typedef  struct art//���������� 
{
    char*  code;  //huffman����
	char letter;  //�������
	int   num;   //���ִ���
}ART,*INK;

typedef char** HuffmanCode;

void Select(HuffmanTree HT, int n, int& s1, int& s2) {
	long int min1 = 1000000000, min2 = 1000000000,k,j;
	for (int i = 1; i <= n; i++) {
		if (HT[i].parent == 0) {
			if (HT[i].weight <min1) {
				min1=HT[i].weight;
				k=i;
			}
		}
	}
		s1 = k;
		//cout<<s1<<endl;
		for (int i = 1; i <= n; i++) {
			if (HT[i].parent == 0 &&i!=k ) {
				if (HT[i].weight < min2) {
				min2 = HT[i].weight;
				j=i;
			}
			}
		}
		s2 = j;
		//cout<<s2<<endl;
	}
	//������Ƶ�ʲ�Ϊ0����ĸ���߿ո�ֵ����ջ�� 
void inputp(INK &P,int &n){
	P=new ART[28];
	int m1;n=0;char a[28]={'#',' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	for(int i=1;i<=27;i++){
		cin>>m1;
		if(m1!=0){
		n++;
		P[n].letter =a[i];
		P[n].num=m1;
	}
	}
}

//�������ַ����� 
int CharCount(INK P,int n){
	int sum=0;
	for(int i=1;i<=n;i++){
		sum+=P[i].num;
	}
	return sum;
}

//����������������������㷨��ʼ��
void CreatHuffmanTree(HuffmanTree &HT, int n,INK P,double &WPL) {
	int m,s1,s2;WPL=0;
	if (n <= 1)return;
	m = 2 * n - 1;   //���鹲2n-1��Ԫ��
	HT = new HTNode[m + 1]; //0�ŵ�Ԫδ�ã�HT[m]��ʾ�����
	for (int i = 1; i <= m; ++i) { //��2n-1��Ԫ�ص�lch��rch��parent��Ϊ0 
		HT[i].lch = 0; HT[i].rch = 0; HT[i].parent = 0;
	}
	for (int i = 1; i <= n; ++i) {
		//cout << "�����" << i << "ƬҶ�ӵ�Ȩ��" << endl;
		HT[i].weight=P[i].num;//����ǰn��Ԫ�ص�weightֵ
	}
	//��ʼ�����������濪ʼ������������
	for (int i = n+1; i <= m; i++) {
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lch = s1; HT[i].rch = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
		WPL+=HT[i].weight;
	}
	//cout << "��������������ֵ" << HT[m].weight << endl;
}

void CreatHuffmanCode(HuffmanTree HT, HuffmanCode& HC, int n,INK &P) {
	int start,c,f;//��Ҷ�ӵ���������ÿ���ַ��Ĺ��������룬����ڱ����HC��
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));    //HC = new char* [n + 1];             
	char *cd = (char*)malloc(n * sizeof(char));                 //cd = new char[n];                 
	cd[n - 1] = '\0';
	for (int i = 1; i <= n; i++) {
		start = n - 1; c = i; f = HT[i].parent;
		while (f != 0) {
			--start;
			if (HT[f].lch == c) cd[start] = '0';
			else cd[start] = '1';
			c = f; f = HT[f].parent;
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
		P[i].code=HC[i];      //��¼��ÿһ���ո������ĸ�ı��� 
	}
	free(cd);
}
//���Ҷ�ӵĹ��������� 
void show(INK P,int n){
	printf("��ĸ   Ȩֵ    ����\n");
	for(int i=1;i<=n;i++){
		cout<<P[i].letter<<"      "<<P[i].num<<"       "<<P[i].code<<endl;
	}
} 
//����С�����ֵĶ����Ʊ��� 
void CreatINK(INK P,int n,string c){
	cout<<"��������Ʊ���=��"; 
	int j=0;
	while(c[j]!='\n'){
		for(int i=1;i<=n;i++){
			if(c[j]==P[i].letter){
			cout<<P[i].code;
			break;
		}
		}
		j++;
	}
	cout<<endl;
} 
//���������
void inputc(string &c){
	c="\n";
	getline(cin,c);       //���cin��iostream�����뻺�� 
	getline(cin,c);
} 
int main() {// 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 0 0 1 1 1 0 0 1 1 �������� 
            // aazy
    int n;double sum1,WPL;HuffmanCode HC;HuffmanTree HT;string s;INK P;
	cout << "�����������Ƶ������" << endl;
	inputp(P,n);sum1=CharCount(P,n);
	string c,c1;char cs;
	inputc(c);
	c1=c+'\n';
	cout<<"������ַ�����=��"<<sum1<<endl;
	CreatHuffmanTree(HT,n,P,WPL);
	cout<<"���WPL=��"<<WPL<<endl;
	cout<<"���ƽ��ÿ���ַ�����ֵ=��"<<(WPL/sum1)<<endl;
	CreatHuffmanCode(HT, HC, n,P);
	//show(HT,HC,n);
	CreatINK(P,n,c1);
	cout<<"�������=��"<<c<<endl;
	//show(P,n); 
	return 0;
}

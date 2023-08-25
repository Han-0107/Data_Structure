#include<iostream>
using namespace std;
#define INF_MAX 999999
#define MVNUM 100
#define OK 1
#define ERROR 0
#define MAXSIZE 1000
typedef int VRType;            //�������������
typedef int ArcType;           //Ȩֵ��������
typedef int Status;
typedef int VerTexType;
//�ڽӾ���Ͷ����
typedef struct ArcCell {
	VRType vexs[MVNUM];        //�����
	ArcType arcs[MVNUM][MVNUM];//Ȩֵ����
	int vexnum, arcnum;        //ͼ�ĵ�ǰ�������ͱ���
}AMGraph;
AMGraph G;
int visited[MVNUM];
//���������ʼ�� 
void Energy(int visited[], AMGraph G) {
	for (int i = 0; i < G.vexnum; i++)
		visited[i] = false;
}
//��³˹�����㷨�Ĵ洢����Ϣ������
typedef struct {
	int begin;
	int end;
	int weight;
}Edge;
//ȡ�����ź���
int LocateVex(AMGraph G, VRType v) {
	for (int i = 0; i < G.vexnum; i++) {
		if (v == G.vexs[i]) return i;
	}
	return -1;
}
//�������Ĺ���(�ڽӾ���)
Status CreatUDN(AMGraph& G) {
	int v1, v2; int w;
	cout << "����������ͼ�Ķ������ͱ߶���:";
	cin >> G.vexnum >> G.arcnum;
	for (int i = 0; i < G.vexnum; i++)  G.vexs[i] = i;
	for (int i = 0; i < G.vexnum; i++)
		for (int j = 0; j < G.vexnum; j++) {
			G.arcs[i][j] = INF_MAX;
		}
	for (int k = 0; k < G.arcnum; k++) {
		cout << "�������" << k << "�߼���Ȩֵ:";
		cin >> v1 >> v2 >> w;
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		G.arcs[i][j] = w;
		G.arcs[j][i] = G.arcs[i][j];
	}
	return OK;
}
//�����������(�ڽӾ���
void DFS(AMGraph G, int v) {
	//int visited[G.vexnum];
	cout << v << ','; visited[v] = true;
	for (int w = 0; w < G.vexnum; w++) {
		if ((G.arcs[v][w] != INF_MAX) && (visited[w]) == 0)
			DFS(G, w);
	}
}
//ѭ�����еĻ�������
typedef struct duilie {
	Status data[MAXSIZE];
	int front;
	int rear;
}ddd;

ddd Q;
//��ʼ��һ���ն���
void InitQueue(ddd& Q)
{
	Q.front = 0;
	Q.rear = 0;
}

//�ж϶����Ƿ�Ϊ��
Status QueueEmpty(ddd Q) {
	if (Q.front == Q.rear) return OK;
	else
		return ERROR;
}

//����Q��Ԫ�ظ�����Ҳ���Ƕ��еĵ�ǰ����
int QueueLength(ddd Q)
{
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

//���
void EnQueue(ddd& Q, Status& e) {
	if ((Q.rear + 1) % MAXSIZE == Q.front) {/*���������ж�*/
		cout << "����" << endl;
		return;
	}
	Q.data[Q.rear] = e;  //��Ԫ��e��ֵ����β
	Q.rear = (Q.rear + 1) % MAXSIZE; //rearָ�������һ��λ�ã���ĩβ��ת������ͷ��
}

//����
void DeQueue(ddd& Q, Status& e)
{
	if (Q.front == Q.rear) {
		cout << "�ӿ�" << endl;
		return;
	}
	e = Q.data[Q.front]; //����ͷԪ�ظ�ֵ��e
	Q.front = (Q.front + 1) % MAXSIZE; //frontָ�������һλ�ã��������ת������ͷ��
}

//�����������(�ڽӾ���
void BFS(AMGraph G, int v) {
	Status u;
	for (int i = 0; i < G.vexnum; i++) visited[i] = false;
	cout << v << ','; visited[v] = true;
	InitQueue(Q);  //��ʼ��һ���ն��У�ѭ�����У�
	EnQueue(Q, v); //���
	while (!QueueEmpty(Q)) {
		DeQueue(Q, u);
		for (int i = 0; i < G.vexnum; i++) {
			if (!visited[i] && G.arcs[u][i] != INF_MAX) {
				cout << G.vexs[i] << ','; visited[i] = true; EnQueue(Q, G.vexs[i]);
			}
		}
	}
	cout << endl;
}
//�����һ����������������ֱ������洢Ȩֵ�ͱ�
struct dd {
	VRType adjvex;
	ArcType lowest;
};  dd closedge[MVNUM];

//��U��V-U����СȨֵ�Ķ�Ӧ��
int minimum(dd closedge[]) {
	double min1 = INF_MAX; int k = -1;
	for (int i = 0; i < G.vexnum; i++) {
		if (closedge[i].lowest < min1 && closedge[i].lowest>0) {
			min1 = closedge[i].lowest;
			k = i;
		}
	}
	return k;
}
//����ķ�㷨������С������
void MiniSpanTree_PRIM(AMGraph G, VRType u) {
	int k = LocateVex(G, u);
	for (int j = 0; j < G.vexnum; j++) //���������ʼ��
		if (j != k) closedge[j] = { u,G.arcs[k][j] };
	closedge[k].lowest = 0;          //��ʼ��U={u}
	for (int i = 0; i < G.vexnum - 1; i++) {
		k = minimum(closedge);       //���T����һ���ڵ㣬��k���ڵ�
		if(closedge[k].adjvex<G.vexs[k])
		cout << closedge[k].adjvex << "-" << G.vexs[k] << ",";//����������ı�
		else
			cout << G.vexs[k] << "-" << closedge[k].adjvex << ",";
		closedge[k].lowest = 0;     //��k�����㲢��U��
		for (int j = 0; j < G.vexnum; j++) {
			if (G.arcs[k][j] < closedge[j].lowest)
				closedge[j] = { G.vexs[k],G.arcs[k][j] };//�¶��㲢��U������ѡ����С��
		}
	}
	cout << endl;
}
//��ʼ��edges������������� 
void OperationEdge(AMGraph G, Edge* edges)
{
	int i, j, k;
	k = 0;
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = i + 1; j < G.vexnum; j++)//ֻ��Ҫת���ڽӾ����һ�룬����ͼ
		{
			if (G.arcs[i][j] != INF_MAX && G.arcs[i][j] != 0)
			{
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G.arcs[i][j];
				k++;
			}
		}
	}
	for (i = 0; i < k - 1; i++)//�򵥽�������
	{
		for (j = i + 1; j < k; j++)
		{
			if (edges[i].weight > edges[j].weight)
			{
				Edge tmp;
				tmp = edges[i];
				edges[i] = edges[j];
				edges[j] = tmp;
			}
		}
	}
	for (int m = 0; m < k; m++) {
		if (edges[m].begin > edges[m].end) {
			VRType swap = edges[m].end;
			edges[m].end = edges[m].begin;
			edges[m].begin = swap;
		}
	}
}
//��ѯ����
int Find(int* parent, int f)
{
	while (parent[f] > 0)
	{
		f = parent[f];
	}

	return f;
}
//��³˹�����㷨
void MiniSpanTree_Kruskal(AMGraph G)
{
	int m, n, k = 0;
	Edge edges[MVNUM];//����߼�����
	int parents[MVNUM];//�����������жϱ�����Ƿ��γɻ�·
	OperationEdge(G, edges);
	for (int i = 0; i < G.vexnum; i++)
		parents[i] = 0;
	int cou = 0;
	for (int i = 0; i < G.vexnum; i++)//ѭ��ÿһ����
	{
		if (cou == G.vexnum - 1) {
			cout << "��С������������ɣ�����" << endl;
			break;
		}
		n = Find(parents, edges[i].begin);
		m = Find(parents, edges[i].end);
		if (m != n)//���m != n��˵���˱�û�к������������γɻ�·
		{
			cou++;
			parents[n] = m;
			cout << edges[i].begin << "-" << edges[i].end << ',';
		}
	}
	cout << endl;
}

//�Ͻ�˹�����㷨�������·��
void ShortestPath_DIJ(AMGraph G, int v0)//��Dijkstra�㷨������ͼG��v0�����ඥ������·�� 
{
	int i, n, v, min, w;//�������õ������б��� 
	n = G.vexnum;//������� 
	bool S[MVNUM];//��������S[]�Ķ��� 
	int D[MVNUM], Path[MVNUM];//��������D[]��Path[]�Ķ��� 
	for (v = 0; v < n; v++)//��������ĳ�ʼ�� 
	{
		S[v] = false;
		D[v] = G.arcs[v0][v];
		if (D[v] < INF_MAX)
			Path[v] = v0;
		else
			Path[v] = -1;
	}
	S[v0] = true;
	D[v0] = 0;//��ʼ������ 
	for (i = 1; i < n; i++)//������n-1�����㣬���ν��м��� 
	{
		min = INF_MAX;//�ݶ���СȨֵ 
		for (w = 0; w < n; w++)
			if (!S[w] && D[w] < min)
			{
				v = w;
				min = D[w];//ѡ��һ����v0���������·�����յ�Ϊv 
			}
		S[v] = true;//���ڼ�¼��ѡ��� 
		for (w = 0; w < n; w++)//���´�v0����������V-S�����ж�������·������ 
			if (!S[w] && (D[v] + G.arcs[v][w] < D[w]))
			{
				D[w] = D[v] + G.arcs[v][w];//����D[w] 
				Path[w] = v;//����w��ǰ��Ϊv 
			}
	}
	//��ӡ������������� 
	for (i = 1; i < n; i++)//��ӡD[] 
		cout << "=:0��" << i << "�ĳ���" << D[i] << endl;
	printf("\n");
}
int main() {
	int v = 0, u = 0;
	CreatUDN(G);
	Energy(visited, G);
	cout << "���������ȱ������=:";
	DFS(G, v);
	cout << endl;
	cout << "���������ȱ������=:";
	BFS(G, v);
	cout << "�������ķ�㷨������С������=:";
	MiniSpanTree_PRIM(G, u);
	cout << "�����³˹�����㷨������С������=:";
	MiniSpanTree_Kruskal(G);
	cout << "����Ͻ�˹�����㷨������С������" << endl;
	ShortestPath_DIJ(G, v);
	return 0;
}


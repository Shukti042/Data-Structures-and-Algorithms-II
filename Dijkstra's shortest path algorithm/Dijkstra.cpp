#include<stdio.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#include<fstream>
using namespace std;
class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item);
    int dequeue();
    bool empty();
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ;
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ;
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ;
		}
		rear = 0 ;
		front = length ;
		delete[] data ;
		data = tempData ;
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data;
    data = 0;
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ;
        }
        delete[] list ;
        list = tempList ;
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position)
{
	if ( position < 0 || position >= length ) return ;
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ;
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}
class node
{
public:
    int v;
    int dist;
    node(int vt,int distt)
    {
        dist=distt;
        v=vt;
    }
};
class minheap
{
    public:
        int heapSize;
        int length;
        int *pos;
        node **a;
        minheap(int capacity)
        {
            pos=new int[capacity];
            heapSize=0;
            length=capacity;
            a=new node*[capacity];
        }
        void swapNode(node** a,node** b)
        {
            node* t = *a;
            *a = *b;
            *b = t;
        }
        void minHeapify(int id)
        {
            int smallest, left, right;
            smallest = id;
            left = 2 * id + 1;
            right = 2 * id + 2;

            if (left < heapSize && a[left]->dist < a[smallest]->dist )
              smallest = left;

            if (right <heapSize && a[right]->dist < a[smallest]->dist )
              smallest = right;

            if (smallest != id)
            {
                node *smallestNode = a[smallest];
                node *idNode = a[id];
                pos[smallestNode->v] = id;
                pos[idNode->v] = smallest;

                swapNode(&a[smallest],&a[id]);

                minHeapify(smallest);
            }
        }
        node* extractMin()
        {
            if (isEmpty())
                return NULL;


            node* root =a[0];


            node* lastNode =a[heapSize - 1];
            a[0] = lastNode;


            pos[root->v] = heapSize-1;
            pos[lastNode->v] = 0;

            heapSize--;
            minHeapify(0);

            return root;
        }
        void decreaseKey(int v, int dist)
        {
            int i = pos[v];

            a[i]->dist = dist;

            while (i && a[i]->dist < a[(i - 1) / 2]->dist)
            {
                pos[a[i]->v] = (i-1)/2;
                pos[a[(i-1)/2]->v] = i;
                swapNode(&a[i], &a[(i - 1) / 2]);

                i = (i - 1) / 2;
            }
        }
        bool isEmpty()
        {
            return heapSize == 0;
        }
        bool isInMinHeap(int v)
        {
           if (pos[v] < heapSize)
             return true;
           return false;
        }

        void printArr(int dist[],int pre[], int n)
        {
            printf("Vertex   Distance from Source   Path\n");
            for (int i = 0; i < n; ++i)
            {
                  printf("%d \t\t %d \t\t ", i, dist[i]);
                  printPath(pre,dist,i);
                  printf("\n");
            }
        }
        void printPath(int pre[],int dist[] ,int i)
        {
            if(pre[i]!=-1)
            {
                 printPath(pre,dist,pre[i]);
            }
            if(i!=-1&&dist[i]!=INFINITY)
                printf("%d ",i);
            if(dist[i]==INFINITY)
                printf("No Path Exists");
        }
};
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;

public:
    int** weight;
	Graph(bool dir);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v,int w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    void printGraph();
    void dijkstra(int src);
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ;
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ;
	adjList = new ArrayList[nVertices] ;
	weight=new int*[n];
	for(int i=0;i<n;i++)
    {
        weight[i]=new int[n];
        for(int j=0;j<n;j++)
        {
            weight[i][j]=INFINITY;
        }
    }
}

void Graph::addEdge(int u, int v,int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	weight[u][v]=w;
	if(!directed)
    {
        adjList[v].insertItem(u) ;
        weight[v][u]=w;
    }
}

void Graph::removeEdge(int u, int v)
{
     if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    this->nEdges-- ;
	adjList[u].removeItem(v) ;
	weight[u][v]=INFINITY;
	if(!directed)
    {
        adjList[v].removeItem(u) ;
        weight[v][u]=INFINITY;
    }
}

bool Graph::isEdge(int u, int v)
{
     if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
     int t=adjList[u].searchItem(v);
     if(t!=NULL_VALUE)
        return true;
     return false;
}

int Graph::getDegree(int u)
{
    return adjList[u].getLength();
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    int l=adjList[u].getLength();
    for(int i=0;i<l;i++)
    {
        if(isEdge(v,adjList[u].getItem(i)))
            return true;
    }
    return false;

}
void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}
void Graph::dijkstra(int src)
{
    int dist[nVertices];
    int pre[nVertices];
    minheap* minHeap = new minheap(nVertices);
    for (int v = 0; v < nVertices; ++v)
    {
        dist[v] = INFINITY;
        pre[v]=-1;
        minHeap->a[v] = new node(v, dist[v]);
        minHeap->pos[v] = v;
    }

    minHeap->a[src] = new node(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    minHeap->decreaseKey(src, dist[src]);

    minHeap->heapSize = nVertices ;

    while (!minHeap->isEmpty())
    {
        node* minHeapNode = minHeap->extractMin();
        int u = minHeapNode->v;
        for(int i=0;i<adjList[u].getLength();i++)
        {
            int v = adjList[u].getItem(i);

            if (minHeap->isInMinHeap(v) && dist[u] != INFINITY &&  weight[u][v] + dist[u] < dist[v])
            {
                dist[v] = dist[u] + weight[u][v];
                pre[v]=u;
                minHeap->decreaseKey( v, dist[v]);
            }
        }
    }

    minHeap->printArr(dist,pre, nVertices);
}

Graph::~Graph()
{
    if(adjList)
    {
            delete[] adjList;
    }
        adjList=0;
}

main()
{
    Graph g(true);
    ifstream myReadFile;
    myReadFile.open("Input.txt");
    int n,s,u,v,w;
    if (myReadFile.is_open())
    {
        myReadFile >> n;
        g.setnVertices(n);
        myReadFile >> s;
        while (!myReadFile.eof())
        {


            myReadFile >> u;
            myReadFile >> v;
            myReadFile >> w;
            g.addEdge(u, v, w);
        }
    }
    g.dijkstra(s);

}

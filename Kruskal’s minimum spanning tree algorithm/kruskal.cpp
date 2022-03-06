#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#include<fstream>
using namespace std;
FILE *output;
class edge {
public:
    int u, v, w;
    edge(int x,int y,int z)
    {
        u=x;
        v=y;
        w=z;
    }
    edge()
    {
        u=-1;
        v=-1;
        w=INFINITY;
    }
    edge operator<(const edge& p)
    {
        this->u=p.u;
        this->v=p.v;
        this->w=p.w;
    }

};
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
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
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
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
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
	void printList();
	bool empty();

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
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
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

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
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

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	edge *edges;

public:
    int** weight;
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void setnEdges();
	void addEdge(int u, int v,int w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    void printGraph();
    void floyd(int **dist,int **pred);
    void Merge( int l, int m, int r);
    void mergeSort(int l,int r) ;
    int kruskal(edge eds[]);
    int Find(int r);
    int *pr;

};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}
void Graph::setnEdges()
{
    edges=new edge[nEdges];
    int index=0,temp;
    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<adjList[i].getLength();j++)
        {
            temp=adjList[i].getItem(j);
            edges[index].u=i;
            edges[index].v=adjList[i].getItem(j);
            edges[index].w=weight[i][temp];
            index++;
        }
    }
    pr=new int[nVertices];

}
void Graph:: Merge(int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    edge L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = edges[l + i];
    for (j = 0; j < n2; j++)
        R[j] = edges[m + 1+ j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].w <= R[j].w)
        {
            edges[k] = L[i];
            i++;
        }
        else
        {
            edges[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        edges[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        edges[k] = R[j];
        j++;
        k++;
    }
}
void Graph::mergeSort(int l,int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(l, m);
        mergeSort(m+1, r);
        Merge(l, m, r);
    }
}
void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
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
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
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
    //write this function
     if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges-- ;
	adjList[u].removeItem(v) ;
	if(!directed)
    {
        adjList[v].removeItem(u) ;
        weight[v][u]=INFINITY;
    }
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
     if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
     int t=adjList[u].searchItem(v);
     if(t!=NULL_VALUE)
        return true;
     return false;

}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    return adjList[u].getLength();
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
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
     /*for(int i=0;i<nEdges;i++)
    {
        printf("%d %d %d\n",edges[i].u,edges[i].v,edges[i].w);
    }*/
}

Graph::~Graph()
{
    if(adjList)
    {
            delete[] adjList;
    }
        adjList=0;
}
int Graph:: Find(int r)
{
    if (pr[r]==r)
    {
        return r;
    }
	pr[r]= Find(pr[r]);
	return pr[r];
}
int Graph:: kruskal(edge eds[])
{
    for (int i = 0; i < nVertices; i++)
        pr[i] = i;

    int Count = 0, s = 0;
    for (int i = 0; i < nEdges; i++) {
        int u = Find(edges[i].u);
        int v = Find(edges[i].v);
        if (u != v) {
            pr[u] = v;
            s += edges[i].w;
            eds[Count]=edges[i];
            Count++;
            if (Count == nVertices - 1)
                break;
        }
    }
    return s;
}

main()
{
    Graph g(true);
    ifstream myReadFile;
    ofstream ofs;
    ofs.open("Output.txt", ofstream::out | ofstream::trunc);
    ofs.close();
    myReadFile.open("Input.txt");
    output = fopen ("Output.txt","a");
    int n,e,u,v,w,**dist,**pred;
    if (myReadFile.is_open())
    {
        myReadFile >> n;
        g.setnVertices(n);
        myReadFile >> e;
        while (!myReadFile.eof())
        {


            myReadFile >> u;
            myReadFile >> v;
            myReadFile >> w;
            g.addEdge(u, v, w);
        }
    }
    int wt;
    g.setnEdges();
    g.mergeSort(0,e-1);
    edge eds[n-1];
    wt=g.kruskal(eds);

    for(int i=0;i<n-1;i++)
    {

        {
            fprintf(output,"%d %d \n",eds[i].u,eds[i].v);
        }
    }
     fprintf(output,"MST Weight:%d \n",wt);



}


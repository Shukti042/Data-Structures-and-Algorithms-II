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

public:
    bool hasNegCycl=false;
    int** weight;
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v,int w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    void printGraph();
    void bellman(int s);
    void printDist(int dist[],int pre[], int n);
	void printPath(int pre[],int dist[] ,int i);
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
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
}

Graph::~Graph()
{
    if(adjList)
    {
            delete[] adjList;
    }
        adjList=0;
}
void Graph::bellman(int s)
{
    int dist[nVertices],prev[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        dist[i]=INFINITY;
        prev[i]=-1;
    }
    dist[s]=0;
    int v;
    for(int i=0;i<nVertices-1;i++)
    {
        for(int u=0;u<nVertices;u++)
        {
            for(int j=0;j<adjList[u].getLength();j++)
            {
                v=adjList[u].getItem(j);
                if(dist[v]>dist[u]+weight[u][v]&&dist[u]!=INFINITY)
                {
                    dist[v]=dist[u]+weight[u][v];
                    prev[v]=u;
                }
            }
        }
    }
    for(int u=0;u<nVertices;u++)
        {
            for(int j=0;j<adjList[u].getLength();j++)
            {
                v=adjList[u].getItem(j);
                if(dist[v]>dist[u]+weight[u][v]&&dist[u]!=INFINITY)
                {
                    hasNegCycl=true;
                    break;
                }
            }
            if(hasNegCycl)
                break;
        }
    if(!hasNegCycl)
        printDist(dist,prev,nVertices);
    else
        printf("The Graph Has Negative weighted Cycle");

}
void Graph:: printDist(int dist[],int pre[], int n)
{
        fprintf(output,"Vertex   Distance from Source   Path\n");
        for (int i = 0; i < n; ++i)
        {
            fprintf(output,"%d \t\t %d \t\t ", i, dist[i]);
            printPath(pre,dist,i);
            fprintf(output,"\n");
        }
}
void Graph:: printPath(int pre[],int dist[] ,int i)
{
    if(pre[i]!=-1)
    {
        printPath(pre,dist,pre[i]);
    }
    if(i!=-1&&dist[i]!=INFINITY)
        fprintf(output,"%d ",i);
    if(dist[i]==INFINITY)
        fprintf(output,"No Path Exists");
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
    g.bellman(s);
}

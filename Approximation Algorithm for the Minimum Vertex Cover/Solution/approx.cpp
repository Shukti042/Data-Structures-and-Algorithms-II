#include<bits/stdc++.h>
using namespace std;
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 0
#define GREY 1
#define BLACK 2

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


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation
	int *color,*parent,*distance,*p,*c,*dt,*ft,time;
	vector<pair<int,int> > edges;

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void visit(int u);
    void dfs();
    vector<int> VCrand();
     vector<int> VCrand2();
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
	color=0;
	distance=0;
	parent=0;
	p=0;
	c=0;
	dt=0;
	ft=0;
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;
    nEdges++;
    edges.push_back(make_pair(u,v));
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 0;
    if(!directed) matrix[v][u] = 0;
    nEdges--;
    edges.erase(remove(edges.begin(), edges.end(),make_pair(u,v) ), edges.end());
    if(!directed)
        edges.erase(remove(edges.begin(), edges.end(),make_pair(v,u) ), edges.end());
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    if(matrix[u][v]==1)
        return true;
    return false;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u>=nVertices) return NULL_VALUE;
    int degree=0;
    for(int j=0;j<nVertices;j++)
    {
        if(matrix[u][j]==1)
            degree++;
    }
    return degree;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    for(int j=0;j<nVertices;j++)
    {
        if(matrix[u][j]==1&&matrix[v][j]==1)
            return true;
    }
    return false;

}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
    int u,v;
    if(color)
        delete[] color;
    if(distance)
        delete [] distance;
    if(parent)
        delete [] parent;
    color=new int[nVertices];
    parent=new int[nVertices];
    distance=new int[nVertices];

    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        distance[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    distance[source] = 0 ;
    q.enqueue(source) ;
    printf("Node=%d Parent=%d Distance=%d Grey\n",source,parent[source],distance[source]);
    while( !q.empty() )
    {
        //complete this part
        u=q.dequeue();
        for(v=0;v<nVertices;v++)
        {
            if(isEdge(u,v))
            {
                if(color[v]==WHITE)
                {
                    color[v]=GREY;
                    distance[v]=distance[u]+1;
                    parent[v]=u;
                    q.enqueue(v);
                    printf("Node:%d Parent:%d Distance:%d Grey\n",v,parent[v],distance[v]);

                }
            }
        }
        color[u]=BLACK;
        printf("Node:%d Parent:%d Distance:%d black\n",u,parent[u],distance[u]);
    }

}

void Graph::dfs()
{
    //write this function
    if(c)
        delete[] c;
    if(p)
        delete [] p;
    if(dt)
        delete [] dt;
    if(ft)
        delete [] ft;
    c=new int[nVertices];
    p=new int[nVertices];
    dt=new int[nVertices];
    ft=new int[nVertices];
    int u,v;
    for(u=0;u<nVertices;u++)
    {
        c[u]=WHITE;
        p[u]=NULL_VALUE;
    }
    time=0;
    for(u=0;u<nVertices;u++)
    {
        if(c[u]==WHITE)
        {
            visit(u);
        }

    }

}
void Graph::visit(int u)
{
    time=time+1;
    dt[u]=time;
    c[u]=GREY;
    printf("Node:%d Discovery time:%d Color:Grey\n",u,dt[u]);
    for(int v=0;v<nVertices;v++)
    {
        if(isEdge(u,v)&&c[v]==WHITE)
        {
            p[v]=u;
            visit(v);
        }
    }
    c[u]=BLACK;
    time=time+1;
    ft[u]=time;
    printf("Node:%d Finish time:%d Color:Black\n",u,ft[u]);
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return INFINITY;
    bfs(u);
    return distance[v];
    return INFINITY ;
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
     if(c)
        delete[] c;
        c=0;
    if(p)
        delete [] p;
        p=0;
    if(dt)
        delete [] dt;
        dt=0;
    if(ft)
        delete [] ft;
        ft=0;
    if(parent)
        delete[] parent;
        parent=0;
    if(color)
        delete[] color;
        color=0;
    if(distance)
        delete[] distance;
        distance=0;
    if(matrix)
        {
            for(int i=0;i<nVertices;i++)
            {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
        matrix=0;
}
vector<int> Graph::VCrand()
{
    vector<int> vc;
    int r,u,v;
    int **mat;
    mat = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        mat[i] = new int[nVertices];
    }
    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            mat[i][j]=matrix[i][j];
        }
    }
   while(edges.size()!=0)
   {
        r=rand()%edges.size();
        u=edges[r].first;
        v=edges[r].second;
        vc.push_back(u);
        vc.push_back(v);
        for(int k=0;k<nVertices;k++)
        {
            matrix[u][k]=0;
            if(mat[u][k]==1)
                edges.erase(remove(edges.begin(), edges.end(),make_pair(u,k) ), edges.end());
            matrix[v][k]=0;
            if(mat[v][k]==1)
                edges.erase(remove(edges.begin(), edges.end(),make_pair(v,k) ), edges.end());
            matrix[k][u]=0;
            if(mat[k][u]==1)
                edges.erase(remove(edges.begin(), edges.end(),make_pair(k,u) ), edges.end());
            matrix[k][v]=0;
            if(mat[k][v]==1)
                edges.erase(remove(edges.begin(), edges.end(),make_pair(k,v) ), edges.end());

        }

   }
    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
                matrix[i][j]=mat[i][j];
        }
    }
    return vc;
}

vector<int> Graph::VCrand2()
{
    vector<int> vc;
    int **mat;
    mat = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        mat[i] = new int[nVertices];
    }
    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            mat[i][j]=matrix[i][j];
        }
    }
    int deg=0,temp,u,v;
    while(deg!=NULL_VALUE)
    {
        deg=NULL_VALUE;
        for(int i=0;i<nVertices;i++)
        {
            for(int j=0;j<nVertices;j++)
            {
                if(matrix[i][j]==1)
                {
                    temp=getDegree(i)+getDegree(j);
                    if(temp>deg)
                    {
                        deg=temp;
                        u=i;
                        v=j;
                    }
                }

            }
        }
        if(deg!=NULL_VALUE)
            {
                vc.push_back(u);
                vc.push_back(v);
                for(int k=0;k<nVertices;k++)
                {
                    matrix[u][k]=0;
                    matrix[v][k]=0;
                    matrix[k][u]=0;
                    matrix[k][v]=0;

                }
            }
    }
    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            matrix[i][j]=mat[i][j];
        }
    }
    return vc;
}

//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    srand(time(0));
    /*Graph G(false);
    G.setnVertices(10);
    G.addEdge(0,1);
    G.addEdge(2,3);
    G.addEdge(4,5);
    G.addEdge(6,7);
    G.addEdge(8,9);
    vector<int> vc=G.VCrand();
    for(int i=0;i<vc.size();i++)
        cout<<vc[i]<<" ";
    cout<<endl;
    vc=G.VCrand2();
    for(int i=0;i<vc.size();i++)
        cout<<vc[i]<<" ";*/
   /* int n,u,v,x,y,p,q;
    float avg;
    float m;
    Graph G(false);
    ifstream fin;
    ofstream fout;
    vector <int> result,result2;
    fout.open("Output.txt");
    fin.open("Input11.txt");
    fin>>n;
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    result2.push_back(G.VCrand2().size());
    fin.close();
    fin.open("Input12.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    fin.close();
    fin.open("Input13.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    fin.close();
    fin.open("Input14.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    fin.close();
    fin.open("Input15.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    fin.close();
    x=result[0];
    y=result[0];
    avg=result[0];
    for(int i=1;i<result.size();i++)
    {
        if(x>result[i])
            x=result[i];
        if(y<result[i])
            y=result[i];
        avg+=result[i];

    }
    fout<<"Method A:"<<endl;
    fout<<"For Data Set 1: Best Case- "<<x<<" Worst Case- "<<y<<" Average- "<<avg/5<<endl;
    result.clear();

    fin.open("Input21.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    result2.push_back(G.VCrand2().size());
    fin.close();
    fin.open("Input22.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    fin.close();
    fin.open("Input23.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    fin.close();
    fin.open("Input24.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    fin.close();
    fin.open("Input25.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    fin.close();
    x=result[0];
    y=result[0];
    avg=result[0];
    for(int i=1;i<result.size();i++)
    {
        if(x>result[i])
            x=result[i];
        if(y<result[i])
            y=result[i];
        avg+=result[i];

    }
    fout<<"For Data Set 2: Best Case- "<<x<<" Worst Case- "<<y<<" Average- "<<avg/5<<endl;
    result.clear();

    fin.open("Input31.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back(G.VCrand().size());
    result2.push_back(G.VCrand2().size());
    fin.close();
    fin.open("Input32.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    fin.close();
    fin.open("Input33.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    fin.close();
    fin.open("Input34.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    fin.close();
    fin.open("Input35.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    fin.close();
    x=result[0];
    y=result[0];
    avg=result[0];
    for(int i=1;i<result.size();i++)
    {
        if(x>result[i])
            x=result[i];
        if(y<result[i])
            y=result[i];
        avg+=result[i];

    }
    fout<<"For Data Set 3: Best Case- "<<x<<" Worst Case- "<<y<<" Average- "<<avg/5<<endl;
    result.clear();

    fin.open("Input41.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back(G.VCrand().size());
    result2.push_back(G.VCrand2().size());
    fin.close();
    fin.open("Input42.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    fin.close();
    fin.open("Input43.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    fin.close();
    fin.open("Input44.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    fin.close();
    fin.open("Input45.txt");
    fin>>n;
    G=new Graph(false);
    G.setnVertices(n);
    while(fin.good())
    {
        fin>>u>>v;
        G.addEdge(u-1,v-1);
    }
    result.push_back( G.VCrand().size());
    fin.close();
    x=result[0];
    y=result[0];
    avg=result[0];
    for(int i=1;i<result.size();i++)
    {
        if(x>result[i])
            x=result[i];
        if(y<result[i])
            y=result[i];
        avg+=result[i];

    }
    fout<<"For Data Set 4: Best Case- "<<x<<" Worst Case- "<<y<<" Average- "<<avg/5<<endl;
    result.clear();
    fout<<endl<<"Method B:"<<endl;
    fout<<"For Data Set 1: Optimal- 420 Obtained- "<<result2[0]<<endl;
    fout<<"For Data Set 2: Optimal- 560 Obtained- "<<result2[1]<<endl;
    fout<<"For Data Set 3: Optimal- 720 Obtained- "<<result2[2]<<endl;
    fout<<"For Data Set 4: Optimal- 900 Obtained- "<<result2[3]<<endl;
    fout.close();*/

}

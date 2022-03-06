#include<bits/stdc++.h>
using namespace std;
#define NULL_VALUE -99999
class node
{
public:
    int data,degree;
    node *sibling,*child;
    node();
    node(int d);
    node* Merge(node *newNode);
    void print();
};
node::node()
{
    data=NULL_VALUE;
    sibling=NULL;
    child=NULL;
    degree=0;
}
node::node(int d)
{
    this->data=d;
    sibling=NULL;
    child=NULL;
    degree=0;
}
node* node::Merge(node *newNode)
{
    if(degree==newNode->degree)
    {
        newNode->sibling=this->child;
        this->child=newNode;
        degree++;
    }
    return this;
}
void node::print()
{
    if(data==NULL_VALUE)
        return;
    node **temp,**temp2;
    temp=new node*[1000];
    temp2=new node*[1000];
    temp[0]=this;
    int l=1,i=0,l1=0,c,c3=0;
    c=pow(2,degree);
    node* t;
    int k=0;
    while(true)
    {
        cout<<"Level "<<k<<"--";
        l1=0;
        for(i=0;i<l;i++)
        {
            t=temp[i];
            while(t!=NULL)
            {
                cout<<t->data<<"("<<t->degree<<")"<<"  ";
                c3++;
                if(t->child!=NULL)
                {
                    temp2[l1]=t->child;
                    l1++;
                }
                t=t->sibling;
            }
        }
        for(i=0;i<l1;i++)
        {
            temp[i]=temp2[i];
        }
        l=l1;
        cout<<endl<<endl;
        k++;
        if(c3>=c)
        break;
    }
}
/*--------------------------------------------
----------------------------------------------
----------------------------------------------
----------------------------------------------
----------------------------------------------
----------------------------------------------*/
class heap
{
public:
    node **heapArr;
    int length;
    heap(int sz);
    void Insert(int i);
    void print();
    int findMin();
    heap* Union(heap *h);
    int extractMin();

};
heap::heap(int sz)
{
    heapArr=new node*[sz];
    length=0;
    for(int i=0;i<sz;i++)
    {
        heapArr[i]=new node();
    }
}
void heap::Insert(int val)
{
    node *a,*x;
    a=new node(val);
    if(length==0)
    {
        heapArr[0]=a;
        length++;
        return;
    }
    else
    {
        bool inserted=false;
        int i=0;
        while(!inserted)
        {
            if(heapArr[i]->data==NULL_VALUE)
            {
                heapArr[i]=a;
                if(length<=a->degree)
                    length++;
                inserted=true;
            }
            else
            {
                if(heapArr[i]->data<a->data)
                {
                    x=heapArr[i]->Merge(a);
                    a=x;
                }
                else
                {
                    a->Merge(heapArr[i]);
                }
                heapArr[i]=new node();
            }
            i++;

        }
    }
}
void heap::print()
{
    for(int i=0;i<length;i++)
    {
        cout<<"B"<<i<<":"<<endl;
        heapArr[i]->print();
        cout<<endl;
    }
}
int heap::findMin()
{
    int m=9999999;
    if(length==0)
        return NULL_VALUE;
    for(int i=0;i<length;i++)
    {
        if(m>heapArr[i]->data&&heapArr[i]->data!=NULL_VALUE)
            m=heapArr[i]->data;
    }
    return m;
}
heap* heap::Union(heap *h)
{
    int l;
    node *a,*x;
    x=NULL;
    if(h->length>this->length)
        l=h->length;
    else
        l=this->length;
    for(int i=0;i<l;i++)
    {
        if(this->heapArr[i]->data==NULL_VALUE)
        {
            if(x==NULL)
            {
                this->heapArr[i]=h->heapArr[i];
            }
            else if(h->heapArr[i]->data==NULL_VALUE)
            {
                this->heapArr[i]=x;
                x=NULL;
            }
            else
            {
                if(x->data < h->heapArr[i]->data)
                    a=x->Merge(h->heapArr[i]);
                else
                    a=h->heapArr[i]->Merge(x);
                x=a;
            }
        }
        else
        {
            if(x==NULL)
            {
                if(h->heapArr[i]->data!=NULL_VALUE)
                {
                    if(this->heapArr[i]->data<h->heapArr[i]->data)
                        x=this->heapArr[i]->Merge(h->heapArr[i]);
                    else
                        x=h->heapArr[i]->Merge(this->heapArr[i]);
                    this->heapArr[i]=new node();
                }
            }
            else
            {
                if(h->heapArr[i]->data!=NULL_VALUE)
                {
                    if(x->data < h->heapArr[i]->data)
                        a=x->Merge(h->heapArr[i]);
                    else
                        a=h->heapArr[i]->Merge(x);
                    x=a;
                }
                else
                {
                    if(x->data < this->heapArr[i]->data)
                    a=x->Merge(this->heapArr[i]);
                    else
                        a=this->heapArr[i]->Merge(x);
                    x=a;
                    this->heapArr[i]=new node();
                }
            }
        }
    }
    if(x!=NULL)
    {
        this->heapArr[l]=x;
        l++;
    }
    this->length=l;
}
int heap::extractMin()
{
    if(length==0)
        return NULL_VALUE;
    int m=9999999,index=0;
    for(int i=0;i<length;i++)
    {
        if(m>heapArr[i]->data&&heapArr[i]->data!=NULL_VALUE)
        {
            m=heapArr[i]->data;
            index=i;
        }
    }
    heap *h;
    node *x,*a;
    h=new heap(100);
    h->length=heapArr[index]->degree;
    x=heapArr[index]->child;
    for(int i=h->length-1;i>=0;i--)
    {
        a=x;
        x=x->sibling;
        a->sibling=NULL;
        h->heapArr[i]=a;
    }
    heapArr[index]=new node();
    this->Union(h);
    return m;
}
/*--------------------------------------------
----------------------------------------------
----------------------------------------------
----------------------------------------------
----------------------------------------------
----------------------------------------------*/
main()
{
   /* node *a,*b,*c,*d,*e,*f,*g,*h,*a1,*b1,*c1,*d1,*e1,*f1,*g1,*h1;
    a=new node(5);
    b=new node(6);
    c=new node(7);
    d=new node(8);
    e=new node(9);
    f=new node(10);
    g=new node(11);
    h=new node(12);
    a->Merge(b);
    c->Merge(d);
    e->Merge(f);
    g->Merge(h);
    a->Merge(c);
    e->Merge(g);
    a->Merge(e);
    a1=new node(5);
    b1=new node(6);
    c1=new node(7);
    d1=new node(8);
    e1=new node(9);
    f1=new node(10);
    g1=new node(11);
    h1=new node(12);
    a1->Merge(b1);
    c1->Merge(d1);
    e1->Merge(f1);
    g1->Merge(h1);
    a1->Merge(c1);
    e1->Merge(g1);
    a1->Merge(e1);
    a->Merge(a1);
    a->print();*/
    /*heap *x,*y;
    x=new heap(100);
    x->Insert(5);
    x->Insert(6);
    x->Insert(1);
    x->Insert(7);
    x->Insert(9);
    x->Insert(8);
    x->Insert(6);
    //x->print();
    y=new heap(100);
    y->Insert(3);
    y->Insert(1);
    y->Insert(11);
    y->Insert(37);
    y->Insert(92);
    y->Insert(28);
    y->Insert(61);
    //y->print();
    x->Union(y);
    x->print();
    x->extractMin();
    x->print();*/
    heap *h1,*h2;
    int n,x;
    h1=new heap(100);
    h2=new heap(100);
    while(true)
    {
        cout<<"1.Insert in Heap1  2.Insert in Heap2   3.Union Heap2 with Heap1"<<endl;
        cout<<"4.Print Heap1   5.Print Heap2  6.Find min(1)  7.Extract min(1) "<<endl;
        cout<<"0.Exit"<<endl;
        cout<<"Enter Your Choice: ";
        cin>>n;
        if(n==1)
        {
            cout<<"Enter The Number to Insert: ";
            cin>>x;
            h1->Insert(x);
        }
        if(n==2)
        {
            cout<<"Enter The Number to Insert: ";
            cin>>x;
            h2->Insert(x);
        }
        if(n==3)
        {
            h1->Union(h2);
        }
        if(n==4)
        {
            h1->print();
        }
        if(n==5)
        {
            h2->print();
        }
        if(n==6)
        {
            cout<<h1->findMin()<<endl;
        }
        if(n==7)
        {
            cout<<h1->extractMin()<<endl;
        }
        if(n==0)
        {
            break;
        }

    }


}


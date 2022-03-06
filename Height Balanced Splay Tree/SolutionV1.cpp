#include<bits/stdc++.h>
using namespace std;
class node
{
public:
    int key;
    node *left,*right;
    node(int key)
    {
        this->key   = key;
        left  = NULL;
        right  = NULL;
    }

};
class SplayTree
{
public:
    int length;
    node *root;
    SplayTree();
    node* Insert(int x);
    node* Delete(int x);
    node* Splay(node* rt,int x);
    node* Search(int x);
    node* rightRotate(node *x);
    node* leftRotate(node *x);
    int maxLvl(node *r);
    void printSpace(int n);
    void Print(node *r);
    void printNodeInternal(vector<node*> nodes, int level, int maxLevel);

};
void SplayTree::Print(node *r)
{
    int mxl=maxLvl(root);
    vector<node*> nodes;
    nodes.push_back(root);
    printNodeInternal( nodes, 1, mxl);
}
void SplayTree:: printNodeInternal(vector<node*> nodes, int level, int maxLevel)
{
    if(nodes.empty())
        return;
    bool test=false;
    for(int i=0;i<nodes.size();i++)
    {
        if(nodes[i]!=NULL)
            test=true;
    }
    if(!test)
        return;
    int floor = maxLevel - level;
    int endgeLines = (int) pow(2, (max(floor - 1, 0)));
    int firstSpaces = (int) pow(2, (floor)) - 1;
    int betweenSpaces = (int) pow(2, (floor + 1)) - 1;
    printSpace(firstSpaces);
    vector<node*> newnodes;
    for(int i=0;i<nodes.size();i++)
    {
        if(nodes[i]!=NULL)
        {
            cout<<nodes[i]->key;
            newnodes.push_back(nodes[i]->left);
            newnodes.push_back(nodes[i]->right);
        }
        else
        {
            newnodes.push_back(NULL);
            newnodes.push_back(NULL);
            cout<<" ";
        }
        printSpace(betweenSpaces);
    }
    cout<<endl;
    for(int i=1;i<=endgeLines;i++)
    {
        for(int j=0;j<nodes.size();j++)
        {
            printSpace(firstSpaces-i);
            if(nodes[j]==NULL)
            {
                printSpace(endgeLines + endgeLines + i + 1);
                continue;
            }
            if (nodes[j]->left != NULL)
                    cout<<"/";
            else
                 printSpace(1);
            printSpace(i+i-1);
            if (nodes[j]->right!=NULL)
                cout<<"\\";
            else
                printSpace(1);

            printSpace(endgeLines + endgeLines - i);
        }
        cout<<endl;
    }
    printNodeInternal(newnodes,level+1,maxLevel);
}
int SplayTree::maxLvl(node *r)
{
    if (r == NULL)
            return 0;
    return max(maxLvl(r->left),maxLvl(r->right)) + 1;
}
void SplayTree::printSpace(int n)
{
    for(int i=0;i<n;i++)
        cout<<" ";
}
node* SplayTree::leftRotate(node *x)
{
    node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}
node* SplayTree::rightRotate(node *x)
{
    node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}
SplayTree::SplayTree()
{
    length=0;
    root=NULL;
}
node* SplayTree::Splay(node *rt,int x)
{
    if (rt == NULL || rt->key == x)
        return rt;

    if (rt->key > x)
    {
        if (rt->left == NULL) return rt;
        if (rt->left->key > x)
        {
            rt->left->left = Splay(rt->left->left, x);
            rt = rightRotate(rt);
        }
        else if (rt->left->key < x)
        {
            rt->left->right = Splay(rt->left->right, x);
            if (rt->left->right != NULL)
                rt->left = leftRotate(rt->left);
        }
        if(rt->left == NULL)
        {
            root=rt;
            return rt;
        }
        else
        {
            root=rightRotate(rt);
            return root;
        }

    }
    else
    {
        if (rt->right == NULL) return rt;

        if (rt->right->key > x)
        {
            rt->right->left = Splay(rt->right->left, x);

            if (rt->right->left != NULL)
                rt->right = rightRotate(rt->right);
        }
        else if (rt->right->key < x)
        {
            rt->right->right = Splay(rt->right->right, x);
            rt = leftRotate(rt);
        }
        if(rt->right == NULL)
        {
            root=rt;
            return root;
        }
        else
        {
            root=leftRotate(rt);
            return root;
        }
    }
}
node* SplayTree::Insert(int x)
{
    if(root==NULL)
    {
        root=new node(x);
        return root;
    }
    else
    {
        node *n=root;
        node *np;
        while(n!=NULL)
        {
            if(x>=n->key)
            {
                np=n;
                n=n->right;
            }
            else
            {
                np=n;
                n=n->left;
            }

        }
        if(x>=np->key)
            np->right=new node(x);
        else
            np->left=new node(x);
    }
    return Splay(root,x);
}
node* SplayTree::Search(int x)
{
    node *n=Splay(root,x);
    if(n->key==x)
        cout<<"The item "<<x<<" was found"<<endl;
    else
        cout<<"The item "<<x<<" was not found"<<endl;
}
node* SplayTree::Delete(int x)
{
    Splay(root,x);
    if(root->key!=x)
        return root;
    else
    {
        node* temp=root->right;
        node*t2=root;
        bool entry=false;
        if(temp!=NULL)
        {
            while(temp->left!=NULL)
            {
                entry=true;
                t2=temp;
                temp=temp->left;
            }
            if(entry)
            {
                t2->left=temp->right;
                int t=temp->key;
                temp=NULL;
                node* r=new node(t);
                r->left=root->left;
                r->right=root->right;
                root=r;
            }
            else
            {
                int t=temp->key;
                node* r=new node(t);
                r->left=root->left;
                r->right=temp->right;
                root=r;
            }

        }
        else
        {
            root=root->left;
        }
        length--;
        return root;
    }
}
main()
{
    SplayTree T;
    int x,n;
    while(true)
    {
        cout<<"1.Insert  2.Splay   3.Delete"<<endl<<"4.Search   5.Print  0.Exit"<<endl;
        cout<<"Enter Your Choice: ";
        cin>>n;
        if(n==1)
        {
            cout<<"Enter The Number to Insert: ";
            cin>>x;
            T.Insert(x);
        }
        if(n==2)
        {
            cout<<"Enter The Number to Splay: ";
            cin>>x;
            T.Splay(T.root,x);
        }
        if(n==3)
        {
            cout<<"Enter The Number to Delete: ";
            cin>>x;
            T.Delete(x);
        }
        if(n==4)
        {
            cout<<"Enter The Number to Search: ";
            cin>>x;
            T.Search(x);
        }
        if(n==5)
        {
            T.Print(T.root);
        }
        if(n==0)
        {
            break;
        }

    }
}

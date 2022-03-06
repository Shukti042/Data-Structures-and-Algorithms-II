#include<bits/stdc++.h>
using namespace std;
#define NULL_VALUE -99999
#define NULL_VALUE2 -9999999
int val=1,hash1ChainCol=0,hash1DoubleCol=0,hash1CustomCol=0;
float hash1ChainHit=0,hash1Doublehit=0,hash1Customhit=0;
int hash1ChainCol2=0,hash1DoubleCol2=0,hash1CustomCol2=0;
float hash1ChainHit2=0,hash1Doublehit2=0,hash1Customhit2=0;
string wordGenerator()
{
    int r;
    r=rand();
    string s="";
    s.push_back('a'+(r%26));
    for(int i=1;i<=6;i++)
    {
        r=rand();
        s.push_back('a'+(r%26));
    }
    return s;
}

long long Hash1(string s,int sz)
{
    const int p = 31;
    const int m = 1000000009;
    long long hash_value = 0;
    long long p_pow = 1;
    char c;
    for (int i=0;i<s.length();i++)
    {
        c=s[i];
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value%sz;
}
unsigned long Hash2(string str,int sz)
{
    unsigned long Hash = 7;
    int c;

    for(int i=0;i<str.length();i++)
    {
        c=str[i];
        Hash ^= (Hash<<5)+(Hash>>2)+c;
    }
    return Hash%sz;
}

int auxHash(string s,int sz)
{
    int r=0;
    for(int i=0;i<s.length();i++)
        r+=s[i];
    return r%sz;
}

class item
{
public:
    string str;
    int value;
    item(string s,int v)
    {
        str=s;
        value=v;
    }
    item()
    {
        str="";
        value=NULL_VALUE;
    }
    bool operator == (const item& it)
    {
        if(it.str.compare(str)==0)
            return true;
        return false;
    }
    bool isEmpty()
    {
        return value==NULL_VALUE;
    }
};


class chainingHash
{
    int len;
    list<item> *chainTable;
public:
    chainingHash(int sz);
    void Insert(string key,int va);
    int Search(string key);
    void Delete(string key);

};
chainingHash::chainingHash(int sz)
{
    len=sz;
    chainTable=new list<item>[sz];
}
void chainingHash::Insert(string key,int va)
{
    int hash_key=Hash1(key,len);
    bool found=false;
    for(list<item>::iterator it=chainTable[hash_key].begin();it!=chainTable[hash_key].end();++it)
    {
        if(key.compare(it->str)==0)
            found=true;
    }
    if(!found)
    {
        if(chainTable[hash_key].size()!=0)
            hash1ChainCol++;
        item t(key,va);
        chainTable[hash_key].push_back(t);
        val++;
    }
}
void chainingHash::Delete(string key)
{
    item t(key,0);
    int hash_key=Hash1(key,len);
    chainTable[hash_key].remove(t);
}
int chainingHash::Search(string key)
{
    int hash_key=Hash1(key,len);
    int v=NULL_VALUE;
    for(list<item>::iterator it=chainTable[hash_key].begin();it!=chainTable[hash_key].end();++it)
    {
        hash1ChainHit++;
        if(key.compare(it->str)==0)
        {
            v=it->value;
            break;
        }
    }
    return v;
}



class chainingHash2
{
    int len;
    list<item> *chainTable;
public:
    chainingHash2(int sz);
    void Insert(string key,int va);
    int Search(string key);
    void Delete(string key);

};
chainingHash2::chainingHash2(int sz)
{
    len=sz;
    chainTable=new list<item>[sz];
}
void chainingHash2::Insert(string key,int va)
{
    int hash_key=Hash2(key,len);
    bool found=false;
    for(list<item>::iterator it=chainTable[hash_key].begin();it!=chainTable[hash_key].end();++it)
    {
        if(key.compare(it->str)==0)
            found=true;
    }
    if(!found)
    {
        if(chainTable[hash_key].size()!=0)
            hash1ChainCol2++;
        item t(key,va);
        chainTable[hash_key].push_back(t);
    }
}
void chainingHash2::Delete(string key)
{
    item t(key,0);
    int hash_key=Hash2(key,len);
    chainTable[hash_key].remove(t);
}
int chainingHash2::Search(string key)
{
    int hash_key=Hash2(key,len);
    int v=NULL_VALUE;
    for(list<item>::iterator it=chainTable[hash_key].begin();it!=chainTable[hash_key].end();++it)
    {
        hash1ChainHit2++;
        if(key.compare(it->str)==0)
        {
            v=it->value;
            break;
        }
    }
    return v;
}


class doubleHash
{
    item *doubleTable;
    int len;
public:
    doubleHash(int sz);
    void Insert(string key,int value);
    int DoubleHash(string key,int i);
    int Search(string key);
    void Delete(string key);

};

doubleHash::doubleHash(int sz)
{
    len=sz;
    doubleTable=new item[sz];
}
int doubleHash::DoubleHash(string key,int i)
{
    int r=(Hash1(key,len) + i *(auxHash(key,len))) % len;
    return r;
}
void doubleHash::Insert(string key,int v)
{
    for(int i=0;;i++)
    {
        int index=DoubleHash(key,i);
        if(doubleTable[index].str.compare(key)==0)
        {
            break;
        }
        else if(index==Hash1(key,len)&&i!=0)
        {
            break;
        }
        else if(!doubleTable[index].isEmpty()&&doubleTable[index].value!=NULL_VALUE2)
        {
            hash1DoubleCol++;
        }
        else
        {
            doubleTable[index].str=key;
            doubleTable[index].value=v;
            break;
        }
    }

}
int doubleHash::Search(string key)
{
    for(int i=0;;i++)
    {
        hash1Doublehit++;
        int index=DoubleHash(key,i);
        if(doubleTable[index].str.compare(key)==0)
        {
            return doubleTable[index].value;
        }
        else if(index==Hash1(key,len)&&i!=0)
        {
            return NULL_VALUE;
        }
        else if(doubleTable[index].isEmpty())
        {
            return NULL_VALUE;
        }

    }
}
void doubleHash::Delete(string key)
{
    for(int i=0;;i++)
    {
        int index=DoubleHash(key,i);
        if(doubleTable[index].str.compare(key)==0)
        {
            doubleTable[index].value=NULL_VALUE2;
            doubleTable[index].str="";
        }
        else if(index==Hash1(key,len)&&i!=0)
        {
            return ;
        }
        else if(doubleTable[index].isEmpty())
        {
            return ;
        }

    }
}



class doubleHash2
{
    item *doubleTable;
    int len;
public:
    doubleHash2(int sz);
    void Insert(string key,int value);
    int DoubleHash(string key,int i);
    int Search(string key);
    void Delete(string key);

};

doubleHash2::doubleHash2(int sz)
{
    len=sz;
    doubleTable=new item[sz];
}
int doubleHash2::DoubleHash(string key,int i)
{
    int r=(Hash2(key,len) + i *(auxHash(key,len))) % len;
    return r;
}
void doubleHash2::Insert(string key,int v)
{
    for(int i=0;;i++)
    {
        int index=DoubleHash(key,i);
        if(doubleTable[index].str.compare(key)==0)
        {
            break;
        }
        else if(index==Hash2(key,len)&&i!=0)
        {
            break;
        }
        else if(!doubleTable[index].isEmpty()&&doubleTable[index].value!=NULL_VALUE2)
        {
            hash1DoubleCol2++;
        }
        else
        {
            doubleTable[index].str=key;
            doubleTable[index].value=v;
            break;
        }
    }

}
int doubleHash2::Search(string key)
{
    for(int i=0;;i++)
    {
        hash1Doublehit2++;
        int index=DoubleHash(key,i);
        if(doubleTable[index].str.compare(key)==0)
        {
            return doubleTable[index].value;
        }
        else if(index==Hash2(key,len)&&i!=0)
        {
            return NULL_VALUE;
        }
        else if(doubleTable[index].isEmpty())
        {
            return NULL_VALUE;
        }

    }
}
void doubleHash2::Delete(string key)
{
    for(int i=0;;i++)
    {
        int index=DoubleHash(key,i);
        if(doubleTable[index].str.compare(key)==0)
        {
            doubleTable[index].value=NULL_VALUE2;
            doubleTable[index].str="";
        }
        else if(index==Hash2(key,len)&&i!=0)
        {
            return ;
        }
        else if(doubleTable[index].isEmpty())
        {
            return ;
        }

    }
}


class customHash
{
    item *customTable;
    int len;
public:
    customHash(int sz);
    void Insert(string key,int value);
    int CustomHash(string key,int i);
    int Search(string key);
    void Delete(string key);

};

customHash::customHash(int sz)
{
    len=sz;
    customTable=new item[sz];
}
int customHash::CustomHash(string key,int i)
{
    int r=(Hash1(key,len) + (7*i*(auxHash(key,len))) + (11*i*i)) % len;
    return r;
}
void customHash::Insert(string key,int v)
{
    for(int i=0;;i++)
    {
        int index=CustomHash(key,i);
        if(customTable[index].str.compare(key)==0)
        {
            break;
        }
        else if(index==Hash1(key,len)&&i!=0)
        {
            break;
        }
        else if(!customTable[index].isEmpty()&&customTable[index].value!=NULL_VALUE2)
        {
            hash1CustomCol++;
        }
        else
        {
            customTable[index].str=key;
            customTable[index].value=v;
            break;
        }
    }

}
int customHash::Search(string key)
{
    for(int i=0;;i++)
    {
        hash1Customhit++;
        int index=CustomHash(key,i);
        if(customTable[index].str.compare(key)==0)
        {
            return customTable[index].value;
        }
        else if(index==Hash1(key,len)&&i!=0)
        {
            return NULL_VALUE;
        }
        else if(customTable[index].isEmpty())
        {
            return NULL_VALUE;
        }

    }
}
void customHash::Delete(string key)
{
    for(int i=0;;i++)
    {
        int index=CustomHash(key,i);
        if(customTable[index].str.compare(key)==0)
        {
            customTable[index].value=NULL_VALUE2;
            customTable[index].str="";
        }
        else if(index==Hash1(key,len)&&i!=0)
        {
            return ;
        }
        else if(customTable[index].isEmpty())
        {
            return ;
        }

    }
}




class customHash2
{
    item *customTable;
    int len;
public:
    customHash2(int sz);
    void Insert(string key,int value);
    int CustomHash(string key,int i);
    int Search(string key);
    void Delete(string key);

};

customHash2::customHash2(int sz)
{
    len=sz;
    customTable=new item[sz];
}
int customHash2::CustomHash(string key,int i)
{
    int r=(Hash2(key,len) + (7*i*(auxHash(key,len))) + (11*i*i)) % len;
    return r;
}
void customHash2::Insert(string key,int v)
{
    for(int i=0;;i++)
    {
        int index=CustomHash(key,i);
        if(customTable[index].str.compare(key)==0)
        {
            break;
        }
        else if(index==Hash2(key,len)&&i!=0)
        {
            break;
        }
        else if(!customTable[index].isEmpty()&&customTable[index].value!=NULL_VALUE2)
        {
            hash1CustomCol2++;
        }
        else
        {
            customTable[index].str=key;
            customTable[index].value=v;
            break;
        }
    }

}
int customHash2::Search(string key)
{
    for(int i=0;;i++)
    {
        hash1Customhit2++;
        int index=CustomHash(key,i);
        if(customTable[index].str.compare(key)==0)
        {
            return customTable[index].value;
        }
        else if(index==Hash2(key,len)&&i!=0)
        {
            return NULL_VALUE;
        }
        else if(customTable[index].isEmpty())
        {
            return NULL_VALUE;
        }

    }
}
void customHash2::Delete(string key)
{
    for(int i=0;;i++)
    {
        int index=CustomHash(key,i);
        if(customTable[index].str.compare(key)==0)
        {
            customTable[index].value=NULL_VALUE2;
            customTable[index].str="";
        }
        else if(index==Hash2(key,len)&&i!=0)
        {
            return ;
        }
        else if(customTable[index].isEmpty())
        {
            return ;
        }

    }
}



main()
{
    srand(time(0));
    int n;
    cin>>n;
    chainingHash chain(n);
    doubleHash dob(n);
    customHash cus(n);
    chainingHash2 chain2(n);
    doubleHash2 dob2(n);
    customHash2 cus2(n);
    vector<string> st;
    string temporary;
    for(int i=1;i<=10000;i++)
    {
        temporary=wordGenerator();
        st.push_back(temporary);
        dob2.Insert(temporary,val);
        cus2.Insert(temporary,val);
        chain2.Insert(temporary,val);
        dob.Insert(temporary,val);
        cus.Insert(temporary,val);
        chain.Insert(temporary,val);
    }
    int j;
    for(int i=0;i<1000;i++)
    {
        j=rand()%10000;
        chain.Search(st[j]);
        dob.Search(st[j]);
        cus.Search(st[j]);
        chain2.Search(st[j]);
        dob2.Search(st[j]);
        cus2.Search(st[j]);
    }
    cout<<endl<<"-------------------HASH 1---------------------"<<endl<<endl;
    cout<<"                  No of Collision"<<"      "<<"Average Hit"<<endl;
    cout<<"Chaining Method   "<<hash1ChainCol<<"                   "<<hash1ChainHit/1000<<endl;
    cout<<"Custom Probing    "<<hash1CustomCol<<"                  "<<hash1Customhit/1000<<endl;
    cout<<"Double Hashing    "<<hash1DoubleCol<<"                  "<<hash1Doublehit/1000<<endl;
    cout<<endl<<"-------------------HASH 2---------------------"<<endl<<endl;
    cout<<"                  No of Collision"<<"      "<<"Average Hit"<<endl;
    cout<<"Chaining Method   "<<hash1ChainCol2<<"                   "<<hash1ChainHit2/1000<<endl;
    cout<<"Custom Probing    "<<hash1CustomCol2<<"                  "<<hash1Customhit2/1000<<endl;
    cout<<"Double Hashing    "<<hash1DoubleCol2<<"                  "<<hash1Doublehit2/1000<<endl;
    /*customHash2 s(1000);
    s.Insert("hello",5);
    s.Insert("hello",9);
    cout<<s.Search("hello")<<endl;
    s.Delete("hello");
    cout<<s.Search("hello")<<endl;
    s.Insert("hello",10);
    cout<<s.Search("hello")<<endl;*/


}

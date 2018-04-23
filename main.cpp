#include <bits/stdc++.h>

using namespace std;
int counter=0;
const int tablesize=997;
const int bucket=2;
int counter1=0;
vector<int>avaar1;
vector<int>avaar2;
vector<int>avaar3;
vector<int>avaar4;

void openf(fstream &f,string s)
{
    f.open( s , ios::in|ios::out) ;
}
struct student
{
    int id;
    char name [51];
};
istream& operator>>(istream& in , student& s)
{
    in>>s.id;
    in.getline( s.name , 51 ) ;
    return in ;
}
ostream& operator<<( ostream& out , student& s )
{
    out << "id: " << s.id << endl ;
    out << "Name: " << s.name << endl ;
    return out ;
}
struct HashIndex
{
    int id;
    int offset;
};
void initializeFile(fstream& ofile)
{

    HashIndex hi;
    hi.offset=-1;

    for(int i = 0 ;  i < tablesize ; i++)
    {
        for(int j = 0 ;  j < bucket ; j++)
            ofile.write((char*)&hi,sizeof(HashIndex));

    }
}
HashIndex  arr[tablesize][bucket];
int add_at_end(student S,fstream& f)
{
    string s="main.txt";
    openf(f,s);
    f.seekp(0,ios::end);
    int t=f.tellp();
    f.write((char*)&S,sizeof S);
    f.close();
    return t;
}
void construct_hash_table(fstream &f)
{
    string hashfile_name="hash.txt";
    openf(f,hashfile_name);
    for(int i=0; i<tablesize; i++)
    {
        for (int j=0; j<bucket; j++)
        {
            HashIndex in=arr[i][j];
            f.write((char*)&in,sizeof(in));
        }
    }
    f.close();
}
void inialize_hash_table()
{

    for(int i=0; i<tablesize; i++)
    {
        for (int j=0; j<bucket; j++)
        {
            arr[i][j].id=-1;
        }
    }
}


/************************method 1************************************/

int mult_hash(int key)
{
    double decimal_point = 0.61803398863412439823150634765625;
    double exp = decimal_point*(key);
    return tablesize*(exp - (int) exp);
}
void addStudent(student s, fstream& f1)
{

    int offset=add_at_end(s,f1);
    HashIndex h;
    h.id=s.id;
    h.offset=offset;
    int RRN = mult_hash(s.id);
    if(arr[RRN][0].id==-1)
        arr[RRN][0]=h;
    else if(arr[RRN][1].id==-1)
        arr[RRN][1]=h;
    else
    {
        RRN++;
        while (arr[RRN][0].id != -1||arr[RRN][0].id!=-1)
        {
            if(arr[RRN][0].id==-1)
            {
                arr[RRN][0]=h;
                break;
            }
            else if(arr[RRN][1].id==-1)
            {
                arr[RRN][1]=h;
                break;
            }

        }
    }


    return ;
}
pair<HashIndex,pair<int,int> > searchStudent(int id)
{ int i=1;
    int RRN=mult_hash(id);
    if(arr[RRN][0].id==id)
     {
            avaar1.push_back(i+avaar1[avaar1.size()-1]);
       return (make_pair(arr[RRN][0],make_pair(RRN,0)));}
    else if(arr[RRN][1].id==id)
     {
       avaar1.push_back(i+avaar1[avaar1.size()-1]);
     return (make_pair(arr[RRN][1],make_pair(RRN,1)));}
    else
    {
        RRN++;

        while (arr[RRN][0].id!=id||arr[RRN][1].id!=id)
        {
            if(arr[RRN][0].id==id)
            {
                  avaar1.push_back(i+avaar1[avaar1.size()-1]);
                return (make_pair(arr[RRN][0],make_pair(RRN,0)));
            }
            else if(arr[RRN][1].id==id)
            {

                   avaar1.push_back(i+avaar1[avaar1.size()-1]);

               return (make_pair(arr[RRN][1],make_pair(RRN,1)));
            }
            i++;
            RRN++;
        }
    }
    cout<<"the id not found"<<endl;
    HashIndex h;
    h.id=-2;
    h.offset=-2;
   return (make_pair(h,make_pair(-1,-1)));
}

void deleteStudent(int id, fstream& ifile)
{
 pair<HashIndex,pair<int,int>> s=searchStudent(id);
    if (s.first.id ==-2)
    {
        return ;
    }
    int ofseet=s.first.offset;
    string file_name="main.txt";
    openf(ifile,file_name);
    ifile.seekp(ofseet,ios::beg);
    char d='*';
    ifile.write((char*)&d,sizeof d);
    arr[s.second.first][s.second.second].id=-2;
      arr[s.second.first][s.second.second].offset=-2;
    ifile.close();
}

/************************method 2************************************/


int quadtric_probing(int key )
{
    int h=mult_hash(key);
    h=(h+(counter*counter))%tablesize;
    return h;
}

void add_student_using_hashing2(student s,fstream& f)
{
    int ID=s.id;
    int ofseet=add_at_end(s,f);
    HashIndex h;
    h.id=ID;
    h.offset=ofseet;
    int key =mult_hash(ID);
    if (arr[key][0].id==-1)
    {
        arr[key][0]=h;
    }
    else
    {

        if (arr[key][1].id==-1)
        {
            arr[key][1]=h;
        }
        else
        {
            while(true)
            {
                key=quadtric_probing(ID);
                if (arr[key][0].id==-1)
                {
                    arr[key][0]=h;
                    counter=0;
                    break;
                }
                else if (arr[key][1].id==-1)
                {
                    arr[key][1]=h;
                    counter=0;
                    break;
                }
                else
                {
                    counter++;
                    if(key>=tablesize){
                        counter=0;
                        break;
                    }

                }
            }
        }
    }
}
pair<HashIndex,pair<int,int>> searchenooo2(int ID)
{
int i=1;
    int z=mult_hash(ID);

    if (arr[z][0].id==ID)
    {
         avaar2.push_back(i+avaar2[avaar2.size()-1]);
        return make_pair(arr[z][0],make_pair(z,0));
    }
    else
    {

        if (arr[z][1].id==ID)
        {
             avaar2.push_back(i+avaar2[avaar2.size()-1]);
            return make_pair(arr[z][1],make_pair(z,1));
        }
        else
        {
            while(true)
            {
                int key=quadtric_probing(ID);
                if (arr[key][0].id==ID)
                {
                         avaar2.push_back(i+avaar2[avaar2.size()-1]);
                    counter=0;
                  return make_pair(arr[key][0],make_pair(key,0));
                }
                else if (arr[key][1].id==ID)
                {   avaar2.push_back(i+avaar2[avaar2.size()-1]);
                    counter=0;
                     return make_pair(arr[key][1],make_pair(key,1));
                }
                else{
                     i++;
                    counter++;
                    if(key>=tablesize){
                        counter=0;
                        break;
                    }
            }}
        }
    }
    cout<<"the id not found"<<endl;
    HashIndex h;
    h.id=-2;
    h.offset=-2;
    return make_pair(h,make_pair(-1,-1));
}

void deletoooo2(int ID,fstream& f)
{
 pair<HashIndex,pair<int,int>> s=searchenooo2(ID);
    if (s.first.id ==-2)
    {
        return ;
    }
    int ofseet=s.first.offset;
    string file_name="main.txt";
    openf(f,file_name);
    f.seekp(ofseet,ios::beg);
    char d='*';
    f.write((char*)&d,sizeof d);
    arr[s.second.first][s.second.second].id=-2;
      arr[s.second.first][s.second.second].offset=-2;
    f.close();
}
/*********************method 3***********************************/

int mid_square(int key)
{
    int temp;
    if(key>9999)
    {
        for (int i=10;; i*=10)
        {
            if(key%i<=9999)
            {
                temp=i;
                break;
            }
        }
        temp=pow(10,temp);
        key&=temp;
    }
    key=pow(key,2);
    temp=0;
    for(int i=10;; i*=10)
    {
        if(key%i<=10)
        {
            temp=i;
            break;
        }
    }
    switch(temp)
    {
    case 4:

    {
        double a=key/1000.0;
        key/=1000;
        a-=key;
        a*=1000;
        key=a;
        break;
    }

    case 5:
    {
        key%=10;
        double a=key/1000.0;
        key/=1000;
        a-=key;
        a*=1000;
        key=a;
        break;
    }
    case 6:
    {
        key%=10;
        double a=key/10000.0;
        key/=10000;
        a-=key;
        a*=10000;
        key=a;
        break;
    }
    case 7:
    {
        key%=100;
        double a=key/1000.0;
        key/=1000;
        a-=key;
        a*=1000;
        key=a;
        break;
    }
    case 8:
    {
        key%=100;
        double a=key/1000.0;
        key/=1000;
        a-=key;
        a*=1000;
        key=a;
        break;
    }

    }
    return key;
}
int floding(int key)
{
    while(key>999999999)
    {
        int x;
        cout<<"wrong key enter again\n";
        cin>>x;
        key=x;
    }
    int temp=0;
    for(int i=10;; i*=10)
    {
        if(key%i<=10)
        {
            temp=i;
            break;
        }
    }
    temp++;
    while((temp)%3!=0)
    {
        key*=10;
        temp++;
    }
    int temp2,a[temp],sum=0;
    double temp3;
    temp/=3;
    for(int i=0; i<3; i++)
    {
        temp2=key;
        temp3=key;
        temp2/=temp;
        temp3/=temp;
        temp3-=temp2;
        temp3*=temp;
        a[i]=temp3;
        key/=temp;
    }
    sum=a[0]+a[1]+a[2];
    key=sum;
    return key;
}
int double_hashing(int key)
{
    int h1,h2,h3;
    h1=floding(key);
    h2=mid_square(key);
    h3=(h1+(counter*h2))%tablesize;
    return h3;
}
void add_student_using_hashing3(student s,fstream &f)
{
    int ID=s.id;
    int ofseet=add_at_end(s,f);
    HashIndex h;
    h.id=ID;
    h.offset=ofseet;
    int z =floding(ID);
    int key;
    if (arr[z][0].id==-1)
    {
        arr[z][0]=h;
    }
    else
    {

        if (arr[z][1].id==-1)
        {
            arr[z][1]=h;
        }
        else
        {
            while(true)
            {
                key=double_hashing(ID);
                if (arr[key][0].id==-1)
                {
                    arr[key][0]=h;
                    counter1=0;
                    break;
                }
                else if (arr[key][1].id==-1)
                {
                    arr[key][1]=h;
                    counter1=0;
                    break;
                }
                else
                {
                    counter1++;
                    if (key>=tablesize)
                    {
                      counter1=0;
                       break;
                    }
                }
            }
        }
    }
}

pair<HashIndex,pair<int,int>> searchenooo3(int ID)
{    int i=1;
      int z=floding(ID);

    if (arr[z][0].id==ID)
    {
            avaar3.push_back(i+avaar3[avaar3.size()-1]);
        return make_pair(arr[z][0],make_pair(z,0));
    }
    else
    {

        if (arr[z][1].id==ID)
        {
               avaar3.push_back(i+avaar3[avaar3.size()-1]);
            return make_pair(arr[z][1],make_pair(z,1));
        }
        else
        {
            while(true)
            {
             int key=double_hashing(ID);
                 if (arr[key][0].id==ID)
                {
                      avaar3.push_back(i+avaar3[avaar3.size()-1]);
                    counter=0;
                  return make_pair(arr[key][0],make_pair(key,0));
                }
                else if (arr[key][1].id==ID)
                {
                       avaar3.push_back(i+avaar3[avaar3.size()-1]);
                    counter=0;
                     return make_pair(arr[key][1],make_pair(key,1));
                }
                else{
                        i++;
                    counter++;
                    if(key>=tablesize){
                        counter=0;
                        break;
                    }
            }}
        }
    }
    cout<<"the id not found"<<endl;
    HashIndex h;
    h.id=-2;
    h.offset=-2;
    return make_pair(h,make_pair(-1,-1));
}

void deletoooo3(int ID,fstream& f)
{
 pair<HashIndex,pair<int,int>> s=searchenooo3(ID);
    if (s.first.id ==-2)
    {
        return ;
    }
    int ofseet=s.first.offset;
    string file_name="main.txt";
    openf(f,file_name);
    f.seekp(ofseet,ios::beg);
    char d='*';
    f.write((char*)&d,sizeof d);
    arr[s.second.first][s.second.second].id=-2;
      arr[s.second.first][s.second.second].offset=-2;
    f.close();
}

/*********************method 4***********************************/
struct index1
{
int id;
int offset;
int index=-1;
};
index1 arr1[tablesize][bucket];
index1 arr2[1000];
int counter2=-1;
void inialize_hash_table1()
{

    for(int i=0; i<tablesize; i++)
    {
        for (int j=0; j<bucket; j++)
        {
            arr1[i][j].id=-1;

        }
    }
     for (int h=0; h<1000; h++)
        {
            arr2[h].id=-1;

        }
}

void add_student_using_hashing4(student s,fstream &f)
{
   int ID=s.id;
    int ofseet=add_at_end(s,f);
    index1 h;
    h.id=ID;
    h.offset=ofseet;
    int z =mult_hash(ID);
    int key;
    if (arr1[z][0].id==-1)
    {
        arr1[z][0]=h;
    }
    else if (arr1[z][1].id==-1)
        {
            arr1[z][1]=h;
        }
        else {
                  counter2++;
                  if(arr1[z][0].index==-1){
                  arr1[z][0].index=counter2;
                  }
           else {
                  if(arr2[arr1[z][0].index].index==-1)
                 arr2[arr1[z][0].index]=h;
                 else {
                      int x=arr2[arr1[z][0].index].index;
                   while (arr2[x].index!=-1) {
                  x= arr2[x].index;
           }
           arr2[x].index=counter2;
           arr2[counter2]=h;}
           }
        }
}
index1  serchenooo4(int ID){
   int i=1;
 int z =mult_hash(ID);
    int key;
    if (arr1[z][0].id==ID)
    {
           avaar4.push_back(i+avaar4[avaar4.size()-1]);
       return arr1[z][0];
    }
    else if (arr1[z][1].id==ID)
        {
               avaar4.push_back(i+avaar4[avaar4.size()-1]);
            return arr1[z][1];
        }
           else {
                  if(arr2[arr1[z][0].index].id==ID)
               {
                      avaar4.push_back(i+avaar4[avaar4.size()-1]);
                 return arr2[arr1[z][0].index];}
                 else {
                      int x=arr2[arr1[z][0].index].index;
                   while (x!=-1) {
                              if (arr2[x].id=ID){
                                           avaar4.push_back(i+avaar4[avaar4.size()-1]);
                                    return arr2[x];

                              }
                              i++;
                  x= arr2[x].index;
           }}
           }
        }

void deletoooo4(int ID,fstream& f)
{
    index1 h =serchenooo4(ID);
    int ofseet=h.offset;
    if (h.id==-2)
    {
        return ;
    }
    string file_name="main.txt";
    openf(f,file_name);
    f.seekp(ofseet,ios::beg);
    char d='*';
    f.write((char*)&d,sizeof d);
    h.id=-2;
    h.offset=-2;
    f.close();
    return;
}
/***************************another functions for all**********/
int *rand_id(int* arr)
{
    arr=new int [500];
    int x;
    for(int i=0; i<500; i++)
    {
        srand(time(NULL));
        x= rand() % 10000 + 1;
        for(int j=0; j<i; j++)
        {
            while(x==arr[j])
            {
                x=rand() % 10000 + 1;
                if(x!=arr[j])
                    break;
            }
        }
        arr[i]=x;
    }
    return arr;
}
student* make_student()
{
    student arrr[500];
    int *a,*b;
    string x="record",y[500];
    b=rand_id(a);
    for(int i=0; i<500; i++)
    {
        stringstream ss ;
        char tmp[51] ;
        ss<<b[i];
        ss>>tmp;
        ss.clear();
        y[i]= x+ tmp ;
        arrr[i].id=b[i];
        for(int j=0; j<y[i].size(); j++)
        {
            arrr[i].name[j]=y[i][j];
            cout<<arrr[i].name[j];
        }
        cout<<endl;
    }
    return arrr;
}

void rand_id(student* arr, fstream& f)
{
    int x;
    int temp[50];
    srand(time(NULL));
    for(int i=0; i<50; i++)
    {
        x=rand()%500+0;
        for(int j=0; j<i; j++)
        {
            while(x==temp[j])
            {
                x=rand()%500+0;
            }
            temp[i]=x;
        }
    }
    for(int i=0; i<50; i++)
    {
        deletoooo3(arr[i].id,f);
    }
}
void print_all(fstream &b,string x)
{
    student  buffer;
    char mark;
    b.open(x,ios::in| ios::binary);
    if(!b)
    {
        cout<<"File not Found";
        exit(0);
    }
    else
    {
        b.read((char*)&mark, sizeof(mark));
        while(!b.eof())
        {
            if(mark!='*')
            {
                b.seekp(-1,ios::cur);
                b.read((char*)&buffer, sizeof(buffer));
                cout<<buffer;
            }
            else
            {
               b.seekp(sizeof(buffer),ios::cur);
            }
        }
    }
    b.close();
}

int avarage(vector<int>s){
return (s[s.size()-1]/s.size());
}
int main()
{
    student *a;
    a=make_student();
    return 0;
}
// rank 1 is separate chain
//rank 2 is (double and quadtric)
//rank 3 is mult hashing


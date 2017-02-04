#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>

using namespace std;
mutex num_mutex;

int total_sum=0;
void ff(int num[10000],int head,int tail,int ID);

int main()
{
    int num[10000],scale=0,sum,j,head,thread_num=0;
    thread *m[32];
    
    while(cin>>scale>>thread_num)
    {
        sum=0,j=0,head=0;
        
        for(int i=0;i<scale;i++){
            num[i] = (rand()%1000)+1;
            sum += num[i];}
        for(int i=(scale/thread_num);i<=scale;i+=(scale/thread_num)){
            m[j] = new thread (ff,num,head,i,j);
            head+= (scale/thread_num);
            j++;}
        for(int i=j-1;i>=0;i--)
            m[i]->join();
        cout<<"Thread: "<<total_sum<<endl;
        cout<<"Main:   "<<sum<<endl;
        total_sum=0;
    }
    return 0;
}
void ff(int num[10000],int head,int tail,int ID)
{
    num_mutex.lock();
    long long int sum=0;
    for(int i=head;i<tail;i++)
        sum+= num[i];
    cout<<"Thread id: "<<ID<<" total:"<<sum<<endl;
    total_sum += sum;
    num_mutex.unlock();
}

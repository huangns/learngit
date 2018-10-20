#include <thread>
#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
#include <algorithm>
#include <ctime>
using namespace std;

template<typename Iterator,typename T>
struct accumulate_block
{

    void operator()(Iterator first,Iterator last,T& result)
    {
//        cout<<"childThread.\n";
        result=std::accumulate(first,last,result);//区间[),第三个参数为累加的初值
    }
};//结构定义尾部要加上分号

template<typename Iterator,typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
   // cout<<"concurrency.\n";
    unsigned long const length=std::distance(first,last);//数列的长度，first + n  = last,n可能为负
    if(!length)
        return init;
    unsigned long const min_per_thread=25;
    unsigned long const max_threads=(length+min_per_thread-1)/min_per_thread;//!!!!
    unsigned long const hardware_threads=std::thread::hardware_concurrency();
    cout<<"hardware_threads: "<<hardware_threads<<endl;
    unsigned long const num_threads=std::min(hardware_threads!=0?hardware_threads:2,max_threads);
    unsigned long const block_size=length/num_threads;
    std::vector<T> res(num_threads);
    std::vector<std::thread> threads(num_threads-1);//主线程分掉了一个所以减一
    
    Iterator block_start=first;
    for(unsigned long i=0;i<(num_threads-1);++i)
    {
        Iterator block_end=block_start;
        std::advance(block_end,block_size);
        threads[i]=std::thread(
	accumulate_block<Iterator,T>(),
        block_start,block_end,std::ref(res[i]));
        block_start=block_end;
    }
    //剩余的未分配完成的全部都交给主线程
    accumulate_block<Iterator,T>()
    (
        block_start,last,res[num_threads-1]
    );
    //对每一个thread，调用join()成员函数
    std::for_each(threads.begin(),threads.end(),std::mem_fn(&std::thread::join));
    return std::accumulate(res.begin(),res.end(),init);
}
template <typename Iterator,typename T>
T noparallel_accumulate(Iterator first, Iterator last, T init)
{
    return std::accumulate(first,last,init);
}

int main()
{
    int datalen=100000;
    vector<double> v(datalen,1.1);
  
   double parallelres=0.0,noparallelres=0.0;
   clock_t parallel_start,parallel_stop,noparallel_start,noparallel_stop;
   parallel_start=clock();
   parallelres=parallel_accumulate(v.begin(),v.end(),0.0);
   parallel_stop=clock();
   
   noparallel_start=clock();
   noparallelres=noparallel_accumulate(v.begin(),v.end(),0.0);
   noparallel_stop=clock();

   cout<<"compare results:\n";
   cout<<"parallel:\n";
   cout<<"res: "<<parallelres<<endl;
   cout<<"delta time: "<<(double)(parallel_stop-parallel_start)/CLOCKS_PER_SEC;
   cout<<" s.\n noparallel:\n";
   cout<<"res: "<<noparallelres<<endl;
   cout<<"delta time: "<<(double)(noparallel_stop-noparallel_start)/CLOCKS_PER_SEC<<" s.\n";
  // cout<<"hardware_concurrency_num: "<<std::thread::hardware_concurrency<<endl;
    return 0;
}

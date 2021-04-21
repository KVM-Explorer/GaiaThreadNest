#include "GaiaThreadNest/Nest.hpp"
#include "GaiaThreadNest/GaiaThreadNest.hpp"
#include <iostream>
#include <unistd.h>
void Sum()
{
    int x=0;
    std::cout<<"Value:"<<x<<std::endl;
}

void Exc()
{
    int c=10;
    std::cout<<"Exc:"<<c<<std::endl;
}

int main()
{
    Gaia::ThreadNest::Nest pool;

    pool.AddWorker(Sum, 1);
    pool.AddWorkerOnce(Exc);
    pool.Excute();

    sleep(2);
    pool.Destory();

    sleep(3);
    return 0;
}
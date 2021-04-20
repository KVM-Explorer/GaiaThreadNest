#include "GaiaThreadNest/Nest.hpp"
#include "GaiaThreadNest/GaiaThreadNest.hpp"
#include <iostream>
#include <unistd.h>
void Sum()
{
    int x=0;
    std::cout<<"Value:"<<++x<<std::endl;
}

int main()
{
    Gaia::ThreadNest::Nest pool;

    pool.AddWorker(Sum, 1);

    pool.Excute();

    sleep(100);
    return 0;
}
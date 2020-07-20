#include <iostream>
#include <thread>


void hello()
{
    std::cout << " Hello " << std::endl;
}

void world()
{
    std::cout << " World. " << std::endl;
}

int main()
{
    // call with two new threads
    std::thread t1(hello);
    std::thread t2(world);

    // TODO: join the threads with the main thread
    t1.join();
    t2.join();


    return 0;
}

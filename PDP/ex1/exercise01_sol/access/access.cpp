#include <iostream>
#include <thread>
#include <mutex>
#include <unordered_map>

int A[100]; /* global variable */

int make_logical_threadid(std::thread::id i)
{
    static int thread_idx = 0;
    static std::mutex thread_mutex;
    static std::unordered_map<std::thread::id, std::size_t> thread_ids;

    std::lock_guard<std::mutex> lock(thread_mutex);
    auto iter = thread_ids.find(i);
    if (iter == thread_ids.end()) {
        iter = thread_ids.insert(std::pair<std::thread::id, std::size_t>(i, thread_idx++)).first;
    }
    return iter->second;
}

void access_one()
{
    int i = make_logical_threadid(std::this_thread::get_id());
    A[i] = rand();
}

void access_two()
{
    int i = make_logical_threadid(std::this_thread::get_id()) % 10;
    A[i] = rand();
}

void access_three()
{
    int i = make_logical_threadid(std::this_thread::get_id());
    A[rand() % 100] = i;
}


int main(int argc, char** argv)
{
    if (argc != 2) {
	std::cout << "Expected exactly one argument!" << std::endl;
        return -1;
    }

    unsigned int num_threads = std::stoi(argv[1]);

    std::thread t[num_threads];
    for (int i = 0; i < num_threads; i++) {
        t[i] = std::thread(access_one);
        //t[i] = std::thread(access_two);
        //t[i] = std::thread(access_three);
    }
    for (int i = 0; i < num_threads; i++) {
        t[i].join();
    }

    return 0;
}

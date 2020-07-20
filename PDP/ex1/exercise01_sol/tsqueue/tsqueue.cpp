#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class threadsafe_queue
{
    private:
        std::queue<T> data;
        std::mutex mut;
        std::condition_variable cond;

    public:
        threadsafe_queue() {}
        threadsafe_queue(threadsafe_queue const& other)
        {
            std::lock_guard<std::mutex> lk(other.mut);
            data = other.data;
        }

        void push(T new_val)
        {
            std::lock_guard<std::mutex> lk(mut);
            data.push(new_val);
            cond.notify_one();
        }

        void wait_and_pop(T& value)
        {
            std::unique_lock<std::mutex> lk(mut);
            cond.wait(lk, [this]{return !data.empty();} );
            value = data.front();
            data.pop();
        }

        bool empty() const
        {
            std::lock_guard<std::mutex> lk(mut);
            return data.empty();
        }

        bool try_pop(T& value)
        {
            std::lock_guard<std::mutex> lk(mut);
            if (data.empty())
                return false;
            value = data.front();
            data.pop();
            return true;
        }
};

int main()
{
    return 0;
}

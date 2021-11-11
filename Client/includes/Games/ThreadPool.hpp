/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-leonard.pooch
** File description:
** ThreadPool.hpp
*/

#ifndef _POOL_
#define _POOL_

#include <condition_variable>
#include <functional>
#include <vector>
#include <thread>
#include <queue>
#include <iostream>
#include <unistd.h>
#include "../Core/Enums.hpp"

template <class T>
class ThreadPool {
public:
    using Task = std::function<void(T)>;

    explicit ThreadPool(std::size_t numThreads) {
        for (std::size_t i = 0; i < numThreads; i++)
            mThreads.emplace_back(std::thread(&ThreadPool::start_thread, this));
    };

~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock{mEventMutex};
        mStopping = true;
    }
    mEventVar.notify_all();
    for (auto &thread : mThreads)
        thread.join();
};

void enqueue(Task task, T v) {
		// std::vector<INPUT> v;
    {
        std::unique_lock<std::mutex> lock{mEventMutex};

		mTasks.emplace(std::move(task));
		mValue.emplace(std::move(v));
    }
    mEventVar.notify_one();
};

private:
void start_thread() {
    while(true) {
        Task task;
			std::vector<INPUT> v;
            {
                std::unique_lock<std::mutex> lock{mEventMutex};
                mEventVar.wait(lock, [this] {return mStopping || !mTasks.empty();});
                if (mStopping && mTasks.empty())
                    break;
                task = std::move(mTasks.front());
				v =  std::move(mValue.front());
				mValue.pop();
                mTasks.pop();
            }
        task(v);
    }
};
private:
    std::vector<std::thread> mThreads;
    std::condition_variable mEventVar;
    std::mutex mEventMutex;
    bool mStopping = false;
    std::queue<Task> mTasks;
    std::queue<T> mValue;
};

#endif
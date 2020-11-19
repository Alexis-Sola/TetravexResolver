#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <vector>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include<thread>
#include<unistd.h>
#include<queue>
#include <future>

using namespace std;

typedef vector<vector<int>> Matrix;

class ThreadPool
{
public:
    //On définit notre Task qui sera la fonction init_thread
    //Prend une Matrix en paramètre
    using Task = function<void(Matrix)>;

    //Constructeur du thread pool et démarre le threadpool avec un certain nombre de thread
    ThreadPool(unsigned numThreads, const Matrix &data);
    ~ThreadPool();

    //La fonction add permet d'ajouter un tâche à la queue
    void add(Task task);

private:
    //tableau de thread
    vector<thread> mThreads;
    condition_variable mEventVar;
    mutex mEventMutex;
    bool mStopping = false;
    //tableau de tâches
    queue<Task> mTasks;
    //démarre le threadpool avec un certain nombre de thread

};
#endif // THREADPOOL_HPP

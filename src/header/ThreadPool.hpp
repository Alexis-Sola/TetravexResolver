#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include "Piece.hpp"
#include "Plateau.hpp"

#include <vector>
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include<thread>
#include<mutex>
#include<unistd.h>
#include<queue>
#include <future>

using namespace std;

class ThreadPool
{
public:
    //Task désignes une fonctions qui ne renvoie rien et qui n'a pas de paramètres
    using Task = function<void(Matrix)>;

    //Constructeur du thread pool
    ThreadPool(size_t numThreads, const Matrix &data);
    ~ThreadPool();

    //La fonction add permet d'ajouter un tâche à la queue
    void add(Task task);

private:
    vector<thread> mThreads;
    condition_variable mEventVar;
    mutex mEventMutex;
    bool mStopping = false;

    queue<Task> mTasks;
    void start(size_t numThreads, const Matrix &data);
    void stop();

};
#endif // THREADPOOL_HPP

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
    ThreadPool(size_t numThreads, const Matrix &data)
    {
        start(numThreads, data);
    }

    ~ThreadPool()
    {
        stop();
    }

    //La fonction add permet d'ajouter un tâche à la queue
    void add(Task task)
    {

        //On lock car on utilise condvar
        unique_lock<mutex> lock(mEventMutex);
        mTasks.emplace(task);

        //On notifie un thread qu'une tâche a été ajouté
        mEventVar.notify_one();
    }

private:
    vector<thread> mThreads;
    condition_variable mEventVar;
    mutex mEventMutex;
    bool mStopping = false;

    queue<Task> mTasks;

    void start(size_t numThreads, const Matrix &data)
    {
        for(size_t i = 0; i < numThreads; i++)
        {
            mThreads.emplace_back([=] {
                while(true)
                {
                    Task task;
                    {
                        //On regarde l'état du mutex
                        unique_lock<mutex> lock(mEventMutex);

                        mEventVar.wait(lock, [=] {
                            return mStopping || !mTasks.empty();
                        });

                        //si mStopping est vrai et qu'il n'y a plus de tache
                        //On sort de la boucle
                        if(mStopping && mTasks.empty())
                            break;

                        //On récupère la première tâche
                        task = mTasks.front();
                        //On supprimme la tâche de la queue
                        mTasks.pop();
                    }

                    //On execute la tache
                    task(data);
                }
            });
        }
    }

    void stop() noexcept
    {
        {
            unique_lock<mutex> lock(mEventMutex);
            mStopping = true;
        }

        //On notifie les threads que l'on doit stopper
        mEventVar.notify_all();

        //On attend que les thread s'arrêtent
        for(auto &thread : mThreads)
            thread.join();
    }

};
#endif // THREADPOOL_HPP

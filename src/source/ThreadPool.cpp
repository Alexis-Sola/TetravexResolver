#include "../header/ThreadPool.hpp"

//Constructeur du thread pool
ThreadPool::ThreadPool(size_t numThreads, const Matrix &data)
{
  start(numThreads, data);
}

ThreadPool::~ThreadPool()
{
  stop();
}

//La fonction add permet d'ajouter un tâche à la queue
void ThreadPool::add(Task task)
{

  //On lock car on utilise condvar
  unique_lock<mutex> lock(mEventMutex);
  mTasks.emplace(task);

  //On notifie un thread qu'une tâche a été ajouté
  mEventVar.notify_one();
}


void ThreadPool::start(size_t numThreads, const Matrix &data)
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

void ThreadPool::stop()
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

#include "../header/ThreadPool.hpp"

//Constructeur qui va lancer un nombre de threads définis
ThreadPool::ThreadPool(unsigned numThreads, const Matrix &data)
{
    //Préparation des threads pour les tâches ques vont attribuées
    for(unsigned i = 0; i < numThreads; i++)
    {
        //On ajoute une méthode au thread
        mThreads.emplace_back([=] {
            //On boucle tant qu'il y a encore des tâches et tant que la pool n'est pas vide
            while(true)
            {
                //Tâches qui sera exécuté dans thread
                Task task;
                {
                    unique_lock<mutex> lock(mEventMutex);

                    //L'exécution du thread est lock
                    //Attend que le prédicat soit vérifié pour être unlock
                    //Le thread sera en attente si mStopping est vrai
                    //Ou s'il n'y plus de tâche dans la file d'attente
                    mEventVar.wait(lock, [=] {
                        return mStopping || !mTasks.empty();
                    });

                    //si mStopping est vrai et qu'il n'y a plus de tache
                    //Le thread n'a plus rien a faire
                    if(mStopping && mTasks.empty())
                        break;

                    //Sinon on récupère la première tâche dans la file
                    task = mTasks.front();
                    //On supprimme la tâche de la file
                    mTasks.pop();

                }
                //On execute la tache
                task(data);
            }
        });
    }
}
//Destructor
ThreadPool::~ThreadPool()
{
    {
        unique_lock<mutex> lock(mEventMutex);
        mStopping = true;

    }
    //On notifie tous les thread de stop and join
    mEventVar.notify_all();
    for(auto &thread : mThreads)
        thread.join();
}
//La fonction add permet d'ajouter un tâche à la queue
void ThreadPool::add(Task task)
{

    unique_lock<mutex> lock(mEventMutex);
    //On ajoute notre tâche à la file d'attente
    mTasks.emplace(task);

    //On notifie un thread en attente qu'une tâche a été ajouté
    mEventVar.notify_one();
}

/*-----------------------------------------------------------------
-                           HackISU S2018
-              Valery S., Leif B., Alek E., Tyler T.
-----------------------------------------------------------------*/
#ifndef THREADEDQUEUE_H
#define THREADEDQUEUE_H

/*-----------------------------------------------------------------
-                           Includes
-----------------------------------------------------------------*/
#include <queue>
#include <mutex>
#include <condition_variable>

/*-----------------------------------------------------------------
-                        Literal Constants
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                           Enumerations
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                             Macros
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                        Forward Declarations
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                             Structs
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                             Functors
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                             Typedefs
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                             Classes
-----------------------------------------------------------------*/
template<typename T>
class ThreadedQueue
{
    private:
        std::queue<T>           collection;
        mutable std::mutex      mu_queue;
        std::condition_variable cond_var;

    public:
        ThreadedQueue()
            : collection()
            , mu_queue()
            , cond_var()
        {};

        ~ThreadedQueue(){};

        inline bool empty()
        {
            std::lock_guard<std::mutex> lock( mu_queue );
            return collection.empty();
        }

        inline size_t size()
        {
            std::lock_guard<std::mutex> lock( mu_queue );
            return collection.size();
        }

        inline void push( const T& aItem )
        {
            std::lock_guard<std::mutex> lock( mu_queue );
            collection.push( aItem );
            cond_var.notify_one();
        }

        inline T& pop()
        {
            std::lock_guard<std::mutex> lock( mu_queue );
            while( collection.empty() )
            {
                cond_var.wait( mu_queue );
            }
            T temp = collection.front();
            collection.pop();

            return temp;
        }

};
#endif
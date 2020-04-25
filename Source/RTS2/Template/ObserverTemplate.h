#pragma once
#include <vector>

template <typename T> 
class Observer
{
public:
    virtual ~Observer() = default;
    virtual void OnFieldChanged(T& Source) = 0;
};

template <typename T>
class Observable
{

    std::vector<Observer<T>*> observers;
    
public:
    void Subscribe(Observer<T>& obs)
    {
        observers.push_back(&obs);
    }

    void Unsubscribe(Observer<T>& obs)
    {
        for(int i = 0; i < observers.size(); i++)
        {
            if(observers[i] == &obs)
            {
                observers.erase(observers.begin() + i);
            }
        }
    }

    void Notify(T& Source)
    {
        for(int i = 0; i < observers.size(); i++)
        {
            if(observers[i] != nullptr)
            {
                observers[i]->OnFieldChanged(Source);
            }
        }
    }
};
#pragma once

#include "CoreMinimal.h"
#include "RTS2/Template/delegates.h"

class RTSPopulationData
{
public:
    
    delegate<int, int> OnChanged;

    void PopulationChanged()
    {
        OnChanged(Population, Limit);
    }
    
    void SetPopulation(int Amount)
    {
        Population = Amount;
        PopulationChanged();
    }

    void SetLimit(int Amount)
    {
        Limit = Amount;
        PopulationChanged();
    }

    int GetLimit()
    {
        return Limit;
    }
    
    int GetPopulation()
    {
        return Population;
    }

    void AddLimit(int Amount)
    {
        Limit+=Amount;
        PopulationChanged();
    }
    
    void operator+(int const & amount)
    {
        Population += amount;
        PopulationChanged();
    }

     void operator-(int const & amount)
    {
        Population -= amount;
        PopulationChanged();
    }
    
    private:

    int Limit;
    int Population;


    
};

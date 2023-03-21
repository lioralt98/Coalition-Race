#include "SelectionPolicy.h"
#include "Graph.h"

int MandatesSelectionPolicy::select(const Graph &graph, vector<int> releventNeighbors, int selfPartyId) const
//find max function - regarding the mandates of each party, returning selected party id
// releventNeighbors - vector of relevent parties ids
{
    int max = -1;
    int selectedPartyId = -1;
    for (unsigned int i = 0; i < releventNeighbors.size(); i++)
    {
        int mandates = graph.getMandates(releventNeighbors[i]);
        if (mandates > max)
        {
            max = mandates;
            selectedPartyId = releventNeighbors[i];
        } 
    }

    return selectedPartyId;
}

MandatesSelectionPolicy *MandatesSelectionPolicy::clone() const
//returns a new pointer to this object, will be used in the copy ctor
{
    return new MandatesSelectionPolicy;
}

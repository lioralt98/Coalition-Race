#include "SelectionPolicy.h"
#include "Graph.h"

int EdgeWeightSelectionPolicy::select(const Graph &graph, vector<int> releventNeighbors, int selfPartyId) const
//find max function - regarding the edge weight, returning selected party id
{
    int max = -1;
    int selectedPartyId = -1;
    for (unsigned int i = 0; i < releventNeighbors.size(); i++)
    {
        int edgeWeight = graph.getEdgeWeight(selfPartyId, releventNeighbors[i]);
        if (edgeWeight > max)
        {
            max = edgeWeight;
            selectedPartyId = releventNeighbors[i];
        } 
    }

    return selectedPartyId;
}

EdgeWeightSelectionPolicy *EdgeWeightSelectionPolicy::clone() const
//returns a new pointer to this object, will be used in the copy ctor, to clone an agent.
{
    return new EdgeWeightSelectionPolicy;
}

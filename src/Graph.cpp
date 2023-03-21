#include "Graph.h"

Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges) {}

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}

int Graph::getNumVertices() const
{
    return mVertices.size();
}

const Party &Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}

Party &Graph::getParty(int partyId) //returns the object party of the party id not in const to be able to make changes
{
    return mVertices[partyId];
}

const vector<int> Graph::getNeighbors(int partyId) const
// Returns a vector of the party's neighbors.
{
    vector<int> neighbors;
    for (unsigned int i = 0; i < mEdges[partyId].size(); i++)
    {
        if (mEdges[partyId][i])
            neighbors.push_back(i);
    }
    return neighbors;
}
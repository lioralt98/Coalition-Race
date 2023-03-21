#pragma once

#include <vector>
#include <list>

#include "Graph.h"
#include "Agent.h"

using std::string;
using std::list;
using std::vector;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);
    
    void step();
    bool shouldTerminate() const;

    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    Agent &getAgent(int agentId); //
    const Party &getParty(int partyId) const;
    Party &getParty(int partyId); //
    const vector<vector<int>> getPartiesByCoalitions() const;
    void insertAgent(Agent &otherAgent, int myPartyId); //

private:
    Graph mGraph;
    vector<Agent> mAgents;
    list<Coalition> mCoalitions; //list of all the coalitions in the race
};

#include "Simulation.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), mCoalitions()
{
    for (unsigned int i = 0; i < mAgents.size(); i++) 
    //for each agent, create a coalition and add the new coalition to the coalition list
    {
        vector<int> initializedParty;
        //add the party that the current agent represents to the initializedParty vector
        initializedParty.push_back(mAgents[i].getPartyId()); 
        //create a coalition and add it to the coalitions list
        mCoalitions.push_back(Coalition(initializedParty, vector<int>(), mGraph.getParty(mAgents[i].getPartyId()).getMandates()));
    }
    int i = 0;
    //for each agent set it's coalition 
    for (auto &it : mCoalitions) 
    {
        mAgents[i].setCoalition(it);
        i++;
    }
}  

void Simulation::step()
{
    //for each party that is in Joined state, run it's step function
    int numofParties = mGraph.getNumVertices();
    for (int i = 0 ; i < numofParties; i++)
    {
        Party &currParty = mGraph.getParty(i);
        if (currParty.getState() != Joined) currParty.step(*this);
    }
    //for each agent, run it's step function
    for(unsigned int j = 0; j < mAgents.size(); j ++)
        mAgents[j].step(*this); 
}

bool Simulation::shouldTerminate() const
{   
    //check if there's a coalition that got at least 61 mandates or 
    //every party joined a coalition
    int numOfParties = mGraph.getNumVertices();
    for (auto &it: mCoalitions)
    {
        if (it.getMandates() > 60)
            return true;
    }
    for (int j = 0; j < numOfParties; j++) 
    {
        if(mGraph.getParty(j).getState() != Joined) 
            return false;
    }
    return true;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

Agent &Simulation::getAgent(int agentId)
//get non const agent
{
    return mAgents[agentId];
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

Party &Simulation::getParty(int partyId) 
//get non const party
{
    return mGraph.getParty(partyId);
}

void Simulation::insertAgent(Agent &otherAgent, int myPartyId)
//clone otherAgent with myPartyId and insert it to mAgents
{
    int size = mAgents.size();
    Agent myAgent(otherAgent);
    myAgent.setId(size);
    myAgent.setPartyId(myPartyId);
    mAgents.push_back(myAgent);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
//for each coalition from coalition list, get it's parties vector and insert it to
//corresponding index in allPartiesPerCoalition
{
    vector<vector<int>> allPartiesPerCoalitions;
    for (auto &it : mCoalitions)
        allPartiesPerCoalitions.push_back(it.getParties());
    return allPartiesPerCoalitions;   
}
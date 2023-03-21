#include "Simulation.h"
#include "SelectionPolicy.h"
#include <iostream>

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mNeighborsInitialized(false), mReleventNeighbors(), mSelectionPolicy(selectionPolicy), mCoalition(nullptr) {}

Agent::~Agent()
{
    if (mSelectionPolicy) delete mSelectionPolicy;
    mCoalition = nullptr;
}

Agent::Agent(const Agent &other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mNeighborsInitialized(false), mReleventNeighbors(), mSelectionPolicy(nullptr), mCoalition(other.mCoalition)
{
    mSelectionPolicy = other.mSelectionPolicy->clone();
}

Agent::Agent(Agent &&other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mNeighborsInitialized(false), mReleventNeighbors(), mSelectionPolicy(other.mSelectionPolicy), mCoalition(other.mCoalition)
{
    other.mSelectionPolicy = nullptr;
}

Agent &Agent::operator=(const Agent &other)
{
    if (this != &other)
    {
        if (mSelectionPolicy) delete mSelectionPolicy;
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        mNeighborsInitialized = other.mNeighborsInitialized;
        mReleventNeighbors = other.mReleventNeighbors;
        mSelectionPolicy = other.mSelectionPolicy->clone();
        mCoalition = other.mCoalition;
    }
    return *this;
}

Agent &Agent::operator=(Agent &&other)
{
    if (mSelectionPolicy) delete mSelectionPolicy;
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    mNeighborsInitialized = false;
    vector<int> mReleventNeighbors;
    mSelectionPolicy = other.mSelectionPolicy;
    other.mSelectionPolicy = nullptr;
    return *this;
}

int Agent::getId() const
{
    return mAgentId;
}

void Agent::setId(int agentId) //set the agent's id
{
    mAgentId = agentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::setPartyId(int partyId) //set the agent's party id
{
    mPartyId = partyId;
}

void Agent::setCoalition(Coalition &c) //set the agent's coalition
{
    mCoalition = &c;
}

Coalition *Agent::getCoalition() const //return the agent's coalition
{
    return mCoalition;
}

void Agent::step(Simulation &sim)
{
    const Graph &graph = sim.getGraph();
    // If mReleventNeighbors is not initializted yet, mNeighborsInitialized is false 
    if (!mNeighborsInitialized)
    {
        // Initialize mReleventNeighbors to hold all the neighbors of this agent's party.
        mReleventNeighbors = graph.getNeighbors(mPartyId);
        // mNeighborsInitialzed set to true, to not initialize again.
        mNeighborsInitialized = true;
    }

    // Iterating through the relevent neighbors to get rid of the parties which their
    // state is set to Joined or their party already got an offer from an agent from this agent's coalition.
    for (vector<int>::iterator it = mReleventNeighbors.begin(); it != mReleventNeighbors.end();)
    {
        if (graph.getParty(*it).getState() == Joined || mCoalition->isOffered(*it))
            it = mReleventNeighbors.erase(it);
        else
            it++;
    }

    // If there are parties that qualify the conditions above, send them to select method to return
    // get the desired party by the agent's selection policy.
    if (mReleventNeighbors.size() > 0)
    {
        int selectedPartyId = mSelectionPolicy->select(graph, mReleventNeighbors, mPartyId);
        Party &selectedParty = sim.getParty(selectedPartyId);
        // Add this agent's id to the selected party's offer list.
        selectedParty.addToMyOffers(mAgentId);
        // Add selected party's id to offers made by the agent's coalition.
        mCoalition->addOfferMade(selectedPartyId);
        // Change party's state to C.O if the offer was the party's first offer.
        // Inorder for the timer of the party to start.
        if (selectedParty.getState() == Waiting)
            selectedParty.setState(CollectingOffers);
    }
}
#pragma once

#include "Coalition.h"
#include "Graph.h"

class SelectionPolicy;
class Simulation;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy); //Ctor
    /*
    * ========= RULE OF FIVE =========
    */
    virtual ~Agent();
    Agent(const Agent &other);
    Agent(Agent &&other);
    Agent &operator=(const Agent &other);
    Agent &operator=(Agent &&other);
    /*
    * ========= RULE OF FIVE =========
    */
    int getPartyId() const;
    void setPartyId(int partyId); //
    int getId() const;
    void setId(int agentId); //
    void setCoalition(Coalition &c); //
    Coalition *getCoalition() const; //
    void step(Simulation &);

private:
    int mAgentId;
    int mPartyId;
    bool mNeighborsInitialized; //
    vector<int> mReleventNeighbors; //
    SelectionPolicy *mSelectionPolicy;
    Coalition *mCoalition; //
};

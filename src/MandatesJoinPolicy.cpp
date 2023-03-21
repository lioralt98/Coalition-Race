#include "JoinPolicy.h"
#include "Simulation.h"
#include "Coalition.h"
#include <vector>

using std::vector;

Agent &MandatesJoinPolicy::join(vector<int> offers, Simulation &s) 
//find max function - regarding the mandates of coalition that is represented by its agent 
//in the "offers" vector, returning selected agent
{
    int max = -1; //representing the max mandates
    int maxAgentId = -1;
    for (unsigned int i = 0 ; i < offers.size(); i++)
    {
        Agent &currAgent = s.getAgent(offers[i]); //get the object agent by agent's id
        int currMandates = currAgent.getCoalition()->getMandates(); //get the mandates of the agent's coalition
        if (currMandates > max)
        {
            max = currMandates;
            maxAgentId = currAgent.getId();
        }
    }
        return s.getAgent(maxAgentId);
}

MandatesJoinPolicy *MandatesJoinPolicy::clone() const
//returns a new pointer to this object, will be used in the copy ctor
{
    return new MandatesJoinPolicy;
}




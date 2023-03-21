#include "JoinPolicy.h"
#include "Simulation.h"
#include <vector>

using std::vector;

Agent &LastOfferJoinPolicy::join(vector<int> offers, Simulation &s)
//returns the last offer made (last element that entered to the party's offers vector)
{
    return s.getAgent(offers.back());
}

LastOfferJoinPolicy *LastOfferJoinPolicy::clone() const
//returns a new pointer to this object, will be used in the copy ctor
{
    return new LastOfferJoinPolicy;
}
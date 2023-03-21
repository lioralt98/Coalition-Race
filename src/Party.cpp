#include "Party.h"
#include "JoinPolicy.h"
#include "Coalition.h"
#include "Simulation.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), mOfferList(), mTimer(0) {}

Party::~Party()
{
    if (mJoinPolicy)
        delete mJoinPolicy;
}

Party::Party(const Party &other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(nullptr), mState(other.mState), mOfferList(other.mOfferList), mTimer(other.mTimer)
{   
    mJoinPolicy = other.mJoinPolicy->clone();  
}

Party &Party::operator=(const Party &other) 
{
    if (this != &other)
    {
        if(mJoinPolicy) delete mJoinPolicy;
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        mJoinPolicy = other.mJoinPolicy->clone();
        mOfferList = other.mOfferList;
        mState = other.mState;
    }
    return *this;
}

Party::Party(Party&& other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState), mOfferList(other.mOfferList), mTimer(other.mTimer)
{
    other.mJoinPolicy = nullptr;
}

Party &Party::operator=(Party &&other)   
{
    if (mJoinPolicy) delete mJoinPolicy;
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    mJoinPolicy = other.mJoinPolicy;
    mOfferList = other.mOfferList;
    mState = other.mState;
    other.mJoinPolicy = nullptr;
    return *this;
}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

void Party::addToMyOffers(int agentId)
//add a new offer to this party's offers vector
//each offer is represented by an agent's id
{
    mOfferList.push_back(agentId);
}

void Party::step(Simulation &s) //
{  
    if (mState == CollectingOffers) //increment mTimer each iteration that the party's state is C.O
        mTimer++;
    if (mTimer == 3) //join a coalition when the timer hits 3 
    {
        if (mOfferList.size() > 0)
        {
            //sending this party's received offer list to the relevant 
            //join function by the join policy
            Agent &selectedAgent = mJoinPolicy->join(mOfferList, s); 
            selectedAgent.getCoalition()->addParty(mId); //adding this party id to the coalition's party list by the agent that this party just joined 
            //adding this party's mandates to the coalition's total mandates by the agent
            //that this party just joined
            selectedAgent.getCoalition()->addMandates(mMandates);
            mState = Joined; //changing the state to joined after joining a coalition
            //sending the selected agent that the party just joined to, to be cloned and added
            //to mAgents field in "Simulation.cpp"
            s.insertAgent(selectedAgent, mId);
        }
    }
}

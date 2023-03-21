#pragma once

#include <vector>
#include <string>

using std::string;
using std::vector;

class JoinPolicy;
class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
    public:
        Party(int id, string name, int mandates, JoinPolicy *); //Ctor
        /*
        * ========= RULE OF FIVE =========
        */
        ~Party();
        Party(const Party &other);
        Party &operator=(const Party &other);
        Party(Party&& other);
        Party &operator=(Party&& other);
        /*
        * ========= RULE OF FIVE =========
        */
        State getState() const;
        void setState(State state);
        int getMandates() const;
        void step(Simulation &s);
        const string &getName() const;
        void addToMyOffers(int agentId); //

    private:
        int mId;
        string mName;
        int mMandates;
        JoinPolicy *mJoinPolicy;
        State mState;
        vector<int> mOfferList; //vector of agent ids that sent an offer to this party
        int mTimer; //
};

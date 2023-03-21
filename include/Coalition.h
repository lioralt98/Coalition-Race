#pragma once

#include <vector>

using std::vector;

class Coalition 
{ 
public:
    Coalition(vector<int> myParties, vector<int> OffersMade, int tlMandates);
    void addMandates(int mandates);
    int getMandates() const;
    void addOfferMade(int partyId);
    void addParty (int partyId);
    bool isOffered(int partyId) const;
    vector<int> getParties() const;

private:
    vector<int> mMyParties;
    vector<int> mOffersMade; //vector of party ids that got an offer from this coalition
    int mtlMandates;
};

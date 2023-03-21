#include "Coalition.h"

Coalition::Coalition(vector<int> myParties, vector<int> OffersMade, int tlMandates) : mMyParties(myParties), mOffersMade(OffersMade), mtlMandates(tlMandates) {}

void Coalition::addMandates(int mandates) 
//increase the total mandates field by adding each party mandates that are in the coalition
{
    mtlMandates += mandates;
}

int Coalition::getMandates() const //get total mandates
{
    return mtlMandates;
}

void Coalition::addOfferMade(int partyId) //add the party to the field of party ids that received an offer from this coalition
{
    mOffersMade.push_back(partyId);
}

void Coalition::addParty(int partyId) //add a party to the parties of the coalition
{
    mMyParties.push_back(partyId);
}

bool Coalition::isOffered(int partyId) const //checking if a party has already received an offer from this coalition
{
    for (unsigned int i = 0; i < mOffersMade.size(); i++)
    {
        if (partyId == mOffersMade[i])
            return true;
    }
    return false;
}
vector<int> Coalition::getParties() const //return this coalition's parties
{
    return mMyParties;
}
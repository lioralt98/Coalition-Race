#pragma once

#include <vector>

using std::vector;

class Agent;
class Simulation;

class JoinPolicy {
   public:
      virtual Agent &join(vector<int> offers, Simulation &s) = 0;
      virtual ~JoinPolicy() {}
      virtual JoinPolicy *clone() const = 0;
};

class MandatesJoinPolicy : public JoinPolicy {
   public:
      virtual Agent &join(vector<int> offers, Simulation &s) override;
      virtual MandatesJoinPolicy *clone() const override;
};

class LastOfferJoinPolicy : public JoinPolicy {
   public:
      virtual Agent &join(vector<int> offers, Simulation &s) override;
      virtual LastOfferJoinPolicy *clone() const override;
};
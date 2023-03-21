#pragma once

#include <vector>

using std::vector;

class Graph;

class SelectionPolicy
{
    public:
        virtual ~SelectionPolicy() {}
        virtual int select(const Graph &graph, vector<int> releventNeighbors, int selfPartyId) const = 0;
        virtual SelectionPolicy *clone() const = 0;
};

class MandatesSelectionPolicy: public SelectionPolicy
{
    public:
        virtual int select(const Graph &graph, vector<int> releventNeighbors, int selfPartyId) const override;
        virtual MandatesSelectionPolicy *clone() const override;
};

class EdgeWeightSelectionPolicy: public SelectionPolicy
{
    public:
        virtual int select(const Graph &graph, vector<int> releventNeighbors, int selfPartyId) const override;
        virtual EdgeWeightSelectionPolicy *clone() const override;
};
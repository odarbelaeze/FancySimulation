#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "Particle.hpp"
#include <fstream>
#include <vector>

using namespace std;

struct Interaction
{
    Particle* ref;
    double J_ex;
    double d;
    Vec r;
};

struct MacroState
{
    Vec magnetization;
    double energy;
};


class System
{
private:
    Particle* particles;
    Interaction** interactions;
    Vec* anisotropy;

    int  n;
    int* nInteractions;

    double energy(Vec H);
    double energy(int i, Vec H);
    double energyDelta(int i, Vec H);
    Vec magnetization();

public:
    System();
    System(ifstream& file);
    ~System();

    vector<double> estabilizeAt(Vec H, double k_BT, int mcs);
    vector<MacroState> measureAt(Vec H, double k_BT, int mcs);
};

#endif
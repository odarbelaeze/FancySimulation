#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "Particle.hpp"
#include <fstream>
#include <veector>

using namespace std;


struct Interaction
{
    int ref;
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
    vector<Particle> particles;
    vector<vector<Interaction> > interactions;
    vector<Vec> anisotropy;

    double energy();
    double energy(int i);
    Vec magnetization();

public:
    System();
    System(ifstream& file);
    ~System();

    void estabilizeAt(Vec B, double T, int mcs);
    void measureAt(Vec B, double T, int mcs);
};

#endif
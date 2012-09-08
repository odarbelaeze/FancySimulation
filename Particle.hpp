#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

#include <valarray>
#include <string>

using namespace std;


typedef valarray<double> Vec;

class Particle
{
private:
	string id;
    Vec pos;
    Vec s;
    Vec st;

    double spinNorm();
    Vec randSpin(double norm, double r);
    Vec cheapRandSpin(double norm);

public:
    Particle();
    Particle(string id, float norm_s);
    Particle(Vec pos);
    Particle(string id, Vec pos);
    Particle(Vec pos, Vec s);
    Particle(string id, Vec pos, Vec s);

    ~Particle();

    void changeSpinTo(Vec new_s);
    void changeSpin(double r);
    void cheapChangeSpin();
    void commitSpin();

    void moveTo(Vec new_pos);
    void move(Vec delta_pos);

    void setId(string id);

    Vec getPos();
    Vec getSpin();
    Vec getTemporalSpin();
    string getId();
};

#endif
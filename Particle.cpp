#include "Particle.hpp"

#include <cstdlib>
#include <cmath>
#include <exception>

/*
    Creates a null instance of Particle.
*/

Particle::Particle() {

}


/*
    Copy constructor.
*/

Particle::Particle(Particle const& other){
    this->id = other.id;
    this->pos = other.pos;
    this->s = other.s;
    this->st = other.st;
}

/*
    Creates a Particle instance with a given pos
*/

Particle::Particle(Vec pos){
    if (pos.size() != 3) throw exception();
    this->pos = pos;
}

/* 
    Creates a Particle instance with a given id and a given position
*/

Particle::Particle(string id, Vec pos){
    if (pos.size() != 3) throw exception();
    this->id = id;
    this->pos = pos;

}

/*
    Creates a Particle instance with a given position and a given spin
*/

Particle::Particle(Vec pos, Vec s){
    if (pos.size() != 3) throw exception();
    if (s.size() != 3) throw exception();
    this->pos = pos;
    this->s = s;


}

/*
    Creates a Particle instance with a given id,  given position and given spin
*/

Particle::Particle(string id, Vec pos, Vec s){
    if (pos.size() != 3) throw exception();
    if (s.size() != 3) throw exception();
    this->id = id;
    this->pos = pos;
    this->s = s;

}


Particle::~Particle(){

}

/*
    Returns the norm of the Particle's spin.
*/


double Particle::spinNorm(){
    return sqrt(pow(this->s, 2.0).sum());
}

/*
    Returns a vector derived from the spin vector with
    norm norm by adding a random vector of norm r.
*/

Vec Particle::randSpin(double norm, double r){
    if (norm < 0) throw exception();
    if (r < 0) throw exception();

    Vec r_xyz(0.0, 3);
    double theta = (double) rand() * 1.0 * M_PI / RAND_MAX;
    double phi   = (double) rand() * 2.0 * M_PI / RAND_MAX;

    r_xyz[0] = r * sin(theta) * cos(phi);
    r_xyz[1] = r * sin(theta) * sin(phi);
    r_xyz[2] = r * cos(theta);

    r_xyz = s + r_xyz;
    r_xyz = norm * (r_xyz / pow(r_xyz, 2.0).sum());

    return r_xyz;
}

/*
    Returns a vector derived from the spin vector with
    norm by adding a random vector of norm 1.0.
*/

Vec Particle::cheapRandSpin(double norm){
    if (norm < 0) throw exception();

    Vec r_xyz(0.0, 3);
    double theta = (double) rand() * 1.0 * M_PI / RAND_MAX;
    double phi   = (double) rand() * 2.0 * M_PI / RAND_MAX;

    r_xyz[0] = 1.0 * sin(theta) * cos(phi);
    r_xyz[1] = 1.0 * sin(theta) * sin(phi);
    r_xyz[2] = 1.0 * cos(theta);

    r_xyz = s + r_xyz;
    r_xyz = norm * (r_xyz / pow(r_xyz, 2.0).sum());

    return r_xyz;
}

/*
    Changes the temporal spin to a given new spin new_s.
*/


void Particle::changeSpinTo(Vec new_s){
    if (new_s.size() != 3) throw exception();
    this->st = new_s; 
}

/*
    Changes the temporal spin st of the particle to a new one
    using the private method randSpin(double, double) with 
    norm spinNorm() and r = r.
*/

void Particle::changeSpin(double r){
    if (r < 0) throw exception();
    this->st = randSpin(spinNorm(), r);
}

/*
    Changes the temporal spin st of the particle to a new one
    using the private method randSpin(double) with 
    norm spinNorm().
*/

void Particle::cheapChangeSpin(){
    this->st = cheapRandSpin(spinNorm());
}

/*
    Changes the actual spin s to the temporal one s;
*/

void Particle::commitSpin(){
    this->s = this->st;
}

/*
    Change the position to a new_pos
*/

void Particle::moveTo(Vec new_pos){
    if (new_pos.size() != 3) throw exception();
    this->pos = new_pos;

}

/*
    Change the position to a delta_pos
*/

void Particle::move(Vec delta_pos){
    if (delta_pos.size() != 3) throw exception();
    this->pos = this->pos + delta_pos;

}

/*
    Sets the id
*/

void Particle::setId(string id){
    this->id = id;

}


/*
    Returns the position of the particle
*/

Vec Particle::getPos(){
    return this->pos;
}

/*
    Returns the spin of the particle
*/

Vec Particle::getSpin(){
    return this->s;

}

/*
    Returns the TemporalSpin of the particle
*/

Vec Particle::getTemporalSpin(){
    return this->st;
}

/*
    Returns the id
*/

string Particle::getId(){
    return this->id;

}

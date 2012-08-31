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
    Creates a Particle instance with a given pos
*/

Particle::Particle(Vec pos){
    if (pos.size() != 3) throw exception();
    this.pos = pos;
}

/* 
    Creates a Particle instance with a given id and a given position
*/

Particle::Particle(string id, Vec pos){
    if (pos.size() != 3) throw exception();
    this.id = id;
    this.pos = pos;

}

/*
    Creates a Particle instance with a given position and a given spin
*/

Particle::Particle(Vec pos, Vec s){
    if (pos.size() != 3) throw exception();
    if (s.size() != 3) throw exception();
    this.pos = pos;
    this.s = s;


}

/*
    Creates a Particle instance with a given id,  given position and given spin
*/

Particle::Particle(string id, Vec pos, Vec s){
    if (pos.size() != 3) throw exception();
    if (s.size() != 3) throw exception();
    this.id = id;
    this.pos = pos;
    this.s = s;

}


Particle::~Particle(){

}

/*
    Returns the norm of the Particle's spin.
*/


double Particle::spinNorm(){
    return sqrt(pow(s, 2).sum());
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

    // TODO: Modify

}

/*
    Changes the existing spin to a given new spin new_s.
*/


void Particle::changeSpinTo(Vec new_s){
    if (new_s.size() != 3) throw exception();
    this.s = new_s; 
}

/*
    Changes the temporal spin st of the particle to a new one
    using the private method randSpin(double, double) with 
    norm spinNorm() and r = r.
*/

void Particle::changeSpin(double r){
    if (r < 0) throw exception();
    this.st = randSpin(spinNorm(), r);
    // TODO: review with exeptions

}

/*
    Changes the temporal spin st of the particle to a new one
    using the private method randSpin(double) with 
    norm spinNorm().
*/

void Particle::cheapChangeSpin(){


}

/*
    Changes the actual spin s to the temporal one s;
*/

void Particle::commitSpin(){
    this.s = this.st;
}

// TODO: change comments and actualize code from here!

/*
    Change the position to a new_pos
*/

void Particle::moveTo(Vec new_pos){
    if (new_pos.size() != 3) throw exception;
    this.new_pos = new_pos;

}

/*
    Change the position to a delta_pos
*/

// Aca no sería moveTo(Vec delta_pos)  ?

void Particle::move(Vec delta_pos){
    if (delta_pos.size() != 3) throw exception;
    this.delta_pos = delta_pos;

}

/*
    Set the id
*/

void Particle::setId(string id){
    this.id = id;

}


/*
    get the position of the particle
*/

Vec Particle::getPos(){
    return this.pos;
}

/*
    Get the spin of the particle
*/

Vec Particle::getSpin(){
    return this.s;

}

/*
    Get the TemporalSpin of the particle
*/

Vec Particle::getTemporalSpin(){
    return this.st;
}

/*
    Get the id
*/

string Particle::getId(){
    return this.id;

}

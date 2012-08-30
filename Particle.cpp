#include "Particle.hpp"

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


double Particle::spinNorm(){

}

/*
    Creates a Particle instance with a given norm and a given r
*/

Vec Particle::randSpin(double norm, double r){
    if (norm < 0) throw exception();
    if (r < 0) throw exception();
    this.norm = norm;
    this.r = r;

}

/*
    Creates a Particle instance with a given norm
*/

Vec Particle::cheapRandSpin(double norm){
    if (norm < 0) throw exception();
    this.norm = norm;

}

/*
    Creates a Particle instance with a given spin new_s
*/


void Particle::changeSpinTo(Vec new_s){
    if (new_s.size() != 3) throw exception;
    this.new_s = new_s;

}

/*
    Creates a Particle instance with a given r
*/

void Particle::changeSpin(double r){
    if (r < 0) throw exception;
    this.r = r;


}

void Particle::cheapChangeSpin(){

}

void Particle::commitSpin(){

}

/*
    Creates a Particle instance with a given position new_pos
*/

void Particle::moveTo(Vec new_pos){
    if (new_pos.size() != 3) throw exception;
    this.new_pos = new_pos;

}

void Particle::move(Vec delta_pos){
    if (delta_pos.size() != 3) throw exception;
    this.delta_pos = delta_pos;

}


void Particle::setId(string id){
    this.id = id;

}


Vec Particle::getPos(){

}

Vec Particle::getSpin(){

}

Vec Particle::getTemporalSpin(){

}

string Particle::getId(){

}

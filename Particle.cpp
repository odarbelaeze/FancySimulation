#include "Particle.hpp"

/*
    Creates a null instance of Particle.
*/

Particle::Particle() {

}

Particle::Particle(Vec pos){

}

Particle::Particle(string id, Vec pos){

}

Particle::Particle(Vec pos, Vec s){

}

Particle::Particle(string id, Vec pos, Vec s){

}


Particle::~Particle(){

}


double Particle::spinNorm(){

}

Vec Particle::randSpin(double norm, double r){

}

Vec Particle::cheapRandSpin(double norm){

}


void Particle::changeSpinTo(Vec new_s){

}

void Particle::changeSpin(double r){

}

void Particle::cheapChangeSpin(){

}

void Particle::commitSpin(){

}


void Particle::moveTo(Vec new_pos){

}

void Particle::move(Vec delta_pos){

}


void Particle::setId(string id){

}


Vec Particle::getPos(){

}

Vec Particle::getSpin(){

}

Vec Particle::getTemporalSpin(){

}

string Particle::getId(){

}

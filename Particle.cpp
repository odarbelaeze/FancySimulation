#include "Particle.hpp"

#include <cassert>

/*
    Creates a null instance of Particle.
*/

Particle::Particle() {

}

/*
	Creates a Particle instance with a given pos
*/

Particle::Particle(Vec pos){
	assert(pos.size() == 3);
	this.pos = pos;
}

/* 
	Creates a Particle instance with a type and a given position
*/

Particle::Particle(string id, Vec pos){
	assert(pos.size() == 3);
	this.id = id;
	this.pos = pos;

}

/*
	Creates a Particle instance with a given position and a given spin
*/

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

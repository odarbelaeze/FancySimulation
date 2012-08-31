#include "System.hpp"
#include "Particle.hpp"

#include <exception>

using namespace std;

/*
    Creates a null instance of System.
*/

System::System(){

}

/*
    Creates a whole System instance from a JSON file.
*/

System::System(ifstream& file){

}

/*
    The method that is called when a System instance gets deleted.
*/

System::~System(){

}

/*
    Returns the actual energy of the system using the Hamiltonian.
*/

double System::energy(){

}

/*
    Returns the contribution of the ith particle to the total energi
    asumming that E_tot = sum E_i for all i.
*/

double System::energy(int i){

}

/*
    Return the total Systems magnetization given by the vector sum of every
    Particle's spin.
*/

Vec System::magnetization(){

}

/*
    Estabilizes the system at a given magnetic field intensity H in meV
    and a given thermal energy k_BT in meV using mcs Monte Carlo steeps.
*/

void System::estabilizeAt(Vec H, double T, int mcs){

}

/*
    Measures the system's observables at a given magnetic field intensity H 
    in meV and a given thermal energy k_BT in meV and returns a 
    vector<MacroState> through for all the mcs Monte Carlo steeps.
*/

vector<MacroState> System::measureAt(Vec H, double T, int mcs){

}
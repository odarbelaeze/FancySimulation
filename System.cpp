#include "System.hpp"
#include "Particle.hpp"

#include <json/json.h>
#include <exception>
#include <cstdlib>
#include <ctime>
#include <cmath>

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
    Json::Value root;
    Json::Reader reader;
    bool parsing_success = reader.parse(file, root);
    if (!parsing_success) throw exception();
}

/*
    The method that is called when a System instance gets deleted.
*/

System::~System(){

}

/*
    Returns the actual energy of the system using the Hamiltonian.
*/

double System::energy(Vec H){
    
    if (H.size() != 3) throw exception();

    double e = 0;
    for (int i = 0; i < this->particles.size(); ++i)
    {
        e += energy(i, H);
    }
    return e;
}

/*
    Returns the contribution of the ith particle to the total energy
    asumming that E_tot = sum E_i for all i.
*/

double System::energy(int i, Vec H){

    if (H.size() != 3) throw exception();

    double e = 0.0;

    /*
        Energy due to interactions.
    */

    for (int j = 0; j < this->interactions.at(i).size(); ++j)
    {
        e -= interactions.at(i).at(j).J_ex * (
            this->particles.at(i).getSpin() * this->particles.at(j).getSpin()
        ).sum();
    }

    /*
        Energy due to magnetocrystaline anysotropy.
    */

    e -= (this->particles.at(i).getSpin() * this->anisotropy.at(i)).sum();

    /*
        Energy due to Zeeman effect.
    */

    e -= (this->particles.at(i).getSpin() * H).sum();

    return e;

}

/*
    Returns the energy delta between the energy of the particle with spin
    s and st.
*/

double System::energyDelta(int i, Vec H){

    if (H.size() != 3) throw exception();

    this->particles.at(i).cheapChangeSpin();

    double temporalEnergy = 0.0;

    /*
        Temporal energy due to interactions.
    */

    for (int j = 0; j < this->interactions.at(i).size(); ++j)
    {
        temporalEnergy -= interactions.at(i).at(j).J_ex * (
            this->particles.at(i).getTemporalSpin() * 
            this->particles.at(j).getSpin()
        ).sum();
    }

    /*
        Energy due to magnetocrystaline anysotropy.
    */

    temporalEnergy -= (this->particles.at(i).getTemporalSpin() * 
            this->anisotropy.at(i)).sum();

    /*
        Energy due to Zeeman effect.
    */

    temporalEnergy -= (this->particles.at(i).getTemporalSpin() * H).sum();

    return temporalEnergy - energy(i, H);

}

/*
    Return the total Systems magnetization given by the vector sum of every
    Particle's spin.
*/

Vec System::magnetization(){
    Vec mag(0.0, 3);

    for (int i = 0; i < this->particles.size(); ++i)
    {
        mag += this->particles.at(i).getSpin();
    }

    return mag;
}

/*
    Estabilizes the system at a given magnetic field intensity H in meV
    and a given thermal energy k_BT in meV using mcs Monte Carlo steeps.
*/

vector<double> System::estabilizeAt(Vec H, double k_BT, int mcs){
    
    vector<double> energies;
    double current_energy = energy(H);
    double energy_delta;                // For a simple speed up.

    srand((unsigned) time (NULL));      // Randomizing random generator.

    for (int k = 0; k < mcs; ++k)
    {
        for (int i = 0; i < this->particles.size(); ++i)
        {
            energy_delta = energyDelta(i, H);

            if (energy_delta < 0.0)
            {
                this->particles.at(i).commitSpin();
                current_energy += energy_delta;
            }
            else
            {
                double r = (double) rand() / RAND_MAX;
                if (r < exp( - energy_delta / k_BT))
                {
                    this->particles.at(i).commitSpin();
                    current_energy += energy_delta;
                }
            }
        }

        energies.push_back(current_energy);
    }

    return energies;
}

/*
    Measures the system's observables at a given magnetic field intensity H 
    in meV and a given thermal energy k_BT in meV and returns a 
    vector<MacroState> through for all the mcs Monte Carlo steeps.
*/

vector<MacroState> System::measureAt(Vec H, double k_BT, int mcs){
    
    MacroState m_state;
    vector<MacroState> m_states;

    m_state.energy = energy(H);
    double energy_delta;                // For a simple speed up.

    srand((unsigned) time (NULL));      // Randomizing random generator.

    for (int k = 0; k < mcs; ++k)
    {
        for (int i = 0; i < this->particles.size(); ++i)
        {
            energy_delta = energyDelta(i, H);

            if (energy_delta < 0.0)
            {
                this->particles.at(i).commitSpin();
                m_state.energy += energy_delta;
            }
            else
            {
                double r = (double) rand() / RAND_MAX;
                if (r < exp( - energy_delta / k_BT))
                {
                    this->particles.at(i).commitSpin();
                    m_state.energy += energy_delta;
                }
            }
        }

        m_state.magnetization = magnetization();
        m_states.push_back(m_state);
    }

    return m_states;
}
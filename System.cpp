#include "System.hpp"
#include "Particle.hpp"

#include <json/json.h>
#include <exception>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define DEBUG

using namespace std;

/*
    Use this carefully.
*/

Vec vson(Json::Value& v_json){
    Vec vec(0.0, v_json.size());
    for (int i = 0; i < v_json.size(); ++i)
    {
        vec[i] = v_json[i].asDouble();
    }
    return vec;
}

double rand_val() {
    return (double) rand() * 1.0 / RAND_MAX;
}

Vec rand_vec(){

    double theta = (double) rand() * 1.0 * M_PI / RAND_MAX;
    double phi   = (double) rand() * 2.0 * M_PI / RAND_MAX;

    double r_xyz[] = {
        sin(theta) * cos(phi),
        sin(theta) * sin(phi),
        cos(theta)
    };

    return Vec(r_xyz, 3);
}

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
    if (!parsing_success) {
        cout << "Parsing not success." << endl
             << reader.getFormattedErrorMessages() << endl;
        throw exception();
    }

    string system_descriptor = root.get(
        "system_descriptor", 
        "explicit particles"
    ).asString();

    string anisotropy_option = root.get(
        "anisotropy", "global"
    ).asString();

    string interaction_descriptor = root.get(
        "interaction_descriptor", "smp"
    ).asString();

    vector<double> smps;

    double cut_off = root.get(
        "rc", 1.0
    ).asDouble();

    if (system_descriptor == "explicit particles")
    {
        Json::Value j_parts = root["particles"];
        Particle p_template;
        if (!j_parts.isArray() || j_parts.empty()) throw exception();

        for (int i = 0; i < j_parts.size(); ++i)
        {
            p_template.setId(j_parts[i]["id"].asString());
            p_template.moveTo(vson(j_parts[i]["pos"]));
            if (j_parts[i]["s"].isDouble()) 
            {
                p_template.changeSpinTo(j_parts[i]["s"].asDouble() * rand_vec());
                p_template.commitSpin();
            }
            else if (j_parts[i]["s"].isArray())
            {
                p_template.changeSpinTo(vson(j_parts[i]["s"]));
                p_template.commitSpin();
            }
            else throw exception();

            if (anisotropy_option == "global") 
                this->anisotropy.push_back(vson(root["k"]));
            else if (anisotropy_option == "random")
            {
                if (j_parts[i].isMember("k"))
                    this->anisotropy.push_back(j_parts[i]["k"].asDouble() * rand_vec());
                else
                    this->anisotropy.push_back(root["k"].asDouble() * rand_vec());
            }
            else if (anisotropy_option == "explicit")
                this->anisotropy.push_back(vson(j_parts[i]["k"]));

            if (interaction_descriptor == "smp") 
                smps.push_back(j_parts[i]["smp"].asDouble());

            this->particles.push_back(p_template);

#ifdef DEBUG
            cout << this->particles.size() << endl;
#endif
        }


    }
    else if (system_descriptor == "multilayer") 
    {
        Json::Value layers = root["layers"];
        Particle p_template;
        if (!layers.isArray() || layers.size() == 0) throw exception();
        for (int layer = 0; layer < layers.size(); ++layer)
        {
            int w = layers[layer].get("w", 1).asInt();
            int h = layers[layer].get("h", 1).asInt();
            int l = layers[layer].get("l", 1).asInt();

            Json::Value basis = layers[layer]["basis"];

            if (!basis.isArray() || basis.size() == 0) throw exception();

            for (int i = 0; i < w; ++i)
            {
                for (int j = 0; j < h; ++j)
                {
                    for (int k = 0; k < l; ++k)
                    {
                        for (int p = 0; p < basis.size(); ++p)
                            {
                                double relpos[] = {i, j, k};
                                p_template.setId(basis[p]["id"].asString());
                                p_template.moveTo(vson(basis[p]["pos"]));
                                p_template.move(Vec(relpos, 3));
                                p_template.move(vson(layers[layer]["origin"]));
                                if (basis[p]["s"].isDouble()) 
                                {
                                    p_template.changeSpinTo(basis[p]["s"].asDouble() * rand_vec());
                                    p_template.commitSpin();
                                }
                                else if (basis[p]["s"].isArray())
                                {
                                    p_template.changeSpinTo(vson(basis[p]["s"]));
                                    p_template.commitSpin();
                                }
                                else throw exception();

                                if (anisotropy_option == "global") 
                                    this->anisotropy.push_back(vson(layers[layer]["k"]));
                                else if (anisotropy_option == "random")
                                {
                                    if (basis[p].isMember("k"))
                                        this->anisotropy.push_back(basis[p]["k"].asDouble() * rand_vec());
                                    else
                                        this->anisotropy.push_back(layers[layer]["k"].asDouble() * rand_vec());
                                }
                                else if (anisotropy_option == "explicit")
                                    this->anisotropy.push_back(vson(basis[p]["k"]));

                                if (interaction_descriptor == "smp") 
                                    smps.push_back(basis[p]["smp"].asDouble());

                                this->particles.push_back(p_template);

                    #ifdef DEBUG
                                cout << this->particles.size() << " at " 
                                     << p_template.getPos()[0] << " "
                                     << p_template.getPos()[1] << " "
                                     << p_template.getPos()[2] << " "
                                     << endl;
                    #endif
                            }
                    }
                }
            }

        }
    }
    else throw exception();

    this->interactions.resize(this->particles.size());

#ifdef DEBUG
    cout << this->interactions.size() << endl;
#endif

    for (int i = 0; i < this->particles.size(); ++i)
    {
        for (int j = i + 1; j < this->particles.size(); ++j)
        {
            Particle p = this->particles.at(i);
            Particle q = this->particles.at(j);
            Interaction inter;

            double d = sqrt(pow(p.getPos() - q.getPos(), 2.0).sum());

            if (d > cut_off) continue;

#ifdef DEBUG
            cout << "Adding asociation: (" << i << ", " << j << ")" << endl;
#endif

            inter.ref = j;
            inter.d = d;

            if (interaction_descriptor == "smp") 
                inter.J_ex = smps[i] + smps[j];
            else if (interaction_descriptor == "constant")
                inter.J_ex = root["J_ex"].asDouble();
            else if (interaction_descriptor == "cases")
                inter.J_ex = root["J_ex"][p.getId() + q.getId()].asDouble();
            else if (interaction_descriptor == "random")
                inter.J_ex = root["J_ex"].asDouble() * rand_val();
            else throw exception();

            this->interactions[i].push_back(inter);
            inter.ref = i;
            this->interactions[j].push_back(inter);
        }
    }

    
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
        Energy due to magnetocrystaline anisotropy.
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
        Energy due to magnetocrystaline anisotropy.
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
#include <iostream>
#include <fstream>
#include <string>
#include "Particle.hpp"
#include "System.hpp"
using namespace std;

int main(int argc, char *argv[])
{
	ifstream f_json("docs/example.json");
	System s_magnetic(f_json);

	Vec B(0.0, 3);
	double t = 0.0;

	cout << endl;
	for (int i = 0; i < 100; i++){
		/*vector<double> energies = */s_magnetic.measureAt(B, t, 10000);
		cout << "\n" << i + 1 << " de 100 Completados.";
	}
	// for (int i = 0; i < energies.size(); i++)
	// 	cout << energies[i] << endl;

    return 0;
}
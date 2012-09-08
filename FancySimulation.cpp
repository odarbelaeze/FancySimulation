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
		vector<MacroState> ms = s_magnetic.measureAt(B, t, 500);
		cout << i + 1 << " de 100 Completados." << endl;
	}
    cout << endl;

    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include "Particle.hpp"
#include "System.hpp"
using namespace std;

double mean(const vector<double>& sample);
MacroState mean(const vector<MacroState>& sample);

int main(int argc, char *argv[])
{
	ifstream f_json("docs/example.json");
	System s_magnetic(f_json);

	Vec h(0.0, 3);
	h[2] = 100.0; 
	double Et = 1000.0;

	vector<MacroState> sample;
	MacroState stats;

	s_magnetic.estabilizeAt(h, Et, 10000);

	while (Et > 0.0){
		sample = s_magnetic.measureAt(h, Et, 1000);
		stats = mean(sample);
		cout << Et << "    " << stats.magnetization[2] << "    " << stats.energy << endl;
		Et -= 10;
	}

    return 0;
}

double mean(const vector<double>& sample){
	double sum = 0;
	int m = sample.size();
	for (int i = 0; i < m; ++i)
	{
		sum += sample[i];
	}
	return sum / m;
}

MacroState mean(const vector<MacroState>& sample) {
	MacroState mean;
	int m = sample.size();
	mean.magnetization = Vec(0.0, 3);
	mean.energy = 0.0;

	for (int i = 0; i < m; ++i)
	{
		mean.magnetization += sample[i].magnetization;
		mean.energy += sample[i].energy;
	}

	mean.magnetization /= m;
	mean.energy /= m;

	return mean;
}
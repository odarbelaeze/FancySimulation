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
    return 0;
}
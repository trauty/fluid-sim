#define SDL_MAIN_HANDLED

#include "fluid-sim.h"

int main()
{
	FluidSim sim;

	if(!sim.init()) 
	{
		return -1;
	}

	sim.execute();

	return 0;
}
///////////////////////////////////////////////////////////////////////////////
//
//	main.cpp
//
///////////////////////////////////////////////////////////////////////////////
#include <systemc.h>
#include "Bubble.h"
#include "Reader.h"
#include "DataRAM.h"

#define RAMSIZE 0x400

// Global variables
bool m_bError = false;

///////////////////////////////////////////////////////////////////////////////
//
//	Main
//
///////////////////////////////////////////////////////////////////////////////
int sc_main(int arg_count, char **arg_value)
{
	// Variables
	int sim_units = 2; //SC_NS 

	// Instanciation des composants
	Bubble iBubble("Bubble");
	Reader iReader("Reader");
	DataRAM iDataRAM( "DataRAM", "memory/mem.hex", RAMSIZE, false );

	// Connexion des ports
	iReader.dataPortRAM(iDataRAM);
	iBubble.readPort(iReader);

	// Démarrage de l'application
	if (!m_bError)
	{
		cout << "Demarrage de la simulation." << endl;
		sc_start(20, SC_MS);
		cout << endl << "Simulation s'est terminee a " << sc_time_stamp() << endl;
	}
	// Fin du programme
	return 0;
}

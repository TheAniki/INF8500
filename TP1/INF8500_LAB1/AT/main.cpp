///////////////////////////////////////////////////////////////////////////////
//
//	main.cpp
//
///////////////////////////////////////////////////////////////////////////////
#include <systemc.h>
#include <Bubble.h>
#include <Reader.h>
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
	Reader instance_reader("Reader");
	DataRAM instance_dataRAM("DataRAM","chiffre.hex",RAMSIZE,false);
	Bubble instance_bubble("Bubble");

	// Déclaration des signaux
	sc_clock sClk( "SysClock", 4000, SC_NS, 0.5 );
	sc_signal<unsigned int> address;
	sc_signal<unsigned int> data;
	sc_signal<bool> request;
	sc_signal<bool> ack;
	
	// Connexion des ports
	// Reader
		instance_reader.clk(sClk);
		instance_reader.dataPortRAM(instance_dataRAM);
		instance_reader.address(address);
		instance_reader.request(request);
		instance_reader.ack(ack);
		instance_reader.data(data);
	
	// Bubble
		instance_bubble.clk(sClk);
		instance_bubble.data(data);
		instance_bubble.ack(ack);
		instance_bubble.address(address);
		instance_bubble.request(request);
	
	// Démarrage de l'application
	if (!m_bError)
	{
		cout << "Demarrage de la simulation." << endl;
		sc_start( -1, sc_core::sc_time_unit(sim_units) );
		cout << endl << "Simulation s'est terminee a " << sc_time_stamp() << " ns";
	}
	// Fin du programme
	return 0;
}

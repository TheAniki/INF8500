///////////////////////////////////////////////////////////////////////////////
//
//	Bubble.h
//
///////////////////////////////////////////////////////////////////////////////
#ifndef _BUBBLE_H_
#define _BUBBLE_H_

#include <systemc.h>
#include <stdio.h>
#include "InterfaceRead.h"


///////////////////////////////////////////////////////////////////////////////
//
//	Class Bubble
//
///////////////////////////////////////////////////////////////////////////////
class Bubble : public sc_module
{
	public:  
		// Ports    
		sc_in_clk clk; 					// Horloge.
		sc_out<unsigned int> address; 	// Adresse.
		sc_in<unsigned int> data; 		// Donnee.
		sc_out<bool> request; 			// Accuse de reception.
		sc_in<bool> ack; 				// Requete.
	
		// Constructor
		Bubble( sc_module_name zName );
		
		// Destructor
		~Bubble();
		
	private:
		// Process SystemC
		SC_HAS_PROCESS(Bubble);
		
		void interface(void);
		void bubbleSort(unsigned int *ptr, int counter);
};

#endif

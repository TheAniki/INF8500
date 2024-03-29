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
		
		void bubble(void);

		// Attributs
		enum BubbleState {Demande_Req,  
		Lecture_Data, 
		Bubble_Sort, 
		Affichage,
		Arret};

		BubbleState state = BubbleState::Demande_Req;
};

#endif

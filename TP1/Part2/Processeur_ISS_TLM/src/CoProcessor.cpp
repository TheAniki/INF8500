///////////////////////////////////////////////////////////////////////////////
//
//	CoProcessor.cpp
//
///////////////////////////////////////////////////////////////////////////////
#include "CoProcessor.h"
#include <iostream>
#include <vector>
using namespace std;


///////////////////////////////////////////////////////////////////////////////
//
//	Constructeur
//
///////////////////////////////////////////////////////////////////////////////
CoProcessor::CoProcessor( sc_module_name zName )
: sc_module(zName)
{
	SC_THREAD(thread);
	sensitive << ClockPort.pos();
		
	reg[0] = 0x0000;
	reg[1] = 0x0000;
	reg[2] = 0x0000;
	reg[3] = 0x0000;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Destructeur
//
///////////////////////////////////////////////////////////////////////////////
CoProcessor::~CoProcessor()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//	thread
//
///////////////////////////////////////////////////////////////////////////////
void CoProcessor::thread(void)
{
	// Variables locales
	/*
		À compléter
	*/


	// Boucle infinie
	while(1)
	{
		
	    // On attend une transaction 
		/*
			À compléter
		*/

		//Lecture adresse
		/*
			À compléter
		*/			
			
		// Write (du point de vue du processeur)
		/*
			À compléter. Selon l'adresse qui vient du processeur:
				- Lecture et stockage du nombre d'éléments à trier et 
				- lecture des éléments à trier
				- Tri (appel à bubbleSort)
				- Ne pas oublier d'utiliser les bons registres
		*/
			
		// Read (du point de vue du processeur)
		/*
			À compléter. Selon l'adresse qui vient du processeur:
				- Lecture du registre d'état du coprocesseur 
				- lecture du nombre d'éléments à envoyer au processeur
				- Lecture des élément triés
		*/

	}
}


///////////////////////////////////////////////////////////////////////////////
//
//	bubbleSort
//
///////////////////////////////////////////////////////////////////////////////
void CoProcessor::bubbleSort(unsigned int *ptr, int n_elements)
{
	/*

		À compléter. Ne pas oublier de modifier l'état du bon registre du coprocesseur à la fin du traitement (voir énoncé)

	*/
}
///////////////////////////////////////////////////////////////////////////////
//
//	Bubble.cpp
//
///////////////////////////////////////////////////////////////////////////////
#include "Bubble.h"


///////////////////////////////////////////////////////////////////////////////
//
//	Constructeur
//
///////////////////////////////////////////////////////////////////////////////
Bubble::Bubble( sc_module_name zName )
: sc_module(zName)
{
	SC_METHOD(bubble);
	sensitive<<clk.pos();
}


///////////////////////////////////////////////////////////////////////////////
//
//	Destructeur
//
///////////////////////////////////////////////////////////////////////////////
Bubble::~Bubble()
{
}

///////////////////////////////////////////////////////////////////////////////
//
//	Swap method https://www.geeksforgeeks.org/bubble-sort/
//
///////////////////////////////////////////////////////////////////////////////
void swap(unsigned int* xp, unsigned int* yp)
{
    unsigned int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Bubble: communication + traitement dans une machine à états
//
///////////////////////////////////////////////////////////////////////////////
void Bubble::bubble(void)
{
	/*
	
	À compléter
		
	Machine à états. Exemple:
	- demande des données à Reader
	- lecture du nombre d'éléments
	- lecture des données (1 lecture par cycle d'horloge)
	- Tri: a chaque passage dans l'état on fait un chagement de position si nécessaire. On reste dans l'état tant que le tri n'est pas terminé (1 opération par cycle d'hrologe)
	- Affichage (pas de wait nécessaire)
	- Arrêt de la simulations
	
	*/
	
	static unsigned int addr = 0x00;
	static std::vector<unsigned int> elements;
	static int i = 1;
	static int j = 1;
	switch (state)
	{
	case Demande_Req:
		this->address.write(addr);
		this->request.write(true);
		addr += 0x04;
		state = Lecture_Data;
		break;	
	case Lecture_Data :
		if(ack.read()){
			elements.push_back(this->data.read());
			this->request.write(false);
			if(elements.size()<=elements[0])
				state= Demande_Req;
			else{
				state = Bubble_Sort;
			}
		}		
		break;
	case Bubble_Sort :
		if (i == 1 && j == 1) std::cout<<std::endl<<"Bubble Begin "<<sc_time_stamp()<<std::endl;
		if(i<elements[0]){
			if(j<elements[0]-i+1){		
				if (elements[j] > elements[j + 1])
					swap(&elements[j], &elements[j + 1]);
				if (j+1 < elements[0]-i+1)
				{
					j++;
				}
				else{
					j = 1;
					i++;
				}
			}
		}else{
			std::cout<<std::endl<<"Bubble end "<<sc_time_stamp()<<std::endl;
			state = Affichage;
		}
		break;
	case Affichage :
		for (int it = 1; it <= elements[0]; it++)
		{
			std::cout << "valeur : " << it << " | " << elements[it] << std::endl;
		}
		state = Arret;	
		break;
	case Arret :
		sc_stop();
		break;
	default:			
		break;
	}
}

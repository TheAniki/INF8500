///////////////////////////////////////////////////////////////////////////////
//
//	Reader.h
//
///////////////////////////////////////////////////////////////////////////////
#ifndef _READER_H_
#define _READER_H_

#include <systemc.h>
#include "LMBIF.h"
#include <InterfaceRead.h>

///////////////////////////////////////////////////////////////////////////////
//
//	Class Reader
//
///////////////////////////////////////////////////////////////////////////////
class Reader : public sc_module, public InterfaceRead
{
	public:
		// Ports
		sc_in_clk clk;					// Horloge.
		sc_port<LMBIF> dataPortRAM;		// Port de donnee.
		sc_out<unsigned int> data;		// Donnee.
		sc_in<unsigned int> address;	// Adresse.
		sc_out<bool> ack; 				// Accuse de reception.
		sc_in<bool> request;			// Requete.
		
		// Constructor
		Reader( sc_module_name zName );

		// Destructor
		~Reader();

	private:
	
	// Read - InterfaceRead
	virtual unsigned int Read(unsigned int uiAddr);
};

#endif

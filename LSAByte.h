#pragma once

// Nécessaire dans .h pour que les ETIQUETTES soient accessibles (B9600, CS8, PAR...) à l'utilisateur
#include <termios.h>


class CLSAByte {

protected:	// Protected : la classe héritée aura accès à ces attributs (pas l'utilisateur de l'objet)

	int iTTYHandle;
	struct termios Parameters;

public:

	CLSAByte( void );
	int Ouvrir( char * pTTY_REF, int iFLAGS );
	int Fermer( void );
	int EnvoyerCaractere( char* pOctet );
	int RecevoirCaractere( char * pRCaractere );
	void ViderTampon( void );
	~CLSAByte( void );



};

#define _DEBUG

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <linux/serial.h> 

#include <errno.h>
#include "LSAByte.h"
#include "LectureBadgeRFID.h"

#define EXIT_SUCCESS 0

#define ERREUR_PARAM_OUVRIR -1
#define ERREUR_PARAM_RECEVOIRCARACTERE -2
#define ERREUR_PARAM_RECEVOIRTRAME -3
#define ERREUR_PARAM_ENVOYERTRAME -4
#define ERREUR_PARAM_ENVOYERCHAINE -5

#define ERREUR_APPLY_NEW_PARAMS -10
 
#define ERREUR_OUVERTURE_INTERFACE -20
#define ERREUR_FERMETURE_INTERFACE -21
#define ERREUR_ENVOI_TRAME -22
#define ERREUR_ENVOI_CHAINE -23
#define ERREUR_LECTURE_CARACTERE -24
#define ERREUR_LECTURE -25
#define ERREUR_LECTURE_CHAINE -26



using namespace std;




/*
	 Valeurs de retour en cas d'erreur :
x	[ ERREUR_PARAM_OUVRIR ] Erreur dans les PARAMETRES passes lors de l'appel de la fonction OUVRIR
x	[ ERREUR_PARAM_RECEVOIRCARACTERE ] Erreur dans le PARAMETRE passe lors de l'appel de la fonction RECEVOIRCARACTERE
x	[ ERREUR_PARAM_RECEVOIRTRAME ] Erreur dans les PARAMETRES passes lors de la fonction RECEVOIRTRAME
x	[ ERREUR_PARAM_ENVOYERTRAME ] Erreur dans les PARAMETRES passes lors de l'appel de la fonction ENVOYERTRAME
===============================================================================================
x	[ ERREUR_APPLY_NEW_PARAMS ] Erreur lors de l'application des NOUVEAUX parametres
===============================================================================================
x	[ ERREUR_OUVERTURE_INTERFACE ] Erreur lors de l'OUVERTURE de l'interface
x	[ ERREUR_OUVERTURE_INTERFACE ] Erreur lors de la FERMETURE de l'interface
x	[ ERREUR_ENVOI_TRAME ] Erreur lors de l'ECRITURE d'une TRAME sur l'interface
x	[ ERREUR_ENVOI_CHAINE ] Erreur lors de l'ECRITURE d'une CHAINE sur l'interface
x	[ ERREUR_LECTURE_CARACTERE ] Erreur lors de la LECTURE (Reception unique) sur l'interface
x	[ ERREUR_LECTURE ] Erreur lors de la LECTURE (Reception multiple) sur l'interface 
x	[ ERREUR_LECTURE_CHAINE ] Erreur lors de la LECTURE d'une CHAINE de caracteres se terminant par CR 
*/


// ========================== Methode d'ouverture de l'interface ========================
int CLSAByte::Ouvrir( char * pTTY_REF, int iFLAGS )
{

	// Ouverture du port et verification des parametres
	// O_RDWR : Ouverture en lecture et ecriture
	// O_NOCTTY : ??
	
	if( pTTY_REF == NULL ) return ERREUR_PARAM_OUVRIR; 
	iTTYHandle = open( pTTY_REF, O_RDWR | O_NONBLOCK | O_NOCTTY );
	if( iTTYHandle < 0 ) return ERREUR_OUVERTURE_INTERFACE; 
	

	// Initialisation des element de la structure a zéro pour plus de securité
	bzero( &Parameters, sizeof( Parameters ) ); 

	
	/* 
	Definition des parametres pour l'interface RS232
	L'entier iFLAGS est le resultat d'un OU BIT A BIT entre les consignes preprocesseur suivante :
	- B300, B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200 -> Pour la vitesse de transmission
	- CS5, CS6, CS7, CS8 : Mode de transmission avec 5, 6, 7 ou 8 bits de donnees
	- CSTOPB : Utiliser DEUX BITS DE STOP au lieu d'UN par defaut
	- PARENB : controle de la PARITE actif, PAIRE
	- PARODD : cumule avec PARENB, la PARITE est alors IMPAIRE
	- CLOCAL : Ignorer le controle de certaines lignes utilisé par les modem (utilisation d'un cable NULL-MODEM 3 fils)
	- CREAD : Permet de pouvoir RECEVOIR des donnees sur cette interface
	*/
	
	Parameters.c_cflag = iFLAGS;
	Parameters.c_iflag &= ~( INLCR | IGNCR | ICRNL | IXON | IXOFF );	
	Parameters.c_lflag &= ~( ECHO | ECHONL | ICANON | ISIG | IEXTEN );
	 
	Parameters.c_cc[VMIN] = 1; 
	Parameters.c_cc[VTIME] = 1;	// Attente en 10ème de secondes après dernier octet reçu 
	//Parameters.c_cc[VSUSP] = (char)-1; //(char)26; // otherwhise we can not send CTRL Z 


	// Cette fonction efface les donnees selon le parametre suivant :
	// TCIOFLUSH : designe la suppression des donnees lues et ecrites, mais pas encore transmises
	tcflush( iTTYHandle, TCIOFLUSH );

	// Application des nouveaux parametres
	// TCSANOW : application immediate de ceux-ci

        if( tcsetattr( iTTYHandle, TCSANOW, &Parameters ) != 0 ) return ERREUR_APPLY_NEW_PARAMS;


	return EXIT_SUCCESS;
}

// ========================== Constructeur =================================
CLSAByte::CLSAByte( void )
{
// Aucune operation n'est effectuée dans le constructeur car il ne peut retourner de valeur
}




// ============== Fermeture de la liaison série ============================
int CLSAByte::Fermer( void )
{

	// Fermeture de l'interface
	if( close( iTTYHandle ) < 0 ) return ERREUR_FERMETURE_INTERFACE; // Fermeture de l'interface
	
	return EXIT_SUCCESS;
}


// ================= Fonction d'envoi d'une chaine de caracteres ===========
int CLSAByte::EnvoyerCaractere( char * pOctet )
{

	// Ecriture vers l'interface 
	if( write( iTTYHandle, pOctet, 1 ) < 0 ) return ERREUR_ENVOI_CHAINE;
	
	return EXIT_SUCCESS;
}

// =================== Fonction de reception d'un caractere ================
int CLSAByte::RecevoirCaractere( char * pRCaractere )
{
int iReturnValue = 0;

	// Verification du parametre de la fonction 
	if( pRCaractere == NULL )
	{
		return ERREUR_PARAM_RECEVOIRCARACTERE;	
	} 

	// Reception d'un caractere 
	iReturnValue = read( iTTYHandle, pRCaractere, 1 );

	if( iReturnValue < 0 )
	{
		return ERREUR_LECTURE_CARACTERE;
	}

	return EXIT_SUCCESS;
}

// =============== Fonction de vidage du tampon de reception ===============
void CLSAByte::ViderTampon ( void )
{
	tcflush( iTTYHandle, TCIOFLUSH );
}


// ====================== Destructeur ======================================
CLSAByte::~CLSAByte( void )
{
	// Destructeur
}




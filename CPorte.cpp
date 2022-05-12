#define _DEBUG

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <linux/serial.h>
#include <errno.h>
#include <iomanip>

#include "CLecteurRFID.h"
#include "CBDD.h"
#include "LSAByte.h"
#include "CPorte.h"

using namespace std;


CPorte::CPorte() {

    this -> pLiaison = new CLSAByte;

    this -> Symbole = {'O','E'};

    // Ouverture de la liaison série

    pLiaison -> Ouvrir("/dev/ttyUSB1", B115200 | CS8 | CLOCAL | CREAD);

}


CPorte::~CPorte() {

    // Fermeture de la liaison série

    pLiaison -> Fermer();

    delete pLiaison;
    
}

bool CPorte::Ouvrir() {
    
    pLiaison -> ViderTampon();

      // Envoie du code ASCII du symbole O;

      pLiaison -> EnvoyerCaractere( & this -> Symbole[0] );

}

bool CPorte::Erreur() {
    
    pLiaison -> ViderTampon();

      // Envoie du code ASCII du symbole E;

      pLiaison -> EnvoyerCaractere( & this -> Symbole[1] );
    
}
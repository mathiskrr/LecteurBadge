#ifndef RFID_H
#define RFID_H

#include <string.h>
#include <string>
#include <termios.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "LSAByte.h"

using namespace std;

class CLectureBadgeRFID {

  private:

    CLSAByte * Lecteur;
    std::vector < char > TrameInventaire;
    std::vector < char > TrameRecu;
    std::vector < string > ListeEPCRecu;
    int Indice;

    unsigned int uiCrc16Cal(unsigned char const * pucY, unsigned char ucX);

  public:

    CLectureBadgeRFID();
    ~CLectureBadgeRFID();
    char Scanner();
    char FinScanner();
    vector < string > ObtenirListeEPC();
    string ObtenirEPC(char IndiceEPC);

};

#endif // RFID_H
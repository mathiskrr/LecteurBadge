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

class CLecteurRFID {

  private:

    CLSAByte * pLecteur;
    std::vector < char > TrameInventaire;
    std::vector < char > TrameRecu;
    std::vector < string > ListeEPCsRecus;

    unsigned int uiCrc16Cal(unsigned char const * pucY, unsigned char ucX);

  public:

    CLecteurRFID();
    ~CLecteurRFID();
    char Scanner();
    vector < string > GetListeEPC();
    string ObtenirEPC(char IndiceEPC);

};

#endif // RFID_H
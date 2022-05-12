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
#include "LSAByte.h"

using namespace std;

#define PRESET_VALUE 0xFFFF
#define POLYNOMIAL 0x8408

CLecteurRFID::CLecteurRFID() {

  this -> pLecteur = new CLSAByte;

  this -> TrameInventaire = {
    '\x04',
    '\xFF',
    '\x01',
    '\x1B',
    '\xB4'
  };

  // Ouverture de la liaison série

  pLecteur -> Ouvrir("/dev/ttyUSB0", B57600 | CS8 | CLOCAL | CREAD);

}


CLecteurRFID::~CLecteurRFID() {

    // Fermeture de la liaison série

    pLecteur -> Fermer();

    delete pLecteur;

  }


char CLecteurRFID::Scanner() {

    char len;
    char i;
    char Donnees;
    unsigned int CRCCalcul;
    unsigned short CRCRecu;
    unsigned int LSB;
    unsigned int MSB;
    unsigned int NbEPC;
    string DonneesEPC;
    unsigned int NbOctetEPC;
    int Indice;

      pLecteur -> ViderTampon();

      //cout << "Taille : " << ListeEPCsRecus.size() << endl;
      
      ListeEPCsRecus.clear();
      TrameRecu.clear();

      //cout << "Taille : " << ListeEPCsRecus.size() << endl;

      // Envoie de la TrameInventaire : Len / Adr / Cmd ( Inventory ) / LSB-CRC16 / MSB-CRC16

      pLecteur -> EnvoyerCaractere( & this -> TrameInventaire[0] );
      pLecteur -> EnvoyerCaractere( & this -> TrameInventaire[1] );
      pLecteur -> EnvoyerCaractere( & this -> TrameInventaire[2] );
      pLecteur -> EnvoyerCaractere( & this -> TrameInventaire[3] );
      pLecteur -> EnvoyerCaractere( & this -> TrameInventaire[4] );

      usleep(100000);

      while (pLecteur -> RecevoirCaractere( & len) != 0);

      //cout << hex << (int)len << " ";

    this -> TrameRecu.push_back(len);

    for (i = 1; i <= len; i = i + 1) {

      int Resultat;
      do {
        Resultat = pLecteur -> RecevoirCaractere( & Donnees);
      } while (Resultat != 0);


      //cout << hex << (int)Donnees << " ";

      this -> TrameRecu.push_back(Donnees);
    }

    // Calcul du CRC de la Trame Reçu

    CRCCalcul = uiCrc16Cal((const unsigned char * ) & this -> TrameRecu[0], len - 2 + 1);

    MSB = this -> TrameRecu[len - 1 + 1];
    LSB = this -> TrameRecu[len - 2 + 1];

    CRCRecu = MSB;
    CRCRecu = CRCRecu << 8;
    CRCRecu = CRCRecu + LSB;

    /*for(Indice = 0; Indice < TrameRecu.size(); Indice++ )
    {
      cout << "TrameRecu :" << hex << setfill ('0') << setw(2) << (int)TrameRecu[ Indice ] << endl;
    }*/

    if (this -> TrameRecu[3] == 1) // Status 
    {


      Indice = 4;
      NbEPC = this -> TrameRecu[Indice++];

      this -> ListeEPCsRecus.clear();

      while (NbEPC != 0) {

        NbOctetEPC = this -> TrameRecu[Indice++];
        DonneesEPC.clear();

        while (NbOctetEPC != 0) {

          DonneesEPC.push_back(this -> TrameRecu[Indice++]);

          NbOctetEPC = NbOctetEPC - 1;

        }

        this -> ListeEPCsRecus.push_back(DonneesEPC);

        NbEPC--;

      }

    }

    return ListeEPCsRecus.size();

}


vector < string > CLecteurRFID::GetListeEPC() {

  return this->ListeEPCsRecus;

}


string CLecteurRFID::GetEPC(char IndiceEPC) {
  
  if( IndiceEPC < ListeEPCsRecus.size() )
  {
    return this->ListeEPCsRecus[IndiceEPC];
  }
  else
  {
    return "";
  }

}


unsigned int CLecteurRFID::uiCrc16Cal(unsigned char const * pucY, unsigned char ucX) {

  unsigned char ucI, ucJ;
  unsigned short int uiCrcValue = PRESET_VALUE;

  for (ucI = 0; ucI < ucX; ucI++) {
    uiCrcValue = uiCrcValue ^ * (pucY + ucI);
    for (ucJ = 0; ucJ < 8; ucJ++) {
      if (uiCrcValue & 0x0001) {
        uiCrcValue = (uiCrcValue >> 1) ^ POLYNOMIAL;
      } else {
        uiCrcValue = (uiCrcValue >> 1);
      }
    }
  }
  return uiCrcValue;

}
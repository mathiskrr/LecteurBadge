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

#include "LectureBadgeRFID.h"

#include "LSAByte.h"

#define PRESET_VALUE 0xFFFF

#define POLYNOMIAL 0x8408

using namespace std;

CLectureBadgeRFID::CLectureBadgeRFID() {

  Lecteur = new CLSAByte;

  this -> TrameInventaire = {
    '\x04',
    '\xFF',
    '\x01',
    '\x1B',
    '\xB4'
  };

}

CLectureBadgeRFID::~CLectureBadgeRFID() {

    delete Lecteur;

  }



char CLectureBadgeRFID::Scanner() {

    
    // Ouverture du port et verification des parametres

    Lecteur -> Ouvrir("/dev/ttyUSB0", B57600 | CS8 | CLOCAL | CREAD);

    Lecteur -> ViderTampon();

    // Envoie de la TrameInventaire : Len / Adr / Cmd ( Inventory ) / LSB-CRC16 / MSB-CRC16

    Lecteur -> EnvoyerCaractere( & TrameInventaire[0]);
    Lecteur -> EnvoyerCaractere( & TrameInventaire[1]);
    Lecteur -> EnvoyerCaractere( & TrameInventaire[2]);
    Lecteur -> EnvoyerCaractere( & TrameInventaire[3]);
    Lecteur -> EnvoyerCaractere( & TrameInventaire[4]);

    usleep(1000000);

}

char CLectureBadgeRFID::FinScanner() {

Lecteur -> Fermer();

}

vector < string > CLectureBadgeRFID::ObtenirListeEPC() {

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

  while (Lecteur -> RecevoirCaractere( & len) != 0);

  TrameRecu.push_back(len);

  for (i = 1; i <= len; i = i + 1) {

    int Resultat;
    do {
      Resultat = Lecteur -> RecevoirCaractere( & Donnees);
    } while (Resultat != 0);

    TrameRecu.push_back(Donnees);
  }

  CRCCalcul = uiCrc16Cal((const unsigned char * ) & TrameRecu[0], len - 2 + 1);

  MSB = TrameRecu[len - 1 + 1];
  LSB = TrameRecu[len - 2 + 1];

  CRCRecu = MSB;
  CRCRecu = CRCRecu << 8;
  CRCRecu = CRCRecu + LSB;

  cout << "CRCs : " << hex << CRCCalcul << " " << CRCRecu << endl;

  if (CRCRecu != CRCCalcul) {
    cout << "Le CRCRecu est different de CRCCalcul" << endl;
  } else {
    cout << "Le CRCRecu est le même que CRCCalcul" << endl;

    if (TrameRecu[3] == 1) // Status 
    {

      Indice = 4;
      NbEPC = TrameRecu[Indice++];

      ListeEPCRecu.clear();

      while (NbEPC != 0) {

        NbOctetEPC = TrameRecu[Indice++];
        DonneesEPC.clear();

        while (NbOctetEPC != 0) {

          DonneesEPC.push_back(TrameRecu[Indice++]);

          NbOctetEPC = NbOctetEPC - 1;

        }

        //cout << DonneesEPC << endl;

        ListeEPCRecu.push_back(DonneesEPC);

        NbEPC--;

      }

      for (Indice = 0; Indice < ListeEPCRecu.size(); Indice++)

        cout << "Donnees EPC : " << ListeEPCRecu[Indice] << endl;
    } else {
      cout << " Pas de Badge à scanner ! " << endl;
    }

  }

}

string CLectureBadgeRFID::ObtenirEPC(char IndiceEPC) {

  this->Indice = IndiceEPC;

}

unsigned int CLectureBadgeRFID::uiCrc16Cal(unsigned char const * pucY, unsigned char ucX) {

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
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

#include "LecteurRFID.h"
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

  pLecteur -> Ouvrir("/dev/ttyUSB0", B57600 | CS8 | CLOCAL | CREAD);

}

CLecteurRFID::~CLecteurRFID() {

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

    // Envoie de la TrameInventaire : Len / Adr / Cmd ( Inventory ) / LSB-CRC16 / MSB-CRC16

    pLecteur -> EnvoyerCaractere( & this -> TrameInventaire[0]);
    pLecteur -> EnvoyerCaractere( & this -> TrameInventaire[1]);
    pLecteur -> EnvoyerCaractere( & this -> TrameInventaire[2]);
    pLecteur -> EnvoyerCaractere( & this -> TrameInventaire[3]);
    pLecteur -> EnvoyerCaractere( & this -> TrameInventaire[4]);

    while (pLecteur -> RecevoirCaractere( & len) != 0);

  this -> TrameRecu.push_back(len);

  for (i = 1; i <= len; i = i + 1) {

    int Resultat;
    do {
      Resultat = pLecteur -> RecevoirCaractere( & Donnees);
    } while (Resultat != 0);

    this -> TrameRecu.push_back(Donnees);
  }

  CRCCalcul = uiCrc16Cal((const unsigned char * ) & this -> TrameRecu[0], len - 2 + 1);

  MSB = this -> TrameRecu[len - 1 + 1];
  LSB = this -> TrameRecu[len - 2 + 1];

  CRCRecu = MSB;
  CRCRecu = CRCRecu << 8;
  CRCRecu = CRCRecu + LSB;

  cout << "CRCs : " << hex << CRCCalcul << " " << CRCRecu << endl;

  if (CRCRecu != CRCCalcul) {
    cout << "Le CRCRecu est different de CRCCalcul" << endl;
  } else {
    cout << "Le CRCRecu est le même que CRCCalcul" << endl;

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

        //cout << DonneesEPC << endl;

        this -> ListeEPCsRecus.push_back(DonneesEPC);

        NbEPC--;

      }

    } else {
      cout << " Pas de Badge à scanner ! " << endl;
    }

  }

}


vector < string > CLecteurRFID::GetListeEPC() {

  int Indice;

     if (this -> TrameRecu[3] == 1) // Status 
     {
      for (Indice = 0; Indice < this -> ListeEPCsRecus.size(); Indice++)

        cout << "Donnees EPC : " << this -> ListeEPCsRecus[Indice] << endl;
      }

}

string CLecteurRFID::ObtenirEPC(char IndiceEPC) {

  int Indice;

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
#include <string.h>

#include <string>

#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include "LSAByte.h"

#include "LectureBadgeRFID.h"

//include BDD :

#include <mysql_driver.h>
 
#include <mysql_connection.h>
 
#include <cppconn/resultset.h>
 
#include <cppconn/statement.h>



#include <iostream>

#include <sstream>

#include <vector>

using namespace std;

#define PRESET_VALUE 0xFFFF

#define POLYNOMIAL 0x8408

sql::mysql::MySQL_Driver * pDriver;
sql::Connection * pConnector;
sql::Statement * pStatement;
sql::ResultSet * pResult;

void ConnectionBDD();

// Prototype Fonction uiCrc16Cal() qui permet de calculer le Cheksum

//unsigned int uiCrc16Cal(unsigned char const * pucY, unsigned char ucX);

int main() {

  ConnectionBDD();
  
  
  string requete;

  requete = "SELECT badge_number FROM TBadges";
  
  
  
  
  delete pResult;
  delete pStatement;
  delete pConnector;
  
}  
  

void ConnectionBDD() {
 
  pDriver = sql::mysql::get_mysql_driver_instance();
  pConnector = pDriver -> connect("tcp://192.168.0.28:3306", "mathis_carrere", "sbRQi87R7");
  pStatement = pConnector -> createStatement();
}

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  // Création de l'objet Lecteur de la classe CLSAByte

  //CLSAByte * Lecteur = new CLSAByte;

  /*CLectureBadgeRFID * Badge = new CLectureBadgeRFID;

  while( 1 ) {

  Badge -> Scanner();

  Badge -> ObtenirListeEPC();

  Badge -> FinScanner();

  }

  delete Badge;

}*/

  /*while (1) {

    // Ouverture du port et verification des parametres

    Lecteur -> Ouvrir((char * )
      "/dev/ttyUSB0", B57600 | CS8 | CLOCAL | CREAD);

    char len;
    char i;
    char Donnees;
    std::vector<char> TrameRecup;
    unsigned int CRCCalcul;
    unsigned short CRCRecu;
    unsigned int LSB;
    unsigned int MSB;
    std::vector<string> EPC;
    unsigned int NbEPC;
    string DonneesEPC;
    unsigned int NbOctetEPC;
    int Indice;

    // Implementation de la Trame dans un Tableau Trame[]

    char Trame[] = {
      '\x04',
      '\xFF',
      '\x01',
      '\x1B',
      '\xB4'
    };

    // Vidange Buffer

    Lecteur -> ViderTampon();

    // Envoie de la trame : Len / Adr / Cmd ( Inventory ) / LSB-CRC16 / MSB-CRC16

    Lecteur -> EnvoyerCaractere( & Trame[0]);
    Lecteur -> EnvoyerCaractere( & Trame[1]);
    Lecteur -> EnvoyerCaractere( & Trame[2]);
    Lecteur -> EnvoyerCaractere( & Trame[3]);
    Lecteur -> EnvoyerCaractere( & Trame[4]);

    usleep(1000000);

    // Reception len en Octet de la trame réponse

    while ( Lecteur -> RecevoirCaractere( & len ) != 0 );

    // cout << "len : " << (int) len << endl;

    TrameRecup.push_back( len );

    //cout << (int)len << " ";

    // Reception Caractere selon la len

    for (i = 1; i <= len; i = i + 1) {

      int Resultat;
      do {
        Resultat = Lecteur -> RecevoirCaractere( & Donnees );
      } while ( Resultat != 0 );
        
      //while ( Lecteur -> RecevoirCaractere( & Donnees ) != 0 );

      // cout << hex << (int)Donnees << " ";// << dec << Donnees << endl;

      //cout << endl;// Sockage Numéro EPC dans un tableau dynamique

      TrameRecup.push_back( Donnees );
    }

    //cout << endl;

    CRCCalcul = uiCrc16Cal((const unsigned char * ) & TrameRecup[0], len-2+1);

    MSB = TrameRecup[len-1+1];
    LSB = TrameRecup[len-2+1];

    CRCRecu = MSB;
    CRCRecu = CRCRecu << 8;
    CRCRecu = CRCRecu + LSB;

    cout << "CRCs : " << hex << CRCCalcul << " " << CRCRecu << endl;

      if ( CRCRecu != CRCCalcul)
      {
        cout << "Le CRCRecu est different de CRCCalcul" << endl;
      }
      else
      {
        cout << "Le CRCRecu est le même que CRCCalcul" << endl;

        if( TrameRecup[ 3 ] == 1 )  // Status 
        {
          
          Indice = 4;
          NbEPC = TrameRecup[ Indice++ ];

          EPC.clear();
          
          while( NbEPC != 0)
          {

            NbOctetEPC = TrameRecup[ Indice++ ];
            DonneesEPC.clear();

            while( NbOctetEPC != 0 )
            {

              DonneesEPC.push_back( TrameRecup[ Indice++ ] );
      
              NbOctetEPC = NbOctetEPC - 1;


            }

            cout << DonneesEPC << endl;

            EPC.push_back( DonneesEPC );

            NbEPC --;

          }

          for(Indice = 0; Indice < EPC.size(); Indice++ )    

            cout << "Donnees EPC : " << EPC[ Indice ] << endl;
        }
        else
        {
          cout << " Pas de Badge à scanner ! " << endl;
        }

      }

    Lecteur -> Fermer();

  }

  //delete Lecteur;

  delete Badge;

  return 0;

}*/

// Définition Fonction uiCrc16Cal() qui permet de calculer le Cheksum

/*unsigned int uiCrc16Cal(unsigned char
  const * pucY, unsigned char ucX) {
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
}*/



#include <string.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "LSAByte.h"
#include "CLecteurRFID.h"
#include "CBDD.h"
#include "INIReader.h"
#include "CPorte.h"

using namespace std;

#define PRESET_VALUE 0xFFFF
#define POLYNOMIAL 0x8408

int main()
{
    CLecteurRFID *pLecteur = new CLecteurRFID;
    CPorte *pPorte = new CPorte;

    string IP;
    string Login;
    string Mdp;
    string Salle;

    INIReader *pReader = new INIReader("config.ini");

    //INIReader reader("config.ini");

    if (pReader->ParseError() < 0) {
        std::cout << "Can't load 'config.ini'\n";
    }
    IP = pReader->GetString( "Database.Setting", "HostName", "" );
    Salle = pReader->GetString( "Database.Setting", "Room", "" );
    Login = pReader->GetString( "Database.Setting", "UserID", "" );
    Mdp = pReader->GetString( "Database.Setting", "Password", "" );

    CBDD *pBDD = new CBDD( IP, Login, Mdp );

    while(1){

      int Indice;
      string NumeroEPC;
      std::vector < string > vsEPC;
      char NbEPCLues;

      pLecteur->Scanner();

      usleep(1000000);

      NbEPCLues = pLecteur->Scanner();

      vsEPC = pLecteur->GetListeEPC();

      NumeroEPC = pLecteur->GetEPC(0);

      if( NumeroEPC == "" )
      {
        cout << "Aucun Numéro de Badge lue !" << endl;
      }
      else{
        cout << "NbEPCLues : " << (int)NbEPCLues << endl;
        
        if( NbEPCLues == 0)
        {
          cout << "Pas de Badge à scanner !" << endl;
        }else{
          cout << "Numéro Badge : " << pLecteur->GetEPC(0) << endl;

          for(Indice = 0; Indice < vsEPC.size(); Indice++ )
          {

            cout << "Liste Numéro Badge : " << vsEPC[Indice] << endl;

          }
        }

        if( pBDD->VerifierBadge( NumeroEPC, Salle ) == true){

          pPorte->Ouvrir();

        }else{

          pPorte->Erreur();
        }

      }

    }

      delete pBDD;
      delete pLecteur;
      delete pPorte;

}

/*while(1){

      int Indice;
      std::vector < string > vsEPC;
      char NbEPCLues;

      pBadge->Scanner();

      usleep(100000);

      NbEPCLues = pBadge->Scanner();

      vsEPC = pBadge->GetListeEPC();

      cout << "NbEPCLues : " << (int)NbEPCLues << endl;
      
      if( NbEPCLues == 0)
      {
        cout << "Pas de Badge à scanner !" << endl;
      }else{
        cout << "Numéro Badge : " << pBadge->GetEPC(0) << endl;

        for(Indice = 0; Indice < vsEPC.size(); Indice++ )
        {

          cout << "Liste Numéro Badge : " << vsEPC[Indice] << endl;

        }
      }

    }*/
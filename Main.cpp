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
#include "LecteurRFID.h"
#include "CBDD.h"
#include "INIReader.h"

using namespace std;

#define PRESET_VALUE 0xFFFF
#define POLYNOMIAL 0x8408

int main()
{
    CLecteurRFID *pBadge = new CLecteurRFID;

    string IP;
    string Salle;

    INIReader *pReader = new INIReader("config.ini");

    //INIReader reader("config.ini");

    if (pReader->ParseError() < 0) {
        std::cout << "Can't load 'config.ini'\n";
    }
    IP = pReader->GetString( "Database.Setting", "HostName", "" );
    Salle = pReader->GetString( "Database.Setting", "Room", "" );

    CBDD *pBDD = new CBDD( IP, "mathis_carrere", "sbRQi87R7" );

      int Indice;
      string NumeroEPC;
      std::vector < string > vsEPC;
      char NbEPCLues;

      pBadge->Scanner();

      usleep(100000);

      NbEPCLues = pBadge->Scanner();

      vsEPC = pBadge->GetListeEPC();

      NumeroEPC = pBadge->GetEPC(0);

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

    pBDD->VerifierBadge( NumeroEPC, Salle );


    cout << "ok1" << endl;
    delete pBadge;
    cout << "ok2" << endl;
    delete pBDD;
    cout << "ok3" << endl;


  delete pBadge;

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
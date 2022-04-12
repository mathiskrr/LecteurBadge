#include <string.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>

#include "LSAByte.h"
#include "LecteurRFID.h"

using namespace std;

#define PRESET_VALUE 0xFFFF
#define POLYNOMIAL 0x8408

int main()
{
    CLecteurRFID *pBadge = new CLecteurRFID;
    
    while(1){

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
    }

    delete pBadge;

}

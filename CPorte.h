#ifndef CPorte_H
#define CPorte_H

#include <string.h>
#include <string>
#include <termios.h>
#include <iostream>
#include <sstream>
#include <vector>

#include "LSAByte.h"
#include "CLecteurRFID.h"
#include "CBDD.h"

using namespace std;

class CPorte {

  private:


  public:

    CPorte( );
    ~CPorte( );
    bool Ouvrir( );
    bool Fermer( );

};

#endif // CPorte_H
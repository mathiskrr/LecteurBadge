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
#include "CBDD.h"
#include "LSAByte.h"
#include "CPorte.h"

using namespace std;


CPorte::CPorte( ) {

}


CPorte::~CPorte() {
    
}

bool CPorte::Ouvrir() {
    
}

bool CPorte::Fermer() {
    
}
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
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iomanip>

#include "LecteurRFID.h"
#include "VerifBDD.h"
#include "LSAByte.h"

using namespace std;


CVerifBDD::CVerifBDD() {

    this -> pBadge = new CLecteurRFID;

}


CVerifBDD::~CVerifBDD() {

    delete pBadge;

}


void CVerifBDD::ConnexionBDD() {

    // Connexion a la Base de données
    pDriver = sql::mysql::get_mysql_driver_instance();
    pConnector = pDriver -> connect( "tcp://192.168.0.28:3306", "mathis_carrere", "sbRQi87R7" );
    pStatement = pConnector -> createStatement();

}

void CVerifBDD::FermetureBDD() {

    delete pDriver;
    delete pResult;
    delete pStatement;
    delete pConnector;

}

bool CVerifBDD::VerifierBadge( string NumeroEPC ) {
    
    string Badge;
    string Salle = "1";
    string Requete = "SELECT CASE WHEN `badge_number` = " + NumeroEPC + " AND `room_id` = " + Salle + " THEN 'true' ELSE 'false' END AS Autorisation FROM BEnOcean.TUsers ORDER BY Autorisation DESC LIMIT 1;";

    ConnexionBDD();


        pResult = pStatement->executeQuery( Requete );

        pResult->next();

        Badge = pResult->getString( "Autorisation" );


        if( Badge == "false" ){

            cout << "Ce badge n'est pas inscrit dans la base de donnees !" << endl;

        }
        else{

            cout << "Ce Badge est inscrit dans la base de donnees !" << endl;

        }

    FermetureBDD();

    return false;

}
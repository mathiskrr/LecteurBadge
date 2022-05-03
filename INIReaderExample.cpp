// Example that shows simple usage of the INIReader class

#include <iostream>
#include "INIReader.h"

using namespace std;

int main()
{
    INIReader reader("bdd.ini");

    if (reader.ParseError() < 0) {
        std::cout << "Can't load 'bdd.ini'\n";
        return 1;
    }
    std::cout	<< "IP : " << reader.GetString( "bdd", "IP", "" ) << endl
				<< "Nom : " << reader.GetString( "bdd", "Nom", "vide" ) << endl
				<< "Mot de passe : " << reader.GetString( "bdd", "Mot de passe", "vide" ) << endl
				<< endl;
    return 0;
}

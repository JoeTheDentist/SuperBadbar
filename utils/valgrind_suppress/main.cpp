#include <iostream>
#include <string>
#include <fstream>
 
#define INPUT "BABAR_SDL.errors" 
#define OUTPUT "BABAR_SDL.supp"

using namespace std;

/**
 *	Programme permettant de générer un fichier d'erreurs 
 *	à supprimer pour valgrind à partir d'un fichier contenant
 *	le rapport des erreurs à supprimer
 *	Il faut enlever l'introduction et la conclusion du rapport 
 *	de valgrind et finir le fichier à lire par "!!!"
 * 	Le nom des fichiers input et output sont pour le moment à écrire en dur dans le main du code
**/

void nouvelle_fonction(ifstream &input, ofstream &output)
{
	string fonction;
	input >> fonction;
	output << "fun:" + fonction << endl;
}

void nouvel_obj(ifstream &input, ofstream &output)
{
	output <<  "obj:*\n";
}


bool nouvelle_erreur(ifstream &input, ofstream &output)
{
	output << "\n{\n<yop>\nMemcheck:Leak\n";
	string valgrind, valgrind2;
	string fin_de_ligne;	
	string to_read;
	char lettre;
	input >> valgrind;
	valgrind2 = valgrind;
	while (valgrind2 == valgrind) {
		if (valgrind[0] == '!')
			return false;
		input >> valgrind;
	}
	getline(input,fin_de_ligne);
	bool continuer = true;
	bool ligne = true;
	while (continuer) {
		input >> valgrind;
		if (valgrind[0] == '!') {
			output << "}\n";	
			return false;
		}
		cout << valgrind << endl;
		ligne = true;
		while(ligne) {			
			input.get(lettre);
			if (lettre == '\n') {
				ligne = false;
				continuer = false;
			} else if (lettre == ':') {
				input.ignore(5, ' ');
				lettre = input.get();
				input.seekg(-1, ios::cur);
				
				if (lettre == '(' || lettre == '?')
					nouvel_obj(input, output);
				else
					nouvelle_fonction(input, output);				
				getline(input, fin_de_ligne);
				ligne = false;
			}
		}
	}
	output << "}\n";
	return true;
}

int main()
{

	ifstream input(INPUT, ios::in);
	if (!input) {
		cout << "FICHIER INTROUVABLE" << endl;
		return 0;
	}
	ofstream output(OUTPUT, ios::out);
	while(nouvelle_erreur(input, output)) {}

	
	
}

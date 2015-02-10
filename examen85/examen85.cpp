#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int const NE_max = 20;
int const NC_max = 5;
void menu(int &choix);

struct Element
{
	string nom;
	char code;
	int cotes[NC_max];
};

void saisie(struct Element tab[], int&NE, int&NC);
void affichage(struct Element tab[], int &NE, int NC);
void tri_alph_code(struct Element tab[], int NE);
void dichotomique(struct Element tab[], int NE, int &posmot, Element nomtrouve, bool &trouve);
void suppression_elmt(struct Element tab[], int &NE, int&posmot, Element nomtrouve);
void calcul_somme(struct Element tab[], int &NE, int NC, int som[]);
void sauvegarde(struct Element tab[], int &NE, int NC, int som[]);



void main()
{
	struct Element liste[NE_max];
	bool boucle = true;
	bool cond = false;
	int NE, NC, posmot;
	Element nomtrouve;
	int som[NE_max];
	do{
		int choix;
		menu(choix);
		switch (choix)
		{

		case 1:cout << "1-Saisie et affichage du tableau" << endl << endl;
			cond = true;
			saisie(liste, NE, NC);
			affichage(liste, NE, NC);
			break;
		case 2:cout << "Tri alphabetique du nom et du code" << endl;
			if (cond == true)
			{
				tri_alph_code(liste, NE);
				affichage(liste, NE, NC);
			}
			else cout << "!!!!!Effectuer dabord le choix 1!!!!!!" << endl;
			break;
		case 3:cout << "Suppression d'un element apres localisation " << endl;
			if (cond == true)
			{
				suppression_elmt(liste, NE, posmot, nomtrouve);
				affichage(liste, NE, NC);
			}
			else cout << "!!!!!!Effectuer dabord le choix 1 puis le 2!!!!!!" << endl;
			break;
		case 4:cout << "Sauvegarde d'element apd valeur seuil" << endl;
			if (cond == true)
			{
				calcul_somme(liste, NE, NC, som);
				sauvegarde(liste, NE, NC,som);

			}
			else cout << "!!!!!!Effectuer dabord le choix 1 puis le 2!!!!!!" << endl;
			break;
		case 5:cout << "Au revoir" << endl;
			boucle = false;
			break;
		}
	} while (boucle == true);

}

void menu(int &choix)
{
	do{
		cout << "****Bonjour****" << endl;
		cout << "Voici les differentes options proposees" << endl << endl;
		cout << "1-Saisie et affichage du tableau" << endl << endl;
		cout << "2-Tri par ordre alphabetique selon le nomet le code" << endl << endl;
		cout << "3-Suppression d'un element apres localisation" << endl << endl;
		cout << "4-Sauvegarde" << endl << endl;
		cout << "5-ARRET du programme" << endl << endl;
		cin >> choix;
	} while (choix<1 || choix>5);
}
void saisie(struct Element tab[], int&NE, int&NC)
{
	do{
		cout << "Avec combien d'elements voulez-vous travailler? !!!!! aux valeurs max" << endl;
		cin >> NE;
	} while (NE < 0 || NE > NE_max);
	do{
		cout << "Combien de cotes dispose chaque element?" << endl;
		cin >> NC;
	} while (NC < 0 || NC > NC_max);

	for (int i = 0; i < NE; i++)
	{
		cout << "Introduisez le NOM de tab[" << i + 1 << "]" << endl;
		cin.sync();
		cin.clear();
		getline(cin, tab[i].nom);
		cout << "Introduisez le CODE associe a tab[" << i + 1 << "]" << endl;
		cin >> tab[i].code;
		for (int j = 0; j < NC; j++)
		{
			cout << "Introduisez la COTE" << j << " associe a tab[" << i + 1 << "]" << endl;
			cin >> tab[i].cotes[j];
		}
	}

}
void affichage(struct Element tab[], int &NE, int NC)
{
	for (int i = 0; i < NE; i++)
	{
		cout << tab[i].nom << "  ";
		cout << tab[i].code << "  ";

		for (int j = 0; j < NC; j++)
		{
			cout << tab[i].cotes[j] << "  ";

		}
		cout << " " << endl;
	}

}
void tri_alph_code(struct Element tab[], int NE)
{
	bool perm = true;
	Element tmp1;
	Element tmp2;
	while (perm == true)
	{
		perm = false;
		for (int i = 0; i < NE - 1; i++)
		{

			if (tab[i].nom>tab[i + 1].nom)
			{

				tmp2 = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp2;
				perm = true;
			}
			else if (tab[i].nom == tab[i + 1].nom)
			{
				if (tab[i].code > tab[i + 1].code)
				{
					tmp1 = tab[i];
					tab[i] = tab[i + 1];
					tab[i + 1] = tmp1;
					perm = true;
				}

			}


		}
	}
}
void dichotomique(struct Element tab[], int NE, int &posmot, Element nomtrouve, bool &trouve)
{
	int Gauche;
	int Droite;
	int milieu;

	Gauche = 0;
	Droite = NE - 1;


	while (Gauche < Droite)
	{
		milieu = (Gauche + Droite) / 2;
		if ((nomtrouve.nom < tab[milieu].nom) || (nomtrouve.nom == tab[milieu].nom && nomtrouve.code <= tab[milieu].code))
		{
			Droite = milieu;
		}
		else
		{
			Gauche = milieu + 1;
		}


	}
	posmot = Droite;
	if (nomtrouve.nom == tab[Droite].nom && nomtrouve.code == tab[Droite].code)
	{
		trouve = true;
	}

}
void suppression_elmt(struct Element tab[], int &NE, int&posmot, Element nomtrouve)
{
	bool trouve = false;

	cout << "Quel nom voulez-vous supprimer?" << endl;
	cin.sync();
	cin.clear();
	getline(cin, nomtrouve.nom);
	cout << "Quel est le code associer a cet element?" << endl;
	cin >> nomtrouve.code;
	dichotomique(tab, NE, posmot, nomtrouve, trouve);
	if (trouve == true)
	{
		for (int i = posmot; i < NE - 1; i++)
		{
			tab[i] = tab[i + 1];
		}
		NE = NE - 1;
	}
	else { cout << "!!!!!!Le mot introduis n'existe pas!!!!!!" << endl; }

}
void calcul_somme(struct Element tab[], int &NE, int NC, int som[])
{
	int somme = 0;
	for (int i = 0; i < NE; i++)
	{
		somme = 0;
		for (int j = 0; j < NC; j++)
		{
			somme = somme + tab[i].cotes[j];
		}
		som[i] = somme;
	}
	/*for (int k = 0; k < NE; k++)
	{
		cout << som[k]<<endl;
	}*/

}
void sauvegarde(struct Element tab[], int &NE, int NC, int som[])
{
	int seuil=0;
	do{
		cout << "Introduisez une valeur seuil comprise entre 0 et 100" << endl;
		cin >> seuil;
	} while (seuil<0 || seuil>100);

	string nom_fichier;
	cout << "quel nom voulez vous donner au fichier? \n" << "entrez le format en .txt \n";
	cin.sync();
	cin.clear();
	getline(cin, nom_fichier);
	ofstream ecrit;
	ecrit.open(nom_fichier);
	if (ecrit)
	{
		for (int i = 0; i < NE; i++)
		{

			if (som[i]>seuil)
			{

				ecrit << tab[i].nom << "    ";
				ecrit << tab[i].code << "    ";

				for (int j = 0; j < NC; j++)
				{
					ecrit << tab[i].cotes[j] << "\t";
				}
				cout << "  " << endl;
			}
		}
	}
	else
	{
		cout << "\n le fichier n'a pas pu etre ouvert \n";
	}






}

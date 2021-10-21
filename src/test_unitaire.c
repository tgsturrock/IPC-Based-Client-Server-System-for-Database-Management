
#include "recherche.h"

/*
 * test_unitaire.c
 *
 *  Created on: 11 oct. 2021
 *  Par : Ylann Blouzat et Thomas Giguere Sturrock
 */

void test_recherche(){
	//Variable servant aux test
	t_critere critere=creer_critere();
	int titre_faux = 2000;
	char *titre_vrai = "Titre";
	char *genre="action";
	char *categorie="short";
	int annee1=2000;
	int annee2=2001;
	char *annees3="2000:2005";
	char *annees4="20005:2000";//test d'un intervalle inverse
	char *annees5="2000;2010";//test avec un mauvais separateur
	char *recup_titre;
	char *recup_genre;
	char *recup_categorie;
	int recup_annee_min;
	int recup_annee_max;

	//essai des fonctions
	set_titre(critere, titre_faux); //test si un titre peut etre un nombre ce qui ne peut etre le cas
	set_titre(critere, titre_vrai); //test si un titre peut etre une chaine de caractere ce qui est correct
	set_genre(critere, genre);
	set_categorie(critere, categorie);
	set_annee_parution_min(critere, annee1);
	set_annee_parution_max(critere, annee2);

	recup_titre=get_titre(critere); //recuperation du titre dans la structure critere
	printf ("Le titre est %s", recup_titre);
	recup_genre=get_genre(critere);
	printf ("Le genre est %s", recup_genre);
	recup_categorie=get_categorie(critere);
	printf ("La categorie est %s", recup_categorie);
	recup_annee_min=get_annee_parution_min(critere);
	printf ("L'annee de parution min est %d", recup_annee_min);
	recup_annee_max=get_annee_parution_max(critere);
	printf ("L'annee de parution max est %d", recup_annee_max);

	set_intervalle_annees(critere, annees3);
	set_intervalle_annees(critere, annees4);
	set_intervalle_annees(critere, annees5);
}

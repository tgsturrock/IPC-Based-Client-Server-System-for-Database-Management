/*
 *  serveur.c
 *
 *  Par : Thomas Giguere Sturrock, Ylann Blouzat
 *  Created on: 25 oct. 2021
 *
 *  Programme qui communique avec un client. Le serveur interagie avec un base de donnees
 *  afin de pouvoir tirer de l'information et/ou lui apporter des modifications selon la demande
 *  du client.
 *
 */

/*
 * Lab3 Serveur-HLR01
 * La portion du programme responsable de l'interatction avec la base de donnees
 * da ete decouple a partir de implementation du laboratoire #2.
 *
 * Serveur-HLR01 finie
 */

#include <unistd.h>
#include <stdio.h>
#include "recherche.h"
#include "imdb.h"
#include "resultat.h"
#include <string.h>

int main(int argc, char *argv[]) {
	char *titre = NULL, *genre = NULL, *annees = NULL, *categorie = NULL,
			*cote = NULL;

	//Lab3 client-HLR02
	/*
	 * On se sert de getopt afin de passer au travers du tableau argv pour retrouver les arguments passer en parametere
	 * afin d'associer des valeurs au chanps qui sont associees a ces arguments.
	 */
	int opt; //variable servant a passer d'un argument a l'autre.
	int flag = 0;
	while ((opt = getopt(argc, argv, ":tcagv")) != -1) {
		switch (opt) {
		case 't':
			titre = argv[optind];
			optind++;
			break;
		case 'c':
			categorie = argv[optind];
			optind++;
			break;
		case 'a':
			annees = argv[optind];
			optind++;
			break;
		case 'g':
			genre = argv[optind];
			optind++;
			break;
			//Lab3-HLR03
			/*
			 * Argument -v qui permet a l'uti;isateur
			 * de demander a evaluer un titre
			 */
		case 'v':
			flag = 1;
			break;
			//HLR03 finie
		case ':':
			printf("Veuillez saisir un titre.\n");
			break;
		case '?':
			printf("unknown option: %c\n", optopt);
			break;
		}
	}
	// optind is for the extra arguments
	// which are not parsed
	for (; optind < argc; optind++) {
		printf("extra arguments: %s\n", argv[optind]);
	}
	//On s<assure qu'au moins un titre est passe en parametre
	if (titre == NULL) {
		printf("Veuillez saisir un titre\n");
		return 0;
	}
	//client-HLR02 finie

	// Création de la structure critere et stockage des arguments reçus
	t_critere critere = creer_critere();

	set_titre(critere, titre);
	if (categorie)
		set_categorie(critere, categorie);
	if (genre)
		set_genre(critere, genre);
	if (annees)
		set_intervalle_annees(critere, annees);

	//Lab2-HLR24
	/*
	 * Le programme principale explore les deux fichiers de base de donnees en utilisant les fonctions du module imdb
	 */

	//recherche dans la base de donnee pour des titre qui concorde avec les criteres de recherche
	t_resultat resultat = lecture(critere);

	//Ajout des cotes de moyenne et nombre de vote aux resultats
	lecture_cote(resultat);
	//HLR24 finie

	//Lab2-HLR25
	/*
	 * Le programme principal donne les resultats de recherche l'utilisateur en utilisant les fonctions du modure resultat.
	 */
	//Impression des resultat en 2 fichier tsv
	fichier_resultat(resultat);
	//HLR25 finie


	int note;
	t_titre titre_chercher = cree_titre();

	int num_titre;
	printf("Veuillez entre un numero de titre:\n");
	//scanf("%i", &num_titre);
	num_titre = 0;
	titre_chercher = print_titre(resultat,num_titre);
	//titre_chercher = get_titre_ID(resultat,"tt0000039");
	printf("\tNumero de titre ; %i\n", num_titre);
	printf("Veuillez entre une cote:\n");
	//scanf("%i", &note);
	note = 10;
	printf("\tNote a rajouter ; %i\n", note);

	fichier_cote(titre_chercher, note);



	//Lab2-HLR26
	/*
	 * Toute la memoire alloue est desallouee avant de quitter le progamme.
	 */
	for (int i = 0; i < get_nb_titre(resultat); i++) {
		if (get_titre_r(resultat, i) != NULL) {
			detruire_titre(get_titre_r(resultat, i));
		}
	}
	//libere la memoire
	detruire_resultat(resultat);
	detruire_critere(critere);


	return 0;
}
//HLR26 finie

//HLR26 finie


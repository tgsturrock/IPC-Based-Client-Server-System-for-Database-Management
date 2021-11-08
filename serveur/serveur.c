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


#include "recherche.h"
#include "imdb.h"
#include "resultat.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_CRITERE_LECTURE "/eclipse-workspace/troisieme-laboratoire/fifo1"

int main(int argc, char *argv[]) {
	char *titre = NULL, *genre = NULL, *annees = NULL, *categorie = NULL,
			*cote = NULL;
    int descripteur_fifo_critere_lecture;
    int noctets=0;
    int erreur_serv=0;
    int taille_titre;
    int taille_genre;
    int taille_categorie;


    erreur_serv = mkfifo(FIFO_CRITERE_LECTURE , 0666);
    if(erreur_serv != 0) {
      printf("Erreur lors de la creation du premier FIFO\n");
      exit(1);
    }
    printf("FIFO cree avec succes\n");
    descripteur_fifo_critere_lecture = open(FIFO_CRITERE_LECTURE, O_RDONLY);

    noctets = read(descripteur_fifo_critere_lecture, &taille_titre, sizeof(int));
    if(noctets == sizeof(int)) {
      titre = malloc(taille_titre*sizeof(char));
    }
    else {
      printf("Erreur lors de la lecture du FIFO\n");
      exit(1);
    }
    noctets = read(descripteur_fifo_critere_lecture, titre, taille_titre*sizeof(char));
    if(noctets != taille_titre*sizeof(char)) {
      printf("Erreur lors de la lecture du FIFO\n");
      exit(1);
    }
    noctets = read(descripteur_fifo_critere_lecture, &taille_genre, sizeof(int));
    if(noctets == sizeof(int)) {
      genre = malloc(taille_genre*sizeof(char));
    }
    else {
      printf("Erreur lors de la lecture du FIFO\n");
      exit(1);
    }
    noctets = read(descripteur_fifo_critere_lecture, genre, taille_genre*sizeof(char));
    if(noctets != taille_genre*sizeof(char)) {
      printf("Erreur lors de la lecture du FIFO\n");
      exit(1);
    }
    noctets = read(descripteur_fifo_critere_lecture, &taille_categorie, sizeof(int));
    if(noctets == sizeof(int)) {
      categorie = malloc(taille_categorie*sizeof(char));
    }
    else {
      printf("Erreur lors de la lecture du FIFO\n");
      exit(1);
    }
    noctets = read(descripteur_fifo_critere_lecture, categorie, taille_categorie*sizeof(char));
    if(noctets != taille_categorie*sizeof(char)) {
      printf("Erreur lors de la lecture du FIFO\n");
      exit(1);
    }




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



	return 0;
}
//HLR26 finie

//HLR26 finie


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
#define FIFO_RESULTAT_ECRITURE "/eclipse-workspace/troisieme-laboratoire/fifo2"

int main(int argc, char *argv[]) {
	char *titre = NULL, *genre = NULL, *annees = NULL, *categorie = NULL, *ID = NULL, *cote = NULL;
    int descripteur_fifo_critere_lecture;
    int descripteur_fifo_resultat_ecriture;
    int noctets=0;
    int erreur=0;
    int annee_parution_min;
    int annee_parution_max;
    int taille_titre;
    int taille_genre;
    int taille_categorie;
    int taille_resultat_titre;
    int taille_resultat_genre;
    int taille_resultat_categorie;
    int taille_resultat_ID;

    /* Tube-HLR02 Reception du critere de recherche cote serveur */

    erreur = mkfifo(FIFO_CRITERE_LECTURE , 0666);
    if(erreur != 0) {
      printf("Erreur lors de la creation du premier FIFO\n");
      exit(1);
    }
    erreur = mkfifo(FIFO_RESULTAT_ECRITURE , 0666);
    if(erreur != 0) {
      printf("Erreur lors de la creation du second FIFO\n");
      exit(1);
    }

    printf("FIFOs cree avec succes\n");

    descripteur_fifo_critere_lecture = open(FIFO_CRITERE_LECTURE, O_RDONLY);
    descripteur_fifo_resultat_ecriture=open(FIFO_RESULTAT_ECRITURE,O_WRONLY);

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
    noctets = read(descripteur_fifo_critere_lecture, annee_parution_min, sizeof(int));
    if(noctets != sizeof(int)) {
      printf("Erreur lors de la lecture du FIFO\n");
      exit(1);
    }
    noctets = read(descripteur_fifo_critere_lecture, annee_parution_max, sizeof(int));
    if(noctets != sizeof(int)) {
      printf("Erreur lors de la lecture du FIFO\n");
      exit(1);
    }
    /* Tube-HLR02 finie */



	// Création de la structure critere et stockage des arguments reçus
	t_critere critere = creer_critere();

	set_titre(critere, titre);
	if (categorie)
		set_categorie(critere, categorie);
	if (genre)
		set_genre(critere, genre);
	if (annee_parution_min != 0){
		set_annee_parution_min(critere, annee_parution_min);
	}
	if (annee_parution_max != 0){
		set_annee_parution_max(critere,annee_parution_max);
	}

	/* Tube-HLR03 : On verifie le fonctionnement */

    printf("Serveur : je recois l'information suivante:\n");
    printf("Titre: %s\n", get_titre(critere));
    if (genre){
        printf("Genre: %s\n", get_genre(critere));
    }
    if (categorie){
    	printf("Categorie: %s\n", get_categorie(critere));
    }
    if (annees){
    	printf("Annee_min: %f\n", get_annee_parution_min(critere));
    	printf("Annee_max: %f\n", get_annee_parution_max(critere));
    }

    /* Tube-HLR03 finie */

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

	/* Tube-HL:R04 : Envoi des resultats cote serveur */

    noctets=write(descripteur_fifo_resultat_ecriture, get_nb_titre(resultat), sizeof(int));
    if(noctets < sizeof(int)) {
      printf("Probleme lors de l'ecriture dans le FIFO\n");
      exit(1);
    }
    int i=0;
	while(i,i<get_nb_titre(resultat)){

	    taille_resultat_titre=strlen(get_titre_t(get_titre_r(resultat,i)))+1;
	    taille_resultat_genre=strlen(get_genre_t(get_titre_r(resultat,i)))+1;
	    taille_resultat_categorie=strlen(get_categorie_t(get_titre_r(resultat,i)))+1;
	    taille_resultat_ID=strlen(get_ID_t(get_titre_r(resultat,i)))+1;
	    titre = malloc(taille_resultat_titre*sizeof(char));
	    genre = malloc(taille_resultat_genre*sizeof(char));
	    categorie = malloc(taille_resultat_categorie*sizeof(char));
	    ID = malloc(taille_resultat_ID*sizeof(char));

	    noctets=write(descripteur_fifo_resultat_ecriture, &taille_resultat_ID, sizeof(int));
	    if(noctets < sizeof(int)) {
	      printf("Probleme lors de l'ecriture dans le FIFO\n");
	      exit(1);
	    }
	    noctets=write(descripteur_fifo_resultat_ecriture,get_ID_t(get_titre_r(resultat,i)),taille_resultat_ID*sizeof(char));
	    if(noctets < taille_resultat_ID*sizeof(char)) {
	      printf("Probleme lors de l'ecriture dans le FIFO\n");
	      exit(1);
	    }

	    noctets=write(descripteur_fifo_resultat_ecriture, &taille_resultat_categorie, sizeof(int));
	    if(noctets < sizeof(int)) {
	      printf("Probleme lors de l'ecriture dans le FIFO\n");
	      exit(1);
	    }
	    noctets=write(descripteur_fifo_resultat_ecriture,get_categorie_t(get_titre_r(resultat,i)),taille_resultat_categorie*sizeof(char));
	    if(noctets < taille_resultat_categorie*sizeof(char)) {
	      printf("Probleme lors de l'ecriture dans le FIFO\n");
	      exit(1);
	    }

	    noctets=write(descripteur_fifo_resultat_ecriture, &taille_resultat_titre, sizeof(int));
	    if(noctets < sizeof(int)) {
	      printf("Probleme lors de l'ecriture dans le FIFO\n");
	      exit(1);
	    }
	    noctets=write(descripteur_fifo_resultat_ecriture,get_titre_t(get_titre_r(resultat,i)),taille_resultat_titre*sizeof(char));
	    if(noctets < taille_resultat_titre*sizeof(char)) {
	      printf("Probleme lors de l'ecriture dans le FIFO\n");
	      exit(1);
	    }
    	noctets=write(descripteur_fifo_resultat_ecriture, get_annee_parution_min_t(get_titre_r(resultat,i)) , sizeof(int));
    	if(noctets < sizeof(int)) {
    		printf("Probleme lors de l'ecriture dans le FIFO\n");
    		exit(1);
    	}
	    noctets=write(descripteur_fifo_resultat_ecriture, &taille_resultat_genre, sizeof(int));
	    if(noctets < sizeof(int)) {
	      printf("Probleme lors de l'ecriture dans le FIFO\n");
	      exit(1);
	    }
	    noctets=write(descripteur_fifo_resultat_ecriture,get_genre_t(get_titre_r(resultat,i)),taille_resultat_genre*sizeof(char));
	    if(noctets < taille_resultat_genre*sizeof(char)) {
	      printf("Probleme lors de l'ecriture dans le FIFO\n");
	      exit(1);
	    }
	    free(titre);
	    free(genre);
	    free(categorie);
	    free(ID);
	    i++;
	}
	/* Tube-HLR04 finie */

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


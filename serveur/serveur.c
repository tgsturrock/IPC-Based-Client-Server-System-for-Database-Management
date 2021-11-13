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

#define FIFO_CLIENT_LECTURE "/tmp/fifo1"
#define FIFO_SERVEUR_ECRITURE "/tmp/fifo2"


int main(int argc, char *argv[]) {
	char *titre = NULL, *genre = NULL, *categorie = NULL,
			*cote = NULL;
	int descripteur_fifo_client_lecture;
	int descripteur_fifo_serveur_ecriture;
	int noctets=0;
	int erreur=0;

	char null[2]="0";

	int annee_parution_min;
	int annee_parution_max;
	int taille_titre;
	int taille_genre;
	int taille_categorie;


	/* Lab3 Tube-HLR02
	 * Ouverture des fifos, connection avec le client puis
	 * Reception du critere de recherche cote serveur */
	printf("Démarrage du serveurs\n");

	unlink(FIFO_SERVEUR_ECRITURE);
	unlink(FIFO_CLIENT_LECTURE);

	//Cree les fifo d'ecriture et de lecture entre le serveur et le client
	erreur = mkfifo(FIFO_CLIENT_LECTURE , 0666);
	if(erreur != 0) {
		unlink(FIFO_SERVEUR_ECRITURE);
		unlink(FIFO_CLIENT_LECTURE);
		printf("Erreur client lors de la creation du FIFO_CRITERE_ECRITURE\n");
		exit(1);
	}
	erreur = mkfifo(FIFO_SERVEUR_ECRITURE , 0666);
	if(erreur != 0) {
		unlink(FIFO_SERVEUR_ECRITURE);
		unlink(FIFO_CLIENT_LECTURE);
		printf("Erreur lors de la creation du FIFO_RESULTAT_LECTURE\n");
		exit(1);
	}
	else{
		//Si tout fonctionne on attend la connexion avec le client
		printf("En attente d'une connexion avec le clients...\n");
	}

	//Ouverture des fifos du cote serveur
	descripteur_fifo_client_lecture = open(FIFO_CLIENT_LECTURE, O_RDONLY);
	descripteur_fifo_serveur_ecriture = open(FIFO_SERVEUR_ECRITURE, O_WRONLY);

	//On affiche que la connection est etablie
	printf("Connexion avec le client établie\n");

	//Lecture du champ titre et de sa taille
	noctets = read(descripteur_fifo_client_lecture, &taille_titre, sizeof(int));
	if(noctets == sizeof(int)) {
		titre = malloc(taille_titre*sizeof(char));
	}
	else {
		printf("Erreur lors de la lecture du de la taille du champ titre\n");
		exit(1);
	}
	noctets = read(descripteur_fifo_client_lecture, titre, taille_titre*sizeof(char));
	if(noctets != taille_titre*sizeof(char)) {
		printf("Erreur lors de la lecture du champ titre\n");
		exit(1);
	}

	//Lecture du champ genre et de sa taille
	noctets = read(descripteur_fifo_client_lecture, &taille_genre, sizeof(int));
	if(noctets == sizeof(int)) {
		genre = malloc(taille_genre*sizeof(char));
	}
	else {
		printf("Erreur lors de la lecture de la taille du champ genre\n");
		exit(1);
	}
	noctets = read(descripteur_fifo_client_lecture, genre, taille_genre*sizeof(char));
	if(noctets != taille_genre*sizeof(char)) {
		printf("Erreur lors de la lecture du du champ genre\n");
		exit(1);
	}

	//Lecture du champ categorie et de sa taille
	noctets = read(descripteur_fifo_client_lecture, &taille_categorie, sizeof(int));
	if(noctets == sizeof(int)) {
		categorie = malloc(taille_categorie*sizeof(char));
	}
	else {
		printf("Erreur lors de la lecture de la taille du champ categorie\n");
		exit(1);
	}
	noctets = read(descripteur_fifo_client_lecture, categorie, taille_categorie*sizeof(char));
	if(noctets != taille_categorie*sizeof(char)) {
		printf("Erreur lors de la lecture du champ categorie\n");
		exit(1);
	}

	//Lecture des champs d'annees de parutions
	noctets = read(descripteur_fifo_client_lecture, &annee_parution_min, sizeof(int));
	if(noctets != sizeof(int)) {
		printf("Erreur lors de la lecture de l'annee de parution minimum\n");
		exit(1);
	}
	noctets = read(descripteur_fifo_client_lecture, &annee_parution_max, sizeof(int));
	if(noctets != sizeof(int)) {
		printf("Erreur lors de la lecture de l'annee de parution maximum\n");
		exit(1);
	}
	/* Lab3 Tube-HLR02 finie */

	// Création de la structure critere et stockage des arguments reçus
	t_critere critere = creer_critere();
	//
	set_titre(critere, titre);
	if (strcmp(categorie,null)!=0)
		set_categorie(critere, categorie);
	else{
		free(categorie);
	}
	if (strcmp(genre,null) != 0)
		set_genre(critere, genre);
	else{
		free(genre);
	}
	if (annee_parution_min != 0){
		set_annee_parution_min(critere, annee_parution_min);
	}
	if (annee_parution_max != 0){
		set_annee_parution_max(critere,annee_parution_max);
	}

	/* Lab3 Tube-HLR03 : On verifie le fonctionnement
	 * On affiche les valeurs des champs recu par le client.
	 */

	printf("Réception des criteres de recherche:\n");
	printf("\tTitre: %s\n", get_titre(critere));
	if (get_genre(critere) != NULL){
		printf("\tGenre: %s\n", get_genre(critere));
	}
	if (get_categorie(critere)!= NULL){
		printf("\tCategorie: %s\n", get_categorie(critere));
	}
	if (annee_parution_min != 0 && annee_parution_max != 0){
		printf("\tAnnee_min: %i\n", get_annee_parution_min(critere));
		printf("\tAnnee_max: %i\n", get_annee_parution_max(critere));
	}
	/* Tube-HLR03 finie */

	//recherche dans la base de donnee pour des titre qui concorde avec les criteres de recherche
	t_resultat resultat = lecture(critere);

	//Ajout des cotes de moyenne et nombre de vote aux resultats
	lecture_cote(resultat);
	//Lab2-HLR24 finie

	//Affichage des resultats cote serveur
	fichier_resultat(resultat);
	//HLR25 finie


	//Lab3 Tube-HLR04
	/* Le serveur envois les resultats de la recherche au client */

	int nb_titre = 0;
	nb_titre = get_nb_titre(resultat);

	//Envoit le nombre de titres contenu dans la strcuture resultat
	noctets=write(descripteur_fifo_serveur_ecriture, &nb_titre, sizeof(int));
	if(noctets < sizeof(int)) {
		printf("Probleme lors de l'ecriture du nombre de titre dans le FIFO\n");
		exit(1);
	}

	int taille_resultat_titre;
	int taille_resultat_genre;
	int taille_resultat_categorie;
	int taille_resultat_ID;
	t_titre titre_resultat = cree_titre();

	/*for(int i =0 ;i<get_nb_titre(resultat);i++){

		titre_resultat = get_titre_r(resultat, 1);

		//On envoit la taille du champ ID et le champ ID au client
		taille_resultat_ID = strlen(get_ID_t(titre_resultat))+1;
		noctets=write(descripteur_fifo_serveur_ecriture, &taille_resultat_ID, sizeof(int));
		if(noctets < sizeof(int)) {
			printf("Probleme lors de l'ecriture de la taille du champ ID dans le FIFO\n");
			exit(1);
		}
		noctets=write(descripteur_fifo_serveur_ecriture,get_ID_t(titre_resultat),taille_titre*sizeof(char));
		if(noctets < taille_titre*sizeof(char)) {
			printf("Probleme lors de l'ecriture du champ ID dans le FIFO\n");
			exit(1);
		}
		//On envoit la taille du champ categorie et le champ categorie au client
		taille_resultat_categorie=strlen(get_categorie_t(titre_resultat))+1;
		noctets=write(descripteur_fifo_serveur_ecriture, &taille_resultat_categorie, sizeof(int));
		if(noctets < sizeof(int)) {
			printf("Probleme lors de l'ecriture de la taille de la categorie dans le FIFO\n");
			exit(1);
		}
		noctets=write(descripteur_fifo_serveur_ecriture,get_categorie_t(titre_resultat),taille_categorie*sizeof(char));
		if(noctets < taille_categorie*sizeof(char)) {
			printf("Probleme lors de l'ecriture du champ categorie dans le FIFO\n");
			exit(1);
		}
		//On envoit la taille du champ titre et le champ titre au client
		taille_resultat_titre=strlen(get_titre_t(titre_resultat))+1;
		noctets=write(descripteur_fifo_serveur_ecriture, &taille_resultat_titre, sizeof(int));
		if(noctets < sizeof(int)) {
			printf("Probleme lors de l'ecriture de la taille du champ titre dans le FIFO\n");
			exit(1);
		}
		noctets=write(descripteur_fifo_serveur_ecriture,get_titre_t(titre_resultat),taille_titre*sizeof(char));
		if(noctets < taille_titre*sizeof(char)) {
			printf("Probleme lors de l'ecriture du champ titre dans le FIFO\n");
			exit(1);
		}
		//On envoit l'annee de parution du film
		annee_parution_min = get_annee_parution_min_t(titre_resultat);
		noctets=write(descripteur_fifo_serveur_ecriture, &annee_parution_min , sizeof(int));
		if(noctets < sizeof(int)) {
			printf("Probleme lors de l'ecriture de l'annee de parution dans le FIFO\n");
			exit(1);
		}
		//On envoit la taille du champ genre et le champ genre au client
		taille_resultat_genre=strlen(get_genre_t(titre_resultat))+1;
		noctets=write(descripteur_fifo_serveur_ecriture, &taille_resultat_genre, sizeof(int));
		if(noctets < sizeof(int)) {
			printf("Probleme lors de l'ecriture de la taille du champ genre dans le FIFO\n");
			exit(1);
		}
		noctets=write(descripteur_fifo_serveur_ecriture,get_genre_t(titre_resultat),taille_genre*sizeof(char));
		if(noctets < taille_genre*sizeof(char)) {
			printf("Probleme lors de l'ecriture du champ genre dans le FIFO\n");
			exit(1);
		}
		//i++;

	}
	//Tube-HLR04 finie

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


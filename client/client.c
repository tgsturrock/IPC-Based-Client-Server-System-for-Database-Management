/**
 * Programme Client - client.c
 *
 * Par : Thomas Giguere Sturrock, Ylann Blouzat
 * Date : 23 Octobre 2021
 *
 * Ce programme est responsable de l'interaction avec l'usager.
 * Il demande a l'usager quelle operation operation qu'il ou elle souhaite effectuer
 * pour ensuite interprete la requete au programme serveur, qui lui renvera les donnees desirer.
 * Le programme montrera alors les donnees a l'usager.
 *
 *
 */

/*
 * Lab3 client-HLR01
 * Decouplage de la partie qui s'occupe d'interagir avec l'utilisateur
 * dans le projet du laboratoire #2.
 *
 * client-HLR01 finie
 */
#include "recherche.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_CLIENT_ECRITURE "/tmp/fifo1"
#define FIFO_SERVEUR_LECTURE "/tmp/fifo2"


int main(int argc, char *argv[]) {
	char *titre = NULL, *genre = NULL, *annees = NULL, *categorie = NULL, *note = NULL;
	int descripteur_fifo_client_ecriture;
	int descripteur_fifo_serveur_lecture;
	int noctets=0;
	int erreur=0;
	char* null = malloc(2*sizeof(char));
	null = "0";


	int taille_titre;
	int taille_genre;
	int taille_categorie;
	int nb_titre_resultat;
	int taille_ID_r;
	int taille_titre_r;
	int taille_genre_r;
	int taille_categorie_r;

	//Lab3 client-HLR02
	/*
	 * On se sert de getopt afin de passer au travers du tableau argv pour retrouver les arguments passer en parametere
	 * afin d'associer des valeurs au chanps qui sont associees a ces arguments.
	 */
	int opt;//variable servant a passer d'un argument a l'autre.
	int flag = 0;
	while((opt = getopt(argc, argv, ":tcagv")) != -1)
	{
		switch(opt)
		{
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
			printf ("Veuillez entree une valeur pour l'option desire\n");
			break;
		case '?':
			printf ("unknown option: %c\n", optopt);
			break;
		}
	}
	// optind is for the extra arguments
	// which are not parsed
	for( ;optind < argc; optind++){
		printf("extra arguments: %s\n", argv[optind]);
	}
	//On s<assure qu'au moins un titre est passe en parametre
	if(titre == NULL){
		printf ("Veuillez saisir un titre\n");
		return 0;
	}
	//client-HLR02 finie


	// Création de la structure critere et stockage des arguments reçus
	t_critere critere = creer_critere();
	/*
	 * On ecrit dans les champs du critere de recherche,si un argument n'a
	 * pas ete specifier par l'usage on inscrit une valeur "null" dans le champ correspondant.
	*/
	set_titre(critere, titre);
	if (categorie)
		set_categorie(critere, categorie);
	else{
		set_categorie(critere, null);
	}
	if (genre)
		set_genre(critere, genre);
	else{
		set_genre(critere, null);
	}
	if (annees)
		set_intervalle_annees(critere, annees);
	else{
		set_intervalle_annees(critere, null);
	}


	/*Lab3 Tube-HLR01 On envoi les criteres de recherche en les ecrivant dans un FIFO*/
	//Ouverture des fifos pour communiquer avec le serveur
	descripteur_fifo_client_ecriture = open(FIFO_CLIENT_ECRITURE,O_WRONLY);
	descripteur_fifo_serveur_lecture = open(FIFO_SERVEUR_LECTURE, O_RDONLY);
	//On indique que la connection a ete etablie avec le serveur
	printf("Connection etablie avec le serveur.\n");

	//On envois le champ titre et sa taille au serveur
	taille_titre=strlen(get_titre(critere))+1;
	noctets=write(descripteur_fifo_client_ecriture, &taille_titre, sizeof(int));
	if(noctets < sizeof(int)) {
		printf("Probleme lors de l'ecriture de la taille du champ titre dans le FIFO\n");
		exit(1);
	}
	noctets=write(descripteur_fifo_client_ecriture,get_titre(critere),taille_titre*sizeof(char));
	if(noctets < taille_titre*sizeof(char)) {
		printf("Probleme lors de l'ecriture du champ titre dans le FIFO\n");
		exit(1);
	}

	/*
	 * Si le critere genre est present on l'envoit avec sa taille au serveur sinon on envois une valeur
	 * "null" pour indiquer au serveur qu'aucun genre a ete specifier par l'usage.
	 */
	if (genre){
		taille_genre=strlen(get_genre(critere))+1;
		noctets=write(descripteur_fifo_client_ecriture, &taille_genre, sizeof(int));
		if(noctets < sizeof(int)) {
			printf("Probleme lors de l'ecriture de la taille du champ genre dans le FIFO\n");
			exit(1);
		}
		noctets=write(descripteur_fifo_client_ecriture,get_genre(critere),taille_genre*sizeof(char));
		if(noctets < taille_genre*sizeof(char)) {
			printf("Probleme lors de l'ecriture du champ genre dans le FIFO\n");
			exit(1);
		}
	}
	else if (genre == NULL){
		genre = null;
		taille_genre=strlen(null)+1;
		noctets=write(descripteur_fifo_client_ecriture, &taille_genre, sizeof(int));
		if(noctets < sizeof(int)) {
			printf("Probleme lors de l'ecriture taille du champ genre null dans le FIFO\n");
			exit(1);
		}
		noctets=write(descripteur_fifo_client_ecriture,get_genre(critere),taille_genre*sizeof(char));
		if(noctets < taille_genre*sizeof(char)) {
			printf("Probleme lors de l'ecriture du champ genre nill dans le FIFO\n");
			exit(1);
		}
	}

	/*
	 * Si le critere categorie est présente on l'envoit avec sa taille au serveur sinon on envois une valeur
	 * "null" pour indiquer au serveur qu'aucune categorie a ete specifier par l'usage.
	 */
	if (categorie){
		taille_categorie=strlen(get_categorie(critere))+1;
		noctets=write(descripteur_fifo_client_ecriture, &taille_categorie, sizeof(int));
		if(noctets < sizeof(int)) {
			printf("Probleme lors de l'ecriture dans le FIFO\n");
			exit(1);
		}
		noctets=write(descripteur_fifo_client_ecriture,get_categorie(critere),taille_categorie*sizeof(char));
		if(noctets < taille_categorie*sizeof(char)) {
			printf("Probleme lors de l'ecriture dans le FIFO\n");
			exit(1);
		}
	}
	else if (categorie == NULL){
		categorie = null;
		taille_categorie=strlen(null)+1;
		noctets=write(descripteur_fifo_client_ecriture, &taille_categorie, sizeof(int));
		if(noctets < sizeof(int)) {
			printf("Probleme lors de l'ecriture dans le FIFO\n");
			exit(1);
		}
		noctets=write(descripteur_fifo_client_ecriture,get_categorie(critere),taille_categorie*sizeof(char));
		if(noctets < taille_categorie*sizeof(char)) {
			printf("Probleme lors de l'ecriture dans le FIFO\n");
			exit(1);
		}
	}

	/*
	 * Si des annees de parution sont présentes dans les critères on les envoit au serveur sinon on envois
	 * des valeurs "null" pour indiquer au serveur qu'aucune annee de parution a ete specifier par l'usage.
	 */
	if (annees){
		int annee_min = get_annee_parution_min(critere);
		noctets=write(descripteur_fifo_client_ecriture, &annee_min , sizeof(int));
		if(noctets < sizeof(int)) {
			printf("Probleme lors de l'ecriture dans le FIFO\n");
			exit(1);
		}
		int annee_max = get_annee_parution_max(critere);
		noctets=write(descripteur_fifo_client_ecriture, &annee_max, sizeof(int));
		if(noctets < sizeof(int)) {
			printf("Probleme lors de l'ecriture dans le FIFO\n");
			exit(1);
		}
	}
	else if(annees == NULL){
		int annee_min = 0;
		noctets=write(descripteur_fifo_client_ecriture, &annee_min , sizeof(int));
		if(noctets < sizeof(int)) {
			printf("Probleme lors de l'ecriture dans le FIFO\n");
			exit(1);
		}
		int annee_max = 0;
		noctets=write(descripteur_fifo_client_ecriture, &annee_max, sizeof(int));
		if(noctets < sizeof(int)) {
			printf("Probleme lors de l'ecriture dans le FIFO\n");
			exit(1);
		}

	}
	/* Tube-HLR01 finie */

	/* Tube-HLR03 : On verifie le fonctionnement on affichant les champs du critere envoyer par le client*/
	printf("Nous avons transmis l'information suivante:\n");
	printf("Titre: %s\n", get_titre(critere));
	if (genre != null){
		printf("Genre: %s\n", get_genre(critere));
	}
	if (categorie != null){
		printf("Categorie: %s\n", get_categorie(critere));
	}
	if (annees){
		printf("Annee_min: %i\n", get_annee_parution_min(critere));
		printf("Annee_max: %i\n", get_annee_parution_max(critere));
	}
	/* Tube-HLR03 finie */

	detruire_critere(critere);

	/* Tube-HLR04: reception des resultats envoyer par le serveur puis on les affiche */
	//On fait la lecture du nombre de resultats reçus
	noctets = read(descripteur_fifo_serveur_lecture, &nb_titre_resultat, sizeof(int));
	if(noctets != sizeof(int)) {
		printf("Erreur lors de la lecture du nombre de titres venant du serveur\n");
		exit(1);
	}
	//On affiche le nombre de résultats reçus
	printf("\t%d résultats reçus\n ");

	int i=0;//variable servant comme compteur
	/*
	 * Pour chaque resultats reçus on affiche ses champs a l'usager
	 */
	while(i<nb_titre_resultat){
		char *titre_r = NULL, *genre_r = NULL, *categorie_r = NULL, *ID_r = NULL;
		int annee_parution_min_r=-1;

		printf("\t[%i] ",i+1);

		//Lecture et affichage du champ ID
		noctets=read(descripteur_fifo_serveur_lecture, &taille_ID_r, sizeof(int));
		if(noctets == sizeof(int)) {
			ID_r = malloc(taille_ID_r*sizeof(char));
		}
		else {
			printf("Erreur lors de la lecture de la taille du champ ID du FIFO\n");
			exit(1);
		}
		noctets=read(descripteur_fifo_serveur_lecture,ID_r,taille_ID_r*sizeof(char));
		if(noctets != taille_ID_r*sizeof(char)) {
			printf("Erreur lors de la lecture du champ ID du FIFO\n");
			exit(1);
		}
		printf("%s\t",ID_r);

		//Lecture et affichage du champ categorie
		noctets=read(descripteur_fifo_serveur_lecture, &taille_categorie_r, sizeof(int));
		if(noctets == sizeof(int)) {
			categorie_r = malloc(taille_categorie_r*sizeof(char));
		}
		else {
			printf("Erreur lors de la lecture de la taille du champ categorie du FIFO\n");
			exit(1);
		}
		noctets=read(descripteur_fifo_serveur_lecture,categorie_r,taille_categorie_r*sizeof(char));
		if(noctets != taille_categorie_r*sizeof(char)) {
			printf("Erreur lors de la lecture du champ categorie du FIFO\n");
			exit(1);
		}
		printf("%s\t",categorie_r);

		//Lecture et affichage du champ titre
		noctets=read(descripteur_fifo_serveur_lecture, &taille_titre_r, sizeof(int));
		if(noctets == sizeof(int)) {
			titre_r = malloc(taille_titre_r*sizeof(char));
		}
		else {
			printf("Erreur lors de la lecture de la taille du champ titre du FIFO\n");
			exit(1);
		}
		noctets=read(descripteur_fifo_serveur_lecture,titre_r,taille_titre_r*sizeof(char));
		if(noctets != taille_titre_r*sizeof(char)) {
			printf("Erreur lors de la lecture du champ titre du FIFO\n");
			exit(1);
		}
		printf("%s\t",titre_r);

		//Lecture et affichage de l'annee de parution
		noctets=read(descripteur_fifo_serveur_lecture, &annee_parution_min_r, sizeof(int));
		if(noctets != sizeof(int)) {
			printf("Erreur lors de la lecture de l'annee de parution du FIFO\n");
			exit(1);
		}
		printf("%i\t",annee_parution_min_r);

		//Lecture et affichage du champ genre
		noctets=read(descripteur_fifo_serveur_lecture, &taille_genre_r, sizeof(int));
		if(noctets == sizeof(int)) {
			genre_r = malloc(taille_genre_r*sizeof(char));
		}
		else {
			printf("Erreur lors de la lecture du FIFO\n");
			exit(1);
		}
		noctets=read(descripteur_fifo_serveur_lecture,genre_r,taille_genre_r*sizeof(char));
		if(noctets != taille_genre_r*sizeof(char)) {
			printf("Erreur lors de la lecture du FIFO\n");
			exit(1);
		}
		printf("%s\n",genre_r);
		i++;
	}
    /* Tube-HLR05 et HLR06 finie */

    return 0;
}
//HLR26 finie


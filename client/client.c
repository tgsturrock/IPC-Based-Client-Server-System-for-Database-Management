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

#define FIFO_CRITERE_ECRITURE "/eclipse-workspace/troisieme-laboratoire/fifo1"

int main(int argc, char *argv[]) {
    char *titre = NULL, *genre = NULL, *annees = NULL, *categorie = NULL, *note = NULL;
    int descripteur_fifo_critere_ecriture;
    int noctets=0;
    int erreur=0;
    int taille_titre;
    int taille_genre;
    int taille_categorie;
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


    set_titre(critere, titre);
    if (categorie)
        set_categorie(critere, categorie);
    if (genre)
        set_genre(critere, genre);
    if (annees)
        set_intervalle_annees(critere, annees);

    /* Tube-HLR01 On envoi les criteres de recherche en les ecrivant dans un FIFO*/

    erreur = mkfifo(FIFO_CRITERE_ECRITURE , 0666);
    if(erreur != 0) {
      printf("Erreur lors de la creation du premier FIFO\n");
      exit(1);
    }


    printf("FIFO cree avec succes\n");

    taille_titre=strlen(get_titre(critere))+1;
    taille_genre=strlen(get_genre(critere))+1;
    taille_categorie=strlen(get_categorie(critere))+1;

    descripteur_fifo_critere_ecriture = open(FIFO_CRITERE_ECRITURE,O_WRONLY);

    noctets=write(descripteur_fifo_critere_ecriture, &taille_titre, sizeof(int));
    if(noctets < sizeof(int)) {
      printf("Probleme lors de l'ecriture dans le FIFO\n");
      exit(1);
    }
    noctets=write(descripteur_fifo_critere_ecriture,get_titre(critere),taille_titre*sizeof(char));
    if(noctets < taille_titre*sizeof(char)) {
          printf("Probleme lors de l'ecriture dans le FIFO\n");
          exit(1);
    }
    noctets=write(descripteur_fifo_critere_ecriture, &taille_genre, sizeof(int));
    if(noctets < sizeof(int)) {
      printf("Probleme lors de l'ecriture dans le FIFO\n");
      exit(1);
    }
    noctets=write(descripteur_fifo_critere_ecriture,get_genre(critere),taille_genre*sizeof(char));
    if(noctets < taille_genre*sizeof(char)) {
          printf("Probleme lors de l'ecriture dans le FIFO\n");
          exit(1);
    }
    noctets=write(descripteur_fifo_critere_ecriture, &taille_categorie, sizeof(int));
    if(noctets < sizeof(int)) {
      printf("Probleme lors de l'ecriture dans le FIFO\n");
      exit(1);
    }
    noctets=write(descripteur_fifo_critere_ecriture,get_categorie(critere),taille_categorie*sizeof(char));
    if(noctets < taille_categorie*sizeof(char)) {
          printf("Probleme lors de l'ecriture dans le FIFO\n");
          exit(1);
    }
    noctets=write(descripteur_fifo_critere_ecriture, get_annee_parution_min(critere) , sizeof(int));
    if(noctets < sizeof(int)) {
      printf("Probleme lors de l'ecriture dans le FIFO\n");
      exit(1);
    }
    noctets=write(descripteur_fifo_critere_ecriture, get_annee_parution_max(critere) , sizeof(int));
    if(noctets < sizeof(int)) {
      printf("Probleme lors de l'ecriture dans le FIFO\n");
      exit(1);
    }

    /* Tube-HLR01 finie */

    detruire_critere(critere);



    return 0;
}
//HLR26 finie


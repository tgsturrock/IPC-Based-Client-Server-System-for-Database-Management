/**
 * Programme Client - client.c
 *
 * Par : Thomas Giguere Sturrock, Ylann Blouzat
 * Date : 23 Octobre 2021
 *
 * Ce programme est responsable de l'interaction avec l'usager.
 * Il demande a l'usager quelle operation operation qu'il ou elle souhater effectuer
 * pour ensuite interprete la requete au programme serveur, qui lui renvera les donnees desirer.
 * Le programme montrera alors les donnees a l'usager.
 *
 *
 */

#include "recherche.h"
#include "imdb.h"
#include "resultat.h"
#include <unistd.h>
#include <stdio.h>
//#include <string.h>

int main(int argc, char *argv[]) {
    char *titre = NULL, *genre = NULL, *annees = NULL, *categorie = NULL;

    //Lab3-HLR02
    /*
     * On se sert de getopt afin de passer au travers du tableau argv pour retrouver les arguments passer en parametere
     * afin d'associer des valeurs au chanps qui sont associees a ces arguments.
     */
    int opt;//variable servant a passer d'un argument a l'autre.

       while((opt = getopt(argc, argv, ":tcag")) != -1)
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
       }
       //HLR02 finie


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

//Lab2-HLR26
/*
 * Toute la memoire alloue est desallouee avant de quitter le progamme.
 */
 for (int j =0 ;j<get_nb_titre(resultat);j++){
	 detruire_titre((get_titre_r(resultat,j)));
 }
    //libere la memoire
 	detruire_resultat(resultat);
    detruire_critere(critere);

    return 0;
}
//HLR26 finie


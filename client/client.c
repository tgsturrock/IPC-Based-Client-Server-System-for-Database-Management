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
//test
#include "recherche.h"
#include <unistd.h>
#include <stdio.h>
//#include <string.h>

int main(int argc, char *argv[]) {
    char *titre = NULL, *genre = NULL, *annees = NULL, *categorie = NULL, *note = NULL;

    //Lab3-HLR02
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
       //HLR02 finie
       if(note == NULL){
    	   printf ("Veuillez saisir un titre\n");
       }

    // Création de la structure critere et stockage des arguments reçus
    t_critere critere = creer_critere();

    if(strpbrk(titre,"") == NULL){
    	strcat(titre," ");
    }

    set_titre(critere, titre);
    if (categorie)
        set_categorie(critere, categorie);
    if (genre)
        set_genre(critere, genre);
    if (annees)
        set_intervalle_annees(critere, annees);

    detruire_critere(critere);

    return 0;
}
//HLR26 finie


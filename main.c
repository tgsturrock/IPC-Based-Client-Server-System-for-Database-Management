/**
 * Programme principal - main.c
 *
 * Par :
 * Date : 
 *
 * À compléter...
 *
 * Exemple d'exécution:
 *  ./a.out -t "The Matrix" -c "movie" -a "1990:2000"
 */

#include "recherche.h"
#include "imdb.h"
#include "resultat.h"
//#include <string.h>

int main(int argc, char *argv[]) {
    char *titre = NULL, *genre = NULL, *annees = NULL, *categorie = NULL;

    // Lab2-HLR01 - Arguments provenant du terminal
    // Si aucun argument n'est donné, le programme s'arrête
    if (argc < 2) {
        printf ("Erreur, pas d'arguments");
        free (argv);
        return 0;
    }
    //HLR01 finie


    // Lab2-HLR02 - Arguments possibles
    for (int i = 1; i < argc ; i++) {
        // Option de titre
        if (strcmp(argv[i], "-t") == 0) {
            // On passe a l'argument qui vient après l'option
            i++;// On implemente le titre
            titre = argv[i];
            i++;
        }
        // Lab2-HLR03 - Argument obligatoire
        else{
        	printf("Vous devez specifier un titre\n");
        	return 0;
        }
        //HLR03 finie
        if (argv[i] != NULL){
        		if(strcmp(argv[i], "-c") == 0) {
        			i++; // On implemente la categorie
        			categorie = argv[i];
        			i++;
        		}
        }
        if (argv[i] != NULL){
        	if (strcmp(argv[i], "-a") == 0) {
        		i++; // On implemente les annees
        		annees = argv[i];
        		i++;
        		}
        }
        if (argv[i] != NULL){
        		if (strcmp(argv[i], "-g") == 0) {
        		i++; // On implemente le genre
        		genre = argv[i];
        		i++;
        		}
        	}
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


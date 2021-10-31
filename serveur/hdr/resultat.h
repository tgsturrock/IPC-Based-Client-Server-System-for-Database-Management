/**
 * Module recherche - recherche.h
 *
 * Par : Ylann Blouzat et Thomas Giguere Sturrock
 * Date : Septembre 2021
 *
 * Le module resultat est responsable de gérer la structure de données qui permet
 * de contenir tous les arguments de recherche reçus par le programme principal.
 * Il définit le type t_titre qui contient les les champs perinents relier a un film.
 */


#ifndef RESULTAT_H
#define RESULTAT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/**
 * Encapsulation de la structure titre
 * Les champs sont accessibles seulement à l'intérieur du module resultat.c
 */
typedef struct titre* t_titre;

/**
 * Encapsulation de la structure resultat
 * Les champs sont accessibles seulement à l'intérieur du module resultat.c
 */

typedef struct resultat* t_resultat;

/*
 * Encapsulation de la fonction qui alloue un bloc memoire a une structure titre
 */
t_titre cree_titre(void);

/*
 * Encapsulation de la fonction qui alloue un bloc memoire a une structure resultat
 */

t_resultat cree_resultat(void);

void calcul_moyenne(t_titre titre, char* nouvelle_cote);

void set_numero_ligne(t_titre titre, int numero_ligne);

void set_note_et_nombre_t(t_titre titre, char* note_moyenne, int nombre_votes);

void add_titre(t_resultat resultat, t_titre titre);

void set_ID_t(t_titre titre, char* ID);

void set_titre_t(t_titre titre, char* titre_str);

void set_genre_t(t_titre titre, char* genre);

void set_categorie_t(t_titre titree, char* categorie);

void set_annee_parution_min_t(t_titre titre, int annee);

void copy_titre(t_titre titre, t_titre copyTitre);


void detruire_titre(t_titre titre);

void detruire_resultat(t_resultat resultat);


/**
 * Observateur de ID
 *
 * Permet d'obtenir le ID de la structure titre
 *
 * titre : la structure à observer
 *
 * Retour : chaine de caractères constituant le ID de la structure donnée
 *          trouve dans la base
 */
char* get_ID_t(t_titre titre);

/**
 * Observateur de titre
 *
 * Permet d'obtenir le titre de la structure titre
 *
 * titre : la structure à observer
 *
 * Retour : chaine de caractères constituant le titre de la structure donnée
 *          trouve dans la base
 */

char* get_titre_t(t_titre titre);

/**
 * Observateur de genre
 *
 * Permet d'obtenir le genre de la structure titre
 *
 * titre : la structure à observer
 *
 * Retour : chaine de caractères constituant le genre de la structure donnée
 *          trouve dans la base
 */

char* get_genre_t(t_titre titre);

/**
 * Observateur de categorie
 *
 * Permet d'obtenir la categorie de la structure titre
 *
 * titre : la structure à observer
 *
 * Retour : chaine de caractères constituant la categorie de la structure donnée
 *          trouve dans la base
 */

char* get_categorie_t(t_titre titre);

/**
 * Observateur de l'annee de parution minimale
 *
 * Permet d'obtenir l'annee de parution minimale de la structure titre
 *
 * titre : la structure à observer
 *
 * Retour : chaine de caractères constituant l'annee de parution minimale de la structure donnée
 *          trouve dans la base
 */

int get_annee_parution_min_t(t_titre titre);

/**
 * Observateur de moyenne
 *
 * Permet d'obtenir la moyenne de la structure titre
 *
 * titre : la structure à observer
 *
 * Retour : chaine de caractères constituant la moyenne de la structure donnée
 *          trouve dans la base
 */

char* get_moyenne(t_titre titre);

/**
 * Observateur de vote
 *
 * Permet d'obtenir le nombre de votes de la structure titre
 *
 * titre : la structure à observer
 *
 * Retour : chaine de caractères constituant le nombre de votes de la structure donnée
 *          trouve dans la base
 */

int get_vote(t_titre titre);

t_titre get_titre_r(t_resultat resultat, int i);

/**
 * Observateur du nombre de titres
 *
 * Permet d'obtenir le nombre de titre de la structure resultat
 *
 * resultat : la structure à observer
 *
 * Retour : nombre entier constituant le nombre de titres de la structure resultat retournee a l'utilisateur
 */

int get_nb_titre(t_resultat resultat);

/**
 * Observateur de numero de ligne
 *
 * Permet d'obtenir le numero de ligne a laquelle se trouve un titre
 * dans le fichier title_ratings.tsv
 *
 * titre : la structure a observer
 *
 * retour: nombre entier constituant le numero de ligne a laquelle se trouve un titre
 *
 */

int get_numero_ligne(t_titre titre);



void fichier_resultat(t_resultat resultat);



#endif

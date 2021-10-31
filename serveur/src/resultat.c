#include "resultat.h"


// Lab2-HLR04 Definition de structure - Titre
/**
 * Structure de données qui permet de contenir tous les arguments
 * d'un titre. Ce sont les champs pertinant qui definissent un titre.
 *
 * ID : identifiant unique du film (tconst)
 * titre: titre rechercher (primaryTitle)
 * annee_parution_min: années de parution (startYear)
 * categorie: (titleType);
 * genre: gentre titre soit; film, video, etc  (genres)
 */
struct titre {
	char* ID;
	char* titre;
	int annee_parution_min;
	char* categorie;
	char* genre;
//Lab2-HLR15
/*
 * Deux nouveau champs sont ajoutes a la structure titre elles correspondent
 * au average rating et au nombre de vote du titre.
 */
	char* note_moyenne;//average rating
	int nombre_votes;//nombre de votes

//Lab3 serveur-HLR03
/* On ajoute un champ pour emmagasiner le numero de ligne */
	int numero_ligne;

};
//HLR04 finie

//Lab2-HLR06 Definition structure Resultats
/*
 * Definition de la structure représentant les résultats de recherche.
 * Elle contient la liste des titres retenus.
 */
struct resultat {
	t_titre* titre;//tableau contenant une liste de titre
	long int nb_titre;// nomnbre de titre contenu dans la liste
};
//HLR06	 finie


//constructeur

//Lab2-HLR05 Allocation de memoires des titres
/*
 * Fonction publique qui alloue dynamiquement un espace memoire pour la struture t_titre et retourne un pointeur vers celle-ci.
 */
t_titre cree_titre(void){

	t_titre titre;//Variable de type t_titre

	titre = (t_titre) malloc(sizeof(struct titre));

	//assert(titre!= NULL);

	if(titre == NULL){
		printf("Echec d'allocation memoire pour titre");
		return 0;
	}

	else{
	        titre->ID = NULL;
	        titre->titre = NULL;
	        titre->annee_parution_min = -1;
	        titre->categorie = NULL;
	        titre->genre = NULL;
	        //lab2-HLR15
	        titre->note_moyenne = NULL;
	        titre->nombre_votes=-1;
	        //HLR15 finie
	        titre->numero_ligne=-1;
	        //serveur-HLR03 finie
	    }
	    return titre;
}
//HLR05 finie

//Lab2-HLR07
/*
 * Fonction publique qui allour dynamiquement un espace memoire
 * pour la structure  resultat
 */
t_resultat cree_resultat(void){

	t_resultat resultat;

	resultat = (t_resultat) malloc(sizeof(struct resultat));

	if(resultat == NULL){
		printf("Echec d'allocation memoire pour resultat");
		return 0;
	}

	else{
		resultat->titre = (t_titre*) malloc(sizeof(t_titre));
		resultat->nb_titre = 0;
	}
	return resultat;
}
//HLR07 finie

//Lab2-HLR08
/*
 * Fonction qui rajoute une structure titre a la structure de resultats et qui fait une copie chaque champ
 * du titre recu en parametre
 */
void add_titre(t_resultat resultat, t_titre titre){

	if (resultat == NULL){
		printf("Structure RESULTAT invalide lors de l'ajout de titre au resultat");
		return;
	}
	if(titre == NULL){
		printf("Structure TITRE invalide lors de l'ajout de titre au resultat");
		return;
	}

	t_titre copy = cree_titre();

	copy_titre(titre, copy); // variable servant a copier le titre


	int i = resultat->nb_titre;

	//Si il y a plus qu'un titre on incremente la largeur du tableau
	if(i > 0){

		int j = i+1;
		t_titre* ptr;//Stocke temporairement l'adresse de l'espace re-alloue
		ptr = (t_titre*)realloc(resultat->titre, j*sizeof(t_titre));


		if (ptr == NULL){
			printf("Erreur d'allocation lors de l'ajout d'un titre");
		}
		resultat->titre = ptr;


		//resultat->titre[i]= cree_titre();
		resultat->titre[i] = copy;//rajoute un titre dans le tableau de resultat
		resultat->nb_titre++;//incremente le nombre de titre
	}
	else{
	//resultat->titre[i] = cree_titre();
	resultat->titre[i] = copy;//rajoute un titre dans le tableau de resultat
	resultat->nb_titre++;//incremente le nombre de titre
	}
}
//HLR08 finie

//Lab2-HLR09
/*
 * Fonction qui permet d'ecrire les resultat dans un fichier TSV
 */


void fichier_resultat(t_resultat resultat){

	/*cree le fichier a ecrire dedans puis on l'ouvre
	FILE *fichier_resultat = fopen("resultat.tsv","w");

	Regarde si le fichier est cree
	if(fichier_resultat == NULL){
	printf("Impossible de cree le fichier resultat");
	return;
	}

	 Pour chaque titre contenu dans la structure resultat on ecrit le contenue de la
	 structrure titre sur une ligne. Chaque champ de la structure titre
	 est separe par une tabulation.


	for(int i = 0; i < (resultat->nb_titre); i++){
		fprintf(fichier_resultat,"%s\t%s\t%d\t%s\t%s\t\n",
				 resultat->titre[i]->ID,
				 resultat->titre[i]->titre,
				 resultat->titre[i]->annee_parution_min,
				 resultat->titre[i]->categorie,
				 resultat->titre[i]->genre);
	}
	//On ferme le fichier une fois que les titre ont ete ajoutes
	fclose(fichier_resultat);//Lab3-HLR03 finie
	*/

	//Lab3 serveur-HLR02
	/*On affiche dans le terminal les resultats de la recherche
	 * au lieu de les ecrire dans un fichier txt
	 */
	for(int i = 0; i < (resultat->nb_titre); i++){
		printf("%s\t%s\t%d\t%s\t%s\t\n",
				 resultat->titre[i]->ID,
				 resultat->titre[i]->titre,
				 resultat->titre[i]->annee_parution_min,
				 resultat->titre[i]->categorie,
				 resultat->titre[i]->genre);
	}

	//Lab3 client-HLR02 finie

	//Creation du fichier cote pour inscrire les cotes des titre
	FILE *fichier_cote = fopen("cote.tsv","w");

	//Assure l'ouerture du fichier
	if(fichier_cote == NULL){
	printf("Impossible de cree le fichier cote");
	return;
	}

	//Imprime dans le fichier les champs de cote
	for(int i = 0; i < (resultat->nb_titre); ++i){
	if(resultat->titre[i]->nombre_votes > 0){

		fprintf(fichier_cote,"%s\t%s\t%d\n",
			resultat->titre[i]->ID,
			resultat->titre[i]->note_moyenne,
			resultat->titre[i]->nombre_votes
			);
		}
	}
	fclose(fichier_cote);
	//HLR 17 finie
}
//HLR09 finie

//lab3 serveur-HLR05
/*
 * Fonction servant a rajouter une evaluation au titre. Elle calcul un nouveau classement moyen
 * du titre passer en parametre a partir de la cote recu en parametre
 */
void calcul_moyenne(t_titre titre, char* nouvelle_cote){

	//On s'assure que la nouvelle cote se trouve entre 0 et 10
	if(0<=nouvelle_cote && nouvelle_cote >= 10){

		int nb_votes = titre->nombre_votes;//On stock le nombre de votes du titre
		double note_moyenne = atof(titre->note_moyenne);//On convertie le note moyenne de string en double et on stock la valeur
		double cote = atof(nouvelle_cote);//On convertie la valeur de nouvelle cote de char en double

		//On fait le calcul de la nouvelle moyenne
		double nouvelle_moyenne = note_moyenne+(cote-note_moyenne)/nb_votes;
		titre->note_moyenne = nouvelle_moyenne;//On stock la nouvelle moyenne
		titre->nombre_votes++;//On incremente le nombre de votes

	}
}
//serveur-HLR05 finie

// Destructeur
void detruire_titre(t_titre titre) {
	free(titre->ID);
	free(titre->categorie);
	free(titre->genre);
	free(titre->note_moyenne);
	free(titre->titre);
	free(titre);
}
void detruire_resultat(t_resultat resultat){
	free(resultat->titre);
	free(resultat);
}

// Mutateurs

//HLR 16
/*
 * Fonction qui permet d'ajouter les information
 * de cote de classement a la structure titre.
 */
void set_note_et_nombre_t(t_titre titre, char* note_moyenne, int nombre_votes) {
	titre->note_moyenne = note_moyenne;
	titre->nombre_votes = nombre_votes;
}
//HLR16 finie

//serveur-HLR04
void set_numero_ligne(t_titre titre, int numero_ligne){
	titre->numero_ligne = numero_ligne;
}

void set_ID_t(t_titre titre, char* ID) {
	titre->ID = ID;
}

void set_titre_t(t_titre titre, char* titre_str) {
	titre->titre = titre_str;
}

void set_genre_t(t_titre titre, char *genre) {
	titre->genre = genre;
}

void set_categorie_t(t_titre titre, char *categorie) {
	titre->categorie = categorie;
}

void set_annee_parution_min_t(t_titre titre, int annee) {
	titre->annee_parution_min = annee;
}

void copy_titre(t_titre titre, t_titre copyTitre){
	 // variable servant a copier le titre

	//Copie les champs de titre recu
	//On alloue une nouvelle addresse pour stocker le champ ID

		if(titre->ID != NULL){
			copyTitre->ID = (char*)calloc(strlen(titre->ID)+1,sizeof(char));
			assert(copyTitre->ID!=NULL);
			strcpy(copyTitre->ID,titre->ID);
		}
		if(titre->titre != NULL){
			copyTitre->titre = (char*)calloc(strlen(titre->titre)+1,sizeof(char));
			assert(copyTitre->titre!=NULL);
			strcpy(copyTitre->titre,titre->titre);
		}
	    copyTitre->annee_parution_min = titre->annee_parution_min;
		if(titre->categorie != NULL){
			copyTitre->categorie = (char*)calloc(strlen(titre->categorie)+1,sizeof(char));
			assert(copyTitre->categorie!=NULL);
			strcpy(copyTitre->categorie,titre->categorie);
		}
		if(titre->genre != NULL){
			copyTitre->genre = (char*)calloc(strlen(titre->genre)+1,sizeof(char));
			assert(copyTitre->genre!=NULL);
			strcpy(copyTitre->genre,titre->genre);
		}

}
// Observateurs
char* get_ID_t(t_titre titre) {
    return titre->ID;
}

char* get_titre_t(t_titre titre) {
    return titre->titre;
}

char* get_genre_t(t_titre titre) {
    return titre->genre;
}

char* get_categorie_t(t_titre titre) {
    return titre->categorie;
}

int get_annee_parution_min_t(t_titre titre) {
    return titre->annee_parution_min;
}

char* get_moyenne(t_titre titre){
	return titre->note_moyenne;
}

int get_vote(t_titre titre){
	return titre->nombre_votes;
}

t_titre get_titre_r(t_resultat resultat, int i){
	return resultat->titre[i];
}

int get_nb_titre(t_resultat resultat){
	return resultat->nb_titre;
}
//serveur-HLR04
int get_numero_ligne(t_titre titre){
	return titre->numero_ligne;
}

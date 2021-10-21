
/**
 * Module imdb- imdb.c
 *
 * Par : Ylann Blouzat et Thomas Giguere Sturrock
 * Date : Septembre 2021
 *
 */

/**
 * Module imdb- imdb.c
 *
 * Par : Ylann Blouzat et Thomas Giguere Sturrock
 * Date : Septembre 2021
 *
 */


#include "recherche.h"
#include "resultat.h"
#include "imdb.h"



//Lab2-HLR12
/*
 * Fonction qui permet de decomposer tous les champs d'une ligne du fichier title_basics.tsv.
 */

void decompose(char* ligne, t_titre titre){

	char *token= NULL;

    token = strsep(&ligne, "\t");//token est tconst
    set_ID_t(titre,token);
    token = strsep(&ligne, "\t");//token est titleType
    set_categorie_t(titre, token);
    token = strsep(&ligne, "\t");//token est primarytitle
    set_titre_t(titre, token);
    token = strsep(&ligne, "\t");//token est originaltitle
    token = strsep(&ligne, "\t");//token est isadult
    token = strsep(&ligne, "\t");//token est startYear;
    set_annee_parution_min_t(titre,atoi(token));
    token = strsep(&ligne, "\t");//token est endYear
    token = strsep(&ligne, "\t");//token est runtime
    token = strsep(&ligne, "\t\n");//token est genres
    set_genre_t(titre, token);

}
//HLR12 finie



//Lab2-HLR13
/*
 * Fonction qui permet de comparer un titre du fichier title_basics.tsv aux criteres de recherches.
 * S'ils concordent, l'entree est conservee dans les resultats
 */

int compare (t_critere critere, t_titre titre, t_resultat resultat){

	 char* titre_c = get_titre(critere);//stockage du titre recherche
	 char* genre_c = get_genre(critere);//stockage du genre recherche
	 char* categorie_c=get_categorie(critere);//stockage de la categorie recherche
	 int anne_parution_min_c = get_annee_parution_min(critere);//stockage de l'annee minimale recherche
	 int anne_parution_max_c = get_annee_parution_max(critere);//stockage de l'annee maximale recherche

	 //stock linformation du titre a comparer dans des string
	 char* titre_t = get_titre_t(titre); //stockage du titre de la base
	 char* genre_t = get_genre_t(titre); //stockage du genre de la base
	 char* categorie_t = get_categorie_t(titre); //stockage de la categorie de la base
	 int anne_parution_min_t = get_annee_parution_min_t(titre); //stockage de l'annee de parution de la base

	 //variable pour verifier l'occurance d'un mot dans un string
	 char* oc = NULL;
	 char* oc2 = NULL;

	 //char* spc = " ";




	 if(get_titre(critere) != NULL){
		 //strcat(titre_c," ");
		 oc = strstr(get_titre_t(titre) , get_titre(critere)); //recherche du mot dans le titre du film de la base
		 }

		 if(get_genre(critere) != NULL){
	     strcat(get_genre(critere)," ");
		 oc2 = strstr(get_genre_t(titre),get_genre(critere)); //recherche du mot dans le genre de la base
		 }

	if ((get_titre(critere) != NULL) && oc != NULL){// il faut un titre et que le critere corresponde pour avancer

	if ((get_genre(critere)==NULL) || oc2 != NULL){ //si pas de genre ou genre correspondant, on avance

			if ((get_categorie(critere)==NULL) || strcmp(get_categorie(critere),categorie_t)==0){//si pas de categorie ou categorie correspondant, on avance

					if ((get_annee_parution_min(critere)==-1) || (get_annee_parution_min(critere)<=get_annee_parution_min_t(titre) && get_annee_parution_min_t(titre)<=get_annee_parution_max(critere))){//si pas d'annee ou annee correspondant, on avance
/*
						//On alloue une nouvelle addresse pour stocker le champ titre
						char* ID = get_ID_t(titre);
						char* i = (char*)malloc(strlen(ID)*sizeof(char));
						if ( i == NULL){
							printf("Erreur d'allocation");
							return 0;
						}
						strcpy(i,ID);// on copy l'ID du film trouve
						set_ID_t(titre,i);// on ajoute l'ID du film trouve

						//On alloue une nouvelle addresse pour stocker le champ titre
						char* t = (char*)malloc(strlen(titre_t)*sizeof(char));
						if ( t == NULL){
							printf("Erreur d'allocation");
							return 0;
						}
						strcpy(t,titre_t); // on copy le titre du film trouve
						set_titre_t(titre,t);// on ajoute le titre du film trouve

						//On alloue une nouvelle addresse pour stocker le champ genre
						char* g = (char*)malloc(strlen(genre_t)*sizeof(char));
						if ( g == NULL){
							printf("Erreur d'allocation");
							return 0;
						}
						strcpy(g,genre_t); // on copy le genre du film trouve
						set_genre_t(titre,g);// on ajoute le genre du film trouve


						//On alloue une nouvelle addresse pour stocker le champ categorie
						char* c = (char*)malloc(strlen(categorie_t)*sizeof(char));
						if ( c == NULL){
							printf("Erreur d'allocation");
							return 0;
						}
						strcpy(c,categorie_t);// on copy la categorie du film trouve
						set_categorie_t(titre,c);// on ajoute la categorie du film trouve
*/
						copy_strings(titre);
						add_titre(resultat, titre);//tout match, on ajoute le titre au resultat
						return 1;
				}
			}
		}
	}
	return 1;
}
//HLR13 finie


//lab2-HLR20
/*
 * Fonction privee permettant de decomposer tous les champs d'une ligne du fichier title_ratings.tsv
 */
void decompose_cote(char* ligne, t_titre titre){

	/*
	 * Creation de 2 token afin de stocker les champs a comparer, plus specifiquement pour
	 * pouvoir ajouter la cote moyenne et le nombre de vote.
	 */
	char *token= NULL;
	char* token2 = NULL;

    token = strsep(&ligne, "\t");//token est tconst
    set_ID_t(titre,token);
    token = strsep(&ligne, "\t");//token est Average
    token2 = strsep(&ligne, "\t");//token est nombre de vote
    set_note_et_nombre_t(titre, token, atoi(token2));

}
//HLR 20 finie

//Lab2-HLR21
/*
 * Fonction privee qui compare l'identifiant unique de la cote  a ceux des titres retenus dans les resiultats.
 * Si la cote est celle d'un titre retenus. les donnees sont ajoutees a la structure titre qui lui corrrespondent.
 */
int compare_cote (t_resultat resultat,t_titre titre){

	int k = get_nb_titre(resultat);
	for(int i =0 ;i<k;i++){

		t_titre titre_res = get_titre_r(resultat,i);
		char* ID_res = get_ID_t(titre_res); // on stock l'ID du resultat
		char* ID_comp = get_ID_t(titre); // on stock l'ID du film de la base

		if (strcmp(ID_res,ID_comp)==0){ // si les deux ID correspondent on avance

			char* moy = get_moyenne(titre); //on recupere la moyenne du film de la base
			int p =get_vote(titre); // on recupere le nombre de vottes du film de la base

			if( strcmp(moy,"NULL")!=0 && p >0){ // si le film a une ;oyenne et qu'il y a des votants, on avance

			char* nm = (char*)malloc(strlen(get_moyenne(titre))*sizeof(char));
			if ( nm == NULL){
				printf("Erreur d'allocation");
				return 0;
			}

			else{
				strcpy(nm,get_moyenne(titre)); //on copie la moyenne
			}
			int vt = 0;
			if(get_vote(titre)== -1){
				vt = 0;
			}
			else{
				vt = get_vote(titre); //on copie le nombre de votes
			}
			set_note_et_nombre_t(titre_res, nm, vt);//on ajoute au resultat le nombre de votes et la moyenne
			}
		}
	}
	return 1;
}

//HLR21 finie

//Lab2-HLR10
/*
 * Une fonction publique qui recoit la liste de critere de recherche en parametre
 * et accede au contenu du fichier title_basics.tsv.
 */
t_resultat lecture(t_critere critere){

	t_resultat resultat = cree_resultat();
	t_titre titre = cree_titre();

	int taille_max = 1024;//taille arbitraire de la ligne de charactere a lire
	char* ligne = (char*)malloc(taille_max*sizeof(char));

	FILE *fichier;

	//HLR23
	/*
	 * Les nom de base de donnees sont title_basics.tsv et title_ratings.tsv
	 */
	fichier = fopen("data/title_basics.tsv", "r");
	//HLR23 finie


//HLR10 finie

//Lab2-HLR11
/*
 * L'exploration des donnees se fait ligne par ligne a la suite de l'ouverture du fichier en mode lecture
 */
	while (fgets(ligne, taille_max, fichier) != NULL){ //HLR 11 & 14

		//Lab2-HLR14
		/*La fonction decompose chaque ligne de titre et la compare avec les criteres de recherche
		 *puis ajoute un titre de la base de donnees aux resultats. Elle retourne un pointeur vers
		 *une structure de resultats remplie de titres repondant aux criteres de recherche.
		*/
		decompose(ligne,titre);
		compare(critere,titre,resultat);

	}

//HLR 11 finie
return resultat;
}
//HLR14 finie

//Lab2-HLR18
/*
 * Fonction qui recoit la liste de resultat et qui accede au fichier title_ratings.tsv
 */
void lecture_cote(t_resultat resultat){

int taille_max =1024;
t_titre titre = cree_titre();
char* ligne = (char*)malloc(taille_max*sizeof(char));

//HlR23
/*
 * Les nom de base de donnees sont title_basics.tsv et title_ratings.tsv
 */
FILE *fichier = fopen("data/title_ratings.tsv", "r");
//HLR 18 et 23 finie

//Lab2-HLR19
/*
 * L'exporation des donnees du fichier cote se fait ligne par ligne.
 */
while (fgets(ligne, taille_max, fichier) != NULL){
//HLR 19 finie

	//Lab2-HLR22
	/*
	 * Chaque ligne de cote lue est decomposee et comparer avec les resultat des titres puis l'information sur la cote de classement est ajouter aux titre correspondant.
	 */
		decompose_cote(ligne, titre);
		compare_cote(resultat,titre);
	//HLR22 finir
	}
}



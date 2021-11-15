
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

void decompose(char *ligne, t_titre titre) {

	char *token = NULL;

	token = strsep(&ligne, "\t"); //token est tconst
	set_ID_t(titre, token);
	token = strsep(&ligne, "\t"); //token est titleType
	set_categorie_t(titre, token);
	token = strsep(&ligne, "\t"); //token est primarytitle
	set_titre_t(titre, token);
	token = strsep(&ligne, "\t"); //token est originaltitle
	token = strsep(&ligne, "\t"); //token est isadult
	token = strsep(&ligne, "\t"); //token est startYear;
	set_annee_parution_min_t(titre, atoi(token));
	token = strsep(&ligne, "\t"); //token est endYear
	token = strsep(&ligne, "\t"); //token est runtime
	token = strsep(&ligne, "\t\n"); //token est genres
	set_genre_t(titre, token);

}
//HLR12 finie

//Lab2-HLR13
/*
 * Fonction qui permet de comparer un titre du fichier title_basics.tsv aux criteres de recherches.
 * S'ils concordent, l'entree est conservee dans les resultats
 */

int compare(t_critere critere, t_titre titre, t_resultat resultat) {

	//variable pour verifier l'occurance d'un mot dans un string
	char *oc = NULL;
	char *oc2 = NULL;

	if (get_titre(critere) != NULL) {
		oc = strstr(get_titre_t(titre), get_titre(critere)); //recherche du mot dans le titre du film de la base
	}

	if (get_genre(critere) != NULL) {
		//strcat(get_genre(critere), " ");
		oc2 = strstr(get_genre_t(titre), get_genre(critere)); //recherche du mot dans le genre de la base
	}

	if ((get_titre(critere) != NULL) && oc != NULL) { // il faut un titre et que le critere corresponde pour avancer

		if ((get_genre(critere) == NULL) || oc2 != NULL) { //si pas de genre ou genre correspondant, on avance

			if ((get_categorie(critere) == NULL)
					|| strcmp(get_categorie(critere), get_categorie_t(titre))
							== 0) { //si pas de categorie ou categorie correspondant, on avance

				if ((get_annee_parution_min(critere) == -1)
						|| (get_annee_parution_min(critere)
								<= get_annee_parution_min_t(titre)
								&& get_annee_parution_min_t(titre)
										<= get_annee_parution_max(critere))) { //si pas d'annee ou annee correspondant, on avance

					add_titre(resultat, titre); //tout match, on ajoute le titre au resultat
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
void decompose_cote(char *ligne, t_titre titre) {

	/*
	 * Creation de 2 token afin de stocker les champs a comparer, plus specifiquement pour
	 * pouvoir ajouter la cote moyenne et le nombre de vote.
	 */
	char *token = NULL;
	char *token2 = NULL;

	token = strsep(&ligne, "\t"); //token est tconst
	set_ID_t(titre, token);
	token = strsep(&ligne, "\t"); //token est Average
	token2 = strsep(&ligne, "\t"); //token est nombre de vote
	set_note_et_nombre_t(titre, token, atoi(token2));

}
//HLR 20 finie

//Lab2-HLR21
/*
 * Fonction privee qui compare l'identifiant unique de la cote  a ceux des titres retenus dans les resiultats.
 * Si la cote est celle d'un titre retenus. les donnees sont ajoutees a la structure titre qui lui corrrespondent.
 */
int compare_cote(t_resultat resultat, t_titre titre, int j) {

	for (int i = 0; i < get_nb_titre(resultat); i++) {

		t_titre titre_res = get_titre_r(resultat, i);

		if (strcmp(get_ID_t(titre_res), get_ID_t(titre)) == 0) { // si les deux ID correspondent on avance

			char *nm = (char*) calloc(strlen(get_moyenne(titre)) + 1,
					sizeof(char));
			if (nm == NULL) {
				printf("Erreur d'allocation");
				return 0;
			}
			strcpy(nm, get_moyenne(titre)); //copy la moyenne
			int vt = get_vote(titre); //on copie le nombre de votes

			//on ajoute au resultat le nombre de votes et la moyenne
			set_note_et_nombre_t(titre_res, nm, vt);

			//on ajoute le numero de ligne associer a la cote extraite
			set_numero_ligne(titre_res, j);
			//serveur-HLR04 finie

		}
		t_titre titre_comp = titre_res;
	}
	return 1;
}

//HLR21 finie

//Lab2-HLR10
/*
 * Une fonction publique qui recoit la liste de critere de recherche en parametre
 * et accede au contenu du fichier title_basics.tsv.
 */
t_resultat lecture(t_critere critere) {

	t_resultat resultat = cree_resultat();
	t_titre titre = cree_titre();

	int taille_max = 1024; //taille arbitraire de la ligne de charactere a lire
	char *ligne = (char*) malloc(taille_max * sizeof(char));

	FILE *fichier;

	//HLR23
	/*
	 * Les nom de base de donnees sont title_basics.tsv et title_ratings.tsv
	 */
	fichier = fopen("data/title_basics.tsv", "r");
	if(fichier==NULL){
		printf("Fichier not found");
	}
	//HLR23 finie

//HLR10 finie

//Lab2-HLR11
	/*
	 * L'exploration des donnees se fait ligne par ligne a la suite de l'ouverture du fichier en mode lecture
	 */
	while (fgets(ligne, taille_max, fichier) != NULL) { //HLR 11 & 14

		//Lab2-HLR14
		/*La fonction decompose chaque ligne de titre et la compare avec les criteres de recherche
		 *puis ajoute un titre de la base de donnees aux resultats. Elle retourne un pointeur vers
		 *une structure de resultats remplie de titres repondant aux criteres de recherche.
		 */
		decompose(ligne, titre);
		compare(critere, titre, resultat);

	}
	fclose(fichier);
	free(ligne);
	free(titre);
//HLR 11 finie
	return resultat;
}
//HLR14 finie

//Lab2-HLR18
/*
 * Fonction qui recoit la liste de resultat et qui accede au fichier title_ratings.tsv
 */
void lecture_cote(t_resultat resultat) {

	int taille_max = 1024;
	t_titre titre = cree_titre();
	char *ligne = (char*) malloc(taille_max * sizeof(char));

	//Lab3 serveur-HLR04
	int num_ligne = 1; //variable permettant de garder en compte le numero de ligne

	//lab2-HlR23
	/*
	 * Les nom de base de donnees sont title_basics.tsv et title_ratings.tsv
	 */
	FILE *fichier = fopen("data/title_ratings.tsv", "r");
	//HLR 18 et 23 finie

	//Lab2-HLR19
	/*
	 * L'exporation des donnees du fichier cote se fait ligne par ligne.
	 */
	while (fgets(ligne, taille_max, fichier) != NULL) {
		//HLR 19 finie

		//Lab2-HLR22
		/*Chaque ligne de cote lue est decomposee et comparer avec les resultat
		 *des titres puis l'information sur la cote de classement est ajouter aux titre correspondant.
		 */
		decompose_cote(ligne, titre);
		compare_cote(resultat, titre, num_ligne); //passe en parametre le numero de ligne a comparer
		//HLR22 finir

		//increment le numero de ligne lorsqu'on change de ligne
		num_ligne++;
	}
	free(ligne);
	free(titre);
	fclose(fichier);
}

//lab3 Serveur-HLR07
/*
 * Fonction  qui permet de mettre a jour la base de donnees de cotes
 * en copiant chaque ligne du fichier original a l'execption de la ligne
 * a laquelle on doit rajouter une cote.
 */
void fichier_cote(t_titre titre, float cote) {
	int taille_max = 1024;
	char *ligne = (char*) malloc(taille_max * sizeof(char));
	int num_ligne = 1;//variable permettant de garder en compte le numero de ligne


	 //Ouvre le fichier title_ratings.tsv
	FILE *fp = fopen("data/title_ratings.tsv", "r");
	FILE *fp2 = fopen("nouvelle_cote.tsv", "w");


	 //L'exporation des donnees du fichier cote se fait ligne par ligne.
	while (fgets(ligne, taille_max, fp) != NULL) {

		//lab3 Serveur-HLR10
		/*
		 * Si le titre ne contient pas de cote dans la base de donnee
		 * on rajoute la cote et le titre a la base de donnees/
		 */
		if (get_vote(titre) == -1) {

			///On calcul la moyenne puis on rajoute un cote au titre
			calcul_moyenne(titre, cote);

			//lab3 Serveur-HLR11
			/*
			 * Les modification apportees au fichier de base de donnes doivent respecter
			 * la structure utilisee par IMDb.
			 */
			//On inscrit la nouvelle cote dans le nouveau fichier cote
			fprintf(fp2, "%s\t%s\t%d\n",
					get_ID_t(titre),
					get_moyenne(titre),
					get_vote(titre));
			printf("[+] Nouvelles valeurs de cotes\n");
			printf("\t[+] Titre: %s\n\t[+] Cote: %s\n\t[+] Nombre de vote:%d\n",
					get_ID_t(titre),
					get_moyenne(titre),
					get_vote(titre));
		}
		//Serveur-HLR10 finie
		else if (get_numero_ligne(titre) != num_ligne) {
			/*
			 * On inscrit chacune des lignes de l'ancien fichier si le numero de ligne ne
			 * correspond pas a celui du titre que l'utilisateur souhaite evaluer
			 */
			fputs(ligne, fp2);
		} else {
			//lab3 Serveur-HLR08
			/*
			 * On ajoute la nouvelle cote de classement au nouveau fichier
			 */
			//calcul la nouvelle cote moyenne
			calcul_moyenne(titre, cote);

			//on inscrit la nouvelle cote dans le fichier cote
			//lab3 Serveur-HLR11


			fprintf(fp2, "%s\t%s\t%d\n",
					get_ID_t(titre),
					get_moyenne(titre),
					get_vote(titre));
			//Serveur-HLR08 finie
			//Serveur-HLR11 finie
			printf("[+] Nouvelles valeurs de cotes\n");
			printf("\t[+] Titre: %s\n\t[+] Cote: %s\n\t[+] Nombre de vote:%d\n",
					get_ID_t(titre),
					get_moyenne(titre),
					get_vote(titre));
		}
		//increment le numero de ligne lorsqu'on change de ligne
		num_ligne++;
	}

	fclose(fp);
	fclose(fp2);

	//lab3 Serveur-HLR09
	/*
	 * Suite a la mise a jour de la base de donnees on remplace l'ancien fichier
	 * de cotes de classement par le nouveau fichier cree.
	 */

	//rewind(fp2);//On retourne au debut du fichier
	fp = fopen("data/title_ratings.tsv", "w+");
	fp2 = fopen("nouvelle_cote.tsv", "r");

	/* On parcour le fichier copier de la base de donnees avec la nouvelle cote,
	 * puis inscit ses ligne dans l'ancien fichier afin de le remplacer.
	 */
	while (fgets(ligne, taille_max, fp2) != NULL) {
		fputs(ligne, fp);
	}
	//Serveur-HLR-09 finie

	fclose(fp);				//ferme le fichier copier
	fclose(fp2);		//ferme le fichier qui remplace l'ancien fichier de cote
	free(ligne);

}
//Serveur-HLR07 finie


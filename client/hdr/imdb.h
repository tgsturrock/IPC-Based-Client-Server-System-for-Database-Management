#include "resultat.h"
/**
 * Module imdb- imdb.h
 *
 * Par : Ylann Blouzat et Thomas Giguere Sturrock
 * Date : Septembre 2021
 *
 */
#ifndef IMDB_H
#define IMDB_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

t_resultat lecture(t_critere critere);
void lecture_cote(t_resultat resultat);


#endif

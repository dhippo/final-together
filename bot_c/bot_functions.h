#ifndef BOT_C_BOT_FUNCTIONS_H
#define BOT_C_BOT_FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <ctype.h>

// Fonction de rappel pour écrire les données reçues
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);

// Fonction pour exécuter une requête cURL avec une URL
void perform_curl_request(const char *url);

// Fonction pour trouver le titre d'une activité à partir de son type
const char *find_activity_title(const char *activity_type);

// Fonction pour trouver le type d'une activité à partir de son titre
const char *find_activity_type(const char *word);

// Fonction pour trouver le type d'une question à partir de son mot
const char *find_question_type(const char *word);

// Fonction pour transformer une chaîne de caractères en minuscules
void to_lowercase(char *str);

// Fonction pour extraire les mots-clés d'activité et de question de la chaîne d'entrée
void identify_activity_and_question(const char *input, const char **activity_type, const char **question_type);

// Fonction pour identifier une question de base
int identify_basic_question(const char *input);

// Fonction pour obtenir une réponse à une question de base
const char *get_basic_answer(int basic_question_index);

// Fonction pour traiter une question
void question_treatment(const char *input);


#endif //BOT_C_BOT_FUNCTIONS_H

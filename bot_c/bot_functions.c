#include "bot_functions.h"

// Fonction de rappel pour écrire les données reçues
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    printf("%.*s", (int)realsize, (char *)contents);
    return realsize;
}

// Fonction pour exécuter une requête cURL avec une URL et un nom d'activité (facultatif)
void perform_curl_request(const char *url) {
    CURL *curl;
    CURLcode res;



    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}
const char *find_activity_title(const char *activity_type) {
    static const char *activity_titles[][2] = {
            {"escapegame", "Escape Game"},
            {"evcaritatif", "Événement caritatif"},
            {"rallye", "Rallye découverte d'une ville/d'un quartier"},
            {"karaoke", "Karaoké"},
            {"realitevirtuelle", "Réalité Virtuelle"},
            {"creationartistique", "Création artistique (peinture, sculpture, etc)"},
            {"competitionsportive", "Compétition sportive"},
            {"apero", "Apéro/Cocktail"},
            {"atelierculinaire", "Atelier culinaire"},
            {"babyfoot", "Tournoi Babyfoot ou Ping pong"},
            {"jeuxdesociete", "Jeux de société"},
            {"randonnee", "Randonnée"},
            {"voyage", "Voyage/Weekend"},
    };

    size_t num_activity_titles = sizeof(activity_titles) / sizeof(activity_titles[0]);

    for (size_t i = 0; i < num_activity_titles; i++) {
        if (strcmp(activity_type, activity_titles[i][0]) == 0) {
            return activity_titles[i][1];
        }
    }
    return NULL;
}


const char *find_activity_type(const char *word) {
    static const char* activity_types[][8] = {
            {"escapegame", "game", "escape", "escapegame", "roomescape", "escepe", "escepegem", "escepe"},
            {"evcaritatif", "association", "associatif", "benevolat", "ong", "caritatif", "humanitaire", "solidarite"},
            {"rallye", "decouverteville", "ville", "exploration", "urbaine", "rallye", "guidé", "promenade"},
            {"karaoke", "karaoké", "chorégraphie", "chant", "karaoke", "théatre", "chanson", "théâtre"},
            {"realitevirtuelle", "vr", "réalité", "immersif", "simulation", "3d", "casque", "virtuelle"},
            {"creationartistique", "peinture", "sculpture", "dessin", "art", "illustration", "artistique", "photographie"},
            {"competitionsportive", "sport", "sportive", "tournoi", "championnat", "match", "competition", "compétition"},
            {"apero", "cocktail", "repas", "soiree", "amuse-gueule", "apero", "apéro", "convivial"},
            {"atelierculinaire", "cuisine", "repas", "gastronomie", "recette", "cours", "dégustation", "ingredient"},
            {"babyfoot", "pong", "pingpong", "babyfoot", "billard", "jeuxdetable", "flechettes", "ping"},
            {"jeuxdesociete", "monopoly", "cartes", "plateau", "stratégie", "societe", "société", "puzzle"},
            {"randonnee", "rando", "randonné", "randonnee", "randonnée", "marche", "paysage", "sentier"},
            {"voyage", "week-end", "vacances", "excursion", "voyage", "aventure", "destination", "exploration"},
    };

    size_t num_activity_types = sizeof(activity_types) / sizeof(activity_types[0]);

    for (size_t i = 0; i < num_activity_types; i++) {
        for (size_t j = 1; j < 8; j++) {
            if (strcmp(word, activity_types[i][j]) == 0) {
                return activity_types[i][0];
            }
        }
    }
    return NULL;
}

// Fonction pour trouver le type de question en fonction d'un mot
const char *find_question_type(const char *word) {
    static const char* question_types[][6] = {
            {"duration", "date", "duree", "quand", "duree", "dure"},
            {"price", "cout", "coute", "prix", "chère", "coûte"},
            {"description", "description", "desc", "expliquer", "explique", "déroule"},
            {"types", "type", "catégorie", "categorie", "genre", "catégories"},
            {"why", "pourquoi", "raison", "avantage", "utilité", "sert"},
    };

    size_t num_question_types = sizeof(question_types) / sizeof(question_types[0]);

    for (size_t i = 0; i < num_question_types; i++) {
        for (size_t j = 1; j < 6; j++) {
            if (strcmp(word, question_types[i][j]) == 0) {
                return question_types[i][0];
            }
        }
    }
    return NULL;
}

void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Fonction pour extraire les mots-clés d'activité et de question de la chaîne d'entrée
void identify_activity_and_question(const char *input, const char **activity_type, const char **question_type) {
    // Copie de la chaîne d'entrée dans le tampon et vérif qu'elle se termine par un caractère nul
    char input_buffer[256];
    strncpy(input_buffer, input, sizeof(input_buffer) - 1);
    input_buffer[sizeof(input_buffer) - 1] = '\0';

    // minsusculisation de la chaîne d'entrée
    to_lowercase(input_buffer);

    /** SEPARATION DE CHAQUE MOT DE LA CHAINE DE CARACTERES **/
    // Analyse des mots de la chaîne d'entrée en les séparant par des espaces
    char *word = strtok(input_buffer, " ");

    // Variables temporaires pour stocker les types d'activité et de question
    const char *temp_activity_type = NULL;
    const char *temp_question_type = NULL;

    // Analyse des mots jusqu'à ce qu'il n'y en ait plus
    while (word != NULL) {
        temp_activity_type = find_activity_type(word);
        if (temp_activity_type) {
            *activity_type = temp_activity_type;
        }

        temp_question_type = find_question_type(word);
        if (temp_question_type) {
            *question_type = temp_question_type;
        }

        word = strtok(NULL, " ");
    }
}

int identify_basic_question(const char *input) {
    char input_lower[256];
    strncpy(input_lower, input, sizeof(input_lower) - 1);
    input_lower[sizeof(input_lower) - 1] = '\0';
    to_lowercase(input_lower);

    static const char* basic_questions[][3] = {
            {"comment ça va ?",                  "comment ca va ?",                  "ça va ?"},
            {"comment t'appelles-tu ?",          "quel est ton nom ?",               "comment tu t'appelles"},
            {"qui est tu ?",                     "qui est ton créateur ?",           "pour qui travailles tu ?"},
            {"où habites-tu ?",                  "t'habites où",                     "où tu habites"},
            {"quel âge as-tu ?",                 "quel age as tu ?",                 "tu as quel âge ?"},
            {"quel est ton sport préféré ?",     "quel est le meilleur sport ?",     "tu aimes le sport ?"},
            {"quel est ton film préféré ?",      "tu connais un film ?",      "tu aimes quel film ?"},
            {"quel est ton jeu vidéo préféré ?", "quel est ton jeu vidéo préféré ?", "tu aimes quel jeu vidéo ?"},
            {"quel est ton livre préféré ?",     "quel est ton livre préféré ?",     "tu aimes quel livre ?"},
            {"quel est ton animal préféré ?",    "quel est ton animal préféré ?",    "tu aimes quel animal ?"},
            {"bonjour",    "bjr",    "bonjour"},
    };

    size_t num_basic_questions = sizeof(basic_questions) / sizeof(basic_questions[0]);

    for (size_t i = 0; i < num_basic_questions; i++) {
        for (size_t j = 0; j < 3; j++) {
            if (strcmp(input_lower, basic_questions[i][j]) == 0) {
                return i;
            }
        }
    }
    return -1;
}

const char *get_basic_answer(int basic_question_index) {
    static const char* basic_answers[][3] = {
            {"Je vais très bien",                             "C'est gentil ça va merci de me demander",                          "En ce moment, ça va super"},
            {"Je suis TogetherBot",                           "Je m'appelle TogetherBot",                      "TogetherBot, c'est moi !"},
            {"Je suis un bot créé par Together",              "Un programme informatique créé pour répondre à vos questions",              "Un bot entraîné sur un domaine spécifique"},
            {"Je suis dans le cloud",                         "Je n'habites pas vraiment quelque part",        "Je ne fais pas partie du monde physique"},
            {"Je suis un bot, je n'ai pas d'âge",             "Je suis un bot, et malheureusement je n'ai pas d'âge",             "Je suis un bot, je ne soufflerai jamais de bougie"},
            {"Mon sport préféré est le tennis",               "Mon sport préféré est le tennis",               "Mon sport préféré est le tennis"},
            {"Mon film préféré est Very Bad Trip",             "Very Bad Trip, je rêve d'être un humain",             "Mon film préféré est Very Bad Trip"},
            {"Mon jeu vidéo préféré est The Witcher 3",       "Mon jeu vidéo préféré est The Witcher 3",       "Mon jeu vidéo préféré est The Witcher 3"},
            {"Mon livre préféré est Le Seigneur des Anneaux", "Mon livre préféré est Le Seigneur des Anneaux", "Mon livre préféré est Le Seigneur des Anneaux"},
            {"Mon animal préféré est le chat",                "Mon animal préféré est le chat",                "Mon animal préféré est le chat"},
            {"salut, vous avez des questions sur les activités du Team Building",                "Bonjour avez-vous une question ?",                "Coucou, vous avez des questions sur les activités ?"}
    };


    // On choisit une réponse aléatoire parmi les réponses associées
    int answer_index = rand() % 3;

    return basic_answers[basic_question_index][answer_index];
}



// Fonction pour traiter la question utilisateur et exécuter les requêtes cURL pour chaque mot de la phrase
void question_treatment(const char *input) {
    // Transformer la chaîne reçue en minuscule
    char input_lower[256];
    strncpy(input_lower, input, sizeof(input_lower) - 1);
    input_lower[sizeof(input_lower) - 1] = '\0';
    to_lowercase(input_lower);

    // Vérification pour savoir si la question est une question de base
    int basic_question_index = identify_basic_question(input_lower);

    if (basic_question_index != -1) {
        const char *answer = get_basic_answer(basic_question_index);
        printf("%s\n", answer);
    } else {
        // On tente ici d'identifier le type d'activité et le type de question
        const char *activity_type = NULL;
        const char *question_type = NULL;
        identify_activity_and_question(input_lower, &activity_type, &question_type);

        // Si on a trouvé les deux, on peut faire une requête cURL avec les deux paramètres et retourner une réponse précise écrite en bdd
        if (activity_type && question_type) {
            char url[1024];
            snprintf(url, sizeof(url), "http://localhost:8888/api-together/index.php?action=specificInfo&activity_type=%s&question_type=%s", activity_type, question_type);
            perform_curl_request(url);
        } else if (activity_type) {
            const char *activity_title = find_activity_title(activity_type);
            printf("Vous cherchez des infos sur l'activité: %s ? ", activity_title);
            printf("_______________________________________");
            printf(" J'ai des infos sur: la durée de l'activité, le prix par personne, les types et les avantages");
        } else if (question_type) {
            printf("De quelles activités voulez-vous connaître l'information suivante: %s ? ", question_type);
        } else {
            printf("Je ne comprends pas la question\n");
        }
    }
}

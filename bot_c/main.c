#include "bot_functions.h"
#include <time.h> // Pour utiliser time()

#define API_BASE_URL "http://localhost:8888/api-together2"
// api serveur: https://togetherandstronger.website/api-together

/**
   POUR COMPILER :  gcc -o nom_executable main.c bot_functions.c -lcurl
*/

int main(int argc, char *argv[]) {

    srand(time(NULL)); // ça fait fonctionner la fonction rand() sinon elle retourne toujours la même valeur
    // voir guide/srand.txt pour plus d'informations

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <question>\n", argv[0]);
        return 1;
    }

    char *question = argv[1];

    question_treatment(question, API_BASE_URL);

    return 0;
}
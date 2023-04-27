#include "bot_functions.h"
#include <time.h> // Ajoutez cette ligne pour utiliser time()

/**
   POUR COMPILER :  gcc -o nom_executable main.c bot_functions.c -lcurl
   vérifier dans bot_functions.c question_treatment() le lien du curl de l'api commence bien par : https://togetherandstronger.website/api-together/
   snprintf(url, sizeof(url), "https://togetherandstronger.website/api-together/index.php?action=specificInfo&activity_type=%s&question_type=%s", activity_type, question_type);
*/

int main(int argc, char *argv[]) {
    srand(time(NULL)); // ça fait fonctionner la fonction rand() sinon elle retourne toujours la même valeur
    // voir guide/srand.txt pour plus d'informations

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <question>\n", argv[0]);
        return 1;
    }

    char *question = argv[1];

    question_treatment(question);

    return 0;
}
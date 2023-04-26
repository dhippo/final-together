#include "bot_functions.h"
#include <time.h> // Ajoutez cette ligne pour utiliser time()


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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <conio.h>

#define MAX_ESPECES 10 // Nombre maximale d'espèces par graphe
// (on met arbitrairement 10 car notre graphe le plus grand possède 10 espèces/sommets)

// Structure définissant une espèce
typedef struct {
    double N_t;      // Population à l'intant t
    double r;        // Rythme de croissance
    double K;        // Capacité de de portage de l'environnement
} Espece;
// Nous avons choisi d'utiliser "double" au lieu de "float" car "double"
// utilise 64bits (8 octets) et est plus adapté dans les calculs mathématiques
// avec de grandes plages de valeurs

void affichage_menu();
void etude_fonctionnelle_graphe_1();
void etude_fonctionnelle_graphe_2();
void etude_fonctionnelle_graphe_3();
// void etude_structurelle_graphe_1();
// void etude_structurelle_graphe_2();
// void etude_structurelle_graphe_3();

#include "Header.h"

// Fonction permettant de lire la matrice adjacente au(x) graphe(s)
void lire_graphe(const char *nomFichier, char ponderation[MAX_ESPECES][MAX_ESPECES], char noms[MAX_ESPECES][20], int *nombre_dEspeces) {
    FILE *fichier = fopen(nomFichier, "r");

    fscanf(fichier, "%d", nombre_dEspeces);   // Lecture du nombre d'espèces

    for (int i=0; i<*nombre_dEspeces; i++) {  // Lecture des noms des espèces
        fscanf(fichier, "%s", noms[i]);
    }
    for (int i=0; i<*nombre_dEspeces; i++) {  // Parcours de la matrice adjacente
        for (int j=0; j<*nombre_dEspeces; j++) {
            fscanf(fichier, "%s", &ponderation[i][j]); /////
        }
    }
    fclose(fichier);    // fermeture du fichier après l'avoir parcouru
}

// Fonction permettant de calculer la population (selon le modèle logistique de dynamique de population)
double calcul_de_population(double N_t, double r, double K) { // voir "Header.h" pour comprendre le choi d'un "double" au lieu d'un "float"
    return N_t + r * N_t * (1 - N_t / K);   // équation du modèle logistique de dynamique de population
}

// Fonction permettant de gérer les contributions des prédécesseurs
void gestion_ponderation(Espece especes[], char ponderation[MAX_ESPECES][MAX_ESPECES], int nombre_dEspeces) {
    for (int i=0; i<nombre_dEspeces; i++) {
        for (int j=0; j<nombre_dEspeces; j++) {
            if (ponderation[j][i]>0) {
                especes[i].N_t -= ponderation[j][i] * especes[j].N_t / especes[i].K;   // application des pondérations de la matrice (vulgairement : "qui mange qui")
                if (especes[i].N_t<0) especes[i].N_t = 0; // Blindage de la fonction pour empêcher la population d'être négative (c'est impossible)
            }
        }
    }
}

// Affichage du menu principal (cf. main.c)
void affichage_menu() {
    printf("\n\n\n\n\n\n");
    printf("\t\t     /$$$$$$$$                            /$$       /$$                 /$$   /$$             /$$                                     / $$\n");
    printf("\t\t    |__  $$__/                           | $$      |__/                | $$$ | $$            | $$                                     | $$\n");
    printf("\t\t       | $$  /$$$$$$   /$$$$$$   /$$$$$$ | $$$$$$$  /$$  /$$$$$$$      | $$$$| $$  /$$$$$$  /$$$$$$   /$$  /$$  /$$  /$$$$$$  /$$$$$$ | $$   /$$\n");
    printf("\t\t       | $$ /$$__  $$ /$$__  $$ /$$__  $$| $$__  $$| $$ /$$_____/      | $$ $$ $$ /$$__  $$|_  $$_/  | $$ | $$ | $$ /$$__  $$/$$__  $$| $$  /$$/\n");
    printf("\t\t       | $$| $$  \\__/| $$  \\ $$| $$  \\ $$| $$  \\ $$| $$| $$            | $$  $$$$| $$$$$$$$  | $$    | $$ | $$ | $$| $$  \\ $$| $$ \\__/| $$$$$$/\n");
    printf("\t\t       | $$| $$      | $$  | $$| $$  | $$| $$  | $$| $$| $$            | $$\\ $$$| $$_____/   | $$ /$$| $$ | $$ | $$| $$  | $$| $$     | $$_  $$\n");
    printf("\t\t       | $$| $$      |  $$$$$$/| $$$$$$$/| $$  | $$| $$|  $$$$$$$      | $$ \\ $$|  $$$$$$$   | $$$$/ |  $$$$$/$$$$/|  $$$$$$/| $$     | $$ \\ $$\n");
    printf("\t\t       |__/|__/       \\______/ | $$____/ |__/  |__/|__/ \\______/       |__/  \\_/ \\______/     \\___/   \\____/\\____/  \\______/ |__/     |__/  \\__/\n");
    printf("\t\t                               | $$\n");
    printf("\t\t                               | $$\n");
    printf("\t\t                               |__/\n");

    printf("\n\t\t\t\t\t\t\t\t\t       Menu Principal\n");
    printf("\n\t\t\t\t\t\t\t\t\t    1. Graphe numero 1\n");
    printf("\n\t\t\t\t\t\t\t\t\t    2. Graphe numero 2\n");
    printf("\n\t\t\t\t\t\t\t\t\t    3. Graphe numero 3\n");
    printf("\n\t\t\t\t\t\t\t\t\t\t4. Quitter\n");
    printf("\n\t\t\t\t\t\t\t\t\t\tVotre choix : ");
}

// Fonction pour l'étude des aspects fonctionnels du graphe 1
void etude_fonctionnelle_graphe_1() {
    int nombre_dEspeces;
    char ponderation[MAX_ESPECES][MAX_ESPECES];
    char noms[MAX_ESPECES][20];
    char nomFichier[100] = "graphe1.txt"; // Nom du fichier stockant la matrice adjacente correspondant au graphe (cf. fonction "lire_graphe")

    lire_graphe(nomFichier, ponderation, noms, &nombre_dEspeces);    // Appel de la fonction "lire_graphe" pour récupérer les informations de la matrice adjacente
    Espece especes[nombre_dEspeces];

    for (int i = 0; i < nombre_dEspeces; i++) { // Menu pemettant de faire varier les paramètres de l'étude
        system("cls");
        printf("\n\nSaisissez les parametres pour l'espece %s :", noms[i]);
        printf("\n\nPopulation initiale (N): ");
        scanf("%lf", &especes[i].N_t);
        printf("Taux de croissance (r): ");
        scanf("%lf", &especes[i].r);
        printf("Capacite de charge (K): ");
        scanf("%lf", &especes[i].K);
        system("cls");
    }

    int iterations = 21; // Limite le nombre d'itérations à 20
    printf("\nEtape\t");
    for (int i = 0; i < nombre_dEspeces; i++) {
        printf("%s ", noms[i]); // Affichage du nom des espèces
    }
    printf("\n");

    for (int t = 0; t < iterations; t++) {
        printf("%d", t);
        for (int i = 0; i < nombre_dEspeces; i++) {
            printf("\t%.2f", especes[i].N_t);
        }
        printf("\n");

        // Mise à jour des populations à chaque itération, suivant le modèle logistique de population
        for (int i = 0; i < nombre_dEspeces; i++) {
            especes[i].N_t = calcul_de_population(especes[i].N_t, especes[i].r, especes[i].K);
            if (especes[i].N_t < 0) especes[i].N_t = 0;
        }
        // Appel de la gestion des ponderation entre les espèces
        gestion_ponderation(especes, ponderation, nombre_dEspeces);
    }
    printf("\n\nAppuyez sur une touche pour revenir au menu secondaire\n");
    getch(); // Attente de l'appui sur une touche par l'utilisateur
    system("cls");
}

// Fonction pour l'étude des aspects fonctionnels du graphe 2
void etude_fonctionnelle_graphe_2() {
    int nombre_dEspeces;
    char ponderation[MAX_ESPECES][MAX_ESPECES];
    char noms[MAX_ESPECES][20];
    char nomFichier[100] = "graphe2.txt"; // Nom du fichier stockant la matrice adjacente correspondant au graphe (cf. fonction "lire_graphe")

    lire_graphe(nomFichier, ponderation, noms, &nombre_dEspeces);    // Appel de la fonction "lire_graphe" pour récupérer les informations de la matrice adjacente
    Espece especes[nombre_dEspeces];

    for (int i = 0; i < nombre_dEspeces; i++) { // Menu pemettant de faire varier les paramètres de l'étude
        system("cls");
        printf("\n\nSaisissez les parametres pour l'espece %s :", noms[i]);
        printf("\n\nPopulation initiale (N): ");
        scanf("%lf", &especes[i].N_t);
        printf("Taux de croissance (r): ");
        scanf("%lf", &especes[i].r);
        printf("Capacite de charge (K): ");
        scanf("%lf", &especes[i].K);
        system("cls");
    }

    int iterations = 21; // Limite le nombre d'itérations à 20
    printf("\nEtape\t");
    for (int i = 0; i < nombre_dEspeces; i++) {
        printf("%s ", noms[i]); // Affichage du nom des espèces
    }
    printf("\n");

    for (int t = 0; t < iterations; t++) {
        printf("%d", t);
        for (int i = 0; i < nombre_dEspeces; i++) {
            printf("\t%.2f", especes[i].N_t);
        }
        printf("\n");

        // Mise à jour des populations à chaque itération, suivant le modèle logistique de population
        for (int i = 0; i < nombre_dEspeces; i++) {
            especes[i].N_t = calcul_de_population(especes[i].N_t, especes[i].r, especes[i].K);
            if (especes[i].N_t < 0) especes[i].N_t = 0;
        }
        // Appel de la gestion des ponderation entre les espèces
        gestion_ponderation(especes, ponderation, nombre_dEspeces);
    }
    printf("\n\nAppuyez sur une touche pour revenir au menu secondaire\n");
    getch(); // Attente de l'appui sur une touche par l'utilisateur
    system("cls");
}

// Fonction pour l'étude des aspects fonctionnels du graphe 3
void etude_fonctionnelle_graphe_3() {
    int nombre_dEspeces;
    char ponderation[MAX_ESPECES][MAX_ESPECES];
    char noms[MAX_ESPECES][20];
    char nomFichier[100] = "graphe3.txt"; // Nom du fichier stockant la matrice adjacente correspondant au graphe (cf. fonction "lire_graphe")

    lire_graphe(nomFichier, ponderation, noms, &nombre_dEspeces);    // Appel de la fonction "lire_graphe" pour récupérer les informations de la matrice adjacente
    Espece especes[nombre_dEspeces];

    for (int i = 0; i < nombre_dEspeces; i++) { // Menu pemettant de faire varier les paramètres de l'étude
        system("cls");
        printf("\n\nSaisissez les parametres pour l'espece %s :", noms[i]);
        printf("\n\nPopulation initiale (N): ");
        scanf("%lf", &especes[i].N_t);
        printf("Taux de croissance (r): ");
        scanf("%lf", &especes[i].r);
        printf("Capacite de charge (K): ");
        scanf("%lf", &especes[i].K);
        system("cls");
    }

    int iterations = 21; // Limite le nombre d'itérations à 20
    printf("\nEtape\t");
    for (int i = 0; i < nombre_dEspeces; i++) {
        printf("%s ", noms[i]); // Affichage du nom des espèces
    }
    printf("\n");

    for (int t = 0; t < iterations; t++) {
        printf("%d", t);
        for (int i = 0; i < nombre_dEspeces; i++) {
            printf("\t%.2f", especes[i].N_t);
        }
        printf("\n");

        // Mise à jour des populations à chaque itération, suivant le modèle logistique de population
        for (int i = 0; i < nombre_dEspeces; i++) {
            especes[i].N_t = calcul_de_population(especes[i].N_t, especes[i].r, especes[i].K);
            if (especes[i].N_t < 0) especes[i].N_t = 0;
        }
        // Appel de la gestion des ponderation entre les espèces
        gestion_ponderation(especes, ponderation, nombre_dEspeces);
    }
    printf("\n\nAppuyez sur une touche pour revenir au menu secondaire\n");
    getch(); // Attente de l'appui sur une touche par l'utilisateur
    system("cls");
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Carte {
    int nrPagini;
    int* capitole;
    char* denumire;
    float pret;
    int nrCapitole;
};

struct Nod {
    struct Carte carte;
    struct Nod* urmator;
};

struct Carte initializare(int nrPagini, const int* capitole, const char* denumire, float pret, int nrCapitole) {
    struct Carte c;
    c.nrPagini = nrPagini;
    c.nrCapitole = nrCapitole;
    c.capitole = (int*)malloc(sizeof(int) * nrCapitole);
    for (int i = 0; i < nrCapitole; i++) {
        c.capitole[i] = capitole[i];
    }
    c.denumire = (char*)malloc(strlen(denumire) + 1);
    strcpy_s(c.denumire, strlen(denumire) + 1, denumire);
    c.pret = pret;
    return c;
}

void inserareSfarsit(struct Nod** cap, struct Carte c) {
    struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
    nou->carte = c;
    nou->urmator = NULL;

    if (*cap == NULL) {
        *cap = nou;
    }
    else {
        struct Nod* aux = *cap;
        while (aux->urmator != NULL) {
            aux = aux->urmator;
        }

        aux->urmator = nou;
    }
}

void afisareLista(struct Nod* cap) {
    while (cap) {
        printf("Carte: %s, %d pagini, %d capitole, pret: %.2f\n",
            cap->carte.denumire, cap->carte.nrPagini, cap->carte.nrCapitole, cap->carte.pret);
        printf("Capitole:");
        for (int i = 0; i < cap->carte.nrCapitole; i++) {
            printf(" %d", cap->carte.capitole[i]);
        }
        printf("\n\n");
        cap = cap->urmator;
    }
}

void dezalocareCarte(struct Carte* c) {
    free(c->capitole);
    free(c->denumire);
    c->capitole = NULL;
    c->denumire = NULL;
}

void dezalocareLista(struct Nod** cap) {
    while (*cap) {
        struct Nod* temp = *cap;
        *cap = (*cap)->urmator;
        dezalocareCarte(&temp->carte);
        free(temp);
    }
}

void stergeDupaDenumire(struct Nod** cap, const char* denumire) {
    struct Nod* aux = *cap;
    struct Nod* anterior = NULL;

    while (aux != NULL && strcmp(aux->carte.denumire, denumire) != 0) {
        anterior = aux;
        aux = aux->urmator;
    }

    if (aux == NULL) {
        printf("Cartea cu denumirea '%s' nu a fost gasita.\n", denumire);
        return;
    }

    if (anterior == NULL) {
        *cap = aux->urmator;
    }
    else {
        anterior->urmator = aux->urmator;
    }

    dezalocareCarte(&aux->carte);
    free(aux);
    printf("Cartea '%s' a fost stearsa cu succes.\n", denumire);
}

int main() {
    struct Nod* lista = NULL;

    int capitole1[] = { 1, 2, 3 };
    int capitole2[] = { 4, 5, 6, 7 };

    struct Carte basme = initializare(150, capitole1, "Basme", 45.0f, 3);
    struct Carte moaraCuNoroc = initializare(250, capitole2, "Moara cu Noroc", 60.0f, 4);

    inserareSfarsit(&lista, basme);
    inserareSfarsit(&lista, moaraCuNoroc);

    afisareLista(lista);

    stergeDupaDenumire(&lista, "Basme");
    afisareLista(lista);

    dezalocareLista(&lista);

    return 0;
}

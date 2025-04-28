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

void inserareMijloc(struct Nod** cap, struct Carte c, int pozitie) {
    if (pozitie < 0) {
        printf("Pozitia trebuie sa fie mai mare sau egala cu 0.\n");
        return;
    }

    struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
    nou->carte = c;

    if (pozitie == 0) {
        nou->urmator = *cap;
        *cap = nou;
        return;
    }

    struct Nod* temp = *cap;
    for (int i = 0; i < pozitie - 1 && temp != NULL; i++) {
        temp = temp->urmator;
    }

    if (temp == NULL) {
        printf("Lista nu are atatea elemente. Se va adauga la sfarsit.\n");
        inserareSfarsit(cap, c);
    }
    else {
        nou->urmator = temp->urmator;
        temp->urmator = nou;
    }
}

void inserareInceput(struct Nod** cap, struct Carte c) {
    struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
    if (nou == NULL) {
        printf("Eroare la alocarea memoriei!\n");
        return;
    }
    nou->carte = c;
    nou->urmator = *cap;
    *cap = nou;
}

int main() {
    struct Nod* lista = NULL;

    int capitole1[] = { 1, 2, 3 };
    int capitole2[] = { 4, 5, 6, 7 };
    int capitole3[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int capitole4[] = { 1, 2, 3, 4, 5, 6 };

    struct Carte basme = initializare(150, capitole1, "Basme", 45.0f, 3);
    struct Carte moaraCuNoroc = initializare(250, capitole2, "Moara cu Noroc", 60.0f, 4);
    struct Carte enciclopediaIstorica = initializare(300, capitole3, "Enciclopedie Istorica", 75.0f, 10);
    struct Carte alchimistul = initializare(300, capitole4, "Alchimistul", 75.0f, 6);

    inserareSfarsit(&lista, basme);
    inserareSfarsit(&lista, moaraCuNoroc);

    afisareLista(lista);

    inserareMijloc(&lista, enciclopediaIstorica, 1);
    afisareLista(lista);

    stergeDupaDenumire(&lista, "Basme");
    afisareLista(lista);

    inserareInceput(&lista, alchimistul);
    afisareLista(lista);

    dezalocareLista(&lista);

    return 0;
}

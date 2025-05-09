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
    struct Nod* precedent;
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
    nou->precedent = NULL;

    if (*cap == NULL) {
        *cap = nou;
    }
    else {
        struct Nod* aux = *cap;
        while (aux->urmator != NULL) {
            aux = aux->urmator;
        }
        aux->urmator = nou;
        nou->precedent = aux;
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

    while (aux && strcmp(aux->carte.denumire, denumire) != 0) {
        aux = aux->urmator;
    }

    if (aux == NULL) {
        printf("Cartea cu denumirea '%s' nu a fost gasita.\n", denumire);
        return;
    }

    if (aux->precedent) {
        aux->precedent->urmator = aux->urmator;
    }
    else {
        *cap = aux->urmator;
    }

    if (aux->urmator) {
        aux->urmator->precedent = aux->precedent;
    }

    dezalocareCarte(&aux->carte);
    free(aux);
    printf("Cartea '%s' a fost stearsa cu succes.\n", denumire);
}

void inserareInceput(struct Nod** cap, struct Carte c) {
    struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
    nou->carte = c;
    nou->urmator = *cap;
    nou->precedent = NULL;

    if (*cap) {
        (*cap)->precedent = nou;
    }
    *cap = nou;
}

void inserareMijloc(struct Nod** cap, struct Carte c, int pozitie) {
    if (pozitie <= 0 || *cap == NULL) {
        inserareInceput(cap, c);
        return;
    }

    struct Nod* temp = *cap;
    for (int i = 0; i < pozitie && temp->urmator != NULL; i++) {
        temp = temp->urmator;
    }

    struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
    nou->carte = c;
    nou->urmator = temp;
    nou->precedent = temp->precedent;

    if (temp->precedent) {
        temp->precedent->urmator = nou;
    }
    else {
        *cap = nou;
    }
    temp->precedent = nou;
}

struct Carte extragereDupaDenumire(struct Nod** cap, const char* denumire) {
    struct Nod* aux = *cap;

    while (aux && strcmp(aux->carte.denumire, denumire) != 0) {
        aux = aux->urmator;
    }

    if (!aux) {
        printf("Cartea cu denumirea '%s' nu a fost gasita.\n", denumire);
        struct Carte c = { 0, NULL, NULL, 0.0f, 0 };
        return c;
    }

    if (aux->precedent) {
        aux->precedent->urmator = aux->urmator;
    }
    else {
        *cap = aux->urmator;
    }

    if (aux->urmator) {
        aux->urmator->precedent = aux->precedent;
    }

    struct Carte rezultat = aux->carte;
    free(aux);
    printf("Cartea '%s' a fost extrasa din lista.\n", rezultat.denumire);
    return rezultat;
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

    struct Carte carteExtrasa = extragereDupaDenumire(&lista, "Moara cu Noroc");
    if (carteExtrasa.denumire != NULL) {
        printf("Carte extrasa: %s, pret: %.2f\n", carteExtrasa.denumire, carteExtrasa.pret);
        // Dezalocam pentru ca nu mai exista in lista si trebuie dezalocata manual
        dezalocareCarte(&carteExtrasa);
    }
    
    // Verificam ca elementul a fost extras si nu mai exista in lista
    afisareLista(lista);

    dezalocareLista(&lista);

    return 0;
}

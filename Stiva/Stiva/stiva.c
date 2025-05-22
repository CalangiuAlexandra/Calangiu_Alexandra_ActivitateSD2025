#define _CRT_SECURE_NO_WARNINGS
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

struct NodStiva {
    struct Carte carte;
    struct NodStiva* next;
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

void push(struct NodStiva** varf, struct Carte c) {
    struct NodStiva* nou = (struct NodStiva*)malloc(sizeof(struct NodStiva));
    nou->carte = c;
    nou->next = *varf;
    *varf = nou;
}

struct Carte pop(struct NodStiva** varf) {
    if (*varf == NULL) {
        printf("Stiva este goala.\n");
        struct Carte c = { 0, NULL, NULL, 0.0f, 0 };
        return c;
    }
    struct NodStiva* temp = *varf;
    struct Carte c = temp->carte;
    *varf = temp->next;
    free(temp);
    return c;
}

void afisareStiva(struct NodStiva* varf) {
    while (varf) {
        printf("Carte: %s, %d pagini, %d capitole, pret: %.2f\n",
            varf->carte.denumire, varf->carte.nrPagini, varf->carte.nrCapitole, varf->carte.pret);
        printf("Capitole:");
        for (int i = 0; i < varf->carte.nrCapitole; i++) {
            printf(" %d", varf->carte.capitole[i]);
        }
        printf("\n\n");
        varf = varf->next;
    }
}

void dezalocareCarte(struct Carte* c) {
    free(c->capitole);
    free(c->denumire);
    c->capitole = NULL;
    c->denumire = NULL;
}

void dezalocareStiva(struct NodStiva** varf) {
    while (*varf) {
        struct Carte c = pop(varf);
        dezalocareCarte(&c);
    }
}

int main() {
    struct NodStiva* stiva = NULL;

    int capitole1[] = { 1, 2, 3 };
    int capitole2[] = { 4, 5, 6, 7 };
    int capitole3[] = { 1, 2, 3, 4, 5 };
    int capitole4[] = { 10, 20, 30 };

    struct Carte c1 = initializare(120, capitole1, "Povesti", 30.0f, 3);
    push(&stiva, c1);

    struct Carte c2 = initializare(200, capitole2, "Roman", 55.0f, 4);
    push(&stiva, c2);

    struct Carte c3 = initializare(180, capitole3, "Manual", 40.0f, 5);
    push(&stiva, c3);

    struct Carte c4 = initializare(300, capitole4, "Enciclopedie", 100.0f, 3);
    push(&stiva, c4);

    printf("Stiva:\n");
    afisareStiva(stiva);

    struct Carte extrasa = pop(&stiva);
    printf("Carte extrasa: %s, pret: %.2f\n\n", extrasa.denumire, extrasa.pret);
    dezalocareCarte(&extrasa);

    printf("Stiva dupa extragere:\n");
    afisareStiva(stiva);

    dezalocareStiva(&stiva);
    return 0;
}

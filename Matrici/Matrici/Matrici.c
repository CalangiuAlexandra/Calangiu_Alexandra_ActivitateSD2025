#include<stdio.h>
#include<stdlib.h>

struct Matrice {
    int nrlinii;
    int nrcol;
    int** elemente;
};

struct Matrice initializare(int nrlinii, int nrcol) {
    struct Matrice m;
    m.nrlinii = nrlinii;
    m.nrcol = nrcol;

    m.elemente = (int**)malloc(sizeof(int*) * m.nrlinii);
    for (int i = 0; i < m.nrlinii; i++) {
        m.elemente[i] = (int*)malloc(sizeof(int) * m.nrcol);
    }

    return m;
}

void citire_matrice(struct Matrice* m) {
    printf("Introduceti elementele matricii cu dimensiunea %d x %d:\n", m->nrlinii, m->nrcol);
    for (int i = 0; i < m->nrlinii; i++) {
        for (int j = 0; j < m->nrcol; j++) {
            printf("Elementul [%d][%d]: ", i, j);
            scanf_s("%d", &m->elemente[i][j]);
        }
    }
}

void afisare_matrice(struct Matrice m) {
    printf("Matricea %d x %d este:\n", m.nrlinii, m.nrcol);
    for (int i = 0; i < m.nrlinii; i++) {
        for (int j = 0; j < m.nrcol; j++) {
            printf("%d ", m.elemente[i][j]);
        }
        printf("\n");
    }
}

struct Matrice adunare_matrici(struct Matrice m1, struct Matrice m2) {
    if (m1.nrlinii != m2.nrlinii || m1.nrcol != m2.nrcol) {
        printf("Nu se pot aduna matricile!\n");
        return;
    }

    struct Matrice adunare = initializare(m1.nrlinii, m1.nrcol);

    for (int i = 0; i < m1.nrlinii; i++) {
        for (int j = 0; j < m1.nrcol; j++) {
            adunare.elemente[i][j] = m1.elemente[i][j] + m2.elemente[i][j];
        }
    }

    return adunare;
}

struct Matrice scadere_matrici(struct Matrice m1, struct Matrice m2) {
    if (m1.nrlinii != m2.nrlinii || m1.nrcol != m2.nrcol) {
        printf("Nu se pot scadea matricile!\n");
        return;
    }

    struct Matrice scadere = initializare(m1.nrlinii, m1.nrcol);

    for (int i = 0; i < m1.nrlinii; i++) {
        for (int j = 0; j < m1.nrcol; j++) {
            scadere.elemente[i][j] = m1.elemente[i][j] - m2.elemente[i][j];
        }
    }

    return scadere;
}

struct Matrice inmultire_matrici(struct Matrice m1, struct Matrice m2) {
    if (m1.nrcol != m2.nrlinii) {
        printf("Nu se pot inmulti matricile!\n");
        return;
    }

    struct Matrice inmultire = initializare(m1.nrlinii, m2.nrcol);

    for (int i = 0; i < m1.nrlinii; i++) {
        for (int j = 0; j < m2.nrcol; j++) {
            inmultire.elemente[i][j] = 0;
            for (int k = 0; k < m1.nrcol; k++) {
                inmultire.elemente[i][j] += m1.elemente[i][k] * m2.elemente[k][j];
            }
        }
    }

    return inmultire;
}

void dezalocare_matrice(struct Matrice* m) {
    for (int i = 0; i < m->nrlinii; i++) {
        free(m->elemente[i]);
    }
    free(m->elemente);
    m->elemente = NULL;
}

int main() {
    int nrlinii, nrcol;
    printf("Introduceti numarul de linii:.\n");
    scanf_s("%d", &nrlinii);
    printf("Introduceti numarul de coloane:.\n");
    scanf_s("%d", &nrcol);
    struct Matrice m1 = initializare(nrlinii, nrcol);
    struct Matrice m2 = initializare(nrlinii, nrcol);

    citire_matrice(&m1);
    citire_matrice(&m2);
    afisare_matrice(m1);
    afisare_matrice(m2);

    struct Matrice adunare = adunare_matrici(m1, m2);
    printf("Adunare matrici:\n");
    afisare_matrice(adunare);
    struct Matrice scadere = scadere_matrici(m1, m2);
    printf("Rezultatul scaderii matricelor:\n");
    afisare_matrice(scadere);
    struct Matrice inmultire = inmultire_matrici(m1, m2);
    printf("Rezultatul inmultirii matricelor:\n");
    afisare_matrice(inmultire);

    dezalocare_matrice(&m1);
    dezalocare_matrice(&m2);
    dezalocare_matrice(&adunare);
    dezalocare_matrice(&scadere);
    dezalocare_matrice(&inmultire);

    return 0;
}

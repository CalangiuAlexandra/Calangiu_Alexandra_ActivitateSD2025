#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Carte {
	int nrPagini;
	int* capitole;
	char* denumire;
	float pret;
	int nrCapitole;
};

//initializare

struct Carte initializare(int nrPagini, const int* capitole, const char* denumire, float pret, int nrCapitole) {
	struct Carte c;
	c.nrPagini = nrPagini;
	c.nrCapitole = nrCapitole;
	c.capitole = (int*)malloc(sizeof(int) * c.nrCapitole);
	for (int i = 0; i < c.nrCapitole; i++) {
		c.capitole[i] = capitole[i];
	}
	c.denumire = (char*)malloc(sizeof(char) * strlen(denumire) + 1);
	strcpy_s(c.denumire, strlen(denumire) + 1, denumire);
	c.pret = pret;
	return c;
}

//afisare
void afisare(struct Carte c) {
	if (c.capitole != NULL) {
		printf("Numarul de pagini este: %d, avand capitolele: ", c.nrPagini);
		for (int i = 0; i < c.nrCapitole; i++) {
			printf(" %d", c.capitole[i]);
		}
		printf(" Denumirea cartii fiind: %s, cu pretul: %5.2f si nr de capitole: %d", c.denumire, c.pret, c.nrCapitole);
	}
}

//citire tastatura

struct Carte citire() {

	int nrPagini;
	int nrCapitole;
	int* capitole;
	char* denumire;
	float pret;
	printf(" Introduceti numarul de pagini: ");
	scanf_s("%d", &nrPagini);
	printf(" Introduceti numarul de capitole aferente cartii: ");
	scanf_s(" %d ", &nrCapitole);
	capitole = (int*)malloc(sizeof(int) * nrCapitole);
	printf(" Introduceti capitolele: ");
	for (int i = 0; i < nrCapitole; i++) {
		scanf_s(" %d", &capitole[i]);
	}
	denumire = (char*)malloc(sizeof(char) * 100);
	printf(" Denumirea cartii este: ");
	scanf_s("%s", denumire, 100);
	printf(" Avand pretul de: ");
	scanf_s("%f", &pret);
	return initializare(nrPagini, capitole, denumire, pret, nrCapitole);
}

//numar de pagini/capitol
void numarPaginiPerCapitol(struct Carte carte) {
	int paginiPerCapitol;
	paginiPerCapitol = carte.nrPagini / carte.nrCapitole;
	printf(" Numarul de pagini per capitol este: %f ", paginiPerCapitol);
}

//numar de capitole pare

void numarCapitolePare(struct Carte carte) {
	int numarCapitolePare = 0;
	for (int i = 0; i < carte.nrCapitole; i++) {
		if (carte.capitole[i] % 2 == 0) {
			numarCapitolePare++;
		}
	}printf(" Numarul de capitole pare este: %d ", numarCapitolePare);
}

//modificare pret

void modificarePret(struct Carte* carte, float noulPret) {
	carte->pret = noulPret;
	printf(" Noul pret este: %f ", noulPret);
}


void dezalocare(struct Carte* carte) {
	if (carte->capitole != NULL) {
		free(carte->capitole);
	}carte->capitole = NULL;
	if (carte->denumire != NULL) {
		free(carte->denumire);
	}carte->denumire = NULL;
}

int main() {
	int nr = 3;
	struct Carte* carti = (struct Carte*)malloc(sizeof(struct Carte) * nr);
	int vectorCapitole1[] = { 1, 2, 3 };
	carti[0] = initializare(200, vectorCapitole1, "Frumoasa si bestia", 95.2, 3);
	int vectorCapitole2[] = { 1, 2, 3, 4 };
	carti[1] = initializare(300, vectorCapitole2, "Muntele dintre noi", 120.5, 4);
	int vectorCapitole3[] = { 1, 2, 3, 4, 5 };
	carti[2] = initializare(400, vectorCapitole3, "Cartea visurilor", 150.0, 5);
	for (int i = 0; i < nr; i++) {
		afisare(carti[i]);
		printf("\n");
	}

	for (int i = 0; i < nr; i++) {
		dezalocare(&carti[i]);
	}

	struct Carte c1;
	int vectorCapitole[] = { 1,2,3 };
	int* capitole = vectorCapitole;
	c1 = initializare(200, capitole, "Frumoasa si bestia", 95.2, 3);
	afisare(c1);
	struct Carte c2;
	c2 = citire();
	afisare(c2);
	numarPaginiPerCapitol(c2);
	numarCapitolePare(c2);
	modificarePret(&c1, 100.5);
	afisare(c1);

	return 0;
}
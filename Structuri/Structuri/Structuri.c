#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct Casa {
	float suprafata;
	int numarEtaje;
	char* strada;
	int valoareCasa;
};

struct Casa initializare(float suprafata, int numarEtaje, const char* strada, int valoareCasa) {
	struct Casa c;
	c.suprafata = suprafata;
	c.numarEtaje = numarEtaje;
	c.strada = (char*)malloc(sizeof(char) * (strlen(strada) + 1));
	strcpy_s(c.strada, strlen(strada) + 1, strada);
	c.valoareCasa = valoareCasa;
	return c;
}

void afisare(struct Casa c) {
	if (c.strada != NULL) {
		printf("Casa are suprafata: %5.2f mp cu numarul de etaje: %d, fiind pe strada: %s, cu o valoare a imobilului de: %d euro\n",
			c.suprafata, c.numarEtaje, c.strada, c.valoareCasa);
	}
	else {
		printf("Casa are suprafata: %5.2f mp cu numarul de etaje: %d, cu o valoare a imobilului de: %d euro\n",
			c.suprafata, c.numarEtaje, c.valoareCasa);
	}

}

void modificareValoareCasa(struct Casa* c, int nouaValoare) {
	if (c->valoareCasa != NULL) {
		c->valoareCasa = nouaValoare;
	}
}

void dezalocare(struct Casa* c) {
	if (c->strada != NULL) {
		free(c->strada);
		c->strada = NULL;
	}
}

void valoareMp(struct Casa* c) {
	if (c->valoareCasa != NULL) {
		printf("Valoarea casei: %f / Mp\n", c->valoareCasa / c->suprafata);
	}
	else {
		printf("Nu se poate determina valoarea imobilului: ");
	}
}

struct Casa citireCasa() {
	float suprafata = 130;
	int numarEtaje = 1;
	char* strada = (char*)malloc(255 * sizeof(char));
	int valoareCasa = 0;

	printf("Introduceti suprafata: \n");
	scanf_s("%f", &suprafata);
	printf("Introduceti numarul de etaje: \n");
	scanf_s("%d", &numarEtaje);
	printf("Casa se gaseste pe strada: \n");
	scanf_s("%254s", strada, 255);

	printf("Valoarea casei fiind de: \n");
	scanf_s("%d", &valoareCasa);
	struct Casa c;
	c = initializare(suprafata, numarEtaje, strada, valoareCasa);

	free(strada);
	return c;

}


int main() {
	struct Casa c;
	c = initializare(120.5, 2, "Bulevardul Dacia", 120000);
	afisare(c);
	modificareValoareCasa(&c, 135000);
	afisare(c);
	valoareMp(&c);
	struct Casa c1;
	c1 = citireCasa();
	afisare(c1);

	return 0;
}





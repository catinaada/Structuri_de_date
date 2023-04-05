#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Librarie Librarie;
typedef struct Nod Nod;

struct Librarie {
	char* nume;
	int nrCarti;
	float suprafata;
};

struct Nod {
	Librarie info;
	Nod* next;
};

Librarie initializareLibrarie(const char* nume, int nrCarti, float suprafata) {
	Librarie librarie;
	librarie.nrCarti = nrCarti;
	librarie.suprafata = suprafata;
	librarie.nume = malloc((strlen(nume) + 1) * sizeof(char));
	strcpy(librarie.nume, nume);

	return librarie;
}

Librarie citireFisierLibrarie(FILE* f) {
	Librarie l;
	char buffer[30];
	fscanf(f, "%s", buffer);
	l.nume = malloc(strlen(buffer));
	strcpy(l.nume, buffer);
	fscanf(f, "%d", &l.nrCarti);
	fscanf(f, "%f", &l.suprafata);
	return l;
}

Librarie* fisier(FILE* file, int* nrLibrarii) {
	Librarie* librarii;
	fscanf(file, "%d", &(*nrLibrarii));
	librarii = malloc(sizeof(Librarie) * (*nrLibrarii));
	for (int j = 0; j < *nrLibrarii; j++) {
		librarii[j] = citireFisierLibrarie(file);
	}
	return librarii;
}

void afisareLibrarie(Librarie l) {
	printf("Nume: %s, Nr Carti: %d, Suprafata: %f ", l.nume, l.nrCarti, l.suprafata);
	printf("\n");
}

Nod* inserareInceput(Nod* cap, Librarie l) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = l;
	nou->next = cap;

	return nou;
}

void inserareFinal(Nod** cap, Librarie l) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = l;
	nou->next = NULL;
	if (*cap) {
		Nod* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		*cap = nou;
	}
}

void afisareNod(Nod* cap) {
	while (cap != NULL) {
		afisareLibrarie(cap->info);
		cap = cap->next;
	}
}

void stergereLista(Nod** cap) {
	while (*cap) {
		free((*cap)->info.nume);
		Nod* p = *cap;
		(*cap) = (*cap)->next;
		free(p);
	}
}

void afisareVector(Librarie* l,int nr) {
	for (int i = 0; i < nr; i++) {
		afisareLibrarie(l[i]);
	}
}

void main() {

	FILE* file = fopen("Librarie.txt", "r");
	if (file!=NULL) {
		Librarie* librarii;
		int nrLibrarii;
		librarii = fisier(file, &nrLibrarii);
		afisareVector(librarii, nrLibrarii);
		printf("\n");
		
		Nod* cap = NULL;
		inserareFinal(&cap, librarii[0]);
		inserareFinal(&cap, librarii[1]);
		cap = inserareInceput(cap, librarii[2]);
		afisareNod(cap);

	}
	else {
		printf("Eroare nu s-a putut citi fisierul");
	}
	
	/*Nod* cap = NULL;
	cap = inserareInceput(cap, initializareLibrarie("Libris", 100, 400));
	cap = inserareInceput(cap, initializareLibrarie("Carturesti",11,1457));
	inserareFinal(&cap, initializareLibrarie("Paralela45",7,789));
	afisareNod(cap);
	stergereLista(&cap);
	afisareNod(cap);*/





}
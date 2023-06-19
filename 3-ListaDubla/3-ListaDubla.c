#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>


typedef struct Librarie Librarie;

struct Librarie {
	char* nume;
	unsigned int nrCarti;
	float suprafata;
};

Librarie citireLibrarie(FILE* f) {
	
	char buffer[30];
	fscanf(f, "%s", buffer);
	Librarie librarie;
	librarie.nume = malloc(strlen(buffer) + 1);
	strcpy(librarie.nume, buffer);
	fscanf(f, "%d", &librarie.nrCarti);
	fscanf(f, "%f", &librarie.suprafata);
	return librarie;
}

void afisareLibrarie(Librarie l) {
	printf("Libraria %s are %d carti si o suprafata de %5.2f \n", l.nume, l.nrCarti, l.suprafata);
}

Librarie* citireVectorLibrarie(const char* numeFisier, int* nrLibrarii) {
	FILE* f = fopen(numeFisier, "r");
	fscanf(f, "%d", nrLibrarii);
	//aloc
	Librarie* librarii;
	librarii = malloc(sizeof(Librarie) * (*nrLibrarii));
	for (int i = 0; i < *nrLibrarii; i++) {
		librarii[i] = citireLibrarie(f);
	}
	return librarii;
}

typedef struct Nod Nod;
typedef struct LD LD;

struct Nod {
	Librarie info;
	Nod* prev;
	Nod* next;
};

struct LD {
	Nod* prim;
	Nod* ultim;
};

void inserareFinal(LD* ld, Librarie l) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = l;
	nou->next = NULL;
	nou->prev = ld->ultim;
	if (ld->ultim) {
		ld->ultim->next = nou;
	}
	else {
		ld->prim = nou;
	}
	ld->ultim = nou;
}

void afisareListaDubla(LD lista) {
	Nod* p = lista.prim;
	while (p) {
		afisareLibrarie(p->info);
		p = p->next;
	}
}


void stergereLD(LD* lista) {
	Nod* p = lista->prim;
	while (p) {
		free(p->info.nume);
		Nod* aux = p->next;
		free(p);
		p = aux;
	}
	lista->prim = NULL;
	lista->ultim = NULL;
}

void main() {
	LD lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	int nrLibrarii;
	Librarie* librarii;
	librarii = citireVectorLibrarie("Librarie.txt", &nrLibrarii);

	for (int i = 0; i < nrLibrarii; i++) {
		inserareFinal(&lista, librarii[i]);
	}

	afisareListaDubla(lista);






}
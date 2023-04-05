#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Librarie Librarie;

struct Librarie {
	char* nume;
	int nrCarti;
	float suprafata;
};

Librarie initialiareLibrarie(const char* nume, int nrCarti, float suprafata) {
	Librarie l;
	l.nrCarti = nrCarti;
	l.suprafata = suprafata;
	l.nume = malloc((strlen(nume) + 1) * sizeof(char));
	strcpy(l.nume, nume);
	return l;
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

Librarie* citireFisier(FILE* f, int* nrLibrarii) {
	Librarie* librarii;
	fscanf(f, "%d", &(*nrLibrarii));
	librarii = malloc(sizeof(Librarie) * (*nrLibrarii));
	for (int j = 0; j < *nrLibrarii; j++) {
		librarii[j] = citireFisierLibrarie(f);
	}

	return librarii;
}

void afisareLibrarie(Librarie l) {
	printf("Nume: %s , nrCarti: %d , Suprafata: %f", l.nume, l.nrCarti, l.suprafata);
}

void afisareVector(Librarie* l,int nr) {
	for (int i = 0; i < nr; i++) {
		afisareLibrarie(l[i]);
		printf("\n");
	}
}


typedef struct Nod Nod;

struct Nod {
	Librarie info;
	Nod* prev;
	Nod* next;
};

typedef struct ListaDubla ListaDubla;

struct ListaDubla {
	Nod* prim;
	Nod* ultim;
};

void inserareInceput(ListaDubla* lista, Librarie librarie) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = librarie;
	nou->prev = NULL;
	nou->next = lista->prim;
	if (lista->prim) {
		lista->prim->prev = nou;
	}
	else {
		lista->ultim = nou;
	}	
	lista->prim = nou;

}

void inserareSfarsit(ListaDubla* lista, Librarie librarie) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = librarie;
	nou->next = NULL;
	nou->prev = lista->ultim;
	if (lista->ultim) {
		lista->ultim->next = nou;

	}
	else {
		lista->prim = nou;
	}
	lista->ultim = nou;

}

void afisareInceput(ListaDubla l) {
	Nod* p = l.prim;
	while (p) {
		afisareLibrarie(p->info);
		p = p->next;
		printf("\n");
	}
}

void afisareFinal(ListaDubla l) {
	Nod* p = l.ultim;
	while (p) {
		afisareLibrarie(p->info);
		p = p->prev;
		printf("\n");
	}
}

void stergereLD(ListaDubla* l) {
	Nod* p = l->prim;
	while (p) {
		free(p->info.nume);
		Nod* aux = p->next;
		free(p);
		p = aux;
	}
	l->prim = NULL;
	l->ultim = NULL;
}



void main() {
	Librarie l = initialiareLibrarie("Libris", 7, 4444);
	
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	
	inserareInceput(&lista, initialiareLibrarie("Libris", 5454, 777));
	inserareSfarsit(&lista, initialiareLibrarie("pa", 789, 10));
	inserareInceput(&lista, initialiareLibrarie("dgdgdg", 333, 888));
	afisareInceput(lista);
	printf("\n");
	stergereLD(&lista);
	afisareFinal(lista);

	printf("\n\n\n");

	//FILE* f = fopen("Librarie.txt", "r");
	//if (f) {
	//	Librarie* librarii;
	//	int nrLibrarii;
	//	librarii = citireFisier(f, &nrLibrarii);
	//	afisareVector(librarii, nrLibrarii);
	//	printf("\n");
	//	ListaDubla ld;
	//	ld.prim = NULL;
	//	ld.ultim = NULL;
	//	inserareInceput(&ld, librarii[0]);
	//	inserareInceput(&ld, librarii[2]);
	//	inserareSfarsit(&ld, librarii[1]);
	//	afisareInceput(ld);

	//}
	//else {
	//	printf("Eroare");
	//}


}
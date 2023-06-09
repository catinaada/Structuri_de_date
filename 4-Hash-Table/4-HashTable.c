#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Piata Piata;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Piata {
	char* nume;
	int nrTarabe;
};

Piata initializarePiata(const char* nume, int nrTarabe) {
	Piata p;
	p.nume = malloc(strlen(nume) + 1);
	strcpy(p.nume, nume);
	p.nrTarabe = nrTarabe;
	return p;
}

Piata citirePiataFisier(FILE* f) {
	Piata p;
	char buffer[30];
	fscanf(f, "%s", buffer);
	p.nume = malloc(strlen(buffer) + 1);
	strcpy(p.nume, buffer);
	fscanf(f, "%d", &p.nrTarabe);
	return p;
}

Piata* citireVectorPiete(const char* numeFisier, int* nrPiete) {
	FILE* f = fopen(numeFisier, "r");
	fscanf(f, "%d", nrPiete);
	Piata* piete = malloc(sizeof(Piata) * (*nrPiete));
	for (int i = 0; i < *nrPiete; i++) {
		piete[i] = citirePiataFisier(f);
	}
	return piete;
}

void afisarePiata(Piata p) {
	printf("Piata %s are %d tarabe\n", p.nume, p.nrTarabe);
}


struct Nod {
	Piata info;
	Nod* next;
};

struct HashTable {
	int dim;
	Nod** tabela;
};

int functieHashTable(int dim, const char*nume) {
	int s = 0;
	for (int i = 0; i < strlen(nume); i++) {
		s += nume[i];
	}
	return s % dim;
}

HashTable initializareHashTable(int dim) {
	HashTable ht;
	ht.dim = dim;
	ht.tabela = malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < dim; i++) {
		ht.tabela[i] = NULL;
	}
	return ht;
}

void inserareLista(Nod** cap, Piata p) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = p;
	nou->next = NULL;
	if(*cap) {
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

void inserarePiataInHash(HashTable ht, Piata p) {
	int poz;
	poz = functieHashTable(ht.dim, p.nume);
	if (ht.tabela[poz] != NULL) {
		inserareLista(&ht.tabela[poz], p);
	}
	else {
		inserareLista(&ht.tabela[poz], p);
	}
}

void afisareLista(Nod* lista) {
	while (lista) {
		afisarePiata(lista->info);
		lista = lista->next;
	}
}

void afisareHashTable(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		printf("Pozitia %d\n", i);
		if (ht.tabela[i] != NULL) {
			afisareLista(ht.tabela[i]);
		}
		else {
			printf("----------\n");
		}
	}
}

Piata cautarePiataDupaNume(HashTable ht, const char* nume) {
	int poz;
	poz = functieHashTable(ht.dim, nume);
	Nod* aux = ht.tabela[poz];
	while (aux && strcmp(aux->info.nume, nume) != 0) {
		aux = aux->next;
	}
	if (aux) {
		return aux->info;
	}
	else {
		return initializarePiata("NA", 0);
	}
}

void stergereHashTable(HashTable* ht) {
	for (int i = 0; i < ht->dim; i++) {
		Nod* p = ht->tabela[i];
		while (p) {
			Nod* aux = p;
			p = p->next;
			free(aux->info.nume);
			free(aux);
		}
	}
	free(ht->tabela);
	ht->tabela = NULL;
	ht->dim = 0;

}

int nrTotalTarabe(HashTable ht) {
	int s = 0;
	for (int i = 0; i < ht.dim; i++) {
		Nod* p = ht.tabela[i];
		while (p) {
			s= s+p->info.nrTarabe;
			p = p->next;
		}
	}

	return s;
}


void main() {

	Piata* piete;
	int nrPiete;
	piete = citireVectorPiete("Piata.txt", &nrPiete);
	afisarePiata(piete[0]);
	afisarePiata(piete[1]);
	afisarePiata(piete[2]);

	printf("\nHash Table\n");
	
	HashTable ht;
	ht = initializareHashTable(nrPiete);
	for (int i = 0; i < nrPiete; i++) {
		inserarePiataInHash(ht, piete[i]);
	}
	afisareHashTable(ht);
	Piata p=cautarePiataDupaNume(ht,"Apusului");
	afisarePiata(p);
	int sumaTarabe = nrTotalTarabe(ht);
	printf("Suma tarabelor: %d\n", sumaTarabe);

	stergereHashTable(&ht);
	afisareHashTable(ht);


}
#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>

typedef struct Elev Elev;
struct Elev {
	char* nume;
	int nrMatricol;
};

Elev initializareElev(const char* nume, int nrMatricol) {
	Elev e;
	e.nume = malloc(strlen(nume) + 1);
	strcpy(e.nume, nume);
	e.nrMatricol = nrMatricol;
	return e;
}

Elev citireElevFisier(FILE* f) {
	Elev e;
	char buffer[30];
	fscanf(f, "%s", buffer);
	e.nume = malloc(strlen(buffer) + 1);
	strcpy(e.nume, buffer);
	fscanf(f, "%d", &e.nrMatricol);
	return e;
}

Elev* citireVectorElevi(const char* numeFisier, int* nrElevi) {
	
	FILE* f = fopen(numeFisier, "r");
	fscanf(f, "%d", nrElevi);
	Elev* e = malloc(sizeof(Elev) * (*nrElevi));
	for (int i = 0; i < *nrElevi; i++) {
		e[i] = citireElevFisier(f);
	}
	return e;
}

void afisareElev(Elev e) {
	printf("Elev: %s, Nr. Matricol: %d\n", e.nume, e.nrMatricol);
}


typedef struct Nod Nod;
struct Nod {
	Elev info;
	Nod* next;
};

void inserareLista(Nod** cap, Elev e) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = e;
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

void afisareLista(Nod* cap) {
	while (cap) {
		afisareElev(cap->info);
		cap = cap->next;
	}
}

typedef struct HashTable HashTable;
struct HashTable {
	int dim;
	Nod** tabela;
};

int functieHash(HashTable ht, int nrMatricol) {
	return nrMatricol % ht.dim;
}

HashTable initializareHash(int dim) {
	HashTable ht;
	ht.dim = dim;
	ht.tabela = malloc(sizeof(Nod*) * dim);

	for (int i = 0; i < dim;i++) {
		ht.tabela[i] = NULL;
	}

	return ht;
}

void inserareElevInHash(HashTable ht, Elev e) {
	int poz;
	poz = functieHash(ht, e.nrMatricol);
	if (ht.tabela[poz] != NULL) {
		inserareLista(&ht.tabela[poz], e);
	}else{
		inserareLista(&ht.tabela[poz], e);
	}
}

void afisareHashTable(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		printf("Pozitia %d\n", i);

		if (ht.tabela[i] != NULL)
			afisareLista(ht.tabela[i]);
		else {
			printf("--------\n");

		}

	}
}

void stergereHash(HashTable* ht) {
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

Elev cautareElevDupaNrMatricol(HashTable ht, int nrMatricol) {
	int poz;
	poz = functieHash(ht, nrMatricol);
	Nod* p = ht.tabela[poz];
	while (p && ht.tabela[poz]->info.nrMatricol != nrMatricol) {
		p = p->next;
	}
	if (p) {
		return p->info;
	}
	else {
		return initializareElev("Fara", 0);
	}
}





void main() {
	Elev* elevi;
	int nrElevi;
	elevi = citireVectorElevi("Elevi.txt", &nrElevi);
	afisareElev(elevi[0]);
	afisareElev(elevi[1]);
	afisareElev(elevi[2]);

	printf("Ht\n");

	HashTable ht = initializareHash(nrElevi); 

	for (int i = 0; i < nrElevi; i++) {
		inserareElevInHash(ht, elevi[i]);
	}
	afisareHashTable(ht);


	Elev p = cautareElevDupaNrMatricol(ht, 1);
	afisareElev(p);

	Elev r = cautareElevDupaNrMatricol(ht, 5);
	afisareElev(r);

	stergereHash(&ht);
	afisareHashTable(ht);



}
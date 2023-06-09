#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>

//Lista simpla

//Am structura Librarie ce contine: numele librariei. numarul de carti si suprafata
//- Sa se realizeze o lista simpla si sa se afiseze. Sa se insereze la inceput si la final
//- Sa se stearga lista
//- Sa se citeasca din fisier si sa fie introduse datele intr-o lista simpla
//- O functie care sterge un nod de pe o pozitie data ca parametru
//Daca lista are mai putine noduri decat index - ul dat, nu se realizeaza stergerea.


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

	librarie.nume = malloc((strlen(nume) + 1) * sizeof(char));
	strcpy(librarie.nume, nume);
	librarie.nrCarti = nrCarti;
	librarie.suprafata = suprafata;

	return librarie;
}

void afisareLibrarie(Librarie l) {
	printf(" Libraria %s are %d carti si o suprafata de %5.2f\n", l.nume, l.nrCarti, l.suprafata);
}

Nod* inserareNodInceput(Librarie l, Nod* cap) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = l;
	nou->next = cap;
	cap = nou;
	return nou;
}

void inserareNodFinal(Librarie l, Nod** cap) {
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

void afisareLista(Nod* cap) {
	while (cap) {
		afisareLibrarie(cap->info);
		cap = cap->next;
	}
}

void stergeLista(Nod** cap) {
	while (*cap) {
		Nod* p = (*cap)->next;
		free((*cap)->info.nume);
		free(*cap);
		*cap = p;
	}
}

//citire fisier
Librarie citireLibrarieFisier(FILE* f) {
	Librarie aux;
	char buffer[30];
	fscanf(f, "%s", buffer);
	aux.nume = malloc(strlen(buffer) + 1);
	strcpy(aux.nume, buffer);
	fscanf(f, "%d", &aux.nrCarti);
	fscanf(f, "%f", &aux.suprafata);
	return aux;
}

Librarie* citireVectorLibrarii(const char* numeFisier, int* nrLibrarii) {
	FILE* f = fopen(numeFisier, "r");
	fscanf(f, "%d", nrLibrarii);

	Librarie* librarii;
	librarii = malloc(sizeof(Librarie) * (*nrLibrarii));
	for (int i = 0; i < *nrLibrarii; i++) {
		librarii[i] = citireLibrarieFisier(f);
	}
	return librarii;
}

//cautare pozitie
Nod* cautarePozitie(Nod* cap, int poz) {
	int i = 0;
	while (cap != NULL && i < poz)
	{
		cap = cap->next;
		i++;
	}
	if (i == poz)
		return cap;
	else return NULL;
}

// O functie care sterge un nod de pe o pozitie data ca parametru
void stergeNodDupaPozitie(Nod** cap, int poz) {
	Nod* p = *cap;

	if (*cap == NULL)return;
	if (poz == 0) {
		Nod* aux = (*cap);
		(*cap) = (*cap)->next;
		free(aux->info.nume);
		free(aux);
		return;
	}
	else {
		Nod* p = cautarePozitie(*cap, poz - 1);
		if (p != NULL) {
			Nod* aux = p->next;
			p->next = p->next->next;
			free(aux->info.nume);
			free(aux);
		}
	}

}




void main() {

	Nod* lista = NULL;
	inserareNodFinal(initializareLibrarie("Librarie", 100, 100), &lista);
	inserareNodFinal(initializareLibrarie("Carturesti", 85, 126), &lista);
	inserareNodFinal(initializareLibrarie("Diverta", 78, 456), &lista);
	lista = inserareNodInceput(initializareLibrarie("Paralela 45", 45, 123), lista);

	afisareLista(lista);
	//stergeLista(&lista);
	//afisareLista(lista);

	printf("\n Acum si din fisier\n");
	int nrLibrarii;
	Librarie* listaFisier = NULL;
	listaFisier = citireVectorLibrarii("Librarie.txt", &nrLibrarii);

	for (int i = 0; i < nrLibrarii; i++) {
		inserareNodFinal(listaFisier[i], &lista);
	}
	afisareLista(lista);
	printf("\n");
	stergeNodDupaPozitie(&lista, 1);
	afisareLista(lista);






}
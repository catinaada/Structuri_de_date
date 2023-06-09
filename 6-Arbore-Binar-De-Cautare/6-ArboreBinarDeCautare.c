#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Brutarie Brutarie;
struct Brutarie {
	char* nume;
	int id;
	int nrAngajati;
};

Brutarie initializareBrutarie(const char* nume, int id, int nrAngajati) {
	Brutarie b;
	b.nume = malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	b.id = id;
	b.nrAngajati = nrAngajati;

	return b;

}

Brutarie citireBrutarie(FILE* f) {
	Brutarie b;
	char buffer[30];
	fscanf(f, "%s", buffer);
	b.nume = malloc(strlen(buffer) + 1);
	strcpy(b.nume, buffer);
	fscanf(f, "%d", &b.id);
	fscanf(f, "%d", &b.nrAngajati);
	return b;
}

Brutarie* citireVectorBrutarii(const char* numeFisier, int* nrBrutarii) {
	FILE* f = fopen(numeFisier, "r");
	fscanf(f, "%d", nrBrutarii);
	Brutarie* brutarii = malloc(sizeof(Brutarie) * (*nrBrutarii));
	for (int i = 0; i < *nrBrutarii; i++) {
		brutarii[i] = citireBrutarie(f);
	}
	return brutarii;
}

void afisareBrutarie(Brutarie b) {
	printf("Brutaria %s are id-ul %d si %d angajati\n",b.nume,b.id,b.nrAngajati);
}

typedef struct Nod Nod;
struct Nod {
	Brutarie info;
	Nod* st;
	Nod* dr;
};


void inserareNod(Brutarie b, Nod** radacina) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = b;
	nou->st = NULL;
	nou->dr = NULL;

	if (*radacina) {
		if ((*radacina)->info.id > b.id) {
			inserareNod(b, &(*radacina)->st);
		}
		else {
			inserareNod(b, &(*radacina)->dr);
		}

	}
	else {
		*radacina = nou;
	}
}


void afisarePreordine(Nod* rad) {
	if (rad) {
		afisareBrutarie(rad->info);
		afisarePreordine(rad->st);
		afisarePreordine(rad->dr);
	}
}

void afisarePostordine(Nod* rad) {
	if(rad) {
		afisarePostordine(rad->st);
		afisarePostordine(rad->dr);
		afisareBrutarie(rad->info);

	}
}

void afisareInordine(Nod* rad) {
	if (rad) {
		afisareInordine(rad->st);
		afisareBrutarie(rad->info);
		afisareInordine(rad->dr);
	}
}


//cautare brutarie
Brutarie cautareBrutarie(Nod* rad, int id) {
	if (rad) {
		if (id < rad->info.id) {
			return cautareBrutarie(rad->st, id);
		}
		else {
			if (id > rad->info.id) {
				return cautareBrutarie(rad->dr, id);
			}
			else {
				return rad->info;
			}
		}
	}
	else {
		return initializareBrutarie("Fara", 0, 0);
	}
}

int determinareInaltime(Nod* rad) {
	if (rad) {
		int hst = determinareInaltime(rad->st);
		int hdr = determinareInaltime(rad->dr);
		return 1 + (hst > hdr ? hst : hdr);
	}
	else {
		return 0;
	}
}

void stergeArbore(Nod** rad) {
	if (*rad) {
		stergeArbore(&(*rad)->st);
		stergeArbore(&(*rad)->dr);
		free((*rad)->info.nume);
		free(*rad);
		*rad = NULL;
	}
}

void main() {
	int nrBrutarii;
	Brutarie* brutarii = citireVectorBrutarii("Brutarii.txt", &nrBrutarii);

	Nod* rad=NULL;
	
	for (int i = 0; i < nrBrutarii; i++) {
		inserareNod(brutarii[i], &rad);
	}
	afisareInordine(rad);
	printf("\n");
	Brutarie b = cautareBrutarie(rad, 7);
	afisareBrutarie(b);

	int h = determinareInaltime(rad);
	printf("inaltimea este: %d\n", h);


}
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Moneda Moneda;
struct Moneda {
	char* tara;
	int valoare;
	float greutate;
	int an;
};

Moneda initializareMoneda(const char* tara, int valoare, float greutate, int an) {
	Moneda moneda;
	moneda.tara = malloc((strlen(tara) + 1) * sizeof(char));
	strcpy(moneda.tara, tara);
	moneda.valoare = valoare;
	moneda.greutate = greutate;
	moneda.an = an;

	return moneda;
}

void afisareMoneda(Moneda m) {
	printf("Tara: %s, Valoare: %d, Greutate: %f, An: %d \n", m.tara, m.valoare, m.greutate, m.an);
}

typedef struct Nod Nod;
struct Nod {
	Moneda info;
	Nod* next;
};

void inserareNodFinal(Nod** cap, Moneda moneda) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = moneda;
	nou->next = NULL;
	if (*cap!=NULL) {
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
		afisareMoneda(cap->info);
		cap = cap->next;
	}
}

Moneda copieMoneda(const Moneda m) {
	Moneda moneda;
	moneda.an = m.an;
	moneda.greutate = m.greutate;
	moneda.valoare = m.valoare;
	moneda.tara = malloc((strlen(m.tara) + 1) * sizeof(char));
	strcpy(moneda.tara, m.tara);
	return moneda;
}

Moneda greutateMaxima(Nod* cap) {
	Moneda moneda;
	float maxim = -1;
	Nod* aux = cap;
	while (cap != NULL) {
		if (cap->info.greutate > maxim) {
			maxim = cap->info.greutate;
		}
		cap = cap->next;
	}
	while (aux != NULL) {
		if (aux->info.greutate == maxim) {
			moneda = copieMoneda(aux->info);
		}
		aux = aux->next;

	}
	if (maxim != -1) {
		return moneda;
	}
	

}

void dezalocare(Nod** cap) {

	while (*cap) {
		free((*cap)->info.tara);
		Nod* p = *cap;
		(*cap) = (*cap)->next;
		free(p);
	}

}
typedef struct LD LD;
typedef struct NodLD NodLD;
struct NodLD {
	Moneda info;
	NodLD* prev;
	NodLD* next;
};

struct LD {
	NodLD* prim;
	NodLD* ultim;
};


void inserareLDInceput(LD* lista, Moneda m) {
	NodLD* nou = malloc(sizeof(NodLD));
	nou->info = m;
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

void inserareLDSfarsit(LD* lista, Moneda m) {
	NodLD* nou = malloc(sizeof(NodLD));
	nou->info = m;
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

void afisareIndeput(LD* l) {
	while (l->prim) {
		afisareMoneda(l->prim->info);
		l->prim = l->prim->next;
	}
}

void stergereLD(LD* lista) {
	NodLD* p = lista->prim;
	while (p->next) {
		free(p->info.tara);
		NodLD* aux = p->next;
		free(p);
		p = aux;
	}
	lista->prim = NULL;
	lista->ultim = NULL;
}

void main() {
	//Nod* lista = NULL;
	//inserareNodFinal(&lista, initializareMoneda("Romania", 50, 0.7, 2019));
	//inserareNodFinal(&lista, initializareMoneda("Bulgaria", 10, 0.27, 2018));
	//inserareNodFinal(&lista, initializareMoneda("Turcia", 50, 0.2, 2019));
	//inserareNodFinal(&lista, initializareMoneda("Romania", 10, 0.7, 2019));
	//inserareNodFinal(&lista, initializareMoneda("Turcia", 50, 1.2, 2018));

	//afisareLista(lista);
	//printf("\n");
	//Moneda m=greutateMaxima(lista);
	//afisareMoneda(m);
	//printf("\n");

	//free(m.tara); 
	///*afisareLista(lista);*/
	//dezalocare(&lista);
	//afisareLista(lista);

	LD listaDubla;
	listaDubla.prim = NULL;
	listaDubla.ultim = NULL;
	inserareLDInceput(&listaDubla, initializareMoneda("Romania", 50, 0.7, 2019));
	inserareLDSfarsit(&listaDubla, initializareMoneda("Croatia", 50, 0.7, 2019));
	inserareLDInceput(&listaDubla, initializareMoneda("Malaiezia", 50, 0.7, 2019));
	afisareIndeput(&listaDubla);


}
	
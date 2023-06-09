#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Mail Mail;
typedef struct Heap Heap;

struct Mail {
	int prioritate;
	char* subiect;
};

struct Heap {
	Mail* mailuri;
	int dimNrElemente;
	int dimTotala;
};

Mail citireMailFisier(FILE* f) {
	Mail m;
	char buffer[40];
	fscanf(f, "%s", buffer);
	m.subiect = malloc(strlen(buffer) + 1);
	strcpy(m.subiect, buffer);
	fscanf(f, "%d", &m.prioritate);
	return m;
}

Mail* citireVectorFisier(const char* numeFisier, int* nrMailuri) {
	FILE* f = fopen(numeFisier, "r");
	fscanf(f, "%d", nrMailuri);
	Mail* mailuri = malloc(sizeof(Mail) * (*nrMailuri));
	for (int i = 0; i < *nrMailuri; i++) {
		mailuri[i] = citireMailFisier(f);
	}
	return mailuri;
}

void afisareMail(Mail m) {
	printf("Subiect: %s, Prioritate: %d\n", m.subiect, m.prioritate);
}

Heap initializareHeap(int dim) {
	Heap aux;
	aux.dimTotala = dim;
	aux.dimNrElemente = 0;
	aux.mailuri = malloc(sizeof(Mail) * dim);
	return aux;
}

void filtrareHeap(Heap heap, int index) {
	int max = index;
	int is = 2 * index + 1;
	int id = 2 * index + 2;

	if (index < heap.dimNrElemente && is<heap.dimNrElemente && heap.mailuri[is].prioritate>heap.mailuri[max].prioritate) {
		max = is;
	}

	if (index < heap.dimNrElemente && id<heap.dimNrElemente && heap.mailuri[id].prioritate>heap.mailuri[max].prioritate) {
		max = id;
	}

	if (index != max) {
		Mail aux = heap.mailuri[index];
		heap.mailuri[index] = heap.mailuri[max];
		heap.mailuri[max] = aux;

		if (2 * max + 1 < heap.dimNrElemente) {
			filtrareHeap(heap, max);
		}
	}

}

Mail extreageMailPrioritateMare(Heap* h) {
	Mail aux = h->mailuri[0];
	h->mailuri[0] = h->mailuri[h->dimNrElemente - 1];
	h->mailuri[h->dimNrElemente - 1] = aux;
	h->dimNrElemente--;
	for (int i = (h->dimNrElemente - 1) / 2; i >= 0; i--) {
		filtrareHeap(*h, i);
	}
	return aux;
}

void afiseazaHeapUtilizat( Heap list)
{
	for (int i = 0; i < list.dimNrElemente; i++)
	{
		afisareMail(list.mailuri[i]);
	}
}
void afiseazaHeapTotal( Heap list)
{
	for (int i = 0; i < list.dimTotala; i++)
	{
		afisareMail(list.mailuri[i]);
	}
}

void main() {

	int nrMailuri;
	Mail* mailuri;
	mailuri = citireVectorFisier("Mail.txt", &nrMailuri);

	Heap heap;
	heap = initializareHeap(6);
	heap.dimNrElemente = 6;
	heap.mailuri = mailuri;

	for (int i = (heap.dimNrElemente - 2) / 2; i >= 0; i--) {
		filtrareHeap(heap, i);
	}
	afiseazaHeapTotal(heap);
	printf("\n");
	afiseazaHeapUtilizat(heap);
	 Mail mail2 = extreageMailPrioritateMare(&heap);
	 printf("\n");

	 afisareMail(mail2);
	 printf("\n");

	 afiseazaHeapUtilizat(heap);


}
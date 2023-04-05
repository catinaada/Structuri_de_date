#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Farmacie Farmacie;

struct Farmacie {
	char* nume;
	int nrAngajati;
	float* salariu;
	int an;
};

Farmacie initializareFarmacie(const char* nume, int nrAngajati, float* salariu, int an) {
	Farmacie f;
	f.an = an;
	f.nrAngajati = nrAngajati;
	f.nume = malloc((strlen(nume) + 1) * sizeof(char));
	strcpy(f.nume, nume);
	f.salariu = malloc(nrAngajati * sizeof(float));
	for (int i = 0; i < nrAngajati; i++) {
		f.salariu[i] = salariu[i];
	}
	return f;
}

Farmacie copiere(const Farmacie f) {
	Farmacie aux;
	aux.an = f.an;
	aux.nrAngajati = f.nrAngajati;
	aux.nume = malloc((strlen(f.nume) + 1) * sizeof(char));
	strcpy(aux.nume, f.nume);
	aux.salariu = malloc(f.nrAngajati * sizeof(float));
	for (int i = 0; i < f.nrAngajati; i++) {
		aux.salariu[i] = f.salariu[i];
	}
	return aux;
}

//adaugaFramacie in Vector si returnez un vector de farmacii
Farmacie* adaugaFarmacieInVector(Farmacie* farmacii, Farmacie f, int* nrFarmacii) {

	(*nrFarmacii)++;
	Farmacie* aux = malloc(sizeof(Farmacie) * (*nrFarmacii));
	for (int i = 0; i < *nrFarmacii - 1; i++) {
		aux[i] = farmacii[i];
	}
	aux[*nrFarmacii - 1] = copiere(f);
	return aux;


}

int calculTotalAngajati(Farmacie* farmacii, int nrFarmacii) {
	int nrTotalAngajati = 0;
	for (int i = 0; i < nrFarmacii; i++) {
		nrTotalAngajati += farmacii[i].nrAngajati;
	}
	return nrTotalAngajati;
}

//citire din fisier -nume, an, nrAng, salarii
Farmacie citireFisierFarmacie(FILE* f) {
	Farmacie aux;
	char buffer[30];
	fscanf(f, "%s", buffer);
	aux.nume = malloc(strlen(buffer) + 1);
	strcpy(aux.nume, buffer);

	fscanf(f, "%d", &aux.an);
	fscanf(f, "%d", &aux.nrAngajati);

	aux.salariu = malloc(aux.nrAngajati * sizeof(float));
	for (int i = 0; i < aux.nrAngajati; i++) {
		fscanf(f, "%f", &aux.salariu[i]);
	}
	return aux;

}

//citire fisier vector de farmacii
Farmacie* citireFisierVectorFarmacii(FILE* file ,int* nrFarmacii) {
	Farmacie* farmacii;
	fscanf(file, "%d", &(*nrFarmacii));
	farmacii = malloc(sizeof(Farmacie) * (*nrFarmacii));
	for (int i = 0; i < (*nrFarmacii); i++) {
		farmacii[i] = citireFisierFarmacie(file);
	}
	return farmacii;
}

//creare matrice de farmacii - in functie de anul farmaciei
Farmacie** creareMatriceFarmacie(Farmacie* farmacii, int**dim,int nrStructuri, int* nrCategorii) {
	Farmacie** matrice;
	*nrCategorii = 3;
	matrice = malloc(sizeof(Farmacie*) * (*nrCategorii));
	*dim= malloc(sizeof(int*) * (*nrCategorii));
	
	for (int i = 0; i < (*nrCategorii); i++) {
		(*dim)[i] = 0;
		matrice[i] = NULL;
	}

	for (int i = 0; i < nrStructuri; i++) {
		int index = farmacii[i].an - 2021;
		matrice[index] = adaugaFarmacieInVector(matrice[index], farmacii[i], &((*dim)[index]));

	}

	return matrice;
}


void afisareFarmacie(Farmacie f) {
	printf("Nume: %s, An: %d, Nr. Angajati: %d : ", f.nume, f.an, f.nrAngajati);
	for (int i = 0; i < f.nrAngajati; i++) {
		printf("%f ", f.salariu[i]);
	}
}

void afisareVectorFarmacii(Farmacie* farmacii, int nrFarmacii) {
	for (int k = 0; k < nrFarmacii; k++) {
		afisareFarmacie(farmacii[k]);
		printf("\n");
	}
}

void afisareMatrice(Farmacie** farmacie, int* dim, int linii) {
	printf("\n");
	for (int i = 0; i < linii; i++) {
		afisareVectorFarmacii(farmacie[i], dim[i]);
	}
}

void main() {
	/*Farmacie f1;
	float salariu[] = { 3500,1451.250 };
	f1 = initializareFarmacie("Tei", 2, salariu, 2022);
	afisareFarmacie(f1);
	printf("\n");
	int nrFarmacii = 1;
	Farmacie* farmacii;
	farmacii = malloc(sizeof(f1));
	farmacii[0] = copiere(f1);
	
	Farmacie f2 = initializareFarmacie("Catena", 2, salariu, 2021);
	Farmacie f3 = initializareFarmacie("Dr. Max", 2, salariu, 2020);

	farmacii = adaugaFarmacieInVector(farmacii, f2, &nrFarmacii);
	farmacii = adaugaFarmacieInVector(farmacii, f3, &nrFarmacii);

	for (int i = 0; i < nrFarmacii; i++) {
		afisareFarmacie(farmacii[i]);
		printf("\n");
	}
	int nrTotalAngajati= calculTotalAngajati(farmacii, nrFarmacii);
	printf("Nr total angajati: %d ", nrTotalAngajati);


	free(f1.nume);
	free(f1.salariu);
	free(f2.nume);
	free(f2.salariu); 
	free(f3.nume);
	free(f3.salariu);
	for (int j = 0; j < nrFarmacii; j++) {
		free(farmacii[j].nume);
		free(farmacii[j].salariu);
	}
	free(farmacii);

	printf("\n");*/

	FILE* file = fopen("Farmacie.txt", "r");
	/*Farmacie farmacia1 = citireFisierFarmacie(file);
	afisareFarmacie(farmacia1);*/
	Farmacie* vectorFarmacii;
	int numarFarmacii;
	vectorFarmacii = citireFisierVectorFarmacii(file, &numarFarmacii);
	//afisareVectorFarmacii(vectorFarmacii, numarFarmacii);

	Farmacie** matrice;
	int* dim;
	int nrCategorii;
	matrice = creareMatriceFarmacie(vectorFarmacii, &dim, numarFarmacii, &nrCategorii);
	afisareMatrice(matrice, dim, nrCategorii);



}
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

//Se va crea o structura numita farmacie ce va contine: denumirea,
//numarul de angajati, salariul fiecarui angajat si anul de infiintare al farmaciei;
//- se va afisa farmacia
// - se va realiza copia unei farmacii
//- se va crea un vector de farmacii
//- se va citi si din fisier un vector de farmacii

typedef struct Farmacie Farmacie;

struct Farmacie {
	char* denumire;
	int nrAngajati;
	float* salariu;
	int an;
};

Farmacie initializareFarmacie(const char* denumire, int nrAngajati, float* salariu, int an) {
	Farmacie farmacie;

	farmacie.denumire = malloc((strlen(denumire) + 1) * sizeof(char));
	strcpy(farmacie.denumire, denumire);
	farmacie.nrAngajati = nrAngajati;
	farmacie.salariu = malloc(nrAngajati * sizeof(float));
	for (int i = 0; i < nrAngajati; i++) {
		farmacie.salariu[i] = salariu[i];
	}
	farmacie.an = an;

	return farmacie;
}

void afisareFarmacie(Farmacie f) {
	printf("Numele farmaciei este %s, din anul %d, avand %d angajati cu salariile: ", f.denumire, f.an, f.nrAngajati);
	for (int i = 0; i < f.nrAngajati; i++) {
		printf("%5.2f ", f.salariu[i]);
	}
	printf("\n");
}

Farmacie copieFarmacie(const Farmacie f) {
	Farmacie aux;
	aux.an = f.an;
	aux.nrAngajati = f.nrAngajati;
	aux.denumire = malloc((strlen(f.denumire) + 1) * sizeof(char));
	strcpy(aux.denumire, f.denumire);
	aux.salariu = malloc(f.nrAngajati * sizeof(float));
	for (int i = 0; i < f.nrAngajati; i++) {
		aux.salariu[i] = f.salariu[i];
	}
	return aux;
}

Farmacie* adaugareFarmacieInVector(Farmacie* farmacii, Farmacie f, int* nrFarmacii) {
	(*nrFarmacii)++;
	Farmacie* aux = malloc(sizeof(Farmacie) * (*nrFarmacii));
	for (int i = 0; i < (*nrFarmacii) - 1 ; i++) {
		aux[i] = farmacii[i];
	}
	aux[*nrFarmacii - 1] = copieFarmacie(f);
	return aux;
}

//citire din fisier
struct Farmacie citireFisier(FILE* f) {
	struct Farmacie aux;

	char buffer[30];
	fscanf(f, "%s", buffer);
	aux.denumire = malloc(strlen(buffer) + 1);
	strcpy(aux.denumire, buffer);

	fscanf(f, "%d", &aux.nrAngajati);

	aux.salariu = malloc(sizeof(float) * aux.nrAngajati);
	for (int i = 0; i < aux.nrAngajati; i++) {
		fscanf(f, "%f5.2", &aux.salariu[i]);

	}

	fscanf(f, "%d", &aux.an);
	return aux;
}

struct Farmacie* citireVectorFisier(const char* numeFisier, int* nr_farmacii) {
	FILE* file = fopen(numeFisier, "r");

	struct Farmacie* vectorFarm;
	fscanf(file, "%d", nr_farmacii);
	vectorFarm = malloc(sizeof(struct Farmacie) * (*nr_farmacii));

	for (int i = 0; i < *nr_farmacii; i++) {
		vectorFarm[i] = citireFisier(file);
	}

	return vectorFarm;
}

void afisareVectorFarmacie(struct Farmacie* vectorFarmacii, int nrFarmacie) {
	printf("Nr farmacii: %d \n", nrFarmacie);
	for (int i = 0; i < nrFarmacie; i++) {
		afisareFarmacie(vectorFarmacii[i]);
	}

}

void main() {

	Farmacie farmacia1;
	Farmacie farmacia2;
	Farmacie farmacia3;
	Farmacie farmacia4;

	float salariu[] = { 3441.4,3000,4000 };
	float salariu1[] = { 3000,4000,3500,3700 };

	farmacia1 = initializareFarmacie("Tei", 3, salariu, 2018);
	farmacia2 = initializareFarmacie("Dona", 3, salariu, 2020);
	farmacia3 = initializareFarmacie("Catena", 4, salariu1, 2019);
	farmacia4 = initializareFarmacie("Dr. Max", 3, salariu, 2018);
	afisareFarmacie(farmacia1);
	afisareFarmacie(farmacia2);
	afisareFarmacie(farmacia3);
	afisareFarmacie(farmacia4);

	//farmacie copie;
	Farmacie farmacia5;
	farmacia5 = copieFarmacie(farmacia1);
	afisareFarmacie(farmacia5);
	
	printf("-------------\nVector de farmacii\n");
	//vector farmacii
	Farmacie* farmacii=NULL;
	int nrFarmacii = 0;
	farmacii = adaugareFarmacieInVector(farmacii,farmacia1,&nrFarmacii);
	farmacii = adaugareFarmacieInVector(farmacii,farmacia2,&nrFarmacii);
	farmacii = adaugareFarmacieInVector(farmacii,farmacia3,&nrFarmacii);
	farmacii = adaugareFarmacieInVector(farmacii,farmacia4,&nrFarmacii);
	farmacii = adaugareFarmacieInVector(farmacii, farmacia5,&nrFarmacii);

	//afisare vector farmacii
	for (int i = 0; i < nrFarmacii; i++) {
		afisareFarmacie(farmacii[i]);
	}

	printf("-------------\nCitire farmacii din fisier\n");
	//vector de farmacii citit din fisier
	struct Farmacie* vectorFarmacii;
	int numarFarmacii;
	vectorFarmacii = citireVectorFisier("Farmacie.txt", &numarFarmacii);
	afisareVectorFarmacie(vectorFarmacii, numarFarmacii);


	//dezalocare memorie
	for (int j = 0; j < nrFarmacii; j++)
	{
		free(farmacii[j].denumire);
		free(farmacii[j].salariu);
	}
	free(farmacii);

	for (int j = 0; j < numarFarmacii; j++)
	{
		free(vectorFarmacii[j].denumire);
		free(vectorFarmacii[j].salariu);
	}
	free(vectorFarmacii);

	free(farmacia1.salariu);
	free(farmacia1.denumire);
	free(farmacia2.salariu);
	free(farmacia2.denumire);
	free(farmacia3.salariu);
	free(farmacia3.denumire);
	free(farmacia4.salariu);
	free(farmacia4.denumire);
	free(farmacia5.salariu);
	free(farmacia5.denumire);

}
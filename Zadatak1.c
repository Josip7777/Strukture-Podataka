
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX_DULJINA (50)


typedef struct {
	char ime[MAX_DULJINA];
	char prezime[MAX_DULJINA];
	float bodovi;
	float rel_bodovi;
} student;

float NadiRandomBodove() {
	float max = 100, min = 1;
	float ocjena = ((max - min) * ((float)rand() / RAND_MAX)) + min;

	return ocjena;
}

float NadiMaxBodova(student* stud, int n) {
	float maxBodovi = 0;
	for (int i = 0; i < n; i++) {
		if (maxBodovi < stud[i].bodovi) {
			maxBodovi = stud[i].bodovi;
		}
	}

	return  maxBodovi;
}

float nadiRelativnoBodove(student stud, float maxBodovi) {
	float rel_bodovi = (stud.bodovi / maxBodovi) * 100;
	return rel_bodovi;
}

int nadiBrojStudenata(char dat[]) {
	srand(time(NULL));

	int brojac = 0;
	char ch = "";
	FILE* f = NULL;

	f = fopen(dat, "r");
	if (f == NULL) {
		printf("Greska pri ucitavanju datoteke!");
		return -1;
	}

	while (!feof(f)) {
		ch = fgetc(f);

		if (ch == '\n' || ch == EOF) {
			brojac++;
		}
	}

	fclose(f);
	return brojac;
}

student* nadiStudente(int n, char dat[]) {
	student* pom;
	FILE* f = NULL;
	pom = (student*)malloc(n * sizeof(student));

	f = fopen(dat, "r");
	if (f == NULL) {
		printf("Greska pri ucitavanju datoteke!");
		return -1;
	}

	for (int i = 0; i < n; i++) {
		fscanf(f, " %s %s", pom[i].ime, pom[i].prezime);
		pom[i].bodovi = NadiRandomBodove();

	}
	fclose(f);
	return pom;
}

int printStudent(student* stud, int brojac) {
	float maxBodovi = NadiMaxBodova(stud, brojac);

	printf("Broj studenata je %d.\n\n", brojac);
	printf("IME\t PREZIME\t OCJENA APSOLUTNO\t OCJENA RELATIVNO\n");

	for (int i = 0; i < brojac; i++) {
		stud[i].rel_bodovi = nadiRelativnoBodove(stud[i], maxBodovi);
		printf("%s\t %s\t %6.0f%%\t %18.0f%%\n", stud[i].ime, stud[i].prezime, stud[i].bodovi, stud[i].rel_bodovi);
	}

	return 0;
}

int main() {

	int brojac = 0;
	int isPrinted = 0;
	char ch = "";
	char dat[MAX_DULJINA] = "studenti.txt";

	student* stud = NULL;

	brojac = NadiBrojStudenata(dat);

	stud = NadiStudente(brojac, dat);

	isPrinted = printStudent(stud, brojac);

	free(stud);

	return isPrinted;
}
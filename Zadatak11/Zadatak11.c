#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define max (60)
#define hashSize 11

struct _lista;
typedef struct _lista* ListaPozicija;
struct _tablica;
typedef struct _tablica* hashTab;
struct _stablo;
typedef struct _stablo* StabloPozicija;

typedef struct _stablo
{
	char grad[max];
	int stanovnici;
	StabloPozicija L;
	StabloPozicija D;

}stablo;

typedef struct _lista
{
	char drzava[max];

	StabloPozicija stablo;
	ListaPozicija next;
}lista;

typedef struct _tablica
{
	ListaPozicija* hashListe;
}tablica;

int ProcitajDatDrzave(hashTab H, char* dat);
int SortiraniUnosListe(ListaPozicija p, char* drzava_ime, char* drzava_dat);
StabloPozicija NapraviStablo(StabloPozicija root, char* grad, int stanovnici);
int print(ListaPozicija p);
int inorder(StabloPozicija S);
int InorderIspisVeceOd(StabloPozicija p, int broj);
ListaPozicija StvoriElementListe(ListaPozicija p);
ListaPozicija StvoriElementListeAlokacija();
ListaPozicija PronadiDrzavu(hashTab H, char* drzava);
StabloPozicija ProcitajDatGradovi(StabloPozicija root, char* drzava_dat);

hashTab InicijalizirajHashTab();
int DodajUTablicu(char* drzava, char* drzava_dat, hashTab H);
int Preslikavanje(char* drzava);


int main()
{
	ListaPozicija  p = NULL;
	hashTab HashTab = NULL;
	char dat[max] = "drzave.txt", c = { 0 }, drzava[max] = { 0 };
	int x = 1, broj = 0;

	HashTab = InicijalizirajHashTab();
	p = StvoriElementListe(p);

	ProcitajDatDrzave(HashTab, dat);
	
	printf("\n1)Biraj drzavu\n2)Izlaz iz petlje\n");
	while (x)
	{
		scanf(" %c", &c);
		switch (c)
		{
		case '1':
			printf("Odaberi drzavu:");
			scanf(" %s", drzava);
			p = PronadiDrzavu(HashTab, drzava);
			if (p == NULL)
			{
				printf("Odabrana drzava nije unesena u file.");
				return -5;
			}
			printf("\nPrikazat ce se gradovi s brojem stanovnika vecim nego uneseni.Unesi broj:");
			scanf("%d", &broj);
			InorderIspisVeceOd(p->stablo, broj);
			break;
		case '2':
			printf("Izlazak iz petlje.\n");
			x = 0;
			break;
		}
	}
	return 0;
}

hashTab InicijalizirajHashTab()
{
	hashTab H=NULL;
	int i=0;

	H = (hashTab)malloc(sizeof(tablica));
	if (H == NULL)
	{
		printf("Greska kod inicijalizacije hash tablice.\n");
		return NULL;
	}

	H->hashListe = (ListaPozicija*)malloc(sizeof(ListaPozicija) * hashSize);
	if (H->hashListe == NULL)
	{
		printf("Greska kod inicijalizecije hash tablice.\n");
		return NULL;
	}

	for (i = 0;i < hashSize;i++)
		H->hashListe[i] = StvoriElementListeAlokacija();

	return H;
}

int DodajUTablicu(char* drzava,char *drzava_dat, hashTab H)
{
	int indeks = 0;
	indeks = Preslikavanje(drzava);

	SortiraniUnosListe(H->hashListe[indeks], drzava, drzava_dat);

	return 0;
}

int Preslikavanje(char* drzava)
{
	int duljina = 0, ostatak=0, suma=0, i=0;
	duljina = strlen(drzava);

	for (i = 0; i < duljina || i < 5; i++) 
		suma += drzava[i];
	
	ostatak = suma % hashSize;

	return ostatak;
}

ListaPozicija StvoriElementListe(ListaPozicija p)
{
	p = (ListaPozicija)malloc(sizeof(lista));
	if (p == NULL)
	{
		printf("Greska pri alokaciji memorije head elementa.");
		return -3;
	}
	strcpy(p->drzava, "");
	p->next = NULL;
	p->stablo = NULL;

	return p;
}

ListaPozicija StvoriElementListeAlokacija()
{
	ListaPozicija p = NULL;
	p = (ListaPozicija)malloc(sizeof(lista));
	if (p == NULL)
	{
		printf("Greska pri alokaciji memorije elementa.");
		return NULL;
	}
	strcpy(p->drzava, "");
	p->next = NULL;
	p->stablo = NULL;

	return p;
}

int ProcitajDatDrzave(hashTab H, char* dat)
{
	FILE* file = NULL;
	char drzava_ime[max] = { 0 }, drzava_dat[max] = { 0 };

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s\n", drzava_ime, drzava_dat);
		DodajUTablicu(drzava_ime, drzava_dat, H);
	}

	fclose(file);
	return 0;
}

int SortiraniUnosListe(ListaPozicija p, char* drzava_ime, char* drzava_dat)
{
	ListaPozicija q = NULL;
	char pom[max] = { 0 };

	q = (ListaPozicija)malloc(sizeof(lista));
	if (q == NULL)
	{
		printf("Greska pri alokaciji memorije.");
		return -2;
	}

	strcpy(q->drzava, drzava_ime);
	q->stablo = NULL;
	q->stablo = ProcitajDatGradovi(q->stablo, drzava_dat);
	strcpy(pom, drzava_ime);

	while (p != NULL)
	{
		if (p->next == NULL)
		{
			p->next = q;
			q->next = NULL;
			break;
		}
		else if (strcmp(pom, p->next->drzava) < 0)
		{
			q->next = p->next;
			p->next = q;
			break;
		}
		p = p->next;
	}
	return 0;
}
StabloPozicija ProcitajDatGradovi(StabloPozicija root, char* drzava_dat)
{
	FILE* file = NULL;
	char grad[max] = { 0 };
	int stanovnici = 0;

	file = fopen(drzava_dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %d\n", grad, &stanovnici);
		root = NapraviStablo(root, grad, stanovnici);
	}
	fclose(file);
	return root;
}
StabloPozicija NapraviStablo(StabloPozicija S, char* grad, int stanovnici)
{
	if (S == NULL)
	{
		S = (StabloPozicija)malloc(sizeof(stablo));
		if (S == NULL)
		{
			printf("Greska pri alokaciji memorije");
			return NULL;
		}
		strcpy(S->grad, grad);
		S->stanovnici = stanovnici;
		S->L = NULL;
		S->D = NULL;
	}
	else if (stanovnici == S->stanovnici)
	{
		if (strcmp(grad, S->grad) < 0)
			S->L = NapraviStablo(S->L, grad, stanovnici);
		else if (strcmp(grad, S->grad) > 0)
			S->D = NapraviStablo(S->D, grad, stanovnici);
	}
	else
	{
		if (stanovnici < S->stanovnici)
			S->L = NapraviStablo(S->L, grad, stanovnici);
		else if (stanovnici > S->stanovnici)
			S->D = NapraviStablo(S->D, grad, stanovnici);
	}
	return S;
}
int print(ListaPozicija p)
{
	while (p != NULL)
	{
		printf("\n%s:\n", p->drzava);
		inorder(p->stablo);
		p = p->next;
	}
}
int inorder(StabloPozicija S)
{
	if (S == NULL)
		return 0;

	inorder(S->L);
	printf(" %s-%d ", S->grad, S->stanovnici);
	inorder(S->D);

	return 0;
}
ListaPozicija PronadiDrzavu(hashTab H, char* drzava)
{
	int indeks = 0;
	indeks = Preslikavanje(drzava);
	ListaPozicija p = H->hashListe[indeks];

	while (p->next != NULL) 
	{
		if (strcmp(drzava, p->next->drzava) == 0)
			return p->next;
		else
			p = p->next;
	}
	return NULL;
}
int InorderIspisVeceOd(StabloPozicija p, int broj)
{
	if (p == NULL)
		return 0;

	InorderIspisVeceOd(p->L, broj);

	if (broj < p->stanovnici)
		printf("%s %d\n", p->grad, p->stanovnici);

	InorderIspisVeceOd(p->D, broj);

	return 0;
}
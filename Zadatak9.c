#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

struct _cvor;
typedef struct _cvor* pozicija;
typedef struct _cvor
{
	int broj;
	pozicija L;
	pozicija D;
}cvor;

struct _lista;
typedef struct _lista* ListaPozicija;
typedef struct _lista
{
	int el;
	ListaPozicija next;
}lista;

int inorder(pozicija S, ListaPozicija head);
pozicija StvoriPrazno(pozicija S);
pozicija insert(pozicija S, int el);
pozicija replace(pozicija S);
int suma(pozicija S);
pozicija random(pozicija S);
int UmetniNaKraj(ListaPozicija head, int broj);
ListaPozicija PronadiZadnji(ListaPozicija head);
int umetni(ListaPozicija head, int broj);
int ispis_liste_u_file(ListaPozicija p1, ListaPozicija p2, ListaPozicija p3, char* dat);

int main()
{
	pozicija root = NULL;
	ListaPozicija head1 = NULL, head2 = NULL, head3 = NULL;
	char ime[50] = "vjezba9_stablo.txt";

	root = StvoriPrazno(root);
	head1 = (ListaPozicija)malloc(sizeof(lista));
	head1->next = NULL;
	head2 = (ListaPozicija)malloc(sizeof(lista));
	head2->next = NULL;
	head3 = (ListaPozicija)malloc(sizeof(lista));
	head3->next = NULL;

	root = insert(root, 2);
	root = insert(root, 5);
	root = insert(root, 7);
	root = insert(root, 8);
	root = insert(root, 11);
	root = insert(root, 1);
	root = insert(root, 4);
	root = insert(root, 2);
	root = insert(root, 3);
	root = insert(root, 7);
	inorder(root, head1);

	root = replace(root);
	inorder(root, head2);

	root = StvoriPrazno(root);
	root = random(root);
	inorder(root, head3);
	ispis_liste_u_file(head1->next, head2->next, head3->next, ime);

	return 0;
}

pozicija StvoriPrazno(pozicija S)
{
	if (S != NULL)
	{
		S->L = StvoriPrazno(S->L);
		S->D = StvoriPrazno(S->D);
		free(S);
	}
	return NULL;
}

int inorder(pozicija S, ListaPozicija head)
{
	if (S == NULL)
		return 0;

	inorder(S->L, head);
	UmetniNaKraj(head, S->broj);
	inorder(S->D, head);

	return 0;
}

pozicija insert(pozicija S, int el)
{
	if (S == NULL)
	{
		S = (pozicija)malloc(sizeof(cvor));
		S->broj = el;
		S->L = NULL;
		S->D = NULL;
	}
	else if (el >= S->broj)
	{
		S->L = insert(S->L, el);
	}
	else if (el <= S->broj)
	{
		S->D = insert(S->D, el);
	}

	return S;
}

int suma(pozicija S)
{
	int suma1 = 0;
	if (S == NULL)
		return suma1;
	if (S->L != NULL)
		suma1 += S->L->broj + suma(S->L);
	if (S->D != NULL)
		suma1 += S->D->broj + suma(S->D);

	return suma1;
}
pozicija replace(pozicija S)
{
	if (S != NULL)
	{
		S->broj = suma(S);
		S->L = replace(S->L);
		S->D = replace(S->D);
	}
	return S;
}

pozicija random(pozicija S)
{
	int i = 0, broj = 0;

	srand(time(NULL));
	for (i = 0;i < 10;i++)
	{
		broj = (rand() % (90 - 10 + 1)) + 10;
		S = insert(S, broj);
	}

	return S;
}

int UmetniNaKraj(ListaPozicija head, int broj)
{
	ListaPozicija zadnji = NULL;
	zadnji = PronadiZadnji(head);
	umetni(zadnji, broj);
	return 0;
}

ListaPozicija PronadiZadnji(ListaPozicija head)
{
	while (head->next != NULL)
		head = head->next;

	return head;
}

int umetni(ListaPozicija head, int broj)
{
	ListaPozicija prvi = NULL;
	prvi = (ListaPozicija)malloc(sizeof(lista));

	if (prvi == NULL)
		return -1;
	prvi->el = broj;
	prvi->next = head->next;
	head->next = prvi;

	return 0;
}

int ispis_liste_u_file(ListaPozicija p1, ListaPozicija p2, ListaPozicija p3, char* dat)
{
	FILE* f = NULL;
	f = fopen(dat, "w");
	if (f == NULL)
	{
		printf("Neuspjesno otvaranje datoteke!");
		return -1;
	}


	while (p1 != NULL)
	{
		fprintf(f,"%d\t", p1->el);
		p1 = p1->next;
	}
	fprintf(f,"\n");
	while (p2 != NULL)
	{
		fprintf(f, "%d\t", p2->el);
		p2 = p2->next;
	}
	fprintf(f, "\n");
	while (p3 != NULL)
	{
		fprintf(f, "%d\t", p3->el);
		p3 = p3->next;
	}


	fclose(f);
	return 0;
}
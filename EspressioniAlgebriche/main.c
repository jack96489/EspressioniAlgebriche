#include <stdio.h>
#include <stdlib.h>
#include "calcolatrice.h"

Espressione inputEspressione(FILE* stream);
void stampa(Espressione e);

int main()
{
	Espressione e = inputEspressione(stdin);
	stampa(e);
	return 0;
}


Espressione inputEspressione(FILE* stream)
{
	Espressione espressione = NULL;
	Elemento* coda = NULL;
	char str[100];

	fgets(str, 100, stream);

	char* info = str;
	while (info[0] != '\0' && info[0] != '\n')
	{
		Elemento* nodo = malloc(sizeof(Elemento));
		nodo->prox = NULL;
		if (info[0] == '(')
		{
			nodo->tipo = parAperta;
			info++;
		}
		else if (info[0] == ')')
		{
			nodo->tipo = parChiusa;
			info++;
		}
		else if (info[0] == '+' || info[0] == '-' || info[0] == '*' || info[0] == '/')
		{
			nodo->tipo = operatore;
			nodo->op = info[0];
			info++;
		}
		else
		{
			float num = strtof(info, &info);
			nodo->tipo = numero;
			nodo->val = num;
		}

		if (espressione == NULL) {
			espressione = nodo;
			coda = nodo;
		}
		else
		{
			coda->prox = nodo;
			coda = nodo;
		}
	}

	return espressione;
}


void stampa(Espressione e) {
	while (e != NULL)
	{
		switch (e->tipo)
		{
		case parAperta:
			printf("(");
			break;
		case parChiusa:
			printf(")");
			break;
		case operatore:
			printf("%c", e->op);
			break;
		case numero:
			printf("%g", e->val);
		default:
			break;
		}
		e = e->prox;
	}
}

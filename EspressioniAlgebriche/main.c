#include <stdio.h>
#include "calcolatrice.h"

Espressione inputEspressione(FILE* stream);
void stampa(Espressione e);

int main()
{
	FILE* stream;
	Espressione e;
	int scelta;
	char filename[50];

	do
	{
		printf("Premere\n[1] per digitare un espressione\n[2] per leggere l'espressione da un file\n[0] per uscire\n");
		scanf("%d%*c", &scelta);

		switch (scelta)
		{
		case 1:
			printf("Digita l'espressione: ");
			e = inputEspressione(stdin);
			stampa(e);
			printf("=%g\n", valutaEspressione(e));
			break;

		case 2:
			printf("Inserisci il nome del file: ");
			scanf("%s", &filename);
			stream = fopen(filename, "r");
			e = inputEspressione(stream);

			if (e)
			{
				stampa(e);
				printf("=%g\n", valutaEspressione(e));
				fclose(stream);
			}
			else 
			{
				perror("Errore lettura file");
			}

			break;

		default:
			break;
		}

		system("pause");
		system("cls");
	} while (scelta != 0);


	return 0;
}

/**
 * @brief Esegue il parsing di un'espressione
 * @param stream: stream da cui leggere
 * @return puntatore all'espressione letta
*/
Espressione inputEspressione(FILE* stream)
{
	Espressione espressione = NULL;
	Elemento* coda = NULL;
	char str[100];

	if (!stream)
		return NULL;

	fgets(str, 100, stream);

	char* info = str;
	while (info[0] != '\0' && info[0] != '\n')
	{
		Elemento* nodo = malloc(sizeof(Elemento));

		if (!nodo)
			exit(EXIT_FAILURE);

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

/**
 * @brief Stampa un'espressione su standard output
 * @param e: espressione da stampare
*/
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


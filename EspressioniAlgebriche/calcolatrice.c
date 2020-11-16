#include "calcolatrice.h"


float calcolaEspressione(Elemento* inizio, Elemento* fine)
{
	float ris;
	float addendo;
	char op;

	//il puntatore inizio sarà spostato alla fine del prodotto
	ris = moltiplica(inizio, &inizio);

	while (inizio->prox && inizio != fine && (inizio->prox->op == '+' || inizio->prox->op == '-')) {
		inizio = inizio->prox;
		op = inizio->op;
		inizio = inizio->prox;

		//il puntatore inizio sarà spostato alla fine del prodotto
		addendo = moltiplica(inizio, &inizio);

		switch (op)
		{
		case '+':
			ris += addendo;
			break;
		case '-':
			ris -= addendo;
			break;
		default:
			exit(EXIT_FAILURE);
		}

	}
	return ris;
}

void sostituisci(Espressione e, Elemento* punt)
{
	Elemento* inizio;
	float ris;


	//se l'espressione è formata solo da numeri
	if (e == punt && e->tipo == numero)
	{
		e = e->prox;
		while (e)
		{
			//se ci sono parentesi non faccio niente (unreachble)
			if (e->tipo == parAperta || e->prox == parChiusa)
			{
				return;
			}
			e = e->prox;
		}

		ris = calcolaEspressione(punt, e);

		punt->val = ris;
		cancella(punt->prox, e);
		punt->prox = NULL;
	}
	else if (punt->tipo == parAperta)
	{
		Elemento* toDelete;
		bool chiusa = false;
		inizio = punt;

		//cerco la prima parentesi chiusa
		while (punt->prox && !chiusa)
		{
			punt = punt->prox;

			//se ci sono altre parentesi aperte non faccio niente
			if (punt->tipo == parAperta)
			{
				return;
			}
			else if (punt->tipo == parChiusa)
			{
				chiusa = true;
			}

		}

		if (chiusa)
		{
			ris = calcolaEspressione(inizio->prox, punt);

			inizio->tipo = numero;
			inizio->val = ris;
			toDelete = inizio->prox;
			inizio->prox = punt->prox;

			cancella(toDelete, punt);
		}
	}

}

float valutaEspressione(Espressione e)
{
	if (!e)
		exit(EXIT_FAILURE);

	//finchè c'è più di un elemento nell'espressione
	while (e->prox) {
		Elemento* ultimaParAperta = NULL;
		bool parentesi = false;
		Elemento* curr = e;

		//Fino alla fine dell'espressione
		while (curr)
		{
			if (curr->tipo == parAperta)
			{
				ultimaParAperta = curr;
				parentesi = true;
			}
			else if (curr->tipo == parChiusa && ultimaParAperta)
			{
				sostituisci(e, ultimaParAperta);
				ultimaParAperta = NULL;
			}
			curr = curr->prox;
		}
		if (!parentesi)
			sostituisci(e, e);
	}
	return e->val;
}

void cancella(Elemento* inizio, Elemento* fine)
{
	Elemento* next;
	while (inizio != fine)
	{
		next = inizio->prox;
		free(inizio);
		inizio = next;
	}
}

float moltiplica(Elemento* inizio, Elemento** fine)
{
	char op;
	float fattore;
	float ris = inizio->val;
	while (inizio->prox && (inizio->prox->op == '*' || inizio->prox->op == '/')) {
		inizio = inizio->prox;
		op = inizio->op;
		inizio = inizio->prox;
		fattore = inizio->val;

		switch (op)
		{
		case '*':
			ris *= fattore;
			break;
		case '/':
			ris /= fattore;
			break;
		default:
			exit(EXIT_FAILURE);
		}
	}

	//imposto il puntatore fine alla fine del prodotto effettuato
	*fine = inizio;

	return ris;
}
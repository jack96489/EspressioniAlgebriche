#include "calcolatrice.h"


float calcolaEspressione(Elemento* inizio, Elemento* fine)
{
	float ris;
	float addendo;
	char op;

	ris = moltiplica(inizio, &inizio);

	while (inizio != fine) {
		inizio = inizio->prox;
		op = inizio->op;
		inizio = inizio->prox;

		addendo = moltiplica(inizio, &inizio);

		switch (op)
		{
		case '+':
			ris += addendo;
			break;
		case '-':
			ris -= addendo;
			break;
		}

	}
	return ris;
}



float moltiplica(Elemento* inizio, Elemento** fine) {
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
		}
	}
	*fine = inizio;
	return ris;
}
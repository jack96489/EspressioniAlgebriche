#pragma once


typedef enum {
	numero,
	operatore,
	parAperta,
	parChiusa
} TipoElemento;

typedef struct El {
	TipoElemento tipo;
	float val;
	char op;
	struct El* prox;
} Elemento;

typedef Elemento* Espressione;


float calcolaEspressione(Elemento* inizio, Elemento* fine);

void sostituisci(Espressione e, Elemento* punt);





float moltiplica(Elemento* inizio, Elemento** fine);


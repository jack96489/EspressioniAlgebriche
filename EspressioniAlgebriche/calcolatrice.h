#pragma once
#include <stdlib.h>

typedef enum {
	false,
	true
} bool;

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

float valutaEspressione(Espressione e);



float moltiplica(Elemento* inizio, Elemento** fine);

void cancella(Elemento* inizio, Elemento* fine);
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

/**
* Calcola il valore di una sottoespressione senza parentesi
* @param inizio: puntatore al primo elemento dell'espressione da calcolare
* @param fine: puntatore all'ultimo elemento dell'espressione da calcolare (escluso)
*/
float calcolaEspressione(Elemento* inizio, Elemento* fine);

/**
* @brief Prova a sostituire un valore numerico a una sottoespressione.
*
* @param e: puntatore all'espressione completa
* @param punt: puntatore al prima elemento della sottoespresione
*
*/

void sostituisci(Espressione e, Elemento* punt);

/**
 * @brief risolve un'espressione
 *
 * @param e: puntatore all'espressione
 * @return valore dell'espressione
*/
float valutaEspressione(Espressione e);


/**
 * @brief Esegue le moltiplicazioni e le divisioni di una sottoespressione
 * @param inizio: puntatore all'inizione della sottoespressione
 * @param fine: puntatore al puntatore che indica la fine della sottoespressione. Viene aggiornato dalla funzione
 * @return Valore della sottoespressione
*/

float moltiplica(Elemento* inizio, Elemento** fine);

/**
 * @brief dealloca una sottoespressione
 * @param inizio: puntatore al primo elemento della lista da deallocare
 * @param fine: puntatore all'ultimo elemento della lista da deallocare
*/

void cancella(Elemento* inizio, Elemento* fine);
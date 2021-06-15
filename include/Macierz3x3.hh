#ifndef MACIERZ3X3_HH
#define MACIERZ3X3_HH


#include "Macierz.hh"

/*!
 *\file
 *\brief Definicja klasy Macierz3x3
 */

/*!
 * \brief Klasa Macierz3x3.
 *
 *  Klasa reprezentuje macierz kwadratowa 3x3, bedąca instancja szablonu Macierz.
 *  Kazda komorka tablicy reprezentuje jedna komorke macierzy, ktore indeksuje 
 *  sie za pomoca operator (). Na macierzy mozna wykonywac podstawowe dzialania z
 *  arytmetyki macierzy, wyswietlac je oraz wczytywac.
 */
typedef Macierz<3>  Macierz3x3;


/*!
 * \brief Metoda sluzaca do generowania macierzy obrotu wokol wybranej osi o zadany kat.
 */
Macierz3x3 MacierzObrotu(double Kat, char Os);



#endif

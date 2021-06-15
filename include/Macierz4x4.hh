#ifndef MACIERZ4X4_HH
#define MACIERZ4X4_HH


#include "Macierz.hh"
#include "Wektor3D.hh"


/*!
 *\file
 *\brief Definicja klasy Macierz4x4
 */

/*!
 *\brief Klasa Macierz4x4 jest instancja szablonu klasy Macierz. Modeluja ona Macierz 4x4.
 * Kazda komorka tablicy bedacej jej atrybutem reprezentuje jedna komorke macierzy. Na
 * macierzy mozna wykonywac podstawowe dzialania arytmetyczne oraz ja wyswietlac.
 * Dodatkowo macierz4x4 mozna przeksztalcic na macierz obrotu i przesuniecia.
 */
typedef Macierz<4> Macierz4x4;


#endif
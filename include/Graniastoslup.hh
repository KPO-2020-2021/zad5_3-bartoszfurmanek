#ifndef GRANIASTOSLUP_HH
#define GRANIASTOSLUP_HH

#include <iostream>
#include "Wektor3D.hh"
#include "Wektor.hh"
#include "Macierz3x3.hh"
#include "Macierz.hh"
#include "BrylaGeometryczna.hh"
#include <tgmath.h>
#include <math.h>
#include <iomanip>
#include <fstream>



/*!
 *\file
 *\brief Definicja klasy Graniastoslup.
 */

/*!
 * \brief Klasa Graniastoslup.
 *
 * Klasa reprezentucja granistoslup szesciokatny prawidlowy. 
 * Jego punkty sa reprezentowane przez tablice wektorow 3D, gdzie jeden 
 * wektor to dany punkt. Prostopadloscian posiada zmienna informujaca 
 * o jego polozniu, oraz o koncie orietnacji wzgledem osi Z. 
 * Prostopadloscian mozna przesuwac oraz obracac. Kazdy prostopadloscian 
 * posiada plik ze wspolrzednymi bryly, dostosowanych do rysowania w gnuplocie.
 */
class Graniastoslup: public BrylaGeometryczna {

/*!
 * \brief Wierzcholki
 *
 * Atrybut modeluje 12 wierzcholkow prostopadloscianu oraz 12 dodatkowych
 * punktow, ktore sluza do rysowania scian prostopadloscianu
 * w gnuplocie. Wierzcholki i punkty sa przedstawione w formie tablicy
 * wektorow3D. Elementy o indeksach 1,2,5,6,9,10,13,14,17,18,21,22 reczywistymi wierzcholkami
 * prostopadloscianu, pozostale elemnty to punkty dodatkowe wspomagajace rysowanie scian
 * w gnuplocie.
 *
 */
  Wektor3D Wierzcholek[24];

/*!
 * \brief Polozenie
 *
 * Atrybut modeluje wspolrzedne polozenia graniastoslupa.
 * Za wspolrzedne polozenia przyjmujemy srodek podstawy danego graniastoslupa.
 *
 */
  Wektor3D Polozenie;

/*!
 * \brief Kat orientacji
 *
 * Atrybut modeluje kat orientacyjny graniastoslupa
 *
 */
  double KatOrientacji;

  public:

/*!
 * \brief Operator przypisania dla Graniastoslup
 */
  Graniastoslup& operator= (const Graniastoslup G);

/*!
 * \brief Indeksowanie wspolrzednych graniastoslupa.
 */
  Wektor3D operator[](int Indeks)const;

/*!
 * \brief Indeksowanie wspolrzednych graniastoslupa.
 */
  Wektor3D& operator[](int Indeks);

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia graniastoslupa.
 */
  Wektor3D WspolPolozenia()const;

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia graniastoslupa.
 */
  Wektor3D& WspolPolozenia();

/*!
 * \brief Uzyskiwanie katu orientacji graniastoslupa.
 */
  double Orientacja()const;

/*!
 * \brief Uzyskiwanie katu orientacji polozenia graniastoslupa.
 */
  double& Orientacja();


/*!
 * \brief Obliczenie wspolrzednych polozenia prostopadloscianu.
 */
  void ObliczPolozenie();

/*!
 * \brief Konstruktor bezparametryczny.
 */
  Graniastoslup();

/*!
 * \brief Konstruktor parametryczny.
 */
  Graniastoslup(Wektor3D WspolPolozenia, double Kat, std::string NazwaBryly, std::string NazwaWzorca, Wektor3D SkalaBryly);

/*!
 * \brief Konstruktor kopiujacy.
 */
  Graniastoslup(const Graniastoslup &G);

/*!
 * \brief Przeciazenie operatora porownania dla graniastoslupa.
 */
  bool operator ==(Graniastoslup Gr)const;

/*!
 * \brief Metoda sluzaca do obracania graniastoslupa o zadany kat wokol wybranej osi.
 */
  Graniastoslup& Obrot(double Kat, char Os);

/*!
 * \brief Metoda sluzaca do przesuwania graniastoslupa o zadany wektor.
 */
  Graniastoslup& Translacja(Wektor3D Wektor);

/*!
 * \brief Metoda sprowadzajaca graniastoslup do wlasnego ukladu wspolrzednych.
 */
  void TransformujDoUkladuRodzica();

/*!
 * \brief Metoda sprowadzajaca graniastoslup do globalnego ukladu wspolrzednych.
 */
  void TransformujDoUkladuGlobalnego();

/*!
 * \brief Zapis wspolrzednych do strumienia.
 */
  void ZapisWspolrzednychDoStrumienia(std::ostream &StrmWy)const;

/*!
 * \brief Odczyt wspolrzednych ze strumienia.
 */
  void OdczytWspolrzednychDoStrumienia(std::istream &StrmWej);

/*!
 * \brief Metoda zapisuje wspolrzedne graniastoslupa do pliku
 */
  bool ZapiszBryle()const;

/*!
 * \brief Metoda odczytuje wspolrzedne graniastloslupa z pliku ze wzorcem bryly.
 */
  bool OdczytajBryleWzorcowa();

/*!
 *\brief Metoda zastepuje wspolrzedne, wspolrzednymi wzorca (Odpowiednio obrocony i przesuniety).
 */
  bool UzyjWzorca();


};

/*!
 * \brief Metoda sluzaca do przekazywania do strumienia wierzcholkow graniastoslupa.
 */
std::ostream& operator << (std::ostream &Strm, const Graniastoslup &Gr);





#endif

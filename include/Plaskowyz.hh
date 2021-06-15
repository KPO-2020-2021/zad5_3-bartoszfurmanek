#ifndef PLASKOWYZ_HH
#define PLASKOWYZ_HH

#include <iostream>
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include "BrylaGeometryczna.hh"
#include <iomanip>
#include <fstream>
#include "ObiektSceny.hh"


/*!
 *\file
 *\brief Definicja klasy Plaskowyz.
 */

/*!
 * \brief Klasa Plaskowyz.
 *
 * Klasa reprezentucja plaskowyz, ktory jest swojego rodzaju prostopadloscianem. 
 * Jego punkty sa reprezentowane przez tablice wektorow 3D, gdzie jeden wektor to dany punkt.
 * Plaskowyz posiada zmienna informujaca o jego polozniu, oraz o koncie orietnacji
 * wzgledem osi Z. Plaskowyz mozna przesuwac oraz obracac. Kazda
 * bryla posiada plik ze wspolrzednymi bryly, dostosowanych
 * do rysowania w gnuplocie. Klasa dziedziczy po klasie BrylaGeometryczna.
 *
 */
class Plaskowyz: public BrylaGeometryczna, public ObiektSceny{

/*!
 * \brief Wierzcholki
 *
 * Atrybut modeluje 8 wierzcholkow prostopadloscianu (plaskowyzu) oraz 8 dodatkowych
 * punktow, ktore sluza do rysowania scian prostopadloscianu
 * w gnuplocie. Wierzcholki i punkty sa przedstawione w formie tablicy
 * wektorow3D. Elementy o indeksach 1,2,5,6,9,10,13,14 reczywistymi wierzcholkami
 * prostopadloscianu, pozostale elemnty to punkty dodatkowe
 *
 */
Wektor3D Wierzcholek[16];

/*!
 * \brief Polozenie
 *
 * Atrybut modeluje wektor3D, bedacy wspolrzednymi polozenia plaskowyzu.
 * Za jego polozenie przyjmuje sie geometryczny srodek jego podstawy.
 */
Wektor3D Polozenie;

/*!
 * \brief KatOrientacji
 *
 * Atrubut modeluje kat obrotu bryly wzgledem wlasnej osi Z.
 */
double KatOrientacji;

public:

/*!
 * \brief Operator przypisania dla Plaskowyzu.
 */
  Plaskowyz& operator= (const Plaskowyz P);

/*!
 * \brief Indeksowanie wierzcholkow Plaskowyzu.
 */
  Wektor3D operator[](int Indeks)const;

/*!
 * \brief Indeksowanie wierzcholkow Plaskowyzu.
 */
  Wektor3D& operator[](int Indeks);

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia Plaskowyzu.
 */
  Wektor3D WspolPolozenia()const;

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia Plaskowyzu.
 */
  Wektor3D& WspolPolozenia();

/*!
 * \brief Uzyskiwanie katu orientacji Plaskowyzu.
 */
  double Orientacja()const;

/*!
 * \brief Uzyskiwanie katu orientacji polozenia Plaskowyzu.
 */
  double& Orientacja();

  /*!
 * \brief Obliczenie wspolrzednych polozenia Plaskowyzu.
 */
  void ObliczPolozenie();

  /*!
 * \brief Konstruktor bezparametryczny.
 */
  Plaskowyz();

/*!
 * \brief Konstruktor parametryczny.
 */
  Plaskowyz(Wektor3D WspolPolozenia, double Kat, std::string Nazwa, std::string NazwaWzorca, Wektor3D SkalaBryly);

/*!
 * \brief Konstruktor kopiujacy.
 */
  Plaskowyz(const Plaskowyz &P);

  /*!
 * \brief Metoda sluzaca do obracania plaskowyzu o zadany kat wokol wybranej osi.
 */
  Plaskowyz& Obrot(double Kat, char Os);

/*!
 * \brief Metoda sluzaca do przesuwania plaskowyzu o zadany wektor.
 */
  Plaskowyz& Translacja(Wektor3D Wektor);

/*!
 * \brief Zapis wspolrzednych plaskowyzu do strumienia.
 */
  void ZapisWspolrzednychDoStrumienia(std::ostream &StrmWy)const;

/*!
 * \brief Odczyt wspolrzednych plaskowyzu ze strumienia.
 */
  void OdczytWspolrzednychDoStrumienia(std::istream &StrmWej);

/*!
 * \brief Metoda zapisuje wspolrzedne plaskowyzu do pliku
 */
  bool ZapiszBryle()const;

/*!
 * \brief Metoda odczytuje wspolrzedne plaskowyzu z pliku ze wzorcem prostopadloscianu.
 */
  bool OdczytajBryleWzorcowa();

/*!
 *\brief Metoda zwracajaca nazwe wybranej bryly obiektu sceny.
 */
  std::string WezNazweBryly(int NumerBryly)const;


};

#endif
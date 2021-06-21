#ifndef GORAZESZCZYTEM_HH
#define GORAZESZYCZTEM_HH

#include <iostream>
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include "BrylaGeometryczna.hh"
#include <iomanip>
#include <fstream>
#include "ObiektSceny.hh"


/*!
 *\file
 *\brief Definicja klasy GoraZeSzczytem.
 */

/*!
 * \brief Klasa GoraZeSzczytem.
 *
 * Klasa reprezentucja gore ze szczytem, ktora jest swojego rodzaju przeksztalceniem klasy prostopadloscian. 
 * Jego punkty sa reprezentowane przez tablice wektorow 3D, gdzie jeden wektor to dany punkt.
 * Gora posiada zmienna informujaca o jego polozniu, oraz o koncie orietnacji
 * wzgledem osi Z. Gora mozna przesuwac oraz obracac. Kazda bryla
 * posiada plik ze wspolrzednymi bryly, dostosowanych  do rysowania w gnuplocie.
 * Klasa dziedziczy po klasie BrylaGeometryczna.
 *
 */
class GoraZeSzczytem: public BrylaGeometryczna, public ObiektSceny{

/*!
 * \brief Wierzcholki
 *
 * Atrybut modeluje 8 wierzcholkow prostopadloscianu (gory ze szczytem) oraz 8 dodatkowych
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
 * Atrybut modeluje wektor3D, bedacy wspolrzednymi polozenia gory.
 * Za jego polozenie przyjmuje sie geometryczny srodek jego podstawy.
 */
Wektor3D Polozenie;

/*!
 * \brief KatOrientacji
 *
 * Atrubut modeluje kat obrotu gory wzgledem wlasnej osi Z.
 */
double KatOrientacji;

public:

/*!
 * \brief Operator przypisania dla gory ze szczytem.
 */
  GoraZeSzczytem& operator= (const GoraZeSzczytem G);

/*!
 * \brief Indeksowanie wierzcholkow gory ze szczytem.
 */
  Wektor3D operator[](int Indeks)const;

/*!
 * \brief Indeksowanie wierzcholkow gory ze szczytem.
 */
  Wektor3D& operator[](int Indeks);

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia gory ze szczytem.
 */
  Wektor3D WspolPolozenia()const;

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia gory ze szczytem.
 */
  Wektor3D& WspolPolozenia();

/*!
 * \brief Uzyskiwanie katu orientacji gory zze szczytem.
 */
  double Orientacja()const;

/*!
 * \brief Uzyskiwanie katu orientacji polozenia gory ze szczytem.
 */
  double& Orientacja();

  /*!
 * \brief Obliczenie wspolrzednych polozenia gory ze szczytem.
 */
  void ObliczPolozenie();

  /*!
 * \brief Konstruktor bezparametryczny.
 */
  GoraZeSzczytem();

/*!
 * \brief Konstruktor parametryczny.
 */
  GoraZeSzczytem(Wektor3D WspolPolozenia, double Kat, std::string Nazwa, std::string NazwaWzorca, Wektor3D SkalaBryly);

/*!
 * \brief Konstruktor kopiujacy.
 */
  GoraZeSzczytem(const GoraZeSzczytem &G);

  /*!
 * \brief Metoda sluzaca do obracania gory ze szczytem o zadany kat wokol osi z.
 */
  GoraZeSzczytem& Obrot(double Kat);

/*!
 * \brief Metoda sluzaca do przesuwania gory ze szczytem o zadany wektor.
 */
  GoraZeSzczytem& Translacja(Wektor3D Wektor);

/*!
 * \brief Zapis wspolrzednych gory ze szczytem do strumienia.
 */
  void ZapisWspolrzednychDoStrumienia(std::ostream &StrmWy)const;

/*!
 * \brief Odczyt wspolrzednych gory ze szczytem ze strumienia.
 */
  void OdczytWspolrzednychDoStrumienia(std::istream &StrmWej);

/*!
 * \brief Metoda zapisuje wspolrzedne gory ze szczytem do pliku
 */
  bool ZapiszBryle()const;

/*!
 * \brief Metoda odczytuje wspolrzedne gory ze szczytem z pliku ze wzorcem prostopadloscianu.
 */
  bool OdczytajBryleWzorcowa();

/*!
 *\brief Metoda zwracajaca nazwe wybranej bryly obiektu sceny.
 */
  std::string WezNazweBryly(int NumerBryly)const;

/*!
 *\brief Metoda zwracajaca skale bryly.
 */
  Wektor3D WezSkaleBryly()const;



};

#endif
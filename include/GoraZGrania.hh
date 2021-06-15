#ifndef GORAZGRANIA_HH
#define GORAZGRANIA_HH

#include <iostream>
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include "BrylaGeometryczna.hh"
#include <iomanip>
#include <fstream>
#include "ObiektSceny.hh"


/*!
 *\file
 *\brief Definicja klasy GoraZGrania.
 */

/*!
 * \brief Klasa GoraZGrania.
 *
 * Klasa reprezentucja gore z grania, ktora jest swojego rodzaju przeksztalceniem klasy prostopadloscian. 
 * Jego punkty sa reprezentowane przez tablice wektorow 3D, gdzie jeden wektor to dany punkt.
 * Gora posiada zmienna informujaca o jego polozniu, oraz o koncie orietnacji
 * wzgledem osi Z. Gora mozna przesuwac oraz obracac. Kazda bryla
 * posiada plik ze wspolrzednymi bryly, dostosowanych  do rysowania w gnuplocie.
 * Klasa dziedziczy po klasie BrylaGeometryczna.
 *
 */
class GoraZGrania: public BrylaGeometryczna, public ObiektSceny{

/*!
 * \brief Wierzcholki
 *
 * Atrybut modeluje 8 wierzcholkow prostopadloscianu (gory z grania) oraz 8 dodatkowych
 * punktow, ktore sluza do rysowania scian gory z grania Wierzcholki i punkty 
 * sa przedstawione w formie tablicy wektorow3D. Elementy o indeksach 
 * 1,2,5,6,9,10,13,14 reczywistymi wierzcholkami prostopadloscianu, 
 * pozostale elemnty to punkty dodatkowe.
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
 * \brief Operator przypisania dla gory z grania.
 */
  GoraZGrania& operator= (const GoraZGrania G);

/*!
 * \brief Indeksowanie wierzcholkow gory z grania.
 */
  Wektor3D operator[](int Indeks)const;

/*!
 * \brief Indeksowanie wierzcholkow gory z grania.
 */
  Wektor3D& operator[](int Indeks);

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia gory z grania.
 */
  Wektor3D WspolPolozenia()const;

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia gory z grania.
 */
  Wektor3D& WspolPolozenia();

/*!
 * \brief Uzyskiwanie katu orientacji gory z grania.
 */
  double Orientacja()const;

/*!
 * \brief Uzyskiwanie katu orientacji polozenia gory z grania.
 */
  double& Orientacja();

  /*!
 * \brief Obliczenie wspolrzednych polozenia gory z grania.
 */
  void ObliczPolozenie();

  /*!
 * \brief Konstruktor bezparametryczny.
 */
  GoraZGrania();

/*!
 * \brief Konstruktor parametryczny.
 */
  GoraZGrania(Wektor3D WspolPolozenia, double Kat, std::string Nazwa, std::string NazwaWzorca, Wektor3D SkalaBryly);

/*!
 * \brief Konstruktor kopiujacy.
 */
  GoraZGrania(const GoraZGrania &G);

  /*!
 * \brief Metoda sluzaca do obracania gory z grania o zadany kat wokol wybranej osi.
 */
  GoraZGrania& Obrot(double Kat, char Os);

/*!
 * \brief Metoda sluzaca do przesuwania gory z grania o zadany wektor.
 */
  GoraZGrania& Translacja(Wektor3D Wektor);

/*!
 * \brief Zapis wspolrzednych gory z grania do strumienia.
 */
  void ZapisWspolrzednychDoStrumienia(std::ostream &StrmWy)const;

/*!
 * \brief Odczyt wspolrzednych gory z grania ze strumienia.
 */
  void OdczytWspolrzednychDoStrumienia(std::istream &StrmWej);

/*!
 * \brief Metoda zapisuje wspolrzedne gory z grania do pliku
 */
  bool ZapiszBryle()const;

/*!
 * \brief Metoda odczytuje wspolrzedne gory z grania z pliku ze wzorcem prostopadloscianu.
 */
  bool OdczytajBryleWzorcowa();

/*!
 *\brief Metoda zwracajaca nazwe wybranej bryly obiektu sceny.
 */
  std::string WezNazweBryly(int NumerBryly)const;



};

#endif
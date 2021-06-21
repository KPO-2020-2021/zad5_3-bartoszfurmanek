#ifndef OBIEKTSCENY_HH
#define OBIEKTSCENY_HH

#include "lacze_do_gnuplota.hh"
#include "BrylaGeometryczna.hh"

/*!
 *\file
 *\brief Definicja klasy Obiekt Sceny.
 */

/*!
 * \brief Rodzaj obiektu sceny definiowanego przez klase.
 *
 *  Wartości tego typu sa identifykatorami mowiacymi jakiego rodzaju
 *  jest obiekt
 */
enum TypObiektuSceny { 
      OB_Zaden              /*! Nie jest to zaden konkretny obiekt */,  
      OB_Dron               /*! obiekt jest dronem */,
      OB_Plaskowyz          /*! obiekt jest plaskowyzem */,
      OB_GoraZGrania        /*! obiekt jest gora z grania */,
      OB_GoraZeSzczytem      /*! obiekt jest gora ze szczytem */
   };

/*!
 *\brief Denicja klasy Obiekt Sceny.
 *Klasa modeluje pojecie obiektu sceny. Klasa jest baza dla
 *do dziedziczenia dla klas obiektow znajdujacych sie na scenie.
 *Kazdy obiekt klasy, posiada identyfikator mowiacy o tym, jakim
 *typem obiektu jest.
 */
class ObiektSceny{

 private:

/*!
 *\brief Identyfikator typu obiektu sceny.
 */
 const TypObiektuSceny _TypObiektu;

 protected:

/*!
 *\brief Konstruktor parametryczny
 */
 ObiektSceny(TypObiektuSceny Typ = OB_Zaden):
 _TypObiektu(Typ) {}
 
 public:

/*!
 *\brief Metoda udostepniajaca identyfikator obiektu
 *\return Typ obiektu
 */
 TypObiektuSceny TypObiektu()
 {return _TypObiektu;}

/*!
 *\brief Metoda zwracajaca nazwe wybranej bryly obiektu sceny.
 */
 virtual std::string WezNazweBryly(int NumerBryly)const=0;

/*!
 *\brief Metoda zwracajaca polozenie wybranego obiektu.
 */
 virtual Wektor3D WspolPolozenia()const=0;

/*!
 *\brief Metoda zwracajaca kat orientacji wybranego obiektu.
 */
 virtual double Orientacja()const=0;

/*!
 *\brief Metoda przesuwajaca obiekt o zadany wektor.
 */
 virtual ObiektSceny& Translacja(Wektor3D Przesuniecie)=0;

/*!
 *\brief Metoda zwracajaca skale bryly.
 *UWAGA: W przypadku klasy Dron metoda zwraca skale korpusu.
 */
 virtual Wektor3D WezSkaleBryly()const=0;

/*!
 *\brief Metoda sluzaca do indeksowania punktow obiektu.
 *UWAGA: W przypadku klasy dron metoda indeksuje korpus.
 */
 virtual Wektor3D operator[](int Indeks)const=0;




};

#endif
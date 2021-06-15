#ifndef BRYLAGEOMETRYCZNA_HH
#define BRYLAGEOMETRYCZNA_HH

#include <string>
#include "Wektor3D.hh"

/*!
 * \file 
 * \brief Definicja klasy BrylaGeometryczna.
 */


/*!
 * \brief Rodzaj bryly geometrycznej modelowanej przez daną klasę
 *
 *  Wartości tego typu sa identifykatorami mowiacymi jakiego typu jest
 *  dana bryla.
 */
enum TypBrylyGeometrycznej { 
      TB_Zadna              /*! Nie jest to żadna konkretna bryla geometryczna */,  
      TB_Prostopadloscian   /*! Bryla geometryczna jest prostopadlsocianem */,
      TB_Graniastoslup      /*! Bryla geometryczna jest graniastoslupem */,
      TB_Plaskowyz          /*! Bryla geometryczna jest plaskowyzem */,
      TB_GoraZeSzczytem     /*! Bryla geometryczna jest gora z ostrym sczytem */,
      TB_GoraZGrania        /*! Bryla geometryczna jest gora z dluga grania */
   };


/*!
 * \brief Klasa BrylaGeometryczna
 *  Klasa modeluje pojęcie bryly geometrycznej.
 *  Klasa jest baza dla dziedziczenia klas modelujacych bryly geometryczne. 
 *  Kazda bryla posiada nazwe bryly wzorcowej oraz bryly finalnej. 
 *  Dodatkowo kazda bryla posiada identyfikator mowiacy jakiego typu bryla jest.
 */
class BrylaGeometryczna {

/*!
 * \brief Identyfikator rodzaju figury geometrycznej
 */
  const TypBrylyGeometrycznej  _TypBryly;

  protected:

/*!
 * \brief Nazwa pliku przechowujacego wspolrzedne bryly finalnej
 */
  std::string NazwaBryly;

/*!
 * \brief Nazwa pliku przechowujacego wspolrzedne bryly wzorcowej
 */
  std::string NazwaBrylyWzorcowej;

/*!
 * \brief Skala wielkosci bryly geometrycznej
 */
  Wektor3D Skala;

/*!
 * \brief Konstruktor parametryczny dla Bryly Geometrycznej
 * \param[in] Typ - identyfikator typu bryly geoemtrycznej. Domyslnie TB_Zadna
 * \param[in] Nazwa - Nazwa pliku przechowujacego wspolrzedne bryly finalnej. Domyslnie nazwa jest pusta.
 * \param[in] NazwaWzorca - Nazwa pliku przechowujacego wspolrzedne bryly wzorcowej. Domyslnie nazwa jest pusta.
 */
  BrylaGeometryczna(TypBrylyGeometrycznej Typ = TB_Zadna, std::string Nazwa=" ", std::string NazwaWzorca=" ", Wektor3D SkalaBryly={1,1,1}): 
  _TypBryly(Typ), NazwaBryly(Nazwa), NazwaBrylyWzorcowej(NazwaWzorca), Skala(SkalaBryly) {}


  public:

/*!
 * \brief Udostępnia indentyfikator typu bryly geometrycznej
 * \return Identyfikator danej bryly geometrycznej
 */
  TypBrylyGeometrycznej TypBryly()const 
  {return _TypBryly;} 

/*!
 * \brief Udostępnia nazwe pliku przechowujacego wspolrzedne bryly geometrycznej
 * \return Nazwa pliku z wspolrzednymi bryly geometrycznej
 */
  std::string NazwaPlikuBryly()const
  {return NazwaBryly;}

/*!
 * \brief Udostępnia nazwe pliku przechowujacego wspolrzedne wzorcowe bryly geometrycznej
 * \return Nazwa pliku z wspolrzednymi wzorcowymi bryly geometrycznej
 */
  std::string NazwaPlikuBrylyWzorcowej()const
  {return NazwaBrylyWzorcowej;}

/*!
 * \brief Skaluje zadany wektor.
 * \param[in] W - Wektor ktory ma zostac wyskalowany.
 * \return Wyskalowany wektor.
 */
  Wektor3D Skaluj(Wektor3D W)
  {return Wektor3D{W[0]*Skala[0],W[1]*Skala[1],W[2]*Skala[2]};}

/*!
 * \brief Metoda uzyskujaca skale bryly.
 * \return Skala bryly.
 */
  Wektor3D SkalaBryly()const
  {return Skala;}

};



#endif
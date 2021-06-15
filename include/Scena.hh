#ifndef SCENA_HH
#define SCENA_HH

#include "Dron.hh"
#include "Plaskowyz.hh"
#include "GoraZeSzczytem.hh"
#include "GoraZGrania.hh"
#include "lacze_do_gnuplota.hh"
#include <list>
#include <memory>




/*!
 *\file
 *\brief Plik zawiera definicje klasy Scena
 */

/*!
 *\brief Klasa scena
 *Klasa definiuje scene, po ktorej dron bedzie sie przemieszczal w
 *Gnuplocie. Scena sklada sie z dwoch dronow, oraz podloza. 
 *Klasa pozwala na animowane wyswietlanie ruchu drona 
 *na pewnej plaszczyznie.
 */
 class Scena{

/*!
 *\brief Lista obiektow sceny
 * Atrybut jest lista wszystkich obiektow znajdujacych sie na scenie.
 */
 std::list<std::shared_ptr<ObiektSceny>> ListaObiektow;

/*!
 *\brief Lacze do gnuplota.
 *Zmienna sluzy do operowania na gnuplocie w celu wyswietlania
 *w nim sceny.
 */
 PzG::LaczeDoGNUPlota  Lacze;

/*!
 *\brief Numer aktywnego drona.
 *Zmienna informuje o numerze aktywnego drona
 */
 int NrAktywnegoDrona;

 /*!
 *\brief Metoda dodajaca do lacza gnuplot nazwe pliku z rysowana bryla.
 */
 bool DodajNazwePliku(std::string NazwaPliku);

 /*!
 *\brief Metoda usuwajaca nazwe pliku wybranej przeszkody
 */
 void UsunNazwePrzeszkody(std::string const NazwaPlikuPrzeszkody);

 public:

/*!
 *\brief Konstruktor bezparametryczny sceny.
 */
 Scena();

/*!
 *\brief Metoda dodajaca drona do sceny.
 */
 void DodajDrona(Wektor3D Polozenie, double Kat, std::string NazwaDrona);


/*!
 *\brief Metoda uzyskujaca numer aktywnego drona.
 */
 int NumerAktywnegoDrona()const;

/*!
 *\brief Metoda uzyskujaca dostep do numeru aktywnego drona.
 */
 int& NumerAktywnegoDrona();

/*!
 *\brief Metoda uzyskujaca dostep do aktywnego drona.
 */
 Dron* AktywnyDron();

/*!
 *\brief Metoda wypisujaca liste dronow.
 */
 void ListaDronow();

/*!
 *\brief Metoda wypisujaca na strumieniu wyjsciowym liste przeszkod znajdujacych na scenie.
 */
 void ListaPrzeszkod();

/*!
 *\brief Metoda usuwajaca z listy wybrana przeszkode.
 */
 bool UsunPrzeszkode(int NumerPrzeszkody);

/*!
 *\brief Metoda dodawajaca do sceny wybrana przeszkode
 */
 bool DodajPrzeszkode(int NumerPrzeszkody, Wektor3D Polozenie, double Kat, Wektor3D Skala, std::string NazwaPrzeszkody);


/*!
 *\brief Metoda wyswietlajaca w sposob aniomowany obrot aktynwego drona o zadany kat,
 * oraz jego przelot o zadana odleglosc.
 */
 bool PrzemiescDrona(double Odleglosc, double Kat);

/*!
 *\brief Metoda wyswietlajaca w sposob aniomowany ruchh po okregu aktywnego drona.
 */
 bool RuchPoOkregu(double Promien);
 };








#endif
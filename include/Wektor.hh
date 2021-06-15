#ifndef WEKTOR_HH
#define WEKTOR_HH



#include <iostream>
#include <tgmath.h>
#include <math.h>
#include <iomanip>


#define MIN_ROZNICA 0.001

/*!
 * \file
 * \brief Szablon klasy reprezentujacej wektor o dowlonym wymiarze.
 */

/*!
 *\brief Szablon klasy reprezentujacej wektor
 * Szablon klasy reprezentujacej wektor. Szablon pozwala tworzyć
 * wektory o roznych wymiar w zaleznosci o zmiennej Wymiar. Klasa
 * może reprezentować wektor o różnych wymiarach. Wektor można
 * indeksować za pomocą operatora []. Na wektorze mozna wykonywać
 * podstawowe dzialania matematyczne.
 */
template <int Wymiar>
class Wektor {

/*!
 * \brief Wektor
 *
 * Atrybut modeluje wektor o danym wymiarze, kazdy element tablicy
 * symbolizuje jedna skladowa wektora.
 *
 */
  double Elem[Wymiar];

  static int IloscAktualna;
  static int IloscOgolna;

  public:

/*!
 * \brief Indeksowanie wektora
 */
  double operator[](int Indeks)const;

/*!
 * \brief Indeksowanie wektora
 */
  double& operator[](int Indeks);

/*!
 * \brief Metoda zwracajaca aktualna ilosc wektorow
 */
  static int WezIloscAktualna()
  {return IloscAktualna;}

/*!
 * \brief Metoda zwracajaca ogolna ilosc wektorow
 */
  static int WezIloscOgolna()
  {return IloscOgolna;}

/*!
 * \brief Konstruktor bezparametryczny dla wektora
 */
  Wektor();

/*!
 * \brief Konstruktor parametryczny dla wektora
 */
  Wektor(const std::initializer_list<double> &ListaElem);

/*!
 * \brief Konstruktor kopiujacy dla wektora
 */
  Wektor(const Wektor &W);

/*!
 * \brief Destruktor dla wektora
 */
  ~Wektor();

/*!
 * \brief Przeciazenie operatora przyrownania dla wektora
 */
  Wektor& operator= (const Wektor W);

 /*!
 * \brief Przeciazenie operatora dodawania dla wektorow
 */
  Wektor operator+ (Wektor W)const;
  
/*!
 * \brief Przeciazenie operatora dodawania z podstawieniem dla wektorow
 */ 
  Wektor& operator+= (Wektor W);

/*!
 * \brief Przeciazenie operatora odejmowania dla wektorow
 */
  Wektor operator- (Wektor W)const;

 /*!
 * \brief Przeciazenie operatora mnozenia dla wektorow
 */
  Wektor operator* (double Liczba)const;

 /*!
 * \brief Przeciazenie operatora porownania dla wektorow
 */
  bool operator == (Wektor W)const;

 /*!
 * \brief Metoda wyliczajaca odleglosc miedzy dwoma wektorami
 */
  double Odleglosc(Wektor W)const;
};

/*!
 * \brief Metoda zwracajaca ogolna ilosc wektorow.
 * \retval aktualna ogolna wektorow.
 */
template<int Wymiar>
int Wektor<Wymiar>::IloscOgolna=0;

/*!
 * \brief Metoda zwracajaca aktualna ilosc wektorow.
 * \retval aktualna ilosc wektorow.
 */
template<int Wymiar>
int Wektor<Wymiar>::IloscAktualna=0;

/*!
 * \brief Metoda służąca do indeksowania Wektora.
 * Argumenty:
 *   \param[in] indeks - indeks zadanej skladowej wektora
 * Zwraca:
 *    \retval Wartośc składowej Wektora o zadanym indeksie.
 */
template<int Wymiar>
double Wektor<Wymiar>::operator [](int Indeks)const
{
if(Indeks >= Wymiar)
    {
    throw std::runtime_error("Blad: Nieodpowiedni numer indeksu");
    }
else
    {
    return Elem[Indeks];
    }
}

/*!
 * \brief Metoda służąca do indeksowania Wektora.
 * Argumenty:
 *  \param[in] indeks - indeks zadanej skladowej wektora
 * Zwraca:
 *  \retval Referencje do składowej wektora o danym indeksie.
 */
template<int Wymiar>
double& Wektor<Wymiar>::operator [](int Indeks)
{
if(Indeks >= Wymiar)
    {
    throw std::runtime_error("Blad: Nieodpowiedni numer indeksu");
    }
else
    {
    return Elem[Indeks];
    }
}

/*!
 * \brief Konstruktor bezparametryczny dla Wektora.
 * \param[in] W - Wektor ktory ma zostac skopiowany.
 */
template<int Wymiar>
Wektor<Wymiar>::Wektor()
{
for(double &Elem_i : Elem)
    {
    Elem_i = 0;
    }
++IloscAktualna;
++IloscOgolna;
}

/*!
 * \brief Konstruktor parametryczny dla Wektora.
 *  Argumenty:
 *  \param[in] ListaElem - lista wartosci skladowych tworzonego wektora.
 */
template<int Wymiar>
Wektor<Wymiar>::Wektor(const std::initializer_list<double> &ListaElem):Wektor<Wymiar>()
{
  if(ListaElem.size() > Wymiar)
    {
      throw std::runtime_error("Blad: Nieodpowiednia liczba parametrow");
    }
  int Indeks = -1;
  for(double Elem_i : ListaElem)
    {
      Elem[++Indeks] = Elem_i;
    }
++IloscAktualna;
++IloscOgolna;
}

/*!
 * \brief Konstruktor kopiujacy dla wektora
 */
template<int Wymiar>
Wektor<Wymiar>::Wektor(const Wektor<Wymiar> &W)
{
  for(int i=0; i<Wymiar; i++)
    {
    Elem[i]=W[i];
    }
++IloscAktualna;
++IloscOgolna;
}

/*!
 * \brief Destruktor dla wektora
 */
template<int Wymiar>
Wektor<Wymiar>::~Wektor()
{
--IloscAktualna;
}

/*!
 * \brief Przeciazenie operatora przyrownania dla wektora
 * \param[in] W - Wektor ktory ma zostac podstawiony
 */
template<int Wymiar>
Wektor<Wymiar>& Wektor<Wymiar>::operator= (const Wektor<Wymiar> W)
{
  for(int i=0; i<Wymiar; i++)
    {
    Elem[i]=W[i];
    }
  return (*this);
}

/*!
 * \brief Metoda służąca do dodawania wektorów.
 * Argumenty:
 *  \param[in] W - Wektor ktory ma zostac dodany.
 * Zwraca:
 *  \retval Sume dwóch wektorów.
 */
template<int Wymiar>
Wektor<Wymiar> Wektor<Wymiar>::operator+ (Wektor<Wymiar> W)const
{
Wektor<Wymiar> Wynik;
for(int i=-1; i<Wymiar; ++i)
    {
    Wynik[i] = (*this)[i] + W[i];
    }
return Wynik;
}

/*!
 * \brief Metoda służąca do dodawania wektorów z podstawieniem.
 * Argumenty:
*  \param[in] W - Wektor ktory ma zostac dodany.
 * Zwraca:
 *  \retval Pierwotny wektor z dodana wartoscia.
 */
template<int Wymiar>
Wektor<Wymiar>& Wektor<Wymiar>::operator+= (Wektor<Wymiar> W)
{
(*this)=(*this)+W;
return (*this);
}

/*!
 * \brief Metoda służąca do odejmowania wektorów.
 * Argumenty:.
 *  \param[in]  W - Drugi wektorowy składnik odejmowania.
 * Zwraca:
 *  \retval Różnice dwóch wektorów.
 */
template<int Wymiar>
Wektor<Wymiar> Wektor<Wymiar>::operator- (Wektor<Wymiar> W)const
{
Wektor<Wymiar> Wynik;
for(int i=-1; i<Wymiar; ++i)
    {
    Wynik[i] = (*this)[i] - W[i];
    }
return Wynik;
}

/*!
 * \brief Metoda służąca do mnożenia wektora przez skalar.
 * Argumenty:
 *  \param[in] Liczba - Wartośc skalarna przez, która wektor będzie mnożony.
 * Zwraca:
 *  \retval Przemnożony wektor.
 */
template<int Wymiar>
Wektor<Wymiar> Wektor<Wymiar>::operator* (double Liczba)const
{
Wektor<Wymiar> Wynik;
for(int i=0; i<Wymiar; i++)
    {
    Wynik[i] = (*this)[i] * Liczba;
    }
return Wynik;
}

/*!
 * \brief Funkcja służąca do mnożenia wektora przez skalar (W kolejnosci skalar * wektor).
 * Argumenty:
 *  \param[in] Liczba - Wartośc skalarna przez, która wektor będzie mnożony.
 *  \param[in] W - Przemnażany wektor.
 * Zwraca:
 *  \retval Przemnożony wektor.
 */
template<int Wymiar>
Wektor<Wymiar> operator * (double Liczba, Wektor<Wymiar> W)
{
Wektor<Wymiar> Wynik;

for(int i=0; i<Wymiar; i++)
    {
    Wynik[i] = W[i] * Liczba;
    }

return Wynik;
}

/*!
 * \brief Metoda służąca do porównywania wektorów z dokladnoscia do 0,001..
 * Argumenty:
 *  \param[in] W - Wektor odniesienia.
 * Zwraca:
 *  \retval True, jeżeli wektory są takie same.
 *  \retval False, jeżeli nie są.
 */
template<int Wymiar>
bool Wektor<Wymiar>::operator == (Wektor<Wymiar> W)const
{
for(int i=-1; i<Wymiar; ++i)
    {
    if(abs((*this)[i]-W[i])>=MIN_ROZNICA)
        {return false;}
    }
return true;
}

/*!
 * \brief Metoda służąca do obliczania odległości między wektorem a wektorem odniesienia.
 * Argumenty:
 *  \param[in] W - Wektor odniesienia
 * Zwraca:
 *  \retval  Wartosc odleglosci miedzy dwoma wektorami.
 */
template<int Wymiar>
double Wektor<Wymiar>::Odleglosc(Wektor<Wymiar> W)const
{
double Wynik=0;
for(int i=-1; i<Wymiar; ++i)
    {
    Wynik += pow(((*this)[i]-W[i]),2);
    }
Wynik = sqrt(Wynik);
return Wynik;
}




/*!
 * \brief Funkcja służąca do wczytywania wektora z danego strumienia.
 * Argumenty:
 *  \param[in] Strm - Strumień, z którego wektor ma zostać wczytany.
 *  \param[in] Wek - Referencja do wektora, do którego dane mają zostać zapisane.
 * Zwraca:
 *  \retval Strumień z którego wektor został wczytany.
 */
template <int Wymiar>
inline
std::istream& operator >> (std::istream &Strm, Wektor<Wymiar> &Wek)
{
for (int i=0; i<Wymiar; i++)
    {
    Strm >> Wek[i];
    if(Strm.fail())
        {
        Strm.setstate(std::ios::failbit);
        throw std::runtime_error("Blad wczytania wektora");
        return Strm;
        }
    }
return Strm;
}

/*!
 * \brief Funkcja służąca do przekazywania wektora do danego strumienia.
 * Argumenty:
 *  \param[in] Strm - Strumień, na który wektor ma zostać wypisany.
 *  \param[in] Wek - Wektor, ktory ma zostać wypisany.
 * Zwraca:
 *  \retval Strumień na który wektor został wypisany.
 */
template <int Wymiar>
inline
std::ostream& operator << (std::ostream &Strm, const Wektor<Wymiar> &Wek)
{
for (int i=0; i<Wymiar; i++)
    {
    Strm << std::fixed << std::setprecision(10)<< Wek[i];
    if(i!=(Wymiar-1))
        {
        Strm << " ";
        }
    }
return Strm;
}

#endif

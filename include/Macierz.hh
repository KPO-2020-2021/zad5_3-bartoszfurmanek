#ifndef MACIERZ_HH
#define MACIERZ_HH

#define PI 3.1415926535
#include "Wektor.hh"
#include <iostream>
#include <iomanip>
#include "Wektor3D.hh"



/*!
 * \file
 * \brief Szablon klasy reprezentujacej macierz kwadratowa o dowlonym wymiarze.
 */

/*!
 *\brief Szablon klasy reprezentujacej macierz kwadratowa.
 * Szablon klasy reprezentujacej macierz. Ilosc kolumn oraz wierszy, a przez to
 * ilosc elementow macierzy zalezy od zmiennej Wymiar. Macierz można indeksować za
 * pomocą operatora().Na macierzy mozna wykonywa podstawowe dzialania matematyczne.
 */
template <int Wymiar>
class Macierz{

/*!
 * \brief Wektor
 *
 * Atrybut modeluje macierz kwadratowa o danym wymiarze, kazdy element tablicy
 * symbolizuje jedna komorke macierzy.
 *
 */
  double Elem[Wymiar][Wymiar];
  
  public:

/*!
 * \brief Indeksowanie macierzy
 */
  double operator() (int IndeksW, int IndeksK)const;

/*!
 * \brief Indeksowanie macierzy
 */
  double& operator() (int IndeksW, int IndeksK);

/*!
 * \brief Konstrutor bezparametryczny macierzy
 */
  Macierz();

/*!
 * \brief Konstrutor parametryczny macierzy
 */
  Macierz(const std::initializer_list<double> &ListaElem);

/*!
 * \brief Przeciazenie operatora porownania dla macierzy
 */
  bool operator== (Macierz M)const;
 
/*!
 * \brief Przeciazenie operatora dodawwania dla macierzy
 */ 
  Macierz operator+ (Macierz M)const;

/*!
 * \brief Przeciazenie operatora odejmowania dla macierzy
 */
  Macierz operator- (Macierz M)const;

/*!
 * \brief Przeciazenie operatora mnozenia dla macierzy
 */  
  Macierz operator* (Macierz M)const;

/*!
 * \brief Przeciazenie operatora mnozenia przez skalar dla macierzy
 */
  Macierz operator* (double Liczba)const;

/*!
 * \brief Przeciazenie operatora mnozenia wektora przez macierz
 */
  Wektor<Wymiar> operator* (Wektor<Wymiar> W)const;

/*!
 *\brief Metoda sluzy do przeksztalcania macierzy4x4 na macierz obrotu i przesuniecia.
 */ 
  void Wypelnij(double alfa, double beta, double gamma, Wektor3D Przesuniecia);

};

/*!
 * \brief Metoda służąca do indeksowania macierzy.
 * Argumenty:
 *  \param[in] IndeksW - Indeks wiersza.
 *  \param[in] IndeksK - Indeks kolumny.
 * Zwraca:
 *  \retval  Wartośc komorki macierzy o danym indeksie.
 */
template<int Wymiar>
double Macierz<Wymiar>::operator() (int IndeksW, int IndeksK)const
{
if((IndeksW >= Wymiar) || (IndeksK >= Wymiar))
    {
    throw std::runtime_error("Blad: Nieodpowiedni numer indeksu");
    }
else
    {
    return Elem[IndeksW][IndeksK];
    }
}

/*!
 * \brief Metoda służąca do indeksowania macierzy.
 * Argumenty:
 *  \param[in] IndeksW - Indeks wiersza.
 *  \param[in] IndeksK - Indeks kolumny.
 * Zwraca:
 *  \retval Referencja do komorki macierzy o danym indeksie.
 */
template<int Wymiar>
double& Macierz<Wymiar>::operator() (int IndeksW, int IndeksK)
{
if((IndeksW >= Wymiar) || (IndeksK >= Wymiar))
    {
    throw std::runtime_error("Blad: Nieodpowiedni numer indeksu");
    }
else
    {
    return Elem[IndeksW][IndeksK];
    }
}

/*!
 * \brief Konstruktor bezparametryczny dla macierzy.
 */
template <int Wymiar>
Macierz<Wymiar>::Macierz()
{
for(int i=0; i<Wymiar; i++)
    {
    for(int j=0; j<Wymiar; j++)
        {
        Elem[i][j]=0;
        }
    }
}

/*!
 * \brief Konstruktor parametryczny dla macierzy.
 * Argumenty:
 *  \param[in] ListaElem - Lista wartosci komorek tworzonej macierzy.
 */
template <int Wymiar>
Macierz<Wymiar>::Macierz(const std::initializer_list<double> &ListaElem):Macierz<Wymiar>()
{
  if(ListaElem.size() > Wymiar*Wymiar)
    {
      throw std::runtime_error("Blad: Nieodpowiednia liczba parametrow");
    }
  int I = 0,K = -1;
  
  for(double Elem_i : ListaElem)
    {
      Elem[I][++K] = Elem_i;
      if(K==(Wymiar-1))
        {
        ++I;
        K=-1;
        }
    }
}


/*!
 * \brief Metoda służąca do porownywania  macierzy z dokladnoscia do 0,001.
 * Argumenty:
 *  \param[in] W - Macierz odniesienia.
 * Zwraca:
 *   \retval True, jeżeli macierz są takie same.
 *   \retval False jeżeli macierze sie roznia
 */
template<int Wymiar>
bool Macierz<Wymiar>::operator== (Macierz<Wymiar> M)const
{
for(int i=0; i<Wymiar; i++)
    {
    for(int j=0; j<Wymiar; j++)
        {
        if((abs((*this)(i,j)-M(i,j)))>=MIN_ROZNICA)
        {return false;}
        }
    }
return true;
}

/*!
 * \brief Metoda służąca do dodawania macierzy.
 * Argumenty:
 *  \param[in] M - Macierz ktora ma zostac dodana.
 * Zwraca:
 *  \retval Suma dwóch macierzy.
 */
template<int Wymiar>
Macierz<Wymiar> Macierz<Wymiar>::operator+ (Macierz<Wymiar> M)const
{
Macierz<Wymiar> Wynik;
for(int i=0; i<Wymiar; i++)
    {
    for(int j=0; j<Wymiar; j++)
        {
        Wynik(i,j) = (*this)(i,j) + M(i,j);
        }
    }
return Wynik;
}

/*!
 * \brief Metoda służąca do odejmowania macierzy.
 * Argumenty:
 *  \param[in] M - Macierz ktora ma zostac odjeta.
 * Zwraca:
 *  \retval Rozniaca dwóch macierzy.
 */
template<int Wymiar>
Macierz<Wymiar> Macierz<Wymiar>::operator- (Macierz<Wymiar> M)const
{
Macierz<Wymiar> Wynik;
for(int i=0; i<Wymiar; i++)
    {
    for(int j=0; j<Wymiar; j++)
        {
        Wynik(i,j) = (*this)(i,j) - M(i,j);
        }
    }
return Wynik;
}

/*!
 * \brief Metoda służąca do mnożenia macierzy.
 * Argumenty:
 *  \param[in] M - Macierz wymnazajaca.
 * Zwraca:
 *  \retval Iloraz dwoch macierzy.
 */
template<int Wymiar>
Macierz<Wymiar> Macierz<Wymiar>::operator* (Macierz<Wymiar> M)const
{
Macierz<Wymiar> Wynik;

int w,k;
for(int i=0; i<Wymiar; i++)
    {
    for(int j=0; j<Wymiar; j++)
        {
        Wynik(i,j)=0;
        w=k=0;
        while (w<Wymiar && k<Wymiar)
            {
            Wynik(i,j) += (*this)(i,k)*M(w,j);
            ++w;
            ++k;
            }
        }
    }
return Wynik;
}

/*!
 * \brief Metoda służąca do mnożenia macierzy przez skalar.
 * Argumenty:
 *  \param[in] Liczba - Skalar.
 * Zwraca:
 *  \retval Iloraz macierzy i sklaru.
 */
template<int Wymiar>
Macierz<Wymiar> Macierz<Wymiar>::operator* (double Liczba)const
{
Macierz<Wymiar> Wynik;

for(int i=0; i<Wymiar; i++)
    {
    for(int j=0; j<Wymiar; j++)
        {
        Wynik(i,j) = (*this)(i,j)*Liczba;
        }
    }
return Wynik;
}

/*!
 * \brief Funkcja służąca do mnożenia macierzy przez skalar (Realizuje mnożenie w kolejności skalar*macierz).
 * Argumenty:
 *  \param[in] M - Macierz ktora ma zostac wymnożona.
 *  \param[in] Liczba - Skalar
 * Zwraca:
 *  \retval Iloraz macierzy i sklaru.
 */
template<int Wymiar>
Macierz<Wymiar> operator* (double Liczba, Macierz<Wymiar> M)
{
Macierz<Wymiar> Wynik;
for(int i=0; i<Wymiar; i++)
    {
    for(int j=0; j<Wymiar; j++)
        {
        Wynik(i,j) = M(i,j)*Liczba;
        }
    }
return Wynik;
}

/*!
 * \brief Metoda służąca do mnożenia macierzy przez wektor.
 * Argumenty:
 *  \param[in] W - Wektor.
 * Zwraca:
 *  \retval  Wektor, będący wynikiem mnożenia macierzy przez wektor.
 */
template<int Wymiar>
Wektor<Wymiar> Macierz<Wymiar>::operator* (Wektor<Wymiar> W)const
{
Wektor<Wymiar> Wynik;

int w,k;
for(int i=0; i<Wymiar; i++)
    {
    for(int j=0; j<Wymiar; j++)
        {
        Wynik[i]=0;
        w=k=0;
        while (w<Wymiar&& k<Wymiar)
            {
            Wynik[i] += (*this)(i,k)*W[w];
            ++w;
            ++k;
            }
        }
    }
return Wynik;
}


/*!
 * \brief Funkcja służąca do przekazywania macierzy do danego strumienia.
 * Argumenty:
 *  \param[in] Strm - Strumień, na który macierz ma zostać wypisany.
 *  \param[in] Mac - Macierz, ktora ma zostać wypisana.
 * Zwraca:
 *  \retval Strumień na który macierz została wypisana.
 */
template <int Wymiar>
inline
std::ostream& operator << (std::ostream &Strm, const Macierz<Wymiar> &Mac)
{
for(int i=0; i<Wymiar; i++)
    {
    for(int j=0; j<Wymiar; j++)
        {
        Strm << std::fixed << std::setprecision(10)<< Mac(i,j);
        if(j!=(Wymiar-1))
            {
            Strm << " ";
            }
        }
    Strm << std::endl;
    }
return Strm;  
}

/*!
 * \brief Metoda sluzy do przeksztalcania macierzy4x4 na macierz obrotu i przesuniecia.
 * Argumenty:
 *  \param[in] alfa - Kat obrotu o os z.
 *  \param[in] beta - Kat obrotu o os y.
 *  \param[in] gamma - Kat obrotu o os x.
 *  \param[in] Przesuniecie - Wektor3D przesuniecia.
 */
template <int Wymiar>
void Macierz<Wymiar>::Wypelnij(double alfa, double beta, double gamma, Wektor3D Przesuniecie)
{

if(Wymiar!=4)
    {
    throw std::runtime_error("Blad: Metoda dziala tylko dla macierzy4x4");
    }
else
    {
    alfa = alfa/180 * PI;          //Zamiana na radiany
    beta = beta/180 * PI;
    gamma = gamma/180 * PI;

    (*this)(0,0)= cos(alfa)*cos(beta);
    (*this)(0,1)= (cos(alfa)*sin(beta)*sin(gamma))-(sin(alfa)*cos(gamma));
    (*this)(0,2)= (cos(alfa)*sin(beta)*cos(gamma))+(sin(alfa)*sin(gamma));
    (*this)(0,3)= Przesuniecie[0];
    (*this)(1,0)= sin(alfa)*cos(beta);
    (*this)(1,1)= (sin(alfa)*sin(beta)*sin(gamma))+(sin(alfa)*sin(gamma));
    (*this)(1,2)= (sin(alfa)*sin(beta)*cos(gamma))-(cos(alfa)*sin(gamma));
    (*this)(1,3)= Przesuniecie[1];
    (*this)(2,0)= -sin(beta);
    (*this)(2,1)= cos(beta)*sin(gamma);
    (*this)(2,2)= cos(beta)*cos(gamma);
    (*this)(2,3)= Przesuniecie[2];
    (*this)(3,0)= 0;
    (*this)(3,1)= 0;
    (*this)(3,2)= 0;
    (*this)(3,3)= 1;
    }
}


#endif

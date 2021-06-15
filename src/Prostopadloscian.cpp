#include "Prostopadloscian.hh"

#define MIN_ROZNICA 0.001

/*!
 *\file
 *\brief Definicja metod klasy Prostopadloscian.
 */

/*!
 * \brief Operator przypisania dla Prostopadloscianu
 * \param[in] P - Prostopadloscian, z wartosciami ktore maja zostac przypisane.
 * \retval Prostopadloscian z nowymi wartosciami.
 */
Prostopadloscian& Prostopadloscian::operator= (const Prostopadloscian P)
{
  for(int i=0; i<16; i++)
    {
    Wierzcholek[i] = P[i];
    }
  Polozenie = P.WspolPolozenia();
  KatOrientacji = P.Orientacja();
  NazwaBryly = P.NazwaPlikuBryly();
  NazwaBrylyWzorcowej = P.NazwaPlikuBrylyWzorcowej();
  Skala = P.SkalaBryly();
  return(*this);
}


/*!
 * \brief Metoda służąca do indeksowania prostopadloscianu.
 *   \param[in] Indeks - indeks zadanego punktu prostopadloscianu.
 *   \retval Wektor3D reprezentujacy dany punkt prostopadloscianu,
 */
Wektor3D Prostopadloscian::operator [](int Indeks)const
{
    if(Indeks >= 16)
        {
        throw std::runtime_error("Blad: Zly indeks");
        }
    
    return Wierzcholek[Indeks];
}

/*!
 * \brief Metoda służąca do indeksowania prostopadloscianu.
 *   \param[in] Indeks - indeks zadanego punktu prostopadloscianu.
 *   \retval Wektor3D reprezentujacy dany punkt prostopadloscianu,
 */
Wektor3D& Prostopadloscian::operator [](int Indeks)
{
    if(Indeks >= 16)
        {
        throw std::runtime_error("Blad: Zly indeks");
        }
    
    return Wierzcholek[Indeks];
}

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia prostopadloscianu.
 *  \retval Wektor3D reprezentujacy polozenie prostopadloscianu.
 */
  Wektor3D Prostopadloscian::WspolPolozenia()const
  {
      return Polozenie;
  }

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia prostopadloscianu.
 *  \retval referencja do Wektora3D reprezentującego polozenie prostopadloscianu.
 */
  Wektor3D& Prostopadloscian::WspolPolozenia()
  {
      return Polozenie;
  }

/*!
 * \brief Uzyskiwanie katu orientacji prostopadloscianu.
 * \retval Wartosc kata orientacji prostopadloscianu.
 */
  double Prostopadloscian::Orientacja()const
  {
      return KatOrientacji;
  }

/*!
 * \brief Uzyskiwanie katu orientacji polozenia prostopadloscianu.
 * \retval referencja do katu orientacji prostopadloscianu.
 */
  double& Prostopadloscian::Orientacja()
  {
      return KatOrientacji;
  }


/*!
 * \brief Obliczenie wspolrzednych polozenia prostopadloscianu.
 * Metoda wylicza wspolrzedne polozenia prostopadloscianu na podstawie
 * wiercholkow jego podstawy. Za wspolrzednie polozenia przyjmuje sie
 * srodek podstawy prostopadloscianu.
 */
  void Prostopadloscian::ObliczPolozenie()
  {
      Polozenie = Wierzcholek[9];
      Polozenie += Wierzcholek[10];
      Polozenie += Wierzcholek[13];
      Polozenie += Wierzcholek[14];
      Polozenie = 0.25 * Polozenie;

  }

/*!
 *\brief Konstruktor bezparamateryczny prostopadloscianu.
 */
Prostopadloscian::Prostopadloscian():
BrylaGeometryczna(TB_Prostopadloscian), Polozenie({0,0,0}), KatOrientacji(0)
{
  for(int i=0; i<16; i++)
    {
    Wierzcholek[i]={0,0,0};
    }
}

/*!
 *\brief Konstruktor parametryczny prostopadloscianu.
 *  \param[in] WspolPolozenia - Wspolrzedne polozenia srodka prostopadloscianu
 *  \param[in] Kat - Kat orientacji prostopadloscianu.
 *  \param[in] NazwaBryly - Nazwa pliku z wspolrzednymi bryly finalnej.
 *  \param[in] NazwaWzorca - Nazwa pliku z wspolrzednymi bryly wzorcowej.
 *  \param[in] SkalaBryly - Skala rozmiaru w jakim prostopadloscian ma zostac stworzony
 */
Prostopadloscian::Prostopadloscian(Wektor3D WspolPolozenia, double Kat, std::string Nazwa, std::string NazwaWzorca, Wektor3D SkalaBryly):
BrylaGeometryczna(TB_Prostopadloscian, Nazwa, NazwaWzorca, SkalaBryly), Polozenie(WspolPolozenia), KatOrientacji(Kat)
{
(*this).OdczytajBryleWzorcowa();
for(int i=0; i<16; i++)
  {
  Wierzcholek[i]=(*this).Skaluj(Wierzcholek[i]);
  }
(*this).Obrot(Kat, 'z');
(*this).Translacja(WspolPolozenia);
while(KatOrientacji<= -360 || KatOrientacji >= 360)     //Usuniecie okresowosci kata.
  {
    if(KatOrientacji<= -360)
    {
      KatOrientacji +=360;
    }
    if(KatOrientacji>= 360)
    {
      KatOrientacji -=360;
    }    
  }
Polozenie=WspolPolozenia;
}

/*!
 * \brief Konstruktor kopiujacy.
 * \param[in] P - Prostopadloscian ktory ma zostac skopiowany.
 */
Prostopadloscian::Prostopadloscian(const Prostopadloscian &P):
BrylaGeometryczna(TB_Prostopadloscian, P.NazwaPlikuBryly(), P.NazwaPlikuBrylyWzorcowej(), P.SkalaBryly()), Polozenie(P.WspolPolozenia()), KatOrientacji(P.Orientacja())
{
  for(int i=0; i<16; i++)
    {
    Wierzcholek[i] = P[i];
    }
}


/*!
 * \brief Metoda służąca do porownywania prostopadloscianow z dokladnoscia do 0,001.
 *  \param[in] Pr - Prostopadloscian odniesienia.
 *   \retval True, jeżeli prostopadlosciany są takie same.
 *   \retval False jeżeli prostopadlosciany sie roznia
 */
bool Prostopadloscian::operator ==(Prostopadloscian Pr)const
{
for(int i=0; i<16; i++)
    {
    if(!((*this)[i]==Pr[i]))
        {return false;}
    }
return true;
}

/*!
 * \brief Metoda służąca do obrotu prostopadloscianu o zadany kat wokol osi x,y,z.
 * UWAGA: Metoda nie sprawdza czy podano poprawna os (mozliwe opcje to x,y oraz z).
 *  \param[in] Kat - Kat obrotu.
 *  \param[in] Os - Os obrotu.
 *   \retval Obrocony prostopadloscian.
 */
Prostopadloscian& Prostopadloscian::Obrot(double Kat, char Os)
{
    for(int i=0; i<16; i++)
    {
    (*this)[i] = MacierzObrotu(Kat, Os) * (*this)[i];  //Wymnożenie każdego wierzcholka przez macierz obrotu
    }               
    return *this;
}

/*!
 * \brief Metoda służąca do przesuniecie prostopadloscianu o zadany wektor
 *  \param[in] Wektor - Wektor przesuniecia.
 *   \retval Przesuniety prostopadloscian.
 */
Prostopadloscian& Prostopadloscian::Translacja(Wektor3D Wektor)
{
    for(int i=0; i<16; i++)
    {
    (*this)[i] += Wektor;
    }
    return (*this);
}

/*!
 * \brief Metoda sprowadzajaca prostopadloscian do wlasnego ukladu wspolrzednych.
 */
  void Prostopadloscian::TransformujDoUkladuRodzica()
  {
    (*this).Translacja((-1*Polozenie));
    (*this).Obrot((KatOrientacji*-1),'z');

  }

/*!
 * \brief Metoda sprowadzajaca prostopadloscian do globalnego ukladu wspolrzednych.
 */
  void Prostopadloscian::TransformujDoUkladuGlobalnego()
  {
    (*this).Obrot(KatOrientacji,'z');
    (*this).Translacja((Polozenie));

  }


/*!
 * \brief Zapis wspolrzednych prostopadloscianu do strumienia.
 * Metoda służy do zapisu wspolrzednych  prostopadloscianu do danego strumienia,
 * w celu zapisu go do pliku, ktory bedzie rysowac gnuplot.
 * przy wykonywaniu rysunku.
 *  \param[in] StrmWy - Strumien na ktory wspolrzedne maja zostac wypisane.
 */
void Prostopadloscian::ZapisWspolrzednychDoStrumienia(std::ostream &StrmWy)const
{
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[0] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[1] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[2] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[3] << std::endl;
  StrmWy << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[4] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[5] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[6] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[7] << std::endl;
  StrmWy << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[8] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[9] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[10] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[11] << std::endl;
  StrmWy << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[12] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[13] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[14] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[15] << std::endl;
  StrmWy << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[0] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[1] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[2] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[3] << std::endl;

}



/*!
 * \brief Odczyt wspolrzednych  prostopadloscianu ze strumienia.
 * Metoda służy do odczytu wspolrzednych wierzcholków prostopadloscianu z danego strumienia.
 *  \param[in] StrmWej - Strumien z ktorego wierzcholki maja zostac wczytane.
 */
void Prostopadloscian::OdczytWspolrzednychDoStrumienia(std::istream &StrmWej)
{
StrmWej >> Wierzcholek[0];
StrmWej >> Wierzcholek[1];
StrmWej >> Wierzcholek[2];
StrmWej >> Wierzcholek[3];

StrmWej >> Wierzcholek[4];
StrmWej >> Wierzcholek[5];
StrmWej >> Wierzcholek[6];
StrmWej >> Wierzcholek[7];

StrmWej >> Wierzcholek[8];
StrmWej >> Wierzcholek[9];
StrmWej >> Wierzcholek[10];
StrmWej >> Wierzcholek[11];

StrmWej >> Wierzcholek[12];
StrmWej >> Wierzcholek[13];
StrmWej >> Wierzcholek[14];
StrmWej >> Wierzcholek[15];
}


/*!
 * \brief Metoda zapisuje wspolrzedne prostopadloscianu do pliku
 * \retval True - jeżeli zapis uda sie pomyslnie.
 * \retval False - jezeli zapis sie nie uda.
 */
  bool Prostopadloscian::ZapiszBryle()const
  {
  std::ofstream  StrmPlikowy;
  StrmPlikowy.open((*this).NazwaPlikuBryly());
  if (!StrmPlikowy.is_open())  {
    std::cerr << "Operacja otwarcia do zapisu \"" << (*this).NazwaPlikuBryly() << "\"" << std::endl
	 << " nie powiodla sie." << std::endl;
    return false;
  }
  (*this).ZapisWspolrzednychDoStrumienia(StrmPlikowy);
  StrmPlikowy.close();
  return !StrmPlikowy.fail();
  }


/*!
 * \brief Metoda odczytuje wspolrzedne prostopadloscianu z pliku ze wzorcem prostopadloscianu.
 * \retval True - jeżeli odczyt uda sie pomyslnie.
 * \retval False - jezeli odczyt sie nie uda.
 */
  bool Prostopadloscian::OdczytajBryleWzorcowa()
  {
  std::ifstream  StrmPlikowy;
  StrmPlikowy.open((*this).NazwaPlikuBrylyWzorcowej());
  if (!StrmPlikowy.is_open())  {
    std::cerr << "Operacja otwarcia do odczytu \"" << (*this).NazwaPlikuBrylyWzorcowej() << "\"" << std::endl
	 << " nie powiodla sie." << std::endl;
    return false;
  }
  (*this).OdczytWspolrzednychDoStrumienia(StrmPlikowy);
  StrmPlikowy.close();
  return !StrmPlikowy.fail();
  }

/*!
 *\brief Metoda zastepuje wspolrzedne, wspolrzednymi wzorca (Odpowiednio obrocony i przesuniety).
  * \retval True - jeżeli odczyt wzorca uda sie pomyslnie.
 * \retval False - jezeli odczyt wzorca sie nie uda.
 */
  bool Prostopadloscian::UzyjWzorca()
  {
    if(!(*this).OdczytajBryleWzorcowa())
      {
      return false;
      }
    for(int i=0; i<16; i++)
      {
      Wierzcholek[i]=(*this).Skaluj(Wierzcholek[i]);
      }
    (*this).Obrot(KatOrientacji, 'z');
    (*this).Translacja(Polozenie);
    return true;
  }


/*!
 * \brief Metoda sluzaca do przekazywania do strumienia wierzcholkow prostopadlocianu.
 * Argumenty:
 *  \param[in] Strm - Strumień, na ktory wierzcholki maja zostac przekazane
 *  \param[in] Pr - Prostopadloscian, ktorego wierzcholki maja zostac przekazane
 * Zwraca:
 *  \retval Strumień na który wierzcholki zostaly wypisane
 */
std::ostream& operator << (std::ostream &Strm, const Prostopadloscian &Pr)
{
    Strm << std::setw(16) << std::fixed << std::setprecision(10) << Pr[1] << std::endl;
    Strm << std::setw(16) << std::fixed << std::setprecision(10) << Pr[2] << std::endl;
    Strm << std::setw(16) << std::fixed << std::setprecision(10) << Pr[5] << std::endl;
    Strm << std::setw(16) << std::fixed << std::setprecision(10) << Pr[6] << std::endl;
    Strm << std::setw(16) << std::fixed << std::setprecision(10) << Pr[9] << std::endl;
    Strm << std::setw(16) << std::fixed << std::setprecision(10) << Pr[10] << std::endl;
    Strm << std::setw(16) << std::fixed << std::setprecision(10) << Pr[13] << std::endl;
    Strm << std::setw(16) << std::fixed << std::setprecision(10) << Pr[14] << std::endl;

return Strm;
}


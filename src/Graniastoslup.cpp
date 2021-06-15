#include "Graniastoslup.hh"

#define MIN_ROZNICA 0.001

/*!
 *\file
 *\brief Definicja metod klasy Graniastoslup.
 */

/*!
 * \brief Operator przypisania dla Graniastoslupa
 * \param[in] G - Graniastoslup, z wartosciami ktore maja zostac przypisane.
 * \retval Graniastoslup z nowymi wartosciami.
 */
Graniastoslup& Graniastoslup::operator= (const Graniastoslup G)
{
  for(int i=0; i<24; i++)
    {
    Wierzcholek[i] = G[i];
    }
  Polozenie = G.WspolPolozenia();
  KatOrientacji = G.Orientacja();
  NazwaBryly = G.NazwaPlikuBryly();
  NazwaBrylyWzorcowej = G.NazwaPlikuBrylyWzorcowej();
  Skala = G.SkalaBryly();
  return(*this);
}



/*!
 * \brief Metoda służąca do indeksowania graniastoslupu.
 *   \param[in] Indeks - indeks zadanego punktu graniastoslupu.
 *   \retval Wektor3D reprezentujacy dany punkt graniastoslupu.
 */
Wektor3D Graniastoslup::operator [](int Indeks)const
{
    if(Indeks >= 24)
        {
        throw std::runtime_error("Blad: Zly indeks");
        }
    
    return Wierzcholek[Indeks];
}

/*!
 * \brief Metoda służąca do indeksowania graniastoslupu.
 *   \param[in] Indeks - indeks zadanego punktu graniastoslupu.
 *   \retval Wektor3D reprezentujacy dany punkt graniastoslupu,
 */
Wektor3D& Graniastoslup::operator [](int Indeks)
{
    if(Indeks >= 24)
        {
        throw std::runtime_error("Blad: Zly indeks");
        }
    
    return Wierzcholek[Indeks];
}

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia graniastoslupu.
 *  \retval Wektor3D reprezentujacy polozenie graniastoslupu.
 */
  Wektor3D Graniastoslup::WspolPolozenia()const
  {
      return Polozenie;
  }

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia graniastoslupu.
 *  \retval referencja do Wektora3D reprezentującego polozenie graniastoslupu.
 */
  Wektor3D& Graniastoslup::WspolPolozenia()
  {
      return Polozenie;
  }

/*!
 * \brief Uzyskiwanie katu orientacji graniastoslupu.
 *  \retval Wartosc kata orientacji graniastoslupu.
 */
  double Graniastoslup::Orientacja()const
  {
      return KatOrientacji;
  }

/*!
 * \brief Uzyskiwanie katu orientacji polozenia graniastoslupu.
 *  \retval referencja do katu orientacji graniastoslupu.
 */
  double& Graniastoslup::Orientacja()
  {
      return KatOrientacji;
  }


/*!
 * \brief Obliczenie wspolrzednych polozenia graniastoslupu.
 * Metoda wylicza wspolrzedne polozenia graniastoslupu na podstawie
 * wiercholkow jego podstawy. Za wspolrzednie polozenia przyjmuje sie
 * srodek podstawy graniastoslupu.
 */
  void Graniastoslup::ObliczPolozenie()
  {
      Polozenie = Wierzcholek[1];
      Polozenie += Wierzcholek[5];
      Polozenie += Wierzcholek[9];
      Polozenie += Wierzcholek[13];
      Polozenie += Wierzcholek[17];
      Polozenie += Wierzcholek[21];
      Polozenie = (1.0/6)* Polozenie;
  }

/*!
 *\brief Konstruktor bezparamateryczny graniastoslupu.
 */
Graniastoslup::Graniastoslup():
BrylaGeometryczna(TB_Graniastoslup), Polozenie({0,0,0}), KatOrientacji(0)
{
  for(int i=0; i<24; i++)
    {
    Wierzcholek[i]={0,0,0};
    }
}

/*!
 *\brief Konstruktor parametryczny graniastoslupnu.
 *  \param[in] WspolPolozenia - Wspolrzedna polozenia srodka podstawy graniastoslupa.
 *  \param[in] Kat - Kat orientacji graniastoslupu.
 *  \param[in] NazwaBryly - Nazwa pliku z wspolrzednymi bryly finalnej.
 *  \param[in] NazwaWzorca - Nazwa pliku z wspolrzednymi bryly wzorcowej.
 *  \param[in] SkalaBryly - Skala rozmiaru w jakim graniastoslup ma zostac stworzony
 */
Graniastoslup::Graniastoslup(Wektor3D WspolPolozenia, double Kat, std::string Nazwa, std::string NazwaWzorca, Wektor3D SkalaBryly):
BrylaGeometryczna(TB_Graniastoslup, Nazwa, NazwaWzorca, SkalaBryly), Polozenie(WspolPolozenia), KatOrientacji(Kat)
{
(*this).OdczytajBryleWzorcowa();
for(int i=0; i<24; i++)
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
 * \param[in] G - Graniastoslup ktory ma zostac skopiowany.
 */
Graniastoslup::Graniastoslup(const Graniastoslup &G):
BrylaGeometryczna(TB_Graniastoslup, G.NazwaPlikuBryly(), G.NazwaPlikuBrylyWzorcowej(), G.SkalaBryly()), Polozenie(G.WspolPolozenia()), KatOrientacji(G.Orientacja())
{
  for(int i=0; i<24; i++)
    {
    Wierzcholek[i] = G[i];
    }
}

/*!
 * \brief Metoda służąca do porownywania graniastoslupow z dokladnoscia do 0,001.
 *  \param[in] Gr - Graniastoslup odniesienia.
 *   \retval True, jeżeli graniastoslupy są takie same.
 *   \retval False jeżeli graniastoslupy sie roznia
 */
bool Graniastoslup::operator ==(Graniastoslup Gr)const
{
for(int i=0; i<24; i++)
    {
    if(!((*this)[i]==Gr[i]))
        {return false;}
    }
return true;
}

/*!
 * \brief Metoda służąca do obrotu graniastoslupu o zadany kat wokol osi x,y,z.
 * UWAGA: Metoda nie sprawdza czy podano poprawna os (mozliwe opcje to x,y oraz z).
 *  \param[in] Kat - Kat obrotu.
 *  \param[in] Os - Os obrotu.
 *   \retval Obrocony graniastoslup.
 */
Graniastoslup& Graniastoslup::Obrot(double Kat, char Os)
{
    for(int i=0; i<24; i++)
    {
    (*this)[i] = MacierzObrotu(Kat, Os) * (*this)[i];  //Wymnożenie każdego wierzcholka przez macierz obrotu
    }
    return *this;
}

/*!
 * \brief Metoda służąca do przesuniecie graniastoslupu o zadany wektor
 *  \param[in] Wektor - Wektor przesuniecia.
 *   \retval Przesuniety graniastoslup.
 */
Graniastoslup& Graniastoslup::Translacja(Wektor3D Wektor)
{
    for(int i=0; i<24; i++)
    {
    (*this)[i] += Wektor;
    }
    return (*this);
}

/*!
 * \brief Metoda sprowadzajaca graniastoslup do wlasnego ukladu wspolrzednych.
 */
  void Graniastoslup::TransformujDoUkladuRodzica()
  {
    (*this).Translacja((-1*Polozenie));
    (*this).Obrot((KatOrientacji*-1),'z');
  }

/*!
 * \brief Metoda sprowadzajaca graniastoslup do globalnego ukladu wspolrzednych.
 */
  void Graniastoslup::TransformujDoUkladuGlobalnego()
  {
    (*this).Obrot(KatOrientacji,'z');
    (*this).Translacja((Polozenie));
  }


/*!
 * \brief Zapis wspolrzednych graniastoslupu do strumienia.
 * Metoda służy do zapisu wspolrzednych graniastoslupu do danego strumienia.
 * Pierwsze wspolrzedne zostaja zapisane ponownie, aby zachowac ciaglosc
 * przy wykonywaniu rysunku.
 * Argumenty:
 *  \param[in] StrmWy - Strumien na ktory wspolrzedne maja zostac wypisane.
 */
void Graniastoslup::ZapisWspolrzednychDoStrumienia(std::ostream &StrmWy)const
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
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[16] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[17] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[18] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[19] << std::endl;
  StrmWy << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[20] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[21] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[22] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[23] << std::endl;
  StrmWy << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[0] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[1] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[2] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[3] << std::endl;
    StrmWy << std::endl;
}


/*!
 * \brief Odczyt wspolrzednych graniastoslupu ze strumienia.
 * Metoda służy do odczytu wspolrzednych wierzcholków graniastoslupu z danego strumienia.
 *  \param[in] StrmWej - Strumien z ktorego wspolrzedne maja zostac wczytane.
 */
void Graniastoslup::OdczytWspolrzednychDoStrumienia(std::istream &StrmWej)
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

StrmWej >> Wierzcholek[16];
StrmWej >> Wierzcholek[17];
StrmWej >> Wierzcholek[18];
StrmWej >> Wierzcholek[19];

StrmWej >> Wierzcholek[20];
StrmWej >> Wierzcholek[21];
StrmWej >> Wierzcholek[22];
StrmWej >> Wierzcholek[23];
}


/*!
 * \brief Metoda zapisuje wspolrzedne graniastoslupu do pliku
 * \retval True - jeżeli zapis uda sie pomyslnie.
 * \retval False - jezeli zapis sie nie uda.
 */
  bool Graniastoslup::ZapiszBryle()const
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
 * \brief Metoda odczytuje wspolrzedne graniastoslupu z pliku ze wzorcem graniastoslupu.
* \retval True - jeżeli odczyt uda sie pomyslnie.
 * \retval False - jezeli odczyt sie nie uda.
 */
  bool Graniastoslup::OdczytajBryleWzorcowa()
  {
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
  }

/*!
 *\brief Metoda zastepuje wspolrzedne, wspolrzednymi wzorca (Odpowiednio obrocony i przesuniety).
 * \retval True - jeżeli odczyt wzorca uda sie pomyslnie.
 * \retval False - jezeli odczyt wzorca sie nie uda.
 */
  bool Graniastoslup::UzyjWzorca()
  {
    if(!(*this).OdczytajBryleWzorcowa())
      {
      return false;
      }
    for(int i=0; i<24; i++)
      {
      Wierzcholek[i]=(*this).Skaluj(Wierzcholek[i]);
      }
    (*this).Obrot(KatOrientacji, 'z');
    (*this).Translacja(Polozenie);
    return true;
  }


/*!
 * \brief Metoda sluzaca do przekazywania do strumienia wierzcholkow graniastoslupu.
 * Argumenty:
 *  \param[in] Strm - Strumień, na ktory wierzcholki maja zostac przekazane
 *  \param[in] Gr - Graniastoslup, ktorego wierzcholki maja zostac przekazane
 * Zwraca:
 *  \retval Strumień na który wierzcholki zostaly wypisane
 */
std::ostream& operator << (std::ostream &Strm, const Graniastoslup &Gr)
{
Strm << std::setw(16) << std::fixed << std::setprecision(10) << Gr[1] << std::endl;
Strm << std::setw(16) << std::fixed << std::setprecision(10) << Gr[2] << std::endl;
Strm << std::setw(16) << std::fixed << std::setprecision(10) << Gr[5] << std::endl;
Strm << std::setw(16) << std::fixed << std::setprecision(10) << Gr[6] << std::endl;
Strm << std::setw(16) << std::fixed << std::setprecision(10) << Gr[9] << std::endl;
Strm << std::setw(16) << std::fixed << std::setprecision(10) << Gr[10] << std::endl;
Strm << std::setw(16) << std::fixed << std::setprecision(10) << Gr[13] << std::endl;
Strm << std::setw(16) << std::fixed << std::setprecision(10) << Gr[14] << std::endl;
Strm << std::setw(16) << std::fixed << std::setprecision(10) << Gr[17] << std::endl;
Strm << std::setw(16) << std::fixed << std::setprecision(10) << Gr[18] << std::endl;
Strm << std::setw(16) << std::fixed << std::setprecision(10) << Gr[21] << std::endl;
Strm << std::setw(16) << std::fixed << std::setprecision(10) << Gr[22] << std::endl;
return Strm;
}


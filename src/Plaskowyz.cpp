#include "Plaskowyz.hh"

/*!
 *\file
 *\brief Definicja metod klasy Plaskowyz.
 */

/*!
 * \brief Metoda służąca do indeksowania plaskowyzu.
 * \param[in] Indeks - indeks zadanego punktu plaskowyzu.
 * \retval Wektor3D reprezentujacy dany punkt plaskowyzu,
 */
Wektor3D Plaskowyz::operator [](int Indeks)const
{
    if(Indeks >= 16)
        {
        throw std::runtime_error("Blad: Zly indeks");
        }
    
    return Wierzcholek[Indeks];
}

/*!
 * \brief Metoda służąca do indeksowania plaskowyzu.
 * \param[in] Indeks - indeks zadanego punktu plaskowyzu.
 * \retval Wektor3D reprezentujacy dany punkt plaskowyzu,
 */
Wektor3D& Plaskowyz::operator [](int Indeks)
{
    if(Indeks >= 16)
        {
        throw std::runtime_error("Blad: Zly indeks");
        }
    
    return Wierzcholek[Indeks];
}

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia plaskowyzu.
 * \retval Wektor3D reprezentujacy polozenie plaskowyzu.
 */
  Wektor3D Plaskowyz::WspolPolozenia()const
  {
      return Polozenie;
  }

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia plaskowyzu.
 * \retval referencja do Wektora3D reprezentującego polozenie plaskowyzu.
 */
  Wektor3D& Plaskowyz::WspolPolozenia()
  {
      return Polozenie;
  }

/*!
 * \brief Uzyskiwanie katu orientacji plaskowyzu.
 * \retval Wartosc kata orientacji plaskowyzu.
 */
  double Plaskowyz::Orientacja()const
  {
      return KatOrientacji;
  }

/*!
 * \brief Uzyskiwanie katu orientacji polozenia plaskowyzu.
 * \retval referencja do katu orientacji plaskowyzu.
 */
  double& Plaskowyz::Orientacja()
  {
      return KatOrientacji;
  }

  /*!
 * \brief Obliczenie wspolrzednych polozenia plaskowyzu.
 * Metoda wylicza wspolrzedne polozenia plaskowyzu na podstawie
 * wiercholkow jego podstawy. Za wspolrzednie polozenia przyjmuje sie
 * srodek podstawy prostopadloscianu.
 */
  void Plaskowyz::ObliczPolozenie()
  {
      Polozenie = Wierzcholek[9];
      Polozenie += Wierzcholek[10];
      Polozenie += Wierzcholek[13];
      Polozenie += Wierzcholek[14];
      Polozenie = 0.25 * Polozenie;

  }

  /*!
 * \brief Operator przypisania dla plaskowyzu
 * \param[in] P - Plaskowyz, z wartosciami ktore maja zostac przypisane.
 * \retval Plaskowyz z nowymi wartosciami.
 */
Plaskowyz& Plaskowyz::operator= (const Plaskowyz P)
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
 *\brief Konstruktor bezparamateryczny plaskowyzu.
 */
Plaskowyz::Plaskowyz():
BrylaGeometryczna(TB_Plaskowyz), ObiektSceny(OB_Plaskowyz), Polozenie({0,0,0}), KatOrientacji(0)
{
  for(int i=0; i<16; i++)
    {
    Wierzcholek[i]={0,0,0};
    }
}

/*!
 *\brief Konstruktor parametryczny plaskowyzu.
 *  \param[in] WspolPolozenia - Wspolrzedne polozenia srodka plaskowyzu
 *  \param[in] Kat - Kat orientacji plaskowyzu.
 *  \param[in] NazwaBryly - Nazwa pliku z wspolrzednymi bryly finalnej.
 *  \param[in] NazwaWzorca - Nazwa pliku z wspolrzednymi bryly wzorcowej.
 *  \param[in] SkalaBryly - Skala, mowiaca o rozmiarze bryly.
 */
Plaskowyz::Plaskowyz(Wektor3D WspolPolozenia, double Kat, std::string Nazwa, std::string NazwaWzorca, Wektor3D SkalaBryly):
BrylaGeometryczna(TB_Plaskowyz, Nazwa, NazwaWzorca, SkalaBryly), ObiektSceny(OB_Plaskowyz),  Polozenie(WspolPolozenia), KatOrientacji(Kat)
{
(*this).OdczytajBryleWzorcowa();
for(int i=0; i<16; i++)
    {
    Wierzcholek[i] = (*this).Skaluj(Wierzcholek[i]);
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
(*this).ZapiszBryle();
}

/*!
 * \brief Konstruktor kopiujacy.
 * \param[in] P - Plaskowyz ktory ma zostac skopiowany.
 */
Plaskowyz::Plaskowyz(const Plaskowyz &P):
BrylaGeometryczna(TB_Plaskowyz, P.NazwaPlikuBryly(), P.NazwaPlikuBrylyWzorcowej(), P.SkalaBryly()), ObiektSceny(OB_Plaskowyz), Polozenie(P.WspolPolozenia()), KatOrientacji(P.Orientacja())
{
  for(int i=0; i<16; i++)
    {
    Wierzcholek[i] = P[i];
    }
  (*this).ZapiszBryle();
}

/*!
 * \brief Metoda służąca do obrotu plaskowyzu o zadany kat wokol osi x,y,z.
 * UWAGA: Metoda nie sprawdza czy podano poprawna os (mozliwe opcje to x,y oraz z).
 *  \param[in] Kat - Kat obrotu.
 *  \param[in] Os - Os obrotu.
 *   \retval Obrocony plaskowyz.
 */
Plaskowyz& Plaskowyz::Obrot(double Kat, char Os)
{
    for(int i=0; i<16; i++)
    {
    (*this)[i] = MacierzObrotu(Kat, Os) * (*this)[i];  //Wymnożenie każdego wierzcholka przez macierz obrotu
    }               
    return *this;
}

/*!
 * \brief Metoda służąca do przesuniecie plaskowyzu o zadany wektor
 *  \param[in] Wektor - Wektor przesuniecia.
 *   \retval Przesuniety plaskowyz.
 */
Plaskowyz& Plaskowyz::Translacja(Wektor3D Wektor)
{
    for(int i=0; i<16; i++)
    {
    (*this)[i] += Wektor;
    }
    return (*this);
}

/*!
 * \brief Zapis wspolrzednych plaskowyzu do strumienia.
 * Metoda służy do zapisu wspolrzednych  plaskowyzu do danego strumienia,
 * w celu zapisu go do pliku, ktory bedzie rysowac gnuplot.
 * przy wykonywaniu rysunku.
 *  \param[in] StrmWy - Strumien na ktory wspolrzedne maja zostac wypisane.
 */
void Plaskowyz::ZapisWspolrzednychDoStrumienia(std::ostream &StrmWy)const
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
 * \brief Odczyt wspolrzednych  plaskowyzu ze strumienia.
 * Metoda służy do odczytu wspolrzednych wierzcholków plaskowyzu z danego strumienia.
 *  \param[in] StrmWej - Strumien z ktorego wierzcholki maja zostac wczytane.
 */
void Plaskowyz::OdczytWspolrzednychDoStrumienia(std::istream &StrmWej)
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
 * \brief Metoda zapisuje wspolrzedne plaskowyzu do pliku
 * \retval True - jeżeli zapis uda sie pomyslnie.
 * \retval False - jezeli zapis sie nie uda.
 */
  bool Plaskowyz::ZapiszBryle()const
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
 * \brief Metoda odczytuje wspolrzedne plaskowyzu z pliku ze wzorcem plaskowyzu.
 * \retval True - jeżeli odczyt uda sie pomyslnie.
 * \retval False - jezeli odczyt sie nie uda.
 */
  bool Plaskowyz::OdczytajBryleWzorcowa()
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
 *\brief Metoda zwracajaca nazwe pliku wybranej bryly obiektu sceny.
 *\param[in] NumerBryly - Numer bryly, ktorej nazwa ma zostac zwrocona.
 * Dla klasy Plaskowyz numer nie ma znaczenia.
 * \return Nazwa pliku wybranej bryly.
 */
std::string Plaskowyz::WezNazweBryly(int NumerBryly)const
{
  NumerBryly++;
  return (*this).NazwaPlikuBryly();
}
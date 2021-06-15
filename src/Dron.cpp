#include "Dron.hh"

#include "Wektor3D.hh"

/*!
 *\file
 *\brief Definicja metod dla klasy Dron.
 */

/*!
 *\brief Operator przypisania dla klasy Dron
 *\param[in] D - Dron, ktorego parametry maja zostac przypisane
 *\retval Dron z nowymi parametrami
 */
Dron& Dron::operator= (Dron D)
{
  (*this).Korpus = D.Korpus;
  (*this).Rotor[0] = D.Rotor[0];
  (*this).Rotor[1] = D.Rotor[1];
  (*this).Rotor[2] = D.Rotor[2];
  (*this).Rotor[3] = D.Rotor[3];
  (*this).Polozenie = D.WspolPolozenia();
  (*this).KatOrientacji = D.Orientacja();
  return (*this);
}
/*!
 *\brief Metoda uzyskujaca wektor3D reprezentujacy wspolrzedne polozenia drona.
 *\retval Wektor3D reprezentujacy wspolrzedne polozenia drona.
 */
Wektor3D Dron::WspolPolozenia()const
{
    return Polozenie;
}

/*!
 *\brief Metoda uzyskujaca dostep do wektora3D reprezentujacego wspolrzedne polozenia drona.
 *\retval referencja do Wektora3D reprezentujacego wspolrzedne polozenia drona.
 */
Wektor3D& Dron::WspolPolozenia() 
{
    return Polozenie;
}

/*!
 *\brief Metoda uzyskujaca kat orientacji drona.
 *\retval Wartosc kata orientacji drona.
 */
double Dron::Orientacja()const
{
    return KatOrientacji;
}

/*!
 *\brief Metoda uzyskujaca dostep do kata  orientacji drona.
 *\retval referencja do wartosci kata orientacji drona.
 */
double& Dron::Orientacja()
{
    return KatOrientacji;
}


/*!
 *\brief Metoda obliczajaca wspolrzedne polozenia korupsu drona
 * oraz jego rotortow. Za wspolrzedne polozenia calego drona 
 * przyjmuje sie polozenie jego korpusu.
 */
void Dron::ObliczPolozenie()
{
    Korpus.ObliczPolozenie();
    (*this).WspolPolozenia()=Korpus.WspolPolozenia();
    for(int i=0; i<4; i++)
    {
        Rotor[i].ObliczPolozenie();
    }
}

/*!
 *\brief Konstruktor bezparametryczny drona.
 */
Dron::Dron():
ObiektSceny(OB_Dron)
{
    Korpus = Prostopadloscian();
    Rotor[0] = Graniastoslup();
    Rotor[1] = Graniastoslup();
    Rotor[2] = Graniastoslup();
    Rotor[3] = Graniastoslup();
}

/*!
 *\brief Konstruktor parametryczny drona.
 * Rotory drona, sa tworzone na podstawie wierzcholkow jego gornej
 * podstawy.
 *\param[in] PolozenieDrona - wspolrzedne polozenia korpusu drona.
 *\param[in] Kat - kat orientacji korpusu drona.
 *\param[in] Nazwa - nazwa drona.
 */
Dron::Dron(Wektor3D PolozenieDrona,double Kat, std::string Nazwa):
ObiektSceny(OB_Dron)
{
    Korpus = Prostopadloscian(PolozenieDrona, Kat, "../data/" + Nazwa + "_Korpus.dat", "../BrylyWzorcowe/ProstopadloscianWzorcowy.dat", Wektor3D{5,5,5});
    Rotor[0] = Graniastoslup(Korpus[1], Kat, "../data/" + Nazwa+"_Rotor1.dat", "../BrylyWzorcowe/GraniastoslupWzorcowy.dat", Wektor3D{4,4,4});
    Rotor[1] = Graniastoslup(Korpus[2], Kat, "../data/" + Nazwa+"_Rotor2.dat", "../BrylyWzorcowe/GraniastoslupWzorcowy.dat", Wektor3D{4,4,4});
    Rotor[2] = Graniastoslup(Korpus[5], Kat, "../data/" + Nazwa+"_Rotor3.dat", "../BrylyWzorcowe/GraniastoslupWzorcowy.dat", Wektor3D{4,4,4});
    Rotor[3] = Graniastoslup(Korpus[6], Kat, "../data/" + Nazwa+"_Rotor4.dat", "../BrylyWzorcowe/GraniastoslupWzorcowy.dat", Wektor3D{4,4,4});
    KatOrientacji=Kat;
    while(KatOrientacji<= -360 || KatOrientacji >= 360)
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
    (*this).ObliczPolozenie();
    (*this).ZapiszBryly();
}
/*!
 *\brief Metoda zapisujaca korpus i rotory dron do plikow z ich brylami.
 * \retval True - jeżeli zapis uda sie pomyslnie.
 * \retval False - jezeli zapis ktorejs z bryl sie nie uda
 */
bool Dron::ZapiszBryly()const
{
    if(!Korpus.ZapiszBryle())
        {
        throw std::runtime_error("Odczyt plikow sie nie powiodl");   
        return false;
        }
    for(int i=0; i<4; i++)
        {
        if(!Rotor[i].ZapiszBryle())
            {
            throw std::runtime_error("Odczyt plikow sie nie powiodl");    
            return false;
            }
        }
    return true;
}

/*!
 *\brief Metoda transformujaca drona do ukladu wspolrzednych jego korpusu.
 */
void Dron::TransformujDoUkladuRodzica()
{
    Korpus.Translacja((-1*Polozenie));
    Rotor[0].Translacja((-1*Polozenie));
    Rotor[1].Translacja((-1*Polozenie));
    Rotor[2].Translacja((-1*Polozenie));
    Rotor[3].Translacja((-1*Polozenie));
    Korpus.Obrot((KatOrientacji*-1),'z');
    Rotor[0].Obrot((KatOrientacji*-1),'z');
    Rotor[1].Obrot((KatOrientacji*-1),'z');
    Rotor[2].Obrot((KatOrientacji*-1),'z');
    Rotor[3].Obrot((KatOrientacji*-1),'z');
}

/*!
 *\brief Metoda transformujaca drona do globalnego ukladu wspolrzednych
 */
void Dron::TransformujDoUkladuGlobalnego()
{
    Korpus.Obrot((KatOrientacji),'z');
    Rotor[0].Obrot((KatOrientacji),'z');
    Rotor[1].Obrot((KatOrientacji),'z');
    Rotor[2].Obrot((KatOrientacji),'z');
    Rotor[3].Obrot((KatOrientacji),'z');
    Korpus.Translacja((Polozenie));
    Rotor[0].Translacja((Polozenie));
    Rotor[1].Translacja((Polozenie));
    Rotor[2].Translacja((Polozenie));
    Rotor[3].Translacja((Polozenie));
}

/*!
 *\brief Metoda obraca calego drona o zadany kat wzgledem osi Z korpusu.
 * Metoda przeksztalca dron do wlasnego ukladu wspolrzednych, obraca go,
 * a nastepnie przywraca do lokalnego ukladu wspolrzednych.
 * \param[in] Kat - Kat obrotu drona.
 */
void Dron::Obrot(double Kat)
{
    (*this).TransformujDoUkladuRodzica();
    Korpus.Obrot(Kat,'z');
    Rotor[0].Obrot(Kat,'z');
    Rotor[1].Obrot(Kat,'z');
    Rotor[2].Obrot(Kat,'z');
    Rotor[3].Obrot(Kat,'z');
    (*this).TransformujDoUkladuGlobalnego();

    (*this).ObliczPolozenie();

    KatOrientacji+=Kat;
    Korpus.Orientacja()+=Kat;
    while(KatOrientacji<= -360 || KatOrientacji >= 360)
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

}
/*!
 *\brief Metoda podnosi drona na dana wysokosc.
 *\param[in] Wysokosc - wysokosc na jaka drona ma zostac podniesiony
 * wzgledem jego poprzedniej wysokosci.
 */
void Dron::Wzniesienie(double Wysokosc)
{
    Wektor3D Przesuniecie{0,0,Wysokosc};
    Korpus.Translacja(Przesuniecie);
    Rotor[0].Translacja(Przesuniecie);
    Rotor[1].Translacja(Przesuniecie);
    Rotor[2].Translacja(Przesuniecie);
    Rotor[3].Translacja(Przesuniecie);

    (*this).ObliczPolozenie();
}

/*!
 *\brief Metoda opuszcza drona o dana wysokosc.
 *\param[in] Wysokosc - wysokosc o jaka drona ma zostac opuszczony
 * wzgledem jego poprzedniej wysokosci.
 */
void Dron::Opadanie(double Wysokosc)
{
    Wektor3D Przesuniecie{0,0,-Wysokosc};
    Korpus.Translacja(Przesuniecie);
    Rotor[0].Translacja(Przesuniecie);
    Rotor[1].Translacja(Przesuniecie);
    Rotor[2].Translacja(Przesuniecie);
    Rotor[3].Translacja(Przesuniecie); 

    (*this).ObliczPolozenie();
}

/*!
 *\brief Metoda obraca wygrany rotor o zadany kat wzgledem jego wlasnej osi Z.
 * Metoda najpierw sprowadza rotor do jego wlasnego ukladu wspolrzednych, po czym
 * obraca go, a nastepnie przywraca do globalnego ukladu wspolrzednych
 *\param[in] Indeks - indeks wybranego rotora.
 *\param[in] Kat - o jaki rotor ma zostac obrocony.
 */
void Dron::ObrotRotora(int Indeks, double Kat)
{
    if(Indeks >=4)
        {
        throw std::runtime_error("Blad: Zly indeks rotora");
        }

    Rotor[Indeks].TransformujDoUkladuRodzica();
    Rotor[Indeks].Obrot(Kat, 'z');
    Rotor[Indeks].TransformujDoUkladuGlobalnego();

    Rotor[Indeks].Orientacja() += Kat;
    while(Rotor[Indeks].Orientacja()<= -360 || Rotor[Indeks].Orientacja() >= 360)
    {
    if(Rotor[Indeks].Orientacja()<= -360)
        {
        Rotor[Indeks].Orientacja() +=360;
        }
    if(Rotor[Indeks].Orientacja()>= 360)
        {
        Rotor[Indeks].Orientacja() -=360;
        }    
    }

  (*this).ObliczPolozenie();

}

/*!
 *\brief Metoda przemieszcza drona od zadana odleglosc.
 * Przemieszczenie odbywa sie wzdloz prostej o takim samym kacie,
 * jak kat orientacji.
 *\param[in] Odleglosc - Dlugosc o jaka dron ma zostac przemieszczony.
 */
void Dron::Przemieszczenie(double Odleglosc)
{
    Wektor3D Przesuniecie{Odleglosc,0,0};
    Przesuniecie = MacierzObrotu(KatOrientacji, 'z') * Przesuniecie;
    Korpus.Translacja(Przesuniecie);
    Rotor[0].Translacja(Przesuniecie);
    Rotor[1].Translacja(Przesuniecie);
    Rotor[2].Translacja(Przesuniecie);
    Rotor[3].Translacja(Przesuniecie);
    (*this).ObliczPolozenie();
}
    
/*!
 *\brief Metoda zastepuje bryly drona brylami wzorcowymi,
 ktore zostaja odpowiednio przemieszczone i obroce, tak
 aby zgadzaly sie z polozeniem aktualnego drona.
 * \retval True - jeżeli oczyt uda sie pomyslnie.
 * \retval False - jezeli odczyt ktorejs z bryl sie nie uda
 */
bool Dron::UzyjWzorca()
{
    (*this).ObliczPolozenie();
    if(!Korpus.UzyjWzorca())
        {
        throw std::runtime_error("Odczyt plikow sie nie powiodl");
        return false;
        }
    for(int i=0; i<4; i++)
        {
        if(!Rotor[i].UzyjWzorca())
            {
            throw std::runtime_error("Odczyt plikow sie nie powiodl");
            return false;
            }
        }
    (*this).ZapiszBryly();
    return true;
}


/*!
 *\brief Metoda rysujaca trase przelotu drona po prostej trasie.
 * Metoda rysuje trase polegajaca na podniesieniu sie drona,
 * obrocie i przelocie o zadana odleglosc pod zadanym katem,
 * a nastepnie opuszczeniu na plaszczyzne.
 * \param[in] Odlegosc - Dlugosc przelotu drona.
 * \param[in] Kat - kat obrotu drona.
 * \param[in] LaczeDoGnuplota - Lacze do gnuplota, ktore ma rysowac trase
 * \retval True, jezeli uda sie zapisac trase do pliku.
 * \retval False, jezeli nie uda sie zapisaac trase do pliku.
 */
bool Dron::RysujTrase(double Odleglosc, double Kat, PzG::LaczeDoGNUPlota  &LaczeDoGnuplota)
    {
    Wektor3D PunktDocelowy = MacierzObrotu(((*this).Orientacja()+Kat), 'z') * Wektor3D{Odleglosc,0,0};     //Obliczenie punktu koncowego trasy
    PunktDocelowy += (*this).WspolPolozenia();
    std::ofstream  StrmPlikowy;
    StrmPlikowy.open("../data/TrasaPrzelotu.dat");
    if (!StrmPlikowy.is_open())  
        {
        std::cerr << "Operacja otwarcia do zapisu " << "TrasaPrzelotu.dat" << std::endl << " nie powiodla sie." << std::endl;
        return false;
        }
    
    StrmPlikowy << (*this).WspolPolozenia() << std::endl;
    StrmPlikowy << ((*this).WspolPolozenia() + Wektor3D{0,0,60}) << std::endl;
    StrmPlikowy << (PunktDocelowy + Wektor3D{0,0,60}) << std::endl;
    StrmPlikowy << PunktDocelowy << std::endl;    
    
    StrmPlikowy.close();

    LaczeDoGnuplota.DodajNazwePliku("../data/TrasaPrzelotu.dat");
    LaczeDoGnuplota.Rysuj();

    return true;
    }

/*!
 *\brief Metoda rysujaca trase przelotu drona po okregu.
 * Metoda rysuje trase polegajaca na podniesieniu sie drona,
 * obrocie i przelocie o zadana odleglosc pod zadanym katem,
 * a nastepnie opuszczeniu na plaszczyzne.
 * \param[in] Promien - Promien okregu po jakim dron bedzie sie przemieszczal.
 * \param[in] LaczeDoGnuplota - Lacze do gnuplota, ktore ma rysowac trase
 * \retval True, jezeli uda sie zapisac trase do pliku.
 * \retval False, jezeli nie uda sie zapisaac trase do pliku.
 */
bool Dron::RysujTrasePoOkregu(double Promien, PzG::LaczeDoGNUPlota  &LaczeDoGnuplota)
{
    std::ofstream  StrmPlikowy;
    StrmPlikowy.open("../data/TrasaPrzelotu.dat");
    if(!StrmPlikowy.is_open())  
        {
        std::cerr << "Operacja otwarcia do zapisu " << "TrasaPrzelotu.dat" << std::endl << " nie powiodla sie." << std::endl;
        return false;
        }
    
    Wektor3D Punkt=Polozenie;

    StrmPlikowy << Polozenie << std::endl;
    Punkt += Wektor3D{0,0,60};
    StrmPlikowy << Punkt << std::endl;
    Punkt += MacierzObrotu((*this).Orientacja(), 'z') * Wektor3D{Promien,0,0};
    StrmPlikowy << Punkt << std::endl;
    for(int i=0; i<180; i++)
        {
        Punkt += MacierzObrotu((*this).Orientacja() +(2*i) + 90, 'z') * Wektor3D{(Promien*0.03490481288),0,0};
        StrmPlikowy << Punkt << std::endl;
        }

    StrmPlikowy.close();

    LaczeDoGnuplota.DodajNazwePliku("../data/TrasaPrzelotu.dat");
    LaczeDoGnuplota.Rysuj();
    return true;
}

/*!
 *\brief Metoda realizuje przelot drona.
 * Jego przemieszenie odbywa sie w sposob animowany.
 * Dron podnosi sie, obraca o odpowiedni kat, przelatuje
 * o zadana odleglosc (Podczas przelotu jego rotory odpowiednio
 * wiruja), a na koniec opuszcza sie na plaszczyzne.
 * \param[in] Odlegosc - Dlugosc przelotu drona.
 * \param[in] Kat - kat obrotu drona.
 * \param[in] LaczeDoGnuplota - Lacze do gnuplota, ktore rysowac ruch drona
 * \retval True, jezeli operacja wykona sie poprawnie
 * \retval False, jezeli podczas operacji wystapia bledy
 */
bool Dron::PrzemiescDrona(double Odleglosc, double Kat, PzG::LaczeDoGNUPlota  &LaczeDoGnuplota)
    {
        int i=0;

        if(Odleglosc<0)
            {
            std::cout << std::endl << "Odleglosc nie moze byc ujemna!" << std::endl;
            return false;
            }
        std::cout <<std::endl << "Rysowanie trasy..." << std::endl;     //Rysowanie trasy
        if(!(*this).RysujTrase(Odleglosc, Kat, LaczeDoGnuplota))
            {
            throw std::runtime_error("Blad zapisu trasy");
            return false;
            }
        usleep(3000000);

        std::cout << std::endl << "Podnoszonie drona..." << std::endl;  //Podnoszenie drona
        for(i=0; i<60; i++)
            {
            (*this).Wzniesienie(1);
            (*this).ObrotRotora(0,10);
            (*this).ObrotRotora(1,-10);
            (*this).ObrotRotora(2,-10);
            (*this).ObrotRotora(3,10);
            if(!(*this).ZapiszBryly())
                {
                return false;
                }
            LaczeDoGnuplota.Rysuj();
            usleep(40000);
            }
        if(!(*this).UzyjWzorca())
            {
            return false;
            }


        std::cout << std::endl << "Obrot drona..."  << std::endl;       //Obrot drona;
        for(i=0; i<abs(Kat); i++)
            {
            if(Kat>0)
                {
                (*this).Obrot(1);
                }
            else
                {
                (*this).Obrot(-1);
                }
            (*this).ObrotRotora(0,10);
            (*this).ObrotRotora(1,-10);
            (*this).ObrotRotora(2,-10);
            (*this).ObrotRotora(3,10);
            if(!(*this).ZapiszBryly())
                {
                return false;
                }
            LaczeDoGnuplota.Rysuj();
            usleep(40000);
            }
        if(!(*this).UzyjWzorca())
            {
            return false;
            }

        std::cout << std::endl << "Lot Drona..."  << std::endl;       //Lot drona;
        for(i=0; i<Odleglosc; i++)
            {
            (*this).Przemieszczenie(1);
            (*this).ObrotRotora(0,10);
            (*this).ObrotRotora(1,-10);
            (*this).ObrotRotora(2,-10);
            (*this).ObrotRotora(3,10);
            if(!(*this).ZapiszBryly())
                {
                return false;
                }
            LaczeDoGnuplota.Rysuj();
            usleep(40000);
            }
        if(!(*this).UzyjWzorca())
            {
            return false;
            }
        
        

        std::cout << std::endl << "Opadanie drona..." << std::endl;  //Opadanie
        for(i=0; i<60; i++)
            {
            (*this).Opadanie(1);
            (*this).ObrotRotora(0,7.5);
            (*this).ObrotRotora(1,-7.5);
            (*this).ObrotRotora(2,-7.5);
            (*this).ObrotRotora(3,7.5);
            if(!(*this).ZapiszBryly())
                {
                return false;
                }
            LaczeDoGnuplota.Rysuj();
            usleep(60000);
            }
        if(!(*this).UzyjWzorca())
            {
            return false;
            }

        std::cout<< std::endl << "Usuwanie trasy..." << std::endl;     //Usuwanie trasy
        LaczeDoGnuplota.UsunOstatniaNazwe();
        LaczeDoGnuplota.Rysuj();
        usleep(3000000);

        return true;
    }


/*!
 *\brief Metoda realizuje przelot aktywnego drona.
 * Jego przemieszenie odbywa sie w sposob animowany.
 * Dron podnosi sie, przelatuje na okrag, a nastepnie obraca sie,
 * aby stac w pozycji stycznej do okregu. Nastepnie wykonuje przelot
 * w po okregu, a na koniec wraca do swojego pierwotnego polozenia.
 * \param[in] Promien - Promien okregu, po jakim dron bedzie sie przemieszczal.
 * \param[in] LaczeDoGnuplota - Lacze do gnuplota, ktore rysowac ruch drona
 * \retval True, jezeli operacja wykona sie poprawnie
 * \retval False, jezeli podczas operacji wystapia bledy
 */
bool Dron::RuchPoOkregu(double Promien, PzG::LaczeDoGNUPlota  &LaczeDoGnuplota)
    {

        int i=0;

        if(Promien <= 0)
            {
            std::cout << std::endl << "Promien nie moze byc mniejszy badz rowny zero" << std::endl << std::endl;
            return false;
            }

        if(Promien<0)
            {
            std::cout << std::endl << "Promien nie moze być ujemny!" << std::endl;
            return false;
            }

        Wektor3D WspolPoloz = Polozenie;
        double Kat = KatOrientacji;

        std::cout <<std::endl << "Rysowanie trasy..." << std::endl;     //Rysowanie trasy
        if(!(*this).RysujTrasePoOkregu(Promien, LaczeDoGnuplota))
            {
            throw std::runtime_error("Blad zapisu trasy");
            return false;
            }
        usleep(3000000);

        std::cout << std::endl << "Podnoszonie drona..." << std::endl;  //Podnoszenie drona
        for(i=0; i<60; i++)
            {
            (*this).Wzniesienie(1);
            (*this).ObrotRotora(0,10);
            (*this).ObrotRotora(1,-10);
            (*this).ObrotRotora(2,-10);
            (*this).ObrotRotora(3,10);
            if(!(*this).ZapiszBryly())
                {
                return false;
                }
            LaczeDoGnuplota.Rysuj();
            usleep(40000);
            }
        if(!(*this).UzyjWzorca())
            {
            return false;
            }


        std::cout << std::endl << "Przemieszczenie na okrag..."  << std::endl;       //Przemieszczenie na okrag
        for(i=0; i<Promien; i++)
            {
            (*this).Przemieszczenie(1);
            (*this).ObrotRotora(0,10);
            (*this).ObrotRotora(1,-10);
            (*this).ObrotRotora(2,-10);
            (*this).ObrotRotora(3,10);
            if(!(*this).ZapiszBryly())
                {
                return false;
                }
            LaczeDoGnuplota.Rysuj();
            usleep(40000);
            }
        if(!(*this).UzyjWzorca())
            {
            return false;
            }

        std::cout << std::endl << "Obrot drona..."  << std::endl;       //Obrot drona;
        for(i=0; i<90; i++)
            {
            (*this).Obrot(1);
            (*this).ObrotRotora(0,10);
            (*this).ObrotRotora(1,-10);
            (*this).ObrotRotora(2,-10);
            (*this).ObrotRotora(3,10);
            if(!(*this).ZapiszBryly())
                {
                return false;
                }
            LaczeDoGnuplota.Rysuj();
            usleep(40000);
            }
        if(!(*this).UzyjWzorca())
            {
            return false;
            }
        

        std::cout << std::endl << "Lot po okregu..."  << std::endl;       //Lot po okregu;
        for(i=0; i<180; i++)
            {
            (*this).Obrot(2);
            (*this).Przemieszczenie(Promien*0.03490481288);
            (*this).ObrotRotora(0,(Promien/2.0));
            (*this).ObrotRotora(1,-(Promien/2.0));
            (*this).ObrotRotora(2,-(Promien/2.0));
            (*this).ObrotRotora(3,(Promien/2.0));
            if(!(*this).ZapiszBryly())
                {
                return false;
                }
            LaczeDoGnuplota.Rysuj();
            usleep(Promien*2000);
            }
        if(!(*this).UzyjWzorca())
            {
            return false;
            }
        
        std::cout << std::endl << "Obrot drona..."  << std::endl;       //Obrot drona;
        for(i=0; i<90; i++)
            {
            (*this).Obrot(1);
            (*this).ObrotRotora(0,10);
            (*this).ObrotRotora(1,-10);
            (*this).ObrotRotora(2,-10);
            (*this).ObrotRotora(3,10);
            if(!(*this).ZapiszBryly())
                {
                return false;
                }
            LaczeDoGnuplota.Rysuj();
            usleep(40000);
            }
        if(!(*this).UzyjWzorca())
            {
            return false;
            }

        std::cout << std::endl << "Przemieszczenie na srodek okregu"  << std::endl;       //Przemieszczenie na srodek okragu
        for(i=0; i<Promien; i++)
            {
            (*this).Przemieszczenie(1);
            (*this).ObrotRotora(0,10);
            (*this).ObrotRotora(1,-10);
            (*this).ObrotRotora(2,-10);
            (*this).ObrotRotora(3,10);
            if(!(*this).ZapiszBryly())
                {
                return false;
                }
            LaczeDoGnuplota.Rysuj();
            usleep(40000);
            }
        if(!(*this).UzyjWzorca())

        std::cout << std::endl << "Powrot do pierwotnego kata orientacji..."  << std::endl;       //Obrot drona;
        for(i=0; i<180; i++)
            {
            (*this).Obrot(1);
            (*this).ObrotRotora(0,10);
            (*this).ObrotRotora(1,-10);
            (*this).ObrotRotora(2,-10);
            (*this).ObrotRotora(3,10);
            if(!(*this).ZapiszBryly())
                {
                return false;
                }
            LaczeDoGnuplota.Rysuj();
            usleep(40000);
            }
        if(!(*this).UzyjWzorca())
            {
            return false;
            }
            
            

        std::cout << std::endl << "Opadanie drona..." << std::endl;  //Opadanie
        for(i=0; i<60; i++)
            {
            (*this).Opadanie(1);
            (*this).ObrotRotora(0,7.5);
            (*this).ObrotRotora(1,-7.5);
            (*this).ObrotRotora(2,-7.5);
            (*this).ObrotRotora(3,7.5);
            if(!(*this).ZapiszBryly())
                {
                return false;
                }
            LaczeDoGnuplota.Rysuj();
            usleep(60000);
            }

        Polozenie = WspolPoloz;
        KatOrientacji = Kat;
        if(!(*this).UzyjWzorca())
            {
            return false;
            }

        std::cout<< std::endl << "Usuwanie trasy..." << std::endl;     //Usuwanie trasy
        LaczeDoGnuplota.UsunOstatniaNazwe();
        LaczeDoGnuplota.Rysuj();
        usleep(3000000);

        return true;
    }

/*!
 *\brief Metoda zwracajaca nazwe pliku wybranej bryly obiektu sceny.
 *\param[in] NumerBryly - Numer bryly, ktorej nazwa ma zostac zwrocona.
 * Dla klasy Dron wartosc 0 zwraca nazwe korpusu, natomiast wartosci od
 * 1 do 4 zwracaja nazwy odpowiednich rotorow.
 * \return Nazwa pliku wybranej bryly.
 */
std::string Dron::WezNazweBryly(int NumerBryly)const
{
if(NumerBryly==0)
    {
    return (*this).Korpus.NazwaPlikuBryly();
    }
else if (NumerBryly >0 && NumerBryly <5)
    {
    return (*this).Rotor[NumerBryly-1].NazwaPlikuBryly();
    }
else
    {
    throw std::runtime_error("Blad: Zly numer bryly");
    }
}
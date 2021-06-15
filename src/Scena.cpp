#include "Scena.hh"

/*!
 *\file
 *\brief Definicja metod klasy Scena
 */

/*!
 *\brief Konstruktor bezparametryczny sceny.
 * Konstruktor tworzy scene. Ustawia zakresy oraz tryb
 * rysowania jej lacza do gnuplota oraz dodaj do sceny
 * plaszczyzne.
 */
Scena::Scena()
{
    Lacze.DodajNazwePliku("../BrylyWzorcowe/Plaszczyzna.dat",PzG::RR_Ciagly,2);
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.UstawZakresY(0,200);
    Lacze.UstawZakresX(0,200);
    Lacze.UstawZakresZ(0,120);
}

/*!
 *\brief Metoda dodajaca drona do sceny.
 * Metoda dodaje do sceny dron na pozycje o zadanym numerze.
 * UWAGA: Metoda nie dodaje nazw plikow z brylami do lacza.
 * \param[in] NrDrona - Numer w tablicy dronow, jaki tworzony dron ma przyjac.
 * \param[in] Polozenie - Wspolrzedne polozenia drona.
 * \param[in] Kat - Kat orientacji drona.
 * \param[in] NazwaDrona - Nazwa drona.
 */
void Scena::DodajDrona(Wektor3D Polozenie, double Kat, std::string NazwaDrona)
{
    ListaObiektow.push_back(std::make_shared<Dron>(Polozenie,Kat,NazwaDrona));
    (*this).DodajNazwePliku("../data/" + NazwaDrona+"_Korpus.dat");
    (*this).DodajNazwePliku("../data/" + NazwaDrona+"_Rotor1.dat");
    (*this).DodajNazwePliku("../data/" + NazwaDrona+"_Rotor2.dat");
    (*this).DodajNazwePliku("../data/" + NazwaDrona+"_Rotor3.dat");
    (*this).DodajNazwePliku("../data/" + NazwaDrona+"_Rotor4.dat");
}

/*!
 *\brief Metoda dodaje do lacza nazwe pliku, z bryla ktora ma zostac rysowana.
 *\param[in] NazwaPliku - nazwa pliku, ktora ma zostac dodana do lacza.
 */
bool Scena::DodajNazwePliku(const std::string NazwaPliku)
{
    const char *Nazwa= NazwaPliku.c_str();
    if(Lacze.DodajNazwePliku(Nazwa,PzG::RR_Ciagly,2))
        {
        return true;
        }
    else
        {
        return false;
        }
}


/*!
 *\brief Metoda uzyskujaca numer aktywnego drona.
 *\retval - Numer aktywnego drona.
 */
int Scena::NumerAktywnegoDrona()const
{
    return NrAktywnegoDrona;
}

/*!
 *\brief Metoda uzyskujaca dostep do aktywnego drona.
 *\retval Referencja do numeru aktywnego drona.
 */
int& Scena::NumerAktywnegoDrona()
{
    return NrAktywnegoDrona;
}

/*!
 *\brief Metoda uzyskujaca dostep do aktywnego drona.
 *\retval referencja do aktywnego drona.
 */
Dron* Scena::AktywnyDron()
{
    int NumerDrona=1;
    for (std::list<std::shared_ptr<ObiektSceny>>::iterator Iter = ListaObiektow.begin();  Iter != ListaObiektow.end();  ++Iter)
        {
        if((*Iter)->TypObiektu() == OB_Dron)
            {
            if(NumerDrona == (*this).NumerAktywnegoDrona())
                {
                return (Dron*) Iter->get();
                }
            else
                {
                ++NumerDrona;
                }
            } 
        }
    throw std::runtime_error("Blad: Brak dronow");
    
}

/*!
 *\brief Metoda wypisujaca liste dronow.
 * Metoda wypisuje wszystkie drony, ktore znajduja sie na liscie obiektow
 * oraz wskazuje, ktory dron jest aktywny
 */
void Scena::ListaDronow()
{
Dron* WskDron;
int i=0;
for (std::list<std::shared_ptr<ObiektSceny>>::iterator Iter = ListaObiektow.begin();  Iter != ListaObiektow.end();  ++Iter)
    {
    if((*Iter)->TypObiektu() == OB_Dron)
        {
        ++i;
        WskDron = (Dron*) Iter->get();
        std::cout << i << " - Polozenie drona: (x,y) " << WskDron->WspolPolozenia()[0] << " " << WskDron->WspolPolozenia()[1];
        if(i == NrAktywnegoDrona)
            {
            std::cout<< " <-- Aktywny dron";
            }
        std::cout << std::endl;
        }
    }
std::cout << std::endl;
}

/*!
 *\brief Metoda wypisujaca na strumieniu wyjsciowym liste przeszkod znajdujacych na scenie.
 */
void Scena::ListaPrzeszkod()
{
Plaskowyz* WskPlaskowyz;
GoraZGrania* WskGoraZGrania;
GoraZeSzczytem* WskGoraZeSzczytem;
int i=0;

for (std::list<std::shared_ptr<ObiektSceny>>::iterator Iter = ListaObiektow.begin();  Iter != ListaObiektow.end();  ++Iter)
    {
    switch((*Iter)->TypObiektu())
        {
        case OB_Plaskowyz:
            {
            ++i;
            WskPlaskowyz = (Plaskowyz*) Iter->get();
            std::cout << i << " - Plaskowyz o wspolrzednych: (x,y) " << WskPlaskowyz->WspolPolozenia()[0] << " " << WskPlaskowyz->WspolPolozenia()[1] << std::endl;
            break;
            }
        case OB_GoraZGrania:
            {
            ++i;
            WskGoraZGrania = (GoraZGrania*) Iter->get();
            std::cout << i << " - Gora z grania o wspolrzednych: (x,y) " << WskGoraZGrania->WspolPolozenia()[0] << " " << WskGoraZGrania->WspolPolozenia()[1] << std::endl;
            break;
            }
        case OB_GoraZeSzczytem:
            {
            ++i;
            WskGoraZeSzczytem = (GoraZeSzczytem*) Iter->get();
            std::cout << i << " - Gora ze szczytem o wspolrzednych: (x,y) " << WskGoraZeSzczytem->WspolPolozenia()[0] << " " << WskGoraZeSzczytem->WspolPolozenia()[1] << std::endl;
            break;
            }
        default:
            {
            break;
            }
        }
    }
std::cout << std::endl;
}

/*!
 *\brief Metoda dodawajaca do sceny wybrana przeszkode
 \param[in] NumerPrzeszkody - 1 - Plaskowyz, 2 - Gora z grania, 3 - gora ze szczytem.
 \param[in] Polozenie - Wspolrzedne polozenia przeszkody.
 \param[in] Kat - Kat orientacji przeszkody, wzgledem wlasnej osi OZ.
 \param[in] NazwaPrzeszkody - Nazwa danej przeszkody
 \retval True, jezeli przeszkoda zostanie dodana, false jezeli operacja sie nie powiedzie.
 */
bool Scena::DodajPrzeszkode(int NumerPrzeszkody, Wektor3D Polozenie, double Kat, Wektor3D Skala, std::string NazwaPrzeszkody)
{
switch(NumerPrzeszkody)
        {
        case 1:
            {
            ListaObiektow.push_back(std::make_shared<Plaskowyz>(Polozenie,Kat,("../data/" + NazwaPrzeszkody + ".dat"),"../BrylyWzorcowe/ProstopadloscianWzorcowy.dat",Skala));
            (*this).DodajNazwePliku(("../data/" + NazwaPrzeszkody + ".dat"));
            return true;
            }
        case 2:
            {
            ListaObiektow.push_back(std::make_shared<GoraZGrania>(Polozenie,Kat,("../data/" + NazwaPrzeszkody + ".dat"),"../BrylyWzorcowe/ProstopadloscianWzorcowy.dat",Skala));
            (*this).DodajNazwePliku(("../data/" + NazwaPrzeszkody + ".dat"));
            return true;
            }
        case 3:
            {
            ListaObiektow.push_back(std::make_shared<GoraZeSzczytem>(Polozenie,Kat,("../data/" + NazwaPrzeszkody + ".dat"),"../BrylyWzorcowe/GraniastoslupWzorcowy.dat",Skala));
            (*this).DodajNazwePliku(("../data/" + NazwaPrzeszkody + ".dat"));
            return true;
            }
        default:
            {
            return false;
            }
        }
}

/*!
 *\brief Metoda usuwajaca wybrana przeszkode ze sceny.
 \param[in] NumerPrzeszkody - Numer przeszkody na liscie przeszkod (Drony nie sa wliczane)
 \retval True, jezeli przeszkoda zostanie usunieta, false jezeli operacja sie nie powiedzie.
 */
bool Scena::UsunPrzeszkode(int NumerPrzeszkody)
{
int AktualnyNumerPrzeszkody=1;
for (std::list<std::shared_ptr<ObiektSceny>>::iterator Iter = ListaObiektow.begin();  Iter != ListaObiektow.end();  ++Iter)
    {
    if((*Iter)->TypObiektu() == OB_Plaskowyz || (*Iter)->TypObiektu() == OB_GoraZGrania || (*Iter)->TypObiektu() == OB_GoraZeSzczytem)
        {
        if(AktualnyNumerPrzeszkody == NumerPrzeszkody)
            {
            (*this).UsunNazwePrzeszkody((*Iter)->WezNazweBryly(0));
            ListaObiektow.remove(*Iter);
            return true;
            }
        else 
            {
            ++AktualnyNumerPrzeszkody;
            }
        }
    }
return false;
}
 /*!
 *\brief Metoda usuwajaca nazwe pliku wybranej przeszkody
 *\param[in] NazwaPlikuPrzeszkody - nazwa pliku przeszkody, ktora ma zostac usunieta.
 */
void Scena::UsunNazwePrzeszkody(std::string const NazwaPlikuPrzeszkody)
{
Lacze.UsunWszystkieNazwyPlikow();
(*this).DodajNazwePliku("../BrylyWzorcowe/Plaszczyzna.dat");
for (std::list<std::shared_ptr<ObiektSceny>>::iterator Iter = ListaObiektow.begin();  Iter != ListaObiektow.end();  ++Iter)
    {
    if((*Iter)->TypObiektu() == OB_Plaskowyz || (*Iter)->TypObiektu() == OB_GoraZGrania || (*Iter)->TypObiektu() == OB_GoraZeSzczytem)
        {
        if((*Iter)->WezNazweBryly(0) != NazwaPlikuPrzeszkody)
            {
            (*this).DodajNazwePliku((*Iter)->WezNazweBryly(0));
            }
        }
    if((*Iter)->TypObiektu() == OB_Dron)
        {
        (*this).DodajNazwePliku((*Iter)->WezNazweBryly(0));
        (*this).DodajNazwePliku((*Iter)->WezNazweBryly(1));
        (*this).DodajNazwePliku((*Iter)->WezNazweBryly(2));
        (*this).DodajNazwePliku((*Iter)->WezNazweBryly(3));
        (*this).DodajNazwePliku((*Iter)->WezNazweBryly(4));
        }
    }

}

/*!
 *\brief Metoda wyswietlajaca w sposob aniomowany obrot aktywnego drona o zadany kat,
 * oraz jego przelot o zadana odleglosc.
 * \param[in] Odleglosc - Odleglosc o jaka dron ma przeleciec.
 * \param[in] Kat - Kat o jaki dron ma sie obrocic.
 * \retval True, jezeli operacja wykona sie poprawnie
 * \retval False, jezeli podczas operacji wystapia bledy
 */
 bool Scena::PrzemiescDrona(double Odleglosc, double Kat)
 {
 if(!(*this).AktywnyDron()->PrzemiescDrona(Odleglosc, Kat, Lacze))
    {
    return false;
    }
return true;
 }

/*!
 *\brief Metoda wyswietlajaca w sposob aniomowany ruch po okregu aktywnego drona.
 * \param[in] Promien - Promien okregu, po jakim dron ma sie przemieszczac.
 * \retval True, jezeli operacja wykona sie poprawnie
 * \retval False, jezeli podczas operacji wystapia bledy
 */
bool Scena::RuchPoOkregu(double Promien)
 {
 if(!(*this).AktywnyDron()->RuchPoOkregu(Promien, Lacze))
    {
    return false;
    }
return true;
 }
 


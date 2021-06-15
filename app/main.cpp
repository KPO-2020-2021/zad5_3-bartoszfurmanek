// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <stdlib.h>
#include "lacze_do_gnuplota.hh"
#include "Scena.hh"
#include "exampleConfig.h"




int main() {


    Scena Sc;                                               //Scena dla dronow
    char Opcja;                                             //Wybor w menu programu
    int WybranyDron;                                        //Numer aktywnego dron
    int KoniecPetli=0;
    double Kat;                                             //Kat obrotu drona
    double Odleglosc;                                       //Odleglosc na jaka dron poleci
    double x,y;                                                //Wspolrzedne x i y
    Wektor3D Skala;                                         //wielkosci skalowania obiektow
    std::string NazwaObiektu;                                //Nazwa dodawanego obiektu
    int NumerObiektu=0;

    Sc.DodajDrona({20,20,0}, 0, "Dron1");                //Dodanie dronow do scemy
    Sc.DodajDrona({20,100,0}, 0, "Dron2");

    Sc.DodajPrzeszkode(1, {100,100,0}, 45, {10,10,5}, "Plaskowyz1");
    Sc.DodajPrzeszkode(2, {50,150,0}, 270, {10,40,40}, "GoraZGrania1");
    Sc.DodajPrzeszkode(3, {150,50,0}, 60, {20,20,100}, "GoraZeszczytem1");
    Sc.DodajPrzeszkode(3, {180,180,0}, 0, {10,10,50}, "GoraZeSzczytem2");
    
    Sc.NumerAktywnegoDrona()=1;                            //Domyslnie dron pierwszy jest aktywny

    std::cout << std::endl;                                //Wyswietlenie menu
    std::cout << "Polozenie aktywnego drona (x,y): ";
    std::cout << Sc.AktywnyDron()->WspolPolozenia()[0];
    std::cout << " ";
    std::cout << Sc.AktywnyDron()->WspolPolozenia()[1];
    std::cout << std::endl << std::endl;
    std::cout << "a - wybierz aktywnego drona" << std::endl;
    std::cout << "p - zadaj parametry przelotu" << std::endl;
    std::cout << "o - zadaj parametry lotu po okregu" << std::endl;
    std::cout << "d - dodaj obiekt do sceny" << std::endl;
    std::cout << "u - usun obiekt ze sceny" << std::endl;
    std::cout << "m - wyswietl menu" << std::endl;
    std::cout << std::endl << "k - koniec programu"<< std::endl;
    
    while(1)
      {
        std::cout << std::endl << "Aktualna ilosc wektorow: " << Wektor3D::WezIloscAktualna() << std::endl;
        std::cout << "Ogolna Ilosc wektorow: " << Wektor3D::WezIloscOgolna() << std::endl;
        std::cout << std::endl << "Twoj wybor (m - menu) -> ";
        std::cin >> Opcja;
        std::cin.ignore(100000,'\n');
        switch(Opcja)
          {
          case 'a':                                       //Wybor aktywnego drona
            {
            std::cout << std::endl << "Wybor aktywnego drona" << std::endl << std::endl;
              Sc.ListaDronow();
              KoniecPetli=0;
              while(!KoniecPetli)
                {
                std::cout << "Wybierz numer drona: ";
                std::cin >> WybranyDron;
                std::cin.ignore(100000,'\n');
                if(WybranyDron <=0 || WybranyDron>2)
                  {
                  std::cout << "Zly numer drona. Sprobuj ponownie" << std::endl;
                  }
                else
                  {
                  Sc.NumerAktywnegoDrona()=WybranyDron;
                  KoniecPetli=1;
                  }
                }
                std::cout << std::endl;                                //Polozenia aktywnego drona
                std::cout << "Polozenie aktywnego drona (x,y): ";
                std::cout << Sc.AktywnyDron()->WspolPolozenia()[0];
                std::cout << " ";
                std::cout << Sc.AktywnyDron()->WspolPolozenia()[1];
                std::cout << std::endl << std::endl;
              break;
            }
          case 'p':                                       //Przelot drona
            {
            std::cout << std::endl << "Podaj kierunek lotu (Kat):";
            std::cin >> Kat;
            std::cin.ignore(100000,'\n');
            std::cout << "Podaj odleglosc lotu: ";
            std::cin >> Odleglosc;
            std::cin.ignore(100000,'\n');
            std::cout << std::endl;

            while(Kat<=-360 || Kat>=360)            //Usuniecie okresow kata
              {
              if(Kat<=-360)
                {
                Kat+=360;
                }
              if(Kat>=360)
                {
                Kat-=360;
                }    
              }
            Sc.PrzemiescDrona(Odleglosc, Kat);
            break;
            }
          case 'o':                                       //Przelot drona
            {
            std::cout << "Podaj promien okregu po ktorym ma przeleciec dron: ";
            std::cin >> Odleglosc;
            std::cin.ignore(100000,'\n');
            std::cout << std::endl;

            Sc.RuchPoOkregu(Odleglosc);
            break;
            }
          case 'm':
            {
            std::cout << std::endl << std::endl;
            std::cout << "a - wybierz aktywnego drona" << std::endl;
            std::cout << "p - zadaj parametry przelotu" << std::endl;
            std::cout << "o - zadaj parametry lotu po okregu" << std::endl;
            std::cout << "m - wyswietl menu" << std::endl;
            std::cout << "d - dodaj obiekt do sceny" << std::endl;
            std::cout << "u - usun obiekt ze sceny" << std::endl;
            std::cout << std::endl << "k - koniec programu"<< std::endl << std::endl;
            break;
            }
          case 'd':
            {
            std::cout << std::endl << "Wybierz rodzaj obiektu" << std::endl << std::endl;
            std::cout << "1 - Plaskowyz" << std::endl;
            std::cout << "2 - Gora z grania" << std::endl;
            std::cout << "3 - Gora ze szczytem" << std::endl << std::endl;
            std::cout << "Numer obiektu: ";
            std::cin >> NumerObiektu;
            std::cin.ignore(100000,'\n');
            if(NumerObiektu < 1 || NumerObiektu > 3)
              {
              std::cout << "Zly numer obiektu" << std::endl;
              break;
              }
            std::cout << "Podaj Wspolrzedne polozenia obiekty (x,y): ";
            std::cin >> x >> y;
            std::cin.ignore(100000,'\n');
            std::cout << "Podaj kat obrotu bryly: ";
            std::cin >> Kat;
            std::cin.ignore(100000,'\n');
            std::cout << "Podaj skale OX, OY, OZ: ";
            std::cin >> Skala;
            std::cin.ignore(100000,'\n');
            std::cout << "Podaj nazwe obiektu: ";
            std::cin >> NazwaObiektu;
            if(Sc.DodajPrzeszkode(NumerObiektu, {x,y,0}, Kat, Skala, NazwaObiektu))
              {
              std::cout << std::endl << "Element został dodany do sceny" << std::endl << std::endl;
              }
            else
              {
              std::cout << std::endl << std::endl << "Obiekt o takim numerze nie istnieje" << std::endl; 
              }
            break;
            }
          case 'u':
            {
            Sc.ListaPrzeszkod();
            std::cout << std::endl << "Podaj numer obiektu, ktory ma zostac usuniety: ";
            std::cin >> NumerObiektu;
            std::cin.ignore(100000,'\n');
            if(Sc.UsunPrzeszkode(NumerObiektu))
              {
              std::cout << std::endl << std::endl << "Udalo sie usunac obiekt" << std::endl;
              }
            else
              {
              std::cout << std::endl << std::endl << "Nie udalo sie usunac obiekt" << std::endl; 
              }
            break;
            }
          case 'k':
            {
            std::cout << std::endl << "Koniec Programu" <<std::endl;
            return 0;
            }
          default:
            {
            std::cout << std::endl << "Nieznana opcja" << std::endl;
            }
          }
      }
return 0;
}

#include "Macierz3x3.hh"

#define PI 3.1415926535

/*!
 *\file
 *\brief Definicja metod klasy Macierz3x3.
 */

/*!
 * \brief Metoda sluzaca do generowania macierzy obrotu wokol wybranej osi o zadany kat.
 * Argumenty:
 *  \param[in] Kat - kat obrotu.
 *  \param[in] Os - Wybrana os obortu (x,y,z).
 * Zwraca:
 *  \retval Macierz obrotu.
 */
Macierz3x3 MacierzObrotu(double Kat, char Os)
{
    Macierz3x3 Wynik;
    Kat = Kat/180 * PI;          //Zamiana na radiany
    switch(Os)
    {
        case 'x':
            {
            Wynik(0,0)=1;
            Wynik(1,1)=cos(Kat);
            Wynik(1,2)=-sin(Kat);
            Wynik(2,1)=sin(Kat);
            Wynik(2,2)=cos(Kat);
            break;
            }
        case 'y':
            {
            Wynik(1,1)=1;
            Wynik(0,0)=cos(Kat);
            Wynik(0,2)=sin(Kat);
            Wynik(2,0)=-sin(Kat);
            Wynik(2,2)=cos(Kat);
            break;
            }
        case 'z':
            {
            Wynik(2,2)=1;
            Wynik(0,0)=cos(Kat);
            Wynik(0,1)=-sin(Kat);
            Wynik(1,0)=sin(Kat);
            Wynik(1,1)=cos(Kat);
            break;
            }
        default:
            {
            throw std::runtime_error("Blad: nieznana os");
            }
    }
    return Wynik;
}







#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;

enum class Rezerwacja { zarezerwowany, niezarezerwowany };
const char* REZERWACJA[] = { "Zarezerwowany", "Niezarezerwowany" };

class Kupiec {
private:
    char Imie[50];
    char Nazwisko[50];
public:
    void setImieNazwisko(const char* i, const char* n) {
        strncpy_s(Imie, i, 50);
        Imie[49] = '\0'; // ensure null termination
        strncpy_s(Nazwisko, n, 50);
        Nazwisko[49] = '\0'; // ensure null termination
    }

    const char* getImie() const {
        return Imie;
    }

    const char* getNazwisko() const {
        return Nazwisko;
    }

    Kupiec(const char* i, const char* n) {
        setImieNazwisko(i, n);
    }
};

class Bilet {
private:
    int numerBiletu[8];
    double cenaBiletu;
    bool zakup = false;
    Rezerwacja rezerwacja = Rezerwacja::niezarezerwowany;
    static int stworzoneBilety;
    static int zarezerwowaneBilety;
    Kupiec* kupujacy;
public:
    void setNumerBiletu(int tab[]) {
        for (int i = 0; i < 8; i++) {
            numerBiletu[i] = tab[i];
        }
    }

    void setCenaBiletu(double c) {
        if (c >= 0) {
            cenaBiletu = c;
        }
        else {
            cenaBiletu = 0;
        }
        if (!zakup) {
            stworzoneBilety++;
            zakup = true;
        }
    }

    void setKupujacy(Kupiec* k) {
        if (k != nullptr) {
            kupujacy = k;
        }
    }

    void setRezerwacja(Rezerwacja r) {
        if (r != rezerwacja) {
            if (r == Rezerwacja::zarezerwowany) {
                zarezerwowaneBilety++;
            }
            else if (r == Rezerwacja::niezarezerwowany) {
                zarezerwowaneBilety--;
            }
        }
        rezerwacja = r;
    }

    int* getNumerBiletu() {
        return numerBiletu;
    }

    double getCenaBiletu() const {
        return cenaBiletu;
    }

    Kupiec* getKupujacy() const {
        return kupujacy;
    }

    Rezerwacja getRezerwacja() const {
        return rezerwacja;
    }

    void Anulacja() {
        if (rezerwacja == Rezerwacja::zarezerwowany) {
            rezerwacja = Rezerwacja::niezarezerwowany;
            zarezerwowaneBilety--;
        }
    }

    Bilet(int nr[], double cen, Kupiec* k) {
        setNumerBiletu(nr);
        setCenaBiletu(cen);
        setKupujacy(k);
        rezerwacja = Rezerwacja::niezarezerwowany;
    }

    ~Bilet() {
        if (rezerwacja == Rezerwacja::zarezerwowany) {
            zarezerwowaneBilety--;
        }
    }

   
};
 ostream& operator<<(ostream& str,  Bilet& b) {
    str << "Numer Biletu: ";
    const int* numerBiletu = b.getNumerBiletu();
    for (int i = 0; i < 8; i++) {
        str << numerBiletu[i];
    }
    str << endl << "Cena Biletu: " << b.getCenaBiletu() << endl
        << "Rezerwacja: " << REZERWACJA[(int)b.getRezerwacja()] << endl
        << "Imie: " << b.getKupujacy()->getImie() << " Nazwisko: " << b.getKupujacy()->getNazwisko();
    return str;
}

int Bilet::stworzoneBilety = 0;
int Bilet::zarezerwowaneBilety = 0;

int main() {
    srand(time(NULL));
    Kupiec k1("Adrian", "Szewczyk"), k2("Jakub", "Wesoły"), k3("Wojtek", "Kowalski");
    Kupiec* wsk = &k2;
    int numerBiletu[8] = { 0, 1, 2, 3, 4, 6, 6, 7 };
    Bilet bilet1(numerBiletu, 30, wsk);

    cout << bilet1 << endl;

    return 0;
}

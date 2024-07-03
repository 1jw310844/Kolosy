#include <iostream>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

enum class AktywnoscKonta { aktywne, nieaktywne };
const char* AKTYWNOSC[] = { "aktywne", "nieaktywne" };

class Klient {
private:
    char nazwaKlienta[50];

public:
    void setNazwa(const char* n) {
        strncpy_s(nazwaKlienta, n, 49);
        nazwaKlienta[49] = '\0'; // ensure null termination
    }

    const char* getNazwa() const {
        return nazwaKlienta;
    }

    Klient(const char* nazwa) {
        setNazwa(nazwa);
    }
};

class KontoBankowe {
private:
    static int licznik;
    int numerKonta[26];
    double StanKonta;
    AktywnoscKonta aktywnosc;
    Klient klient;

public:
    // Setery i getery
    void setNumerKonta(const int tab[]) {
        for (int i = 0; i < 26; i++) {
            numerKonta[i] = tab[i];
        }
    }

    const int* getNumerKonta() const {
        return numerKonta;
    }

    void setStanKonta(double stan) {
        StanKonta = (stan < 0) ? 0 : stan;
    }

    double getStanKonta() const {
        return StanKonta;
    }

    void setAktywnoscKonta(AktywnoscKonta akt) {
        if (akt != aktywnosc) {
            if (akt == AktywnoscKonta::aktywne) {
                licznik++;
            }
            else if (akt == AktywnoscKonta::nieaktywne) {
                licznik--;
            }
        }
        aktywnosc = akt;
    }

    AktywnoscKonta getAktywnoscKonta() const {
        return aktywnosc;
    }

    Klient getKlient() const {
        return klient;
    }

    // Konstruktor argumentowy
    KontoBankowe(const int tab[], double stan, AktywnoscKonta akt, const Klient& kl)
        : klient(kl) {
        setStanKonta(stan);
        setAktywnoscKonta(akt);
        setNumerKonta(tab);
    }

    // Destruktor
    ~KontoBankowe() {
        if (aktywnosc == AktywnoscKonta::aktywne) {
            licznik--;
        }
    }

    // Funkcja polimorficzna do obliczania prognozy stanu konta na rok
    virtual double prognozaStanuKontaNaRok() const {
        // Zwykłe konto bankowe ma oprocentowanie 0%
        return StanKonta;
    }

    // Statyczna metoda do zwracania licznika aktywnych kont
    static int getLicznik() {
        return licznik;
    }

    // Operator konwersji na double (stan konta)
    operator double() const {
        return StanKonta;
    }

    // Metoda konwersji klienta na nowe aktywne konto bankowe
    static KontoBankowe klientTOkontoBankowe(const Klient& k) {
        int numerKonta[26] = {};
        for (int i = 0; i < 26; i++) {
            numerKonta[i] = rand() % (9 + 1);
        }
        // losowy numer konta (zerowy w tym przypadku)
        return KontoBankowe(numerKonta, 0, AktywnoscKonta::aktywne, k);
    }

    // Operator += do powiększania stanu konta
    KontoBankowe& operator+=(double p) {
        setStanKonta(StanKonta + p);
        return *this;
    }
};

// Inicjalizacja statycznej zmiennej członkowskiej licznik
int KontoBankowe::licznik = 0;

// Operator << do wypisywania danych konta
ostream& operator<<(ostream& str, const KontoBankowe& k) {
    str << "[";
    const int* numerKonta = k.getNumerKonta();
    for (int i = 0; i < 26; ++i) {
        str << numerKonta[i];
    }
    str << "] ";
    str << k.getKlient().getNazwa() << " : ";
    if (k.getAktywnoscKonta() == AktywnoscKonta::aktywne) {
        str << "[" << k.getStanKonta() << "]";
    }
    else {
        str << "NIEAKTYWNE";
    }
    return str;
}

class KontoOszczedniosciowe : public KontoBankowe {
private:
    double StopaProcentowa;

public:
    // Konstruktor
    KontoOszczedniosciowe(const int tab[], double stan, AktywnoscKonta akt, const Klient& kl, double stopa)
        : KontoBankowe(tab, stan, akt, kl) {
        setStopaProcentowa(stopa);
    }

    // Setter dla stopy procentowej
    void setStopaProcentowa(double s) {
        if (s > 0 && s < 0.1) {
            StopaProcentowa = s;
        }
        else {
            StopaProcentowa = 0;
        }
    }

    // Getter dla stopy procentowej
    double getStopaProcentowa() const {
        return StopaProcentowa;
    }

    // Obliczanie prognozy stanu konta na rok
    double prognozaStanuKontaNaRok() const override {
        double rocznaStopa = StopaProcentowa;
        return getStanKonta() * pow(1 + rocznaStopa, 1);
    }
};

int main() {
    srand(time(0));
    // Tworzenie klienta
    Klient klient1("Adriano Kanciano");

    // Tworzenie zwykłego konta bankowego
    int numerKonta1[26] = {};
    KontoBankowe konto1(numerKonta1, 2300, AktywnoscKonta::aktywne, klient1);
    cout << "Konto 1: " << konto1 << endl;

    // Konwersja obiektu klienta na nowe aktywne konto bankowe
    KontoBankowe kontoNowe = KontoBankowe::klientTOkontoBankowe(klient1);
    cout << "Nowe konto dla klienta 1: " << kontoNowe << endl;

    // Zwiększenie stanu konta
    konto1 += 3000;
    cout << "Po zwiększeniu stanu konta 1: " << konto1 << endl;

    // Tworzenie konta oszczędnościowego
    KontoOszczedniosciowe kontoOszcz(numerKonta1, 10000, AktywnoscKonta::nieaktywne, klient1, 0.05);
    cout << "Konto oszczędnościowe: " << kontoOszcz << endl;

    // Obliczanie prognozy stanu konta oszczędnościowego za rok
    double prognoza = kontoOszcz.prognozaStanuKontaNaRok();
    cout << "Prognoza stanu konta oszczędnościowego za rok: " << prognoza << endl;

    // Wyświetlenie liczby aktywnych kont
    cout << "Liczba aktywnych kont: " << KontoBankowe::getLicznik() << endl;
    KontoBankowe* wsk = new KontoBankowe(numerKonta1, 10000, AktywnoscKonta::aktywne, klient1);
    cout << "Liczba aktywnych kont: " << KontoBankowe::getLicznik() << endl;
    delete wsk;
    cout << "Liczba aktywnych kont: " << KontoBankowe::getLicznik() << endl;
    return 0;
}

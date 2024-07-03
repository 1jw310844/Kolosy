#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;

enum class Stan { dopuszczony, niedopuszczony };
const char* STAN[] = { "Dopuszczony", "Niedopuszczony" };

class Wlasciciel {
protected:
    char nazwisko[50];
public:
    void setNazwisko(const char* n) {
        strncpy_s(nazwisko, n, 49);
        nazwisko[49] = '\0'; // Zapewniamy zakończenie łańcucha null
    }
    const char* getNazwisko() const {
        return nazwisko;
    }
    Wlasciciel(const char* n) {
        setNazwisko(n);
    }
};

struct numerRejestracyjny {
    char litery[3];
    int cyfry[5];
};

class Samochod {
protected:
    numerRejestracyjny numer;
    static int cyfryNumeru[5];
    double stanLicznika;
    Stan stan;
    Wlasciciel* wlasciciel;
public:
    void Inkrementuj() {
        for (int i = 4; i >= 0; --i) {
            if (cyfryNumeru[i] < 9) {
                cyfryNumeru[i]++;
                break;
            }
            else {
                cyfryNumeru[i] = 0;
            }
        }
    }
    void setNumer(const char* l) {
        for (int i = 0; i < 3; i++) {
            if ((l[i] >= 65 && l[i] <= 90) || (l[i] >= 97 && l[i] <= 122)) {
                this->numer.litery[i] = l[i];
            }
            else {
                throw invalid_argument("Błędne litery w numerze rejestracyjnym");
            }
        }
        for (int i = 0; i < 5; ++i) {
            this->numer.cyfry[i] = cyfryNumeru[i];
        }
        Inkrementuj();
    }
    numerRejestracyjny getNumer() const {
        return numer;
    }
    void setStanLicznika(double s) {
        if (s >= 0) {
            stanLicznika = s;
        }
        else {
            throw invalid_argument("Błędny stan licznika");
        }
    }
    double getStanLicznika() const {
        return stanLicznika;
    }
    void setStan(Stan st) {
        stan = st;
    }
    Stan getStan() const {
        return stan;
    }
    void setWlasciciel(Wlasciciel* w) {
        wlasciciel = w;
    }
    Wlasciciel* getWlasciciel() const {
        return wlasciciel;
    }
    Samochod(const char* l, double s, Stan st, Wlasciciel* w)
        : stanLicznika(s), stan(st), wlasciciel(w) {
        setNumer(l);
    }
    virtual double Zasieg() const {
        return 800;
    }
    double Konwersja(double w) const {
        double wartosc;
        if (stan == Stan::dopuszczony) {
            wartosc = (w - 0.1 * stanLicznika) * 1.0;
        }
        else {
            wartosc = (w - 0.1 * stanLicznika) * 0.2;
        }
        return max(wartosc, 400.0);
    }
    bool operator==(const Samochod& s) const {
        return (strcmp(this->numer.litery, s.numer.litery) == 0 &&
            abs(this->stanLicznika - s.stanLicznika) <= 10);
    }
};

int Samochod::cyfryNumeru[5] = { 0, 0, 0, 0, 0 };

class SamochodElektryczny : public Samochod {
protected:
    double stanBaterii;
public:
    void setStanBaterii(double s) {
        if (s >= 0 && s <= 100) {
            stanBaterii = s;
        }
        else {
            throw invalid_argument("Błędny stan baterii");
        }
    }
    double getStanBaterii() const {
        return stanBaterii;
    }
    SamochodElektryczny(Samochod s, double sb)
    : Samochod(s) 
    {
         setStanBaterii(sb);
    }
    double Zasieg() const override {
        return (2.5 * stanBaterii);
    }
};

ostream& operator<<(ostream& str, const Samochod& s) {
    str << "Numer: " << s.getNumer().litery[0] << s.getNumer().litery[1] << s.getNumer().litery[2] << "-";
    for (int i = 0; i < 5; ++i) {
        str << s.getNumer().cyfry[i];
    }
    str << endl
        << "Stan Licznika: " << s.getStanLicznika() << endl
        << "Stan Auta: " << STAN[(int)s.getStan()] << endl
        << "Wlasciciel: " << s.getWlasciciel()->getNazwisko() << endl;
    return str;
}

int main()
{
    Wlasciciel w1("Szewczyk"), w2("Wesoly"), w3("Malinski");
    Wlasciciel* wlasciciele[] = { &w1, &w2, &w3 };
    try {
        Samochod s1("ABC", 200000, Stan::dopuszczony, wlasciciele[0]);
        cout << s1 << endl;
        Samochod s2("DEF", 200000, Stan::dopuszczony, wlasciciele[1]);
        cout << s2 << endl;
        Samochod s3("ARe", 200000, Stan::dopuszczony, wlasciciele[2]);
        cout << s3 << endl;

    }
    catch (const invalid_argument& e) {
        cout << "BLAD: " <<endl;
    }
    
    

    Samochod s1("ABC", 200000, Stan::dopuszczony, wlasciciele[0]);
    cout << s1<<endl;
    w1.setNazwisko("Kanciano");
    cout << s1 << endl;
    Samochod s2("ABC", 200000, Stan::dopuszczony, wlasciciele[1]);
    

    if (s1 == s2) {
        cout << "Dziala" << endl;
    }
    else {
        cout << "Nie dziala" << endl;
    }
    
    SamochodElektryczny ele1(s1, 99);
    Samochod* wsk = &s1;
    cout << wsk->Zasieg() << endl;
    wsk = &ele1;
    cout << wsk->Zasieg() << endl;
    wsk = nullptr;
    double wartosc = s1.Konwersja(30000);
    cout << wartosc<<endl;
    double wartosc1 = s1.Konwersja(1000);
    cout << wartosc1;
    return 0;
}

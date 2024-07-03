#include <iostream>
#include <cstring>
#include <cassert>
#include <iomanip>

using namespace std;

enum class Dostepnosc { dostepna, niedostepna };
const char* DOSTEPNOSC[] = { "Dostepna","Niedostepna" };

class Autor {
protected:
    char nazwisko[50];
public:
    void setNazwisko(const char* n) {
        strncpy_s(nazwisko, n, 50);
    }
    const char* getNazwisko() const {
        return nazwisko;
    }
    Autor(const char* n) {
        setNazwisko(n);
    }
};

class Ksiazka {
protected:
    static Ksiazka* wzorzec;
    char tytul[50];
    int liczbaStron;
    Dostepnosc dostepnosc;
    Autor* autor;

public:

    static void UstawienieWzorca(Ksiazka* w) {
        wzorzec = w;
    }
    void setTytul_Dostepnosc(const char* t, Dostepnosc d) {
        strncpy_s(tytul, t, 50);
        dostepnosc = d;
    }
    void setLiczbaStron(int l) {
        if (l > 0) {
            liczbaStron = l;
        }
        else throw invalid_argument("Bledna liczba stron");
    }
    void setAutor(Autor* a) {
        if (a != nullptr) {
            autor = a;
        }
        else throw invalid_argument("Bledne wskazanie");
    }
    const char* getTytul() const {
        return tytul;
    }
    int getLiczbaStron() const {
        return liczbaStron;
    }
    Dostepnosc getDostepnosc() const {
        return dostepnosc;
    }
    Autor* getAutor() const {
        return autor;
    }
    Ksiazka() {
        assert(wzorzec != nullptr);
        setTytul_Dostepnosc(wzorzec->tytul, wzorzec->dostepnosc);
        setLiczbaStron(wzorzec->liczbaStron);
        setAutor(wzorzec->autor);
    }
    Ksiazka(const char* t, int l, Dostepnosc d, Autor* a) {
        setTytul_Dostepnosc(t, d);
        setLiczbaStron(l);
        setAutor(a);
    }
    virtual double CenaKsiazki() {
        return liczbaStron;
    }
    operator const char* () {
        static char informacje[200]; // statyczny buffer, aby uniknąć problemów z pamięcią
        const char* dostepnoscStr = DOSTEPNOSC[static_cast<int>(dostepnosc)];

        // formatowanie liczby stron
        char liczbaStronStr[10];
        snprintf(liczbaStronStr, sizeof(liczbaStronStr), "%d", liczbaStron);

        // tworzenie pełnego łańcucha znaków
        snprintf(informacje, sizeof(informacje), "%s, %s, %s, %s",
            tytul, liczbaStronStr, dostepnoscStr, autor->getNazwisko());

        return informacje;
    }
    bool operator==(const Ksiazka& k) {
        return (this->liczbaStron == k.liczbaStron) &&
            (this->dostepnosc == k.dostepnosc) &&
            (strcmp(this->autor->getNazwisko(), k.autor->getNazwisko()) == 0);
    }
};
Ksiazka* Ksiazka::wzorzec = nullptr;

class EBook :public Ksiazka {
protected:
    double MB;
public:
    void setMB(double m) {
        if (MB > 0) {
            MB = m;
        }
        else throw invalid_argument("Bledna MegaBajty");
    }
    double getMB() {
        return MB;
    }
    double CenaKsiazki() override {
        return liczbaStron - (liczbaStron * 0.25);
    }
    EBook(Ksiazka k, double m)
        :Ksiazka(k)
    {
        MB = m;
    }
};

int main()
{
    //Test konstruktora domyslnego
    //Ksiazka k1, k2;

    Autor a1("Szewczyk"), a2("Mickiewicz"), a3("Słowacki");
    Autor* autorzy[3] = { &a1,&a2,&a3 };

    try {

        Ksiazka k1("Programowanie", 320, Dostepnosc::dostepna, autorzy[0]), k2("Pan Tadeusz", 200, Dostepnosc::dostepna, autorzy[1]);
        Ksiazka k3("Pan Tadeusz", 200, Dostepnosc::dostepna, autorzy[1]);
        const char* ksiazka = static_cast<const char*>(k1);
        Ksiazka* wsk = &k1;
        Ksiazka::UstawienieWzorca(wsk);
        Ksiazka k4;
       // cout << ksiazka << endl;
        //Nie powinno dzialac
        if (k3 == k1) {
            cout << "Dziala" << endl;
        }
        else cout << "Nie dziala" << endl;
        //Powinno dzialac
        if (k3 == k2) {
            cout << "Dziala" << endl;
        }
        else cout << "Nie dziala" << endl;
        EBook eb1(k1, 30);
        Ksiazka* wskaznik = &k1;
        cout << wskaznik->CenaKsiazki() << endl;
        wskaznik = &eb1;
        cout << wskaznik->CenaKsiazki() << endl;
        
    }
    catch (invalid_argument) {
        cout << "BLAD!" << endl;
    }
}

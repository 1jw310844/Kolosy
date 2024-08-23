#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
using namespace std;

struct Zadanie
{
	int rozmiar;
	int* tab = nullptr;
};
Zadanie* utworzStrukture(Zadanie* z, int size)
{
	z->rozmiar = size;
	z->tab = new int[size] {};
	return z;
}
void zwolnij(Zadanie* z)
{
	delete[] z->tab;
	z->tab = nullptr;
}

Zadanie* wypelnij(Zadanie* z)
{
	int wielkosc = z->rozmiar;
	for (int i = 0; i < wielkosc; i++)
	{
		z->tab[i] = i + 1;
	}
	return z;
}

void zapisz(Zadanie* z, FILE* plik)
{
	for (int i = 0; i < z->rozmiar; i++)
	{
		fprintf(plik, "%d ", z->tab[i]);
	}
}

ostream& operator<< (ostream& ekr, FILE* plik)
{
	char liczba;
	if (plik != nullptr)
	{
		rewind(plik);
		while (!feof(plik))
		{
			liczba = fgetc(plik);
			ekr << liczba;
		}
	}
	return ekr;
}

int main()
{
	Zadanie s1;
	utworzStrukture(&s1, 10);
	cout << s1.rozmiar << endl;
	wypelnij(&s1);
	for (int i = 0; i < s1.rozmiar; i++)
	{
		cout << s1.tab[i] << " ";
	}
	cout << endl;

	FILE* tablica = fopen("tablica.txt", "w");
	zapisz(&s1, tablica);
	fclose(tablica);

	tablica = fopen("tablica.txt", "r");
	rewind(tablica);
	cout << tablica;
	fclose(tablica);
	

	zwolnij(&s1);
	return 0;

}

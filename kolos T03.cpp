#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
using namespace std;

struct Struktura
{
	int rozmiar;
	int* tablica = nullptr;
};
Struktura* alokacja(Struktura *s, int size)
{
	s->rozmiar = size;
	s->tablica = new int[size] {};
	return s;
}
Struktura* wypelnij(Struktura * s)
{

	for (int i = 0; i < s->rozmiar; i++)
	{
		s->tablica[i] = i + 1;
	}
	return s;
}
void dealokacja(Struktura* s)
{
	delete[] s->tablica;
	s->tablica = nullptr;
}

void zapis(FILE* plik, Struktura* s)
{
	for (int i = 0; i < s->rozmiar; i++)
	{
		fprintf(plik, "%d ", s->tablica[i]);
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
void czyTakieSame(Struktura* s1, Struktura* s2)
{
	int licznik = 0;
	if (s1->rozmiar == s2->rozmiar)
	{
		for (int i = 0; i < s1->rozmiar; i++)
		{
			if (s1->tablica[i] == s2->tablica[i])
			{
				licznik++;
			}
			else
			{ 
				cerr << "Sa inne";
				break;
			}
		}
		if (licznik == s1->rozmiar)
		{
			cerr << "Sa takie same";
		}
	}
	else
	{
		cerr << "Sa inne";
	}
}
int main()
{
	Struktura s1;
	Struktura s2;
	alokacja(&s1, 11);
	alokacja(&s2, 11);
	FILE* plik = fopen("plik1.txt", "w");
	wypelnij(&s1);
	wypelnij(&s2);
	zapis(plik, &s1);
	fclose(plik);
	plik = fopen("plik1.txt", "r");
	rewind(plik);
	cout << plik << endl;
	fclose(plik);
	czyTakieSame(&s1, &s2);
	dealokacja(&s1);
	dealokacja(&s2);
}

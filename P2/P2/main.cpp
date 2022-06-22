#include "MyMath.h"

#include <iostream>

int main()
{
	int in;
	int it;
	int anz;
	int n;
	mp::cpp_int candidate;
	std::cout << "Aktion waehlen: " << std::endl
		<< "1. Miller-Rabin Test" << std::endl
		<< "2. Naechstgroessere Primzahl suchen " << std::endl
		<< "3. Anzahl Zeugen " << std::endl
		<< "4. Durchscnittlicher Abstand zur naechsten Primzahl in Groessenordnung n " << std::endl
		<< "5. Durchschnittlichen Abstand von 0 < n < 100 erneut berechnen" << std::endl;
	std::cin >> in;
	if (in < 4)
	{
		std::cout << "Zahl eingeben: ";
		std::cin >> candidate;
	}
	if (in < 3)
	{
		std::cout << "Iterationen eingeben: ";
		std::cin >> it;
	}
	if (in == 1)
	{
//		mpr::uniform_int_distribution<mp::cpp_int> ui(mp::cpp_int(1), candidate);
		if (millerRabin(candidate, it) == 0)
		{
			std::cout << "Kandidat ist wahrscheinlich Primzahl!" << std::endl;
		}
		else
		{
			std::cout << "Kandidat ist zusammengesetzt!" << std::endl;
		}
	}
	else if (in == 2)
	{
//		mpr::uniform_int_distribution<mp::cpp_int> ui(mp::cpp_int(1), candidate);
		mp::cpp_int next = nextPrim(candidate, it);
		std::cout << "Naechste Primzahl ist " << next << std::endl;
	}
	else if (in == 3)
	{
		std::cout << "Anzahl Zeugen fuer " << candidate << ": " << anzZeugen(candidate) << std::endl;
	}
	else if (in == 4)
	{
		std::cout << "Anzahl Ziehungen: ";
		std::cin >> anz;
		std::cout << "Groessenordnung: ";
		std::cin >> n;
		std::cout << "Iterationen: ";
		std::cin >> it;
		std::cout << std::endl << "Durchschnittlicher Abstand in Groessenordnung n = " << n << " : " << avgDistance(anz, n, it) << std::endl;
	}
	else if (in == 5)
	{
		avgNextPrim(100, 50);
	}
	else
	{
		std::cout << "Falsche Eingabe!" << std::endl;
	}
	system("pause");
	return 0;
}
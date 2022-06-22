#include "myMath.h"

// Testfunktion, die c*x = d mod m durch Ausprobieren löst - nur zum Vergleich mit gcdExt()
int func(int c, int d, int m)
{
	int x = 0;
	while (x < INT_MAX)
	{
		if ((c*x) % m == d % m)
			return x;
		x++;
	}
}

// Durchschnittliche Schritte zur gcd-Berechnung von anz Zahlen mit n Länge
int averageSteps(int anz, int n)
{
	int avg = 0;
	int steps = 0;
	// Obergrenze/Untergrenze
	cpp_int lower = power((cpp_int)10, (cpp_int)(n - 1));
	cpp_int upper = power((cpp_int)10, (cpp_int)n) - 1;
	//std::cout << "Grenzen: " << lower << "," << std::endl << "\t " << upper << std::endl;

	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	mt19937 mt(seed);

	// Zahlen ziehen
	uniform_int_distribution<cpp_int> ui(cpp_int(1), upper);

	cpp_int a;
	cpp_int b;
	// anz mal durchführen
	for (int i = 0; i < anz; i++)
	{
		// Seed generieren

		a = ui(mt);
		b = ui(mt);

		// gcd berechnen und Schritte aufaddieren und am Schluss durch anz teilen
		gcd(a, b, steps);
		avg += steps;
		steps = 0;
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	//std::cout << "a: " << a << std::endl << "b: " << b << std::endl;
	return avg /= anz;
}

int main()
{
	// Generiert 400 Bit-stellige Zahl per Mersenne twister

	mt19937 mt(time(0));
	uniform_int_distribution<cpp_int> ui(-(cpp_int(1) << 400), cpp_int(1) << 400);
	int steps = 0;

	// einzeln definierte große Zahlen
	//mp::int512_t  a = power((mp::int512_t)9, (mp::int512_t)100) + 1;
	//mp::int512_t  b = power((mp::int512_t)10, (mp::int512_t)100) + 1;

	// Normale Integer
	//int a = 8;
	//int b = 50;

	//int gcdVal = gcd(a, b, steps);
	//std::cout << "gcd(" << std::endl
	//	<< a << "," << std::endl
	//	<< b << std::endl
	//	<< ") = " << gcdVal << std::endl
	//	<< "Schritte: " << steps << std::endl << std::endl;

	//std::ofstream myfile;
	//myfile.open("data.txt");
	//// Durchscnittliche Schritte bei anz Sätzen mit Zahlen von n Länge
	//int anz = 1000;
	//for (int n = 1; n <= 100; n++)
	//{
	//	int avg = averageSteps(anz, n);
	//	myfile << n << "\t" << avg << std::endl;
	//}
	//myfile.close();

	int c = 13;
	int d = 1;
	int m = 36;

	//mp::int1024_t  c = power((mp::int1024_t)9, (mp::int1024_t)100) + 1;
	//mp::int1024_t  d = power((mp::int1024_t)8, (mp::int1024_t)100) + 1;
	//mp::int1024_t  m = power((mp::int1024_t)10, (mp::int1024_t)100) + 1;

	////int test = func(c, d, m);
	int1024_t result = gcdExt(c, d, m);
	//int result = gcdExt(c, d, m);
	if (result < 0)
	{
		std::cout << "Es ist ein Fehler aufgetreten!" << std::endl;
		if (result == -1)
		{
			// c*x = d mod m ist lösbar wenn gcd(c,m) d teilt
			std::cout << "gcd(" << c << ", " << m << ") teilt nicht " << d << std::endl;
		}
		if (result == -2)
		{
			// 	c*x = d mod m ist lösbar wenn gcd(c,m) = 1
			std::cout << "gcd(" << c << ", " << m << ") ist nicht = 1!" << std::endl;
		}
	}
	else
	{
		std::cout << "Loesung fuer " << c << " * x = " << d << " mod " << m << ": x = " << result << std::endl;
		int1024_t doubleCheck = (c * result) % m;
		if (doubleCheck == d)
		{
			std::cout << "Testrechnung c * x = d mod m erfolgreich!" << std::endl;
		}
	}

	system("pause");
	return 0;
}
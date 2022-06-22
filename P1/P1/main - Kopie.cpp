#include "myMath.h"
#include <mutex>

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
	mp::cpp_int lower = power((mp::cpp_int)10, (mp::cpp_int)(n - 1));
	mp::cpp_int upper = power((mp::cpp_int)10, (mp::cpp_int)n) - 1;
	//std::cout << "Grenzen: " << lower << "," << std::endl << "\t " << upper << std::endl;

	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	mpr::mt19937 mt(seed);

	// Zahlen ziehen
	mpr::uniform_int_distribution<mp::cpp_int> ui(mp::cpp_int(1), upper);

	mp::cpp_int a;
	mp::cpp_int b;
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

	mpr::mt19937 mt(time(0));
	mpr::uniform_int_distribution<mp::cpp_int> ui(-(mp::cpp_int(1) << 400), mp::cpp_int(1) << 400);
	int steps = 0;

	//for (int i = 0; i < 10; i++)
	//{
	//	// Zufällige große Zahlen
	//	mp::cpp_int a = ui(mt);
	//	mp::cpp_int b = ui(mt);
	//	int gcdVal = gcd(a, b, steps);
	//	std::cout << "gcd(" << std::endl
	//		<< a << "," << std::endl
	//		<< b << std::endl
	//		<< ") = " << gcdVal << std::endl
	//		<< "Schritte: " << steps << std::endl << std::endl;
	//	steps = 0;
	//}	

	// einzeln definierte große Zahlen
	//mp::int512_t  a = power((mp::int512_t)9, (mp::int512_t)100) + 1;
	//mp::int512_t  b = power((mp::int512_t)10, (mp::int512_t)100) + 1;

	// Normale Integer
	//int a = 4812;
	//int b = 870;

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

	//int c = 6;
	//int d = 3;
	//int m = 18;

	mp::int512_t  c = power((mp::int512_t)9, (mp::int512_t)100) + 1;
	mp::int512_t  d = power((mp::int512_t)8, (mp::int512_t)100) + 1;
	mp::int512_t  m = power((mp::int512_t)10, (mp::int512_t)100) + 1;

	//int test = func(c, d, m);
	mp::cpp_int result = gcdExt(c, d, m);
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
			//	if (d == 1 && gcd(c, m, steps) != 1)
			std::cout << "gcd(" << c << ", " << m << ") ist nicht = 1!" << std::endl;
		}
	}
	else
	{
		std::cout << "Loesung fuer " << c << " * x = " << d << " mod " << m << " = " << result << std::endl;
	}
	//func(12, 52, 56);

	system("pause");
	return 0;
}
#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/math/special_functions/pow.hpp>
#include <boost/math/special_functions/powm1.hpp>
#include <boost/mpl/modulus.hpp>
#include <boost/random.hpp>

#include <cmath>
#include <chrono>
#include <fstream>

namespace mp = boost::multiprecision;
namespace mpr = boost::random;

auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
mpr::mt19937 mt(seed);

// eigene Mod-Funktion da "%"-Operator in c++ nur Teilerrest liefert
mp::cpp_int mod(mp::cpp_int a, mp::cpp_int b)
{
	return (a%b + b) % b;
}

// schnelle Exponentiation, da boost keine cpp_ints miteinander potenzieren möchte
template <typename T> T power(T base, T exponent)
{
	mp::cpp_int result = 1;
	if (exponent == 0)
		return result;
	if (exponent == 1)
		return base;
	while (exponent > 0)
	{
		// exponent % 2 != 0
		if (exponent & 1)
			result *= base;
		// exponent /= 2
		exponent >>= 1;
		base *= base;
	}
	return result;
}

bool istZusammengesetzt(mp::cpp_int a, mp::cpp_int n)
{
	mp::cpp_int k;
	k = n - 1;
	if (mp::powm(a, k, n) != 1)
		return true;

	while (true)
	{
		mp::cpp_int modM = mp::powm(a, k, n);
		if (modM == 1)
		{
			if (k % 2 != 0)
			{
				return false;
			}
			else
			{
				k /= 2;
				continue;
			}
		}
		else if (modM == (n - 1))
		{
			return false;
		}
		return true;
	}
}

int millerRabin(mp::cpp_int n, int it)
{
	// Zahlen ziehen, wenn n > 1
	if (n == 1)
		return 1;
	mpr::uniform_int_distribution<mp::cpp_int> ui(mp::cpp_int(1), (n - 1));

	mp::cpp_int a;
	// it Iterationen durchführen
	for (int i = 0; i < it; i++)
	{
		a = ui(mt);
		if (istZusammengesetzt(a, n))
			return 1;
	}
	return 0;
}

mp::cpp_int nextPrim(mp::cpp_int n, int it)
{
	mp::cpp_int candidate;
	// Ist n gerade, um 1 erhöhen
	if (n % 2 == 0)
	{
		if (n == 2)
			return n;
		candidate = n + 1;
	}
	else
	{
		// Distribution zieht sonst zahlen von 1-1 und führt MR-Test durch
		if (n == 1)
			return 2;
		candidate = n;
	}
	while (true)
	{
		if (millerRabin(candidate, it) == 0)
		{
			return candidate;
		}
		candidate += 2;
	}
}

int anzZeugen(mp::cpp_int n)
{
	int anz = 0;
	// n-1 Iterationen durchführen
	for (int a = 1; a < n - 1; a++)
	{
		if (istZusammengesetzt(a, n))
		{
			anz++;
		}
	}
	return anz;
}

int avgDistance(int anz, int n, int it)
{
	mp::cpp_int avg = 0;
	mp::cpp_int lower = power((mp::cpp_int)10, (mp::cpp_int)(n - 1));
	mp::cpp_int upper = power((mp::cpp_int)10, (mp::cpp_int)n) - 1;
	//std::cout << "Pruefe Zahlen von " << lower << " - " << upper << std::endl;

	// Zahlen ziehen 
	mpr::uniform_int_distribution<mp::cpp_int> ui(lower, upper);

	mp::cpp_int a;
	mp::cpp_int next;
	for (int i = 0; i < anz; i++)
	{
		a = ui(mt);
		//std::cout << "Suche naechste Primzahl zu " << a << std::endl;
		next = nextPrim(a, it); // erster Durchlauf mit 50
		avg += (next - a);
	}
	return int(avg /= anz);
}

int avgNextPrim(int anz, int it)
{
	std::ofstream myfile;
	myfile.open("data.txt");

	for (int n = 1; n < 100; n++)
	{
		myfile << n << "\t" << avgDistance(anz, n, it) << std::endl;

	}
	myfile.close();
	return 0;
}
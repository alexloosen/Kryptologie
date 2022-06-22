#pragma once
#include "MyMath.h"

mp::cpp_int encrypt(mp::cpp_int msg, mp::cpp_int e, mp::cpp_int n)
{
	return mp::powm(msg, e, n);
}

mp::cpp_int decrypt(mp::cpp_int ciph, mp::cpp_int d, mp::cpp_int n)
{
	return mp::powm(ciph, d, n);
}

mp::cpp_int findRandomPrime(mpr::uniform_int_distribution<mp::cpp_int> ui)
{
	mp::cpp_int p = ui(mt);
	p = nextPrim(p, 25);
	return p;
}

int createKey(mp::cpp_int & n, mp::cpp_int & e, mp::cpp_int & d)
{
	mp::cpp_int f;
	mp::cpp_int lower = power((mp::cpp_int)10, (mp::cpp_int)(100 - 1));
	mp::cpp_int upper = power((mp::cpp_int)10, (mp::cpp_int)100) - 1;
	//std::cout << "Pruefe Zahlen von " << lower << " - " << upper << std::endl;

	// Zahlen ziehen
	mpr::uniform_int_distribution<mp::cpp_int> ui(lower, upper);

	mp::cpp_int p, q;

	//p = findRandomPrime(ui);
	//q = findRandomPrime(ui);
	p = 31;
	q = 41;

	n = p * q;
	f = (p - 1) * (q - 1);

	//e = findRandomPrime(ui);
	//if (mp::gcd(e, f) != 1)
	//{
	//	std::cout << "Fehler bei Erzeugung von e!" << std::endl;
	//	return -1;
	//}

	e = 2;

	while (e < f)
	{
		if (gcd(e, f) == 1)
		{
			break;
		}
		e++;
	}

	// Löse e*d = 1 mod f
	d = gcdExt(e,mp::cpp_int(1),f);

	std::cout << "Erzeugter Schluessel: " << std::endl <<
		"p = " << p << std::endl <<
		"q = " << q << std::endl <<
		"n = " << n << std::endl <<
		"e = " << e << std::endl <<
		"d = " << d << std::endl;

	return 0;
}
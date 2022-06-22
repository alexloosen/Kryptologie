#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <boost/random/independent_bits.hpp>
#include <boost/math/special_functions/pow.hpp>

#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <random>
#include <vector>


using namespace boost::multiprecision;
using namespace boost::random;

// Methode zur erzeugung großer Zahlen mit Basis und Exponent
template <typename T> T power(T base, T exponent)
{
	// exponent-lang prod mit Basis multiplizieren
	T prod = 1;
	while (exponent > 0)
	{
		//if (exponent % 2 == 0)
		//{
		//	prod = prod * prod;
		//	exponent /= 2;
		//	continue;
		//}
		prod *= base;
		exponent--;
	}
	return prod;
}

// gcd nach Euklidischem Algorithmus
template <typename T> int gcd(T a, T b, int& n)
{
	//std::cout << "Berechne gcd(" << a << "," << b << ")" << std::endl;
	// Laufvariablen
	T r0 = a;
	T r1 = b;
	T rk = 0;

	if (a == 0 || b == 0)
		return 0;
	// Solange rk = r0 mod r1 rechnen, bis es null ist.
	// An dieser Stelle ist r1 (das Ergebnis des letzten Durchlaufs) der gcd von (a,b)
	while (true)
	{
		n++;
		rk = r0 % r1;
		if (rk == 0)
		{
			//std::cout << "Schritte: " << n << std::endl;
			return (int)r1;
		}
		r0 = r1;
		r1 = rk;
	}
}

// erweiterter Euklidischer Algorithmus
template <typename T> T gcdExt(T c, T d, T m)
{
	int steps = 0;
	// Prüfung auf Lösbarkeit
	// c*x = d mod m ist lösbar wenn gcd(c,m) d teilt
	if (d % gcd(c, m, steps) != 0)
		return -1;
	// c*x = d mod m ist lösbar wenn gcd(c,m) = 1
	if (d == 1 && gcd(c, m, steps) != 1)
		return -2;
	// Variablen/Initialisierung
	int k = 1;
	T xs;
	std::vector<T> r;
	std::vector<T> q;
	std::vector<T> x;
	std::vector<T> y;

	// c,m tauschen, wenn c kleiner m
	//if (c < m)
	//	std::swap(c, m);

	r.push_back(c);
	r.push_back(m);

	q.push_back(0);
	q.push_back(0);

	x.push_back(1);
	x.push_back(0);

	y.push_back(0);
	y.push_back(1);

	while (true)
	{
		if (r[k - 1] % r[k] == 0)
			break;
		// rk+1 = rk-1 % rk
		r.push_back(r[k - 1] % r[k]);
		// qk+1 = qk-1 div qk - alle Integer verlieren beim Teilen den Nachkommaanteil
		q.push_back(r[k - 1] / r[k]);
		// xk+1 = xk-1 - xk * qk+1
		x.push_back(x[k - 1] - (x[k] * q[k + 1]));
		// yk+1 = yk-1 - yk * qk+1
		y.push_back(y[k - 1] - (y[k] * q[k + 1]));
		k++;
	}
	std::cout << "Erw. Euklidischer Algorithmus fuer " << c << " * x = " << d << " mod " << m << std::endl;
	std::cout << "\tr\t|\tq\t|\tx\t|\ty" << std::endl << "\t-------------------------------------------------" << std::endl;
	for (int i = 0; i < r.size(); i++)
	{
		std::cout << "\t" << r[i] << "\t|\t" << q[i] << "\t|\t" << x[i] << "\t|\t" << y[i] << std::endl;
	}
	// wenn c*x = d mod m, dann ist x = xs mod m wobei m hier im Code möglicherweise mit c vertauscht wurde (je nach dem welches groeßer war).
	// in jedem Fall steht das gesuchte m in r[0], also die größere der beiden Zahlen die per Algorithmus untersucht werden
	xs = (d / r.back()) * x.back();
	xs = xs % m;
	return xs < T(0) ? xs + m : xs;
}
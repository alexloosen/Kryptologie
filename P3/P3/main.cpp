#include "myCrypt.h"

#include <string>

int main()
{
	mp::cpp_int n, e, d, m, c;
	m = mp::cpp_int("4521657289549572843368406548163437198169851118668808227848449995252240926789287576240491184606659631257209109718731983090853400721187234895527349922599142328224858937269124959306508675349172813622356");
	c = mp::cpp_int("27965605169417597044704796410707146702830317180409957310903480707298305210637");
	int akt;
	std::string publicData = "publickey";
	std::string privateData = "privatekey";
	std::fstream fsPublic;
	std::fstream fsPrivate;
	while (true)
	{
		std::cout << std::endl
			<< "Aktion auswaehlen: " << std::endl
			<< "1. Neues Keypaar erstellen" << std::endl
			<< "2. Key in neuer Datei abspeichern" << std::endl
			<< "3. Key aus Datei einlesen" << std::endl
			<< "4. Nachricht verschluesseln" << std::endl
			<< "5. Nachricht entschluesseln" << std::endl
			<< "6. Programm beenden" << std::endl;
		std::cin >> akt;
		if (akt == 1)
		{
			createKey(n, e, d);
		}
		else if (akt == 2)
		{
			fsPublic.open(publicData, std::fstream::out);
			fsPrivate.open(privateData, std::fstream::out);
			fsPublic << n << "\t" << std::endl << e;
			fsPrivate << d << "\n";

			fsPublic.close();
			fsPrivate.close();
		}
		else if (akt == 3)
		{
			fsPublic.open(publicData, std::fstream::in);
			fsPrivate.open(privateData, std::fstream::in);
			{
				while (fsPublic >> n >> e){}
			}
			fsPrivate >> d;
			std::cout << "Gefundener Schluessel: " << std::endl <<
				"n = " << n << std::endl <<
				"e = " << e << std::endl <<
				"d = " << d << std::endl;

		}
		else if (akt == 4)
		{
			c = encrypt(m, e, n);
			std::cout << "Encrypted Message: " << c << std::endl;
		}
		else if (akt == 5)
		{
			m = decrypt(c, d, n);
			std::cout << "Decrypted Message: " << m << std::endl;
		}
		else
		{
			std::cout << "Programm wird beendet." << std::endl;
			break;
		}

	}
	// Stellenanzahl von m darf Stellenanzahl der beiden Primzahlen nicht überschreiten
	//std::cout << "Message: " << m << std::endl;
	//c = encrypt(m, e, n);
	//m = decrypt(c, d, n);
	system("pause");
	return 0;
}
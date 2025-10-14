
#include <iostream>
#include <iomanip>
#include <fstream>
#include<sstream>
#include <vector>
#include <codecvt>
//#include "tinyutf8.h"

using namespace std;

#include <Windows.h>
//#include <cstdio>

void printIfstreamErrorFlags(ifstream& stream)
{

	//SetConsoleOutputCP(CP_UTF8); //#include <Windows.h>

	cout << u8"\nWartoœci flag b³êdu strumienia: " << endl << endl;

	cout << "goodbit: "; // brak b³êdów strumienia
	if (stream.rdstate() & std::ifstream::goodbit)
		cout << 1 << endl;
	else cout << 0 << endl;

	cout << "eofbit: ";//osi¹gniêto koniec pliku w czasie czytania
	if (stream.rdstate() & std::ifstream::eofbit)
		cout << 1 << endl;
	else cout << 0 << endl;


	cout << "faildbit: ";//jakaœ operacja we/wy nie powiod³a siê. Po wyzerowaniu tej flagi strumieñ nadal nadaje siê do pracy.
	if (stream.rdstate() & std::ifstream::failbit)
		cout << 1 << endl;
	else cout << 0 << endl;


	cout << "badbit: ";//nast¹pi³ jakiœ powa¿ny b³¹d naruszaj¹cy budowê  strumienia. Dalsza praca z tym strumieniem jest niemo¿liwa.
	if (stream.rdstate() & std::ifstream::badbit)
		cout << 1 << endl << endl;
	else cout << 0 << endl << endl;

}


void printOfstreamErrorFlags(ofstream& stream)
{

	//SetConsoleOutputCP(CP_UTF8); //#include <Windows.h>

	cout << u8"\nWartoœci flag b³êdu strumienia: " << endl << endl;

	cout << "goodbit: "; // brak b³êdów strumienia
	if (stream.rdstate() & std::ofstream::goodbit)
		cout << 1 << endl;
	else cout << 0 << endl;

	cout << "eofbit: ";//osi¹gniêto koniec pliku w czasie czytania
	if (stream.rdstate() & std::ofstream::eofbit)
		cout << 1 << endl;
	else cout << 0 << endl;


	cout << "faildbit: ";//jakaœ operacja we/wy nie powiod³a siê. Po wyzerowaniu tej flagi strumieñ nadal nadaje siê do pracy.
	if (stream.rdstate() & std::ofstream::failbit)
		cout << 1 << endl;
	else cout << 0 << endl;


	cout << "badbit: ";//nast¹pi³ jakiœ powa¿ny b³¹d naruszaj¹cy budowê  strumienia. Dalsza praca z tym strumieniem jest niemo¿liwa.
	if (stream.rdstate() & std::ofstream::badbit)
		cout << 1 << endl << endl;
	else cout << 0 << endl << endl;

}



int main()
{

	SetConsoleOutputCP(CP_UTF8);

	/***************************Zapis pliku tekstowego**********************************************/

	//UWAGA:  w systemie Windows sekwencja koñca linii  LF w czasie zapisu zamieniana jest na CRLF


	ofstream outFile;

	const char* name = "plik.txt";//typ string te¿ dzia³a w funkcji open

	printOfstreamErrorFlags(outFile);


	outFile.open(name, ios::out);//otwarcie w trybie zapisu (tworzenia)

	if (!outFile.good())// funkcja good() zwraca wartoœæ true je¿eli flaga goodbit jest ustawiona na 1 
	{
		cout << u8"B³¹d otwarcia pliku: " << name << endl;// ogólny komunikat z kontekstu kodu 

		printOfstreamErrorFlags(outFile);

		exit(1);
	}


	//-----------------------------------------------------------------------------------------------------
	//u¿ycie funkcji ostream & put(char)  


	string linia1 = u8"¿ó³ty";
	string linia2 = "linia2";
	string linia3 = "linia3";

	for (char c : linia1)
		outFile.put(c);
	outFile.put('\n');

	for (char c : linia2)
		outFile.put(c);
	outFile.put('\n');

	for (char c : linia3)
		outFile.put(c);


	outFile.close();

	//-------------------------------------------------------------------------------------------------[
	//u¿ycie  operatora << 
	outFile.open(name, ios::trunc);//otwarcie w trybie kasowania ca³ej zawartoœci (ale nie samego pliku)

	outFile << linia1 << endl;
	outFile << linia2 << endl;
	outFile << linia3;
	outFile.close();
	// sprawdzanie stanu flag 

	printOfstreamErrorFlags(outFile);




	/***************************Czytanie pliku tekstowego**********************************************/


	ifstream inFile;

	
	//UWAGA:  w systemie Windows sekwencja koñca linii  CRLF w czasie czytania zamieniana jest na LF

	printIfstreamErrorFlags(inFile);


	inFile.open(name, ios::in);//otwarcie w trybie czytania


	printIfstreamErrorFlags(inFile);


	if (!inFile.good())// funkcja good() zwraca wartoœæ true je¿eli flaga goodbit jest ustawiona na 1 
	{
		cout << u8"B³¹d otwarcia pliku: " << name << endl;// ogólny komunikat z kontekstu kodu 

		printIfstreamErrorFlags(inFile);

		exit(1);
	}

	//-----------------------------------------------------------------------------------------------------
	//u¿ycie funkcji 'int get()'  //nie czyta poprawnie utf8 - st¹d poni¿ej czêœæ bajtów pliku ignorujemy
	//(ale w druku numerycznym jest ok - 2 bajty na polski znak, np. '¿' to bajty 197 188) - ¿eby to zobaczyæ zakomentuj inFile.ignore(ile_ignorujemy);
	int ile = 0;

	int i;

	int ile_ignorujemy = linia1.size() + 1;
	inFile.ignore(ile_ignorujemy);

	while (!inFile.eof())// po LF równie¿ drukuje '\n'
	{
		ile++;
		i = inFile.get();
		//cout << char(i) << '\n';//znakowo - jako ostatni¹ wartoœæ wydrukuje '\n',bo char(-1) nie istnieje
		cout << i << '\n';//numerycznie - jako ostatni¹ wartoœæ wydrukuje -1 i '\n', bo get() zwróci EOF
	}

	bool test_eof = inFile.eof();

	// sprawdzanie stanu flag 

	printIfstreamErrorFlags(inFile);

	if (inFile.eof())// sprawdza czy flaga eofbit jest ustawiona
		inFile.clear(inFile.rdstate() & ~ios_base::eofbit);//kasowanie flagi eofbit  

	printIfstreamErrorFlags(inFile);

	if (inFile.fail())// sprawdza czy flaga eof lub flaga failbit s¹ ustawione
		inFile.clear(inFile.rdstate() & ~(ios::eofbit | ios::failbit));

	printIfstreamErrorFlags(inFile);

	inFile.seekg(0, inFile.beg);//reset pozycji - nie dzia³a gdy wczeœniej osi¹gnieto  - flagi b³êdu eofbit i/lub fail s¹ ustawione 

	//--------------------------------------------------------------------------------------
	//u¿ycie funkcji 'istream & get(typ_znaku &c)' - podobnie nie czyta poprawnie utf8
	

	inFile.ignore(ile_ignorujemy);


	ile = 0;
	char c;
	while (!inFile.eof()) //koniec gdy eofbit == 1
	{
		ile++;
		inFile.get(c);//tu zostanie osi¹gniêty EOF, ale wartoœæ c siê nie zmieni i w zwi¹zku z tym ostani znak by³by drukowany podwójnie bez ponizszego if

		if (!inFile.eof())
			cout << c << '\n';
	}


	if (inFile.fail())// sprawdza czy flaga eof lub flaga failbit s¹ ustawione
		inFile.clear(inFile.rdstate() & ~(ios::eofbit | ios::failbit));

	inFile.seekg(0, inFile.beg);

	//-----------------------------------------------------------------------------------------
	//u¿ycie funkcji istream& get(char* gdzie , streamsize d³ugoœæ , char ogranicznik ='\n' ) 

	char znaki[10000];//maksymalna iloœæ czytanych znaków
	inFile.get(znaki, sizeof(znaki), EOF);// czyta maksymalnie 255 znaków, chyba ¿e wczeœniej natrafi na ogranicznik. 
	//Ogranicznik EOF powoduje przeczytanie wszystkiego, ³¹cznie ze znakami LF	
	cout << znaki;// znak LF jest w ci¹gu znaki
	cout << endl;//w ostatniej linii nie ma LF


	if (inFile.fail())// sprawdza czy flaga eof lub flaga failbit s¹ ustawione
		inFile.clear(inFile.rdstate() & ~(ios::eofbit | ios::failbit));

	inFile.seekg(0, inFile.beg);



	//-------------------------------------------------------------------------------------
	//u¿ycie funkcji istream & getline(char * gdzie , streamsize ile , char ogran = '\n');

	char linia[255];//maksymalna d³ugoœæ linii
	while (inFile.getline(linia, sizeof(linia)))// znak LF jest usuwany z linii
		cout << linia << endl;


	if (inFile.fail())// sprawdza czy flaga eof lub flaga failbit s¹ ustawione
		inFile.clear(inFile.rdstate() & ~(ios::eofbit | ios::failbit));

	inFile.seekg(0, inFile.beg);


	//-------------------------------------------------------------------------------------
	//u¿ycie funkcji istream & std::getline(istream wej , string schowek , char ogranicznik = '\n');

	string line;
	while (getline(inFile, line))// znak LF jest usuwany z linii
		cout << line << endl;

	if (inFile.fail())// sprawdza czy flaga eof lub flaga failbit s¹ ustawione
		inFile.clear(inFile.rdstate() & ~(ios::eofbit | ios::failbit));

	inFile.seekg(0, inFile.beg);


	//-------------------------------------------------------------------------------------
	//u¿ycie operatora >> z klasy istream

	string Linia;
	while (inFile >> Linia)  // znaki LF s¹ usuwane
	{
		cout << Linia << endl;
	}


	if (inFile.fail())// sprawdza czy flaga eof lub flaga failbit s¹ ustawione
		inFile.clear(inFile.rdstate() & ~(ios::eofbit | ios::failbit));

	inFile.seekg(0, inFile.beg);


	//-------------------------------------------------------------------------------------
	//u¿ycie funkcji filebuf* rdbuf() const z klasy ifstream

	ostringstream ss;
	ss << inFile.rdbuf(); // wczytanie ca³ego pliku ze znakami LF
	string linie = ss.str();//konwersja na jeden string
	cout << linie;
	cout << endl;//ostatnia linia nie ma LF


	//-------------------------------------------------------------------------------------
	//u¿ycie funkcji read i vector<::byte> C++17


	auto endPos = inFile.tellg();
	inFile.seekg(0, inFile.beg);
	int size = size_t(endPos - inFile.tellg());//rozmiar pliku

	std::vector<::byte> buff(size);
	inFile.read((char*)buff.data(), buff.size());
	cout << buff.data() << endl;

	inFile.close();


	//##################################################################################################################################

	//zapis do  pliku binarnego 


	string nameB{ "plik.bin" };

	ofstream outFileB;

	outFileB.open(nameB, ios::out | ios::binary);

	printOfstreamErrorFlags(outFileB);

	//dane do zapisu
	struct Osoba
	{
		string imie;
		string nazwisko;
		int wiek;
		double wzrost;
	};


	double d{ 13.14322872 };
	int n{ 10034 };
	string txt{ u8"chsz¹szcz brzmi w trzcinie" };
	string komunikat{ u8"W szczêkach\n chrz¹szcza\n trzeszczy mi¹¿sz," };
	Osoba osoba{ u8"Pawe³", u8"Œmie³owski", 30, 186.5 };

	outFileB.write((char*)&d, sizeof(double));
	outFileB.write((char*)&n, sizeof(int));
	int dlugosc_txt = txt.size();
	outFileB.write((char*)&dlugosc_txt, sizeof(int));
	//cout << txt.data() << sizeof(char) * dlugosc_txt << endl;
	outFileB.write((char*)txt.data(), sizeof(char) * dlugosc_txt);
	int dlugosc_kom = komunikat.size();
	outFileB.write((char*)&dlugosc_kom, sizeof(int));
	outFileB.write((char*)komunikat.data(), sizeof(char) * dlugosc_kom);
	outFileB.write((char*)&osoba, sizeof(osoba));
	outFileB.close();


	printOfstreamErrorFlags(outFileB);


	/***************************Czytanie pliku binarnego**********************************************/


	ifstream inFileB;

	inFileB.open(nameB, ios::in | ios::binary);



	printIfstreamErrorFlags(inFileB);

	//zmienne do wczytania danych

	//-------------------------------------------------------------------------------------------------------
	//u¿ycie u¿ycie funkcji istream & read(char* gdzie , streamsize ile ); 

	double D;
	int N, DLUGOSC_TXT, DLUGOSC_KOM;
	string TXT;
	string KOMUNIKAT;
	Osoba OSOBA;


	inFileB.read((char*)&D, sizeof(double));
	inFileB.read((char*)&N, sizeof(int));
	inFileB.read((char*)&DLUGOSC_TXT, sizeof(int));
	TXT.resize(DLUGOSC_TXT);
	inFileB.read((char*)&TXT[0], DLUGOSC_TXT);
	inFileB.read((char*)&DLUGOSC_KOM, sizeof(int));
	KOMUNIKAT.resize(DLUGOSC_KOM);
	inFileB.read((char*)&KOMUNIKAT[0], DLUGOSC_KOM);
	inFileB.read((char*)&OSOBA, sizeof(Osoba));


	cout << D << endl;
	cout << N << endl;
	cout << TXT << endl;
	cout << KOMUNIKAT << endl;
	cout << OSOBA.imie << " " << OSOBA.nazwisko << " " << OSOBA.wiek << " " << OSOBA.wzrost << endl;

	printIfstreamErrorFlags(inFileB);


	if (inFile.fail())// sprawdza czy flaga eof lub flaga failbit s¹ ustawione
		inFile.clear(inFile.rdstate() & ~(ios::eofbit | ios::failbit));


	//-------------------------------------------------------------------------------------------------------
	//u¿ycie vector<byte> 

	auto end = inFileB.tellg();
	inFileB.seekg(0, inFile.beg);
	int fileSize = size_t(end - inFileB.tellg());//rozmiar pliku

	std::vector<::byte> buffer(fileSize);

	inFileB.read((char*)buffer.data(), buffer.size());

	double* Liczba = reinterpret_cast<double*>(buffer.data());

	int offset = sizeof(double);

	int* LiczbaInt = reinterpret_cast<int*>(buffer.data() + offset);

	offset += sizeof(int);

	int* dlugoscInt = reinterpret_cast<int*>(buffer.data() + offset);

	offset += sizeof(int);

	std::vector<char> textBuf1(buffer.begin() + offset, buffer.begin() + offset + *dlugoscInt);

	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

	std::wstring text1 = converter.from_bytes(textBuf1.data(), textBuf1.data() + textBuf1.size());

	offset += *dlugoscInt;

	dlugoscInt = reinterpret_cast<int*>(buffer.data() + offset);

	offset += sizeof(int);

	std::vector<char> textBuf2(buffer.begin() + offset, buffer.begin() + offset + *dlugoscInt);

	std::wstring text2 = converter.from_bytes(textBuf2.data(), textBuf2.data() + textBuf2.size());

	offset += *dlugoscInt;

	Osoba* osoba1 = reinterpret_cast<Osoba*>(buffer.data() + offset);

	//int osobaSize = sizeof(osoba1->wzrost);

	cout << *Liczba << endl;
	cout << *LiczbaInt << endl;
	cout << converter.to_bytes(text1) << endl;
	cout << converter.to_bytes(text2) << endl;
	cout << osoba1->imie << endl;
	cout << osoba1->nazwisko << endl;
	cout << osoba1->wiek << endl;
	cout << osoba1->wzrost << endl;

	inFileB.close();
	
}


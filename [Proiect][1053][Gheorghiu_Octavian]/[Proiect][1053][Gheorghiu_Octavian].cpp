#include <iostream>
#include <string>
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
using namespace std;


class ProdusGolf {
private:
	static int idProdusCurent;
	const int idProdus;
	char* numeProdus = nullptr;
	int numarDimensiuni = 0;
	float vanzari[3] = { 0,0,0 };
	float* dimensiune = nullptr;
	float* pret = nullptr;
public:
	ProdusGolf() :idProdus(idProdusCurent) {
		this->idProdusCurent++;
		this->numeProdus = new char[4];
		strcpy(this->numeProdus, "N/A");
	}

	ProdusGolf(char* numeProdus) : idProdus(idProdusCurent) {
		this->idProdusCurent++;
		if (numeProdus != nullptr) {
			this->numeProdus = new char[strlen(numeProdus) + 1];
			strcpy(this->numeProdus, numeProdus);
		}

		else {
			this->numeProdus = new char[4];
			strcpy(this->numeProdus, "N/A");
		}
	}

	ProdusGolf(char* numeProdus, int numarDimensiuni, float* dimensiune, float* pret, float* vanzari) : idProdus(idProdusCurent) {
		this->idProdusCurent++;
		if (numeProdus != nullptr) {
			this->numeProdus = new char[strlen(numeProdus) + 1];
			strcpy(this->numeProdus, numeProdus);
		}
		else {
			this->numeProdus = new char[4];
			strcpy(this->numeProdus, "N/A");
		}
		if (numarDimensiuni != 0 && dimensiune != nullptr && pret != nullptr) {
			this->numarDimensiuni = numarDimensiuni;
			this->dimensiune = new float[this->numarDimensiuni];
			this->pret = new float[this->numarDimensiuni];
			for (int i = 0; i < this->numarDimensiuni; i++) {
				this->dimensiune[i] = dimensiune[i];
				this->pret[i] = pret[i];
			}
		}
		for (int i = 0; i < 3; i++)
			this->vanzari[i] = vanzari[i];

	}

	ProdusGolf(const ProdusGolf& p) :idProdus(p.idProdus) {
		if (p.numeProdus != nullptr) {
			this->numeProdus = new char[strlen(p.numeProdus) + 1];
			strcpy(this->numeProdus, p.numeProdus);
			if (p.numarDimensiuni != 0 && p.dimensiune != nullptr && p.pret != nullptr) {
				this->numarDimensiuni = p.numarDimensiuni;
				this->dimensiune = new float[this->numarDimensiuni];
				this->pret = new float[this->numarDimensiuni];
				for (int i = 0; i < this->numarDimensiuni; i++) {
					this->dimensiune[i] = p.dimensiune[i];
					this->pret[i] = p.pret[i];
				}
			}
			for (int i = 0; i < 3; i++)
				this->vanzari[i] = p.vanzari[i];
		}
	}

	ProdusGolf operator=(const ProdusGolf& p) {
		if (this != &p) {
			if (p.numeProdus != nullptr) {
				if (this->numeProdus != nullptr)
					delete[] this->numeProdus;
				this->numeProdus = new char[strlen(p.numeProdus) + 1];
				strcpy(this->numeProdus, p.numeProdus);
				if (p.numarDimensiuni != 0 && p.dimensiune != nullptr && p.pret != nullptr) {
					this->numarDimensiuni = p.numarDimensiuni;
					if (this->dimensiune != nullptr)
						delete[] this->dimensiune;
					this->dimensiune = new float[this->numarDimensiuni];
					if (this->pret != nullptr)
						delete[]this->pret;
					this->pret = new float[this->numarDimensiuni];
					for (int i = 0; i < this->numarDimensiuni; i++) {
						this->dimensiune[i] = p.dimensiune[i];
						this->pret[i] = p.pret[i];
					}
				}
				for (int i = 0; i < 3; i++)
					this->vanzari[i] = p.vanzari[i];
			}
		}
		return *this;
	}

	void setNumeProdus(char* numeProdus) {
		if (numeProdus != nullptr) {
			if (this->numeProdus != nullptr)
				delete[] this->numeProdus;
			this->numeProdus = new char[strlen(numeProdus) + 1];
			strcpy(this->numeProdus, numeProdus);
		}
	}

	int getIdProdus() {
		return this->idProdus;
	}

	float profitProdus() {
		float profit = 0;
		for (int i = 0; i < 3; i++)
			profit += this->vanzari[i];
		return profit;
	}

	float operator[](int index) {
		if (index > 0 && index < this->numarDimensiuni)
			return this->pret[index];
	}

	ProdusGolf& operator++() {
		if (this->numarDimensiuni > 0 && this->pret != nullptr) {
			for (int i = 0; i < this->numarDimensiuni; i++)
				this->pret[i] = this->pret[i] + 0.1 * this->pret[i];
		}
		return *this;
	}

	ProdusGolf operator++(int x) {
		ProdusGolf copie = *this;
		if (this->numarDimensiuni > 0 && this->pret != nullptr) {
			for (int i = 0; i < this->numarDimensiuni; i++)
				this->pret[i] = this->pret[i] + 0.1 * this->pret[i];
		}
		return copie;
	}

	ProdusGolf& operator+=(float vanzare) {
		if (vanzare >= 0) {
			this->vanzari[0] = this->vanzari[1];
			this->vanzari[1] = vanzari[2];
			this->vanzari[2] = vanzare;
		}
		return *this;
	}

	ProdusGolf operator+(float vanzare) {
		ProdusGolf copie = *this;
		copie += vanzare;
		return copie;
	}

	bool operator>(ProdusGolf p) {
		return this->profitProdus() > p.profitProdus();
	}

	bool operator!() {
		if (this->numarDimensiuni == 0 && this->dimensiune == nullptr && this->pret == nullptr)
			return true;
		else
			return false;
	}

	explicit operator float() {
		return this->vanzari[this->numarDimensiuni - 1];
	}

	friend ostream& operator<<(ostream& out, const ProdusGolf& p) {
		out << "\n****";
		out << "\nid: " << p.idProdus;
		if (p.numeProdus == nullptr)
			out << "\nNume produs: N/A";
		else
			out << "\nNume produs: " << p.numeProdus;
		out << "\nNumar dimensiuni: " << p.numarDimensiuni;
		if (p.numarDimensiuni > 0 && p.dimensiune != nullptr && p.pret != nullptr) {
			for (int i = 0; i < p.numarDimensiuni; i++) {
				out << "\n" << i + 1 << ". dimensiunea de: " << p.dimensiune[i] << " cu pretul de : " << p.pret[i] << " lei.";
			}
		}
		out << "\n Vanzarile pe ultimele 3 luni (lei): " << p.vanzari[0] << ", " << p.vanzari[1] << ", " << p.vanzari[2];
		out << endl;
		return out;
	}

	friend istream& operator>>(istream& in, ProdusGolf& p) {
		cout << "\n\nNume: ";
		char aux[20];
		//in.getline(aux, 20);
		in >> aux;
		if (p.numeProdus != nullptr)
			delete[] p.numeProdus;
		p.numeProdus = new char[strlen(aux) + 1];
		strcpy(p.numeProdus, aux);
		cout << "\nNumar dimensiuni: ";
		in >> p.numarDimensiuni;
		if (p.numarDimensiuni > 0) {
			p.dimensiune = new float[p.numarDimensiuni];
			p.pret = new float[p.numarDimensiuni];
			for (int i = 0; i < p.numarDimensiuni; i++) {
				cout << endl << i + 1 << ". dimensiunea: ";
				in >> p.dimensiune[i];
				cout << "cu pretul de:";
				in >> p.pret[i];
			}
		}
		cout << "\nVanzarile pe ultimele 3 luni:";
		in >> p.vanzari[0];
		in >> p.vanzari[1];
		in >> p.vanzari[2];

		return in;
	}

	void writeToBinFile(fstream& f) {
		int lg = strlen(this->numeProdus)+1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->numeProdus, lg);
		for (int i = 0; i < 3; i++)
			f.write((char*)&this->vanzari[i], sizeof(float));
		f.write((char*)&this->numarDimensiuni, sizeof(int));
		for(int i=0;i<this->numarDimensiuni;i++)
			f.write((char*)&this->dimensiune[i], sizeof(float));
		for (int i = 0; i < this->numarDimensiuni; i++)
			f.write((char*)&this->pret[i], sizeof(float));
	}

	void readFromBinFile(fstream& f) {
		int lg = 0;
		f.read((char*)&lg, sizeof(int));
		char* buf = new char[lg];
		f.read(buf, lg);
		if (this->numeProdus != nullptr)
			delete[] this->numeProdus;
		this->numeProdus = new char[lg];
		strcpy(this->numeProdus, buf);
		delete[] buf;
		for (int i = 0; i < 3; i++)
			f.read((char*)&this->vanzari[i], sizeof(float));
		if (this->dimensiune != nullptr)
			delete[] this->dimensiune;
		if (this->pret != nullptr)
			delete[] this->pret;
		f.read((char*)&this->numarDimensiuni, sizeof(float));
		this->dimensiune = new float[this->numarDimensiuni];
		this->pret = new float[this->numarDimensiuni];
		for (int i = 0; i < this->numarDimensiuni; i++)
			f.read((char*)&this->dimensiune[i], sizeof(float));
		for (int i = 0; i < this->numarDimensiuni; i++)
			f.read((char*)&this->pret[i], sizeof(float));
	}

	void readFromTxtFile(fstream& f) {
		char aux[100];
		f >> aux;
		if (this->numeProdus != nullptr)
			delete[]this->numeProdus;
		this->numeProdus = new char[strlen(aux) + 1];
		strcpy(this->numeProdus, aux);
		for (int i = 0; i < 3; i++) 
			f >> this->vanzari[i];
		f >> this->numarDimensiuni;
		this->dimensiune = new float[this->numarDimensiuni];
		for (int i = 0; i < this->numarDimensiuni; i++)
			f >> this->dimensiune[i];
		this->pret = new float[this->numarDimensiuni];
		for (int i = 0; i < this->numarDimensiuni; i++)
			f >> this->pret[i];
 }

	~ProdusGolf() {
		if (this->numeProdus != nullptr)
			delete[] this->numeProdus;
		if (this->dimensiune != nullptr)
			delete[]this->dimensiune;
		if (this->pret != nullptr)
			delete[]this->pret;
	}
};
int ProdusGolf::idProdusCurent = 1;

class Teren {
private:
	static int idTerenCurent;
	const int idTeren;
	char* numeTeren = nullptr;
	int numarObstacole[3] = { 0,0,0 };//obstacole de tip apa, nisip si zona cu acces dificil
	int par = 0;//numarul asteptat de lovituri
	int numarHoleInOne = 0;//cate persoane au dat din prima;
	string* numeSportivi = nullptr;
public:

	Teren() :idTeren(idTerenCurent) {
		this->idTerenCurent++;
		this->numeTeren = new char[6];
		strcpy(this->numeTeren, "teren");
	}

	Teren(char* numeTeren, int par, int* numarObstacole, int numarHoleInOne, string* numeSportivi) :idTeren(idTerenCurent) {
		this->idTerenCurent++;
		if (numeTeren != nullptr) {
			this->numeTeren = new char[strlen(numeTeren) + 1];
			strcpy(this->numeTeren, numeTeren);
		}
		else {
			this->numeTeren = new char[6];
			strcpy(this->numeTeren, "teren");
		}
		this->par = par;
		for (int i = 0; i < 3; i++)
			this->numarObstacole[i] = numarObstacole[i];
		if (numarHoleInOne > 0 && numeSportivi != nullptr) {
			this->numarHoleInOne = numarHoleInOne;
			this->numeSportivi = new string[this->numarHoleInOne];
			for (int i = 0; i < this->numarHoleInOne; i++)
				this->numeSportivi[i] = numeSportivi[i];
		}
	}

	Teren(const Teren& t) :idTeren(t.idTeren) {
		if (t.numeTeren != nullptr) {
			this->numeTeren = new char[strlen(t.numeTeren) + 1];
			strcpy(this->numeTeren, t.numeTeren);
		}
		else {
			this->numeTeren = new char[6];
			strcpy(this->numeTeren, "teren");
		}
		this->par = t.par;
		for (int i = 0; i < 3; i++)
			this->numarObstacole[i] = t.numarObstacole[i];
		if (t.numarHoleInOne > 0 && t.numeSportivi != nullptr) {
			this->numarHoleInOne = t.numarHoleInOne;
			this->numeSportivi = new string[this->numarHoleInOne];
			for (int i = 0; i < this->numarHoleInOne; i++)
				this->numeSportivi[i] = t.numeSportivi[i];
		}
	}

	Teren operator=(const Teren& t) {
		if (this != &t) {
			if (t.numeTeren != nullptr) {
				if (this->numeTeren != nullptr);
				delete[]this->numeTeren;
				this->numeTeren = new char[strlen(t.numeTeren) + 1];
				strcpy(this->numeTeren, t.numeTeren);
			}
			this->par = t.par;
			for (int i = 0; i < 3; i++)
				this->numarObstacole[i] = t.numarObstacole[i];
			if (t.numarHoleInOne > 0 && t.numeSportivi != nullptr) {
				this->numarHoleInOne = t.numarHoleInOne;
				if (this->numeSportivi != nullptr)
					delete[]this->numeSportivi;
				this->numeSportivi = new string[this->numarHoleInOne];
				for (int i = 0; i < this->numarHoleInOne; i++)
					this->numeSportivi[i] = t.numeSportivi[i];
			}
		}
		return *this;
	}

	int numarTotalObstacole() {
		int total = 0;
		total += this->numarObstacole[0];
		total += this->numarObstacole[1];
		total += this->numarObstacole[2];
		return total;
	}

	char* getNumeTeren() {
		return this->numeTeren;
	}

	int operator[](int index) {
		if (index > 0 && index < 3)
			return this->numarObstacole[index];
	}

	bool operator>(const Teren& t) {
		return(this->par > t.par);
	}

	bool operator!() {
		if (this->numarHoleInOne == 0)
			return true;
		return false;
	}

	explicit operator int() {
		return this->numarTotalObstacole();
	}

	Teren& operator++() {
		this->par++;
		return*this;
	}

	Teren& operator++(int x) {
		Teren copie = *this;
		this->par++;
		return copie;
	}

	Teren& operator+=(string numeSportiv) {
		Teren copie = *this;
		this->numarHoleInOne++;
		if (this->numeSportivi != nullptr)
			delete[]this->numeSportivi;
		this->numeSportivi = new string[numarHoleInOne];
		for (int i = 0; i < this->numarHoleInOne - 1; i++)
			this->numeSportivi[i] = copie.numeSportivi[i];
		this->numeSportivi[this->numarHoleInOne - 1] = numeSportiv;
		return *this;
	}

	Teren& operator+(string numeSportiv) {
		Teren copie = *this;
		copie += numeSportiv;
		return copie;
	}

	friend ostream& operator<<(ostream& out, const Teren& t) {
		out << "\n\n****";
		out << "\nid teren: " << t.idTeren;
		out << "\nNume teren: " << t.numeTeren;
		out << "\nPar: " << t.par;
		out << "\nNumar obstacole: ";
		out << "\n -Apa: " << t.numarObstacole[0];
		out << "\n -Nisip: " << t.numarObstacole[1];
		out << "\n -Acces dificil: " << t.numarObstacole[2];
		out << "\nNumar hole-in-one: " << t.numarHoleInOne << endl;
		if (t.numarHoleInOne > 0 && t.numeSportivi != nullptr)
			for (int i = 0; i < t.numarHoleInOne; i++)
				out << i + 1 << ": " << t.numeSportivi[i] << "   ";
		return out;
	}

	friend istream& operator>>(istream& in, Teren& t) {
		cout << "\n\nNume: ";
		char aux[30];
		in >> aux;
		if (strlen(aux) > 1) {
			delete[]t.numeTeren;
			t.numeTeren = new char[strlen(aux) + 1];
			strcpy(t.numeTeren, aux);
		}
		cout << "Par: ";
		in >> t.par;
		cout << "Numar obstacole de tip apa: ";
		in >> t.numarObstacole[0];
		cout << "Numar obstacole de tip nisip: ";
		in >> t.numarObstacole[1];
		cout << "Numar obstacole de tip acces dificil: ";
		in >> t.numarObstacole[2];
		cout << "Numar de hole in one: ";
		in >> t.numarHoleInOne;
		if (t.numarHoleInOne > 0) {
			t.numeSportivi = new string[t.numarHoleInOne];
			for (int i = 0; i < t.numarHoleInOne; i++) {
				cout << i + 1 << ": ";
				in >> t.numeSportivi[i];
			}
		}
		return in;
	}

	void writeToBinFile(fstream& f) {
		int lg = strlen(this->numeTeren) + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->numeTeren,lg);
		for (int i = 0; i < 3; i++)
			f.write((char*)&this->numarObstacole, sizeof(int));
		f.write((char*)&this->par, sizeof(int));
		f.write((char*)&this->numarHoleInOne, sizeof(int));
		for (int i = 0; i < this->numarHoleInOne; i++) {
			int lg = this->numeSportivi[i].length() + 1;
			f.write((char*)&lg, sizeof(int));
			f.write(this->numeSportivi[i].data(), lg);
		}
	}

	void readFromBinFile(fstream& f) {
		int lg = 0;
		f.read((char*)&lg, sizeof(int));
		char* buf = new char[lg];
		f.read(buf, lg);
		if (this->numeTeren != nullptr)
			delete[] this->numeTeren;
		this->numeTeren = new char[lg];
		strcpy(this->numeTeren, buf);
		delete[] buf;
		for (int i = 0; i < 3; i++)
			f.read((char*)&this->numarObstacole[i], sizeof(int));
		f.read((char*)&this->par, sizeof(int));
		f.read((char*)&this->numarHoleInOne, sizeof(int));
		this->numeSportivi = new string[this->numarHoleInOne];
		for (int i = 0; i < this->numarHoleInOne; i++) {
			f.read((char*)&lg, sizeof(int));
			char* buf = new char[lg];
			f.read(buf, lg);
			this->numeSportivi[i] = buf;
			delete[] buf;
		}

	}

	void readFromTxtFile(fstream& f) {
		char aux[100];
		f >> aux;
		if (this->numeTeren != nullptr)
			delete[]this->numeTeren;
		this->numeTeren = new char[strlen(aux) + 1];
		strcpy(this->numeTeren, aux);
		f >> this->numarObstacole[0];
		f >> this->numarObstacole[1];
		f >> this->numarObstacole[2];
		f >> this->par;
		f >> this->numarHoleInOne;
		this->numeSportivi = new string[this->numarHoleInOne];
		for (int i = 0; i < this->numarHoleInOne; i++)
			f >> this->numeSportivi[i];
	}

	~Teren() {
		if (this->numeTeren != nullptr)
			delete[]this->numeTeren;
		if (this->numeSportivi != nullptr)
			delete[]this->numeSportivi;
	}
};
int Teren::idTerenCurent = 1;

class Jucator {
private:
	static int idJucatorCurent;
	const int idJucator;
	char* numeJucator = nullptr;
	int varsta = 0;
	int mediePunctaj[5] = { 3,3,3,3,3 };//istoric ultimele 5 punctaje
	int numarCampionateJucate = 0;
	int* locuri = nullptr;

public:
	Jucator() :idJucator(idJucatorCurent) {
		this->idJucatorCurent++;
		this->numeJucator = new char[7];
		strcpy(this->numeJucator, "Anonim");
	}

	Jucator(char* numeJucator, int varsta, int* mediePunctaj, int numarCampionateJucate, int* locuri) :idJucator(idJucatorCurent) {
		this->idJucatorCurent++;
		if (numeJucator != nullptr) {
			this->numeJucator = new char[strlen(numeJucator) + 1];
			strcpy(this->numeJucator, numeJucator);
		}
		else {
			this->numeJucator = new char[10];
			strcpy(this->numeJucator, "Anonim");
		}
		if (varsta > 0)
			this->varsta = varsta;
		for (int i = 0; i < 5; i++)
			this->mediePunctaj[i] = mediePunctaj[i];
		if (numarCampionateJucate > 0 && locuri != nullptr) {
			this->numarCampionateJucate = numarCampionateJucate;
			this->locuri = new int[this->numarCampionateJucate];
			for (int i = 0; i < this->numarCampionateJucate; i++)
				this->locuri[i] = locuri[i];
		}

	}

	Jucator(const Jucator& j) :idJucator(j.idJucator) {
		if (j.numeJucator != nullptr) {
			this->numeJucator = new char[strlen(j.numeJucator) + 1];
			strcpy(this->numeJucator, j.numeJucator);
		}
		else {
			this->numeJucator = new char[10];
			strcpy(this->numeJucator, "Anonim");
		}
		if (j.varsta > 0)
			this->varsta = j.varsta;
		for (int i = 0; i < 5; i++)
			this->mediePunctaj[i] = j.mediePunctaj[i];
		if (j.numarCampionateJucate > 0 && j.locuri != nullptr) {
			this->numarCampionateJucate = j.numarCampionateJucate;
			this->locuri = new int[this->numarCampionateJucate];
			for (int i = 0; i < this->numarCampionateJucate; i++)
				this->locuri[i] = j.locuri[i];
		}
	}

	Jucator operator=(const Jucator& j) {
		if (this != &j) {
			if (j.numeJucator != nullptr) {
				if (this->numeJucator != nullptr)
					delete[]this->numeJucator;
				this->numeJucator = new char[strlen(j.numeJucator) + 1];
				strcpy(this->numeJucator, j.numeJucator);
			}
			else {
				this->numeJucator = new char[10];
				strcpy(this->numeJucator, "Anonim");
			}
			if (j.varsta > 0)
				this->varsta = j.varsta;
			for (int i = 0; i < 5; i++)
				this->mediePunctaj[i] = j.mediePunctaj[i];
			if (j.numarCampionateJucate > 0 && j.locuri != nullptr) {
				this->numarCampionateJucate = j.numarCampionateJucate;
				if (this->locuri != nullptr)
					delete[]this->locuri;
				this->locuri = new int[this->numarCampionateJucate];
				for (int i = 0; i < this->numarCampionateJucate; i++)
					this->locuri[i] = j.locuri[i];
			}
		}
		return *this;
	}

	int locMaxim() {
		int maxim = 1000;
		if (this->numarCampionateJucate > 0 && this->locuri != nullptr) {
			maxim = this->locuri[0];
			for (int i = 1; i < this->numarCampionateJucate; i++)
				if (this->locuri[i] > maxim)
					maxim = this->locuri[i];
		}
		else {
			maxim = 0;
		}
		return maxim;
	}

	void setNumeJucator(char* numeJucator) {
		if (numeJucator != nullptr) {
			if (this->numeJucator != nullptr)
				delete[] this->numeJucator;
			this->numeJucator = new char[strlen(numeJucator) + 1];
			strcpy(this->numeJucator, numeJucator);
		}
	}

	char* getNumeJucator() {
		return this->numeJucator;
	}

	int getIdJucator() {
		return this->idJucator;
	}

	int operator[](int index) {
		if (index > 0 && index < this->numarCampionateJucate)
			return this->locuri[index];
	}

	bool operator>(Jucator j) {
		if (this->locMaxim() != 0 && j.locMaxim() != 0)
			return this->locMaxim() > j.locMaxim();
		if (this->locMaxim() == 0 && j.locMaxim() != 0)
			return false;
		if (this->locMaxim() != 0 && j.locMaxim() == 0)
			return true;
		return false;
	}

	bool operator!() {
		if (this->numarCampionateJucate == 0 && this->locuri == nullptr)
			return true;
		else
			return false;
	}

	explicit operator int() {
		return this->mediePunctaj[0];
	}

	Jucator& operator++() {
		this->varsta++;
		return *this;
	}

	Jucator& operator++(int x) {
		Jucator copie = *this;
		this->varsta++;
		return copie;
	}

	Jucator& operator+=(int mediePunctaj) {
		this->mediePunctaj[4] = this->mediePunctaj[3];
		this->mediePunctaj[3] = this->mediePunctaj[2];
		this->mediePunctaj[2] = this->mediePunctaj[1];
		this->mediePunctaj[1] = this->mediePunctaj[0];
		this->mediePunctaj[0] = mediePunctaj;
		return *this;
	}

	Jucator& operator+(int mediePunctaj) {
		Jucator copie = *this;
		copie += mediePunctaj;
		return copie;
	}

	friend ostream& operator<<(ostream& out, const Jucator& j) {
		cout << "\n\n****";
		out << "\nid jucator: " << j.idJucator;
		out << "\nNume jucator: " << j.numeJucator;
		out << "\nVarsta: " << j.varsta;
		out << "\nMedie punctaje: ";
		for (int i = 0; i < 5; i++)
			out << j.mediePunctaj[i] << " ";
		out << "\nNumar campionate jucate: " << j.numarCampionateJucate << endl;
		if (j.numarCampionateJucate > 0 && j.locuri != nullptr)
			for (int i = 0; i < j.numarCampionateJucate; i++)
				out << i + 1 << ": " << j.locuri[i] << " ";
		return out;
	}

	friend istream& operator>>(istream& in, Jucator& j) {
		cout << "\nNume: ";
		char aux[30];
		in >> aux;
		if (strlen(aux) > 1) {
			delete[]j.numeJucator;
			j.numeJucator = new char[strlen(aux) + 1];
			strcpy(j.numeJucator, aux);
		}
		cout << "\nVarsta: ";
		in >> j.varsta;
		cout << "\nMedie ultimele 5 punctaje: ";
		for (int i = 0; i < 5; i++)
			in >> j.mediePunctaj[i];
		cout << "\nNumar campionate jucate: ";
		in >> j.numarCampionateJucate;
		if (j.numarCampionateJucate > 0) {
			if (j.locuri != nullptr)
				delete[]j.locuri;
			j.locuri = new int[j.numarCampionateJucate];
			for (int i = 0; i < j.numarCampionateJucate; i++) {
				cout << "\nCampionatul " << i + 1 << ": ";
				in >> j.locuri[i];
			}
		}
		return in;
	}

	void writeToBinFile(fstream& f) {
		int lg = strlen(this->numeJucator) + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->numeJucator, lg);
		f.write((char*)&this->varsta, sizeof(int));
		for(int i=0;i<5;i++)
			f.write((char*)&this->mediePunctaj[i], sizeof(int));
		f.write((char*)&this->numarCampionateJucate, sizeof(int));
		for(int i=0;i<this->numarCampionateJucate;i++)
			f.write((char*)&this->locuri[i], sizeof(int));
	}

	void readFromBinFile(fstream& f) {
		int lg = 0;
		f.read((char*)&lg, sizeof(int));
		char* buf = new char[lg];
		f.read(buf, lg);
		if (this->numeJucator != nullptr)
			delete[] this->numeJucator;
		this->numeJucator = new char[lg];
		strcpy(this->numeJucator, buf);
		delete[] buf;
		f.read((char*)&this->varsta, sizeof(int));
		for(int i=0;i<5;i++)
			f.read((char*)&this->mediePunctaj[i], sizeof(int));
		f.read((char*)&this->numarCampionateJucate, sizeof(int));
		if (this->locuri != nullptr)
			delete[] this->locuri;
		this->locuri = new int[this->numarCampionateJucate];
		for (int i = 0; i < this->numarCampionateJucate; i++)
			f.read((char*)&this->locuri[i], sizeof(int));
	}

	void readFromTxtFile(fstream& f) {
		char aux[100];
		f >> aux;
		if (this->numeJucator != nullptr)
			delete[]this->numeJucator;
		this->numeJucator = new char[strlen(aux) + 1];
		strcpy(this->numeJucator, aux);
		f >> this->varsta;
		for (int i = 0; i < 5; i++)
			f >> this->mediePunctaj[i];
		f >> this->numarCampionateJucate;
		for (int i = 0; i < this->numarCampionateJucate; i++)
			f >> this->locuri[i];
	}

	~Jucator() {
		if (this->numeJucator != nullptr)
			delete[]this->numeJucator;
		if (this->locuri != nullptr)
			delete[]this->locuri;
	}
};
int Jucator::idJucatorCurent = 1;

class Campionat {
private:
	char* numeCampionat = nullptr;
	int premii[3] = { 10000,5000,3000 };
	static int taxaInscriere;
	int numarTerenuri = 0;
	Teren* terenuri = nullptr;
	int numarJucatori = 0;
	Jucator* jucatori = nullptr;

public:
	Campionat() {
		this->numeCampionat = new char[10];
		strcpy(this->numeCampionat, "Campionat");
	}

	Campionat(char* numeCampionat) {
		if (strlen(numeCampionat) > 1) {
			this->numeCampionat = new char[strlen(numeCampionat) + 1];
			strcpy(this->numeCampionat, numeCampionat);
		}
		else {
			this->numeCampionat = new char[10];
			strcpy(this->numeCampionat, "Campionat");
		}
	}

	Campionat(char* numeCampionat, int numarTerenuri, Teren* terenuri, int numarJucatori, Jucator* jucatori, int* premii) {
		if (strlen(numeCampionat) > 1) {
			this->numeCampionat = new char[strlen(numeCampionat) + 1];
			strcpy(this->numeCampionat, numeCampionat);
		}
		else {
			this->numeCampionat = new char[10];
			strcpy(this->numeCampionat, "Campionat");
		}
		if (numarTerenuri > 0 && terenuri != nullptr) {
			this->numarTerenuri = numarTerenuri;
			this->terenuri = new Teren[numarTerenuri];
			for (int i = 0; i < this->numarTerenuri; i++)
				this->terenuri[i] = terenuri[i];
		}
		if (numarJucatori > 0 && jucatori != nullptr) {
			this->numarJucatori = numarJucatori;
			this->jucatori = new Jucator[this->numarJucatori];
			for (int i = 0; i < this->numarTerenuri; i++)
				this->jucatori[i] = jucatori[i];
		}
		if (premii != nullptr) {
			this->premii[0] = premii[0];
			this->premii[1] = premii[1];
			this->premii[2] = premii[2];
		}
	}

	Campionat(const Campionat& c) {
		this->numeCampionat = new char[strlen(c.numeCampionat) + 1];
		strcpy(this->numeCampionat, c.numeCampionat);
		if (numarTerenuri > 0 && c.terenuri != nullptr) {
			this->numarTerenuri = c.numarTerenuri;
			this->terenuri = new Teren[c.numarTerenuri];
			for (int i = 0; i < this->numarTerenuri; i++)
				this->terenuri[i] = c.terenuri[i];
		}
		if (c.numarJucatori > 0 && c.jucatori != nullptr) {
			this->numarJucatori = c.numarJucatori;
			this->jucatori = new Jucator[this->numarJucatori];
			for (int i = 0; i < this->numarTerenuri; i++)
				this->jucatori[i] = c.jucatori[i];
		}
		if (premii != nullptr) {
			this->premii[0] = c.premii[0];
			this->premii[1] = c.premii[1];
			this->premii[2] = c.premii[2];
		}
	}

	Campionat operator=(const Campionat& c) {
		if (this != &c) {
			this->numeCampionat = new char[strlen(c.numeCampionat) + 1];
			strcpy(this->numeCampionat, c.numeCampionat);
			if (numarTerenuri > 0 && c.terenuri != nullptr) {
				this->numarTerenuri = c.numarTerenuri;
				if (this->terenuri != nullptr)
					delete[]this->terenuri;
				this->terenuri = new Teren[c.numarTerenuri];
				for (int i = 0; i < this->numarTerenuri; i++)
					this->terenuri[i] = c.terenuri[i];
			}
			if (c.numarJucatori > 0 && c.jucatori != nullptr) {
				this->numarJucatori = c.numarJucatori;
				if (this->jucatori != nullptr)
					delete[]this->jucatori;
				this->jucatori = new Jucator[this->numarJucatori];
				for (int i = 0; i < this->numarTerenuri; i++)
					this->jucatori[i] = c.jucatori[i];
			}
			if (premii != nullptr) {
				this->premii[0] = c.premii[0];
				this->premii[1] = c.premii[1];
				this->premii[2] = c.premii[2];
			}
		}
		return *this;
	}

	void addParticipant(const Jucator j) {
		Campionat copie = *this;
		this->numarJucatori++;
		if (this->jucatori != nullptr)
			delete[]this->jucatori;
		this->jucatori = new Jucator[this->numarJucatori];
		for (int i = 0; i < this->numarJucatori - 1; i++)
			this->jucatori[i] = copie.jucatori[i];
		this->jucatori[this->numarJucatori - 1] = j;
	}

	int getPremiiTotale() {
		int premiiTotale = 0;;
		premiiTotale += this->premii[0];
		premiiTotale += this->premii[1];
		premiiTotale += this->premii[2];
		return premiiTotale;
	}

	string getNumeCampionat() {
		return this->numeCampionat;
	}

	Teren operator[](int index) {
		if (index > 0 && index < this->numarTerenuri)
			return this->terenuri[index];
	}

	explicit operator Jucator() {
		return this->jucatori[0];
	}

	bool operator>(Campionat c) {
		return(this->getPremiiTotale() > c.getPremiiTotale());
	}

	bool operator!() {
		if (this->numarJucatori == 0)
			return true;
		return false;
	}

	Campionat& operator++() {
		this->premii[0] += 1000;
		this->premii[1] += 1000;
		this->premii[2] += 1000;
		return *this;
	}

	Campionat operator++(int x) {
		Campionat copie = *this;
		this->premii[0] += 1000;
		this->premii[1] += 1000;
		this->premii[2] += 1000;
		return copie;
	}

	Campionat& operator+=(int valoare) {
		this->premii[0] += valoare;
		return *this;
	}

	Campionat& operator+(int valoare) {
		Campionat copie = *this;
		copie += valoare;
		return copie;
	}

	friend ostream& operator<<(ostream& out, const Campionat& c) {
		out << "\n\n<~~~~~~~~~~~~~~~CAMPIONAT~~~~~~~~~~~~~~~>\n";
		out << "\nNume campionat: " << c.numeCampionat;
		out << "\nNumar terenuri: " << c.numarTerenuri;
		if (c.numarTerenuri > 0 && c.terenuri != nullptr)
			for (int i = 0; i < c.numarTerenuri; i++)
				out << "\n------- Teren " << i + 1 << " -------" << c.terenuri[i];
		out << "\nNumar jucatori: " << c.numarJucatori;
		if (c.numarJucatori > 0 && c.jucatori != nullptr)
			for (int i = 0; i < c.numarJucatori; i++)
				out << "\n------- Jucator " << i + 1 << " -------" << c.jucatori[i];
		out << endl << "\nPremii pentru top 3: " << c.premii[0] << ", " << c.premii[1] << ", " << c.premii[2];
		return out;
	}

	friend istream& operator>>(istream& in, Campionat& c) {
		cout << "\nNume campionat: ";
		char aux[30];
		in >> aux;
		if (c.numeCampionat != nullptr)
			delete[]c.numeCampionat;
		c.numeCampionat = new char[strlen(aux) + 1];
		strcpy(c.numeCampionat, aux);
		cout << "\nNumar terenuri: ";
		in >> c.numarTerenuri;
		if (c.numarTerenuri > 0) {
			if (c.terenuri != nullptr)
				delete[]c.terenuri;
			c.terenuri = new Teren[c.numarTerenuri];
			for (int i = 0; i < c.numarTerenuri; i++) {
				cout << "\n\n--TERENUL " << i + 1 << "--";
				in >> c.terenuri[i];
			}
		}
		cout << "\nNumar jucatori: ";
		in >> c.numarJucatori;
		if (c.numarJucatori > 0) {
			if (c.jucatori != nullptr)
				delete[]c.jucatori;
			c.jucatori = new Jucator[c.numarJucatori];
			for (int i = 0; i < c.numarJucatori; i++) {
				cout << "\n\n--JUCATORUL " << i + 1 << "--";
				in >> c.jucatori[i];
			}
		}
		cout << "\nPremiul locul 1: ";
		in >> c.premii[0];
		cout << "\nPremiul locul 2: ";
		in >> c.premii[1];
		cout << "\nPremiul locul 3: ";
		in >> c.premii[2];
		return in;
	}

	void writeToBinFile(fstream& f) {
		int lg = strlen(this->numeCampionat) + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->numeCampionat, lg);
		f.write((char*)&this->numarTerenuri, sizeof(int));
		for (int i = 0; i < this->numarTerenuri; i++)
			this->terenuri[i].writeToBinFile(f);
		f.write((char*)&this->numarJucatori, sizeof(int));
		for (int i = 0; i < this->numarJucatori; i++)
			this->jucatori[i].writeToBinFile(f);
		for (int i = 0; i < 3; i++)
			f.write((char*)&this->premii[i], sizeof(int));
		f.write((char*)&this->taxaInscriere, sizeof(int));
	}

	void readFromBinFile(fstream& f) {
		int lg = 0;
		f.read((char*)&lg, sizeof(int));
		char* buf = new char[lg];
		f.read(buf, lg);
		if (this->numeCampionat != nullptr)
			delete[] this->numeCampionat;
		this->numeCampionat = new char[lg];
		strcpy(this->numeCampionat, buf);
		delete[] buf;
		f.read((char*)&this->numarTerenuri, sizeof(int));
		if (this->terenuri != nullptr)
			delete[] this->terenuri;
		this->terenuri = new Teren[this->numarTerenuri];
		for (int i = 0; i < this->numarTerenuri; i++)
			this->terenuri[i].readFromBinFile(f);
		f.read((char*)&this->numarJucatori, sizeof(int));
		if (this->jucatori != nullptr)
			delete[] this->jucatori;
		this->jucatori = new Jucator[this->numarJucatori];
		for (int i = 0; i < this->numarJucatori; i++)
			this->jucatori[i].readFromBinFile(f);
		for (int i = 0; i < 3; i++)
			f.read((char*)&this->premii[i], sizeof(int));
		f.read((char*)&this->taxaInscriere, sizeof(int));
	}

	void readFromTxtFile(fstream& f) {
		char aux[100];
		f >> aux;
		if (this->numeCampionat != nullptr)
			delete[]this->numeCampionat;
		this->numeCampionat = new char[strlen(aux) + 1];
		strcpy(this->numeCampionat, aux);
		f >> this->premii[0];
		f >> this->premii[1];
		f >> this->premii[2];
		f >> this->taxaInscriere;
		f >> this->numarTerenuri;
		if (this->terenuri != nullptr)
			delete[]this->terenuri;
		this->terenuri = new Teren[this->numarTerenuri];
		for (int i = 0; i < this->numarTerenuri; i++)
			terenuri[i].readFromTxtFile(f);
		f >> this->numarJucatori;
		if (this->jucatori != nullptr)
			delete[]this->jucatori;
		this->jucatori = new Jucator[this->numarJucatori];
		for (int i = 0; i < this->numarJucatori; i++)
			jucatori[i].readFromTxtFile(f);
	}

	~Campionat() {
		if (this->terenuri != nullptr)
			delete[]this->terenuri;
		if (this->jucatori != nullptr)
			delete[]this->jucatori;
	}
};
int Campionat::taxaInscriere = 100;

class GolfClub {
private:
	static int idGolfClubCurent;
	const int idGolfClub;
	char* numeClub = nullptr;
	int preturi[2]{ 50,400 };//pret pe lusa si pe an
	int numarJucatori = 0;
	Jucator* jucatori = nullptr;
	int numarTerenuri = 0;
	Teren* terenuri = nullptr;
	int numarCampionate = 0;
	Campionat* campionate = nullptr;
	int numarProduse = 0;
	ProdusGolf* produse = nullptr;
public:
	GolfClub() :idGolfClub(idGolfClubCurent) {
		this->idGolfClubCurent++;
		this->numeClub = new char[15];
		strcpy(this->numeClub, "Club de golf");
	}

	GolfClub(char* numeClub, int* preturi, int numarJucatori, Jucator* jucatori, int numarTerenuri, Teren* terenuri, int numarCampionate, Campionat* campionate, int numarProduse, ProdusGolf* produse) :idGolfClub(idGolfClubCurent) {
		this->idGolfClubCurent++;
		if (numeClub != nullptr) {
			this->numeClub = new char[strlen(numeClub) + 1];
			strcpy(this->numeClub, numeClub);
		}
		this->preturi[0] = preturi[0];
		this->preturi[1] = preturi[1];
		if (numarJucatori > 0 && jucatori != nullptr) {
			this->numarJucatori = numarJucatori;
			this->jucatori = new Jucator[this->numarJucatori];
			for (int i = 0; i < this->numarJucatori; i++)
				this->jucatori[i] = jucatori[i];
		}
		if (numarTerenuri > 0 && terenuri != nullptr) {
			this->numarTerenuri = numarTerenuri;
			this->terenuri = new Teren[numarTerenuri];
			for (int i = 0; i < this->numarTerenuri; i++)
				this->terenuri[i] = terenuri[i];
		}
		if (numarCampionate > 0 && campionate != nullptr) {
			this->numarCampionate = numarCampionate;
			this->campionate = new Campionat[this->numarCampionate];
			for (int i = 0; i < this->numarCampionate; i++)
				this->campionate[i] = campionate[i];
		}
		if (numarProduse > 0 && produse != nullptr) {
			this->numarProduse = numarProduse;
			this->produse = new ProdusGolf[this->numarProduse];
			for (int i = 0; i < this->numarProduse; i++)
				this->produse[i] = produse[i];
		}
	}

	GolfClub(const GolfClub& g) :idGolfClub(g.idGolfClub) {
		if (g.numeClub != nullptr) {
			this->numeClub = new char[strlen(g.numeClub) + 1];
			strcpy(this->numeClub, g.numeClub);
		}
		this->preturi[0] = g.preturi[0];
		this->preturi[1] = g.preturi[1];
		if (g.numarJucatori > 0 && g.jucatori != nullptr) {
			this->numarJucatori = g.numarJucatori;
			this->jucatori = new Jucator[this->numarJucatori];
			for (int i = 0; i < this->numarJucatori; i++)
				this->jucatori[i] = g.jucatori[i];
		}
		if (g.numarTerenuri > 0 && g.terenuri != nullptr) {
			this->numarTerenuri = g.numarTerenuri;
			this->terenuri = new Teren[g.numarTerenuri];
			for (int i = 0; i < this->numarTerenuri; i++)
				this->terenuri[i] = g.terenuri[i];
		}
		if (g.numarCampionate > 0 && g.campionate != nullptr) {
			this->numarCampionate = g.numarCampionate;
			this->campionate = new Campionat[this->numarCampionate];
			for (int i = 0; i < this->numarCampionate; i++)
				this->campionate[i] = g.campionate[i];
		}
		if (g.numarProduse > 0 && g.produse != nullptr) {
			this->numarProduse = g.numarProduse;
			this->produse = new ProdusGolf[this->numarProduse];
			for (int i = 0; i < this->numarProduse; i++)
				this->produse[i] = g.produse[i];
		}
	}

	int getIdClubGolf() {
		return this->idGolfClub;
	}

	int getProfitMaxim() {
		return (this->preturi[1] * this->numarJucatori);
	}

	GolfClub operator=(const GolfClub& g) {
		if (this != &g) {
			if (g.numeClub != nullptr) {
				this->numeClub = new char[strlen(g.numeClub) + 1];
				strcpy(this->numeClub, g.numeClub);
			}
			this->preturi[0] = g.preturi[0];
			this->preturi[1] = g.preturi[1];
			if (g.numarJucatori > 0 && g.jucatori != nullptr) {
				this->numarJucatori = g.numarJucatori;
				this->jucatori = new Jucator[this->numarJucatori];
				for (int i = 0; i < this->numarJucatori; i++)
					this->jucatori[i] = g.jucatori[i];
			}
			if (g.numarTerenuri > 0 && g.terenuri != nullptr) {
				this->numarTerenuri = g.numarTerenuri;
				this->terenuri = new Teren[g.numarTerenuri];
				for (int i = 0; i < this->numarTerenuri; i++)
					this->terenuri[i] = g.terenuri[i];
			}
			if (g.numarCampionate > 0 && g.campionate != nullptr) {
				this->numarCampionate = g.numarCampionate;
				this->campionate = new Campionat[this->numarCampionate];
				for (int i = 0; i < this->numarCampionate; i++)
					this->campionate[i] = g.campionate[i];
			}
			if (g.numarProduse > 0 && g.produse != nullptr) {
				this->numarProduse = g.numarProduse;
				this->produse = new ProdusGolf[this->numarProduse];
				for (int i = 0; i < this->numarProduse; i++)
					this->produse[i] = g.produse[i];
			}
		}
		return *this;
	}

	GolfClub& operator++() {
		this->preturi[0] += 10;
		this->preturi[1] += 100;
		return *this;
	}

	GolfClub operator++(int x) {
		GolfClub copie;
		this->preturi[0] += 10;
		this->preturi[1] += 100;
		return copie;
	}

	Campionat operator[](int index) {
		if (index > 0 && index < this->numarCampionate)
			return this->campionate[index];
	}

	explicit operator Teren() {
		return this->terenuri[0];
	}

	bool operator!() {
		if (this->numarJucatori < 1)
			return true;
		return false;
	}

	bool operator>(GolfClub g) {
		return(this->preturi[1] > g.preturi[1]);
	}

	friend ostream& operator<<(ostream& out, const GolfClub& g) {
		out << "\n\n->->->->->->->->->->GOLF CLUB<-<-<-<-<-<-<-<-<-<-";
		out << "\nid club: " << g.idGolfClub;
		out << "\nNume club: " << g.numeClub;
		out << "\nPret abonament:  1 luna: " << g.preturi[0] << ",  12 luni: " << g.preturi[1];
		out << "\nNumar jucatori: " << g.numarJucatori;
		if (g.numarJucatori > 0 && g.jucatori != nullptr)
			for (int i = 0; i < g.numarJucatori; i++)
				out << "\n" << i + 1 << ". " << g.jucatori[i];
		out << "\nNumar terenuri: " << g.numarTerenuri;
		if (g.numarTerenuri > 0 && g.terenuri != nullptr)
			for (int i = 0; i < g.numarTerenuri; i++)
				out << "\n" << i + 1 << ". " << g.terenuri[i];
		out << "\nNumar campionate: " << g.numarCampionate;
		if (g.numarCampionate > 0 && g.campionate != nullptr)
			for (int i = 0; i < g.numarCampionate; i++)
				out << "\n" << i + 1 << ". " << g.campionate[i];
		out << "\nNumar Produse: " << g.numarProduse;
		if (g.numarProduse > 0 && g.produse != nullptr)
			for (int i = 0; i < g.numarProduse; i++)
				out << "\n" << i + 1 << ". " << g.produse[i];
		return out;
	}

	friend istream& operator>>(istream& in, GolfClub& g) {
		cout << "\nNume club: ";
		char aux[30];
		in >> aux;
		if (strlen(aux) > 1) {
			delete[]g.numeClub;
			g.numeClub = new char[strlen(aux) + 1];
			strcpy(g.numeClub, aux);
		}
		cout << "\nPretul pe 1 luna respectiv 12 luni";
		in >> g.preturi[0];
		in >> g.preturi[1];

		cout << "\nnumar Jucatori: ";
		in >> g.numarJucatori;
		if (g.numarJucatori > 0) {
			if (g.jucatori != nullptr)
				delete[]g.jucatori;
			g.jucatori = new Jucator[g.numarJucatori];
			for (int i = 0; i < g.numarJucatori; i++) {
				cout << "\n\n--JUCATORUL " << i + 1 << "--";
				in >> g.jucatori[i];
			}
		}

		cout << "\nNumar terenuri: ";
		in >> g.numarTerenuri;
		if (g.numarTerenuri > 0) {
			if (g.terenuri != nullptr)
				delete[]g.terenuri;
			g.terenuri = new Teren[g.numarTerenuri];
			for (int i = 0; i < g.numarTerenuri; i++) {
				cout << "\n\n--TERENUL " << i + 1 << "--";
				in >> g.terenuri[i];
			}
		}

		cout << "\nNumar campionate: ";
		in >> g.numarCampionate;
		if (g.numarCampionate > 0) {
			if (g.campionate != nullptr)
				delete[]g.campionate;
			g.campionate = new Campionat[g.numarCampionate];
			for (int i = 0; i < g.numarCampionate; i++) {
				cout << "\n\n--CAMPIONATUL " << i + 1 << "--";
				in >> g.campionate[i];
			}
		}

		cout << "\nNumar produse: ";
		in >> g.numarProduse;
		if (g.numarProduse > 0) {
			if (g.produse != nullptr)
				delete[]g.produse;
			g.produse = new ProdusGolf[g.numarProduse];
			for (int i = 0; i < g.numarProduse; i++) {
				cout << "\n\n--PRODUSUL " << i + 1 << "--";
				in >> g.produse[i];
			}
		}

		return in;
	}

	void writeToBinFile(fstream& f) {
		int lg = strlen(this->numeClub) + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->numeClub, lg);
		f.write((char*)&this->preturi[0], sizeof(int));
		f.write((char*)&this->preturi[1], sizeof(int));
		f.write((char*)&this->numarJucatori, sizeof(int));
		for (int i = 0; i < this->numarJucatori; i++)
			this->jucatori[i].writeToBinFile(f);
		f.write((char*)&this->numarTerenuri, sizeof(int));
		for (int i = 0; i < this->numarTerenuri; i++)
			this->terenuri[i].writeToBinFile(f);
		f.write((char*)&this->numarCampionate, sizeof(int));
		for (int i = 0; i < this->numarCampionate; i++)
			this->campionate[i].writeToBinFile(f);
		f.write((char*)&this->numarProduse, sizeof(int));
		for (int i = 0; i < this->numarProduse; i++)
			this->produse[i].writeToBinFile(f);
	}

	void readFromBinFile(fstream& f) {
		int lg = 0;
		f.read((char*)&lg, sizeof(int));
		char* buf = new char[lg];
		f.read(buf, lg);
		if (this->numeClub != nullptr)
			delete[] this->numeClub;
		this->numeClub = new char[lg];
		strcpy(this->numeClub, buf);
		delete[] buf;
		f.read((char*)&this->preturi[0], sizeof(int));
		f.read((char*)&this->preturi[1], sizeof(int));
		f.read((char*)&this->numarJucatori, sizeof(int));
		if (this->jucatori != nullptr)
			delete[] this->jucatori;
		this->jucatori = new Jucator[this->numarJucatori];
		for (int i = 0; i < this->numarJucatori; i++)
			this->jucatori[i].readFromBinFile(f);
		f.read((char*)&this->numarTerenuri, sizeof(int));
		if (this->terenuri != nullptr)
			delete[] this->terenuri;
		this->terenuri = new Teren[this->numarTerenuri];
		for (int i = 0; i < this->numarTerenuri; i++)
			this->terenuri[i].readFromBinFile(f);
		f.read((char*)&this->numarCampionate, sizeof(int));
		if (this->campionate != nullptr)
			delete[] this->campionate;
		this->campionate = new Campionat[this->numarCampionate];
		for (int i = 0; i < this->numarCampionate; i++)
			this->campionate[i].readFromBinFile(f);
		f.read((char*)&this->numarProduse, sizeof(int));
		if (this->produse != nullptr)
			delete[] this->produse;
		this->produse = new ProdusGolf[this->numarProduse];
		for (int i = 0; i < this->numarProduse; i++)
			this->produse[i].readFromBinFile(f);
	}

	~GolfClub() {
		if (this->numeClub != nullptr)
			delete[]this->numeClub;
		if (this->jucatori != nullptr)
			delete[]this->jucatori;
		if (this->terenuri != nullptr)
			delete[]this->terenuri;
		if (this->campionate != nullptr)
			delete[]this->campionate;
		if (this->produse != nullptr)
			delete[]this->produse;
	}
};
int GolfClub::idGolfClubCurent = 1;


class Gestiune {
private:
	int _numarProduse = 0;
	ProdusGolf* _produse = nullptr;
	int _numarTerenuri = 0;
	Teren* _terenuri = nullptr;
	int _numarJucatori = 0;
	Jucator* _jucatori = nullptr;
	int _numarCampionate = 0;
	Campionat* _campionate = nullptr;
	int _numarCluburi = 0;
	GolfClub* _cluburi= nullptr;
	fstream finProduse;// ("Produse.txt", ios::in | ios::app);
	fstream finTerenuri;// ("Terenuri.txt", ios::in);
	fstream finJucatori;// ("Jucatori.txt", ios::in);
	fstream finCampionate;// ("Campionate.txt", ios::in);
	fstream finCluburi;// ("Cluburi.txt", ios::in);
public:
	Gestiune(int numarFisiere, char** fisiere) {
		int ok[5] = { 0,0,0,0,0 };
		if (numarFisiere > 1) {
			for (int i = 1; i < numarFisiere; i++)
				if (strstr(fisiere[i], "Produs")) {
					finProduse.open(fisiere[i], ios::in);
					if (finProduse.is_open()) {
						cout << "\n--FISIER TXT\n";
						finProduse >> this->_numarProduse;
						this->_produse = new ProdusGolf[this->_numarProduse];
						ProdusGolf produsAux;
						for (int i = 0; i < this->_numarProduse; i++) {
							produsAux.readFromTxtFile(finProduse);
							_produse[i] = produsAux;
							//cout << _produse[i];
						}
						ok[i-1]++;
					}
				}
			else
				if (strstr(fisiere[i], "Teren")) {
					finTerenuri.open(fisiere[i], ios::in);
					if (finTerenuri.is_open()) {
						cout << "\n--FISIER TXT\n";
						finTerenuri >> this->_numarTerenuri;
						this->_terenuri = new Teren[this->_numarTerenuri];
						Teren terenAux;
						for (int i = 0; i < this->_numarTerenuri; i++) {
							terenAux.readFromTxtFile(finTerenuri);
							_terenuri[i] = terenAux;
							//cout << _terenuri[i];
						}
						ok[i-1]++;
					}
				}
			else
				if (strstr(fisiere[i], "Jucator")) {
					finJucatori.open(fisiere[i], ios::in);
					if (finJucatori.is_open()) {
						cout << "\n--FISIER TXT\n";
						finJucatori >> this->_numarJucatori;
						this->_jucatori = new Jucator[this->_numarJucatori];
						Jucator jucatorAux;
						for (int i = 0; i < this->_numarJucatori; i++) {
							jucatorAux.readFromTxtFile(finJucatori);
							_jucatori[i] = jucatorAux;
							//cout << _jucatori[i];
						}
						ok[i-1]++;
					}
				}
			else
				if (strstr(fisiere[i], "Campionat")) {
					finCampionate.open(fisiere[i], ios::in);
					if (finCampionate.is_open()) {
						cout << "\n--FISIER TXT\n";
						finCampionate >> this->_numarCampionate;
						this->_campionate = new Campionat[this->_numarCampionate];
						Campionat campionatAux;
						for (int i = 0; i < this->_numarCampionate; i++) {
							campionatAux.readFromTxtFile(finCampionate);
							_campionate[i] = campionatAux;
							cout << _campionate[i];
						}
						ok[i-1]++;
					}
				}
			else
				if (strstr(fisiere[i], "Club")) {}
		}
			
		if (ok[0] == 0) {
			finProduse.open("ProduseBin.txt", ios::in | ios::binary);
			finProduse.read((char*)&this->_numarProduse, sizeof(int));
			cout <<endl << this->_numarProduse << " produse: ";
			cout << "\n--FISIER BIN\n";
			this->_produse = new ProdusGolf[this->_numarProduse];
			ProdusGolf produsAux;
			for (int i = 0; i < this->_numarProduse; i++) {
				produsAux.readFromBinFile(finProduse);
				this->_produse[i] = produsAux;
				//cout << _produse[i];
			}
			finProduse.close();
		}
		if (ok[1] == 0){
			finTerenuri.open("TerenuriBin.txt", ios::in | ios::binary);
			finTerenuri.read((char*)&this->_numarTerenuri, sizeof(int));
			cout <<endl << this->_numarTerenuri << " terenuri: ";
			cout << "\n--FISIER BIN\n";
			this->_terenuri = new Teren[this->_numarTerenuri];
			Teren terenAux;
			for (int i = 0; i < this->_numarTerenuri; i++) {
				terenAux.readFromBinFile(finTerenuri);
				this->_terenuri[i] = terenAux;
				//cout << _terenuri[i];
			}
			finTerenuri.close();
		}
		if (ok[2] == 0){
			finJucatori.open("JucatoriBin.txt", ios::in | ios::binary);
			finJucatori.read((char*)&this->_numarJucatori, sizeof(int));
			cout <<endl << this->_numarJucatori << " jucatori: ";
			cout << "\n--FISIER BIN\n";
			this->_jucatori = new Jucator[this->_numarJucatori];
			Jucator jucatorAux;
			for (int i = 0; i < this->_numarJucatori; i++) {
				jucatorAux.readFromBinFile(finJucatori);
				this->_jucatori[i] = jucatorAux;
				//cout << _jucatori[i];
			}
			finJucatori.close();
		}
		if (ok[3] == 0){
			finCampionate.open("CampionateBin.txt", ios::in | ios::binary);
			finCampionate.read((char*)&this->_numarCampionate, sizeof(int));
			cout << endl << this->_numarCampionate << " campionate: ";
			cout << "\n--FISIER BIN\n";
			this->_campionate = new Campionat[this->_numarCampionate];
			Campionat campionatAux;
			for (int i = 0; i < this->_numarCampionate; i++) {
				campionatAux.readFromBinFile(finCampionate);
				this->_campionate[i] = campionatAux;
				//cout << _campionate[i];
			}
			finCampionate.close();
		}
		if (ok[4] == 0){}

		
	}
	~Gestiune() {
		if (this->_produse != nullptr)
			delete[]this->_produse;
		if (this->_terenuri != nullptr)
			delete[]this->_terenuri;
		if (this->_jucatori != nullptr)
			delete[]this->_jucatori;
		if (this->_campionate != nullptr)
			delete[]this->_campionate;
		if (this->_cluburi != nullptr)
			delete[]this->_cluburi;
	}
};

int main(int numarFisiere, char* fisiere[7])
{
	int optiune = 0;
	cout << "Alegeti clasa:\n1.ProdusGolf.\n2.Teren.\n3.Jucator.\n4.Campionat.\n5.GolfClub.\n\nClasa nr.: ";
	cin >> optiune;
	switch (optiune)
	{
	case 1: {
		cout << "\n\n--------------------------------\n\tClasa ProdusGolf";
		char numeProdus1[20];
		strcpy(numeProdus1, "masinuta de golf");
		ProdusGolf p1(numeProdus1);
		cout << p1;
		char numeProdus2[20];
		strcpy(numeProdus2, "minge de golf");
		float vanzari[3] = { 230,400,150 };
		float dimensiuni[3] = { 1,2,3 };
		float pret[3] = { 5.5,10,14.5 };
		ProdusGolf p2(numeProdus2, 3, dimensiuni, pret, vanzari);
		cout << p2;
		ProdusGolf p3(p2);
		cout << p3;
		char numeProdus3[20];
		strcpy(numeProdus3, "crosa de golf");
		float vanzari2[3] = { 500,450,700 };
		float dimensiuni2[4] = { 4,6,8,12 };
		float pret2[4] = { 52.6, 66.3, 80, 99.9 };
		ProdusGolf p4(numeProdus3, 4, dimensiuni2, pret2, vanzari2);
		cout << p4;
		ProdusGolf p5;
		//cout << p5;
		//cin >> p5;
		//cout << p5;
		//p1 = p5;
		//cout << p1;
		char numeNou[20] = "Masina de golf";
		p1.setNumeProdus(numeNou);
		cout << p1;
		cout << p2.profitProdus() << endl;
		cout << p4.profitProdus() << endl;
		if (p2 > p4)
			cout << p2.profitProdus() << endl;
		else
			cout << p4.profitProdus() << endl;
		cout << p2[2];
		p2++;
		cout << p2;
		float ultimaVanzare = 0;
		ultimaVanzare = (float)p2;
		cout << ultimaVanzare;
		cout << p3 + 333;
		break;
	}
	case 2: {
		Teren t1;
		cout << t1;
		char numeTeren1[20];
		strcpy(numeTeren1, "Valea regilor");
		int numarObstacole1[3] = { 1,0,3 };
		string numeSportivi[3] = { "Tom Ford","Alexander","Mathew" };
		Teren t2(numeTeren1, 5, numarObstacole1, 3, numeSportivi);
		cout << t2;
		Teren t3(t2);
		cout << t3;
		t3 = t2;
		t3++;
		cout << t3;
		t3 += "Vlad";
		cout << t3;
		Teren t4;
		//cin >> t4;
		//cout << t4;
		cout << "\n\nNumar total obstacole pe terenul " << t3.getNumeTeren() << " este  de: " << t3.numarTotalObstacole();
		if (!t2)
			cout << endl << "nu a reusit nimeni hole in 1";
		else
			cout << endl << "Pe acest teren s-a dat hole in 1";
		int obstacoleNisip = t4[1];
		cout << endl << obstacoleNisip;
		int numarTotal = (int)t2;
		cout << endl << numarTotal;
		cout << endl;
		break;
	}
	case 3: {
		Jucator j1;
		cout << j1;
		char numeJucator1[30];
		strcpy(numeJucator1, "John Alexander");
		int mediePunctaj1[5] = { 3,5,2,0,0 };
		int locuri[4] = { 14,16,9,11 };
		Jucator j2(numeJucator1, 21, mediePunctaj1, 4, locuri);
		Jucator j3(j2);
		cout << j2;
		cout << j3;
		j1 = j2;
		cout << j1;
		Jucator j4;
		//cin >> j4;
		cout << j4;
		if (!j4)
			cout << endl << "Nu este complet jucatorul cu id-ul " << j4.getIdJucator();
		int maxim = j2.locMaxim();
		cout << endl << maxim;
		char nume2[20];
		strcpy(nume2, "Valeriu");
		j4.setNumeJucator(nume2);
		if (j2 > j4)
			cout << endl << j2.getNumeJucator() << "are un rezultat mai bun decat " << j4.getNumeJucator() << endl;
		j4++;
		j4 += 4;
		cout << j4;
		int ultimaMedie = (int)j2;
		cout << endl << ultimaMedie;
		cout << endl << j2[2];
		break;
	}
	case 4: {
		cout << "\n\n--------------------------------\n\tClasa Campionat";
		//Teren

		Teren t1;
		char numeTeren1[20];
		strcpy(numeTeren1, "Valea regilor");
		int numarObstacole1[3] = { 1,0,3 };
		string numeSportivi[3] = { "Tom Ford","Alexander","Mathew" };
		Teren t2(numeTeren1, 5, numarObstacole1, 3, numeSportivi);
		Teren t3(t2);
		t3++;
		t3 += "Vlad";
		Teren t4;

		//ProdusGolf

		char numeProdus1[20];
		strcpy(numeProdus1, "masinuta de golf");
		ProdusGolf p1(numeProdus1);
		char numeProdus2[20];
		strcpy(numeProdus2, "minge de golf");
		float vanzari[3] = { 230,400,150 };
		float dimensiuni[3] = { 1,2,3 };
		float pret[3] = { 5.5,10,14.5 };
		ProdusGolf p2(numeProdus2, 3, dimensiuni, pret, vanzari);
		ProdusGolf p3(p2);
		char numeProdus3[20];
		strcpy(numeProdus3, "crosa de golf");
		float vanzari2[3] = { 500,450,700 };
		float dimensiuni2[4] = { 4,6,8,12 };
		float pret2[4] = { 52.6, 66.3, 80, 99.9 };
		ProdusGolf p4(numeProdus3, 4, dimensiuni2, pret2, vanzari2);
		ProdusGolf p5;
		char numeNou[20] = "Masina de golf";
		p1.setNumeProdus(numeNou);

		//Jucaor

		Jucator j1;
		char numeJucator1[30];
		strcpy(numeJucator1, "John Alexander");
		int mediePunctaj1[5] = { 3,5,2,0,0 };
		int locuri[4] = { 14,16,9,11 };
		Jucator j2(numeJucator1, 21, mediePunctaj1, 4, locuri);
		Jucator j3(j2);
		j1 = j2;
		Jucator j4;
		j4++;
		j4 += 4;

		//campionat
		char numeCampionat1[20];
		strcpy(numeCampionat1, "Cupa amatorilor");
		Campionat c1(numeCampionat1);

		Teren terenuri1[2] = { t1,t2 };
		Jucator jucatori1[2] = { j1,j2 };
		int premii[3] = { 20000,10000,5000 };
		char numeCampionat2[20];
		strcpy(numeCampionat2, "Cupa mare");
		Campionat c2(numeCampionat2, 2, terenuri1, 2, jucatori1, premii);

		cout << c1;
		cout << c2;
		Campionat c3(c2);
		cout << endl << c3.getPremiiTotale();
		c3 += 200;
		cout << endl << c3.getPremiiTotale();
		if (c2 > c1)
			cout << endl << "campionatul cu premiile cele mai mari este: " << c2.getNumeCampionat() << endl;
		else
			cout << endl << "campionatul cu premiile cele mai mari este: " << c1.getNumeCampionat() << endl;
		char numeCampionat3[20];
		strcpy(numeCampionat3, "Cupa Intermediara");
		Campionat c4(numeCampionat3);
		//cin >> c4;
		//cout << endl << c4 << endl;
		if (!c4)
			cout << "\n\nNu s-a inscris nimeni la cupa " << c4.getNumeCampionat();
		cout << c2[1];
		cout << "\n\nprima persoana inscrisa este: " << (Jucator)c2;
		c1.addParticipant(j3);
		cout << c1;

		cout << endl;

		break;
	}
	case 5: {
		cout << "\n\n--------------------------------\n\tClasa GolfClub";
		//Teren

		Teren t1;
		char numeTeren1[20];
		strcpy(numeTeren1, "Valea regilor");
		int numarObstacole1[3] = { 1,0,3 };
		string numeSportivi[3] = { "Tom Ford","Alexander","Mathew" };
		Teren t2(numeTeren1, 5, numarObstacole1, 3, numeSportivi);
		Teren t3(t2);
		t3++;
		t3 += "Vlad";
		Teren t4;

		//ProdusGolf

		char numeProdus1[20];
		strcpy(numeProdus1, "masinuta de golf");
		ProdusGolf p1(numeProdus1);
		char numeProdus2[20];
		strcpy(numeProdus2, "minge de golf");
		float vanzari[3] = { 230,400,150 };
		float dimensiuni[3] = { 1,2,3 };
		float pret[3] = { 5.5,10,14.5 };
		ProdusGolf p2(numeProdus2, 3, dimensiuni, pret, vanzari);
		ProdusGolf p3(p2);
		char numeProdus3[20];
		strcpy(numeProdus3, "crosa de golf");
		float vanzari2[3] = { 500,450,700 };
		float dimensiuni2[4] = { 4,6,8,12 };
		float pret2[4] = { 52.6, 66.3, 80, 99.9 };
		ProdusGolf p4(numeProdus3, 4, dimensiuni2, pret2, vanzari2);
		ProdusGolf p5;
		char numeNou[20] = "Masina de golf";
		p1.setNumeProdus(numeNou);

		//Jucaor

		Jucator j1;
		char numeJucator1[30];
		strcpy(numeJucator1, "John Alexander");
		int mediePunctaj1[5] = { 3,5,2,0,0 };
		int locuri[4] = { 14,16,9,11 };
		Jucator j2(numeJucator1, 21, mediePunctaj1, 4, locuri);
		Jucator j3(j2);
		j1 = j2;
		Jucator j4;
		j4++;
		j4 += 4;


		//Campionat

		char numeCampionat1[20];
		strcpy(numeCampionat1, "Cupa amatorilor");
		Campionat c1(numeCampionat1);
		Teren terenuri1[2] = { t1,t2 };
		Jucator jucatori1[2] = { j1,j2 };
		int premii[3] = { 20000,10000,5000 };
		char numeCampionat2[20];
		strcpy(numeCampionat2, "Cupa mare");
		Campionat c2(numeCampionat2, 2, terenuri1, 2, jucatori1, premii);
		Campionat c3(c2);
		c3 += 200;
		char numeCampionat3[20];
		strcpy(numeCampionat3, "Cupa Intermediara");
		Campionat c4(numeCampionat3);
		c1.addParticipant(j3);

		//GolfClub

		GolfClub g1;
		char numeClub1[20];
		strcpy(numeClub1, "Golfers");
		Teren terenuri2[3] = { t1,t2,t3 };
		Jucator jucatori2[2] = { j2,j4 };
		Campionat campionate1[2] = { c2,c3 };
		ProdusGolf produse1[2] = { p1,p2 };
		int preturi[2] = { 60,550 };
		GolfClub g2(numeClub1, preturi, 2, jucatori2, 3, terenuri2, 2, campionate1, 2, produse1);
		GolfClub g3(g2);
		g3 = g2;
		cout << g1;
		cout << g2;
		g1++;
		if (g1 > g2)
			cout << endl << "g1>g2";
		else
			cout << endl << "g1<g2";

		if (!g1)
			cout << "clubul g1 nu are membri";

		cout << "\n\nprimul teren din clubul de golf este: " << (Teren)g2;
		//cin >> g1;
		//cout << g1;
		break;
	}
	case 6: {

		//Teren

		Teren t1;
		char numeTeren1[20];
		strcpy(numeTeren1, "Valea regilor");
		int numarObstacole1[3] = { 1,0,3 };
		string numeSportivi[3] = { "Tom Ford","Alexander","Mathew" };
		Teren t2(numeTeren1, 5, numarObstacole1, 3, numeSportivi);
		Teren t3(t2);
		t3++;
		t3 += "Vlad";
		Teren t4;

		//ProdusGolf

		char numeProdus1[20];
		strcpy(numeProdus1, "masinuta de golf");
		ProdusGolf p1(numeProdus1);
		char numeProdus2[20];
		strcpy(numeProdus2, "minge de golf");
		float vanzari[3] = { 230,400,150 };
		float dimensiuni[3] = { 1,2,3 };
		float pret[3] = { 5.5,10,14.5 };
		ProdusGolf p2(numeProdus2, 3, dimensiuni, pret, vanzari);
		ProdusGolf p3(p2);
		char numeProdus3[20];
		strcpy(numeProdus3, "crosa de golf");
		float vanzari2[3] = { 500,450,700 };
		float dimensiuni2[4] = { 4,6,8,12 };
		float pret2[4] = { 52.6, 66.3, 80, 99.9 };
		ProdusGolf p4(numeProdus3, 4, dimensiuni2, pret2, vanzari2);
		ProdusGolf p5;
		char numeNou[20] = "Masina de golf";
		p1.setNumeProdus(numeNou);

		//Jucaor

		Jucator j1;
		char numeJucator1[30];
		strcpy(numeJucator1, "John Alexander");
		int mediePunctaj1[5] = { 3,5,2,0,0 };
		int locuri[4] = { 14,16,9,11 };
		Jucator j2(numeJucator1, 21, mediePunctaj1, 4, locuri);
		Jucator j3(j2);
		j1 = j2;
		Jucator j4;
		j4++;
		j4 += 4;


		//Campionat

		char numeCampionat1[20];
		strcpy(numeCampionat1, "Cupa amatorilor");
		Campionat c1(numeCampionat1);
		Teren terenuri1[2] = { t1,t2 };
		Jucator jucatori1[2] = { j1,j2 };
		int premii[3] = { 20000,10000,5000 };
		char numeCampionat2[20];
		strcpy(numeCampionat2, "Cupa mare");
		Campionat c2(numeCampionat2, 2, terenuri1, 2, jucatori1, premii);
		Campionat c3(c2);
		c3 += 200;
		char numeCampionat3[20];
		strcpy(numeCampionat3, "Cupa Intermediara");
		Campionat c4(numeCampionat3);
		c1.addParticipant(j3);

		//GolfClub

		GolfClub g1;
		char numeClub1[20];
		strcpy(numeClub1, "Golfers");
		Teren terenuri2[3] = { t1,t2,t3 };
		Jucator jucatori2[2] = { j2,j4 };
		Campionat campionate1[2] = { c2,c3 };
		ProdusGolf produse1[2] = { p1,p2 };
		int preturi[2] = { 60,550 };
		GolfClub g2(numeClub1, preturi, 2, jucatori2, 3, terenuri2, 2, campionate1, 2, produse1);
		GolfClub g3(g2);

		//fstream fout("CampionateBin.txt", ios::out | ios::binary);
		//int i = 4;
		//fout.write((char*)&i, sizeof(int));
		//cout << i;
		//c1.writeToBinFile(fout);
		//c2.writeToBinFile(fout);
		//c3.writeToBinFile(fout);
		//c4.writeToBinFile(fout);
		//p5.writeToBinFile(fout);
		//fout.close();

		////cout << g1;
		//fstream fin("ProduseBin.txt", ios::in | ios::binary);
		//i=0;
		//fin.read((char*)&i, sizeof(int));
		//cout << i;
		//p5.readFromBinFile(fin);
		//cout << p5;
		//p5.readFromBinFile(fin);
		//cout << p5;
		//p5.readFromBinFile(fin);
		//cout << p5;
		//p5.readFromBinFile(fin);
		//cout << p5;
		//p5.readFromBinFile(fin);
		//cout << p5;
		cout << numarFisiere;
		Gestiune gst(numarFisiere,fisiere);
		//cout << fisiere[1];
		//cout << endl << sizeof(gst);
		break;
	}
	default: {
		cout << "Nu ai ales o clasa de intre 1-5.";
		break;
	}
	}
	return 0;
}
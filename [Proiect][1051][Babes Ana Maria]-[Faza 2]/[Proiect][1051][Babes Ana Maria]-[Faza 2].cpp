#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<list>
#include<set>
#include<map>
using namespace std;

class IFile {
	virtual void saveToFile(fstream& file) = 0;
	virtual void restoreFromFile(fstream& file) = 0;
};


class MateriePrima : IFile {
private:
	string nume = "-";
	float stoc = 0;
	string unitateMasura = " ";

public:
	MateriePrima() {}

	MateriePrima(string nume) {
		this->nume = nume;
	}

	MateriePrima(string nume, float stoc, string unitateMasura) {
		this->nume = nume;
		if (stoc > 0)
			this->stoc = stoc;
		this->unitateMasura = unitateMasura;
	}

	MateriePrima(const MateriePrima& m) {
		this->nume = m.nume;
		this->stoc = m.stoc;
		this->unitateMasura = m.unitateMasura;
	}

	MateriePrima& operator=(const MateriePrima& m) {
		if (this != &m) {
			this->nume = m.nume;
			this->stoc = m.stoc;
			this->unitateMasura = m.unitateMasura;
		}
		return *this;
	}

	void setNume(string nume) {
		if (nume.length() >= 2) {
			this->nume = nume;
		}
		else {
			cout << "\nEroare: Numele trebuie sa aiba cel putin 2 caractere!";
		}
	}

	string getNume() const {
		return this->nume;
	}

	void setStoc(float stoc) {
		if (stoc > 0) {
			this->stoc = stoc;
		}
		else {
			cout << "\nValoarea stocului trebuie sa fie pozitiva!";
		}
	}
	float getStoc() const {
		return this->stoc;
	}

	void setUnitateMasura(string unitateMasura) {
		if (unitateMasura.length() >= 1 && unitateMasura.length() <= 10) {
			this->unitateMasura = unitateMasura;
		}
		else {
			cout << "\nUnitatea de masura trebuie sa aiba intre 1 si 10 caractere!";
		}
	}

	string getUnitateMasura() const {
		return this->unitateMasura;
	}

	void updateStoc(float cantitate) {
		if (stoc - cantitate >= 0) {
			stoc -= cantitate;
		}
		else {
			cout << "\nStoc insuficient pentru materia prima!";
		}
	}

	void afisare() {
		cout << "\n----------------------------";
		cout << "\nNumele materiei prime: " << this->nume;
		cout << "\nStoc disponibil: " << this->stoc << " " << this->unitateMasura;
		cout << "\n----------------------------";
	}


	~MateriePrima() {}

	friend ostream& operator <<(ostream& out, const MateriePrima& m) {
		out << "\n----------------------------";
		out << "\nNumele materiei prime: " << m.nume;
		out << "\nStoc disponibil: " << m.stoc << " " << m.unitateMasura;
		return out;
	}

	friend ofstream& operator <<(ofstream& out, const MateriePrima& m) {
		out << "\n----------------------------";
		out << "\nNumele materiei prime: " << m.nume;
		out << "\nStoc disponibil: " << m.stoc << " " << m.unitateMasura;
		return out;
	}

	friend istream& operator>>(istream& in, MateriePrima& m) {
		//cout << "\nIntroduceti numele materiei prime: ";
		in >> m.nume;
		//cout << "\nIntroduceti stocul: ";
		in >> m.stoc;
		//cout << "\nIntroduceti unitatea de masura: ";
		in >> m.unitateMasura;
		return in;
	}

	friend ifstream& operator>>(ifstream& in, MateriePrima& m) {
		in >> m.nume;
		in >> m.stoc;
		in >> m.unitateMasura;
		return in;
	}

	void saveToFile(fstream& file) {
		int lgNume = this->nume.length() + 1;
		file.write((char*)&lgNume, sizeof(int));
		file.write(this->nume.data(), lgNume);

		file.write((char*)&this->stoc, sizeof(float));

		int lgUnitMas = this->unitateMasura.length() + 1;
		file.write((char*)&lgUnitMas, sizeof(int));
		file.write(this->unitateMasura.data(), lgUnitMas);
	}

	void restoreFromFile(fstream& file) {
		int lgNume;
		file.read((char*)&lgNume, sizeof(int));
		char* bufferNume = new char[lgNume];
		file.read(bufferNume, lgNume);
		this->nume = bufferNume;
		delete[] bufferNume;

		file.read((char*)&this->stoc, sizeof(float));

		int lgUnitMas;
		file.read((char*)&lgUnitMas, sizeof(int));
		char* bufferUnitMas = new char[lgUnitMas];
		file.read(bufferUnitMas, lgUnitMas);
		this->unitateMasura = bufferUnitMas;
		delete[] bufferUnitMas;
	}

};

class Ingredient : IFile {
private:
	MateriePrima ingredient;
	float cantitate = 0;

public:
	Ingredient() {}

	Ingredient(MateriePrima& ingredient, float cantitate) {
		this->ingredient = ingredient;
		this->cantitate = cantitate;
	}

	Ingredient(const Ingredient& i) {
		this->ingredient = i.ingredient;
		this->cantitate = i.cantitate;
	}

	Ingredient& operator =(const Ingredient& i) {
		if (this != &i) {
			this->ingredient = i.ingredient;
			this->cantitate = i.cantitate;
		}
		return *this;
	}

	const MateriePrima& getIngredient() const {
		return this->ingredient;
	}

	void setCantitate(float cantitate) {
		if (cantitate > 0) {
			this->cantitate = cantitate;
		}
		else {
			cout << "\nValoarea cantitatii trebuie sa fie pozitiva!";
		}
	}

	float getCantitate() const {
		return this->cantitate;
	}

	void afisare() {
		cout << "\n----------------------------";
		cout << "\nNumele ingredientului: " << this->ingredient.getNume();
		cout << "\nCantitatea necesara: " << this->cantitate;
		cout << "\n----------------------------";
	}

	void dubleazaCantitate() {
		if (cantitate > 0) {
			cantitate *= 2;
		}
	}

	~Ingredient() {}

	friend ostream& operator <<(ostream& out, const Ingredient& i) {
		out << "\n----------------------------";
		out << "\nNumele ingredientlui: " << i.ingredient.getNume();
		out << "\nCantitatea necesara: " << i.cantitate << " " << i.ingredient.getUnitateMasura();
		return out;
	}

	friend ofstream& operator <<(ofstream& out, const Ingredient& i) {
		out << "\n----------------------------";
		out << "\nNumele ingredientlui: " << i.ingredient.getNume();
		out << "\nCantitatea necesara: " << i.cantitate << " " << i.ingredient.getUnitateMasura();
		return out;
	}

	friend istream& operator>>(istream& in, Ingredient& i) {
		in >> i.ingredient;
		cout << "\nIntroduceti cantitatea necesara: ";
		in >> i.cantitate;
		return in;
	}

	friend ifstream& operator>>(ifstream& in, Ingredient& i) {
		in >> i.ingredient;
		cout << "\nIntroduceti cantitatea necesara: ";
		in >> i.cantitate;
		return in;
	}

	void saveToFile(fstream& file) {
		ingredient.saveToFile(file);

		file.write((char*)&cantitate, sizeof(float));
	}

	void restoreFromFile(fstream& file) {
		ingredient.restoreFromFile(file);

		file.read((char*)&cantitate, sizeof(float));
	}
};

class Preparat  {
private:
	string denumire = "-";
	int nrIngrediente = 0;
	Ingredient* listaIngrediente = nullptr;
	float pret = 0;

public:

	Preparat() {}

	Preparat(string denumire) {
		this->denumire = denumire;
	}

	Preparat(string denumire, float pret) {
		this->denumire = denumire;
		if (pret > 0) {
			this->pret = pret;
		}
	}

	Preparat(string denumire, int nrIngrediente, Ingredient* listaIngrediente, float pret) {
		this->denumire = denumire;
		if (nrIngrediente > 0 && listaIngrediente != nullptr) {
			this->nrIngrediente = nrIngrediente;
			this->listaIngrediente = new Ingredient[this->nrIngrediente];
			for (int i = 0;i < nrIngrediente;i++) {
				this->listaIngrediente[i] = listaIngrediente[i];
			}
		}
		if (pret > 0) {
			this->pret = pret;
		}
	}


	Preparat(const Preparat& p) {
		delete[]this->listaIngrediente;
		this->listaIngrediente = nullptr;
		this->denumire = p.denumire;
		if (p.nrIngrediente > 0 && p.listaIngrediente != nullptr) {
			this->nrIngrediente = p.nrIngrediente;
			this->listaIngrediente = new Ingredient[this->nrIngrediente];
			for (int i = 0;i < nrIngrediente;i++) {
				this->listaIngrediente[i] = p.listaIngrediente[i];
			}
		}
		this->pret = p.pret;
	}

	Preparat& operator =(const Preparat& p) {
		if (this != &p) {
			delete[]this->listaIngrediente;
			this->listaIngrediente = nullptr;
			this->denumire = p.denumire;
			if (p.nrIngrediente > 0 && p.listaIngrediente != nullptr) {
				this->nrIngrediente = p.nrIngrediente;
				this->listaIngrediente = new Ingredient[this->nrIngrediente];
				for (int i = 0;i < nrIngrediente;i++) {
					this->listaIngrediente[i] = p.listaIngrediente[i];
				}
			}
			this->pret = p.pret;
		}
		return *this;
	}

	void setDenumire(string denumire) {
		if (denumire.length() >= 2) {
			this->denumire = denumire;
		}
		else {
			cout << "\nDenumirea trebuie sa aiba cel putin 2 caractere!";
		}
	}

	string getDenumire() const {
		return this->denumire;
	}

	void setNrIngrediente(int nrIngrediente) {
		if (nrIngrediente > 0) {
			this->nrIngrediente = nrIngrediente;
		}
		else
			cout << "\nNumarul trebuie sa fie pozitiv!";
	}

	int getNrIngrediente() const {
		return this->nrIngrediente;
	}

	void setListaIngrediente(const Ingredient* listaIngrediente, int nrIngrediente) {
		if (listaIngrediente != nullptr) {
			delete[]this->listaIngrediente;
			this->nrIngrediente = nrIngrediente;
			this->listaIngrediente = new Ingredient[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++) {
				this->listaIngrediente[i] = listaIngrediente[i];
			}
		}
		else
			cout << "\nLista de ingrediente invalida!";
	}

	const Ingredient* getListaIngrediente() const {
		return this->listaIngrediente;
	}

	void setPret(float pret) {
		if (pret > 0) {
			this->pret = pret;
		}
		else
			cout << "\nPretul trebuie sa fie pozitiv!";
	}

	float getPret()const {
		return this->pret;
	}

	void afisare() {
		cout << "\n----------------------------";
		cout << "\nDenumirea preparatului: " << this->denumire;
		cout << "\nNumarul ingredientelor necesare: " << this->nrIngrediente;
		cout << "\nIngredientele necesare: ";
		for (int i = 0; i < this->nrIngrediente; i++) {
			cout << this->listaIngrediente[i].getIngredient().getNume();
			if (i < this->nrIngrediente - 1) {
				cout << ", ";
			}
		}
		cout << "\nPretul preparatului: " << this->pret << " lei";
		cout << "\n----------------------------";
	}

	~Preparat() {
		delete[]this->listaIngrediente;
		this->listaIngrediente = nullptr;
	}

	friend ostream& operator <<(ostream& out, const Preparat& p) {
		out << "\n----------------------------";
		out << "\nDenumirea preparatului: " << p.denumire;
		out << "\nNumarul ingredientelor necesare: " << p.nrIngrediente;
		out << "\nIngredientele necesare: ";
		for (int i = 0; i < p.nrIngrediente; i++) {
			out << p.listaIngrediente[i].getIngredient().getNume();
			if (i < p.nrIngrediente - 1) {
				out << ", ";
			}
		}
		out << "\nPretul preparatului: " << p.pret << " lei";
		return out;
	}

	friend istream& operator>>(istream& in, Preparat& p) {
		delete[]p.listaIngrediente;
		p.listaIngrediente = nullptr;
		//cout << "Introduceti denumirea preparatului: ";
		in.ignore();
		getline(in, p.denumire);
		//cout << "Introduceti numarul ingredientelor necesare: ";
		in >> p.nrIngrediente;
		p.listaIngrediente = new Ingredient[p.nrIngrediente];
		//cout << "Introduceti ingredientele necesare: ";
		for (int i = 0; i < p.nrIngrediente; i++) {
			//cout << "\nIngredient " << i + 1 << ":";
			in >> p.listaIngrediente[i];
		}
		//cout << "Introduceti pretul preparatului: ";
		in >> p.pret;
		return in;
	}
};

class Meniu {
private:
	int nrPreparate = 0;
	Preparat* listaPreparate = nullptr;

public:
	Meniu() {}

	Meniu(int nrPreparate) {
		if (nrPreparate > 0) {
			this->nrPreparate = nrPreparate;
		}
	}

	Meniu(int nrPreparate, Preparat* listaPreparate) {
		if (nrPreparate > 0 && listaPreparate != nullptr) {
			this->nrPreparate = nrPreparate;
			this->listaPreparate = new Preparat[this->nrPreparate];
			for (int i = 0;i < nrPreparate;i++) {
				this->listaPreparate[i] = listaPreparate[i];
			}
		}
	}

	Meniu(const Meniu& menu) {
		delete[]this->listaPreparate;
		this->listaPreparate = nullptr;
		if (menu.nrPreparate > 0 && menu.listaPreparate != nullptr) {
			this->nrPreparate = menu.nrPreparate;
			this->listaPreparate = new Preparat[this->nrPreparate];
			for (int i = 0;i < nrPreparate;i++) {
				this->listaPreparate[i] = menu.listaPreparate[i];
			}
		}
	}

	Meniu& operator =(const Meniu& menu) {
		if (this != &menu) {
			delete[]this->listaPreparate;
			this->listaPreparate = nullptr;
			if (menu.nrPreparate > 0 && menu.listaPreparate != nullptr) {
				this->nrPreparate = menu.nrPreparate;
				this->listaPreparate = new Preparat[this->nrPreparate];
				for (int i = 0;i < nrPreparate;i++) {
					this->listaPreparate[i] = menu.listaPreparate[i];
				}
			}
		}
		return *this;
	}

	void setNrPreparate(int nrPreparate) {
		if (nrPreparate > 0) {
			this->nrPreparate = nrPreparate;
		}
	}

	int getNrPreparate() const {
		return this->nrPreparate;
	}

	void setListaPreparate(const Preparat* listaPreparate, int nrPreparate) {
		if (listaPreparate != nullptr) {
			delete[] this->listaPreparate;
			this->nrPreparate = nrPreparate;
			this->listaPreparate = new Preparat[this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++) {
				this->listaPreparate[i] = listaPreparate[i];
			}
		}
		else
			cout << "\nLista de preparate invalida!";
	}

	Preparat* getListaPreparate() {
		return this->listaPreparate;
	}

	void afisare() {
		cout << "\nNumarul preparatelor este: " << this->nrPreparate;
		cout << "\nPreparatele sunt: ";
		for (int i = 0;i < this->nrPreparate;i++) {
			cout << this->listaPreparate[i].getDenumire();
			if (i < this->nrPreparate - 1) {
				cout << ", ";
			}
		}
	}

	float PretTotalMeniu() const {
		float pretTotal = 0;
		for (int i = 0; i < nrPreparate; i++) {
			pretTotal = pretTotal+ listaPreparate[i].getPret();
		}
		return pretTotal;
	}

	Preparat* cautaPreparat(string& numePreparat) {
		Preparat* preparate = getListaPreparate();
		int ok = 0;
		for (int i = 0; i < nrPreparate; i++) {
			if (listaPreparate[i].getDenumire() == numePreparat) {
				ok = 1;
				//return &listaPreparate[i];
			}
		}
		if (ok == 0) {
			cout << "\nPreparatul " << numePreparat << " nu se afla in meniu.";
			return nullptr;
		}
		else
			cout << "\nPreparat gasit!";
	}

	Preparat getPreparat(string& nume) {
		for (int i = 0; i < nrPreparate; i++) {
			if (listaPreparate[i].getDenumire() == nume) {
				return listaPreparate[i];
			}
		}
		//return nullptr;
	}

	~Meniu() {
		delete[]this->listaPreparate;
		this->listaPreparate = nullptr;
	}

	friend ostream& operator <<(ostream& out, const Meniu& menu) {
		out << "\n--------------MENIU--------------";
		for (int i = 0;i < menu.nrPreparate;i++) {
			out << "\n" << menu.listaPreparate[i].getDenumire();
			out << "............" << menu.listaPreparate[i].getPret() << " lei";
		}
		out << "\n---------------------------------";
		return out;
	}

	friend istream& operator>>(istream& in, Meniu& menu) {
		delete[]menu.listaPreparate;
		menu.listaPreparate = nullptr;
		cout << "\nIntroduceti numarul preparatelor: ";
		in >> menu.nrPreparate;
		menu.listaPreparate = new Preparat[menu.nrPreparate];
		cout << "Introduceti preparatele: ";
		for (int i = 0; i < menu.nrPreparate; i++) {
			cout << "\nPreparat " << i + 1 << ":";
			in >> menu.listaPreparate[i];
		}
		return in;
	}
};

class Comanda {
private:
	int nrPreparateComandate = 0;
	Preparat* preparateComandate = nullptr;
	Meniu meniu;
	int* portiiComandate = nullptr;

public:
	Comanda() {}

	Comanda(Meniu meniu) :meniu(meniu) {}

	Comanda(int nrPreparateComandate) {
		if (nrPreparateComandate > 0) {
			this->nrPreparateComandate = nrPreparateComandate;
		}
	}

	Comanda(int nrPreparateComandate, Preparat* preparateComandate, int* portiiComandate) {
		if (nrPreparateComandate > 0 && preparateComandate != nullptr) {
			this->nrPreparateComandate = nrPreparateComandate;
			this->preparateComandate = new Preparat[this->nrPreparateComandate];
			this->portiiComandate = new int[this->nrPreparateComandate];
			for (int i = 0;i < nrPreparateComandate;i++) {
				this->preparateComandate[i] = preparateComandate[i];
				this->portiiComandate[i] = portiiComandate[i];
			}
		}
	}

	Comanda(int nrPreparateComandate, Preparat* preparateComandate, const Meniu meniu, int* portiiComandate) :meniu(meniu) {
		if (nrPreparateComandate > 0 && preparateComandate != nullptr) {
			this->nrPreparateComandate = nrPreparateComandate;
			this->preparateComandate = new Preparat[this->nrPreparateComandate];
			this->portiiComandate = new int[this->nrPreparateComandate];
			for (int i = 0;i < nrPreparateComandate;i++) {
				this->preparateComandate[i] = preparateComandate[i];
				this->portiiComandate[i] = portiiComandate[i];
			}
		}
	}

	Comanda(const Comanda& c) {
		delete[]this->preparateComandate;
		this->preparateComandate = nullptr;
		delete[]this->portiiComandate;
		this->portiiComandate = nullptr;
		if (c.nrPreparateComandate > 0 && c.preparateComandate != nullptr) {
			this->nrPreparateComandate = c.nrPreparateComandate;
			this->preparateComandate = new Preparat[this->nrPreparateComandate];
			this->portiiComandate = new int[this->nrPreparateComandate];
			for (int i = 0;i < nrPreparateComandate;i++) {
				this->preparateComandate[i] = c.preparateComandate[i];
				this->portiiComandate[i] = c.portiiComandate[i];
			}
		}
	}

	Comanda& operator =(const Comanda& c) {
		if (this != &c) {
			delete[]this->preparateComandate;
			this->preparateComandate = nullptr;
			delete[]this->portiiComandate;
			this->portiiComandate = nullptr;
			if (c.nrPreparateComandate > 0 && c.preparateComandate != nullptr) {
				this->nrPreparateComandate = c.nrPreparateComandate;
				this->preparateComandate = new Preparat[this->nrPreparateComandate];
				this->portiiComandate = new int[this->nrPreparateComandate];
				for (int i = 0;i < nrPreparateComandate;i++) {
					this->preparateComandate[i] = c.preparateComandate[i];
					this->portiiComandate[i] = c.portiiComandate[i];
				}
			}
		}
		return *this;
	}

	void setNrPreparateCom(int nrPreparateComandate) {
		if (nrPreparateComandate > 0) {
			this->nrPreparateComandate = nrPreparateComandate;
		}
	}

	int getNrPreparateCom() const {
		return this->nrPreparateComandate;
	}

	void setPreparateCom(const Preparat* preparateComandate, int nrPreparateComandate) {
		if (preparateComandate != nullptr) {
			delete[] this->preparateComandate;
			this->nrPreparateComandate = nrPreparateComandate;
			this->preparateComandate = new Preparat[this->nrPreparateComandate];
			for (int i = 0; i < this->nrPreparateComandate; i++) {
				this->preparateComandate[i] = preparateComandate[i];
			}
		}
		else
			cout << "\nLista de preparate comandate invalida!";
	}

	Preparat* getPreparateCom() const {
		return this->preparateComandate;
	}

	int* getPortiiComandate() const {
		return this->portiiComandate;
	}

	float PretTotalComanda() const {
		float pretTotal = 0;
		for (int i = 0; i < nrPreparateComandate; ++i) {
			pretTotal = pretTotal + preparateComandate[i].getPret()*portiiComandate[i];
		}
		return pretTotal;
	}

	void afiseazaComanda() const {
		cout << "\nComanda plasata:\n";
		for (int i = 0; i < nrPreparateComandate; ++i) {
			cout << preparateComandate[i].getDenumire() << "............." << preparateComandate[i].getPret() << " lei" "\n";
		}
		cout << "\nTotal de plata: " << PretTotalComanda() << " lei\n";
	}

	void adaugaPreparat(const Preparat& preparat, int portii) {
		if (verificaStoc(preparat, portii)) {
			nrPreparateComandate++;
			Preparat* tempPreparate = new Preparat[nrPreparateComandate];
			int* tempPortii = new int[nrPreparateComandate];

			for (int i = 0; i < nrPreparateComandate - 1; ++i) {
				tempPreparate[i] = preparateComandate[i];
				tempPortii[i] = portiiComandate[i];
			}

			tempPreparate[nrPreparateComandate - 1] = preparat;
			tempPortii[nrPreparateComandate - 1] = portii;

			delete[] preparateComandate;
			delete[] portiiComandate;

			preparateComandate = tempPreparate;
			portiiComandate = tempPortii;

			cout << "Preparatul a fost adaugat in comanda.\n";
		}
		else {
			cout << "Nu exista suficient stoc pentru preparatul selectat.\n";
		}
	}

	bool verificaStoc(const Preparat& preparat, int portii) const {
		const Ingredient* listaIngrediente = preparat.getListaIngrediente();
		bool stocSuficient = true;

		for (int i = 0; i < preparat.getNrIngrediente(); ++i) {
			const MateriePrima& ingredient = listaIngrediente[i].getIngredient();
			float cantitateNecesara = listaIngrediente[i].getCantitate() * portii;

			if (ingredient.getStoc() - cantitateNecesara < 0) {
				cout << "Stoc insuficient pentru " << ingredient.getNume() << ". Comanda nu poate fi procesata.\n";
				return false;
			}
		}


		for (int i = 0; i < preparat.getNrIngrediente(); ++i) {
			MateriePrima ingredient = listaIngrediente[i].getIngredient();
			float cantitateNecesara = listaIngrediente[i].getCantitate() * portii;
			ingredient.updateStoc(cantitateNecesara);
		}

		return true;
	}

	void salveazaComanda() {
		ofstream fisierComenzi("comenzi.txt", ios::app);

		if (fisierComenzi.is_open()) {
			fisierComenzi << *this;
			fisierComenzi.close();
			cout << "Comanda a fost salvata in fisierul comenzi.txt.\n";
		}
		else {
			cout << "Eroare la deschiderea fisierului comenzi.txt.\n";
		}
	}

	friend ostream& operator<<(ostream& out, const Comanda& c) {
		out << "\n--------------COMANDA--------------";
		for (int i = 0; i < c.nrPreparateComandate; i++) {
			out << "\n" << c.preparateComandate[i].getDenumire();
			out << "............" << c.preparateComandate[i].getPret() << " lei";
		}
		out << "\n-----------------------------------";
		out << "\nTotal de plata: " << c.PretTotalComanda() << " lei\n";
		out << "\n-----------------------------------";
		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Comanda& c) {

		for (int i = 0; i < c.nrPreparateComandate; i++) {
			out <<c.nrPreparateComandate << " " << c.preparateComandate[i].getDenumire() << " " << c.portiiComandate[i] << " " << c.preparateComandate[i].getPret() << " ";
		}

		out << c.PretTotalComanda() << endl;

		return out;
	}

	friend istream& operator>>(istream& in, Comanda& c) {
		cout << "\nIntroduceti numarul de preparate dorite: ";
		int nrPreparate;
		in >> nrPreparate;
		in.ignore();

		Preparat* preparate = new Preparat[nrPreparate];
		int* portii = new int[nrPreparate];

		for (int i = 0; i < nrPreparate; ++i) {
			cout << "\nIntroduceti numele preparatului " << i + 1 << ": ";
			string denumirePreparat;
			getline(in, denumirePreparat);

			if (!c.meniu.cautaPreparat(denumirePreparat)) {
				cout << "\nPreparatul " << denumirePreparat << " nu exista in meniu.\n";
				delete[] preparate;
				delete[] portii;
				return in;
			}

			Preparat preparat = c.meniu.getPreparat(denumirePreparat);

			cout << "\nIntroduceti numarul de portii dorite pentru " << denumirePreparat << ": ";
			in >> portii[i];
			in.ignore();

			c.adaugaPreparat(preparat, portii[i]);
		}
		c.salveazaComanda();

		delete[] preparate;
		delete[] portii;

		return in;
	}

	~Comanda() {
		delete[]this->preparateComandate;
		this->preparateComandate = nullptr;
	}
};


//SALVARE DATE IN FISIERE BINARE
void saveToBinFile(const string& txtFName, const string& binFName) {
	ifstream txtFile(txtFName);
	ofstream binFile(binFName, ios::out | ios::binary);

	if (!txtFile.is_open() || !binFile.is_open()) {
		cout << "Eroare la deschiderea fisierelor." << endl;
		return;
	}

	string line;
	while (getline(txtFile, line)) {
		binFile.write(line.c_str(), line.size());
		binFile.put('\n');
	}

	txtFile.close();
	binFile.close();
}

//RAPORT 1
void preparatePretMic(const vector<Preparat>& preparate, float limitaPret, const string& fisierRaport) {
	ofstream raport(fisierRaport);

	if (!raport.is_open()) {
		cout << "Eroare la deschiderea fisierului de raport: " << fisierRaport << endl;
		return;
	}
	cout << "--------------------------- Raport ---------------------------";
	cout << "\nPreparate cu pret mai mic de " << limitaPret << " lei:" << endl;
	raport << "--------------------------- Raport ---------------------------";
	raport << "\nPreparate cu pret mai mic de " << limitaPret << " lei:" << endl;

	for (const Preparat& preparat : preparate) {
		if (preparat.getPret() < limitaPret) {
			cout << preparat.getDenumire()<< " - " << preparat.getPret() << " lei" << endl;
			raport << preparat.getDenumire() << " - " << preparat.getPret() << " lei" << endl;
		}
	}

	raport.close();
}

//RAPORT 2
void stocMare(const vector<MateriePrima>& matPrime, float limitaStoc, const string& fisierRaport) {
	ofstream raport(fisierRaport);

	if (!raport.is_open()) {
		cout << "Eroare la deschiderea fisierului de raport: " << fisierRaport << endl;
		return;
	}
	cout << "--------------------------- Raport ---------------------------";
	cout << "\nMaterii prime cu stoc mai mare de " << limitaStoc  << endl;
	raport << "--------------------------- Raport ---------------------------";
	raport << "\nMaterii prime cu stoc mai mare de " << limitaStoc << endl;

	for (const MateriePrima& matPrima : matPrime) {
		if (matPrima.getStoc() > limitaStoc) {
			cout << matPrima.getNume() << " - " << matPrima.getStoc() << " " << matPrima.getUnitateMasura() << endl;
			raport << matPrima.getNume() << " - " << matPrima.getStoc() << " " << matPrima.getUnitateMasura() << endl;
		}
	}

	raport.close();
}

//RAPORT 3
void MPUnitMas(const vector<MateriePrima>& matPrime, const string& unitateMasura, const string& fisierRaport) {
	ofstream raport(fisierRaport);

	if (!raport.is_open()) {
		cout << "Eroare la deschiderea fisierului de raport." << endl;
		return;
	}

	cout << "--------------------------- Raport ---------------------------";
	cout << "\nMaterii prime cu unitatea de masura: " << unitateMasura << endl;
	raport << "--------------------------- Raport ---------------------------";
	raport << "\nMaterii prime cu unitatea de masura: " << unitateMasura << endl;

	for (const MateriePrima& matPrima : matPrime) {
		if (matPrima.getUnitateMasura() == unitateMasura) {
			cout << matPrima.getNume() << " - " << matPrima.getUnitateMasura() << endl;
			raport << matPrima.getNume() << " - " << matPrima.getUnitateMasura() << endl;
		}
	}

	raport.close();
}

//CITIRE DATE DIN FIS CSV ANGAJATI
struct Angajat {
	string nume;
	int varsta;
	string functie;
};

vector<Angajat> citesteAngDinCSV(const string& numeFisier) {
	vector<Angajat> angajati;
	ifstream file(numeFisier);

	if (!file.is_open()) {
		cout << "Eroare la deschiderea fisierului." << endl;
		return angajati;
	}

	string linie;
	while (getline(file, linie)) {
		istringstream linieStream(linie);
		string token;

		Angajat angajat;
		getline(linieStream, token, ',');
		angajat.nume = token;

		getline(linieStream, token, ',');
		angajat.varsta = stoi(token);

		getline(linieStream, token, ',');
		angajat.functie = token;

		angajati.push_back(angajat);
	}

	cout << "\n--------------- Angajati ---------------" << endl;
	file.close();
	return angajati;
}

//CITIRE DATE FIS CSV
vector<vector<string>> citesteCSV(const string& numeFisier, char delimitator) {
	vector<vector<string>> rezultat;

	ifstream fisier(numeFisier);
	if (!fisier.is_open()) {
		cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
		return rezultat;
	}

	string linie;
	while (getline(fisier, linie)) {
		vector<string> linieData;
		stringstream linieStream(linie);
		string valoare;

		while (getline(linieStream, valoare, delimitator)) {
			linieData.push_back(valoare);
		}

		rezultat.push_back(linieData);
	}

	fisier.close();

	return rezultat;
}



//RAPORT 4
struct PreparatStr {
	string numePreparat;
	int portiiComandate;
	float pretPreparat;
};

struct ComandaStr {
	int nrPreparateCom;
	vector<PreparatStr> preparate;
	float pretTotalComanda;
	
	//ComandaStr() : nrPreparateCom(0),numePreparat("-"), portiiComandate(0), pretPreparat(0.0f), pretTotalComanda(0.0f) {}
};//struct pt ca nu ex constr cu acesti param in clasa comanda

void RaportComenzi(const string& fisierComenzi) {
	vector<ComandaStr> comenzi;

	ifstream fisier(fisierComenzi);

	if (!fisier.is_open()) {
		cout << "Eroare la deschiderea fisierului: " << fisierComenzi << endl;
		return;
	}

	int contorComenzi = 1;

	while(!fisier.eof()) {
		ComandaStr comanda;

		int nrPrep;
		fisier >> nrPrep;
		comanda.nrPreparateCom = nrPrep;

		if (fisier.eof()) {
			break;
		}

		comanda.preparate.resize(nrPrep);

		for (int i = 0; i < nrPrep; ++i) {
			fisier >> comanda.preparate[i].numePreparat >> comanda.preparate[i].portiiComandate >> comanda.preparate[i].pretPreparat;
		}

		float pretTotal;
		fisier >> pretTotal; 
		comanda.pretTotalComanda = pretTotal;

		comenzi.push_back(comanda);
	}

	fisier.close();

	if (comenzi.empty()) {
		cout << "Nu exista comenzi in fisier.\n";
		return;
	}

	cout << "--------------------------- Raport Comenzi ---------------------------\n";

	for (const auto& comanda : comenzi) {
		cout << "Comanda " << contorComenzi << endl;
		for (const auto& preparat : comanda.preparate) {
			cout << "Denumire preparat: " << preparat.numePreparat << "\tPortii : " << preparat.portiiComandate
				<< "\tPret: " << preparat.pretPreparat << "\tPret total: " << comanda.pretTotalComanda << endl;
		}
		contorComenzi++;
	}

	cout << "-----------------------------------------------------------------------\n";

}

void CitesteComenziDinFisier(const string& fisierComenzi, vector<ComandaStr>& comenzi) {
	vector<ComandaStr> comenziCit;

	ifstream fisier(fisierComenzi);

	if (!fisier.is_open()) {
		cout << "Eroare la deschiderea fisierului: " << fisierComenzi << endl;
		return;
	}

	while (!fisier.eof()) {
		ComandaStr comanda;

		int nrPrep;
		fisier >> nrPrep;
		comanda.nrPreparateCom = nrPrep;

		if (fisier.eof()) {
			break;
		}

		for (int i = 0; i < nrPrep; ++i) {
			PreparatStr preparat;
			fisier >> preparat.numePreparat >> preparat.portiiComandate >> preparat.pretPreparat;
			comanda.preparate.push_back(preparat);
		}

		fisier >> comanda.pretTotalComanda;

		comenzi.push_back(comanda);
	}

	fisier.close();
}

//RAPORT 5 CU SET
void ComenziPesteSuma( float sumaMinima) {
	vector<ComandaStr> comenziCit;
	string fisierComenzi = "comenzi.txt";

	ifstream fisier(fisierComenzi);

	if (!fisier.is_open()) {
		cout << "Eroare la deschiderea fisierului: " << fisierComenzi << endl;
		return;
	}

	while (!fisier.eof()) {
		ComandaStr comanda;

		int nrPrep;
		fisier >> nrPrep;
		comanda.nrPreparateCom = nrPrep;

		if (fisier.eof()) {
			break;
		}

		for (int i = 0; i < nrPrep; ++i) {
			PreparatStr preparat;
			fisier >> preparat.numePreparat >> preparat.portiiComandate >> preparat.pretPreparat;
			comanda.preparate.push_back(preparat);
		}

		fisier >> comanda.pretTotalComanda;

		comenziCit.push_back(comanda);
	}

	fisier.close();
	set<string> comenziPesteSuma;

	for (const auto& comanda : comenziCit) {
		if (comanda.pretTotalComanda > sumaMinima) {
			comenziPesteSuma.insert("Comanda " + to_string(comanda.nrPreparateCom) + " - Suma: " + to_string(static_cast<int>(comanda.pretTotalComanda)));
		}
	}

	cout << "------------------------ Comenzi Peste Suma ------------------------\n";

	for (const auto& comanda : comenziPesteSuma) {
		cout << comanda  << endl;
	}

	cout << "-----------------------------------------------------------------------\n";
}

int main(int argc,char* argv[]) {

	//CITIRE FIS TXT

	string stocMaterieprima = argv[1];
	string preparateF = argv[2];

	//CITIRE SI CREARE OBJ-MAT PRIME
	vector<MateriePrima> materiiPrime;

	ifstream stoc(stocMaterieprima);

	if (stoc.is_open()) {
		MateriePrima mat;

		while (stoc >> mat) {
			materiiPrime.push_back(mat);
		}

		stoc.close();
	}

	//VECT DE OBJ-INGR
	vector<Ingredient> ingrediente;
	for (int i = 0; i < materiiPrime.size(); ++i) {
		ingrediente.push_back(Ingredient(materiiPrime[i], 1));
	}

	//CITIRE SI CREARE OBJ-PREP
	vector<Preparat> preparate;

	ifstream prep(preparateF);

	if (prep.is_open()) {
		string denumire;
		int nrIngrediente;
		float pret;

		while (prep >> denumire >> nrIngrediente) {

			vector<Ingredient> listaIngrediente;

			for (int i = 0; i < nrIngrediente; i++) {
				string numeMaterie;

				prep >> numeMaterie;

				for (int i = 0; i < ingrediente.size(); i++)
				{
					if (ingrediente[i].getIngredient().getNume() == numeMaterie)
					{
						listaIngrediente.push_back(ingrediente[i]);
						break;
					}
				}

			}

			Ingredient* listaAuxIng = new Ingredient[listaIngrediente.size()];

			for (int i = 0; i < listaIngrediente.size(); i++)
			{
				listaAuxIng[i] = listaIngrediente[i];
			}

			prep >> pret;

			preparate.push_back(Preparat(denumire, nrIngrediente, listaAuxIng, pret));
			delete[] listaAuxIng;
		}

		prep.close();
	}

	Preparat* listaPrep = new Preparat[preparate.size()];
	for (int i = 0;i < preparate.size();i++) {
		listaPrep[i] = preparate[i];
	}

	//VECT OBJ-MENU
	vector<Meniu> meniu;
	for (int i = 0; i < preparate.size(); ++i) {
		meniu.push_back(Meniu(preparate.size(), listaPrep));
	}

	//saveToBinFile("stocMateriePrima.txt", "stocMateriePrima.bin");

	//saveToBinFile("preparate.txt", "preparate.bin");


	//preparatePretMic(preparate, 20, "raport_preparate.txt");

	//stocMare(materiiPrime, 5, "raport_mat_prime.txt");

	//MPUnitMas(materiiPrime,"kg", "raport_unit_mas_mp.txt");

	//vector<Angajat> angajati = citesteAngDinCSV("angajati.csv");

	/*for (const auto& angajat : angajati) {
		cout << "Nume: " << angajat.nume << ", Varsta: " << angajat.varsta << ", Functie: " << angajat.functie << endl;
	}

	vector<vector<string>> date = citesteCSV("angajati.csv", ',');

	for (const auto& linie : date) {
		for (const auto& valoare : linie) {
			cout << valoare << "\t";
		}
		cout << endl;
	}*/

	MateriePrima materie("orez", 10, "kg");

	/*fstream file("materiePrima.bin", ios::out | ios::binary);
	materie.saveToFile(file);
	file.close();

	fstream file("materiePrima.bin", ios::in | ios::binary);
	MateriePrima materieCitita;
	materieCitita.restoreFromFile(file);
	file.close();

	cout << "Materie citita din fisier: " << materieCitita << endl;*/

	Ingredient ingr(materie, 2);
	//fstream file2("ingredient.bin", ios::out | ios::binary);
	//ingr.saveToFile(file2);
	//file2.close();

	//fstream file2("ingredient.bin", ios::in | ios::binary);
	//Ingredient ingrCitit;
	//ingrCitit.restoreFromFile(file2);

	//cout << "Ingredient citit din fisier: " << ingrCitit << endl;

	/*cout << meniu[0];

	Comanda c(meniu[0]);
	cin >> c;
	cout << c;

	for (int i = 0; i < preparate.size(); i++) {
		cout << preparate[i] << endl;
	}

	for (int i = 0; i < ingrediente.size(); ++i) {
		ingrediente[i].afisare();
	}

	for (int i = 0;i < materiiPrime.size();i++) {
		cout << materiiPrime[i] << endl;
	}*/

	//RaportComenzi("comenzi.txt");

	//vector<ComandaStr> comenziCitite;
	ComenziPesteSuma (50);

	//cin.get();
	delete[] listaPrep;
	return 0;
}

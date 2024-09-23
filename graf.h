#ifndef _GRAF_H_
#define _GRAF_H_

#include<iostream>
#include<fstream>
using namespace std;

struct Cvor {
	string rec="";
	int ind_prvog_suseda = 0;
	bool ima_suseda = false;
};

struct Grana {
	int id_suseda=0;
	double tezina_grane=0;
	Grana(int id = 0, double tez = 0) :id_suseda(id), tezina_grane(tez) {}
};



class Graf {
private:
	int br_cv=0;
	int br_grana=0;
	
	Grana *edges=nullptr;
	Cvor *indices=nullptr;

public:
	Graf(string ime_dat);
	Graf(){}
	~Graf() { brisanje(); }

	void dodajCvor(string rec);
	int obrisiCvor(string rec);

	int dodajGranu(string cv1, string cv2, double tez);
	int obrisiGranu(string cv1, string cv2);

	void ispis()const;
	void ispisRep()const;
	void brisanje();

	void k_najslicnijih(int k, string rec)const;

	void najkraci_put(string cv1, string cv2)const;

	int indeks_indices(string rec)const;
};

#endif
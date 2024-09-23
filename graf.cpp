#include"graf.h"
#include <iomanip> 

void Graf::brisanje()
{
	delete[] edges;
	delete[] indices;
	br_cv = 0;
	br_grana = 0;
	edges = nullptr;
	indices = nullptr;
}

void Graf::k_najslicnijih(int k, string rec) const
{

	int ind_indices = indeks_indices(rec);
	int indedges2;
	double knovi;
	double* nizmaks = new double[br_cv];
	double* niztek = new double[br_cv];
	//inicijalizovanje nulama
	for (int i = 0; i < br_cv; i++)
	{
		nizmaks[i] = 0;
		niztek[i] = 0;
	}
	//inicijalizovanje direktnih suseda za zadati cvor njihovim tezinama
	for (int i_edges = indices[ind_indices].ind_prvog_suseda; i_edges < indices[ind_indices + 1].ind_prvog_suseda; i_edges++)
	{
		nizmaks[edges[i_edges].id_suseda] = edges[i_edges].tezina_grane;
		niztek[edges[i_edges].id_suseda] = edges[i_edges].tezina_grane;
	}
	for (int i = 0; i < br_cv - 1; i++)
	{
		double* niz_sledeca = new double[br_cv];
		//inicijalizovanje nulama
		for (int i = 0; i < br_cv; i++)
		{
			niz_sledeca[i] = 0;
		}

		for (int j = 0; j < br_cv; j++) {
			if (niztek[j] != 0) {
				
				for (indedges2 = indices[j].ind_prvog_suseda; indedges2 < indices[j + 1].ind_prvog_suseda; indedges2++) {
					int ind_upisa = edges[indedges2].id_suseda;
					knovi = niztek[j] * edges[indedges2].tezina_grane;
					niz_sledeca[ind_upisa] = knovi;
					if (knovi > nizmaks[ind_upisa])
						nizmaks[ind_upisa] = knovi;
				}
				
			}
		}
		delete[] niztek;
		niztek = niz_sledeca;
	}
	nizmaks[ind_indices] = 0;

	for (int i = 0; i < k; i++) {
		int makspoz = 0;
		for (int j = 0; j < br_cv; j++)
			if (nizmaks[makspoz] < nizmaks[j])
				makspoz = j;
		if (nizmaks[makspoz] != 0) {
			cout << indices[makspoz].rec << endl;
			nizmaks[makspoz] = 0;
		}
	}

	delete[] nizmaks;
	delete[] niztek;

}

void Graf::najkraci_put(string cv1, string cv2) const
{
	int ind_indices, ind_dostiznog, ind_edges;
	if ((ind_indices = indeks_indices(cv1)) == -1 || (ind_dostiznog = indeks_indices(cv2))==-1)
		return; 
	double* d = new double[br_cv];
	double* w = new double[br_cv];
	int* t = new int[br_cv];
	int* S = new int[br_cv];
	int* V = new int[br_cv];
	//inicijalizacije potrebnih vektora
	for (int i = 0; i < br_cv; i++)
	{
		V[i] = 1;
		S[i] = 0;
		d[i] = 1000;
		t[i] = -1;
	}
	S[ind_indices] = 1;
	V[ind_indices] = 0;
	for (ind_edges = indices[ind_indices].ind_prvog_suseda; ind_edges < indices[ind_indices + 1].ind_prvog_suseda; ind_edges++)
	{
		d[edges[ind_edges].id_suseda] = edges[ind_edges].tezina_grane;
		t[edges[ind_edges].id_suseda] = ind_indices;
	}
	for (int k = 0; k < br_cv - 2; k++)
	{
		double min;
		int indeks;
		//pp uzimanje prvog iz V kao cvora sa min rastojanjem
		for (int i = 0; i < br_cv; i++)
		{
			if (V[i] != 0)
			{
				indeks = i;
				min = d[i];
				break;
			}
		}
		
		//nalazenje min
		for (int i = 0; i < br_cv; i++)
		{
			if (V[i] != 0)
			{
				if (d[i] < min)
				{
					min = d[i];
					indeks = i;
				}
			}
		}
		S[indeks] = 1;
		V[indeks] = 0;
		for (int i = 0; i < br_cv; i++)
		{
			w[i] = 1000;
		}
		for (ind_edges = indices[indeks].ind_prvog_suseda; ind_edges < indices[indeks + 1].ind_prvog_suseda; ind_edges++)
		{
			w[edges[ind_edges].id_suseda] = edges[ind_edges].tezina_grane;
		}

		for (int j = 0; j < br_cv; j++)
		{
			if (V[j] == 1)
			{
				
				if (d[indeks] + w[j] < d[j])
				{
					d[j] = d[indeks] + w[j];
					t[j] = indeks;
				}
			}
		}
	}

	
	if (d[ind_dostiznog] < 1000)
		cout << "Najkrace rastojanje od " << cv1 << " do " << cv2 << " : " << d[ind_dostiznog] << endl;
	else cout << "Cvor nije dostizan" << endl;

	//PATH
}

int Graf::indeks_indices(string rec) const
{
	int ind_indices;
	for (ind_indices = 0; ind_indices < br_cv; ind_indices++) {
		if (indices[ind_indices].rec == rec)
			return ind_indices;
	}
	cout << "Ne postoji cvor " <<rec<< endl;
	return -1;
}

Graf::Graf(string ime_dat)
{
	ifstream f;
	f.open(ime_dat, ios::in);

	if (f.is_open()) {
		string rec;
		f >> br_cv;
		f >> br_grana;

		indices = new Cvor[br_cv + 1];
		edges = new Grana[br_grana];

		for (int i = 0; i < br_cv; i++)
		{
			f >> rec;
			indices[i].rec = rec;

		}


		int ind_edges = 0, ind_cvora = 0, ind_suseda = 1;
		indices[ind_cvora].ind_prvog_suseda = ind_edges;
		for (; ind_edges < br_grana; ind_edges++) {
			f >> rec;
			string rec2;
			f >> rec2;
			double tezina;
			f >> tezina;



			while (true) {
				if (indices[ind_cvora].rec == rec) {
					break;
				}
				if (indices[++ind_cvora].rec != rec) {
					indices[ind_cvora].ind_prvog_suseda = ind_edges;
					continue;
				}

				//ind_suseda = 0;
				indices[ind_cvora].ind_prvog_suseda = ind_edges;
				break;
			}

			//postavljanje da ima suseda
			indices[ind_cvora].ima_suseda = true;

			ind_suseda = indeks_indices(rec2);
			edges[ind_edges] = Grana(ind_suseda, tezina);
		}
		for (++ind_cvora; ind_cvora <= br_cv; ind_cvora++)
			indices[ind_cvora].ind_prvog_suseda = ind_edges;
		f.close();
	}
	else
		cout << "Neuspesno otvaranje datoteke!" << endl;
	
}

void Graf::ispis() const
{
	cout << "Broj cvorova: " << br_cv << ", broj grana: " << br_grana << endl;
	cout << "Cvorovi:" << endl;
	for (int i = 0; i < br_cv; i++) {
		cout << indices[i].rec << " ";
	}
	cout << endl << "Grane:" << endl;
	int br = 0;
	for (int i_edges = 0, i_indices=0; i_edges < br_grana; i_edges++) {
		if (br < indices[i_indices + 1].ind_prvog_suseda - indices[i_indices].ind_prvog_suseda) {
			br++;
		}
		else{
			i_indices++;
			while(indices[i_indices].ima_suseda!=true)
				i_indices++;
			br = 1;
		}
		
		cout <<i_edges<<" "<< indices[i_indices].rec << " " << indices[edges[i_edges].id_suseda].rec << " " << edges[i_edges].tezina_grane << endl;
	}
}

void Graf::ispisRep() const
{
	cout << "Indices:" << endl;
	for (int i = 0; i < br_cv + 1; i++)
	{
		cout << i << " " << indices[i].rec << " " << indices[i].ind_prvog_suseda << "\t" << indices[i].ima_suseda << endl;

	}
	cout << endl<<"Edges:"<<endl;
	for (int i = 0; i < br_grana; i++)
	{
		cout << i << " " << edges[i].tezina_grane << " " << edges[i].id_suseda << " " << indices[edges[i].id_suseda].rec << endl;
	}
}

void Graf::dodajCvor(string rec)
{
	Cvor* novi = new Cvor[br_cv + 2];
	int i = 0;

	if (br_cv == 0)
	{
		novi[i].rec = rec;
	}
	else {
		for (; i < br_cv; i++) {
			novi[i] = indices[i];
		}
		novi[i].rec = rec;
		novi[i].ind_prvog_suseda = indices[i].ind_prvog_suseda;
		i++;
		novi[i].ind_prvog_suseda = novi[i - 1].ind_prvog_suseda;

		delete[] indices;
	}
	indices = novi;
	br_cv++;
	cout << "Cvor dodat" << endl;
}

int Graf::obrisiCvor(string rec)
{
	int ind_indices = 0;
	for (; indices[ind_indices].rec != rec && ind_indices < br_cv; ind_indices++);
	if (indices[ind_indices].rec != rec) {
		cout << "Ne postoji zadat cvor" << endl;
		return -1;
	}
	

	while (indices[ind_indices].ima_suseda) {
		int ind_edges = indices[ind_indices].ind_prvog_suseda;
		obrisiGranu(indices[ind_indices].rec, indices[edges[ind_edges].id_suseda].rec);
	}
	for (int ind_indices2 = 0; ind_indices2 < br_cv; ind_indices2++)
	{
		obrisiGranu(indices[ind_indices2].rec, rec);

	}

	br_cv--;
	int i;
	Cvor* nova = new Cvor[br_cv + 1];
	for (i = 0; i < ind_indices; i++) {
		nova[i] = indices[i];
	}
	for (; i < br_cv + 1; i++) {
		nova[i] = indices[i + 1];
	}

	for (int ind_edges = 0; ind_edges < br_grana; ind_edges++) {
		if (edges[ind_edges].id_suseda > ind_indices) {
			edges[ind_edges].id_suseda--;
		}
	}

	delete[] indices;
	indices = nova;
	
	return 0;
}

int Graf::dodajGranu(string cv1, string cv2, double tez)
{
	int ind_indices = indeks_indices(cv1);
	if (ind_indices == -1) return -1;
	

	int indicescv2 = indeks_indices(cv2);
	if (indicescv2 == -1)return -1;
	int ind_edges;
	for (ind_edges = indices[ind_indices].ind_prvog_suseda; ind_edges < indices[ind_indices].ind_prvog_suseda + indices[ind_indices + 1].ind_prvog_suseda - indices[ind_indices].ind_prvog_suseda; ind_edges++)
	{
		if (edges[ind_edges].id_suseda == indicescv2)
		{
			cout << "Grana vec postoji" << endl;
			return -1;
		}
	}
	//ubacuje se kao prvi sused u edges
	Grana* novi = new Grana[++br_grana];
	for (int i = 0; i < ind_edges; i++)//kopiranje do indeksa umetanja u edges
	{
		novi[i] = edges[i];
	}
	ind_edges = indices[ind_indices].ind_prvog_suseda;
	novi[ind_edges].id_suseda = indicescv2;
	novi[ind_edges].tezina_grane = tez;
	ind_edges++;
	for (; ind_edges < br_grana; ind_edges++)
	{
		novi[ind_edges] = edges[ind_edges - 1];
	}
	delete[] edges;
	edges = novi;

	if (!indices[ind_indices].ima_suseda)
		indices[ind_indices].ima_suseda = true;
	ind_indices++;
	for (; ind_indices < br_cv + 1; ind_indices++) {
		indices[ind_indices].ind_prvog_suseda++;
	}
	cout << "Grana dodata" << endl;
	return 0;
}

int Graf::obrisiGranu(string cv1, string cv2)
{
	int ind_indices = 0;
	while (indices[ind_indices].rec != cv1 && ind_indices<br_cv)
		ind_indices++;
	if (indices[ind_indices].rec!=cv1) {
		/*cout << "Ne postoji prvi cvor grane" << endl;*/
		return -1;
	}

		int br_suseda = indices[ind_indices + 1].ind_prvog_suseda - indices[ind_indices].ind_prvog_suseda, k = 0;

		int ind_edges = indices[ind_indices].ind_prvog_suseda;
		for (; ind_edges < indices[ind_indices].ind_prvog_suseda + br_suseda; ind_edges++)
		{
			if (indices[edges[ind_edges].id_suseda].rec == cv2)
			{
				if (br_suseda == 1)
					indices[ind_indices].ima_suseda = false;
				//uredjivanje edges
				Grana* novi = new Grana[br_grana - 1];
				int i = 0;
				for (; i < ind_edges; i++)
					novi[i] = edges[i];

				for (; i < br_grana - 1; i++)
					novi[i] = edges[i + 1];

				delete[] edges;
				edges = novi;

				//uredjivanje indices
				ind_indices++;
				for (; ind_indices < br_cv + 1; ind_indices++)
					indices[ind_indices].ind_prvog_suseda--;

				br_grana--;
				return 0;
			}
				
		}

		/*cout << "Ne postoji grana!" << endl;*/
		return -1;
		
}

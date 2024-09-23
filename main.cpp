#include"graf.h"


int main() {
	
	string ime, ime2;
	cout << "Unesite ime dat: ";
	cin >> ime;
	Graf g(ime);
	char c;
	cout << "Unesite:1 ispis, 2 brisanje grafa, 3 dodavanje cvora, 4 brisanje cvora, 5 dodavanje grane,\n 6 brisanje grane, 7 k_najslicnijih, 8 najkraci put,  0 kraj" << endl;
	while (c = getchar())
	{
		switch (c)
		{
		case '0': return 0;
		case '1':
			g.ispis();
			break;
		case '2':
			g.brisanje();
			break;
		case '3':
			cout << "Unesite ime cvora za dodavanje: ";
			cin >> ime;
			g.dodajCvor(ime);
			break;
		case '4':
			cout << "Unesite ime cvora za brisanje: ";
			cin >> ime;
			g.obrisiCvor(ime);
			break;
		case '5':
			cout << "Unesite cvorove za dodavanje grane i tezinu ";
			cin >> ime;
			cin >> ime2;
			double tez;
			cin >> tez;
			g.dodajGranu(ime, ime2, tez);
			break;
		case '6':
			cout << "Unesite cvorove za brisanje grane ";
			cin >> ime;
			cin >> ime2;
			if (g.obrisiGranu(ime, ime2) == -1)
				cout << "Ne postoji zadata grana" << endl;
			break;
		case '7':
			cout << "Unesite br najslicnijih koji se trazi i cvor za koje se traze najslicnije ";
			int k;
			cin >> k;
			cin >> ime;
			g.k_najslicnijih(k, ime);
			break;
		case '8':
			cout << "Unesite imena cvorova izmedju kojih se trazi najkrace rastojanje ";
			cin >> ime >> ime2;
			g.najkraci_put(ime, ime2);
			break;
		}

	}

}
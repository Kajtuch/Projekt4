#include <iostream>
#include <SFML/Graphics.hpp> 
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>

////////////////////////////////////////////////
//Tutaj definiujemy sobie kolory			  //
#define	BIALY sf::Color(255,255,255)		  //
#define	CZARNY sf::Color(0,0,0)				  //
#define CZERWONY sf::Color(255,0,0)			  //
#define ZIELONY sf::Color(0,255,0)			  //
#define NIEBIESKI sf::Color(0,0,255)		  //
#define SZARY sf::Color(150,150,150)		  //
#define CIEMNOSZARY sf::Color(220,220,220)	  //
//											  //
////////////////////////////////////////////////

const int SZEROKOSC_OKNA = 1500;
const int WYSOKOSC_OKNA = 750;
const int PREDKOSC = 1;

using namespace std;

void wyswietlanie_ludkow(sf::RenderWindow* okno, sf::Sprite* patyczak1, sf::Sprite* patyczak2, sf::Sprite* patyczak3, sf::Sprite* patyczak4, int ktory, int y)
{
	if (ktory == 1)
	{
		(*patyczak1).setPosition(600, y);
		(*okno).draw(*patyczak1);
	}
	else if (ktory == 2)
	{
		(*patyczak2).setPosition(600, y);
		(*okno).draw(*patyczak2);
	}
	else if (ktory == 3)
	{
		(*patyczak3).setPosition(600, y);
		(*okno).draw(*patyczak3);
	}
	else if (ktory == 4)
	{
		(*patyczak4).setPosition(600, y);
		(*okno).draw(*patyczak4);
	}
}

																					//deklaruje tutaj funkcje buduj¹ce winde i piêtra dla przejrzystoœci zwracaj¹ obiekt bêd¹cy jakimœ prostok¹tem który mo¿na potem namalowaæ
	sf::RectangleShape lewa_sciana1();												//to funkcje zwracaj¹ce jakiœ skonstruowany prostok¹t
	sf::RectangleShape lewa_sciana2();
	sf::RectangleShape prawa_sciana();
	sf::RectangleShape sufit();
	sf::RectangleShape parter();
	sf::RectangleShape pietro1();
	sf::RectangleShape pietro2();

	int ktory_przycisk(int x, int y);											//funkcja sprawdza na którym przycisku mamy aktualnie myszkê

	void narysuj_winde(sf::RenderWindow* okno) {
		(*okno).draw(lewa_sciana1());												//draw rysuje jakiœ obiekt
		(*okno).draw(lewa_sciana2());
		(*okno).draw(prawa_sciana());
		(*okno).draw(sufit());
		(*okno).draw(parter());
		(*okno).draw(pietro1());
		(*okno).draw(pietro2());
		
	}
	void narysuj_interfejs(sf::RenderWindow* okno, int wybrany, vector<int> pasazerowie);

	void w_dol(int* wysokosc, sf::Clock zegar);
	void w_gore(int* wysokosc, sf::Clock zegar);
	void spisywanie(int* spis, string kierunek, vector<int>* poziomy);
	
	int pozycja(int wysokosc);													//funkcja zwraca pietro na ktorym jest teraz podnosnik jesli jest miedzy pietrami zwraca "-1" gdy podnosnik jest pomiedzy 0 a 1 i "-2" gdy jest pomiedzy 1 i 2


	int main() {
		bool ludzik_zero = false;
		sf::Clock stoper;
		bool czy_zegar_zaczal_odmierzac = false;
		bool czy_w_kabinie_sa_ludzie = false;
		int spis_ludzi_na_pietrach[3];												//tablica wype³niona intami oznaczaj¹cymi iloœæ ludzi jad¹cych w tym kierunku co winda na danych pietrach
		bool czy_sa_ludzie_na_trasie = false;														//zawiera informacje o tym czy wykryto jakis ludzi na trasie windy
		//int polecenie = 0;																//zmienna zawiera polecenia jakie aktualnie wykonuje winda polecenia to: 0="stop",1="zaladuj",2="wypakuj",3="jedz" 
		string kierunek = "gora";
		//int aktualna_pozycja = 0;															//zmienna posiada informacje o tym na ktorym pietrze znajduje sie winda
		sf::Clock zegar;																//zmienna typu zegar XD
		int wysokosc = 0;																	//wysokosc na jakiej znajduje siê podnosnik wzgledem spodu szybu windy
		int wybrany = -1;
		bool czy_klikniety = false;
		sf::RenderWindow okno;															//tworzym nasze okno jako obiekt klasy Window z zakresu nazw sf
		sf::RectangleShape podnosnik;
		podnosnik.setSize(sf::Vector2f(100, 10));
		podnosnik.setFillColor(CZERWONY);
		okno.create(sf::VideoMode(SZEROKOSC_OKNA, WYSOKOSC_OKNA, 32), "winda");			// tutaj powstaje nasze okno pierwszy argument funkcji to wymiary okna np. "1000, 500," 32 oznacza zakres kolorów. drugi argument to nazwa okna

		sf::Texture ludek1;                                                                //textura ludka
		ludek1.loadFromFile("ludki/1ludek.png");
		sf::Sprite patyczak1;                                                            //sprite ludka
		patyczak1.setTexture(ludek1);
		patyczak1.setScale(sf::Vector2f(0.1, 0.15));

		sf::Texture ludek2;                                                                //textura ludka
		ludek2.loadFromFile("ludki/2ludek.png");
		sf::Sprite patyczak2;                                                            //sprite ludka
		patyczak2.setTexture(ludek2);
		patyczak2.setScale(sf::Vector2f(0.1, 0.15));

		sf::Texture ludek3;                                                                //textura ludka
		ludek3.loadFromFile("ludki/3ludek.png");
		sf::Sprite patyczak3;                                                            //sprite ludka
		patyczak3.setTexture(ludek3);
		patyczak3.setScale(sf::Vector2f(0.1, 0.15));

		sf::Texture ludek4;                                                                //textura ludka
		ludek4.loadFromFile("ludki/4ludek.png");
		sf::Sprite patyczak4;                                                            //sprite ludka
		patyczak4.setTexture(ludek4);
		patyczak4.setScale(sf::Vector2f(0.1, 0.15));

		


		vector<int> poziom[3];															//tablica 3 elementowa sk³adajaca siê z vektorów typu int zawiera informacje o pasa¿erach na ka¿dym pietrze
		vector<int> pasazerowie;																//ta tablica zawiera informacje o tym ile i ggdzie jad¹cych pasarzerów znajduje sie na podnoœniku

	sf::Event input;																//deklaruje zmienn¹ event ktora zawieraæ bêdzie informacje o tym co my robimy (np ruszamy myszk¹)
	
	while (okno.isOpen()) {															// pêtla wykonuje siê dopóki okno jest otwarte
		bool czy_stop = true;
		//sf::Time deltaczasu = zegar.restart();
		okno.clear(BIALY);															//metoda clear wype³nia ca³e okno kolorem, kolor jest jak¹œ klas¹
		okno.pollEvent(input);														//wywo³anie tej funkcji sprawia ¿e zmienna input wype³niona jest informacjami o eventach
		sf::Vector2i pozycja_myszki = sf::Mouse::getPosition(okno);
		if (input.type == sf::Event::Closed) {										//ten if zamyka okno je¿eli klikniesz X w prawym górnym rogu okna
			okno.close();
			break;
		}
		/////////////////////////////////////////////////////////////////////////////obs³uga przycisków
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			zegar.restart();
			if (!czy_klikniety) {
				switch (ktory_przycisk(pozycja_myszki.x, pozycja_myszki.y)) {
				case 0: {
					wybrany = 0;
					break;
				}
				case 1: {
					wybrany = 1;
					break;
				}
				case 2: {
					wybrany = 2;
					break;
				}
				case 3: {
					if (wybrany == -1 || wybrany == 0 ) {
						wybrany = -1;
						break;
					}
					else {
						poziom[wybrany].push_back(0);
					}
					break;
				}
				case 4: {
					if (wybrany == -1 || wybrany == 1 ) {
						wybrany = -1;
						break;
					}
					else {
						poziom[wybrany].push_back(1);
					}
					break;
				}
				case 5: {
					if (wybrany == -1 || wybrany == 2 ) {
						wybrany = -1;
						break;
					}
					else {
						poziom[wybrany].push_back(2);
					}
					break;
				}
				default:
				{
					break;
				}
				}
			}
			czy_klikniety = true;
		}
		else {
			czy_klikniety = false;
		}
		///tutaj dane w konsolce
		if (czy_klikniety) {
			system("cls");
			cout << "\n poziom 2: ";
			for (int i = 0; i < poziom[2].size(); i++) {
				cout << poziom[2][i] << " ";
			}
			cout << "\n poziom 1: ";
			for (int i = 0; i < poziom[1].size(); i++) {
				cout << poziom[1][i] << " ";
			}
			cout << "\n poziom 0: ";
			for (int i = 0; i < poziom[0].size(); i++) {
				cout << poziom[0][i] << " ";
			}
			cout << "\n winda:";
			for (int i = 0; i < pasazerowie.size(); i++) {
				cout << pasazerowie[i] << " ";
			}
			cout <<endl<<"pozycja: "<< pozycja(wysokosc) << endl;
			cout << "wysokosc: " << wysokosc<<endl<<"kierunek: "<<kierunek<<endl;
		}
		///
		////////////////////////////////////////////////////////////////////////////dzia³anie windy
		spisywanie(spis_ludzi_na_pietrach, kierunek, poziom);
		
		for (int i = 0; i < 3; i++) {
			if (spis_ludzi_na_pietrach[i]!=0) {
				czy_stop = false;
			}
		}
		if (czy_stop && pasazerowie.size() == 0 && !ludzik_zero) {
			if (!czy_zegar_zaczal_odmierzac) {
				zegar.restart();
				czy_zegar_zaczal_odmierzac = true;
			}
			else {
				if (zegar.getElapsedTime().asSeconds() > 5) {
					kierunek = "dol";
					ludzik_zero = true;
					czy_zegar_zaczal_odmierzac = false;
				}
			}
		}
		else {
			czy_zegar_zaczal_odmierzac = false;
			if (pozycja(wysokosc)==0) {
				ludzik_zero = false;
			}
			if (kierunek == "gora") {
				if (pozycja(wysokosc) < 0) {
					w_gore(&wysokosc, zegar);
				}
				else {
					czy_sa_ludzie_na_trasie = false;
					czy_w_kabinie_sa_ludzie = false;

					if (pasazerowie.size() > 0) {//wypakunek
						for (int i = pasazerowie.size() - 1; i >= 0; i--) {
							if (pasazerowie[i] == pozycja(wysokosc)) {
								pasazerowie.erase(pasazerowie.begin() + i);
							}
						}
					}


					if (pasazerowie.size() < 4 && poziom[pozycja(wysokosc)].size() > 0) {//za³adunek
						for (int i = poziom[pozycja(wysokosc)].size() - 1; i >= 0; i--) {
							if (poziom[pozycja(wysokosc)][i] > pozycja(wysokosc)) {
								pasazerowie.push_back(poziom[pozycja(wysokosc)][i]);
								poziom[pozycja(wysokosc)].erase(poziom[pozycja(wysokosc)].begin() + i);
							}
						}
					}

					if (pasazerowie.size()) {
						for (int i = 0; i < pasazerowie.size(); i++) {
							if (pasazerowie[i] > pozycja(wysokosc)) {
								czy_w_kabinie_sa_ludzie = true;
							}
						}
					}


					for (int i = pozycja(wysokosc)+1; i < 3; i++) {
						if (spis_ludzi_na_pietrach[i]) {
							czy_sa_ludzie_na_trasie = true;
							break;
						}
					}

					if (!czy_w_kabinie_sa_ludzie && !czy_sa_ludzie_na_trasie) {
						kierunek = "dol";
					}
					else {
						w_gore(&wysokosc, zegar);
					}

				}
			}
			else {// kierunek == "dol"
				if (pozycja(wysokosc) < 0) {
					w_dol(&wysokosc, zegar);
				}
				else {
					czy_sa_ludzie_na_trasie = false;
					czy_w_kabinie_sa_ludzie = false;
					if (pasazerowie.size() > 0) {
						for (int i = pasazerowie.size() - 1; i >= 0; i--) {
							if (pasazerowie[i] == pozycja(wysokosc)) {
								pasazerowie.erase(pasazerowie.begin() + i);
							}
						}
					}


					if (pasazerowie.size() < 4 && poziom[pozycja(wysokosc)].size() > 0) {
						for (int i = poziom[pozycja(wysokosc)].size() - 1; i >= 0; i--) {
							if (poziom[pozycja(wysokosc)][i] < pozycja(wysokosc)) {
								pasazerowie.push_back(poziom[pozycja(wysokosc)][i]);
								poziom[pozycja(wysokosc)].erase(poziom[pozycja(wysokosc)].begin() + i);
							}
						}
					}
					if (pasazerowie.size()) {
						for (int i = 0; i < pasazerowie.size(); i++) {
							if (pasazerowie[i] < pozycja(wysokosc)) {
								czy_w_kabinie_sa_ludzie = true;
							}
						}
					}

					for (int i = 0; i < pasazerowie.size(); i++) {
						if (pasazerowie[i] < pozycja(wysokosc)) {
							czy_w_kabinie_sa_ludzie = true;
							break;
						}
					}
					for (int i = 0; i < pozycja(wysokosc); i++) {
						if (spis_ludzi_na_pietrach[i]) {
							czy_sa_ludzie_na_trasie = true;
							break;
						}
					}
					if (!czy_w_kabinie_sa_ludzie && !czy_sa_ludzie_na_trasie && !ludzik_zero) {
						kierunek = "gora";
					}
					else {
						w_dol(&wysokosc, zegar);
					}

				}
			}
		}
		
		


		wyswietlanie_ludkow(&okno, &patyczak1, &patyczak2, &patyczak3, &patyczak4, pasazerowie.size(), 600 - wysokosc - 70);
		podnosnik.setPosition(610, (int)(600-wysokosc));
		narysuj_interfejs(&okno,wybrany,pasazerowie);
		narysuj_winde(&okno);
		okno.draw(podnosnik);
		okno.display();																//metoda odpowiedzialna za wyœwietlanie zmian za ka¿dym razem jak jest wywo³ana daje .

	}

	return 0;
}

sf::RectangleShape lewa_sciana1() {
	sf::RectangleShape sciana;
	sciana.setSize(sf::Vector2f(10, 200));
	sciana.setPosition(600, 100);
	sciana.setFillColor(CIEMNOSZARY);
	return sciana;
}
sf::RectangleShape lewa_sciana2() {
	sf::RectangleShape sciana;
	sciana.setSize(sf::Vector2f(10, 200));
	sciana.setPosition(600, 410);
	sciana.setFillColor(CIEMNOSZARY);
	return sciana;
}
sf::RectangleShape sufit() {
	sf::RectangleShape sciana;
	sciana.setSize(sf::Vector2f(100, 10));
	sciana.setPosition(610, 100);
	sciana.setFillColor(CIEMNOSZARY);
	return sciana;
}
sf::RectangleShape prawa_sciana() {
	sf::RectangleShape sciana;
	sciana.setSize(sf::Vector2f(10, 290));
	sciana.setPosition(700, 210);
	sciana.setFillColor(CIEMNOSZARY);
	return sciana;
}
sf::RectangleShape parter() {
	sf::RectangleShape sciana;
	sciana.setSize(sf::Vector2f(340, 10));
	sciana.setPosition(610, 600);
	sciana.setFillColor(CIEMNOSZARY);
	return sciana;
}
sf::RectangleShape pietro1() {
	sf::RectangleShape sciana;
	sciana.setSize(sf::Vector2f(350, 10));
	sciana.setPosition(260, 400);
	sciana.setFillColor(CIEMNOSZARY);
	return sciana;
}
sf::RectangleShape pietro2() {
	sf::RectangleShape sciana;
	sciana.setSize(sf::Vector2f(340, 10));
	sciana.setPosition(700, 210);
	sciana.setFillColor(CIEMNOSZARY);
	return sciana;
}
void narysuj_interfejs(sf::RenderWindow* okno, int wybrany, vector<int> pasazerowie) {								//ta funkcja tylko rysuje przyciski nie robi nic wiecej
	int nr_przycisku = 0;
	sf::Font font;																//aby zapisaæ liczbe potrzeba czcionki
	if (!font.loadFromFile("arialbd.ttf")) {									// aby pobraæ jak¹œ czcionkê nale¿y j¹ umieœciæ w pliku gdzie jest main.cpp 
		cout << "\nblad przy pobieraniu czcionki\n";
	}
	sf::RectangleShape przycisk;
	sf::Text liczba;
	for (int i = 0; i < 6; i++) {
		przycisk.setSize(sf::Vector2f(100, 100));
		przycisk.setPosition(100*(i%3), (i/3)*100);
		if (wybrany == i) {
			przycisk.setFillColor(CZERWONY);
		}
		else {
			przycisk.setFillColor(CIEMNOSZARY);
		}
		(*okno).draw(przycisk);
		przycisk.setSize(sf::Vector2f(80, 80));
		przycisk.setPosition(100 * (i % 3) + 10, (i / 3) * 100 + 10);
		przycisk.setFillColor(SZARY);
		(*okno).draw(przycisk);
		liczba.setFont(font);
		liczba.setString(to_string(i%3));
		liczba.setPosition(100 * (i % 3) + 40, (i / 3) * 100 + 25);
		liczba.setCharacterSize(36);
		liczba.setFillColor(CZARNY);
		(*okno).draw(liczba);
	}
	sf::Text Masa;
	Masa.setFont(font);
	Masa.setString("Waga pasazerow: " + to_string(((pasazerowie).size()) * 70));
	Masa.setPosition(600, 10);
	Masa.setCharacterSize(20);
	Masa.setFillColor(CZARNY);
	(*okno).draw(Masa);
	int x;
	sf::Text pietra;
	pietra.setFont(font);
	pietra.setCharacterSize(30);
	pietra.setFillColor(CZARNY);
	for (int i = 0; i < 3; i++) {
		pietra.setString(to_string(i));
		if (i % 2 == 0) {
			x = 800;
		}
		else {
			x = 500;
		}
		pietra.setPosition(x, 500-i*200-20);
		(*okno).draw(pietra);
	}
}


int ktory_przycisk(int x, int y) {

		if (x < 0 || y < 0 || x > 300 || y > 200) {
			
			return -1;
		}
		else {
			if (x < 100 && y < 100) {
				
				return 0;
			}
			else {
				if (x < 200 && y < 100) {
					
					return 1;
				}
				else {
					if (x < 300 && y < 100) {
						
						return 2;
					}
					else {
						if (x < 100 && y < 200) {
							
							return 3;
						}
						else {
							if (x < 200 && y < 200) {
								;
								return 4;
							}
							else {
								if (x < 300 && y < 200) {
									
									return 5;
								}
							}
						}
					}
				}
			}
		}
	return -1;
}

int pozycja(int wysokosc) {
	if(wysokosc==0){
		return 0;
	}
	else {
		if (wysokosc < 200) {
			return -1;
		}
		else {
			if (wysokosc == 200) {
				return 1;
			}
			else {
				if (wysokosc == 390) {
					return 2;
				}
				else {
					if (wysokosc > 200) {
						return -2;
					}
				}
			}
		}
	}
}

void spisywanie(int* spis, string kierunek, vector<int>* poziomy) {
	spis[0] = 0;
	spis[1] = 0;
	spis[2] = 0;
	for (int i = 0; i < 3; i++) {
		spis[i]=poziomy[i].size();
	}
	
}

void w_gore(int* wysokosc, sf::Clock zegar) {
	zegar.restart();
	sf::Time delta;
	int mikrosekundy;
	while (true) {
		delta = zegar.getElapsedTime();
		mikrosekundy = delta.asMicroseconds();
		if (mikrosekundy > 50) {
			break;
		}
	}
	*wysokosc = *wysokosc + 1 * PREDKOSC;
}
void w_dol(int* wysokosc, sf::Clock zegar) {
	zegar.restart();
	sf::Time delta;
	int mikrosekundy;
	while (true) {
		delta = zegar.getElapsedTime();
		mikrosekundy = delta.asMicroseconds();
		if (mikrosekundy > 50) {
			break;
		}
	}
	*wysokosc = *wysokosc - 1 * PREDKOSC;
}

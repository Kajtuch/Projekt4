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
const int PREDKOSC = 50;

using namespace std;
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
	void narysuj_interfejs(sf::RenderWindow* okno, int wybrany);

	void w_dol(int* wysokosc, sf::Clock zegar);
	void w_gore(int* wysokosc, sf::Clock zegar);
	
	int pozycja(int wysokosc);													//funkcja zwraca pietro na ktorym jest teraz podnosnik jesli jest miedzy pietrami zwraca "-1" gdy podnosnik jest pomiedzy 0 a 1 i "-2" gdy jest pomiedzy 1 i 2

	bool czy_pietro_pe³ne(int* ludzie) {
		for (int i = 0; i < 6; i++) {
			if (ludzie[i] == -1) {
				return false;
			}	
		}
		return true;
	}

	int main() {
		string kierunek = "gora";																//zmienna ma wartosc "gora" lub "dol" w zale¿noœci od tego w ktora strone sie porusza winda
		int aktualna_pozycja = 0;															//zmienna posiada informacje o tym na ktorym pietrze znajduje sie winda
		sf::Clock zegar;																//zmienna typu zegar XD
		int wysokosc = 0;																	//wysokosc na jakiej znajduje siê podnosnik wzgledem spodu szybu windy
		int wybrany = -1;
		bool czy_klikniety = false;
		sf::RenderWindow okno;															//tworzym nasze okno jako obiekt klasy Window z zakresu nazw sf
		sf::RectangleShape podnosnik;
		podnosnik.setSize(sf::Vector2f(100, 10));
		podnosnik.setFillColor(CZERWONY);
		okno.create(sf::VideoMode(SZEROKOSC_OKNA, WYSOKOSC_OKNA, 32), "winda");			// tutaj powstaje nasze okno pierwszy argument funkcji to wymiary okna np. "1000, 500," 32 oznacza zakres kolorów. drugi argument to nazwa okna

		vector<int> poziom[3];															//tablica 3 elementowa sk³adajaca siê z vektorów typu int zawiera informacje o pasa¿erach na ka¿dym pietrze
		vector<int> pasazerowie;																//ta tablica zawiera informacje o tym ile i ggdzie jad¹cych pasarzerów znajduje sie na podnoœniku

	sf::Event input;																//deklaruje zmienn¹ event ktora zawieraæ bêdzie informacje o tym co my robimy (np ruszamy myszk¹)
	
	while (okno.isOpen()) {															// pêtla wykonuje siê dopóki okno jest otwarte
		okno.clear(BIALY);															//metoda clear wype³nia ca³e okno kolorem, kolor jest jak¹œ klas¹
		okno.pollEvent(input);														//wywo³anie tej funkcji sprawia ¿e zmienna input wype³niona jest informacjami o eventach
		sf::Vector2i pozycja_myszki = sf::Mouse::getPosition(okno);
		if (input.type == sf::Event::Closed) {										//ten if zamyka okno je¿eli klikniesz X w prawym górnym rogu okna
			okno.close();
			break;
		}
		/////////////////////////////////////////////////////////////////////////////obs³uga przycisków
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
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
		///to pokazuje w konsolce gdzie ile jest ludzi 
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
			cout <<endl<< ktory_przycisk(pozycja_myszki.x, pozycja_myszki.y)<< endl;
		}
		///
		////////////////////////////////////////////////////////////////////////////dzia³anie windy
		aktualna_pozycja = pozycja(wysokosc);
		if (aktualna_pozycja < 0) {
			if (kierunek == "gora") {
				w_gore(&wysokosc, zegar);
			}
			else {
				w_dol(&wysokosc, zegar);
			}
			
		}
		else {
			for (int i = pasazerowie.size()-1;i>=0; i--) {
				if (pasazerowie[i]==aktualna_pozycja) {
					pasazerowie.erase(pasazerowie.begin()+i);
				}
			}
			if (kierunek == "gora") {
				bool zmiana = true;													//je¿eli ta zmienna pozostanie true po wykonaniu pêtli to znaczy ¿e powinien zmienic sie kierunek jazdy windy
				bool stop = true;
				for (int i = poziom[aktualna_pozycja].size() - 1; i >= 0; i--) {
					if (poziom[aktualna_pozycja][i] > aktualna_pozycja && pasazerowie.size()<3) {
						pasazerowie.push_back(poziom[aktualna_pozycja][i]);
						poziom[aktualna_pozycja].erase(poziom[aktualna_pozycja].begin() + i);
						zmiana = false;
					}
				}
				if (zmiana) {
					for (int i = poziom[aktualna_pozycja].size() - 1; i >= 0; i--) {
						if (poziom[aktualna_pozycja][i] < aktualna_pozycja && pasazerowie.size() < 3) {
							pasazerowie.push_back(poziom[aktualna_pozycja][i]);
							poziom[aktualna_pozycja].erase(poziom[aktualna_pozycja].begin() + i);
							kierunek = "dol";
						}
					}
					stop = false;
				}
				if (!stop) {

				}
				else {
					if (zmiana) {
						w_dol(&wysokosc, zegar);
					}
					else {
						w_gore(&wysokosc, zegar);
					}
				}
				
			}
			else {
				if (kierunek == "dol") {
					bool zmiana = true;													//je¿eli ta zmienna pozostanie true po wykonaniu pêtli to znaczy ¿e powinien zmienic sie kierunek jazdy windy
					bool stop = true;
					for (int i = poziom[aktualna_pozycja].size() - 1; i >= 0; i--) {
						if (poziom[aktualna_pozycja][i] < aktualna_pozycja && pasazerowie.size() < 3) {
							pasazerowie.push_back(poziom[aktualna_pozycja][i]);
							poziom[aktualna_pozycja].erase(poziom[aktualna_pozycja].begin() + i);
							zmiana = false;
						}
					}
					if (zmiana) {
						for (int i = poziom[aktualna_pozycja].size() - 1; i >= 0; i--) {
							if (poziom[aktualna_pozycja][i] > aktualna_pozycja && pasazerowie.size() < 3) {
								pasazerowie.push_back(poziom[aktualna_pozycja][i]);
								poziom[aktualna_pozycja].erase(poziom[aktualna_pozycja].begin() + i);
								kierunek = "gora";
							}
						}
						stop = false;
					}
					if (!stop) {

					}
					else {
						if (!zmiana) {
							w_dol(&wysokosc, zegar);
						}
						else {
							w_gore(&wysokosc, zegar);
						}
					}
				}
			}
		}
		





		podnosnik.setPosition(610, 600+wysokosc);
		narysuj_interfejs(&okno,wybrany);
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
void narysuj_interfejs(sf::RenderWindow* okno, int wybrany) {								//ta funkcja tylko rysuje przyciski nie robi nic wiecej
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
				if (wysokosc == 400) {
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

void w_gore(int* wysokosc, sf::Clock zegar) {
	sf::Time uplyw_czasu = zegar.restart();
	float sekundy = uplyw_czasu.asSeconds();
	*wysokosc =+ sekundy * PREDKOSC;
}
void w_dol(int* wysokosc, sf::Clock zegar) {
	sf::Time uplyw_czasu = zegar.restart();
	float sekundy = uplyw_czasu.asSeconds();
	*wysokosc =- sekundy * PREDKOSC;
}
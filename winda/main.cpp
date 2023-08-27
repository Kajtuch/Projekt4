#include <iostream>
#include <SFML/Graphics.hpp> 
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

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

using namespace std;
																					//deklaruje tutaj funkcje buduj¹ce winde i piêtra dla przejrzystoœci zwracaj¹ obiekt bêd¹cy jakimœ prostok¹tem który mo¿na potem namalowaæ
	sf::RectangleShape lewa_sciana1();												//to funkcje zwracaj¹ce jakiœ skonstruowany prostok¹t
	sf::RectangleShape lewa_sciana2();
	sf::RectangleShape prawa_sciana();
	sf::RectangleShape sufit();
	sf::RectangleShape parter();
	sf::RectangleShape pietro1();
	sf::RectangleShape pietro2();

	int ktory_przycisk(float x, float y);											//funkcja sprawdza na którym przycisku mamy aktualnie myszkê

	void narysuj_winde(sf::RenderWindow* okno) {
		(*okno).draw(lewa_sciana1());												//draw rysuje jakiœ obiekt
		(*okno).draw(lewa_sciana2());
		(*okno).draw(prawa_sciana());
		(*okno).draw(sufit());
		(*okno).draw(parter());
		(*okno).draw(pietro1());
		(*okno).draw(pietro2());
		
	}
	void narysuj_interfejs(sf::RenderWindow* okno);

	bool czy_pietro_pe³ne(int* ludzie) {
		for (int i = 0; i < 6; i++) {
			if (ludzie[i] == -1) {
				return false;
			}	
		}
		return true;
	}

int main() {
	int wybrany;
	sf::RenderWindow okno;															//tworzym nasze okno jako obiekt klasy Window z zakresu nazw sf
	sf::RectangleShape podnosnik;
	podnosnik.setSize(sf::Vector2f(100, 10));
	podnosnik.setFillColor(CZERWONY);
	podnosnik.setPosition(610, 600);
	okno.create(sf::VideoMode(SZEROKOSC_OKNA, WYSOKOSC_OKNA, 32), "winda");			// tutaj powstaje nasze okno pierwszy argument funkcji to wymiary okna np. "1000, 500," 32 oznacza zakres kolorów. drugi argument to nazwa okna
	
	sf::Event input;																//deklaruje zmienn¹ event ktora zawieraæ bêdzie informacje o tym co my robimy (np ruszamy myszk¹)

	while (okno.isOpen()) {															// pêtla wykonuje siê dopóki okno jest otwarte
		okno.clear(BIALY);															//metoda clear wype³nia ca³e okno kolorem, kolor jest jak¹œ klas¹
		okno.pollEvent(input);														//wywo³anie tej funkcji sprawia ¿e zmienna input wype³niona jest informacjami o eventach
		system("cls");
		cout << "X: " << input.mouseMove.x << "  Y: " << input.mouseMove.y;
		if (input.type == sf::Event::Closed) {										//ten if zamyka okno je¿eli klikniesz X w prawym górnym rogu okna
			okno.close();
			break;
		}
		////////////////////////////////////////////////// obs³uga windy
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&& ktory_przycisk(input.mouseMove.x, input.mouseMove.y)>=0) {
			if (ktory_przycisk(input.mouseMove.x, input.mouseMove.y) <= 2) {
				wybrany = ktory_przycisk(input.mouseMove.x, input.mouseMove.y);
			}
			else {
				switch (ktory_przycisk(input.mouseMove.x, input.mouseMove.y)) {
				case 3: {
					
				}
				case 4: {

				}
				case 5: {

				}
				default{
					break;
				}
				}
			}
		}
		



		narysuj_interfejs(&okno);
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
void narysuj_interfejs(sf::RenderWindow* okno) {								//ta funkcja tylko rysuje przyciski nie robi nic wiecej
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
		przycisk.setFillColor(CIEMNOSZARY);
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
int ktory_przycisk(float x, float y) {
	if (x < 0 || y < 0 || x > 300|| y > 200) {
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
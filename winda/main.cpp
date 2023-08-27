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
																					//deklaruje tutaj funkcje buduj�ce winde i pi�tra dla przejrzysto�ci zwracaj� obiekt b�d�cy jakim� prostok�tem kt�ry mo�na potem namalowa�
	sf::RectangleShape lewa_sciana1();												//to funkcje zwracaj�ce jaki� skonstruowany prostok�t
	sf::RectangleShape lewa_sciana2();
	sf::RectangleShape prawa_sciana();
	sf::RectangleShape sufit();
	sf::RectangleShape parter();
	sf::RectangleShape pietro1();
	sf::RectangleShape pietro2();


	void narysuj_winde(sf::RenderWindow* okno) {
		(*okno).draw(lewa_sciana1());												//draw rysuje jaki� obiekt
		(*okno).draw(lewa_sciana2());
		(*okno).draw(prawa_sciana());
		(*okno).draw(sufit());
		(*okno).draw(parter());
		(*okno).draw(pietro1());
		(*okno).draw(pietro2());
		
	}

int main() {
	sf::RenderWindow okno;															//tworzym nasze okno jako obiekt klasy Window z zakresu nazw sf
	okno.create(sf::VideoMode(SZEROKOSC_OKNA, WYSOKOSC_OKNA, 32), "winda");			// tutaj powstaje nasze okno pierwszy argument funkcji to wymiary okna np. "1000, 500," 32 oznacza zakres kolor�w. drugi argument to nazwa okna
	
	sf::Event input;																//deklaruje zmienn� event ktora zawiera� b�dzie informacje o tym co my robimy (np ruszamy myszk�)

	while (okno.isOpen()) {															// p�tla wykonuje si� dop�ki okno jest otwarte
		okno.clear(BIALY);															//metoda clear wype�nia ca�e okno kolorem, kolor jest jak�� klas�
		okno.pollEvent(input);														//wywo�anie tej funkcji sprawia �e zmienna input wype�niona jest informacjami o eventach
		system("cls");
		cout << "X: " << input.mouseMove.x << "  Y: " << input.mouseMove.y;

		if (input.type == sf::Event::Closed) {										//ten if zamyka okno je�eli klikniesz X w prawym g�rnym rogu okna
			okno.close();
			break;
		}

		narysuj_winde(&okno);	
		okno.display();															//metoda odpowiedzialna za wy�wietlanie zmian za ka�dym razem jak jest wywo�ana daje .

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
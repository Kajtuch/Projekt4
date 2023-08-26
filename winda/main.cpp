#include <iostream>
#include <SFML/Graphics.hpp> 
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

int main() {
	cout << "hello world\n";

	sf::Window okno;//tworzym nasze okno jako obiekt klasy Window z zakresu nazw sf

	okno.create(sf::VideoMode(1600, 600, 32), "winda"); // tutaj powstaje nasze okno pierwszy argument funkcji to wymiary okna np. "1600, 600," 32 oznacza zakres kolorów. drugi argument to nazwa okna

	while (okno.isOpen()) {// pêtla wykonuje siê dopóki okno jest otwarte


		okno.display();//metoda odpowiedzialna za wyœwietlanie zmian.
	}
	system("pause");
	return 0;
}
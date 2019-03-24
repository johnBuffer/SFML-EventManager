#include <SFML/Graphics.hpp>
#include "event_manager.hpp"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "Test window");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	EventManager evm(window);
	evm.registerCallback(sf::Event::EventType::Closed, [&](const sf::Event&) {window.close(); });
	evm.addKeyCallback(sf::Keyboard::A, sf::Event::EventType::KeyPressed, [&](const sf::Event&) {std::cout << "YEEEES" << std::endl; });
	evm.addKeyCallback(sf::Keyboard::A, sf::Event::EventType::KeyReleased, [&](const sf::Event&) {std::cout << "NOOOO" << std::endl; });

	while (window.isOpen())
	{
		evm.processEvents();

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
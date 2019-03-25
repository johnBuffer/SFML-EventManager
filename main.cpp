#include <SFML/Graphics.hpp>
#include "event_manager.hpp"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "Test window");

	EventManager evm(window);
	evm.addEventCallback(sf::Event::EventType::Closed, [&](const sf::Event&) {window.close(); });
	evm.addKeyPressedCallback(sf::Keyboard::A, [&](const sf::Event&) {std::cout << "A Pressed" << std::endl; });
	evm.addKeyReleasedCallback(sf::Keyboard::A, [&](const sf::Event&) {std::cout << "A released" << std::endl; });

	evm.addEventCallback(sf::Event::EventType::MouseButtonPressed, [&](const sf::Event&) {std::cout << "Mouse button pressed" << std::endl; });

	while (window.isOpen())
	{
		evm.processEvents();

		window.clear();
		window.display();
	}

	return 0;
}
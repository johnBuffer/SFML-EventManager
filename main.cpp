#include <SFML/Graphics.hpp>
#include "event_manager.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "Test window");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	EventManager evm(window);
	evm.registerCallback(sf::Event::EventType::Closed, [&]() {window.close(); });

	while (window.isOpen())
	{
		evm.processEvents();

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
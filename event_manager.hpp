#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>

#include <array>

using EventCallback = std::function<void(const sf::Event& event)>;

template<typename T>
using EventCallbackMap = std::unordered_map<T, EventCallback>;

/*
	This class handles Key related events
*/
class KeyEventManager
{
public:
	KeyEventManager() = default;
	~KeyEventManager() = default;

	void processKeyEvent(const sf::Event& event) const
	{
		sf::Keyboard::Key key_code = event.key.code;
		auto it(m_callmap.find(key_code));
		if (it != m_callmap.end())
		{
			// Call its associated callback
			(it->second)(event);
		}
	}

	void addKeyCallback(sf::Keyboard::Key key_code, EventCallback callback)
	{
		m_callmap[key_code] = callback;
	}

private:
	EventCallbackMap<sf::Keyboard::Key> m_callmap;
};


/*
	This class handles any type of event and call its associated callbacks if any.
	To process key event in a more convenient way its using a KeyManager
*/
class EventManager
{
public:
	EventManager(sf::Window& window) :
		m_window(window)
	{
		// Register key events built in callbacks
		this->addEventCallback(sf::Event::EventType::KeyPressed, [&](const sf::Event& event) {m_key_pressed_manager.processKeyEvent(event); });
		this->addEventCallback(sf::Event::EventType::KeyReleased, [&](const sf::Event& event) {m_key_released_manager.processKeyEvent(event); });
	}

	// Attach new callback to an event
	void addEventCallback(sf::Event::EventType type, EventCallback callback)
	{
		m_events_callmap[type] = callback;
	}

	// Calls events' attached callbacks
	void processEvents() const
	{
		// Iterate over events
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			// If event type is registred
			sf::Event::EventType type = event.type;
			auto it(m_events_callmap.find(type));
			if (it != m_events_callmap.end())
			{
				// Call its associated callback
				(it->second)(event);
			}
		}
	}

	// Removes a callback
	void removeCallback(sf::Event::EventType type)
	{
		// If event type is registred
		auto it(m_events_callmap.find(type));
		if (it != m_events_callmap.end())
		{
			// Remove its associated callback
			m_events_callmap.erase(it);
		}
	}

	// Adds a key pressed callback
	void addKeyPressedCallback(sf::Keyboard::Key key_code, EventCallback callback)
	{
		m_key_pressed_manager.addKeyCallback(key_code, callback);
	}

	// Adds a key released callback
	void addKeyReleasedCallback(sf::Keyboard::Key key_code, EventCallback callback)
	{
		m_key_released_manager.addKeyCallback(key_code, callback);
	}

private:
	sf::Window& m_window;

	KeyEventManager m_key_pressed_manager;
	KeyEventManager m_key_released_manager;
	EventCallbackMap<sf::Event::EventType> m_events_callmap;
};
#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>

#include <array>

using EventCallback = std::function<void(const sf::Event& event)>;

template<typename T>
using EventCallbackMap = std::unordered_map<T, EventCallback>;

class KeyEventManager
{
public:
	KeyEventManager() = default;

	void processKeypressedEvent(const sf::Event& event) const
	{
		processKeyEvent(m_key_pressed_callmap, event);
	}

	void processReleasedEvent(const sf::Event& event) const
	{
		processKeyEvent(m_key_released_callmap, event);
	}

	void addKeyCallback(sf::Keyboard::Key key_code, sf::Event::EventType type, EventCallback callback)
	{
		if (type == sf::Event::KeyPressed)
		{
			m_key_pressed_callmap[key_code] = callback;
		}
		else if (type == sf::Event::KeyReleased)
		{
			m_key_released_callmap[key_code] = callback;
		}
	}

private:
	EventCallbackMap<sf::Keyboard::Key> m_key_pressed_callmap;
	EventCallbackMap<sf::Keyboard::Key> m_key_released_callmap;

	void processKeyEvent(const EventCallbackMap<sf::Keyboard::Key>& event_map, const sf::Event& event) const
	{
		sf::Keyboard::Key key_code = event.key.code;
		auto it(event_map.find(key_code));
		if (it != event_map.end())
		{
			// Call its associated callback
			(it->second)(event);
		}
	}
};


class EventManager
{
public:
	EventManager(sf::Window& window) :
		m_window(window)
	{
		this->registerCallback(sf::Event::EventType::KeyPressed, [&](const sf::Event& event) {m_key_manager.processKeypressedEvent(event); });
		this->registerCallback(sf::Event::EventType::KeyReleased, [&](const sf::Event& event) {m_key_manager.processReleasedEvent(event); });
	}

	void registerCallback(sf::Event::EventType type, EventCallback callback)
	{
		m_events_callmap[type] = callback;
	}

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

	void addKeyCallback(sf::Keyboard::Key key_code, sf::Event::EventType type, EventCallback callback)
	{
		m_key_manager.addKeyCallback(key_code, type, callback);
	}

private:
	sf::Window& m_window;

	KeyEventManager m_key_manager;
	EventCallbackMap<sf::Event::EventType> m_events_callmap;
};
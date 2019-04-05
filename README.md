# SFML-EventManager

Little helper to allow callbacks based event management with [SFML](https://github.com/SFML/SFML)

## Installation

1. Clone repo ❤️

2. Include header
```cpp
#include "event_manager.hpp"
```

## Usage

1. Declare your callbacks
```cpp
// Instanciate an events manager
sfev::EventManager evm(window);
```
```cpp
// Add a close callback
evm.addEventCallback(sf::Event::EventType::Closed, [&](const sf::Event&) {window.close(); });
```

Example of Mouse and Keyboard events handling
```cpp
using cEvent = const sf::Event&;

// Add Key event callback
evm.addKeyPressedCallback(sf::Keyboard::A, [&](cEvent) {std::cout << "A Pressed" << std::endl; });
evm.addKeyReleasedCallback(sf::Keyboard::A, [&](cEvent) {std::cout << "A released" << std::endl; });

// Add Mouse button event callback
evm.addMousePressedCallback(sf::Mouse::Left, [&](cEvent) {std::cout << "Mouse LEFT pressed" << std::endl; });
evm.addMouseReleasedCallback(sf::Mouse::Left, [&](cEvent) {std::cout << "Mouse LEFT released" << std::endl; });

// Add another Mouse button event callback
evm.addMousePressedCallback(sf::Mouse::Right, [&](cEvent) {std::cout << "Mouse RIGHT pressed" << std::endl; });
evm.addMouseReleasedCallback(sf::Mouse::Right, [&](cEvent) {std::cout << "Mouse RIGHT released" << std::endl; });
```

2. Enjoy clean events pooling loop
```cpp
while (window.isOpen())
{
  // Clean and peaceful
  evm.processEvents();

  window.clear();
  ...
  window.display();
}
```

## Technical details

The callback is a ```std::function<void(const sf::Event& event)>``` so you can pass any callable object with this signature. 

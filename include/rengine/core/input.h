#pragma once

#include <library/vec2.h>
#include <SFML/Window.hpp>

namespace REngine {

class InputController {
public:
    bool w, a, s, d;
    bool lmb, rmb;
    bool space;
    Vec2<float> mousePosition;

public:
    void HandleEvent(sf::Event event);
    
    void KeyPressed(sf::Event::KeyEvent& e);
    void KeyReleased(sf::Event::KeyEvent& e);
    void MouseMoved(sf::Event::MouseMoveEvent& e);
    void MousePressed(sf::Event::MouseButtonEvent& e);
    void MouseReleased(sf::Event::MouseButtonEvent& e);
};

} // namespace REngine

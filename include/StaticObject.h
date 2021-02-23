#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>


class StaticObject :public GameObject {
public:

    //using section
    using GameObject::GameObject;
    
    //distructors
    virtual ~StaticObject() = default;

};


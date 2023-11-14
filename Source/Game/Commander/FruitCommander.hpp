#pragma once

#include "../../Engine/Graphic/Base/BaseCommander.hpp"

#include "../Scene/FruitScene.hpp"

struct FruitCommander : public BaseCommander {
    FruitCommander(std::shared_ptr<BaseScene> scene);

protected:
    void _on_key_pressed(const Event::KeyPressed& evt) override;

private:
    std::shared_ptr<FruitScene> m_scene;
    std::shared_ptr<Fruit> m_currentFruit;

    int m_last_add_ms = 0;
};
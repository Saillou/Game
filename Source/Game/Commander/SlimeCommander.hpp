#pragma once

#include "../../Engine/Graphic/Base/BaseCommander.hpp"
#include "../Scene/SlimeScene.hpp"

struct SlimeCommander : public BaseCommander {
    SlimeCommander(std::shared_ptr<BaseScene> scene);

protected:
    std::shared_ptr<SlimeScene> m_scene;
};
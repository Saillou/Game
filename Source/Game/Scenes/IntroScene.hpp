#pragma once

#include "../../Engine/Graphic/Base/BaseScene.hpp"

#include <vector>
#include <memory>
#include "Objects/SphereBatch.hpp"

// -- Scene --
struct IntroScene : public BaseScene {
    IntroScene();

    void draw() override;
    void resize(int width, int height) override;

    void startText() {
        m_anime_text = true;
    }
    void startBrownian() {
        m_anime_brownian = true;
    }

private:
    void _update_camera();
    const std::vector<glm::vec2> _get_title_pos(size_t i = -1) const;

    SphereBatch m_decors;
    SphereBatch m_title;

    bool m_anime_text = false;
    bool m_anime_brownian = false;
};

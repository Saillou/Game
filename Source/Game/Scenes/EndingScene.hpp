#pragma once

#include "../../Engine/Graphic/Base/BaseScene.hpp"
#include "../../Utils/Timeline.hpp"

#include "Objects/AnimatedText.hpp"
#include "Objects/BoxBatch.hpp"
#include "Objects/Sphere.hpp"

// -- Scene --
struct EndingScene : public BaseScene {
    EndingScene();

    void draw() override;
    void resize(int width, int height) override;

private:
    void _update_camera();
    void _createScenario();

    Timeline<Drawable> m_timeline;
    BoxBatch m_sand;
    Box m_ground;
    Sphere m_slime;
};

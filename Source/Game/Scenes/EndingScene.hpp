#pragma once

#include "../../Engine/Graphic/Base/BaseScene.hpp"
#include "../../Utils/Timeline.hpp"
#include "../../Engine/Physx/Physx.hpp"

#include "Objects/AnimatedText.hpp"
#include "Objects/BoxBatch.hpp"
#include "Bodies/SphereBody.hpp"
#include "Bodies/BoxBody.hpp"

#include "../Commanders/Common/BaseItem.hpp"

// -- Scene --
struct EndingScene : public BaseScene {
    EndingScene();

    void draw() override;
    void resize(int width, int height) override;

    void createActors();
    void addSand();

    void moveSlime(float dx, float dy);

private:
    void _update_camera();
    void _createScenario();

    Timeline<Drawable> m_timeline;

    BoxBatch m_sand;
    std::vector<Physx::PBody> m_sand_bodies;

    std::shared_ptr<BaseItem> m_ground;
    std::shared_ptr<BaseItem> m_slime;

    std::shared_ptr<SphereBody> m_light;
};

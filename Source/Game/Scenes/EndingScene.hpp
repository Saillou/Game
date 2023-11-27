#pragma once

#include "../../Engine/Graphic/Base/BaseScene.hpp"
#include "../../Utils/Animator.hpp"

#include <vector>

// -- Utils --
struct AnimatedText 
{
    // Statics
    static glm::vec2 s_viewport_size;

    // Subs
    struct Data {
        std::string text;
        glm::vec2 pos;    // [0, 1] x [0, 1]
        float size;
        glm::vec3 color;
    };
    
    // Methods
    AnimatedText(const Data& start, const Data& end, float duration, Animator::Tweet::Type type = Animator::Tweet::Type::Linear);
    void draw();

private:
    const Data _start;
    const Data _end;
    Data _current;

    Animator::uTweet _tweet;
};

// -- Scene --
struct EndingScene : public BaseScene {
    EndingScene();

    void draw() override;
    void resize(int width, int height) override;

private:
    void _createScenario();

    std::vector<AnimatedText> m_texts;
};

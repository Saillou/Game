#pragma once

#include "../../Engine/Graphic/BaseScene.hpp"
#include "../../Engine/Graphic/Drawables/BaseShape.hpp"
#include "../../Engine/Graphic/Shaders/ComputeShader.hpp"
#include "../../Engine/Graphic/Utils/StorageBuffer.hpp"

#include <unordered_map>
#include <memory>

// Helper
struct Camera {
    glm::mat4 projection;
    glm::mat4 modelview;
};


// Object wrapper
struct SceneObject {
    SceneObject() = default;
    virtual ~SceneObject() = default;

    template<typename T> inline T* as() {  
        return reinterpret_cast<T*>(this); 
    }
};



// -- Scene --
struct FruitScene : public BaseScene {
    FruitScene();

    void draw() override;
    void resize(int width, int height) override;

private:
    typedef std::shared_ptr<SceneObject> sSceneObject;

    std::unordered_map<std::string, sSceneObject> m_shapes;
    Camera m_camera;
};

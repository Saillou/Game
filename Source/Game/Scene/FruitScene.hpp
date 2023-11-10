#pragma once

#include "../../Engine/Graphic/BaseScene.hpp"
#include "../../Engine/Graphic/Drawables/BaseShape.hpp"
#include "../../Engine/Graphic/Shaders/ComputeShader.hpp"
#include "../../Engine/Graphic/Utils/StorageBuffer.hpp"

#include <unordered_map>
#include <memory>

// Helper
struct Camera {
    glm::mat4 m_projection;
    glm::mat4 m_modelview;
};


// Object wrapper
struct SceneObject {
    SceneObject(std::unique_ptr<BaseShape> uShape) : 
        m_shape(nullptr), 
        m_shader() 
    {
        m_shape.swap(uShape);
    }
    virtual ~SceneObject() = default;

    virtual void draw() {
        m_shader.use();

        m_shape->bind();
        m_shape->draw();
    }

    template<typename T> inline T* as() {  
        return reinterpret_cast<T*>(this); 
    }

protected:
    std::unique_ptr<BaseShape> m_shape;
    Shader m_shader;
};



// -- Scene --
struct FruitScene : public BaseScene {
    FruitScene();

    void draw() override;
    void resize(int width, int height) override;

private:
    typedef std::shared_ptr<SceneObject> sSceneObject;

    std::unordered_map<std::string, sSceneObject> m_shapes;
    Camera camera;
};

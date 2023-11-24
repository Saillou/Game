#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "../Graphic/Base/Light.hpp"
#include "../Graphic/Camera.hpp"

class BaseBody {
    friend class Physx;

public:
    enum class ContactType {
        Sphere,
        Box
    };

    BaseBody(ContactType type, glm::vec3 position = glm::vec3(0.f), glm::vec3 dimensions = glm::vec3(0.f), glm::vec3 orientation = glm::vec3(0.f));
    virtual ~BaseBody();

    // Methods to implement
    virtual void draw(const Camera& camera, const std::vector<std::unique_ptr<Light>>& lights) const = 0;

    // To do: protect these members (a bit)
    ContactType type;
    glm::vec3 position;
    glm::vec3 dimensions;
    glm::vec3 orientation;

protected:
    // Internal params
    const float _mass       = 1.0f;
    const float _bouncyness = 0.7f;

    // Internal data
    glm::vec3 _speedPosition    { glm::vec3(0.f) };
    glm::vec3 _speedOrientation { glm::vec3(0.f) };
};
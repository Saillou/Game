#pragma once

#include <glm/glm.hpp>

class BaseBody {
    friend class Physx;

public:
    enum class ContactType {
        Sphere,
        Facette,
        Parallelepiped
    };

    BaseBody(ContactType type, glm::vec3 position = glm::vec3(0.f), glm::mat3 dimensions = glm::mat3(0.f), glm::vec3 orientation = glm::vec3(0.f));
    virtual ~BaseBody();

    // To do: protect these members (a bit)
    ContactType type;
    glm::vec3 position;
    glm::mat3 dimensions;
    glm::vec3 orientation;

protected:
    // Internal params
    const float _bouncyness = 1.0f;
    const float _friction   = 1.0f;

    // Internal data
    glm::vec3 _speedPosition    { glm::vec3(0.f) };
    glm::vec3 _speedOrientation { glm::vec3(0.f) };
};
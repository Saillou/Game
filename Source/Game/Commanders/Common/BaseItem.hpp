#pragma once


#include <glm/gtx/string_cast.hpp>

#include "../../../Utils/Timer.hpp"
#include "../../../Engine/Physx/Physx.hpp"
#include "../../../Engine/Graphic/Base/BaseScene.hpp"

// ------------ Base ------------
class BaseItem {
protected:
    using sBody = std::shared_ptr<BaseBody>;

    Timer::Chronometre  _time;
    sBody               _body;
    Physx::PBody        _pbody;

    virtual void _onAdd();

public:
    explicit BaseItem();
    virtual ~BaseItem() = default;

    // Getters
    sBody body() const;

    // Methods
    void addAs(Physx::BodyType type);
    void setType(Physx::BodyType type);
    void removePhysx();

private:
    virtual const sBody& createBody() { return _body; };
};

#include "BaseItem.hpp"

using namespace reactphysics3d;


// ------------------------ Base ------------------------
BaseItem::BaseItem():
    _body(nullptr),
    _pbody(nullptr)
{ }

// Getters
BaseItem::sBody BaseItem::body() const {
    return _body;
}

// Methods
void BaseItem::addTo(std::shared_ptr<BaseScene> scene, Physx::BodyType type) {
    _pbody = Physx::Add(_body ? _body : createBody(), type);
    _onAdd();
}

void BaseItem::_onAdd() {
    // to be overrided
}

#include "BoxBatch.hpp"

// -- Objects --
BoxBatch::BoxBatch(const glm::vec3& dims, const glm::vec4& color) :
    object(std::make_unique<Box>(dims))
{
    object->addRecipe(Cookable::CookType::Batch, color);
}

void BoxBatch::create() {
    object->shape()->createBatch(models);
}

void BoxBatch::update() {
    object->shape()->updateBatch(models);
}

void BoxBatch::draw(const Camera& camera, const std::vector<std::unique_ptr<Light>>& lights) {
    object->drawBatch((int)models.size(), camera, lights);
}
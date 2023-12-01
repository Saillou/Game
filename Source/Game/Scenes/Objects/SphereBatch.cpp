#include "SphereBatch.hpp"

// -- Objects --
SphereBatch::SphereBatch(float radius, const glm::vec4& color) :
    object(std::make_unique<Sphere>(radius))
{
    object->addRecipe(Cookable::CookType::Batch, color);
}

void SphereBatch::create() {
    object->shape()->createBatch(models);
}

void SphereBatch::update() {
    object->shape()->updateBatch(models);
}

void SphereBatch::draw(const Camera& camera, const std::vector<std::unique_ptr<Light>>& lights) {
    object->drawBatch((int)models.size(), camera, lights);
}
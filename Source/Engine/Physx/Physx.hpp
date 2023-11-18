#pragma once

#include <memory>
#include <unordered_set>

#include "BaseBody.hpp"

// Singleton
class Physx {
public:
    enum class BodyType {
        Static, Dynamic
    };
    static void Add(std::shared_ptr<BaseBody> body, BodyType type = BodyType::Static);
    static void Clear();
    static void Compute(float delta_time_ms);

private:
    static Physx& _get();

    // Instance members
    std::unordered_set<std::shared_ptr<BaseBody>> m_static_elements;
    std::unordered_set<std::shared_ptr<BaseBody>> m_dynamic_elements;

    // -- No copy --
    Physx() = default;

    Physx& operator=(const Physx&) = delete;
    Physx(const Physx&) = delete;
    Physx(Physx&&) = delete;
};
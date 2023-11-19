#pragma once

#include <memory>
#include <unordered_set>

#include "BaseBody.hpp"

// Singleton
class Physx {
public:
    enum class BodyType {
        Static, Dynamic, Kinematic
    };
    static void Add(std::shared_ptr<BaseBody> body, BodyType type = BodyType::Static);
    static void Clear();
    static void Compute(float delta_time_ms);

private:
    static Physx& _get();

    // Hide physics details
    struct _impl;
    std::unique_ptr<_impl> p_impl;

    // -- No copy --
    Physx();
    ~Physx();

    Physx& operator=(const Physx&) = delete;
    Physx(const Physx&) = delete;
    Physx(Physx&&) = delete;
};
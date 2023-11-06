#include "BaseDrawable.hpp"

#include <unordered_map>

std::shared_ptr<BaseShape> BaseDrawable::_Get_Or_Create(ShapeCreator creator, const std::string& shape_key) {
    // Cache all shape created 
    // (may need to clean it up with some LFU's caching)
    static std::unordered_map<std::string, std::shared_ptr<BaseShape>> s_shapes;

    const auto it_shape = s_shapes.find(shape_key);
    if (it_shape == s_shapes.cend()) {
        if (it_shape == s_shapes.cend())
            s_shapes[shape_key] = creator();
    }

    return s_shapes.at(shape_key);
}

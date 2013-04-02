#ifndef BULLET_OBJECTS_CONVERTER_HPP
#define BULLET_OBJECTS_CONVERTER_HPP

class btCollisionObject;

namespace skeletor {
namespace animation {

class Box;

}; // namespace animation
namespace physics {

class BulletObjectsConverter {
public:
        static void convertBox(btCollisionObject *obj, animation::Box* target);
};

}; // namespace physics
}; // namespace skeletor

#endif // BULLET_OBJECTS_CONVERTER_HPP

#ifndef BULLET_OBJECTS_CONVERTER_HPP
#define BULLET_OBJECTS_CONVERTER_HPP

class btCollisionObject;

namespace skeletor {
namespace animation {
class Box;
class Joint;
class SkeletonPose;
}; // namespace animation
namespace physics {

class BulletRagdoll;

/**
 * Class to convert bullet objects from/to skeletor objects.
 */
class BulletObjectsConverter {
public:
        /**
         * Convert a box from bullet object to skeletor box.
         *
         * @param obj - from
         * @param target - to
         */
        static void convertBox(btCollisionObject *obj, animation::Box* target);

};

}; // namespace physics
}; // namespace skeletor

#endif // BULLET_OBJECTS_CONVERTER_HPP

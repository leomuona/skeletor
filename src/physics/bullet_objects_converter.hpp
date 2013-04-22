#ifndef BULLET_OBJECTS_CONVERTER_HPP
#define BULLET_OBJECTS_CONVERTER_HPP

class btCollisionObject;

namespace skeletor {
namespace animation {
class Box;
class SkeletonPose;
}; // namespace animation
namespace physics {

class BulletRagdoll;

class BulletObjectsConverter {
public:
        static void convertBox(btCollisionObject *obj, animation::Box* target);
        static void convertSkeleton(BulletRagdoll *obj,
                                    animation::SkeletonPose *target);
};

}; // namespace physics
}; // namespace skeletor

#endif // BULLET_OBJECTS_CONVERTER_HPP

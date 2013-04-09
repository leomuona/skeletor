#include "physics/bullet_objects_converter.hpp"

#include "animation/box.hpp"
#include "math/vec3.hpp"
#include "btBulletDynamicsCommon.h"

namespace skeletor {
namespace physics {

void BulletObjectsConverter::convertBox(btCollisionObject *obj, animation::Box *target)
{
        btRigidBody *body = btRigidBody::upcast(obj);
        if (body) {
                float mass = body->getInvMass();
                target->setMass(mass);
                btTransform bodyTransform;
                body->getMotionState()->getWorldTransform(bodyTransform);                           btVector3 btOrigin = bodyTransform.getOrigin();
                math::Vec3f loc;
                loc.x = btOrigin.getX();
                loc.y = btOrigin.getY();
                loc.z = btOrigin.getZ();
                target->setLocation(loc);
        } 

        // set edges
        btBoxShape *shape = static_cast<btBoxShape*>(obj->getCollisionShape());
        if (shape) {
                btVector3 btv;
                math::Vec3f mv;
                for (int i = 0; i < 8; ++i) {
                        shape->getVertex(i, btv);
                        mv.x = btv.getX();
                        mv.y = btv.getY();
                        mv.z = btv.getZ();
                        target->setVertex(i, mv);
                }
        }
}

}; // namespace physics
}; // namespace skeletor

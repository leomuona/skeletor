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
        } 

        // set edges
        btBoxShape *shape = static_cast<btBoxShape*>(obj->getCollisionShape());
        if (shape) {
                btVector3 pa, pb;
                math::Vec3f mpa, mpb;
                for (int i = 0; i < 12; ++i) {
                        shape->getEdge(i, pa, pb);
                        mpa.x = pa.getX();
                        mpa.y = pa.getY();
                        mpa.z = pa.getZ();
                        mpb.x = pb.getX();
                        mpb.y = pb.getY();
                        mpb.z = pb.getZ();
                        target->setEdge(i, mpa, mpb);
                }
        }
}

}; // namespace physics
}; // namespace skeletor

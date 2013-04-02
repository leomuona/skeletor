#include "physics/bullet_objects_converter.hpp"

#include "animation/box.hpp"
#include "math/vec3.hpp"
#include "btBulletDynamicsCommon.h"

namespace skeletor {
namespace physics {

animation::Box* BulletObjectsConverter::convertBox(btCollisionObject *obj)
{
        float mass = 0;
        btRigidBody *body = btRigidBody::upcast(obj);
        if (body) {
                mass = body->getInvMass();
        } 
        animation::Box *box = new animation::Box(0, mass);

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
                        box->setEdge(i, mpa, mpb);
                }
        }

        return box;
}

}; // namespace physics
}; // namespace skeletor

#ifndef BULLET_RAGDOLL_HPP
#define BULLET_RAGDOLL_HPP

#include "math/mat4x4.hpp"
#include <vector>

class btCollisionShape;
class btDynamicsWorld;
class btRigidBody;
class btTransform;
class btTypedConstraint;

namespace skeletor {
namespace animation {

class Joint;
class SkeletonPose;

} // namespace animation
namespace physics {

class BulletRagdoll
{
public:
        BulletRagdoll(unsigned int id, btDynamicsWorld *ownerWorld,
                      animation::SkeletonPose *skeletonPose,
                      const math::Mat4x4f &transMat);
        ~BulletRagdoll();

        unsigned int getId() const;
        void setId(unsigned int id);

        btDynamicsWorld* getOwnerWorld() const;
        void setOwnerWorld(btDynamicsWorld *world);

        std::vector<btCollisionShape*> getShapes() const;
        void setShapes(std::vector<btCollisionShape*> shapes);

        std::vector<btRigidBody*> getBodies() const;
        void setBodies(std::vector<btRigidBody*> bodies);

        std::vector<btTypedConstraint*> getJoints() const;
        void setJoints(std::vector<btTypedConstraint*> joints);

private:
        unsigned int m_id;
        btDynamicsWorld *m_ownerWorld;
        
        /** bone radius, maybe changed to be bone specific in future? */
        float m_boneRadius;

        std::vector<btCollisionShape*> m_shapes;
        std::vector<btRigidBody*> m_bodies;
        std::vector<btTypedConstraint*> m_joints;

        btRigidBody* createRigidBody(float mass,
                const btTransform &startTransform, btCollisionShape *shape);
        void createJointRecursively(animation::Joint *joint,
                                    math::Mat4x4f matrix,
                                    animation::SkeletonPose *skeletonPose);
};

}; // namespace physics
}; // namespace skeletor

#endif // BULLET_RAGDOLL_HPP

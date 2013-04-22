#ifndef BULLET_RAGDOLL_HPP
#define BULLET_RAGDOLL_HPP

#include "math/mat4x4.hpp"
#include <map>

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

        std::map<std::string, btCollisionShape*> getShapes() const;

        std::map<std::string, btRigidBody*> getBodies() const;

        std::map<std::string, btTypedConstraint*> getJoints() const;

private:
        unsigned int m_id;
        btDynamicsWorld *m_ownerWorld;
        
        /** bone radius, maybe changed to be bone specific in future? */
        float m_boneRadius;

        std::map<std::string, btCollisionShape*> m_shapes;
        std::map<std::string, btRigidBody*> m_bodies;
        std::map<std::string, btTypedConstraint*> m_joints;

        btRigidBody* createRigidBody(float mass,
                const btTransform &startTransform, btCollisionShape *shape);
        void createJointRecursively(animation::Joint *joint,
                                    math::Mat4x4f matrix,
                                    animation::SkeletonPose *skeletonPose);
};

}; // namespace physics
}; // namespace skeletor

#endif // BULLET_RAGDOLL_HPP

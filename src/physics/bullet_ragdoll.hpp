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

/**
 * Ragdoll that can be used in physics calculations.
 * This is made for Bullet physics engine simulation.
 */
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

        /**
         * Get collision shapes of this ragdoll.
         *
         * @return map: key = joint ID, value = pointer to collision shape
         */
        std::map<std::string, btCollisionShape*> getShapes() const;

        /**
         * Get rigid bodies of this ragdoll.
         *
         * @return map: key = joint ID, value = pointer to rigid body
         */
        std::map<std::string, btRigidBody*> getBodies() const;

        /**
         * Get joints a.k.a. constraints of this ragdoll. Constraint is between
         * current joint and it's parent joint.
         *
         * @return map: key = joint ID, value = pointer to constraint
         */
        std::map<std::string, btTypedConstraint*> getJoints() const;

private:
        unsigned int m_id;
        
        /**
         * The world this ragdoll belongs to.
         */
        btDynamicsWorld *m_ownerWorld;
        
        /** bone radius, maybe changed to be bone specific in future? */
        float m_boneRadius;

        std::map<std::string, btCollisionShape*> m_shapes;
        std::map<std::string, btRigidBody*> m_bodies;
        std::map<std::string, btTypedConstraint*> m_joints;

        /**
         * Helper function to create bullet rigid body.
         */
        btRigidBody* createRigidBody(float mass,
                const btTransform &startTransform, btCollisionShape *shape);

        /**
         * Helper function to create joints recursively. Call with root joint
         * to begin.
         */
        void createJointRecursively(animation::Joint *joint,
                                    math::Mat4x4f matrix,
                                    animation::SkeletonPose *skeletonPose);
};

}; // namespace physics
}; // namespace skeletor

#endif // BULLET_RAGDOLL_HPP

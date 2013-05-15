#include "test/physics/bullet_objects_converter.hpp"

#include "physics/bullet_objects_converter.hpp"
#include "animation/box.hpp"
#include "math/mat4x4.hpp"

#include "btBulletDynamicsCommon.h"

#include <iostream>

namespace skeletor {
namespace test {
namespace physics {

int testBulletObjectsConverter()
{
        int result = 0;

        using namespace skeletor::physics;
        std::cout << "Starting testBulletObjectsConverter...\n";
        
        float edge = 10;
        float x = 5, y = 5, z = 5;
        float mass = 12345;

        // create compare box
        animation::Box *cmpBox = new animation::Box(1, mass);
        math::Mat4x4f m;
        m.identity();
        m.m[12] = x;
        m.m[13] = y;
        m.m[14] = z;
        cmpBox->setMultMatrix(m);

        // create bullet box
        btBoxShape *shape = new btBoxShape(btVector3(edge, edge, edge));
        btTransform transform;
        transform.setIdentity();
        transform.setOrigin(btVector3(x, y, z));
        btVector3 localInertia(0,0,0);
        shape->calculateLocalInertia(mass, localInertia);
        btDefaultMotionState *motionState = new btDefaultMotionState(transform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,
                                motionState, shape, localInertia);
        btRigidBody *bulletBox = new btRigidBody(rbInfo);

        // create test box
        animation::Box *testBox = new animation::Box(1, 1); // mass = 1

        // convert
        BulletObjectsConverter::convertBox(bulletBox, testBox);

        // compare
        math::Mat4x4f testMat = testBox->getMultMatrix();
        math::Mat4x4f cmpMat = cmpBox->getMultMatrix();
        for (int i=0; i < 16; ++i) {
                if (testMat.m[i] != cmpMat.m[i]) {
                        std::cout << "Error: Boxes' matrices differs."
                        << testMat.m[i] << " (test) vs. " << cmpMat.m[i]
                        << " (cmp).\n";
                        result = 1;
                }
        }

        delete shape;
        delete motionState;
        delete bulletBox;

        delete testBox;
        delete cmpBox;

        std::cout << "testBulletObjectsConverter done with return code " << result << ".\n";
        return result;
}

}; // namespace physics
}; // namespace test
}; // namespace skeletor


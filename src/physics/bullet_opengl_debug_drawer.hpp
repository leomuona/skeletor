#ifndef BULLET_OPENGL_DEBUG_DRAWER_HPP
#define BULLET_OPENGL_DEBUG_DRAWER_HPP

#include "btBulletDynamicsCommon.h"

namespace skeletor {
namespace physics {

class BulletOpenGLDebugDrawer : public btIDebugDraw
{
public:
        BulletOpenGLDebugDrawer();

        virtual void drawLine(const btVector3& from, const btVector3& to,
                              const btVector3& color);
        
        virtual void drawContactPoint(const btVector3& pointOnB,
                                      const btVector3& normalOnB,
                                      btScalar distance, int lifeTime,
                                      const btVector3& color);
        
        virtual void reportErrorWarning(const char* warningString);

        virtual void draw3dText(const btVector3& location, const char* textString);

        virtual void setDebugMode(int debugMode);
        virtual int getDebugMode() const;

private:
        int m_debugMode;
};

}; // namespace physics
}; // namespace skeletor

#endif // BULLET_OPENGL_DEBUG_DRAWER_HPP

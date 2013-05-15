#ifndef BULLET_OPENGL_DEBUG_DRAWER_HPP
#define BULLET_OPENGL_DEBUG_DRAWER_HPP

#include "btBulletDynamicsCommon.h"

namespace skeletor {
namespace physics {

/**
 * Drawer implementation from bullet's btIDebugDraw.
 * Used for fast and easy debugging.
 */
class BulletOpenGLDebugDrawer : public btIDebugDraw
{
public:
        BulletOpenGLDebugDrawer();

        /**
         * Draws line between two vectors in space.
         */
        virtual void drawLine(const btVector3& from, const btVector3& to,
                              const btVector3& color);
        
        /**
         * Bullet draws contact point with this.
         */
        virtual void drawContactPoint(const btVector3& pointOnB,
                                      const btVector3& normalOnB,
                                      btScalar distance, int lifeTime,
                                      const btVector3& color);
        
        /**
         * Reports error warning via std::cout.
         */
        virtual void reportErrorWarning(const char* warningString);

        /**
         * Not yet implemented. -> Does nothing.
         */
        virtual void draw3dText(const btVector3& location, const char* textString);

        virtual void setDebugMode(int debugMode);
        virtual int getDebugMode() const;

private:
        int m_debugMode;
};

}; // namespace physics
}; // namespace skeletor

#endif // BULLET_OPENGL_DEBUG_DRAWER_HPP

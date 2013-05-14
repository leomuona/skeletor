#include "physics/bullet_opengl_debug_drawer.hpp"

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>

namespace skeletor {
namespace physics {

BulletOpenGLDebugDrawer::BulletOpenGLDebugDrawer()
:m_debugMode(0)
{

}

void BulletOpenGLDebugDrawer::drawLine(const btVector3& from,
                                       const btVector3& to,
                                       const btVector3& color)
{
        glBegin(GL_LINES);
                glColor4f(color.getX(), color.getY(), color.getZ(), 1.f);
                glVertex3d(from.getX(), from.getY(), from.getZ());
                glVertex3d(to.getX(), to.getY(), to.getZ());
        glEnd();
}
        
void BulletOpenGLDebugDrawer::drawContactPoint(const btVector3& pointOnB,
                                               const btVector3& normalOnB,
                                               btScalar distance, int lifeTime,
                                               const btVector3& color)
{
        btVector3 to = pointOnB + normalOnB * distance;
        glBegin(GL_LINES);
                glColor4f(color.getX(), color.getY(), color.getZ(), 1.f);
                glVertex3d(pointOnB.getX(), pointOnB.getY(), pointOnB.getZ());
                glVertex3d(to.getX(), to.getY(), to.getZ());
        glEnd();
}
        
void BulletOpenGLDebugDrawer::reportErrorWarning(const char* warningString)
{
        std::cout << warningString << "\n";
}

void BulletOpenGLDebugDrawer::draw3dText(const btVector3& location,
                                         const char* textString)
{
        // TODO: Maybe in the future?
}

void BulletOpenGLDebugDrawer::setDebugMode(int debugMode)
{
        m_debugMode = debugMode;
}

int BulletOpenGLDebugDrawer::getDebugMode() const
{
        return m_debugMode;
}

}; // namespace physics
}; // namespace skeletor

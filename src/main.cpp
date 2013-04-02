#include <iostream>

#include "animation/box.hpp"
#include "animation/parse.hpp"
#include "animation/skeleton.hpp"
#include "animation/skeleton_pose.hpp"
#include "graphics/opengl_skeleton_renderer.hpp"
#include "graphics/camera.hpp"
#include "math/vec2.hpp"
#include "physics/bullet_physics.hpp"
#include "physics/bullet_objects_converter.hpp"

#include "btBulletDynamicsCommon.h"
#include <SDL/SDL.h>

bool mouseLeft = false;
bool mouseRight = false;
skeletor::math::Vec2f mousemotion;
skeletor::graphics::OpenGLSkeletonRenderer sr;
skeletor::graphics::Camera camera;
skeletor::physics::BulletPhysics bp;

void onMouseButtonDown(int x, int y)
{
}

void onMouseButtonUp(int x, int y)
{
}

void onMouseMotion(int x, int y)
{
	if (mouseLeft) {
		mousemotion += skeletor::math::Vec2f(-x, y);
	}
}

void onResize(int w, int h)
{
	sr.onResize(skeletor::math::Vec2i(w, h));
}

bool onEvent(const SDL_Event &event)
{
	switch (event.type) {
	case SDL_QUIT:
		return false;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE: return false;
		default:break;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			mouseLeft = true;
			onMouseButtonDown(event.button.x, event.button.y);
			break;
		case SDL_BUTTON_RIGHT:
			mouseRight = true;
			onMouseButtonDown(event.button.x, event.button.y);
			break;
		default: break;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:  mouseLeft = false;  break;
		case SDL_BUTTON_RIGHT: mouseRight = false; break;
		default: break;
		}
		break;

	case SDL_MOUSEMOTION:
		onMouseMotion(event.motion.xrel, event.motion.yrel);
		break;

	case SDL_VIDEORESIZE:
		onResize(event.resize.w, event.resize.h);
		break;
	}
	return true;
}

int main()
{
        std::cout << "Skeletor: Hello World! HYHAHEHEHEHE!\n";

	using namespace skeletor;
	animation::Skeleton *skel = animation::Parse::load("../res/astroboy_walk.dae");

	std::cout << *skel;

	animation::SkeletonPose pose;
	pose.setSkeleton(skel);

        sr.initRenderer(math::Vec2i(800, 600), 32, false, "skeletor");
	sr.addSkeleton(pose);

        bp.initPhysics();
        bp.createUniqueBox(1, math::Vec3f(0, -25, 0), 50, 0);
        btCollisionObject *btBox = bp.getCollisionObject(1);
        animation::Box *box = new animation::Box(1, 0);
        physics::BulletObjectsConverter::convertBox(btBox, box);

	bool running = true;
	float dt;
	float total_time = 0;
	unsigned int last_step = 0;
	while (running) {
		unsigned int duration = SDL_GetTicks() - last_step;
		dt = duration / 1000.f;
		total_time += dt;
		last_step = SDL_GetTicks();

		pose.apply(total_time);

		// set camera motion to zero.
		mousemotion.setZero();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			running &= onEvent(event);
		}

		// handle camera motion.
		mousemotion *= DEGREES_2_RADIANS;
		camera.onCameraMotion(mousemotion);

		sr.drawFrame(camera);
		sr.swapBuffers();
	}

        delete box;

        return 0;
}

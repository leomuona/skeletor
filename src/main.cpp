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
#include "player.hpp"

#include "btBulletDynamicsCommon.h"
#include <SDL/SDL.h>

bool mouseLeft = false;
bool mouseRight = false;
skeletor::math::Vec2f mousemotion;
skeletor::graphics::OpenGLSkeletonRenderer sr;
skeletor::Player player(skeletor::math::Vec3f(0, 0, 0), skeletor::math::Vec3f(1, 0, 0));

// wasd key states
bool wasd[4] = { false, false, false, false };

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
		case SDLK_w: wasd[0] = true; break;
		case SDLK_a: wasd[1] = true; break;
		case SDLK_s: wasd[2] = true; break;
		case SDLK_d: wasd[3] = true; break;
		default:break;
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_w: wasd[0] = false; break;
		case SDLK_a: wasd[1] = false; break;
		case SDLK_s: wasd[2] = false; break;
		case SDLK_d: wasd[3] = false; break;
		default:break;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		case SDL_BUTTON_WHEELDOWN:
			player.onCameraZoom(1.1f);
			break;
		case SDL_BUTTON_WHEELUP:
			player.onCameraZoom(0.9f);
			break;
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

skeletor::math::Vec2f getMovementVector()
{
	skeletor::math::Vec2f movementVector;
	movementVector.x += (wasd[1]) ?  1 : 0;
	movementVector.x += (wasd[3]) ? -1 : 0;
	movementVector.y += (wasd[0]) ?  1 : 0;
	movementVector.y += (wasd[2]) ? -1 : 0;
	return movementVector;
}

int main()
{
        std::cout << "Skeletor: Hello World! HYHAHEHEHEHE!\n";

	using namespace skeletor;
	animation::Skeleton *skel = animation::Parse::load("../res/astroboy_walk.dae");

	std::cout << *skel;

	animation::SkeletonPose pose;
	pose.setSkeleton(skel);
	pose.setPlayer(&player);

	physics::BulletPhysics bp;

        sr.initRenderer(math::Vec2i(800, 600), 32, false, "skeletor");
	sr.addSkeleton(pose);

        bp.initPhysics();
        bp.createUniqueBox(1, math::Vec3f(5, -5, 5), 10, 0);
        btCollisionObject *btFloorBox = bp.getCollisionObject(1);
        animation::Box *floorBox = new animation::Box(1, 0);
        physics::BulletObjectsConverter::convertBox(btFloorBox, floorBox);
        sr.addBox(*floorBox);

        bp.createUniqueBox(2, math::Vec3f(4, 10, -7), 2, 10.f);
        btCollisionObject *btTestBox1 = bp.getCollisionObject(2);
        animation::Box *testBox1 = new animation::Box(2, 10.f);
        physics::BulletObjectsConverter::convertBox(btTestBox1, testBox1);
        sr.addBox(*testBox1);

        bp.createUniqueBox(3, math::Vec3f(4, 5, -5.15f), 2, 10.f);
        btCollisionObject *btTestBox2 = bp.getCollisionObject(3);
        animation::Box *testBox2 = new animation::Box(3, 10.f);
        physics::BulletObjectsConverter::convertBox(btTestBox2, testBox2);
        sr.addBox(*testBox2);
         
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
                
                // simulate physics
                bp.stepSimulation(dt);
                physics::BulletObjectsConverter::convertBox(btTestBox1, testBox1);
                physics::BulletObjectsConverter::convertBox(btTestBox2, testBox2);

		// set camera motion to zero.
		mousemotion.setZero();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			running &= onEvent(event);
		}

		player.move(getMovementVector(), dt);

		// handle camera motion.
		mousemotion *= DEGREES_2_RADIANS;
		player.onCameraMotion(mousemotion);

		sr.drawFrame(player.getCamera());
		sr.swapBuffers();
	}

        delete floorBox;
        delete testBox1;
        delete testBox2;

        return 0;
}

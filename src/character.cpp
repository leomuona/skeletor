#include "character.hpp"
#include "animation/animation_library.hpp"
#include "animation/skeleton.hpp"
#include "animation/skeleton_pose.hpp"

#include <iostream>

namespace skeletor {

Character::Character()
	: m_xFadeStatus(kNominal)
	, m_currentPose(NULL)
	, m_xFadeStartPose(NULL)
	, m_xFadeTargetPose(NULL)
	, m_xFadeTime(0.15f)
	, m_xFadeCurrentTime(0)
	, m_internalTimer(0)
{
	using namespace animation;
	m_skeletons.insert(std::pair<std::string, Skeleton *>
		("../res/astroboy_walk_blender.dae",
		 AnimationLibrary::instance()->getSkeleton(
		 	"../res/astroboy_walk_blender.dae")));
	m_skeletons.insert(std::pair<std::string, Skeleton *>
		("../res/astroboy_stand_blender.dae",
		 AnimationLibrary::instance()->getSkeleton(
		 	"../res/astroboy_stand_blender.dae")));

	m_currentPose = new SkeletonPose;
	m_currentPose->setSkeleton(AnimationLibrary::instance()->getSkeleton("../res/astroboy_stand_blender.dae"));
}

Character::~Character()
{
	delete m_xFadeStartPose;
	delete m_xFadeTargetPose;
	delete m_currentPose;
}

void Character::beginXFade(const std::string &target)
{
	std::cout << "start xfade: " << target << std::endl;

	m_xFadeCurrentTime = 0;
	m_xFadeStatus = kFading;

	m_xFadeStartPose = new animation::SkeletonPose(*m_currentPose);

	m_xFadeTargetPose = new animation::SkeletonPose();
	m_xFadeTargetPose->setSkeleton(m_skeletons.find(target)->second);
	m_xFadeTargetPose->apply(0);
}

void Character::xFade(float dt)
{
	m_xFadeCurrentTime += dt;
	if (m_xFadeCurrentTime > m_xFadeTime) {
		endXFade(m_xFadeCurrentTime - m_xFadeTime);
	} else {
		m_currentPose->xFade(*m_xFadeStartPose, *m_xFadeTargetPose, m_xFadeCurrentTime, m_xFadeTime);
	}
}

void Character::endXFade(float dt)
{
	std::cout << "ended xfade.\n";

	m_xFadeStatus = kDone;
	m_currentPose->setSkeleton(&m_xFadeTargetPose->getSkeleton());
	m_currentPose->apply(dt);
	m_internalTimer = dt;

	delete m_xFadeStartPose;
	m_xFadeStartPose = NULL;
	delete m_xFadeTargetPose;
	m_xFadeTargetPose = NULL;
}

void Character::apply(float dt)
{
	m_internalTimer += dt;
	if (m_xFadeStatus == kFading) {
		xFade(dt);
	} else {
		m_currentPose->apply(m_internalTimer);
	}
}

}; // namespace skeletor

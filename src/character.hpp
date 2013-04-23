#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <map>
#include <string>

namespace skeletor {
namespace animation {
class Skeleton;
class SkeletonPose;
};

enum XFadeStatus
{
	kNominal,
	kFading,
	kDone,
};

/**
 * Generic character class, that contains pointers to used skeletons and holds
 * the current pose.
 *
 * Also provides the 'utils' for cross fading.
 */
class Character
{
protected:
	/**
	 * Key: uniqie string identifier - For now filename should be good.
	 * value: Skeleton also contains animations.
	 */
	std::map<std::string, animation::Skeleton *> m_skeletons; 

	/** \brief current pose. */
	animation::SkeletonPose *m_currentPose;

	/** \brief starting pose of the xfade. */
	animation::SkeletonPose *m_xFadeStartPose;

	/** \brief target skeleton pose of the xfade. */
	animation::SkeletonPose *m_xFadeTargetPose;

	float m_xFadeTime;
	float m_xFadeCurrentTime;
	float m_internalTimer;

	XFadeStatus m_xFadeStatus;
public:
	Character();
	~Character();

	/**
	 * Start the cross fade from current pose to target pose.
	 *
	 * @param target pose unique id.
	 */
	void beginXFade(const std::string &target);

	/**
	 * CrossFade from current pose to given pose.
	 *
	 * This assumes that the skeletons in m_skeletons are pritty much the
	 * same.
	 * 
	 * @param dt - delta time.
	 */
	void xFade(float dt);

	/**
	 * Marks the xfade as done.
	 *
	 * @param dt - delta time
	 */
	void endXFade(float dt);

	/**
	 * Applies the current pose to skeleton by transforming it in time,
	 * or continues the xfade.
	 *
	 * @param dt
	 */
	void apply(float dt);

	/**
	 * Get the current pose.
	 */
	const animation::SkeletonPose *getCurrentPose() const;
	animation::SkeletonPose *getCurrentPose();
};

inline const animation::SkeletonPose *Character::getCurrentPose() const
{
	return m_currentPose;
}

inline animation::SkeletonPose *Character::getCurrentPose()
{
	return m_currentPose;
}

}; // namespace skeletor

#endif // CHARACTER_HPP

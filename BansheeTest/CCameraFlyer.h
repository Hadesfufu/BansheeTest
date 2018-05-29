// A simple component that moves a Camera component attached to the same SceneObject
#include "Scene/BsComponent.h"
#include "Scene/BsSceneObject.h"
#include "Components/BsCCamera.h"
#include "Input/BsVirtualInput.h"
#include "Utility/BsTime.h"

using namespace bs;

class CCameraFlyer : public Component
{
public:
	// Basic constructor same as above
	CCameraFlyer(const HSceneObject& parent)
		:Component(parent)
	{}
private:
	// Called once when component is first added to a scene object
	void onInitialized() override
	{
		// Find the camera component we'll be influencing (assumed to be on the same scene object)
		mCamera = SO()->getComponent<CCamera>();
		// Create virtual buttons we'll be using for movement (assuming we registered them previously)
		mMoveForward = VirtualButton("Forward");
		mMoveBack = VirtualButton("Back");
		mMoveLeft = VirtualButton("Left");
		mMoveRight = VirtualButton("Right");
		mMoveUp = VirtualButton("Up");
		mMoveDown = VirtualButton("Down");
	}
	// Called every frame while the component is active
	void update() override
	{
		// Check if any movement or rotation keys are being held
		bool goingForward = gVirtualInput().isButtonHeld(mMoveForward);
		bool goingBack = gVirtualInput().isButtonHeld(mMoveBack);
		bool goingLeft = gVirtualInput().isButtonHeld(mMoveLeft);
		bool goingRight = gVirtualInput().isButtonHeld(mMoveRight);
		bool goingUp = gVirtualInput().isButtonHeld(mMoveUp);
		bool goingDown = gVirtualInput().isButtonHeld(mMoveDown);

		// If the movement button is pressed, determine direction to move in
		Vector3 direction = Vector3::ZERO;
		if (goingForward) direction += Vector3(0, 1, 0);
		if (goingBack) direction -= Vector3(0, 1, 0);
		if (goingRight) direction += Vector3(1, 0, 0);
		if (goingLeft) direction -= Vector3(1, 0, 0);
		if (goingUp) direction += Vector3(0, 0, 1);
		if (goingDown) direction -= Vector3(0, 0, 1);
		// Multiply direction with speed and move in the direction
		float frameDelta = gTime().getFrameDelta();	
		float speed = 1.0f;
		Vector3 velocity = direction * speed;
		SO()->move(velocity * frameDelta);
	}
	HCamera mCamera; // Camera component that is influenced by this component.
					 // Virtual keys we will use for movement
	VirtualButton mMoveForward;
	VirtualButton mMoveBack;
	VirtualButton mMoveLeft;
	VirtualButton mMoveRight;
	VirtualButton mMoveUp;
	VirtualButton mMoveDown;
};

typedef GameObjectHandle<CCameraFlyer> HCameraFlyer;
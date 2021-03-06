#include "BsApplication.h"
#include "BsCorePrerequisites.h"
#include "Importer/BsImporter.h"
#include "Resources/BsResources.h"
#include "Resources/BsBuiltinResources.h"
#include "Scene/BsSceneObject.h"
#include "Components/BsCCamera.h"
#include "Material/BsMaterial.h"
#include "Renderer/BsRenderable.h"
#include "Components/BsCRenderable.h"
#include "Input/BsInput.h"
#include "Debug/BsDebug.h"
#include "CCameraFlyer.h"

using namespace bs;

int main()
{
	Application::startUp(VideoMode(1280, 720), "My app", false);;

	SPtr<InputConfiguration> inputConfig = gVirtualInput().getConfiguration();

	inputConfig->registerButton("Forward", BC_W);
	inputConfig->registerButton("Forward", BC_UP);

	inputConfig->registerButton("Back", BC_S);
	inputConfig->registerButton("Back", BC_DOWN);

	inputConfig->registerButton("Left", BC_A);
	inputConfig->registerButton("Left", BC_LEFT);

	inputConfig->registerButton("Right", BC_D);
	inputConfig->registerButton("Right", BC_RIGHT);

	inputConfig->registerButton("Up", BC_Q);
	inputConfig->registerButton("Down", BC_E);

	HSceneObject cameraSO = SceneObject::create("Camera");
	HCamera camera = cameraSO->addComponent<CCamera>();
	camera->setMain(true);
	cameraSO->setPosition(Vector3(0.0f, 0.0f, 40.0f));
	cameraSO->lookAt(Vector3(0, 0, 0));
	HCameraFlyer Flyer = cameraSO->addComponent<CCameraFlyer>();


	HMesh mesh = gResources().load<Mesh>("Data/Meshes/Box.asset");
	HTexture texture = gResources().load<Texture>("Data/Textures/Black.asset");
	
	//HShader shader = gResources().load<Shader>("Data/Shaders/DebugDraw.bsl.asset");
	HShader shader = gBuiltinResources().getBuiltinShader(BuiltinShader::Standard);

	HMaterial material = Material::create(shader);

	HSceneObject renderableSO = SceneObject::create("3D object");
	HRenderable renderable = renderableSO->addComponent<CRenderable>();
	renderable->setMesh(mesh);
	renderable->setMaterial(material);
	renderableSO->setPosition(Vector3(0.0f, 0.0f, 0.0f));



	Application::instance().runMainLoop();
	Application::shutDown();
	
	return 0;
}
/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/

#include "TutorialApplication.h"

Sphere*              theBall;
//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    mCamera->setPosition(Ogre::Vector3(0, 600, 600));
    mCamera->lookAt(Ogre::Vector3(0, 0, 0));

    //make ball

    //Give it a random starting direction
    Ogre::Real x = Ogre::Math::SymmetricRandom();
    Ogre::Real y = Ogre::Math::SymmetricRandom();
    Ogre::Real z = Ogre::Math::SymmetricRandom();
    Ogre::Vector3 direction = Ogre::Vector3(x, y, z);

    Ogre::Real scale = 1.0f;
    Ogre::Real radius = 50.0f;
    //Give it a random speed
    Ogre::Real speed = Ogre::Math::RangeRandom(350.0, 800.0);
    //TODO MEMORY LEAK???
    theBall = new Sphere(mSceneMgr, direction, scale, radius, speed);

    createRoom();

    //Setting Shadow type
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    // mSceneMgr->setAmbientLight(Ogre::ColourValue(.65f, .5f, .5f));

    Ogre::Light* pointLight = mSceneMgr->createLight("PointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setDiffuseColour(0, 0.0, 1.0);
    pointLight->setSpecularColour(0, 0.0, 1.0);
    pointLight->setPosition(Ogre::Vector3(-800, -800, 800));

    Ogre::Light* pointLight2 = mSceneMgr->createLight("PointLight2");
    pointLight2->setType(Ogre::Light::LT_POINT);
    pointLight2->setDiffuseColour(1.0, 0.0, 0.0);
    pointLight2->setSpecularColour(1.0, 0.0, 0.0);
    pointLight2->setPosition(Ogre::Vector3(800, 800, -800));

    // Ogre::Light* spotLight = mSceneMgr->createLight("SpotLight");
    // spotLight->setDiffuseColour(0, 0, 1.0);
    // spotLight->setSpecularColour(0, 0, 1.0);
    // spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    // spotLight->setDirection(0, -1, 0);
    // spotLight->setPosition(Ogre::Vector3(0, -800, 0));
    // spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));


    //add more lights!
    //get a point light in there

}

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
    bool ret = BaseApplication::frameRenderingQueued(fe);
    theBall->move(fe);

    return ret;
}


void TutorialApplication::createRoom(void)
{
    // Define a floor plane mesh
    Ogre::Plane p;
    p.normal = Ogre::Vector3::UNIT_Y;
    p.d = 1000;
    Ogre::MeshManager::getSingleton().createPlane("floor",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            p, 2000, 2000, 1, 1, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

    p.normal = Ogre::Vector3::UNIT_Z;
    p.d = 1000;
    Ogre::MeshManager::getSingleton().createPlane("wallfront",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            p, 2000, 2000, 1, 1, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);

    p.normal = Ogre::Vector3::NEGATIVE_UNIT_X;
    p.d = 1000;
    Ogre::MeshManager::getSingleton().createPlane("wallright",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            p, 2000, 2000, 1, 1, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);

    p.normal = Ogre::Vector3::UNIT_X;
    p.d = 1000;
    Ogre::MeshManager::getSingleton().createPlane("wallleft",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            p, 2000, 2000, 1, 1, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);

    p.normal = Ogre::Vector3::NEGATIVE_UNIT_Z;
    p.d = 1000;
    Ogre::MeshManager::getSingleton().createPlane("wallback",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            p, 2000, 2000, 1, 1, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);

    p.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
    p.d = 1000;
    Ogre::MeshManager::getSingleton().createPlane("roof",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            p, 2000, 2000, 1, 1, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

    // Create the entities
    Ogre::Entity* ent;
    ent = mSceneMgr->createEntity("floor");
    ent->setMaterialName("Examples/BumpyMetal");
    mSceneMgr->getRootSceneNode()->attachObject(ent);
    ent->setCastShadows(false);

    ent = mSceneMgr->createEntity("wallfront");
    ent->setMaterialName("Examples/Rockwall");
    mSceneMgr->getRootSceneNode()->attachObject(ent);
    ent->setCastShadows(false);

    ent = mSceneMgr->createEntity("wallright");
    ent->setMaterialName("Examples/Rockwall");
    mSceneMgr->getRootSceneNode()->attachObject(ent);
    ent->setCastShadows(false);

    ent = mSceneMgr->createEntity("wallleft");
    ent->setMaterialName("Examples/Rockwall");
    mSceneMgr->getRootSceneNode()->attachObject(ent);
    ent->setCastShadows(false);

    ent = mSceneMgr->createEntity("wallback");
    ent->setMaterialName("Examples/Rockwall");
    mSceneMgr->getRootSceneNode()->attachObject(ent);
    ent->setCastShadows(false);

    ent = mSceneMgr->createEntity("roof");
    ent->setMaterialName("Examples/BumpyMetal");
    mSceneMgr->getRootSceneNode()->attachObject(ent);
    ent->setCastShadows(false);
}

//---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char *argv[])
#endif
{
    // Create application object
    TutorialApplication app;

    try {
        app.go();
    } catch (Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        std::cerr << "An exception has occurred: " <<
                  e.getFullDescription().c_str() << std::endl;
#endif
    }

    return 0;
}

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------

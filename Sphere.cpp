#include "Sphere.h"

Sphere::Sphere(Ogre::SceneManager* mSceneMgr, Ogre::Vector3& dir, Ogre::Real& scale, Ogre::Real& radius, Ogre::Real& speed)
{

    // sEnt = mSceneMgr->createEntity("mySphere", "sphere.mesh");
    sEnt = mSceneMgr->createEntity("mySphere", "sphere.mesh");
    // sEnt->setMaterialName("Examples/RustySteel");
    sEnt->setCastShadows(true);
    sNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("Ball");
    sNode->attachObject(sEnt);
    sNode->scale(scale, scale, scale);
    sDirection = dir;
    sDirection.normalise();
    sRadius = radius;
    sSpeed = speed;

    std::cout << sNode->getName();
}

void Sphere::move(const Ogre::FrameEvent& evt) {

    Ogre::Vector3 bPosition = sNode->getPosition();
    // std::cout << bPosition.y << std::endl;


    if (bPosition.y < -1000.0f + sRadius && sDirection.y < 0.0f) {
        sDirection.y = -sDirection.y;
    }
    if (bPosition.y > 1000.0f - sRadius && sDirection.y > 0.0f) {
        sDirection.y = -sDirection.y;
    }
    if (bPosition.z < -1000.0f + sRadius && sDirection.z < 0.0f) {
        sDirection.z = -sDirection.z;
    }
    if (bPosition.z > 1000.0f - sRadius && sDirection.z > 0.0f) {
        sDirection.z = -sDirection.z;
    }
    if (bPosition.x < -1000.0f + sRadius && sDirection.x < 0.0f)  {
        sDirection.x = -sDirection.x;
    }
    if (bPosition.x > 1000.0f - sRadius && sDirection.x > 0.0f) {
        sDirection.x = -sDirection.x;
    }

   sNode->translate(sSpeed * evt.timeSinceLastFrame * sDirection, Ogre::Node::TS_LOCAL );

}
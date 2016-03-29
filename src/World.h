//
// Created by Engin Manap on 13.02.2016.
//

#ifndef UBERGAME_WORLD_H
#define UBERGAME_WORLD_H

#include <vector>
#include "PhysicalRenderable.h"
#include "GLHelper.h"
#include <SDL2/SDL_stdinc.h>
#include "glm/glm.hpp"
#include "InputHandler.h"
#include "Camera.h"
#include "Model.h"
#include "SkyBox.h"
#include "BulletDebugDrawer.h"
#include "GUILayer.h"
#include "SDLFontManager.h"
#include <btBulletDynamicsCommon.h>

class World {
    std::vector<PhysicalRenderable*> objects;
    std::vector<GUILayer*> guiLayers;
    SkyBox* sky;
    GLHelper *glHelper;
    SDLFontManager fontManager;
    Camera camera;
    BulletDebugDrawer* debugDrawer;

    btDiscreteDynamicsWorld* dynamicsWorld;
    std::vector<btRigidBody*> rigidBodies;


    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;

public:
    World(GLHelper*);
    ~World();


    void play(Uint32, InputHandler&);
    void render();
};

#endif //UBERGAME_WORLD_H

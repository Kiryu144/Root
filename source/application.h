/* Created by David Klostermann on 31.05.2017. */
#ifndef ROOT_APPLICATION_H
#define ROOT_APPLICATION_H

#include "static/basicmesh.h"
#include "world/chunk/chunk.h"
#include "world/block/blockmesh.h"
#include "resources/resourcemanager.h"
#include "world/world/blockworld.h"

#include <THREADS/mingw.thread.h>
#include <THREADS/mingw.mutex.h>
#include <amethyst>
#include <atomic>

class Application {
private:
    bool m_keepRunning = true;

    BlockWorld* blockWorld;
    AM::Camera cam;
    AM::Debugcamera debugCam;


    std::atomic<bool> m_loadingFinished;
    void draw();
    void load(); //Threaded
public:
    Application();

    void init();
    void loop();
};


#endif

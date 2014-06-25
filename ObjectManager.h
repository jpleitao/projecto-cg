#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "common.h"
#include "Object.h"
#include "Player.h"
#include <vector>

class ObjectManager {
private:
    std::vector<Object*> opaqueObjects;
    std::vector<Object*> transparentObjects;
    std::vector<Object*> allObjects;
    Renderer* renderer;

    vec2 laserOrigin;
    vec2 laserDirection;
    std::vector<Object*> temporaryLaserObjects;


public:
    ObjectManager(Renderer* renderer);

    void setRenderer(Renderer* renderer) { this->renderer = renderer; }
    void addObject(Object* object);
    void removeObject(Object* object);

    void renderObjects();
    void collideAndFall();
    void checkLimits();
    void moveObjects();
    void processLaser();
    void processPlayer(Player* player);
    void clearLaser();

    void setLaserOrigin(vec2 o) {laserOrigin=o;}
    void setLaserDirection(vec2 d) {laserDirection=d;}
    vec2 getLaserOrigin() { return laserOrigin;}
    vec2 getLaserDirection() { return laserDirection;}
    void stopObjects();

private:
    vec2* intersectLineSegments(vec2 a, vec2 b,         vec2 c, vec2 d);
    vec2* intersectLineWithSegment(vec2 lineOrigin, vec2 direction, vec2 a, vec2 b);
    int  closestPointToSourcePoint(vec2 sourcePoint, std::vector<vec2> points);

    void processLaserFromPoint(vec2 origin,  vec2 direction, int depth=0);

};
#endif

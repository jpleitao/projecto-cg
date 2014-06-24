#include "ObjectManager.h"
#include "Renderer.h"
#include <algorithm>
#include "Line.h"
#include "Light.h"

ObjectManager::ObjectManager(Renderer* renderer) : renderer(renderer)
{}

void ObjectManager::addObject(Object* object) {
    if (object->isTransparent())
        transparentObjects.push_back(object);
    else
        opaqueObjects.push_back(object);

    allObjects.push_back(object);
}
void ObjectManager::removeObject(Object* object) {
    std::vector<Object*>* vec = &opaqueObjects;
    if ( object->isTransparent() )
        vec = &transparentObjects;

    std::vector<Object*>::iterator position = std::find(vec->begin(), vec->end(), object);
    if (position != vec->end())
        vec->erase(position);

    position = std::find(allObjects.begin(), allObjects.end(), object);
    if (position != allObjects.end())
        allObjects.erase(position);
}

void ObjectManager::renderObjects() {
    glEnable(GL_CULL_FACE);
    renderer->render(opaqueObjects);
    glDisable(GL_CULL_FACE);
    renderer->render(transparentObjects);
    glEnable(GL_CULL_FACE);
}

void ObjectManager::collideAndFall() {
    bool colide = true;
    Object* obj_to_move;
    Object* obj_colided;

    while (colide){
        
        colide = false;
        
        //Check for collisions! -- For each object test it with the ones after him
        for (int i=0;i<allObjects.size();i++){
            Object* current = allObjects[i];
            if ( !current->objectHasBoundingBox() ) continue; //Skip world objects
            colide = false;

            for (int j=i+1;j<allObjects.size();j++){
                Object* obj = allObjects[j];

                if (current->collision(obj)){
                    std::cout << "COLLISION!\n";
                    colide = true;

                    bool do_stuff = false;

                    if (obj->getIsBeingPuxed()){
                        obj_to_move = current;
                        obj_colided = obj;
                        do_stuff = true;
                    }

                    else if (current->getIsBeingPuxed()){
                        obj_to_move = obj;
                        obj_colided = current;
                        do_stuff = true;
                    }

                    if (do_stuff)
                    {
                        //Move current away
                        obj_to_move->moveAwayFrom(obj_colided);

                        //Set obj velocity - FIXME: REFACTOR
                        obj_to_move->move(true, (FACTOR * (obj_colided->getVelocityX()) ), (FACTOR * (obj_colided->getVelocityZ()) ) );
                        obj_to_move->translate(vec3( (FACTOR * (obj_colided->getVelocityX()) ),0.0f,(FACTOR * (obj_colided->getVelocityZ()) ) ));
                    }

                    //assert(0);
                }
            }

            if (!colide){
                //Object is not coliding with anything, so we can make it go down
                current->fall();
                for (int j=i+1;j<allObjects.size();j++){
                    if (current->collision(allObjects[j])){
                        std::cout << "FALSE!\n";
                        //Move the object in the opposite direction
                        current->undoFall();

                        //Stop the falling of the object
                        current->setVelocity_y(0);
                        break;
                    }
                }
            }
        }
    }
}

/*Checks if the current object is within the limits of the cenario*/
void ObjectManager::checkLimits()
{
    for (int i=0;i<allObjects.size();i++){
        Object* current = allObjects[i];

        if (!current->objectHasBoundingBox()) continue;
        
        //Check height
        if (current->getCenterY() < MIN_Y )
            current->translate(vec3(0.0f, (MIN_Y - current->getCenterY() ), 0.0f));

        else if (current->getCenterY() > MAX_Y )
            current->translate(vec3(0.0f, (MAX_Y - current->getCenterY() ), 0.0f));
        

        //Check X and Z positions. Get the maximum and minimum of each
        GLfloat max_x, min_x, max_z, min_z, current_x, current_z;

        max_x = current->getVertexAt(0)[0]; min_x = max_x; max_z = current->getVertexAt(0)[2]; min_z = max_z;

        for (int j=1;j<current->getVertexesSize();j++){

            current_x = current->getVertexAt(j)[0];
            current_z = current->getVertexAt(j)[2];

            if (current_x < min_x)
                min_x = current_x;

            else if (current_x > max_x)
                max_x = current_x;

            if (current_z < min_z)
                min_z = current_z;

            else if (current_z > max_z)
                max_z = current_z;
        }

        /*Compare the maximum and minimum values for the X and Z positions with the maximum and minimum allowed and perform
         *the required translactions*/
        if (min_x < MIN_X)
            current->translate(vec3((MIN_X - min_x),0.0f, 0.0f));

        if (max_x > MAX_X)
            current->translate(vec3((MAX_X - max_x),0.0f, 0.0f));

        if (min_z < MIN_Z)
            current->translate(vec3(0.0f,0.0f, (MIN_Z - min_z)));

        if (max_z > MAX_Z)
            current->translate(vec3(0.0f,0.0f, (MAX_Z - max_z)));
    }
}

void ObjectManager::moveObjects()
{
    for (int i=0;i<allObjects.size();i++){
        Object* current = allObjects[i];

        current->translate(vec3(current->getVelocityX(), 0.0f, current->getVelocityZ()));
    }
}

void ObjectManager::processLaser() {
    processLaserFromPoint(laserOrigin, laserDirection);
    
}

void ObjectManager::processLaserFromPoint(vec2 origin, vec2 direction, int depth) {
    if ( depth == 15 ) return;

    std::vector<vec2> candidatePoints;
    std::vector<Object*> originatingObjects;
    std::vector<std::vector<vec2> > originalLines;

    for (int i = 0; i < opaqueObjects.size(); i++ ) {
        Object* thisObj = opaqueObjects.at(i);
        if ( !thisObj->objectHasBoundingBox() || !thisObj->atLaserHeight()) continue;
        std::vector<std::vector<vec2> > lines = thisObj->getBoundingBoxLines();
/*
        for (int k = 0 ; k < lines.size(); k++) {
            std::vector<vec2> line = lines.at(k);
            printf("LINE %d ", k);
            for (int k2 = 0; k2 < line.size(); k2++) {
                printf("(%f,%f)->", line.at(k2).x, line.at(k2).y);
            }
            std::vector<Object*> objs;
            objs.push_back(new Object(new Line(vec3(line.at(0).x,LASER_Y/2,line.at(0).y), vec3(line.at(1).x,LASER_Y/2,line.at(1).y), vec3(0,1,0))));
            renderer->render(objs);
            delete objs.at(0);
            printf("\n");
        }*/

        for (int j = 0; j < lines.size(); j++) {
            vec2 lineP = lines.at(j).at(0), lineQ = lines.at(j).at(1);
            vec2* intersection = intersectLineWithSegment(origin, direction, lineP, lineQ);
            if ( intersection ) {
                candidatePoints.push_back(vec2(intersection->x,intersection->y));
                originatingObjects.push_back(thisObj);
                originalLines.push_back(lines.at(j));
                delete intersection;
            }
        }        
    }

    if ( candidatePoints.size() == 0) {
        //Must intersect a wall FIXME
        //printf("Laser not intersecting objects!\n");
        
        vec2 point = 1000.0f*direction;

        Object* l = new Object(new Line(vec3(origin.x,LASER_Y,origin.y), vec3(point.x,LASER_Y,point.y)));
        temporaryLaserObjects.push_back(l);
        addObject(l);
    } else {
        int index = closestPointToSourcePoint(origin, candidatePoints);
        vec2 point = candidatePoints.at(index);
        vec2 unit = glm::normalize(point-origin);
        vec2 lightXZ = point-0.15f*unit;

        Object* obj = originatingObjects.at(index);
        obj->setLaserLight(new Light(vec3(lightXZ.x, LASER_Y, lightXZ.y),vec3(1.0f,0.0f,0.0f)) );

        Object* l = new Object(new Line(vec3(origin.x,LASER_Y,origin.y), vec3(point.x,LASER_Y,point.y)));
        temporaryLaserObjects.push_back(l);
        addObject(l);

        vec2 originalLineP = originalLines.at(index).at(0), originalLineQ = originalLines.at(index).at(1);
        vec2 originalVec = originalLineQ - originalLineP;
        vec2 ortho1 = glm::normalize(vec2(-originalVec.y, originalVec.x));
        vec2 ortho2 = glm::normalize(vec2(originalVec.y, -originalVec.x));
        vec2 surfaceNormal = glm::dot(ortho1, unit) < 0.0f ? ortho1 : ortho2;

        vec2 reflected =  glm::reflect(unit, surfaceNormal);

        processLaserFromPoint(point-0.01f*unit, reflected, ++depth);
    }

    
}

void ObjectManager::clearLaser() {
    for (int i = 0; i < temporaryLaserObjects.size(); i++) {
        removeObject(temporaryLaserObjects.at(i));
        delete temporaryLaserObjects.at(i);        
    }
    temporaryLaserObjects.clear();
    for (int i = 0; i < allObjects.size(); i++ ) {
        allObjects.at(i)->setLaserLight(NULL);
    }
}

vec2* ObjectManager::intersectLineSegments(vec2 p1, vec2 p2,         vec2 p3, vec2 p4) {

    //printf("Intersecting (%f,%f) --- (%f,%f)\t\t(%f,%f) --- (%f,%f)\n", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y );
/*
    float A2 = p4.y - p3.y;
    float B2 = p4.x - p3.x;
    float C2 = A2*p3.x + B2*p3.y;

    float A1 = p2.x - p1.y;
    float B1 = p2.x - p1.x;
    float C1 = A1 * p1.x + B1 * p1.y;

   float det = A1*B2 - A2*B1;
   if (det == 0)
   {
        return NULL;
   }
   vec2 d = vec2((B2 * C1 - B1 * C2) / det, -(A1 * C2 - A2 * C1) / det);
   return new vec2(d);*/
    // Store the values for fast access and easy
    // equations-to-code conversion
    // 
    //if 
    double x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    double y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;
     
    double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    //printf("x1:%f,  y1:%f,   d:%f\n", x1, y1, d);
    // If d is zero, there is no intersection
    if (d == 0) {
        //printf("That determinant is zero!\n");
        return NULL;
    }
     
    // Get the x and y
    float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
    float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
     
    // Check if the x and y coordinates are within both lines
    if ( x < min(x1, x2) || x > max(x1, x2) ||
    x < min(x3, x4) || x > max(x3, x4) ) return NULL;
    if ( y < min(y1, y2) || y > max(y1, y2) ||
    y < min(y3, y4) || y > max(y3, y4) ) return NULL;
     
    //printf("Returning a value\n");
    return new vec2(x,y);
}
vec2* ObjectManager::intersectLineWithSegment(vec2 lineOrigin, vec2 direction, vec2 a, vec2 b) {
    vec2 unit =  glm::normalize(direction);

    vec2 farPoint = lineOrigin + 100.0f*unit;

    return intersectLineSegments(lineOrigin, farPoint, a, b);
}
int  ObjectManager::closestPointToSourcePoint(vec2 sourcePoint, std::vector<vec2> points) {
    //printf("HITS %d points!\n", points.size());
    int i = 0;
    ;
    float bestDist = glm::length(vec2(points.at(0) - sourcePoint));

    for ( int j = 1; j < points.size(); j++) {
        float thisDist = glm::length(vec2(points.at(j) - sourcePoint));
        //printf("->(%f,%f) - (%f,%f), thisDist = %f, best = %f\n", points.at(j).x, points.at(j).y, sourcePoint.x, sourcePoint.y, thisDist, bestDist);
        if ( thisDist < bestDist) {
            i = j;
            bestDist = thisDist;
        }
    }

    return i;
}

void ObjectManager::stopObjects()
{
    Object* current;
    for (int i=0;i<this->allObjects.size();i++){
        current = this->allObjects[i];

        //Stop the object
        current->move(false);
    }
}

//------------------------------------------------------------------------------
// FRONTIÈRES:  An interactive granular sampler.
//------------------------------------------------------------------------------
// More information is available at
//     http::/ccrma.stanford.edu/~carlsonc/256a/Borderlands/index.html
//
//
// Copyright (C) 2011  Christopher Carlson
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


//
//  CloudVis.cpp
//  Frontières
//
//  Created by Christopher Carlson on 11/15/11.
//

#include "visual/CloudVis.h"
#include "visual/GrainVis.h"
#include "visual/SampleVis.h"
#include "model/Scene.h"
#include "model/ParamCloud.h"
#include "utility/GTime.h"

// TODO avoid this
#include "interface/MyGLApplication.h"
#include "interface/MyGLWindow.h"

#include "model/Cloud.h"
// graphics includes
#include <qopengl.h>
#ifndef __APPLE__
#include <GL/glu.h>
#endif

#include <math.h>

extern CloudParams g_defaultCloudParams;

//-----------------------------------------------------------------------------------------------
// GRAPHICS
//-----------------------------------------------------------------------------------------------

CloudVis::~CloudVis()
{
    if (!isMidiVis) {
        for (int i = 0; i < g_maxMidiVoices; i++){
            delete playedCloudVisMidi[i];
        }
    }
    for (GrainVis *vis : myGrainsV)
        delete vis;
    delete myTrajectory;
}

CloudVis::CloudVis(float x, float y, unsigned int numGrainsVis,
                                 VecSceneSample *rects, bool c_isMidiVis)
{
    cout << "creation cloudvis" << endl;
    startTime = GTime::instance().sec;

    isMidiVis = c_isMidiVis;

    if (!isMidiVis)
        isPlayed = g_defaultCloudParams.activateState;

    // create MidiVis

    for (int i = 0; i < g_maxMidiVoices; i++){
        if (!isMidiVis) {
            CloudVis *l_CloudVisMidi = new CloudVis(x, y, numGrainsVis, rects, true);
            playedCloudVisMidi[i] = l_CloudVisMidi;
        }
        isPlayedCloudVisMidi[i] = false;
    }

    //initialise trajectory

    stopTrajectory();
    myTrajectory = nullptr;
    Trajectory *tr = nullptr;
    switch (g_defaultCloudParams.trajectoryType) {
    case BOUNCING:
        //tr=new Bouncing(g_defaultCloudParams.radius,g_defaultCloudParams.speed,g_defaultCloudParams.angle,x,y);
        tr=new Circular(g_defaultCloudParams.speed,x,y,g_defaultCloudParams.radius,g_defaultCloudParams.angle,0,1);
        isMoving = true;
        break;
    case CIRCULAR:
        tr=new Circular(g_defaultCloudParams.speed,x,y,g_defaultCloudParams.radius,g_defaultCloudParams.angle,
                        g_defaultCloudParams.strech,g_defaultCloudParams.progress );
        isMoving = true;
        break;
    case HYPOTROCHOID:
        tr=new Hypotrochoid(g_defaultCloudParams.speed,x,y,g_defaultCloudParams.radius,g_defaultCloudParams.radiusInt,
                            g_defaultCloudParams.expansion, g_defaultCloudParams.angle,g_defaultCloudParams.progress);
        isMoving = true;
        break;
    default :
        break;
    }

    setTrajectory(tr);

    updateCloudPosition(x, y);
    updateCloudOrigin(x, y);

    xRandExtent = g_defaultCloudParams.xRandExtent;
    yRandExtent = g_defaultCloudParams.yRandExtent;

    // init add and remove flags to false
    addFlag = false;
    removeFlag = false;

    // select on instantiation
    isSelected = true;

    // pulse frequency
    freq = 1.0f;

    // pointer to landscape visualization objects
    theLandscape = rects;

    for (int i = 0; i < numGrainsVis; i++) {
        myGrainsV.push_back(new GrainVis(gcX, gcY, isMidiVis));
    }

    numGrains = numGrainsVis;


    // visualization stuff
    minSelRad = 15.0f;
    maxSelRad = 19.0f;
    lambda = 0.997;
    selRad = minSelRad;
    targetRad = maxSelRad;
    lastDrawTime=0;

}


void CloudVis::setDuration(float dur)
{
    freq = 1000.0 / dur;
    if (!isMidiVis) {
        for (int i = 0; i < g_maxMidiVoices; i++){
            playedCloudVisMidi[i]->setDuration(dur); ;
        }
    }
}

// print information
void CloudVis::describe(std::ostream &out)
{
    out << "- X : " << getX() << "\n";
    out << "- Y : " << getY() << "\n";
    out << "- X extent : " << getXRandExtent() << "\n";
    out << "- Y extent : " << getYRandExtent() << "\n";
}

void CloudVis::registerCloud(Cloud *cloudToRegister)
{
    myCloud = cloudToRegister;
    if (!isMidiVis) {
        for (int i = 0; i < g_maxMidiVoices; i++){
            playedCloudVisMidi[i]->registerCloud(myCloud);
            playedCloudVisMidi[i]->registerCloudMidi(cloudToRegister->getMidiCloud(i));
        }
    }
}

void CloudVis::registerCloudMidi(CloudMidi *cloudMidiToRegister)
{
    myCloudMidi = cloudMidiToRegister;
}

void CloudVis::changesDone(bool done)
{
    changed_gcX= done;
    changed_gcY = done;
    changed_xRandExtent = done;
    changed_yRandExtent = done;
}

// return cloud x
float CloudVis::getX()
{
    return gcX;
}
// return cloud y
float CloudVis::getY()
{
    return gcY;
}

float CloudVis::getOriginX()
{
    return origin_gcX;
}

float CloudVis::getOriginY()
{
    return origin_gcY;
}

Trajectory* CloudVis::getTrajectory()
{
    return this->myTrajectory;
}

bool CloudVis::getIsMoving()
{
    return isMoving;
}

void CloudVis::setTrajectory(Trajectory *tr)
{
    if ((isMoving || myTrajectory != nullptr))
    {
        delete myTrajectory;
    }
    myTrajectory = tr;
    if (!isMidiVis) {
        for (int i = 0; i < g_maxMidiVoices; i++){
            cout << "set traj, i = " << i << endl;
            if (tr == nullptr) {
                Trajectory *trMidi = nullptr;
                playedCloudVisMidi[i]->setTrajectory(trMidi);
            }
            else {
                switch (tr->getType()) {
                case BOUNCING:
                {
                    //cout << "BOUNCING"<< endl;
                    Circular *trv = dynamic_cast<Circular*>(tr);
                    Circular *trMidi = nullptr;
                    trMidi = new Circular(trv->getSpeed(), trv->getOrigin().x, trv->getOrigin().y, trv->getRadius(),trv->getAngle(),0,1);
                    playedCloudVisMidi[i]->setTrajectory(trMidi);
                    break;
                }
                case CIRCULAR:
                {
                    //cout << "CIRCULAR"<< endl;
                    Circular *trv = dynamic_cast<Circular*>(tr);
                    Circular *trMidi = nullptr;
                    trMidi = new Circular(trv->getSpeed(), trv->getOrigin().x, trv->getOrigin().y, trv->getRadius(),trv->getAngle(),
                                            trv->getStrech(),trv->getProgress());
                    playedCloudVisMidi[i]->setTrajectory(trMidi);
                    break;
                }
                case HYPOTROCHOID:
                {
                    //cout << "HYPOTROCHOID"<< endl;
                    Hypotrochoid *trv = dynamic_cast<Hypotrochoid*>(tr);
                    Hypotrochoid *trMidi = nullptr;
                    trMidi = new Hypotrochoid(trv->getSpeed(),trv->getOrigin().x, trv->getOrigin().y, trv->getRadius(),trv->getRadiusInt(),
                                                trv->getExpansion(), trv->getAngle(), trv->getProgress());
                    playedCloudVisMidi[i]->setTrajectory(trMidi);
                    break;
                }
                default :
                {
                    cout << "defaut"<< endl;
                    break;
                }
                }
            }
        }
    }
    if(tr == nullptr){
        stopTrajectory();
    }
}

bool CloudVis::hasTrajectory()
{
    return myTrajectory != nullptr;
}

bool CloudVis::getIsMidiVis()
{
    return isMidiVis;
}

void CloudVis::setIsMidiVis(bool md)
{
    isMidiVis = md;
}

void CloudVis::activateMidiVis(int l_numNote, bool l_activate)
{
    if (!isMidiVis) {
        cout << "activateMidiVis, note ="<<l_numNote<<endl;
        isPlayedCloudVisMidi[l_numNote] = l_activate;
        playedCloudVisMidi[l_numNote]->setIsPlayed(l_activate);
        if (l_activate) {
            if (myTrajectory != nullptr) {
                playedCloudVisMidi[l_numNote]->startTrajectory();
            }
        }
        else
            if (myTrajectory != nullptr) {
                playedCloudVisMidi[l_numNote]->stopTrajectory();
            }
    }
}

bool CloudVis::getStateMidiVis(int l_numNote)
{
    return isPlayedCloudVisMidi[l_numNote];
}

CloudVis *CloudVis::getMidiCloudVis(int l_numNote)
{
    return playedCloudVisMidi[l_numNote];
}

bool CloudVis::getIsPlayed()
{
    return isPlayed;
}

void CloudVis::setIsPlayed(bool l_isPlayed)
{
    isPlayed = l_isPlayed;
}

void CloudVis::setTrajectoryType(int l_trajectoryType)
{
    trajectoryType = l_trajectoryType;
}

int CloudVis::getTrajectoryType()
{
    return trajectoryType;
}

void CloudVis::stopTrajectory()
{
    isMoving = false;
}

void CloudVis::startTrajectory()
{
    isMoving = true;
}

void CloudVis::restartTrajectory()
{
    if (myTrajectory != nullptr) {
        myTrajectory->restart();
        restartingTrajectory = true;
        draw();
        restartingTrajectory = false;
    }
}


void CloudVis::draw()
{
    if (isMidiVis & !isPlayed) {
        return;
    }

    double t_sec = 0;
    double dt = 0;

    t_sec = GTime::instance().sec - startTime;
    dt = t_sec - lastDrawTime;
    lastDrawTime = t_sec;
    //std::cout << "time between drawings: " <<dt<<std::endl;
    // cout << t_sec << endl;

    //computing trajectory
    pt2d pos = {0.,0.};
    //if (this->getIsMoving() && !this->isSelected){
    if (this->getIsMoving() || restartingTrajectory) {
        pos = this->myTrajectory->computeTrajectory(dt);
        updateCloudPosition(pos.x,pos.y);
    }

    // if ((g_time -last_gtime) > 50){
    glPushMatrix();
    glTranslatef((GLfloat)gcX, (GLfloat)gcY, 0.0);
    // Cloud representation

    if (isMidiVis)
        glColor4f(0.8, 0.9, 0.1, 0.4);
    else
        if (isSelected)
            glColor4f(0.1, 0.7, 0.6, 0.35);
        else
            glColor4f(0.0, 0.4, 0.7, 0.8);

    selRad = minSelRad + 0.5 * (maxSelRad - minSelRad) *
                             sin(2 * PI * (freq * t_sec + 0.125));
    if (xRandExtent >= yRandExtent)
        gluDisk(gluNewQuadric(), selRad + xRandExtent, selRad + xRandExtent + 1.0, 128, 2);
    else
        gluDisk(gluNewQuadric(), selRad + yRandExtent, selRad + yRandExtent + 1.0, 128, 2);
    glPopMatrix();
    glPushMatrix();

    // origin
    glTranslatef((GLfloat)origin_gcX, (GLfloat)origin_gcY, 0.0);

    if (!isMidiVis) {

        // Cloud origin representation

        if (isSelected)
            glColor4f(0.1, 0.7, 0.6, 0.35);
        else
            glColor4f(0.0, 0.4, 0.7, 0.8);

        gluDisk(gluNewQuadric(), selRad, selRad + 5.0, 128, 2);
        glPopMatrix();
        glPushMatrix();

        //glColor4f(0.1, 0.7, 0.6, 0.35);
        glLineWidth(2.0f);
    }
    else {
        glPopMatrix();
        glPushMatrix();

        //glColor4f(0.8, 0.9, 0.1, 0.4);
        glLineWidth(1.0f);
    }
    glBegin(GL_LINE_STRIP);
    glVertex2f(origin_gcX, origin_gcY);
    glVertex2f(gcX, gcY);
    glEnd();

    // update grain motion;
    // Individual grains
    if (isPlayed){
        for (int i = 0; i < numGrains; i++) {
            //if (isMidiVis)
                //cout << "i = " << i << endl;
            myGrainsV[i]->draw(isMidiVis);
        }
    }
    glPopMatrix();

    // draw cloudMidi
    if (!isMidiVis) {
        for (int i = 0; i < g_maxMidiVoices; i++) {
            if (isPlayedCloudVisMidi[i]) {
                cout << "drawn i =" << i << endl;
                playedCloudVisMidi[i]->draw();
            }
        }
    }

    // end point version
}


// get trigger position/volume relative to sample visuals for single grain voice
void CloudVis::getTriggerPos(unsigned int idx, double *playPos,
                                    double *playVol, float theDur)
{
    bool trigger = false;
    SampleVis *theRect = NULL;
    if (idx < myGrainsV.size()) {
        GrainVis *theGrain = myGrainsV[idx];
        // TODO: motion models
        // updateGrainPosition(idx,gcX + randf()*50.0 + randf()*(-50.0),gcY + randf()*50.0 + randf()*(-50.0));
        updateGrainPosition(idx, gcX + (randf() * xRandExtent - randf() * xRandExtent),
                            gcY + (randf() * yRandExtent - randf() * yRandExtent));
        VecSceneSample &landscape = *theLandscape;
        for (int i = 0, n = landscape.size(); i < n; i++) {
            theRect = landscape[i]->view.get();
            bool tempTrig = false;
            tempTrig = theRect->getNormedPosition(playPos, playVol, theGrain->getX(),
                                                  theGrain->getY(), i);
            if (tempTrig == true)
                trigger = true;
            // cout << "playvol: " << *playPos << ", playpos: " << *playVol << endl;
        }
        if (trigger == true) {
            theGrain->trigger(theDur);
        }
    }
}


// rand cloud size
void CloudVis::setFixedXRandExtent(float X)
{
    xRandExtent = X;
    if (!isMidiVis) {
        for (int i = 0; i < g_maxMidiVoices; i++){
            playedCloudVisMidi[i]->setFixedXRandExtent(X); ;
        }
    }
    changed_xRandExtent = true;
}

void CloudVis::setFixedYRandExtent(float Y)
{
    yRandExtent = Y;
    if (!isMidiVis) {
        for (int i = 0; i < g_maxMidiVoices; i++){
            playedCloudVisMidi[i]->setFixedYRandExtent(Y); ;
        }
    }
    changed_yRandExtent = true;
}
void CloudVis::setFixedRandExtent(float X, float Y)
{
    setFixedXRandExtent(X);
    setFixedYRandExtent(Y);
}

bool CloudVis::changedXRandExtent()
{
    return changed_xRandExtent;
}

bool CloudVis::changedYRandExtent()
{
    return changed_yRandExtent;
}

void CloudVis::setXRandExtent(float mouseX)
{
    xRandExtent = fabs(mouseX - gcX);
    if (xRandExtent < 2.0f)
        xRandExtent = 0.0f;
    if (!isMidiVis) {
        for (int i = 0; i < g_maxMidiVoices; i++){
            playedCloudVisMidi[i]->setXRandExtent(mouseX); ;
        }
    }
    changed_xRandExtent = true;
}
void CloudVis::setYRandExtent(float mouseY)
{
    yRandExtent = fabs(mouseY - gcY);
    if (yRandExtent < 2.0f)
        yRandExtent = 0.0f;
    if (!isMidiVis) {
        for (int i = 0; i < g_maxMidiVoices; i++){
            playedCloudVisMidi[i]->setYRandExtent(mouseY); ;
        }
    }
    changed_yRandExtent = true;
}
void CloudVis::setRandExtent(float mouseX, float mouseY)
{
    setXRandExtent(mouseX);
    setYRandExtent(mouseY);
}
float CloudVis::getXRandExtent()
{
    return xRandExtent;
}
float CloudVis::getYRandExtent()
{
    return yRandExtent;
}
void CloudVis::setX(int newX)
{
    updateCloudOrigin(newX, gcY);
}

void CloudVis::setY(int newY)
{
    updateCloudOrigin(gcX, newY);
}

void CloudVis::setOriginX(int newX)
{
    updateCloudOrigin(newX, origin_gcY);
}

void CloudVis::setOriginY(int newY)
{
    updateCloudOrigin(origin_gcX, newY);
}

bool CloudVis::changedGcX()
{
    return changed_gcX;
}

bool CloudVis::changedGcY()
{
    return changed_gcY;
}
//
void CloudVis::updateCloudPosition(float newX, float newY)
{
    float xDiff = newX - gcX;
    float yDiff = newY - gcY;
    gcX = newX;
    gcY = newY;
    for (int i = 0; i < myGrainsV.size(); i++) {
        float newGrainX = myGrainsV[i]->getX() + xDiff;
        float newGrainY = myGrainsV[i]->getY() + yDiff;
        myGrainsV[i]->moveTo(newGrainX, newGrainY);
    }
    //changed_gcX = true;
    //changed_gcY = true;
}

void CloudVis::updateCloudOrigin(float newOriginX, float newOriginY)
{
    //cout << "updatecloudorigin" << endl;
    //cout << "origin x = " << newOriginX << endl;
    //cout << "origin y = " << newOriginY << endl;
    origin_gcX = newOriginX;
    origin_gcY = newOriginY;
    if (myTrajectory != nullptr){
        myTrajectory->setOrigin(newOriginX, newOriginY);
    }
    if (!isMidiVis) {
        for (int i = 0; i < g_maxMidiVoices; i++){
            playedCloudVisMidi[i]->updateCloudOrigin(newOriginX, newOriginY);
        }
    }
    changed_gcX = true;
    changed_gcY = true;
}

void CloudVis::updateCloudTrajectoryPosition(float newX, float newY)
{
    float xDiff = newX - gcX;
    float yDiff = newY - gcY;
    origin_gcX = newX - gcX;
    origin_gcY = newX - gcY;
    for (int i = 0; i < myGrainsV.size(); i++) {
        float newGrainX = myGrainsV[i]->getX() + xDiff;
        float newGrainY = myGrainsV[i]->getY() + yDiff;
        myGrainsV[i]->moveTo(newGrainX, newGrainY);
    }
}

void CloudVis::updateGrainPosition(int idx, float x, float y)
{
    if (idx < numGrains)
        myGrainsV[idx]->moveTo(x, y);
}

void CloudVis::setState(bool l_state)
{
    isOn = l_state;
}


// check mouse selection
bool CloudVis::select(float x, float y)
{
    float xdiff = x - origin_gcX;
    float ydiff = y - origin_gcY;

    if (sqrt(xdiff * xdiff + ydiff * ydiff) < maxSelRad)
        return true;
    else
        return false;
}

void CloudVis::setSelectState(bool selectState)
{
    isSelected = selectState;
    if (!isMidiVis) {
        for (int i = 0; i < g_maxMidiVoices; i++){
            playedCloudVisMidi[i]->setSelectState(selectState); ;
        }
    }
}

void CloudVis::addGrain()
{
    //    addFlag = true;
    myGrainsV.push_back(new GrainVis(gcX, gcY, isMidiVis));
    numGrains = myGrainsV.size();
}

// remove a grain from the cloud (visualization only)
void CloudVis::removeGrain()
{
    //    removeFlag = true;
    if (numGrains > 1) {
        // delete object
        delete myGrainsV[myGrainsV.size() - 1];
        myGrainsV.pop_back();
        numGrains = myGrainsV.size();
    }
}

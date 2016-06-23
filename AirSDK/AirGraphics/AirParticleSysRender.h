//
//  AirParticleSysRender.h
//  AirCpp
//
//  Created by Penghao on 14-3-18.
//  Copyright (c) 2014年 PengHao. All rights reserved.
//

#ifndef __AirCpp__AirParticleSysRender__
#define __AirCpp__AirParticleSysRender__

#include <iostream>
#include "AirGraphicsRender.h"
namespace AirCpp {
    
    class AirParticleSysRender : public AirGraphicsRender {
    protected:
        bool b_configed;
        
        //hardware performers
        GLint performLevel;
        GLint particleNum;
        GLint particleSize;
        
        // Attribute locations
        GLint  lifetimeLoc;
        GLint  startPositionLoc;
        GLint  endPositionLoc;
        // Uniform location
        GLint timeLoc;
        GLint centerPositionLoc;
        GLint samplerLoc;
        
        // Texture handle
        GLuint textureId;
        // Particle vertex data
        GLfloat *particleData;
        // Current time
        GLfloat time;
        
        GLint colorLoc;
        GLfloat color[4];
        
        // buffer data
        GLuint offset;
        GLuint vboIds;
        
        GLint projectionLoc;
        GLfloat projection[16];
        
        // speed
        GLfloat slowdown;
        AirVector3D speed;
        
        
    public:
        AirParticleSysRender():
        b_configed(false),
        performLevel(0),
        particleNum(0),
        particleSize(0),
        lifetimeLoc(0),
        startPositionLoc(0),
        endPositionLoc(0),
        timeLoc(0),
        centerPositionLoc(0),
        samplerLoc(0),
        textureId(0),
        particleData(NULL),
        time(0),
        colorLoc(0),
        offset(0),
        vboIds(0),
        projectionLoc(0)
        {
            
        }
        
    };
}

#endif /* defined(__AirCpp__AirParticleSysRender__) */

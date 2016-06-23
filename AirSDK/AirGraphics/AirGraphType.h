//
//  AirGraphType.h
//  AirOtaGraghics
//
//  Created by 彭浩 on 13-6-21.
//  Copyright (c) 2013年 hao peng. All rights reserved.
//

#ifndef AirGraghics_AirGraphType_h
#define AirGraghics_AirGraphType_h
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#define PI 3.1415926535897932384626433832795f
//法线向量
typedef struct {
    GLfloat v[4];
}AGVector;

typedef struct
{
    GLfloat   m[4][4];
    
} AGMatrix;

class AGPoint
{
protected:
    GLfloat v[3];
    AGPoint(GLfloat x, GLfloat y, GLfloat z)
    {
        v[0] = x;
        v[1] = y;
        v[2] = z;
    }
};

class AGMatrix1
{
public:
    GLfloat m[16];
};


typedef AGMatrix AGCoordinate;

#endif

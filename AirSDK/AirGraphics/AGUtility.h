//
//  AirGraphUtility.h
//  AirGraghics
//
//  Created by 彭浩 on 13-6-21.
//  Copyright (c) 2013年 hao peng. All rights reserved.
//

#ifndef AirGraghics_AirGraphUtility_h
#define AirGraghics_AirGraphUtility_h
#include <math.h>
#include <OpenGLES/ES2/gl.h>
#include "AirGraphType.h"
#ifdef __cplusplus

extern "C" {
#endif
    
#define AIRGRAPHUTILITY_API
    //AGMatrix translate
    void AIRGRAPHUTILITY_API AirGraphScale(AGMatrix *result, GLfloat sx, GLfloat sy, GLfloat sz);
    void AIRGRAPHUTILITY_API AirGraphTranslate(AGMatrix *result, GLfloat tx, GLfloat ty, GLfloat tz);
    void AIRGRAPHUTILITY_API AirGraphRotate(AGMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
    void AIRGRAPHUTILITY_API AirGraphFrustum(AGMatrix *result, float left, float right, float bottom, float top, float nearZ, float farZ);
    void AIRGRAPHUTILITY_API AirGraphPerspective(AGMatrix *result, float fovy, float aspect, float nearZ, float farZ);
    void AIRGRAPHUTILITY_API AirGraphOrtho(AGMatrix *result, float left, float right, float bottom, float top, float nearZ, float farZ);
    
    void AIRGRAPHUTILITY_API AGMatrixMultiply(AGMatrix *result, AGMatrix *srcA, AGMatrix *srcB);
    void AIRGRAPHUTILITY_API AGMatrixLoadIdentity(AGMatrix *result);
    
#ifdef __cplusplus
    
}
#endif


#endif

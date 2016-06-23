//
//  AirGraphicsUtility.h
//  AirCpp
//
//  Created by Penghao on 14-3-17.
//  Copyright (c) 2014年 PengHao. All rights reserved.
//

#ifndef __AirCpp__AirGraphicsUtility__
#define __AirCpp__AirGraphicsUtility__

#include <iostream>
#include "OpenGLInclude.h"
#ifdef __cplusplus

extern "C" {
#endif
    
#define AIR_OPENGL_API
    extern char*  OSLoadPNG ( const char *fileName, int *width, int *height );
    GLuint AIR_OPENGL_API AirGraphLoadShader ( GLenum type, const char *shaderSrc );
    int AIR_OPENGL_API AirGraphLoadProgram ( const char *vertShaderSrc, const char *fragShaderSrc );
    char* AIR_OPENGL_API AirGraphLoadPNG ( const char *fileName, int *width, int *height );
    char * AIR_OPENGL_API AirGraphReadRenderFile(const char *filename);
    GLuint AIR_OPENGL_API loadTexture(const GLchar *fileName);
    void AIR_OPENGL_API logMessage ( const char *formatStr, ... );
    void AIR_OPENGL_API AirGraphPerror();
#ifdef __cplusplus
    
}
#endif

#endif /* defined(__AirCpp__AirGraphicsUtility__) */

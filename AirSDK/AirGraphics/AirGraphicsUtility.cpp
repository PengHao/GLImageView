//
//  AirGraphicsUtility.cpp
//  AirCpp
//
//  Created by Penghao on 14-3-17.
//  Copyright (c) 2014年 PengHao. All rights reserved.
//

#include "AirGraphicsUtility.h"
#include "../AirDefined.h"

GLuint AIR_OPENGL_API AirGraphLoadShader ( GLenum type, const char *shaderSrc )
{
    GLuint shader;
    GLint compiled;
    // Create the shader object
    shader = glCreateShader ( type );
    if ( shader == 0 )
        return 0;
    // Load the shader source
    glShaderSource ( shader, 1, &shaderSrc, NULL );
    // Compile the shader
    glCompileShader ( shader );
    
    GLint infoLen = 0;
    
    glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );
    if ( infoLen > 0 )
    {
        char* infoLog = (char*)malloc (sizeof(char) * infoLen );
        glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );
        DebugLog("\n%s", infoLog);
        free ( infoLog );
    }
    
    // Check the compile status
    glGetShaderiv ( shader, GL_COMPILE_STATUS, &compiled );
    if ( !compiled )
    {
        glDeleteShader ( shader );
        return 0;
    }
    return shader;
    
}

char * AIR_OPENGL_API AirGraphReadRenderFile(const char *filename){
    char *str;
    FILE *fp;
    if((fp=fopen(filename,"r"))==NULL)
    {
        return NULL;
    }
    //can not bigger than 2TB
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    str = (char *)malloc(sizeof(char)*filesize+1);
    fseek(fp, 0, SEEK_SET);
    fread(str, 1, filesize, fp);
    *(str+filesize)='\0';
    fclose(fp);
    return str;
}

int AIR_OPENGL_API AirGraphLoadProgram ( const char *vertShaderSrc, const char *fragShaderSrc )
{
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;
    
    // Load the vertex/fragment shaders
    vertexShader = AirGraphLoadShader ( GL_VERTEX_SHADER, vertShaderSrc );
    if ( vertexShader == 0 )
        return -1;
    
    fragmentShader = AirGraphLoadShader ( GL_FRAGMENT_SHADER, fragShaderSrc );
    if ( fragmentShader == 0 )
    {
        glDeleteShader( vertexShader );
        return -1;
    }
    
    // Create the program object
    programObject = glCreateProgram ( );
    
    if ( programObject == 0 )
        return -1;
    
    glAttachShader ( programObject, vertexShader );
    glAttachShader ( programObject, fragmentShader );
    
    // Link the program
    glLinkProgram ( programObject );
    
    // Check the link status
    glGetProgramiv ( programObject, GL_LINK_STATUS, &linked );
    
    if ( !linked )
    {
        GLint infoLen = 0;
        
        glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );
        
        if ( infoLen > 1 )
        {
            char* infoLog = (char* )malloc (sizeof(char) * infoLen );
            
            glGetProgramInfoLog ( programObject, infoLen, NULL, infoLog );
            free ( infoLog );
        }
        
        glDeleteProgram ( programObject );
        return -1;
    }
    
    // Free up no longer needed shader resources
    glDeleteShader ( vertexShader );
    glDeleteShader ( fragmentShader );
    
    return programObject;
}


GLuint loadTexture(const GLchar *fileName)
{
    int width, height;
    char *buffer = OSLoadPNG ( fileName, &width, &height );
    GLuint texId;
    
    if ( buffer == NULL )
    {
        logMessage ( "Error loading (%s) image.\n", fileName );
        return 0;
    }
    
    glGenTextures ( 1, &texId );
    glBindTexture ( GL_TEXTURE_2D, texId );
    glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    free ( buffer );
    return texId;
}

void logMessage ( const char *formatStr, ... )
{
    va_list params;
    char buf[BUFSIZ];
    va_start ( params, formatStr );
    vsprintf ( buf, formatStr, params );
    printf ( "%s", buf );
    va_end ( params );
}


void AirGraphPerror(){
    
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        printf("Error glGetError: glError: 0x%04X", err);
    }
};
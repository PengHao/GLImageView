//
//  AirImageRender.hpp
//  GLImageView
//
//  Created by 彭浩 on 16/5/5.
//  Copyright © 2016年 彭浩. All rights reserved.
//

#ifndef AirImageRender_hpp
#define AirImageRender_hpp

#include <stdio.h>
#include "AirGraphType.h"
#include "AGUtility.h"
#include "AirGraphicsRender.h"

namespace AirCpp {
    
    extern GLfloat cubeVerts[12];
    
    extern GLfloat cubeTex[8];
    
    extern GLushort cubeIndices[6];
    
    class AirImageRender: public AirGraphicsRender {
    protected:
        // Attribute locations
        GLint  positionLoc;
        // Uniform locations
        GLint  mvpLoc;
        // Rotation angle
        GLfloat   angle;
        
        // Texture handle
        GLuint textureId;
        GLint texCoordLoc;
        GLint textureLoc;
        
        GLint frameLoc;
        GLint offsetLoc;
        AGVector frame;
        AGMatrix modelview;
        AGMatrix  mvpMatrix;
        void bind_shader_atrribute(GLuint shaderProgram) {
            // Get the attribute locations
            positionLoc = glGetAttribLocation ( shaderProgram, "a_position" );
            // Get the uniform locations
            mvpLoc = glGetUniformLocation( shaderProgram, "u_mvpMatrix" );
            texCoordLoc = glGetAttribLocation(shaderProgram, "TexCoordIn");
            textureLoc = glGetUniformLocation(shaderProgram, "s_texture");
            frameLoc = glGetUniformLocation(shaderProgram, "a_frame");
            offsetLoc = glGetUniformLocation(shaderProgram, "offset");
        }
    public:
        GLfloat offsetx;
        GLfloat offsety;
        AirImageRender():
        offsetx(0),
        offsety(0)
        {
            positionLoc = -1;
            mvpLoc = -1;
            angle = 45.0f;
        }
        
        ~AirImageRender() {
            glDeleteTextures(1, &textureId);
        }
        
        int init(const std::string &vshfilename_, const std::string &fshfilename_, const AGVector &frame_, const GLfloat &wWidth, const GLfloat &wHeight, const std::string &texturePath) {
            int rs = AirGraphicsRender::init(vshfilename_, fshfilename_);
            if (rs == 0) {
                textureId = loadTexture(texturePath.c_str());
                if ( textureId <= 0 )
                {
                    printf("load texture faild");
                    return -1;
                }
                frame = frame_;
                
                
                float sw = frame_.v[2] / wWidth; //scale w
                float sh = frame_.v[3] / wHeight; //scale h
                float sy = sh;
                float sx = sw;
                
                offsetx = (wWidth/2.0 - frame_.v[0])/wWidth * 2 - sx ;
                offsety = (wHeight/2.0 - frame_.v[1])/wHeight * 2 - sy;
                
                AGMatrixLoadIdentity( &modelview );
                AirGraphScale(&modelview, sx, sy, 1.0f);
            }
            return rs;
        }
        
        void update(bool forcibly)
        {
            AGMatrix perspective;
            float    aspect;
            
            // Compute a rotation angle based on time to rotate the cube
            angle += ( 0.05 * 40.0f );
            if( angle >= 360.0f )
                angle -= 360.0f;
            // Compute the window aspect ratio
            aspect = 1.0;
            
            // Generate a perspective matrix with a 60 degree FOV
            AGMatrixLoadIdentity( &perspective );
            
            // Translate away from the viewer
            AirGraphTranslate( &modelview, 0.0, 0.0, -1.0 );
            
            // Rotate the cube
//            AirGraphRotate( &modelview, angle, 1.0, 0.0, 1.0 );
            
            // Compute the final MVP by multiplying the
            // modevleiw and perspective matrices together
            AGMatrixMultiply( &mvpMatrix, &modelview, &perspective );
            AirGraphicsRender::update(forcibly);
        }
        
        void render(){
            glUseProgram (program);
            glEnable ( GL_TEXTURE_2D );
//            glEnable(GL_LINE_SMOOTH);
//            glEnable(GL_BLEND);
//            glEnable(GL_ALPHA);
//            
//            glAlphaFunc(GL_GREATER,0.0);
//            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            // Bind the texture
            
            
            glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), cubeTex);
            glEnableVertexAttribArray(texCoordLoc);
            glActiveTexture ( GL_TEXTURE1);
            glBindTexture ( GL_TEXTURE_2D, textureId );
            glUniform1i ( textureLoc, 1);
            
            // Load the vertex position
            glVertexAttribPointer (positionLoc, 3, GL_FLOAT,
                                   GL_FALSE, 3 * sizeof(GLfloat), cubeVerts );
            glEnableVertexAttribArray (positionLoc );
            
            // Load the MVP matrix
            glUniform4f(frameLoc, frame.v[0], frame.v[1], frame.v[2], frame.v[3]);
            glUniform2f(offsetLoc, offsetx, offsety);
            glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &mvpMatrix.m[0][0] );
            
            // Draw the cube
            glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, cubeIndices );
            glDisableVertexAttribArray(positionLoc);
            glDisableVertexAttribArray(texCoordLoc);
            glDisableVertexAttribArray(offsetLoc);
            
            AirGraphicsRender::render();
        }
    };
    
}

#endif /* AirImageRender_hpp */

//
//  AirGraphicsRender.h
//  AirCpp
//
//  Created by Penghao on 14-2-7.
//  Copyright (c) 2014年 PengHao.

//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#ifndef __AirCpp__AirGraphicsRender__
#define __AirCpp__AirGraphicsRender__

#include <iostream>
#include <list>
#include "../AirMath/AirMath.h"
#include "AirGraphicsUtility.h"

namespace AirCpp{
    using namespace AirMath::LinearAlgebra;
    typedef AirPoint3 AirCoordinate3D;
    typedef AirPoint3 AirPosition3D;
    typedef AirPoint3 AirVector3D;
    
    
    class AirGraphicsRender {
    protected:
        AirCoordinate3D *coordinate;
        AirPosition3D *center;
        bool needUpdate;
        std::list<AirGraphicsRender *> render_array;
        GLfloat program;
        std::string vshfilename;
        std::string fshfilename;
    
    public:
        
        int init(const std::string &vshfilename_, const std::string &fshfilename_, AirCoordinate3D *coordinate_ = nullptr, AirPosition3D *center_ = nullptr ){
            coordinate = coordinate_;
            center = center_;
            vshfilename = vshfilename_;
            fshfilename = fshfilename_;
            compire_shader_program();
            return 0;
        }
        
        void add_render(AirGraphicsRender *_render){
            render_array.push_back(_render);
        };
        
        void remove_render(AirGraphicsRender *_render){
            render_array.remove(_render);
        }
        
        void remove_all() {
            for (std::list<AirGraphicsRender *>::iterator it = render_array.begin(); it != render_array.end(); ++it) {
                delete *it;
            }
            render_array.clear();
        }
        
        virtual void bind_shader_atrribute(GLuint shaderProgram){
            
        }
        
        virtual void getUniformLocations(void){
            
        }
        
        
        virtual int compire_shader_program(){
            char *vsh_str, *fsh_str;
            vsh_str = AirGraphReadRenderFile(vshfilename.c_str());
            fsh_str = AirGraphReadRenderFile(fshfilename.c_str());
            if (!vsh_str||!fsh_str) {
                printf("file text is null");
                return -1;
            }
            _airGraphLoadProgram ( vsh_str, fsh_str );
            if (program == -1) {
                return -1;
            }
            free(vsh_str);
            free(fsh_str);
            return 0;
        }
        
        
    public:
        
        
        virtual ~AirGraphicsRender(void){
            delete coordinate;
            delete center;
        };
        
        virtual void update(bool forcibly)
        {
            for(auto &it : render_array) {
                it->update(forcibly);
            }
        }
        
        virtual void render()
        {
            for(auto &it : render_array) {
                it->render();
            }
        }
        
        
    protected:
        
        void _airGraphLoadProgram ( const char *vertShaderSrc, const char *fragShaderSrc )
        {
            GLuint vertexShader;
            GLuint fragmentShader;
            GLint linked;
            
            // Load the vertex/fragment shaders
            vertexShader = AirGraphLoadShader ( GL_VERTEX_SHADER, vertShaderSrc );
            if ( vertexShader == 0 ){
                program = -1;
                return;
            }
            fragmentShader = AirGraphLoadShader ( GL_FRAGMENT_SHADER, fragShaderSrc );
            if ( fragmentShader == 0 )
            {
                glDeleteShader( vertexShader );
                program = -1;
                return;
            }
            
            // Create the program object
            program = glCreateProgram ( );
            
            if ( program == 0 ){
                program = -1;
                return;
            }
            
            glAttachShader ( program, vertexShader );
            glAttachShader ( program, fragmentShader );
            
            // Link the program
            glLinkProgram ( program );
            
            //must bind attribute before link
            bind_shader_atrribute(program);
            
            // Check the link status
            glGetProgramiv ( program, GL_LINK_STATUS, &linked );
            
            if ( !linked )
            {
                GLint infoLen = 0;
                
                glGetProgramiv ( program, GL_INFO_LOG_LENGTH, &infoLen );
                
                if ( infoLen > 1 )
                {
                    char* infoLog = (char* )malloc (sizeof(char) * infoLen );
                    
                    glGetProgramInfoLog ( program, infoLen, NULL, infoLog );
                    free ( infoLog );
                }
                
                glDeleteProgram ( program );
                program = -1;
                return;
            }
            //bind buffer after link
            getUniformLocations();
            // Free up no longer needed shader resources
            glDeleteShader ( vertexShader );
            glDeleteShader ( fragmentShader );
        }
    };
}
#endif /* defined(__AirCpp__AirGraphicsRender__) */

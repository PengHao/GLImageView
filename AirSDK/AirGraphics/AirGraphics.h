//
//  AirGraphics.h
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

#ifndef AirCpp_AirGraphics_h
#define AirCpp_AirGraphics_h
#include "OpenGLInclude.h"
#include "AirGraphicsContext/AirGraphicsContext.h"
namespace AirCpp{
    typedef enum{
        NONE = 0,
        USE_DEPTH_BUFFER = 0x0001,
        USE_STENCIL_BUFFER = 0x0003
    }GraghicConfig;
    
    class AirGraphics {
    private:
        GLuint view_render_buffer;
        GLuint view_frame_buffer;
        GLuint depth_render_buffer;
        GLuint stencil_render_buffer;
        GraghicConfig params;
        AirGraphicsContext *p_context;
    private:
        int creat_frame_buffer(){
            glGenFramebuffers(1, &view_frame_buffer);
            glGenRenderbuffers(1, &view_render_buffer);
            glBindFramebuffer(GL_FRAMEBUFFER, view_frame_buffer);
            glBindRenderbuffer(GL_RENDERBUFFER, view_render_buffer);
            
            if (p_context->bind_to_drawable_storage()==-1) {
                return -1;
            }
            
            glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &window_width);
            glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &window_height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, view_render_buffer);
            
            if ((USE_DEPTH_BUFFER&params)==USE_DEPTH_BUFFER) {
                glGenRenderbuffers(1, &depth_render_buffer);
                glBindRenderbuffer(GL_RENDERBUFFER, depth_render_buffer);
                glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, window_width, window_height);
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_render_buffer);
            }
            if ((USE_STENCIL_BUFFER&params)==USE_STENCIL_BUFFER)
            {
                //现有代码有一些错误，无法启用stencil buffer
                glGenRenderbuffers(1, &stencil_render_buffer);
                glBindRenderbuffer(GL_RENDERBUFFER, stencil_render_buffer);
                glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, window_width, window_height);
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, stencil_render_buffer);
            }
            
            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
                printf("failed to make complete framebuffer object %x  \n", glCheckFramebufferStatus(GL_FRAMEBUFFER));
                return -1;
            }else{
                return 0;
            }
        }
        
        void destroyFramebuffer(void){
            glDeleteFramebuffers(1, &view_frame_buffer);
            view_frame_buffer = 0;
            glDeleteRenderbuffers(1, &view_render_buffer);
            view_render_buffer = 0;
            
            if(depth_render_buffer) {
                glDeleteRenderbuffers(1, &depth_render_buffer);
                depth_render_buffer = 0;
            }
            
            if(stencil_render_buffer) {
                glDeleteRenderbuffers(1, &stencil_render_buffer);
                stencil_render_buffer = 0;
            }
        }
    public:
        GLint window_width;
        GLint window_height;
        int init(GraghicConfig params_, AirGraphicsContext *p_context_){
            
            view_frame_buffer = 0;
            view_render_buffer = 0;
            depth_render_buffer = 0;
            stencil_render_buffer = 0;
            p_context = p_context_;
            params = params_;
            
            if(p_context->active() != 0){
                return -1;
            }else{
                if(creat_frame_buffer() != -1){
                    glViewport(0, 0, window_width, window_height);
                    return 0;
                }else{
                    return -1;
                }
            }
        }
        
        int active(){
            return p_context->active();
        }
        
        void ready_to_update_buffer(void) {
            //更新到系统相关硬件上
            active();
            glBindFramebuffer(GL_FRAMEBUFFER, view_frame_buffer);
            
            glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &window_width);
            glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &window_height);
            
            glViewport(0, 0, window_width, window_height);
            const float polygonOffsetFactor = -1.0f;
            const float polygonOffsetUnits = -2.0f;
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//            glDepthFunc(GL_LEQUAL);
//            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(polygonOffsetFactor, polygonOffsetUnits);
        }
        
        void display_render_buffer(){
            glBindRenderbuffer(GL_RENDERBUFFER, view_render_buffer);
            p_context->display_content();
        }
    };
}

#endif

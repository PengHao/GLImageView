//
//  AirImageRender.cpp
//  GLImageView
//
//  Created by 彭浩 on 16/5/5.
//  Copyright © 2016年 彭浩. All rights reserved.
//

#include "AirImageRender.hpp"


namespace AirCpp {
    
    GLfloat cubeVerts[12] =
    {
        1.0f,  1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
    };
    
    GLfloat cubeTex[8] =
    {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
    };
    
    GLushort cubeIndices[6] =
    {
        0, 1, 2,
        0, 2, 3,
    };
}
//
//  AirGraphicsScene.h
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

#ifndef __AirCpp__AirGraphicsScene__
#define __AirCpp__AirGraphicsScene__

#include <iostream>
#include "AirGraphicsRender.h"
#include "AirGraphics.h"
namespace AirCpp{
    class AirGraphicsScene
    {
    public:
        AirGraphicsScene(){
            graghics = NULL;
            p_rootObject = NULL;
        };
        
        
        virtual ~AirGraphicsScene(){
//            release(p_rootObject);
//            release(graghics);
        };
        
        int init(AirGraphics *graghics_, AirGraphicsRender * _rootObject){
            if (_rootObject == NULL) {
                return -1;
            }
            p_rootObject = _rootObject;
            graghics = graghics_;
            return 0;
        }

        /**
         *	@brief	update the node and children node
         *	@param 	forcibly 	true: must be updated false: update the node if needed;
         */
        void rend(bool forcibly){
            assert(graghics != NULL);
            assert(p_rootObject != NULL);
            graghics->ready_to_update_buffer();
            p_rootObject->update(forcibly);
            p_rootObject->render();
            graghics->display_render_buffer();
        };
        
    protected:
        /**
         *	@brief	node data
         */
        AirGraphics *graghics;
        AirGraphicsRender * p_rootObject;
    };
}
#endif /* defined(__AirCpp__AirGraphicsScene__) */

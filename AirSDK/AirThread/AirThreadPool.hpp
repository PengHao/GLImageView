//
//  AirThreadPool.hpp
//  kxmovie
//
//  Created by penghao on 16/1/25.
//
//

#ifndef AirThreadPool_hpp
#define AirThreadPool_hpp

#include <stdio.h>
#include "../AirContainer/AirArray.h"
#include "AirThread.h"
namespace AirCpp {
    class AirThreadPool : public AirObject
    {
    protected:
        
        static AirMutableArray<AirThread> threads;
        static int max_thread_count;
    public:
        static AirThread *main_thread(){ return nullptr;};
        static AirThread *get_free_thread(){ return nullptr;};
    };
 
}
#endif /* AirThreadPool_hpp */

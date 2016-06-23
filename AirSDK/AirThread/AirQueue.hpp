//
//  AirQueue.hpp
//  kxmovie
//
//  Created by penghao on 16/1/25.
//
//

#ifndef AirQueue_hpp
#define AirQueue_hpp

#include <AirObject/AirObject.h>
#include <AirContainer/AirArray.h>
#include <stdio.h>
#include <functional>
#include <AirThread/AirOperation.h>

#define FINISHED 0x001

namespace AirCpp {
    class AirQueue : public AirObject {
        friend class AirThread;
        
    private:
        AirMutableArray<AirOperation> *operation_list;
        
        void pushOperation(AirOperation *operation);
        
    protected:
        
        AirOperation *head_operation() {
            return operation_list->last_object();
        }
        
        void remove_operation(AirOperation * o) {
            operation_list->remove_object(o);
        }
        
    public:
        
        AirQueue(){
            operation_list  = new AirMutableArray<AirOperation>();
        };
        
        virtual ~AirQueue(){
            release(operation_list);
        };
    };
}

#endif /* AirQueue_hpp */

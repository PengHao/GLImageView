//
//  AirHttpServer.h
//  AirCpp
//
//  Created by Penghao on 14-4-4.
//  Copyright (c) 2014年 PengHao. All rights reserved.
//

#ifndef __AirCpp__AirHttpServer__
#define __AirCpp__AirHttpServer__

#include <iostream>
#include "../../AirIO/AirHttp/AirHttpConnect.h"
#include "../../AirContainer/AirArray.h"
#include "../../AirIO/AirSocketServer.h"

namespace AirCpp {
    class AirHttpServer : public AirSocketServer{
    protected:
        
        AirMutableArray<AirHttpConnect<AirHttpServer> > *connect_array;
    public:
        int init(int port ,int domainType, int dataType, int protocol){
            socket_listener = new AirFreeBSDSocketListener<AirSocketServer>(this);
            if (socket_listener->init(domainType, dataType, protocol, 30) < 0) {
                delete socket_listener;
                socket_listener = NULL;
                return -1;
            }
            if (socket_listener->listen_port(port, 20) < 0) {
                delete socket_listener;
                socket_listener = NULL;
                return -1;
            }
            connect_array = new AirMutableArray<AirHttpConnect<AirHttpServer> >();
            return 0;
        };
        
        
        virtual void handle_connect_request(int *socket_handle, sockaddr *client_addr){
            printf("handle_connect_request \n");
            AirHttpConnect<AirHttpServer> *conn = new AirHttpConnect<AirHttpServer>();
            if (conn->init(socket_handle, this)==0) {
                conn->active();
                connect_array->add_object(conn);
            }
            release(conn);
        }
        
        void recevied_finished(AirHttpConnect<AirHttpServer> *connect, const void *context){
//            AirMutableData *data = &connect->http_response->response_data;
            printf("\n ====http head==== \n");
            connect->http_response->response_header.decs();
            printf("\n ====http boddy==== \n");
//            for (int i = 0 ; i < data->count(); ++i) {
//                char * tp = air_str_ncpy((char *)(*data)[i]->c_data, (*data)[i]->length);
//                printf("%s", tp);
//                free(tp);
//            }
        }
    };
    
}
#endif /* defined(__AirCpp__AirHttpServer__) */

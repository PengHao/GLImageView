//
//  AirFreeBSDSocketServer.h
//  AirCpp
//
//  Created by Penghao on 14-4-11.
//  Copyright (c) 2014年 PengHao. All rights reserved.
//

#ifndef __AirCpp__AirFreeBSDSocketServer__
#define __AirCpp__AirFreeBSDSocketServer__

#include <iostream>
#include <map>

#include <sys/event.h>
#include "AirSocketServer.h"
using namespace std;

namespace AirCpp{
    class AirFreeBSDSocketServer : public AirSocketServer{
    protected:
        struct kevent ev[MAX_THREAD_NUM];
        struct timespec ts = { 10, 0 }, ts1 = {0,0};
        int kq[MAX_THREAD_NUM];
        map<int , AirSocketConnect<AirSocketServer> *> connect_map[MAX_THREAD_NUM];
    public:
        //call back
        AirFreeBSDSocketServer(){
            for (int i = 0; i < MAX_THREAD_NUM; ++i) {
                kq[i] = kqueue();
            }
        }
        
        virtual void *recevie_data(void *index){
            while (true) {
                switch (kevent(kq[*(int *)index], NULL, 0, &ev[*(int *)index], 1, &ts )) {
                    case -1:
                        printf("kevent(3)");
                        break;
                    case 0:
                        printf("connect time out\n");
//                        EV_SET( &ev[*(int *)index], (int)ev[*(int *)index].ident, EVFILT_READ|EVFILT_WRITE, EV_DELETE|EV_DISABLE, 0,0,0);
//                        connect_map[*(int *)index][(int)ev[*(int *)index].ident]->close();
//                        connect_map[*(int *)index].erase((int)ev[*(int *)index].ident);
                        continue;
                    default:
                        connect_map[*(int *)index][(int)ev[*(int *)index].ident]->read_data((int)ev[*(int *)index].ident);
                        continue;
                }
            }
        }
        
        virtual void handle_connect_request(int *socket_handle, sockaddr *client_addr){
            printf("handle_connect_request %d\n", *socket_handle);
            AirSocketConnect<AirSocketServer> *conn = new AirSocketConnect<AirSocketServer>();
            if (conn->init(socket_handle, this)==0) {
                for (int i = 0; i < MAX_THREAD_NUM; ++i) {
                    if (connect_map[i].size()<MAX_OPER_PER_THREAD) {
                        connect_map[i].insert(pair<int , AirSocketConnect<AirSocketServer> *>(*socket_handle,retain(conn)));
                        EV_SET( &ev[i], *socket_handle, EVFILT_READ|EVFILT_WRITE, EV_ADD|EV_ENABLE, 0,0,0);
                        kevent(kq[i], &ev[i], 1, NULL, 0, &ts1);
                        break;
                    }
                }
            }
            release(conn);
        }
    };
}

#endif /* defined(__AirCpp__AirFreeBSDSocketServer__) */

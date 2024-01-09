#include <stdio.h>
#include <string.h>
#include <chrono>
#include <thread>
#include <iostream>
#include "socket_can.h"

/*
 * sudo ip link add vcan0 type vcan
 * sudo ip link set vcan0 up
 */

void TxThread()
{
    /*Open Socket CAN Channel
     * vcan0 interface name
     * 500000 baud rate
     */
    socketcan::SocketCAN* sock = socketcan::SocketCAN::OpenChannel("vcan0", 500000);

    while (1)
    {
        if(sock->SendFrame(0x555, (unsigned char*)"Hello", 5))
        {
            perror("Write");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    delete sock;
}

void RxThread()
{
    socketcan::SocketCAN* sock = socketcan::SocketCAN::OpenChannel("vcan0", 500000);
    struct can_frame rxFrame;

    while (1)
    {
       if(sock->ReceiveFrame(rxFrame) < 0)
       {
           perror("Read error");
       }

       std::cout<<"0x"<<rxFrame.can_id<<" ["<<(int)rxFrame.can_dlc<<"] "<<std::hex;

       for (int i = 0; i < rxFrame.can_dlc; i++)
           std::cout<<(int)rxFrame.data[i]<<std::hex<<" ";

       std::cout<<"\n";
    }
    delete sock;
}

int main(int argc, char **argv)
{
    std::cout<<"C++ CAN Socket"<<std::endl;

    std::thread txThread = std::thread(TxThread);
    std::thread rxThread = std::thread(RxThread);

    while(1)
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    return 0;
}

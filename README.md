# socket-can-wrapper-cpp

A C++ wrapper for socket can library

## ![test status](https://github.com/shashiwakale/socket-can-wrapper-cpp/actions/workflows/c-cpp.yml/badge.svg)

## Build Instruction

```bash
$ git clone https://github.com/shashiwakale/socket-can-wrapper-cpp.git
$ cd socket-can-wrapper-cpp
$ make
```

## Add Virtual CAN Interface in Linux

```bash
$ sudo ip link add vcan0 type vcan
$ sudo ip link set vcan0 up
```

## Run the binary

```bash
$ ./socket_can
```
## API Usage

### Send CAN Frame

```cpp
#include "socket_can.h"

int main(int argc, char** argv)
{
    /*Open CAN Channel*/
    socketcan::SocketCAN* sock = socketcan::SocketCAN::OpenChannel("vcan0", 500000);

    /*Send Frame*/
    if(sock->SendFrame(0x555, (unsigned char*)"Hello", 5))
    {
        perror("Write");
    }

    delete sock;
}
```

### Receive CAN Frame

```cpp
#include "socket_can.h"

int main(int argc, char** argv)
{
    /*Open CAN Channel*/
    socketcan::SocketCAN* sock = socketcan::SocketCAN::OpenChannel("vcan0", 500000);

    /*CAN Frame*/
    struct can_frame rxFrame;

    /*Receive Frame*/
    if(sock->ReceiveFrame(rxFrame) < 0)
    {
        perror("Read error");
    }
    else
    {
        std::cout<<"0x"<<rxFrame.can_id<<" ["<<(int)rxFrame.can_dlc<<"] "<<std::hex;

        for (int i = 0; i < rxFrame.can_dlc; i++)
        {
            std::cout<<(int)rxFrame.data[i]<<std::hex<<" ";
        }

        std::cout<<"\n";
    }
    delete sock;
}
```

## License
[MIT](https://github.com/shashiwakale/socket-can-wrapper-cpp/blob/main/LICENSE)
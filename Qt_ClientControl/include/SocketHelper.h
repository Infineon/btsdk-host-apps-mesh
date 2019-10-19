#pragma once
#include "ThreadHelper.h"
#ifndef WIN32
#include <sys/types.h>
#include <sys/socket.h>
typedef unsigned char UINT8;
typedef unsigned char BYTE;
typedef unsigned short UINT16;
typedef unsigned char *LPBYTE;
typedef int SOCKET;
#endif
//**************************************************************************************************
//*** Definitions for Socket Comm
//**************************************************************************************************
typedef struct
{
    UINT8   pkt_type;
    UINT8   data[1200];
} tSCRIPT_PKT;

//
// Serial Bus class, use this class to read/write from/to the serial bus device
//
class SocketHelper : public ThreadHelper
{
public:
    static int SOCK_PORT_NUM;
    SocketHelper();
    virtual ~SocketHelper();
    static SocketHelper* GetInstance();

    // oopen serialbus driver to access device
    void SetOpenPort(int port);
    void sendToHost(UINT16 type, LPBYTE pData, DWORD len);
protected:
    virtual BOOL Begin();
    virtual BOOL CleanUp();
    virtual BOOL Process();
private:
    static SocketHelper _socketHelper;
    // read data from device
    DWORD Read(LPBYTE b, DWORD dwLen);
    DWORD ReadNewHciPacket(BYTE* pu8Buffer, int bufLen, int * pOffset);
    DWORD Write(LPBYTE b, DWORD dwLen);
    int CallWicedHciApi(UINT8* data, UINT8 len);
    int read_script_pct(char *pPkt);
    DWORD hci_control_proc_rx_cmd(BYTE* p_buffer, DWORD length);
public:
    // write data to device
    DWORD SendWicedCommand(UINT16 command, LPBYTE b, DWORD dwLen);

    BOOL IsOpened();

private:
    int m_nPortNumber;
    SOCKET  m_ListenSocket;
    SOCKET  m_ClientSocket;
};

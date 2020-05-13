#include "stdafx.h"
#include "ControlComm.h"
#include "hci_control_api.h"

extern void Log(WCHAR* _Format, ...);
extern "C" void ods(char* fmt_str, ...);

#define APP_UDP_PORT 9877
#define UDP_BUFFER_SIZE 1500

class ClsStopWatch
{
public:
    ClsStopWatch()
    {
    }

    void Start()
    {
        GetSystemTimeAsFileTime(&sft);

    }

    __int64 Stop()
    {
        GetSystemTimeAsFileTime(&eft);

        sli.LowPart = sft.dwLowDateTime;
        sli.HighPart = sft.dwHighDateTime;
        eli.LowPart = eft.dwLowDateTime;
        eli.HighPart = eft.dwHighDateTime;

        long long int dif = eli.QuadPart - sli.QuadPart;
        __int64 dftDuration = dif / 10000L;
        return dftDuration;
    }

private:
    FILETIME sft;
    FILETIME eft;
    SYSTEMTIME sst;
    SYSTEMTIME est;
    LARGE_INTEGER sli;
    LARGE_INTEGER eli;
};




DWORD WINAPI UDPServerReceiveThread(LPVOID lpdwThreadParam);

BOOL SetupUDPServer();

DWORD WINAPI UDPServerReceiveThread(LPVOID lpdwThreadParam);

void StopUDPServer();

BOOL SetupUDPClientSocket(char* pipstr);
/*
Function:   SendMessageToUDPServer
Parameters: p_msg - message buffer that needs to be send to the UDP Server
            len - length of the buffer
Usage:
            char fieldval[80];
            GetDlgItemTextA(m_hWnd, IDC_TC_NET_LEVEL_TRX_PDU, fieldval, sizeof(fieldval));
            SendMessageToUDPServer((char*)fieldval, strlen(fieldval));
*/
BOOL SendMessageToUDPServer(char* p_msg, UINT len);

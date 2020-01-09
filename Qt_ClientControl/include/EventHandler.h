#pragma once
#include "stdafx.h"
#include <string>
using namespace std;

typedef enum _state
{
    STATE_IDLE,
    STATE_LOCAL_GET_COMPOSITION_DATA,
    STATE_LOCAL_ADD_APPLICATION_KEY,
    STATE_LOCAL_BIND_MODELS,
    STATE_REMOTE_GET_COMPOSITION_DATA,
    STATE_REMOTE_ADD_APPLICATION_KEY,
    STATE_REMOTE_BIND_MODELS
} MESH_STATE;

class CEventHandler
{
public:
    CEventHandler();
    virtual void ProcessData(DWORD opcode, LPBYTE p_data, DWORD len);
    void TraceHciPkt(BYTE type, BYTE *buffer, USHORT length);

protected:
    SOCKET log_sock = INVALID_SOCKET;

private:
    MESH_STATE m_state;
    string p_local_composition_data;
    string p_remote_composition_data;
    static int initialized;
//    void ProcessCoreProvisionEnd(LPBYTE p_data, DWORD len);
//    void ProcessDescriptorStatus(LPBYTE p_data, DWORD len);
    void ProcessScanCapabilitiesStatus(LPBYTE p_data, DWORD len);
    void ProcessScanStatus(LPBYTE p_data, DWORD len);
    void ProcessScanReport(LPBYTE p_data, DWORD len);
    void ProcessProxyDeviceNetworkData(LPBYTE p_data, DWORD len);
    void ProcessProvisionEnd(LPBYTE p_data, DWORD len);
    void ProcessProvisionLinkStatus(LPBYTE p_data, DWORD len);
    void ProcessProvisionDeviceCapabilities(LPBYTE p_data, DWORD len);
    void ProcessProvisionOobDataRequest(LPBYTE p_data, DWORD len);
    void ProcessNodeResetStatus(LPBYTE p_data, DWORD len);
    void ProcessCompositionDataStatus(LPBYTE p_data, DWORD len);
    void ProcessFriendStatus(LPBYTE p_data, DWORD len);
    void ProcessKeyRefreshPhaseStatus(LPBYTE p_data, DWORD len);
    void ProcessGattProxyStatus(LPBYTE p_data, DWORD len);
    void ProcessRelayStatus(LPBYTE p_data, DWORD len);
    void ProcessDefaultTtlStatus(LPBYTE p_data, DWORD len);
    void ProcessBeaconStatus(LPBYTE p_data, DWORD len);
    void ProcessModelPublicationStatus(LPBYTE p_data, DWORD len);
    void ProcessModelSubscriptionStatus(LPBYTE p_data, DWORD len);
    void ProcessModelSubscriptionList(LPBYTE p_data, DWORD len);
    void ProcessNetKeyStatus(LPBYTE p_data, DWORD len);
    void ProcessNetKeyList(LPBYTE p_data, DWORD len);
    void ProcessAppKeyStatus(LPBYTE p_data, DWORD len);
    void ProcessAppKeyList(LPBYTE p_data, DWORD len);
    void ProcessModelAppStatus(LPBYTE p_data, DWORD len);
    void ProcessModelAppList(LPBYTE p_data, DWORD len);
    void ProcessNodeIdentityStatus(LPBYTE p_data, DWORD len);
    void ProcessHearbeatSubscriptionStatus(LPBYTE p_data, DWORD len);
    void ProcessHearbeatPublicationStatus(LPBYTE p_data, DWORD len);
    void ProcessNetworkTransmitParamsStatus(LPBYTE p_data, DWORD len);
    void ProcessHealthCurrentStatus(LPBYTE p_data, DWORD len);
    void ProcessHealthFaultStatus(LPBYTE p_data, DWORD len);
    void ProcessHealthPeriodStatus(LPBYTE p_data, DWORD len);
    void ProcessHealthAttentionStatus(LPBYTE p_data, DWORD len);
    void ProcessLpnPollTimeoutStatus(LPBYTE p_data, DWORD len);
    void ProcessProxyFilterStatus(LPBYTE p_data, DWORD len);
};

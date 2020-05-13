#pragma once

#include "ClientControl.h"
#include "ControlComm.h"

#define IDT_SEND_VENDOR_DATA 2
#define SEND_VENDOR_DATA_INTERVAL 4000

// CMeshPerformance dialog

class CMeshPerformance : public CPropertyPage
{
    DECLARE_DYNAMIC(CMeshPerformance)

public:
    CMeshPerformance();
    virtual ~CMeshPerformance();
    void OnCancel();
    void SetDlgItemHex(DWORD id, DWORD val);
    DWORD GetHexValue(DWORD id, LPBYTE buf, DWORD buf_size);
    DWORD GetHexValueInt(DWORD id);

    CListBox* m_trace;

    BOOL m_bConnected;
    BOOL m_bPerfTestRunning;
    BOOL m_bLocalDisableNtwkRetransmit;

    void DisplayCurrentGroup();

    void ProcessVendorSpecificData(LPBYTE p_data, DWORD len);
    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MESH_PERF };
#endif


protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

    DECLARE_MESSAGE_MAP()

public:
    virtual BOOL OnSetActive();
    afx_msg void OnClose();
    afx_msg void OnBnClickedClearTrace();

    void SendVendorData();
    void OnBnClickedVsData();

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedVsPerfTest();
    afx_msg void OnBnClickedVsPerfTestStop();

    afx_msg void OnTimer(UINT_PTR nIDEvent);

    LRESULT OnAddVendorModel(WPARAM wparam, LPARAM lparam);

    int m_timer_count;
    int m_max_iterations;
    int m_packet_len;
    afx_msg void OnBnClickedMeshSetAdvTxPower();
    afx_msg void OnCbnSelchangePerfControlDevice();
    afx_msg void OnBnClickedVsPerfShowResults();

    void SyncControlDevices();

    void InitTestResults(int test_id);
    afx_msg void OnBnClickedMeshSetNtwkRetransmit();
    afx_msg void OnBnClickedMeshSetAdvTxPowerAll();
    afx_msg void OnBnClickedMeshSetNtwkRetransmitAll();
};

extern CClientControlApp theApp;

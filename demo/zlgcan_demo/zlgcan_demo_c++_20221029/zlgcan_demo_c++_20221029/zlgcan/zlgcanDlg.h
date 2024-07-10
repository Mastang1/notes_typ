
// zlgcanDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "zlgcan/zlgcan.h"
#include "afxcmn.h"

// Cusbcanfdx00udemoDlg 对话框
class CZlgcanDlg : public CDialog
{
// 构造
public:
	CZlgcanDlg(CWnd* pParent = NULL);	// 标准构造函数
// 对话框数据
	enum { IDD = IDD_ZLGCANDEMO_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	void OnRecv();
// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnCbnSelchangeComboDevice();
	afx_msg void OnCbnSelchangeComboNetMode();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonInitcan();
	afx_msg void OnBnClickedButtonStartcan();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonClear();
    afx_msg void OnBnClickedButtonGetTxAvailable();
    afx_msg void OnBnClickedButtonClearTxQueue();
    afx_msg void OnBnClickedCheckDelaySendMode();
    afx_msg void OnBnClickedButtonGetSendMode();
    afx_msg void OnBnClickedButtonAutosendStart();
    afx_msg void OnBnClickedButtonAutosendStop();
    afx_msg void OnBnClickedButtonStopSingleAutosend();
    afx_msg void OnBnClickedButtonAddAutosend();

	DECLARE_MESSAGE_MAP()
private:
	void InitCombobox(int ctrl_id, int start, int end, int current);
	void EnableCtrl(BOOL opened);
	BOOL SetCustomBaudrate();
	BOOL SetTransmitType();
    BOOL SetResistanceEnable();
    BOOL SetBaudrate();
	BOOL SetCanfdBaudrate();
	static UINT WINAPI OnDataRecv(LPVOID data);
	void AddData(const ZCAN_Receive_Data* data, UINT len);
	void AddData(const ZCAN_ReceiveFD_Data* data, UINT len);
    void AddData(const ZCAN_Transmit_Data* data, UINT len);
    void AddData(const ZCAN_TransmitFD_Data* data, UINT len);
	void AddData(const CString& data);
    void SetCtrlStateDelaySend(BOOL delay_send, BOOL delay_send_mode, BOOL get_send_mode);
    BOOL IsNetCAN(UINT type );
    BOOL IsNetCANFD(UINT type );
    BOOL IsNetTCP(UINT type );
    BOOL IsNetUDP(UINT type );
    void SetAutoSendCtrlState(BOOL support_can, BOOL support_canfd, BOOL support_index, BOOL support_single_cancel, BOOL support_get_autosend_list);
    void GetViewCANFrame(ZCAN_Transmit_Data& can_data, BOOL add_delay_flag);
    void GetViewCANFrame(ZCAN_TransmitFD_Data& canfd_data, BOOL add_delay_flag);
    void AddAutosendCan(int nEnable);
    void AddAutosendCanfd(int nEnable);

private:
	int device_type_index_;
	int device_index_;
	int channel_index_;
	int work_mode_index_;
	int baud_index_;
	int abit_baud_index_;
	int dbit_baud_index_;
	BOOL custom_baud_enable_;
    BOOL resistance_enable_;
	int frame_type_index_;
	int protocol_index_;
	int canfd_exp_index_;
	int send_type_index_;
    int net_mode_index_;
	CListBox data_recv_list_;
	CString acc_code_;
	CString acc_mask_;
	CString id_;
	CString datas_;
	CString custom_baudrate_;
	CComboBox ctrl_device_type_;
	CComboBox ctrl_device_index_;
	CComboBox ctrl_channel_index_;
	DEVICE_HANDLE device_handle_;
	CHANNEL_HANDLE channel_handle_;
	IProperty* property_;
	BOOL start_;
	CButton ctrl_open_device_;
	CButton ctrl_int_can_;
	CButton ctrl_start_can_;
	CButton ctrl_close_device_;
	BOOL device_opened_;
	int filter_mode_;
    CComboBox m_comboAbit;
    CComboBox m_comboDbit;
    int send_count_once_;
    int frm_delay_time_;
    BOOL frm_delay_flag_;
    CButton ctrl_delay_send_mode_;
    BOOL    support_delay_send_;            //设备是否支持队列发送
    BOOL    support_delay_send_mode_;       //设备队列发送是否需要设置队列发送模式,USBCANFD系列，PCIECANFD系列设备需要设置发送模式才可以进行队列发送
    BOOL    support_get_send_mode_;         //设备是否支持查询当前模式
    int auto_send_index_;
    int auto_send_period_;
    CSpinButtonCtrl m_spinAutSendIndex;
    CEdit m_editAutoSendIndex;
public:
    afx_msg void OnBnClickedButtonGetDevAutosend();
	afx_msg void OnCbnSelchangeComboDeviceIndex();
};

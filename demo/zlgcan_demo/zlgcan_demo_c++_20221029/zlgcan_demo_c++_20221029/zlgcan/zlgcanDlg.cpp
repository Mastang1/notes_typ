
// zlgcanDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <process.h>
#include "zlgcanDemo.h"
#include "zlgcanDlg.h"
#include "zlgcan/zlgcan.h"
#include "utility.h"
#include "zcloudDlg.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TMP_BUFFER_LEN      1000

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// Cusbcanfdx00udemoDlg �Ի���

CZlgcanDlg::CZlgcanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZlgcanDlg::IDD, pParent)
	, device_type_index_(0)
	, device_index_(0)
	, channel_index_(0)
	, work_mode_index_(0)
	, abit_baud_index_(0)
	, dbit_baud_index_(0)
	, custom_baud_enable_(FALSE)
	, resistance_enable_(TRUE)
	, frame_type_index_(0)
	, protocol_index_(1)
	, canfd_exp_index_(1)
	, send_type_index_(0)
	, acc_code_(_T("00000000"))
	, acc_mask_(_T("FFFFFFFF"))
	, id_(_T("00000001"))
	, datas_(_T("00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63"))
	, custom_baudrate_(_T(""))
	, filter_mode_(1)
    , net_mode_index_(0)
    , baud_index_(0)
    , send_count_once_(10)
    , frm_delay_time_(1000)
    , frm_delay_flag_(FALSE)
    , auto_send_index_(0)
    , auto_send_period_(1000)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	device_opened_ = FALSE;
	start_ = FALSE;
    property_ = NULL;
    support_delay_send_ = FALSE;
    support_delay_send_mode_ = FALSE;
    support_get_send_mode_ = FALSE;
}

void CZlgcanDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_CBIndex(pDX, IDC_COMBO_DEVICE, device_type_index_);
    DDX_CBIndex(pDX, IDC_COMBO_DEVICE_INDEX, device_index_);
    DDX_CBIndex(pDX, IDC_COMBO_CHANNEL_INDEX, channel_index_);
    DDX_CBIndex(pDX, IDC_COMBO_DEVICE_INDEX2, work_mode_index_);
    DDX_CBIndex(pDX, IDC_COMBO_ABIT, abit_baud_index_);
    DDX_CBIndex(pDX, IDC_COMBO_ABIT2, dbit_baud_index_);
    DDX_CBIndex(pDX, IDC_COMBO_BAUD, baud_index_);
    DDX_Check(pDX, IDC_CHECK_CUSTOM_BAUDRATE, custom_baud_enable_);
    DDX_Check(pDX, IDC_CHECK_RESISTANCE, resistance_enable_);
    DDX_CBIndex(pDX, IDC_COMBO_FRAME_TYPE, frame_type_index_);
    DDX_CBIndex(pDX, IDC_COMBO_PROTOCOL, protocol_index_);
    DDX_CBIndex(pDX, IDC_COMBO_CANFD_EXP, canfd_exp_index_);
    DDX_CBIndex(pDX, IDC_COMBO_SEND_TYPE, send_type_index_);
    DDX_Control(pDX, IDC_LIST1, data_recv_list_);
    DDX_Text(pDX, IDC_EDIT_ACC_CODE, acc_code_);
    DDV_MaxChars(pDX, acc_code_, 8);
    DDX_Text(pDX, IDC_EDIT_ACC_MASK, acc_mask_);
    DDV_MaxChars(pDX, acc_mask_, 8);
    DDX_Text(pDX, IDC_EDIT_FILTER_START2, id_);
    DDV_MaxChars(pDX, id_, 8);
    DDX_Text(pDX, IDC_EDIT_FILTER_START3, datas_);
    DDX_Control(pDX, IDC_COMBO_DEVICE, ctrl_device_type_);
    DDX_Control(pDX, IDC_COMBO_DEVICE_INDEX, ctrl_device_index_);
    DDX_Control(pDX, IDC_COMBO_CHANNEL_INDEX, ctrl_channel_index_);
    DDX_Text(pDX, IDC_EDIT_CUSTOM_BAUDRATE, custom_baudrate_);
    DDX_Control(pDX, IDC_BUTTON_OPEN, ctrl_open_device_);
    DDX_Control(pDX, IDC_BUTTON_INITCAN, ctrl_int_can_);
    DDX_Control(pDX, IDC_BUTTON_STARTCAN, ctrl_start_can_);
    DDX_Control(pDX, IDC_BUTTON_CLOSE, ctrl_close_device_);
    DDX_CBIndex(pDX, IDC_COMBO_FILTER_MODE, filter_mode_);
    DDX_CBIndex(pDX, IDC_COMBO_NET_MODE, net_mode_index_);
    DDX_Control(pDX, IDC_COMBO_ABIT, m_comboAbit);
    DDX_Control(pDX, IDC_COMBO_ABIT2, m_comboDbit);
    DDX_Text(pDX, IDC_EDIT_SEND_ONCE, send_count_once_);
    DDX_Text(pDX, IDC_EDIT_TIME, frm_delay_time_);
    DDV_MinMaxInt(pDX, frm_delay_time_, 0, 65535);
    DDX_Check(pDX, IDC_CHECK_DELAY_SEND_FLAG, frm_delay_flag_);
    DDV_MinMaxInt(pDX, send_count_once_, 1, 10000);
    DDX_Control(pDX, IDC_CHECK_DELAY_SEND_MODE, ctrl_delay_send_mode_);
    DDX_Text(pDX, IDC_EDIT_AUTOSEND_INDEX, auto_send_index_);
    DDX_Text(pDX, IDC_EDIT_AUTOSEND_TIME_PERIOD, auto_send_period_);
    DDX_Control(pDX, IDC_SPIN_AUTOSEND_INDEX, m_spinAutSendIndex);
    DDX_Control(pDX, IDC_EDIT_AUTOSEND_INDEX, m_editAutoSendIndex);
}

BEGIN_MESSAGE_MAP(CZlgcanDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CZlgcanDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_INITCAN, &CZlgcanDlg::OnBnClickedButtonInitcan)
	ON_BN_CLICKED(IDC_BUTTON_STARTCAN, &CZlgcanDlg::OnBnClickedButtonStartcan)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CZlgcanDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CZlgcanDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CZlgcanDlg::OnBnClickedButtonSend)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICE, &CZlgcanDlg::OnCbnSelchangeComboDevice)
	ON_CBN_SELCHANGE(IDC_COMBO_NET_MODE, &CZlgcanDlg::OnCbnSelchangeComboNetMode)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CZlgcanDlg::OnBnClickedButtonClear)
    ON_BN_CLICKED(IDC_BUTTON_GET_TX_AVAILABLE, &CZlgcanDlg::OnBnClickedButtonGetTxAvailable)
    ON_BN_CLICKED(IDC_BUTTON_CLEAR_TX_QUEUE, &CZlgcanDlg::OnBnClickedButtonClearTxQueue)
    ON_BN_CLICKED(IDC_CHECK_DELAY_SEND_MODE, &CZlgcanDlg::OnBnClickedCheckDelaySendMode)
    ON_BN_CLICKED(IDC_BUTTON_GET_SEND_MODE, &CZlgcanDlg::OnBnClickedButtonGetSendMode)
    ON_BN_CLICKED(IDC_BUTTON_AUTOSEND_START, &CZlgcanDlg::OnBnClickedButtonAutosendStart)
    ON_BN_CLICKED(IDC_BUTTON_AUTOSEND_STOP, &CZlgcanDlg::OnBnClickedButtonAutosendStop)
    ON_BN_CLICKED(IDC_BUTTON_STOP_SINGLE_AUTOSEND, &CZlgcanDlg::OnBnClickedButtonStopSingleAutosend)
    ON_BN_CLICKED(IDC_BUTTON_ADD_AUTOSEND, &CZlgcanDlg::OnBnClickedButtonAddAutosend)
    ON_BN_CLICKED(IDC_BUTTON_GET_DEV_AUTOSEND, &CZlgcanDlg::OnBnClickedButtonGetDevAutosend)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICE_INDEX, &CZlgcanDlg::OnCbnSelchangeComboDeviceIndex)
END_MESSAGE_MAP()


// Cusbcanfdx00udemoDlg ��Ϣ�������

BOOL CZlgcanDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitCombobox(IDC_COMBO_DEVICE_INDEX, 0, 32, 0);
	OnCbnSelchangeComboDevice();
    SetDlgItemText(IDC_EDIT_LOCAL_PORT, TEXT("1080"));
    SetDlgItemText(IDC_EDIT_REMOTE_ADDR, TEXT("192.168.3.176"));
    SetDlgItemText(IDC_EDIT_REMOTE_PORT, TEXT("8000"));

    m_spinAutSendIndex.SetBuddy(&m_editAutoSendIndex);
    m_spinAutSendIndex.SetRange(0, 32);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CZlgcanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CZlgcanDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CZlgcanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

typedef struct _DeviceInfo
{
	UINT device_type;  //�豸����
	UINT channel_count;//�豸��ͨ������
}DeviceInfo;
/*
�б�������Ҫ�ͶԻ������豸�б�����һһ��Ӧ
*/
static const DeviceInfo kDeviceType[] = {
    {ZCAN_USBCAN1, 1},
    {ZCAN_USBCAN2, 2},
	{ZCAN_PCI9820I,2},
    {ZCAN_USBCAN_E_U, 1},
    {ZCAN_USBCAN_2E_U, 2},
    {ZCAN_USBCAN_4E_U, 4},
	{ZCAN_PCIE_CANFD_100U, 1},
	{ZCAN_PCIE_CANFD_200U, 2},
	{ZCAN_PCIE_CANFD_400U_EX, 4 },
	{ZCAN_USBCANFD_200U, 2},
	{ZCAN_USBCANFD_100U, 1},
	{ZCAN_USBCANFD_MINI, 1},
    {ZCAN_CANETTCP, 1},
    {ZCAN_CANETUDP, 1},
    {ZCAN_WIFICAN_TCP, 1},
    {ZCAN_WIFICAN_UDP, 1},
	{ZCAN_CLOUD, 1},
    {ZCAN_CANFDWIFI_TCP, 1},
    {ZCAN_CANFDWIFI_UDP, 1},
    {ZCAN_CANFDNET_TCP, 2},
    {ZCAN_CANFDNET_UDP, 2},
    {ZCAN_CANFDNET_400U_TCP, 4},
    {ZCAN_CANFDNET_400U_UDP, 4},
};

void CZlgcanDlg::OnBnClickedButtonOpen()
{
	UpdateData(TRUE);
    if (kDeviceType[device_type_index_].device_type == ZCAN_CLOUD)
    {
        zcloudDlg dlg;
        if (IDCANCEL == dlg.DoModal())
        {
            return;
        }
        device_index_ = dlg.GetDeviceIndex();
    }
    device_handle_ = ZCAN_OpenDevice(kDeviceType[device_type_index_].device_type, device_index_, 0);
	if (INVALID_DEVICE_HANDLE == device_handle_)
	{
		AddData(_T("���豸ʧ��!"));
		return;
	}
	device_opened_ = TRUE;
	EnableCtrl(TRUE);
    AddData(_T("���豸�ɹ�!"));
}
//USBCANFD
static const UINT kAbitTimingUSB[] = {
	1000000,//1Mbps
    800000,//800kbps
    500000,//500kbps
    250000,//250kbps
    125000,//125kbps
    100000,//100kbps
    50000 //50kbps
};
static const UINT kDbitTimingUSB[] = {
    5000000,//5Mbps
    4000000,//4Mbps
    2000000,//2Mbps
    1000000 //1Mbps
};

//PCIECANFD brp=1
static const UINT kAbitTimingPCIE[] = {
    1000000, //1M(80%)
    800000, //800K(80%)
    500000, //500K(80%)
    250000, //250K(80%)
    125000  //125K(80%)
};
static const UINT kDbitTimingPCIE[] = {
    8000000, //8Mbps(80%)
    5000000, //5Mbps(75%)
    5000000, //5Mbps(87.5%)
    4000000, //4Mbps(80%)
    2000000, //2Mbps(80%)
    1000000  //1Mbps(80%)
};

static const unsigned kBaudrate[] = {
    1000000,
    800000,
    500000,
    250000,
    125000,
    100000,
    50000,
    20000,
    10000,
    5000
};

void CZlgcanDlg::OnBnClickedButtonInitcan()
{
	if (!device_opened_)
	{
		AddData(_T("�豸��û��!"));
		return;
	}
	ZCAN_CHANNEL_INIT_CONFIG config;
	memset(&config, 0, sizeof(config));
    UpdateData(TRUE);
    UINT type = kDeviceType[device_type_index_].device_type;
    const BOOL cloudDevice = type==ZCAN_CLOUD;
    const BOOL netcanfd = IsNetCANFD(type);
    const BOOL netcan = IsNetCAN(type);
    const BOOL netDevice = (netcan || netcanfd);
    const BOOL tcpDevice = IsNetTCP(type);
    const BOOL server = net_mode_index_ == 0;
    const BOOL usbcanfd = type==ZCAN_USBCANFD_100U ||
        type==ZCAN_USBCANFD_200U || type==ZCAN_USBCANFD_MINI;
    const BOOL pciecanfd = type==ZCAN_PCIE_CANFD_100U ||
		type == ZCAN_PCIE_CANFD_200U || type == ZCAN_PCIE_CANFD_400U_EX;
    const BOOL canfdDevice = usbcanfd || pciecanfd;


    if (cloudDevice)
    {
    }
    else if (netDevice)
    {
        char path[50] = {0};
        char value[100] = {0};
        TCHAR buffer[100] = {0};
        if (tcpDevice)
        {
            sprintf_s(path, "%d/work_mode", channel_index_);
            sprintf_s(value, "%d", server?1:0);
            ZCAN_SetValue(device_handle_,path, value);
            if (server)
            {
                sprintf_s(path, "%d/local_port", channel_index_);
                GetDlgItemText(IDC_EDIT_LOCAL_PORT, buffer, 100);
                sprintf_s(value, "%s", Utility::W2AEx(buffer).c_str());
				ZCAN_SetValue(device_handle_, path, value);
            } // server
            else
            {
                sprintf_s(path, "%d/ip", channel_index_);
                GetDlgItemText(IDC_EDIT_REMOTE_ADDR, buffer, 100);
                sprintf_s(value, "%s", Utility::W2AEx(buffer).c_str());
				ZCAN_SetValue(device_handle_, path, value);
                sprintf_s(path, "%d/work_port", channel_index_);
                GetDlgItemText(IDC_EDIT_REMOTE_PORT, buffer, 100);
                sprintf_s(value, "%s", Utility::W2AEx(buffer).c_str());
				ZCAN_SetValue(device_handle_, path, value);
            }
        } // tcp
        else
        {
            sprintf_s(path, "%d/local_port", channel_index_);
            GetDlgItemText(IDC_EDIT_LOCAL_PORT, buffer, 100);
            sprintf_s(value, "%s", Utility::W2AEx(buffer).c_str());
			ZCAN_SetValue(device_handle_, path, value);
            sprintf_s(path, "%d/ip", channel_index_);
            GetDlgItemText(IDC_EDIT_REMOTE_ADDR, buffer, 100);
            sprintf_s(value, "%s", Utility::W2AEx(buffer).c_str());
			ZCAN_SetValue(device_handle_, path, value);
            sprintf_s(path, "%d/work_port", channel_index_);
            GetDlgItemText(IDC_EDIT_REMOTE_PORT, buffer, 100);
            sprintf_s(value, "%s", Utility::W2AEx(buffer).c_str());
			ZCAN_SetValue(device_handle_, path, value);
        }
    }
    else
    {
        //���ò�����
        if (custom_baud_enable_)
        {	
            if (!SetCustomBaudrate())
            {
                AddData(_T("�����Զ��岨����ʧ��!"));
                return;
            }
        }
        else
        {
            if (!canfdDevice && !SetBaudrate())
            {
                AddData(_T("���ò�����ʧ��!"));
                return;
            }
        }

        if (usbcanfd) {

            char path[50] = {0};
            char value[100] = {0};
            sprintf_s(path, "%d/canfd_standard", channel_index_);
            sprintf_s(value, "%d", 0);
			ZCAN_SetValue(device_handle_, path, value);
        }
        if (usbcanfd)
        {   
			//���ò�����
			if (custom_baud_enable_)
			{
				if (!SetCustomBaudrate())
				{
					AddData(_T("�����Զ��岨����ʧ��!"));
					return;
				}
			}
			else
			{
				if (!SetCanfdBaudrate())
				{
					AddData(_T("���ò�����ʧ��!"));
					return;
				}
			}
            config.can_type = TYPE_CANFD;
            config.canfd.mode = work_mode_index_;
            config.canfd.filter = filter_mode_;
            config.canfd.acc_code = _tcstoul(acc_code_, 0, 16);
            config.canfd.acc_mask = _tcstoul(acc_mask_, 0, 16);

        }
        else if (pciecanfd)
		{

			char path[50] = { 0 };
			char value[100] = { 0 };
			if (!SetCanfdBaudrate())
			{
				AddData(_T("���ò�����ʧ��!"));
				return;
			}
			
			if (type == ZCAN_PCIE_CANFD_400U_EX )
				{
				sprintf_s(path, "0/set_device_recv_merge");
                sprintf_s(value, "0");
				ZCAN_SetValue(device_handle_, path, value);
				}
			
            config.can_type = TYPE_CANFD;
            config.canfd.mode = work_mode_index_;
            config.canfd.filter = filter_mode_;
            config.canfd.acc_code = _tcstoul(acc_code_, 0, 16);
            config.canfd.acc_mask = _tcstoul(acc_mask_, 0, 16);

        }
        else
        {
            config.can_type = TYPE_CAN;
            config.can.mode = work_mode_index_;
            config.can.filter = filter_mode_;
            config.can.acc_code = _tcstoul(acc_code_, 0, 16);
            config.can.acc_mask = _tcstoul(acc_mask_, 0, 16);
        }
    }

	channel_handle_ = ZCAN_InitCAN(device_handle_, channel_index_, &config);
	if (INVALID_CHANNEL_HANDLE == channel_handle_)
	{
		AddData(_T("��ʼ��CANʧ��!"));
		return;
	}
    if (usbcanfd)
    {
        if (resistance_enable_ && !SetResistanceEnable())
        {
            AddData(_T("�����ն˵���ʧ��!"));
            return;
        }
    }
	ctrl_int_can_.EnableWindow(FALSE);
    AddData(_T("��ʼ���ɹ�!"));
}

void CZlgcanDlg::OnBnClickedButtonStartcan()
{
	if (ZCAN_StartCAN(channel_handle_) != STATUS_OK)
	{
		AddData(_T("����CANʧ��!"));
		return;
	}
	ctrl_start_can_.EnableWindow(FALSE);
	start_ = TRUE;
	_beginthreadex(NULL, 0, OnDataRecv, this, 0, NULL);
    AddData(_T("����CAN�ɹ�!"));
}

void CZlgcanDlg::OnBnClickedButtonReset()
{
	if (ZCAN_ResetCAN(channel_handle_) != STATUS_OK)
	{
		AddData(_T("��λʧ��!"));
		return;
	}
	ctrl_start_can_.EnableWindow(TRUE);
	start_ = FALSE;
    AddData(_T("��λ�ɹ�!"));
}

void CZlgcanDlg::OnBnClickedButtonClose()
{
	// TODO: Add your control notification handler code here

	ZCAN_ResetCAN(channel_handle_);
    ZCAN_CloseDevice(device_handle_);
	start_ = FALSE;
	EnableCtrl(FALSE);
	ctrl_start_can_.EnableWindow(TRUE);
	ctrl_int_can_.EnableWindow(TRUE);
	device_opened_ = FALSE;
    AddData(_T("�豸�ѹر�!"));
}

void CZlgcanDlg::OnBnClickedButtonSend()
{
    CWaitCursor waitCursor;
	UpdateData(TRUE);
	if (datas_.IsEmpty())
	{
		AddData(_T("����Ϊ��"));
		return;
	}

    int  nSendCount = send_count_once_;
	UINT result;//���͵�֡��
	if (0 == protocol_index_)//can
	{
		ZCAN_Transmit_Data can_data;
        GetViewCANFrame(can_data, TRUE);

        if (nSendCount > 0)
        {
            ZCAN_Transmit_Data* pData = new ZCAN_Transmit_Data[nSendCount];
            for (int i=0; i<nSendCount; ++i)
            {
                memcpy_s(&pData[i], sizeof(ZCAN_Transmit_Data), &can_data, sizeof(can_data));
            }

            AddData(pData, 1);
            result = ZCAN_Transmit(channel_handle_, pData, nSendCount);
            delete [] pData;
        }
	}
	else //canfd
	{
		ZCAN_TransmitFD_Data canfd_data;
        GetViewCANFrame(canfd_data, TRUE);

        if (nSendCount > 0)
        {
            ZCAN_TransmitFD_Data* pData = new ZCAN_TransmitFD_Data[nSendCount];
            for (int i=0; i<nSendCount; ++i)
            {
                memcpy_s(&pData[i], sizeof(ZCAN_TransmitFD_Data), &canfd_data, sizeof(canfd_data));
            }

            AddData(pData, 1);
            result = ZCAN_TransmitFD(channel_handle_, pData, nSendCount);
            delete [] pData;
        }
	}
    CString csText;
    csText.Format(_T("��������:%d, �ɹ�����:%d"), nSendCount, result);
	if (result != nSendCount)
	{
		AddData(_T("��������ʧ��! ") + csText);
	}
	else
	{
		AddData(_T("�������ݳɹ� ") + csText);
	}
}

void CZlgcanDlg::InitCombobox( int ctrl_id, int start, int end, int current )
{
	CComboBox* ctrl = static_cast<CComboBox*>(GetDlgItem(ctrl_id));
	ASSERT(ctrl != NULL);
	ctrl->ResetContent();
	CString temp;
	for (int i = start; i < end; ++i)
	{
		temp.Format(_T("%d"), i);
		ctrl->AddString(temp);
	}
	ctrl->SetCurSel(current);
}

void CZlgcanDlg::OnCbnSelchangeComboDevice()
{
	UpdateData(TRUE);
	InitCombobox(IDC_COMBO_CHANNEL_INDEX, 0, kDeviceType[device_type_index_].channel_count, 0);
    UINT type = kDeviceType[device_type_index_].device_type;
    const BOOL cloudDevice = type==ZCAN_CLOUD;
    const BOOL netcanfd = IsNetCANFD(type);
    const BOOL netcan = IsNetCAN(type);
    const BOOL netDevice = (netcan || netcanfd);
    const BOOL tcpDevice = IsNetTCP(type);
    const BOOL usbcanfd = type==ZCAN_USBCANFD_100U ||
        type==ZCAN_USBCANFD_200U || type==ZCAN_USBCANFD_MINI;
    const BOOL pciecanfd = type==ZCAN_PCIE_CANFD_100U ||
        type==ZCAN_PCIE_CANFD_200U || type==ZCAN_PCIE_CANFD_400U|| type==ZCAN_PCIE_CANFD_400U_EX;

    const BOOL canfdDevice = usbcanfd || pciecanfd || netcanfd;
    const BOOL accFilter = pciecanfd || type==ZCAN_USBCAN1 || type==ZCAN_USBCAN2;

    //���з���֧��
    support_delay_send_ = usbcanfd || pciecanfd || netcanfd;
    support_delay_send_mode_ = usbcanfd || pciecanfd;
    support_get_send_mode_ = usbcanfd || pciecanfd;
    SetCtrlStateDelaySend(support_delay_send_, support_delay_send_mode_, support_get_send_mode_);
    ctrl_delay_send_mode_.SetCheck(BST_UNCHECKED);

    //��ʱ����֧��
    const BOOL support_autosend_canfd = canfdDevice;    // CANFD �豸
    const BOOL support_autosend_can = canfdDevice ;     // CANFD �豸������CAN�豸
    const BOOL support_autosend_index = (support_autosend_can && !pciecanfd);   // PCIECANFD ��֧��ʹ���������ƶ�ʱ��PCIECANFD���һ������������
    const BOOL support_stop_single_autosend = usbcanfd;
    const BOOL support_get_autosend_list = netcanfd;
    SetAutoSendCtrlState(support_autosend_can, support_autosend_canfd, support_autosend_index, support_stop_single_autosend, support_get_autosend_list);

    if (usbcanfd)
    {
        m_comboAbit.ResetContent();
        m_comboAbit.AddString(TEXT("1Mbps"));
        m_comboAbit.AddString(TEXT("800kbps"));
        m_comboAbit.AddString(TEXT("500kbps"));
        m_comboAbit.AddString(TEXT("250kbps"));
        m_comboAbit.AddString(TEXT("125kbps"));
        m_comboAbit.AddString(TEXT("100kbps"));
        m_comboAbit.AddString(TEXT("50kbps"));
        m_comboAbit.SetCurSel(0);
        m_comboDbit.ResetContent();
        m_comboDbit.AddString(TEXT("5Mbps"));
        m_comboDbit.AddString(TEXT("4Mbps"));
        m_comboDbit.AddString(TEXT("2Mbps"));
        m_comboDbit.AddString(TEXT("1Mbps"));
        m_comboDbit.SetCurSel(0);
    }
    else if (pciecanfd)
    {
        m_comboAbit.ResetContent();
        m_comboAbit.AddString(TEXT("1Mbps(80%)"));
        m_comboAbit.AddString(TEXT("800kbps(80%)"));
        m_comboAbit.AddString(TEXT("500kbps(80%)"));
        m_comboAbit.AddString(TEXT("250kbps(80%)"));
        m_comboAbit.AddString(TEXT("125kbps(80%)"));
		m_comboAbit.AddString(TEXT("100kbps"));
		m_comboAbit.AddString(TEXT("50kbps"));
        m_comboAbit.SetCurSel(0);
        m_comboDbit.ResetContent();
        m_comboDbit.AddString(TEXT("5Mbps(80%)"));
        m_comboDbit.AddString(TEXT("4Mbps(80%)"));
        m_comboDbit.AddString(TEXT("2Mbps(80%)"));
        m_comboDbit.AddString(TEXT("1Mbps(80%)"));
        m_comboDbit.SetCurSel(2);
    }

    GetDlgItem(IDC_COMBO_DEVICE_INDEX2)->EnableWindow(!cloudDevice && !netDevice);
    GetDlgItem(IDC_CHECK_RESISTANCE)->EnableWindow(usbcanfd);
    GetDlgItem(IDC_COMBO_BAUD)->EnableWindow(!canfdDevice && !netDevice && !cloudDevice);
    GetDlgItem(IDC_COMBO_ABIT)->EnableWindow(canfdDevice && !netDevice && !cloudDevice);
    GetDlgItem(IDC_COMBO_ABIT2)->EnableWindow(canfdDevice && !netDevice && !cloudDevice);
    GetDlgItem(IDC_CHECK_CUSTOM_BAUDRATE)->EnableWindow(!cloudDevice && !netDevice);
    GetDlgItem(IDC_EDIT_CUSTOM_BAUDRATE)->EnableWindow(!cloudDevice && !netDevice);
    GetDlgItem(IDC_COMBO_FILTER_MODE)->EnableWindow(accFilter && !cloudDevice && !netDevice);
    GetDlgItem(IDC_EDIT_ACC_CODE)->EnableWindow(accFilter && !cloudDevice && !netDevice);
    GetDlgItem(IDC_EDIT_ACC_MASK)->EnableWindow(accFilter && !cloudDevice && !netDevice);
    GetDlgItem(IDC_STATIC_WORK_MODE)->EnableWindow(!cloudDevice && !netDevice);
    GetDlgItem(IDC_STATIC_BAUD)->EnableWindow(!canfdDevice && !netDevice && !cloudDevice);
    GetDlgItem(IDC_STATIC_A_BAUDRATE)->EnableWindow(canfdDevice && !netDevice && !cloudDevice);
    GetDlgItem(IDC_STATIC_D_BAUDRATE)->EnableWindow(canfdDevice && !netDevice && !cloudDevice);
    GetDlgItem(IDC_STATIC_CUSTOM_BAUDRATE)->EnableWindow(!cloudDevice && !netDevice);
    GetDlgItem(IDC_STATIC_FILTER_MODE)->EnableWindow(accFilter && !cloudDevice && !netDevice);
    GetDlgItem(IDC_STATIC_ACC_CODE)->EnableWindow(accFilter && !cloudDevice && !netDevice);
    GetDlgItem(IDC_STATIC_ACC_MASK)->EnableWindow(accFilter && !cloudDevice && !netDevice);

    GetDlgItem(IDC_STATIC_NET_MODE)->EnableWindow(tcpDevice);
    GetDlgItem(IDC_COMBO_NET_MODE)->EnableWindow(tcpDevice);
    OnCbnSelchangeComboNetMode();
}

void CZlgcanDlg::OnCbnSelchangeComboNetMode()
{
	UpdateData(TRUE);
    UINT type = kDeviceType[device_type_index_].device_type;
    BOOL tcpDevice = IsNetTCP(type);
    BOOL udpDevice = IsNetUDP(type);
    if (tcpDevice)
    {
        const BOOL server = net_mode_index_ == 0;
        GetDlgItem(IDC_STATIC_LOCAL_PORT)->EnableWindow(server);
        GetDlgItem(IDC_STATIC_REMOTE_PORT)->EnableWindow(!server);
        GetDlgItem(IDC_STATIC_REMOTE_ADDR)->EnableWindow(!server);
        GetDlgItem(IDC_EDIT_LOCAL_PORT)->EnableWindow(server);
        GetDlgItem(IDC_EDIT_REMOTE_PORT)->EnableWindow(!server);
        GetDlgItem(IDC_EDIT_REMOTE_ADDR)->EnableWindow(!server);
    } else if (udpDevice)
    {
        GetDlgItem(IDC_STATIC_LOCAL_PORT)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_REMOTE_PORT)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_REMOTE_ADDR)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_LOCAL_PORT)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_REMOTE_PORT)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_REMOTE_ADDR)->EnableWindow(TRUE);
    } else
    {
        GetDlgItem(IDC_STATIC_LOCAL_PORT)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_REMOTE_PORT)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_REMOTE_ADDR)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_LOCAL_PORT)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_REMOTE_PORT)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_REMOTE_ADDR)->EnableWindow(FALSE);
    }
}

void CZlgcanDlg::EnableCtrl( BOOL opened )
{
	ctrl_device_type_.EnableWindow(!opened);
	ctrl_device_index_.EnableWindow(!opened);
	ctrl_channel_index_.EnableWindow(!opened);
	ctrl_open_device_.EnableWindow(!opened);
}

//�����Զ��岨����, ��Ҫ��CANMasterĿ¼�µ�baudcal�����ַ���
BOOL CZlgcanDlg::SetCustomBaudrate()
{

	char path[50] = {0};
	char value[100] = {0};
	string baudrate = Utility::W2AEx(custom_baudrate_);
	sprintf_s(path, "%d/baud_rate_custom", channel_index_);
	sprintf_s(value, "%s", baudrate.data());
	return 1 == ZCAN_SetValue(device_handle_, path, value);
}

UINT WINAPI CZlgcanDlg::OnDataRecv( LPVOID data )
{
	CZlgcanDlg* this_ = static_cast<CZlgcanDlg*>(data);
	if (this_)
	{
		this_->OnRecv();
	}
	return 0;
}

void CZlgcanDlg::OnRecv()
{
	ZCAN_Receive_Data can_data[100];
	ZCAN_ReceiveFD_Data canfd_data[100];
	UINT len;
	while(start_)
	{
		if (len = ZCAN_GetReceiveNum(channel_handle_, TYPE_CAN))
		{
			len = ZCAN_Receive(channel_handle_, can_data, 100, 50);
			AddData(can_data, len);
		}
		if (len = ZCAN_GetReceiveNum(channel_handle_, TYPE_CANFD))
		{
			len = ZCAN_ReceiveFD(channel_handle_, canfd_data, 100, 50);
			AddData(canfd_data, len);
		}
        //����������ʱ���While(1),��ռ�ô�����CPU
        Sleep(15);
	}
}

void CZlgcanDlg::AddData( const ZCAN_Receive_Data* data, UINT len )
{
	char item[TMP_BUFFER_LEN];
	for (UINT i = 0; i < len; ++i)
	{
		const ZCAN_Receive_Data& can = data[i];
		const canid_t& id = can.frame.can_id;
		sprintf_s(item, "���յ�CAN ID:%08X %s %s ����:%d ����:", GET_ID(id), IS_EFF(id)?"��չ֡":"��׼֡"
			, IS_RTR(id)?"Զ��֡":"����֡", can.frame.can_dlc);
		for (UINT i = 0; i < can.frame.can_dlc; ++i)
		{
			size_t item_len = strlen(item);
			sprintf_s(&item[item_len], TMP_BUFFER_LEN-item_len, "%02X ", can.frame.data[i]);
		}
		AddData(CString(item));
	}
}

void CZlgcanDlg::AddData( const ZCAN_ReceiveFD_Data* data, UINT len )
{
	char item[TMP_BUFFER_LEN];
	for (UINT i = 0; i < len; ++i)
	{
		const ZCAN_ReceiveFD_Data& canfd = data[i];
		const canid_t& id = canfd.frame.can_id;
		sprintf_s(item, "���յ�CANFD ID:%08X %s %s ����:%d ����:", GET_ID(id), IS_EFF(id)?"��չ֡":"��׼֡"
			, IS_RTR(id)?"Զ��֡":"����֡", canfd.frame.len);
		for (UINT i = 0; i < canfd.frame.len; ++i)
		{
			size_t item_len = strlen(item);
			sprintf_s(&item[item_len], TMP_BUFFER_LEN-item_len, "%02X ", canfd.frame.data[i]);
		}
		AddData(CString(item));
	}
}

void CZlgcanDlg::AddData( const CString& data )
{
    SYSTEMTIME stTime;
    GetLocalTime(&stTime);
    CString csData;
    csData.Format(_T("[%02d:%02d:%02d.%03d] "), stTime.wHour, stTime.wMinute, stTime.wSecond, stTime.wMilliseconds);
    csData += data;
    const int MAX_LEN_IN_ONELINE = 100;
    int nStrLen = csData.GetLength();
    int nPrinted = 0;
    CString csLine;
    int nOnce = 0;
    while (nPrinted < nStrLen)
    {
        nOnce = min(MAX_LEN_IN_ONELINE, nStrLen - nPrinted);
        csLine = csData.Mid(nPrinted, nOnce);
        data_recv_list_.AddString(csLine);
        nPrinted += nOnce;
    }
	data_recv_list_.SetCurSel(data_recv_list_.GetCount() - 1);
}

void CZlgcanDlg::AddData( const ZCAN_Transmit_Data* data, UINT len )
{
    char item[TMP_BUFFER_LEN];
    for (UINT i = 0; i < len; ++i)
    {
        const ZCAN_Transmit_Data& can = data[i];
        const canid_t& id = can.frame.can_id;
        sprintf_s(item, "Tx CAN ID:%08X %s %s ����:%d ����:", GET_ID(id), IS_EFF(id)?"��չ֡":"��׼֡"
            , IS_RTR(id)?"Զ��֡":"����֡", can.frame.can_dlc);
        for (UINT i = 0; i < can.frame.can_dlc; ++i)
        {
            size_t item_len = strlen(item);
            sprintf_s(&item[item_len], TMP_BUFFER_LEN-item_len, "%02X ", can.frame.data[i]);
        }
        AddData(CString(item));
    }

}

void CZlgcanDlg::AddData( const ZCAN_TransmitFD_Data* data, UINT len )
{
    char item[TMP_BUFFER_LEN];
    for (UINT i = 0; i < len; ++i)
    {
        const ZCAN_TransmitFD_Data& can = data[i];
        const canid_t& id = can.frame.can_id;
        sprintf_s(item, "Tx CANFD ID:%08X %s %s ����:%d ����:", GET_ID(id), IS_EFF(id)?"��չ֡":"��׼֡"
            , IS_RTR(id)?"Զ��֡":"����֡", can.frame.len);
        for (UINT i = 0; i < can.frame.len; ++i)
        {
            size_t item_len = strlen(item);
            sprintf_s(&item[item_len], TMP_BUFFER_LEN-item_len, "%02X ", can.frame.data[i]);
        }
        AddData(CString(item));
    }
}

void CZlgcanDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
    if (ZCLOUD_IsConnected())
    {
        ZCLOUD_DisconnectServer();
    }
	OnBnClickedButtonClose();
	CDialog::OnClose();
}
void CZlgcanDlg::OnBnClickedButtonClear()
{
	data_recv_list_.ResetContent();
}

BOOL CZlgcanDlg::SetTransmitType()
{

	char path[50] = {0};
	char value[100] = {0};
	sprintf_s(path, "%d/send_type", channel_index_);
	sprintf_s(value, "%d", send_type_index_);
	return 1 == ZCAN_SetValue(device_handle_, path, value);
}

//�����ն˵���ʹ��
BOOL CZlgcanDlg::SetResistanceEnable()
{

	char path[50] = {0};
	sprintf_s(path, "%d/initenal_resistance", channel_index_);
	char value[10] = {0};
	sprintf_s(value, "%d", resistance_enable_);
	return 1 == ZCAN_SetValue(device_handle_, path, value);
}

//����CAN��������
BOOL CZlgcanDlg::SetBaudrate()
{

	char path[50] = {0};
	sprintf_s(path, "%d/baud_rate", channel_index_);
	char value[10] = {0};
	sprintf_s(value, "%d", kBaudrate[baud_index_]);
	return 1 == ZCAN_SetValue(device_handle_, path, value);
}

//����USBCANFD��������
BOOL CZlgcanDlg::SetCanfdBaudrate()
{

	char path[50] = { 0 };
	sprintf_s(path, "%d/canfd_abit_baud_rate", channel_index_);
	char value[10] = { 0 };
	sprintf_s(value, "%d", kAbitTimingUSB[abit_baud_index_]);
	int ret_a = ZCAN_SetValue(device_handle_, path, value);

	sprintf_s(path, "%d/canfd_dbit_baud_rate", channel_index_);
	sprintf_s(value, "%d", kDbitTimingUSB[dbit_baud_index_]);
	int ret_d = ZCAN_SetValue(device_handle_, path, value);
	return 1 == (ret_a&&ret_d);
}

void CZlgcanDlg::OnBnClickedButtonGetTxAvailable()
{
    // TODO: Add your control notification handler code here

    char path[50] = {0};
    char value[100] = {0};
    CString csText;
    sprintf_s(path, "%d/get_device_available_tx_count/1", channel_index_);
	const char* pRet =(const char*) ZCAN_GetValue(device_handle_,path);
    if (pRet)
    {
        UINT nSpace = *(int*)pRet;
        csText.Format(_T("���п��ÿռ�:%d"), nSpace);
    }
    else
    {
        csText.Format(_T("��ȡ���п��ÿռ�ʧ��!"));
    }
    AddData(csText);
}

void CZlgcanDlg::OnBnClickedButtonClearTxQueue()
{
    // TODO: Add your control notification handler code here
    
    char path[50] = {0};
    char value[100] = {0};
    sprintf_s(path, "%d/clear_delay_send_queue", channel_index_);
	int nRet = ZCAN_SetValue(device_handle_, path, value);
    CString csText;
    csText.Format(_T("������з��� [%s]"), nRet > 0 ? _T("�ɹ�") : _T("ʧ��") );
    AddData(csText);
}

void CZlgcanDlg::OnBnClickedCheckDelaySendMode()
{
    // TODO: Add your control notification handler code here
  
    char path[50] = {0};
    char value[100] = {0};
    int nDelaySendQueueMode = (ctrl_delay_send_mode_.GetCheck() == BST_CHECKED);
    sprintf_s(path, "%d/set_send_mode", channel_index_);
    sprintf_s(value, "%d", nDelaySendQueueMode);
	int nRet = ZCAN_SetValue(device_handle_, path, value);
    CString csText, csRet;
    csText = (nDelaySendQueueMode ? _T("�������з���ģʽ") : _T("�رն��з���ģʽ"));
    csRet.Format(_T(" [%s]"), nRet > 0 ? _T("�ɹ�") : _T("ʧ��"));
    AddData(csText + csRet);
}

void CZlgcanDlg::SetCtrlStateDelaySend( BOOL delay_send, BOOL delay_send_mode, BOOL get_send_mode )
{
    ctrl_delay_send_mode_.EnableWindow(delay_send && delay_send_mode);
    GetDlgItem(IDC_BUTTON_GET_TX_AVAILABLE)->EnableWindow(delay_send);
    GetDlgItem(IDC_BUTTON_CLEAR_TX_QUEUE)->EnableWindow(delay_send);
    GetDlgItem(IDC_CHECK_DELAY_SEND_FLAG)->EnableWindow(delay_send);
    GetDlgItem(IDC_BUTTON_GET_SEND_MODE)->EnableWindow(delay_send && get_send_mode);
}

BOOL CZlgcanDlg::IsNetCAN( UINT type )
{
    return (type==ZCAN_CANETUDP || type==ZCAN_CANETTCP || type==ZCAN_WIFICAN_TCP || type==ZCAN_WIFICAN_UDP ||
            type==ZCAN_CANDTU_NET || type==ZCAN_CANDTU_NET_400);
}

BOOL CZlgcanDlg::IsNetCANFD( UINT type )
{
    return (type==ZCAN_CANFDNET_TCP || type==ZCAN_CANFDNET_UDP ||
        type==ZCAN_CANFDNET_400U_TCP || type==ZCAN_CANFDNET_400U_UDP ||
        type==ZCAN_CANFDWIFI_TCP || type==ZCAN_CANFDWIFI_UDP);
}

BOOL CZlgcanDlg::IsNetTCP( UINT type )
{
    return (type==ZCAN_CANETTCP || type==ZCAN_WIFICAN_TCP || type==ZCAN_CANDTU_NET || type==ZCAN_CANDTU_NET_400 ||
        type==ZCAN_CANFDNET_TCP || type==ZCAN_CANFDNET_400U_TCP ||type==ZCAN_CANFDWIFI_TCP );
}

BOOL CZlgcanDlg::IsNetUDP( UINT type )
{
    return (type==ZCAN_CANETUDP || type==ZCAN_WIFICAN_UDP ||
        type==ZCAN_CANFDNET_UDP || type==ZCAN_CANFDNET_400U_UDP ||type==ZCAN_CANFDWIFI_UDP);
}

void CZlgcanDlg::OnBnClickedButtonGetSendMode()
{
    // TODO: Add your control notification handler code here
   
    CString csText;
    char path[50] = {0};
    sprintf_s(path, "%d/get_send_mode/1", channel_index_);
	const char* pRet = (const char*)ZCAN_GetValue(device_handle_, path);
    if (pRet)
    {
        UINT nMode = *(int*)pRet;
        csText.Format(_T("�豸��ǰģʽ:[%s]"), nMode ? _T("���з���ģʽ") : _T("��������ģʽ"));
    }
    else
    {
        csText.Format(_T("��ȡͨ��ģʽʧ��!"));
    }
    AddData(csText);
}

void CZlgcanDlg::SetAutoSendCtrlState( BOOL support_can, BOOL support_canfd, BOOL support_index, BOOL support_single_cancel, BOOL support_get_autosend_list)
{
    BOOL support_autosend = support_can || support_canfd;
    GetDlgItem(IDC_EDIT_AUTOSEND_INDEX)->EnableWindow(support_index);
    GetDlgItem(IDC_EDIT_AUTOSEND_TIME_PERIOD)->EnableWindow(support_autosend);
    GetDlgItem(IDC_BUTTON_ADD_AUTOSEND)->EnableWindow(support_autosend);
    GetDlgItem(IDC_BUTTON_AUTOSEND_START)->EnableWindow(support_autosend);
    GetDlgItem(IDC_BUTTON_AUTOSEND_STOP)->EnableWindow(support_autosend);
    GetDlgItem(IDC_BUTTON_STOP_SINGLE_AUTOSEND)->EnableWindow(support_single_cancel);
    GetDlgItem(IDC_BUTTON_GET_DEV_AUTOSEND)->EnableWindow(support_get_autosend_list);
}

void CZlgcanDlg::AddAutosendCan(int nEnable)
{
    // TODO: Add your control notification handler code here

    UpdateData(TRUE);
    ZCAN_AUTO_TRANSMIT_OBJ autoObj;
    memset(&autoObj, 0, sizeof(autoObj));
    autoObj.enable = nEnable;
    autoObj.interval = auto_send_period_;
    autoObj.index = auto_send_index_;
    GetViewCANFrame(autoObj.obj, FALSE);

    char path[50] = {0};
    sprintf_s(path, "%d/auto_send", channel_index_);
	int nRet = ZCAN_SetValue(device_handle_, path, (const char*)&autoObj);
    CString csText;
    csText.Format(_T("���CAN��ʱ���� ����:%d ����:%d ����:%d ms ID:0x%X [%s]"), autoObj.index, autoObj.enable, autoObj.interval, autoObj.obj.frame.can_id, (nRet ? _T("�ɹ�") : _T("ʧ��")));
    AddData(csText);
}

void CZlgcanDlg::AddAutosendCanfd(int nEnable)
{
    // TODO: Add your control notification handler code here

    UpdateData(TRUE);
    ZCANFD_AUTO_TRANSMIT_OBJ autoObj;
    memset(&autoObj, 0, sizeof(autoObj));
    autoObj.enable = nEnable;
    autoObj.interval = auto_send_period_;
    autoObj.index = auto_send_index_;
    GetViewCANFrame(autoObj.obj, FALSE);

    char path[50] = {0};
    sprintf_s(path, "%d/auto_send_canfd", channel_index_);
	int nRet =  ZCAN_SetValue(device_handle_, path, (const char*)&autoObj);
    CString csText;
    csText.Format(_T("���CANFD��ʱ���� ����:%d ����:%d ����:%d ms ID:0x%X [%s]"), autoObj.index, autoObj.enable, autoObj.interval, autoObj.obj.frame.can_id, (nRet ? _T("�ɹ�") : _T("ʧ��")));
    AddData(csText);
}

void CZlgcanDlg::OnBnClickedButtonAutosendStart()
{
    // TODO: Add your control notification handler code here

    char path[50] = {0};
    char value[100] = {0};
    sprintf_s(path, "%d/apply_auto_send", channel_index_);
	int nRet = ZCAN_SetValue(device_handle_, path,"0");
    CString csText;
    csText.Format(_T("��ʼ��ʱ���� [%s]"), (nRet ? _T("�ɹ�") : _T("ʧ��")));
    AddData(csText);
}

void CZlgcanDlg::OnBnClickedButtonAutosendStop()
{
    // TODO: Add your control notification handler code here

    char path[50] = {0};
    char value[100] = {0};
    sprintf_s(path, "%d/clear_auto_send", channel_index_);
	int nRet = ZCAN_SetValue(device_handle_, path, "0");
    CString csText;
    csText.Format(_T("ֹͣ��ʱ���� [%s]"), (nRet ? _T("�ɹ�") : _T("ʧ��")));
    AddData(csText);
}

void CZlgcanDlg::OnBnClickedButtonStopSingleAutosend()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (0 == protocol_index_)
    {
        //CAN
        AddAutosendCan(0);
    }
    else
    {
        // CANFD
        AddAutosendCanfd(0);
    }
}

void CZlgcanDlg::GetViewCANFrame( ZCAN_Transmit_Data& can_data, BOOL add_delay_flag )
{
    UpdateData(TRUE);
    UINT id = _tcstoul(id_, 0, 16);
    string data = Utility::W2AEx(datas_);
    BOOL bDelay = frm_delay_flag_;
    UINT nDelayTime = frm_delay_time_;

    memset(&can_data, 0, sizeof(can_data));
    can_data.frame.can_id = MAKE_CAN_ID(id, frame_type_index_, 0, 0);
    can_data.frame.can_dlc = Utility::split(can_data.frame.data, CAN_MAX_DLEN, data, ' ', 16);
    can_data.transmit_type = send_type_index_;
    if (add_delay_flag && bDelay)
    {
        can_data.frame.__pad |= TX_DELAY_SEND_FLAG;
        can_data.frame.__res0 = LOBYTE(nDelayTime);
        can_data.frame.__res1 = HIBYTE(nDelayTime);
    }
}

void CZlgcanDlg::GetViewCANFrame( ZCAN_TransmitFD_Data& canfd_data, BOOL add_delay_flag )
{
    UpdateData(TRUE);
    UINT id = _tcstoul(id_, 0, 16);
    string data = Utility::W2AEx(datas_);
    BOOL bDelay = frm_delay_flag_;
    UINT nDelayTime = frm_delay_time_;

    memset(&canfd_data, 0, sizeof(canfd_data));
    canfd_data.frame.can_id = MAKE_CAN_ID(id, frame_type_index_, 0, 0);
    canfd_data.frame.len = Utility::split(canfd_data.frame.data, CANFD_MAX_DLEN, data, ' ', 16);
    canfd_data.transmit_type = send_type_index_;
    canfd_data.frame.flags |= canfd_exp_index_ ? CANFD_BRS : 0;
    if (add_delay_flag && bDelay)
    {
        canfd_data.frame.flags |= TX_DELAY_SEND_FLAG;
        canfd_data.frame.__res0 = LOBYTE(nDelayTime);
        canfd_data.frame.__res1 = HIBYTE(nDelayTime);
    }

}

void CZlgcanDlg::OnBnClickedButtonAddAutosend()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (0 == protocol_index_)
    {
        //CAN
        AddAutosendCan(1);
    }
    else
    {
        // CANFD
        AddAutosendCanfd(1);
    }
}

void CZlgcanDlg::OnBnClickedButtonGetDevAutosend()
{
    // TODO: Add your control notification handler code here

    CString csText;
    UINT nCount = 0;
    char path[50] = {0};

    //CAN
    sprintf_s(path, "%d/get_auto_send_can_count/1", channel_index_);
    const char* pRet = (const char*)ZCAN_GetValue(device_handle_,path);
    if (pRet)
    {
        nCount = *(int*)pRet;
        csText.Format(_T("CAN��ʱ��������:%d"), nCount);
        AddData(csText);
        if (nCount > 0)
        {
            sprintf_s(path, "%d/get_auto_send_can_data/1", channel_index_);
            pRet = (const char*) ZCAN_GetValue(device_handle_,path);
            if (pRet)
            {
                const ZCAN_AUTO_TRANSMIT_OBJ* pData = (ZCAN_AUTO_TRANSMIT_OBJ*)pRet;
                for (UINT i = 0; i < nCount; i++)
                {
                    csText.Format(_T("CAN ��ʱ ����:%d ���:%d ms ID:0x%08x"), pData[i].index, pData[i].interval, pData[i].obj.frame.can_id);
                    AddData(csText);
                }
            }
            else
            {
                csText.Format(_T("��ȡCAN��ʱ��������ʧ��!"));
                AddData(csText);
                return;
            }
        }
    }
    else
    {
        csText.Format(_T("��ȡCAN��ʱ��������ʧ��!"));
        AddData(csText);
        return;
    }


    //CANFD
    sprintf_s(path, "%d/get_auto_send_canfd_count/1", channel_index_);
    pRet = (const char*)ZCAN_GetValue(device_handle_,path);
    if (pRet)
    {
        nCount = *(int*)pRet;
        csText.Format(_T("CANFD��ʱ��������:%d"), nCount);
        AddData(csText);
        if (nCount > 0)
        {
            sprintf_s(path, "%d/get_auto_send_canfd_data/1", channel_index_);
			pRet = (const char*)ZCAN_GetValue(device_handle_, path);
            if (pRet)
            {
                const ZCANFD_AUTO_TRANSMIT_OBJ* pData = (ZCANFD_AUTO_TRANSMIT_OBJ*)pRet;
                for (UINT i = 0; i < nCount; i++)
                {
                    csText.Format(_T("CANFD ��ʱ ����:%d ���:%d ms ID:0x%08x"), pData[i].index, pData[i].interval, pData[i].obj.frame.can_id);
                    AddData(csText);
                }
            }
            else
            {
                csText.Format(_T("��ȡCANFD��ʱ��������ʧ��!"));
                AddData(csText);
                return;
            }
        }
    }
    else
    {
        csText.Format(_T("��ȡCANFD��ʱ��������ʧ��!"));
        AddData(csText);
        return;
    }
}


void CZlgcanDlg::OnCbnSelchangeComboDeviceIndex()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


// ListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "List.h"
#include "ListDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_ERROR_MESSAGE_LENGTH 256

// CListDlg dialog


CListDlg::CListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CListDlg::IDD, pParent)
	, m_isAdxRtListAvailable(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXTBOX_SOURCE, m_textboxSource);
	DDX_Control(pDX, IDC_TEXTBOX_INSTRUMENT, m_textboxInstrument);
	DDX_Control(pDX, IDC_TEXTBOX_FIELD, m_textboxField);
	DDX_Control(pDX, IDC_BUTTON_REGISTER, m_buttonAdded);
	DDX_Control(pDX, IDC_LISTVIEW_ADDED_ITEMS, m_listviewRegisteredItems);
	DDX_Control(pDX, IDC_BUTTON_UNREGISTER, m_buttonRemove);
	DDX_Control(pDX, IDC_BUTTON_UNREGISTER_ALL, m_buttonRemoveAll);
	DDX_Control(pDX, IDC_TEXTBOX_FREQUENCY, m_textboxFrequency);
	DDX_Control(pDX, IDC_TEXTBOX_TIMEOUT, m_textboxTimeout);
	DDX_Control(pDX, IDC_BUTTON_SET_MODE, m_buttonSetMode);
	DDX_Control(pDX, IDC_RADIO_RUNMODE_IMMEDIATE, m_radioRunModeImmediate);
	DDX_Control(pDX, IDC_RADIO_RUNMODE_FREQUENCY, m_radioRunModeFrequency);
	DDX_Control(pDX, IDC_RADIO_RUNMODE_FREQUENCY_IF_CHANGED, m_radioRunModeFrequencyIfChanged);
	DDX_Control(pDX, IDC_RADIO_RUNMODE_SNAPSHOT, m_radioRunModeSnapshot);
	DDX_Control(pDX, IDC_RADIO_FIELDOUTPUT_SHOW_ALL, m_radioFieldOutputShowAll);
	DDX_Control(pDX, IDC_RADIO_FIELDOUTPUT_UPDATED_FIELDS, m_radioFieldOutputUpdatedFields);
	DDX_Control(pDX, IDC_RADIO_ERROR_MODE_EXCEPTION, m_radioErrorModeException);
	DDX_Control(pDX, IDC_RADIO_ERROR_MODE_NO_EXCEPTION, m_radioErrorModeNoException);
	DDX_Control(pDX, IDC_RADIO_ERROR_MODE_DIALOG, m_radioErrorModeDialog);
	DDX_Control(pDX, IDC_LISTBOX_OUTPUT, m_listboxOutput);
	DDX_Control(pDX, IDC_BUTTON_START, m_buttonStart);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_buttonStop);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_buttonClose);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_buttonClear);
	//DDX_Control(pDX, IDC_ADXRTLIST, m_adxRtList);
	DDX_Control(pDX, IDC_LABEL_SOURCE_STATUS, m_labelSourceStatus);
	DDX_Control(pDX, IDC_LABEL_PLATFORM_STATUS, m_labelPlatformStatus);
	DDX_Control(pDX, IDC_LABEL_MODE_STRING, m_labelModeString);
}

BEGIN_MESSAGE_MAP(CListDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_RADIO_RUNMODE_FREQUENCY, &CListDlg::OnBnClickedRadioRunMode)
	ON_BN_CLICKED(IDC_RADIO_RUNMODE_FREQUENCY_IF_CHANGED, &CListDlg::OnBnClickedRadioRunMode)
	ON_BN_CLICKED(IDC_RADIO_RUNMODE_IMMEDIATE , &CListDlg::OnBnClickedRadioRunMode)
	ON_BN_CLICKED(IDC_RADIO_RUNMODE_SNAPSHOT , &CListDlg::OnBnClickedRadioRunMode)
	ON_BN_CLICKED(IDC_RADIO_FIELDOUTPUT_EXISTING_FIELDS, &CListDlg::OnBnClickedRadioFieldOutput)
	ON_BN_CLICKED(IDC_RADIO_FIELDOUTPUT_SHOW_ALL, &CListDlg::OnBnClickedRadioFieldOutput)
	ON_BN_CLICKED(IDC_RADIO_FIELDOUTPUT_UPDATED_FIELDS, &CListDlg::OnBnClickedRadioFieldOutput)
	ON_BN_CLICKED(IDC_RADIO_ERROR_MODE_DIALOG, &CListDlg::OnBnClickedRadioErrorMode)
	ON_BN_CLICKED(IDC_RADIO_ERROR_MODE_EXCEPTION, &CListDlg::OnBnClickedRadioErrorMode)
	ON_BN_CLICKED(IDC_RADIO_ERROR_MODE_NO_EXCEPTION, &CListDlg::OnBnClickedRadioErrorMode)
	ON_BN_CLICKED(IDC_BUTTON_REGISTER, &CListDlg::OnBnClickedButtonRegister)
	ON_BN_CLICKED(IDC_BUTTON_UNREGISTER, &CListDlg::OnBnClickedButtonUnregister)
	ON_BN_CLICKED(IDC_BUTTON_UNREGISTER_ALL, &CListDlg::OnBnClickedButtonUnregisterAll)
	ON_BN_CLICKED(IDC_BUTTON_SET_MODE, &CListDlg::OnBnClickedButtonSetMode)
	ON_BN_CLICKED(IDC_BUTTON_SET_SOURCE, &CListDlg::OnBnClickedButtonSetSource)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CListDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CListDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CListDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_START, &CListDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CListDlg::OnBnClickedButtonConnect)
END_MESSAGE_MAP()


// CListDlg message handlers

BOOL CListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_labelPlatformStatus.SetWindowText(_T(" "));

	m_textboxSource.SetWindowText(_T("IDN"));
	m_textboxInstrument.SetWindowText(_T("EUR="));
	m_textboxField.SetWindowText(_T("BID"));
	m_textboxFrequency.SetWindowText(_T("10"));
	m_textboxTimeout.SetWindowText(_T("10"));

	m_radioRunModeImmediate.SetCheck(BST_CHECKED);
	m_radioFieldOutputUpdatedFields.SetCheck(BST_CHECKED);
	m_radioErrorModeException.SetCheck(BST_CHECKED);
	OnBnClickedRadioFieldOutput();
	OnBnClickedRadioRunMode();
	OnBnClickedRadioErrorMode();

	m_listviewRegisteredItems.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_listviewRegisteredItems.InsertColumn(1, _T("Instrument"), LVCFMT_LEFT, 80);
	m_listviewRegisteredItems.InsertColumn(2, _T("Field"), LVCFMT_LEFT, 150);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CListDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CListDlg::OnBnClickedButtonRegister()
{
	if (!m_isAdxRtListAvailable)
	{
		m_listboxOutput.AddString(_T("AdxRtList is not available. Please connect to the platform."));
		return;
	}

	CString l_instrument;
	CString l_field;

	m_textboxInstrument.GetWindowText(l_instrument);
	m_textboxField.GetWindowText(l_field);
	l_instrument = l_instrument.Trim();
	l_field = l_field.Trim();
	if ( ( l_instrument == _T("") ) || ( l_field == _T("") ) )
	{
		return;
	}

	try
	{
		m_adxRtList.RegisterItems(_variant_t(l_instrument), _variant_t(l_field));
	}
	catch (_com_error& l_exception)
	{
		_bstr_t l_errorMessage = l_exception.Description();
		m_listboxOutput.AddString(l_errorMessage);
		return;
	}

	int l_itemCount = m_listviewRegisteredItems.GetItemCount();
	m_listviewRegisteredItems.InsertItem(l_itemCount, l_instrument);
	m_listviewRegisteredItems.SetItemText(l_itemCount, 1, l_field);

	m_textboxInstrument.SetFocus();
	m_textboxInstrument.SetSel(0, -1);
}

void CListDlg::OnBnClickedButtonUnregister()
{
	if (!m_isAdxRtListAvailable)
	{
		m_listboxOutput.AddString(_T("AdxRtList is not available. Please connect to the platform."));
		return;
	}

	POSITION l_position = m_listviewRegisteredItems.GetFirstSelectedItemPosition();
	if ( l_position == NULL )
	{
		return;
	}

	int l_index = m_listviewRegisteredItems.GetNextSelectedItem(l_position);

	CString l_instrumentList = m_listviewRegisteredItems.GetItemText(l_index, 0);	//It might have "," comma separator
	CString l_fieldList = m_listviewRegisteredItems.GetItemText(l_index, 1);		//It might have "," comma separator
	int l_itemPos = 0;		
	CString l_singleItem = l_instrumentList.Tokenize( _T(","), l_itemPos );
	try
	{
		while ( l_singleItem != _T("") )
		{
			int l_fieldPos = 0;
			CString l_singleField = l_fieldList.Tokenize( _T(","), l_fieldPos );
			while ( l_singleField != _T("") )
			{
				m_adxRtList.UnregisterFields( _variant_t(l_singleItem), _variant_t(l_singleField) );
				l_singleField = l_fieldList.Tokenize( _T(","), l_fieldPos );
			}
			l_singleItem = l_instrumentList.Tokenize( _T(","), l_itemPos );
		}
		
	}
	catch (_com_error& l_exception)
	{
		_bstr_t l_errorMessage = l_exception.Description();
		m_listboxOutput.AddString(l_errorMessage);
		return;
	}

	m_listviewRegisteredItems.DeleteItem(l_index);
	if ( m_listviewRegisteredItems.GetItemCount() > 0 )
	{
		m_listviewRegisteredItems.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
	}
}

void CListDlg::OnBnClickedButtonUnregisterAll()
{
	if (!m_isAdxRtListAvailable)
	{
		m_listboxOutput.AddString(_T("AdxRtList is not available. Please connect to the platform."));
		return;
	}

	try
	{
		m_adxRtList.UnregisterAllItems();
	}
	catch (_com_error& l_exception)
	{
		_bstr_t l_errorMessage = l_exception.Description();
		m_listboxOutput.AddString(l_errorMessage);
		return;
	}

	m_listviewRegisteredItems.DeleteAllItems();
}

void CListDlg::OnBnClickedButtonSetMode()
{
	if (!m_isAdxRtListAvailable)
	{
		m_listboxOutput.AddString(_T("AdxRtList is not available. Please connect to the platform."));
		return;
	}

	CString l_frequency, l_timeout, l_mode;

	m_textboxFrequency.GetWindowText(l_frequency);
	m_textboxTimeout.GetWindowText(l_timeout);
	l_mode.Format( _T("FRQ:%sS TIMEOUT:%s"), l_frequency, l_timeout );

	try
	{
		m_adxRtList.put_Mode(l_mode);
		m_labelModeString.SetWindowText(l_mode);
	}
	catch (_com_error& l_exception)
	{
		_bstr_t l_errorMessage = l_exception.Description();
		m_listboxOutput.AddString(l_errorMessage);
	}
}

void CListDlg::OnBnClickedButtonSetSource()
{
	if (!m_isAdxRtListAvailable)
	{
		m_listboxOutput.AddString(_T("AdxRtList is not available. Please connect to the platform."));
		return;
	}

	CString l_source;
	m_textboxSource.GetWindowText(l_source);
	l_source = l_source.Trim();

	try 
	{
		m_adxRtList.put_Source(l_source);
		m_adxRtList.put_DebugLevel(RT_DEBUG_NO);
	}
	catch (_com_error& l_exception)
	{
		_bstr_t l_errorMessage = l_exception.Description();
		m_listboxOutput.AddString(l_errorMessage);
	}
}

void CListDlg::OnBnClickedButtonStop()
{
	if (!m_isAdxRtListAvailable)
	{
		m_listboxOutput.AddString(_T("AdxRtList is not available. Please connect to the platform."));
		return;
	}

	try 
	{
		m_adxRtList.StopUpdates();
	}
	catch (_com_error& l_exception)
	{
		_bstr_t l_errorMessage = l_exception.Description();
		m_listboxOutput.AddString(l_errorMessage);
	}
}

void CListDlg::OnBnClickedButtonClose()
{
	if (!m_isAdxRtListAvailable)
	{
		m_listboxOutput.AddString(_T("AdxRtList is not available. Please connect to the platform."));
		return;
	}

	try 
	{
		m_adxRtList.CloseAllLinks();
	}
	catch (_com_error& l_exception)
	{
		_bstr_t l_errorMessage = l_exception.Description();
		m_listboxOutput.AddString(l_errorMessage);
	}
}

void CListDlg::OnBnClickedButtonClear()
{
	m_listboxOutput.ResetContent();
}

void CListDlg::OnBnClickedButtonStart()
{
	if (!m_isAdxRtListAvailable)
	{
		m_listboxOutput.AddString(_T("AdxRtList is not available. Please connect to the platform."));
		return;
	}

	try 
	{
		OnBnClickedRadioRunMode();
		m_adxRtList.put_ErrorMode(m_errorMode);
		m_adxRtList.StartUpdates(m_runMode);
	}
	catch (_com_error& l_exception)
	{
		_bstr_t l_errorMessage = l_exception.Description();
		m_listboxOutput.AddString(l_errorMessage);
	}
}

void CListDlg::OnBnClickedRadioFieldOutput()
{
	if (m_radioFieldOutputShowAll.GetCheck() == BST_CHECKED)
	{
		m_fieldRowView = RT_FRV_ALL;
	}

	if (m_radioFieldOutputUpdatedFields.GetCheck() == BST_CHECKED)
	{
		m_fieldRowView = RT_FRV_UPDATED;
	}
}

void CListDlg::OnBnClickedRadioRunMode()
{
	if (m_radioRunModeFrequency.GetCheck() == BST_CHECKED)
	{
		m_runMode = RT_MODE_ONTIME;
	}

	if (m_radioRunModeFrequencyIfChanged.GetCheck() == BST_CHECKED)
	{
		m_runMode = RT_MODE_ONTIME_IF_UPDATED;
	}

	if (m_radioRunModeImmediate.GetCheck() == BST_CHECKED)
	{
		m_runMode = RT_MODE_ONUPDATE;
	}

	if (m_radioRunModeSnapshot.GetCheck() == BST_CHECKED)
	{
		m_runMode = RT_MODE_IMAGE;
	}
}

void CListDlg::OnBnClickedRadioErrorMode()
{
	if (m_radioErrorModeDialog.GetCheck() == BST_CHECKED)
	{
		m_errorMode = DIALOGBOX;
	}

	if (m_radioErrorModeException.GetCheck() == BST_CHECKED)
	{
		m_errorMode = EXCEPTION;
	}

	if (m_radioErrorModeNoException.GetCheck() == BST_CHECKED)
	{
		m_errorMode = NO_EXCEPTION;
	}
}

void CListDlg::OnBnClickedButtonConnect()
{
	// TODO: Add your control notification handler code here
	HRESULT l_hr = m_eikonDesktopAPI.CreateObject();
	if (l_hr != S_OK)
	{
		m_labelPlatformStatus.SetWindowText(_T("Failed to create EikonDesktopDataAPI"));
		return;
	}
	else
	{
		EEikonDataAPIInitializeResult l_initStatus = m_eikonDesktopAPI.Initialize(this);
		if (l_initStatus == Succeed)
		{
			m_labelPlatformStatus.SetWindowText(_T("Connecting..."));
		}
		else
		{
			EEikonStatus l_status = m_eikonDesktopAPI.GetStatus();
			m_labelPlatformStatus.SetWindowText(GetPlatformStatusText(l_status));
		}
	}
}

CString CListDlg::GetPlatformStatusText(EEikonStatus a_eStatus)
{
	switch (a_eStatus)
	{
	case Connected:
		return _T("Connected");
	case Disconnected:
		return _T("Disconnected");
	case LocalMode:
		return _T("LocalMode");
	case Offline:
		return _T("Offline");
	}
	return _T("Unknown");
}

CString CListDlg::GetInstrumentStatusDescription(CString a_itemName, long a_itemStatus)
{
	CString l_description;

	switch(a_itemStatus)
	{
	case RT_ITEM_OK:
		l_description = _T("RT_ITEM_OK");
		break;
	case RT_ITEM_INVALID:
		l_description = _T("RT_ITEM_INVALID");
		break;
	case RT_ITEM_UNKNOWN:
		l_description = _T("RT_ITEM_UNKNOWN");
		break;
	case RT_ITEM_STALE:
		l_description = _T("RT_ITEM_STALE");
		break;
	case RT_ITEM_DELAYED:
		l_description = _T("RT_ITEM_DELAYED");
		break;
	case RT_ITEM_NOT_PERMISSIONED:
		l_description = _T("RT_ITEM_NOT_PERMISSIONED");
		break;
	default:
		l_description = _T("Unknown item status!!!");
		break;
	}
	
	return l_description;
}

CString CListDlg::GetFieldStatusDescription(CString a_fieldName, long a_fieldStatus)
{
	CString l_description = _T("");

	switch(a_fieldStatus)
	{
	case RT_FIELD_OK:
		l_description = _T("RT_FIELD_OK");
		break;
	case RT_FIELD_INVALID:
		l_description = _T("RT_FIELD_INVALID");
		break;
	case RT_FIELD_UNKNOWN:
		l_description = _T("RT_FIELD_UNKNOWN");
		break;
	case RT_FIELD_UNDEFINED:
		l_description = _T("RT_FIELD_UNDEFINED");
		break;
	default:
		l_description = _T("");
		break;
	}

	return l_description;
}

void CListDlg::GetFieldInformation(CString a_itemName, 
									  std::vector<CString> &a_fieldNames, 
									  std::vector<CString> &a_fieldValues, 
									  std::vector<CString> &a_fieldStatuses )
{
	int l_fieldColumnView = (m_fieldRowView == RT_FRV_EXISTING)? RT_FCV_VALUE: RT_FCV_VALUE | RT_FCV_STATUS;
	_variant_t l_listFields;
	try
	{
		l_listFields.Attach(m_adxRtList.get_ListFields( a_itemName, m_fieldRowView, (RT_FieldColumnView)l_fieldColumnView));
	}
	catch (_com_error& l_exception)
	{
		_bstr_t l_errorMessage = l_exception.Description();
		m_listboxOutput.AddString(l_errorMessage);
	}

	if ( (l_listFields.vt == VT_EMPTY) || (l_listFields.vt != (VT_VARIANT | VT_ARRAY) ))
	{
		return;
	}

	SAFEARRAY *l_sa = l_listFields.parray;
	LONG l_fieldStart = ((*l_sa).rgsabound[1]).lLbound;
	LONG l_fieldEnd = l_fieldStart + ((*l_sa).rgsabound[1]).cElements;
	LONG l_colStart = ((*l_sa).rgsabound[0]).lLbound;
	for ( LONG j = l_fieldStart; j < l_fieldEnd; ++j )
	{
		LONG l_indices[2];

		l_indices[0] = j;
		l_indices[1] = l_colStart;	// Column of ItemName
		_variant_t l_varFieldName;
		SafeArrayGetElement(l_sa, l_indices, &l_varFieldName);

		l_indices[0] = j;
		l_indices[1] = l_colStart + 1; // Column of ItemStatus
		_variant_t l_varFieldValue;
		SafeArrayGetElement(l_sa, l_indices, &l_varFieldValue);

		_variant_t l_varFieldStatus;
		
		if (m_fieldRowView == RT_FRV_EXISTING)
		{
			l_varFieldStatus = RT_FIELD_OK;
		}
		else
		{
			l_indices[0] = j;
			l_indices[1] = 2;
			SafeArrayGetElement(l_sa, l_indices, &l_varFieldStatus);
		}

		a_fieldNames.push_back( CString(l_varFieldName) );
		a_fieldValues.push_back( CString(l_varFieldValue) );
		a_fieldStatuses.push_back( 
			GetFieldStatusDescription( CString(l_varFieldName), l_varFieldStatus.lVal )
		);
	}
}


void CListDlg::DisplayValues(_variant_t& a_listItems)
{
	if ((a_listItems.vt == VT_EMPTY) || (a_listItems.vt != (VT_VARIANT | VT_ARRAY)))
	{
		return;
	}

	SAFEARRAY *l_sa = a_listItems.parray;
	LONG l_itemStart = ((*l_sa).rgsabound[1]).lLbound;
	LONG l_itemEnd = l_itemStart + ((*l_sa).rgsabound[1]).cElements;
	LONG l_colStart = ((*l_sa).rgsabound[0]).lLbound;
	for ( LONG i = l_itemStart; i < l_itemEnd; ++i )
	{
		LONG l_indices[2];

		l_indices[0] = i;
		l_indices[1] = l_colStart;	// Column of ItemName
		_variant_t l_varItemName;
		SafeArrayGetElement(l_sa, l_indices, &l_varItemName);

		l_indices[0] = i;
		l_indices[1] = l_colStart + 1; // Column of ItemStatus
		_variant_t l_varItemStatus;
		SafeArrayGetElement(l_sa, l_indices, &l_varItemStatus);

		CString l_itemName(l_varItemName.bstrVal);
		long l_itemStatus = l_varItemStatus.lVal;
		CString l_itemStatusDescription = GetInstrumentStatusDescription(l_itemName, l_itemStatus);

		// Display the received information
		std::vector<CString> l_fieldNames;
		std::vector<CString> l_fieldValues;
		std::vector<CString> l_fieldStatuses;
		GetFieldInformation(l_itemName, l_fieldNames, l_fieldValues, l_fieldStatuses);
		for ( size_t j = 0; j < l_fieldNames.size(); ++j )
		{
			CString l_displayMessage;
			l_displayMessage.Format(
				_T("[%s][%s]   [%s][%s][%s]"),
				l_itemStatusDescription,
				l_fieldStatuses[j],
				l_itemName, 
				l_fieldNames[j],
				l_fieldValues[j]
			);

			m_listboxOutput.AddString(l_displayMessage);
		}
	}
}

void CListDlg::OnStatusChanged(EEikonStatus a_eStatus)
{
	m_labelPlatformStatus.SetWindowText(GetPlatformStatusText(a_eStatus));
	if (a_eStatus == Connected)
	{
		m_isAdxRtListAvailable = S_OK == m_adxRtList.Initialize(this, &m_eikonDesktopAPI);
	}
}

void CListDlg::OnUpdate(BSTR a_itemName, VARIANT a_userTag, enum RT_ItemStatus a_itemStatus)
{
	UpdateData(TRUE) ;

	SAFEARRAY *l_sa;
	SAFEARRAYBOUND l_saBound[2];
	l_saBound[0].lLbound = 0;
	l_saBound[1].lLbound = 0;
	l_saBound[0].cElements = 1;
	l_saBound[1].cElements = 2;
	l_sa = SafeArrayCreate(VT_VARIANT, 2, l_saBound);

	LONG l_indices[2];
	l_indices[0] = 0;
	l_indices[1] = 0;
	SafeArrayPutElement(l_sa, l_indices, &_variant_t(a_itemName));

	l_indices[0] = 0;
	l_indices[1] = 1;

	SafeArrayPutElement(l_sa, l_indices, &_variant_t(a_itemStatus));

	_variant_t l_listItems;
	l_listItems.vt = (VT_VARIANT | VT_ARRAY);
	l_listItems.parray = l_sa;

	DisplayValues(l_listItems);
}

void CListDlg::OnImage(RT_DataStatus a_dataStatus)
{
	UpdateData(TRUE);

	_variant_t l_listItems;
	try
	{
		l_listItems.Attach(m_adxRtList.get_ListItems(RT_IRV_ALL, RT_ICV_STATUS));
	}
	catch (_com_error& l_exception)
	{
		_bstr_t l_errorMessage = l_exception.Description();
		m_listboxOutput.AddString(l_errorMessage);
	}
	DisplayValues(l_listItems);
}

void CListDlg::OnTime()
{
	UpdateData(TRUE) ;

	_variant_t l_listItems;
	try
	{
		l_listItems.Attach(m_adxRtList.get_ListItems(RT_IRV_ALL, RT_ICV_STATUS));
	}
	catch (_com_error& l_exception)
	{
		_bstr_t l_errorMessage = l_exception.Description();
		m_listboxOutput.AddString(l_errorMessage);
	}
	DisplayValues(l_listItems);
}

void CListDlg::OnStatusChange(RT_ListStatus a_listStatus, RT_SourceStatus a_sourceStatus, RT_RunMode a_runMode)
{
	switch (a_listStatus)
	{
	// 0 = RT_LIST_INACTIVE, 1 = RT_LIST_RUNNING,
	// 2 = RT_LIST_UPDATES_STOPPED, 3 = RT_LIST_LINKS_CLOSED
	case RT_LIST_INACTIVE : break;
	case RT_LIST_RUNNING : break;
	case RT_LIST_UPDATES_STOPPED : break;
	case RT_LIST_LINKS_CLOSED : break;
	}

	switch(a_sourceStatus) 
	{
	// 0 = RT_SOURCE_UP, 1 = RT_SOURCE_DOWN, 2 = RT_SOURCE_INVALID,
	// 3 = RT_SOURCE_UNDEFINED, 4 = RT_SOURCE_NOT_SET
	case RT_SOURCE_UP : m_labelSourceStatus.SetWindowText(_T("Status: Up"));break ;
	case RT_SOURCE_DOWN : m_labelSourceStatus.SetWindowText(_T("Status: Down"));break ;
	case RT_SOURCE_INVALID : m_labelSourceStatus.SetWindowText(_T("Status: Invalid"));break ;
	case RT_SOURCE_UNDEFINED : m_labelSourceStatus.SetWindowText(_T("Status: Unknown"));break ;
	case RT_SOURCE_NOT_SET : m_labelSourceStatus.SetWindowText(_T("Status: Not set"));break ;
	}

	switch(a_runMode)
	{
	// 1 = RT_MODE_ONTIME_IF_UPDATED, 2 = RT_MODE_ONTIME,
	// 3 = RT_MODE_ONUPDATE, 4 = RT_MODE_IMAGE, 5 = RT_MODE_NOT_SET
	case RT_MODE_ONTIME_IF_UPDATED : break;
	case RT_MODE_ONTIME : break;
	case RT_MODE_ONUPDATE : break;
	case RT_MODE_IMAGE : break;
	case RT_MODE_NOT_SET : break;
	}
}
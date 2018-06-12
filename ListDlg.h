
// ListDlg.h : header file
//
#pragma once
#include <vector>
#include "IEikonDesktopDataAPIEventListener.h"
#include "IAdxRtListEventListener.h"
#include "EikonDesktopDataAPI.h"
#include "AdxRtList.h"

// CListDlg dialog
class CListDlg : public CDialogEx, public IEikonDesktopDataAPIEventListener, public IAdxRtListEventListener
{
// Construction
public:
	CListDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_List_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	//IEikonDesktopDataAPIEventListener
	void OnStatusChanged(EEikonStatus a_eStatus);

	//IAdxRtListEventListener
	void OnUpdate(BSTR a_itemName, VARIANT a_userTag, enum RT_ItemStatus a_itemStatus);
	void OnImage(RT_DataStatus a_dataStatus);
	void OnTime();
	void OnStatusChange(RT_ListStatus a_listStatus, RT_SourceStatus a_sourceStatus, RT_RunMode a_runMode);

	CString GetInstrumentStatusDescription(CString a_itemName, long a_itemStatus);
	CString GetFieldStatusDescription(CString a_fieldName, long a_fieldStatus);
	void GetFieldInformation(CString a_itemName, std::vector<CString> &a_fieldNames, 
								std::vector<CString> &a_fieldValues, std::vector<CString> &a_fieldStatuses);
	void DisplayValues(_variant_t& a_listItems);

	CEdit m_textboxSource;
	CStatic m_labelSourceStatus;
	CStatic m_labelPlatformStatus;
	CEdit m_textboxInstrument;
	CEdit m_textboxField;
	CButton m_buttonAdded;
	CListCtrl m_listviewRegisteredItems;
	CButton m_buttonRemove;
	CButton m_buttonRemoveAll;
	CEdit m_textboxFrequency;
	CEdit m_textboxTimeout;
	CButton m_buttonSetMode;
	CStatic m_labelModeString;
	CButton m_radioRunModeImmediate;
	CButton m_radioRunModeFrequency;
	CButton m_radioRunModeFrequencyIfChanged;
	CButton m_radioRunModeSnapshot;
	CButton m_radioFieldOutputShowAll;
	CButton m_radioFieldOutputUpdatedFields;
	CButton m_radioErrorModeException;
	CButton m_radioErrorModeNoException;
	CButton m_radioErrorModeDialog;
	CListBox m_listboxOutput;
	CButton m_buttonStart;
	CButton m_buttonStop;
	CButton m_buttonClose;
	CButton m_buttonClear;

	afx_msg void OnBnClickedRadioRunMode();
	afx_msg void OnBnClickedButtonRegister();
	afx_msg void OnBnClickedButtonUnregister();
	afx_msg void OnBnClickedButtonUnregisterAll();
	afx_msg void OnBnClickedButtonSetMode();
	afx_msg void OnBnClickedRadioFieldOutput();
	afx_msg void OnBnClickedRadioErrorMode();

	afx_msg void OnBnClickedButtonSetSource();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonConnect();
private:
	CAdxRtList m_adxRtList;
	RT_RunMode m_runMode;
	AdxErrorMode m_errorMode;
	RT_FieldRowView m_fieldRowView;
	CEikonDesktopDataAPI m_eikonDesktopAPI;
	CString GetPlatformStatusText(EEikonStatus a_eStatus);
	bool m_isAdxRtListAvailable;
};

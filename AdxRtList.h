#pragma once
#include <atlbase.h>
#include <atlcom.h>

class IAdxRtListEventListener;
class CAdxRtList;
class CEikonDesktopDataAPI;

typedef IDispEventImpl<0, CAdxRtList, &DIID_IAdxRtListEvents, &LIBID_AdfinXRtLib, 6, 0> IAdxRtListEventListenerImpl;

class CAdxRtList : IAdxRtListEventListenerImpl
{
public:
	CAdxRtList(void);
	virtual ~CAdxRtList(void);

	BEGIN_SINK_MAP(CAdxRtList)
		SINK_ENTRY_INFO(0, DIID_IAdxRtListEvents, 0x1, OnUpdate, &m_OnUpdateInfo)
		SINK_ENTRY_INFO(0, DIID_IAdxRtListEvents, 0x2, OnImage, &m_OnImageInfo)
		SINK_ENTRY_INFO(0, DIID_IAdxRtListEvents, 0x3, OnTime, &m_OnTimeInfo)
		SINK_ENTRY_INFO(0, DIID_IAdxRtListEvents, 0x4, OnStatusChange, &m_OnStatusInfo)
	END_SINK_MAP()

    STDMETHOD_(void, OnUpdate)(BSTR a_itemName, VARIANT a_userTag, enum RT_ItemStatus a_itemStatus);
	STDMETHOD_(void, OnImage)(RT_DataStatus a_dataStatus);
	STDMETHOD_(void, OnTime)();
    STDMETHOD_(void, OnStatusChange)(RT_ListStatus a_listStatus, RT_SourceStatus a_courceStatus, RT_RunMode a_runMode);

	HRESULT Initialize(IAdxRtListEventListener* m_adxRtListEventListener, CEikonDesktopDataAPI* a_eikonDesktopDataAPI);

	// IAdxRtList methods
	_bstr_t get_Source();
	void put_Source(LPCTSTR newValue);
	RT_SourceStatus get_SourceStatus();
	RT_ListStatus get_ListStatus();
	void RegisterItems(const _variant_t& ItemList, const _variant_t& FieldList);
	void UnregisterItems(const _variant_t& ItemList);
	void UnregisterAllItems();
	void UnregisterFields(const _variant_t& ItemList, const _variant_t& FieldList);
	BOOL IsRegisteredItem(LPCTSTR ItemName);
	BOOL IsRegisteredField(LPCTSTR ItemName, LPCTSTR FieldName);
	void StartUpdates(RT_RunMode RunMode);
	void StopUpdates();
	void CloseAllLinks();
	RT_ItemStatus get_ItemStatus(LPCTSTR ItemName);
	RT_FieldStatus get_FieldStatus(LPCTSTR ItemName, LPCTSTR FieldName);
	VARIANT get_Value(LPCTSTR ItemName, LPCTSTR FieldName);
	VARIANT get_UserTag(LPCTSTR ItemName, LPCTSTR FieldName);
	void put_UserTag(LPCTSTR ItemName, LPCTSTR FieldName, const _variant_t& newValue);
	VARIANT get_ListFields(LPCTSTR ItemName, RT_FieldRowView RView, RT_FieldColumnView CView);
	VARIANT get_ListItems(RT_ItemRowView RView, RT_ItemColumnView CView);
	long get_FieldListCount(LPCTSTR ItemName, RT_FieldRowView RView);
	long get_ItemListCount(RT_ItemRowView RView);
	_bstr_t get_Mode();
	void put_Mode(LPCTSTR newValue);
	AdxErrorMode get_ErrorMode();
	void put_ErrorMode(AdxErrorMode newValue);
	RT_DebugLevel get_DebugLevel();
	void put_DebugLevel(RT_DebugLevel newValue);
	long get_ErrorCode();
	_bstr_t get_ErrorString();
	VARIANT get_Attribute(const _variant_t& Attrib);

private:
	static struct _ATL_FUNC_INFO m_OnUpdateInfo;
	static struct _ATL_FUNC_INFO m_OnImageInfo;
	static struct _ATL_FUNC_INFO m_OnTimeInfo;
	static struct _ATL_FUNC_INFO m_OnStatusInfo;

	IAdxRtListPtr m_rtList;
	IAdxRtListEventListener* m_adxRtListEventListener;
	bool m_isEventAdvisedOK;
};



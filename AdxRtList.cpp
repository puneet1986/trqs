#include "StdAfx.h"
#include "AdxRtList.h"
#include "IAdxRtListEventListener.h"
#include "EikonDesktopDataAPI.h"

struct _ATL_FUNC_INFO CAdxRtList::m_OnUpdateInfo = 
{ 
	CC_STDCALL, VT_EMPTY, 3, 
	{
		VT_BSTR,VT_VARIANT,VT_I4
	}
}; 

struct _ATL_FUNC_INFO CAdxRtList::m_OnImageInfo = 
{ 
	CC_STDCALL, VT_EMPTY, 1,
	{
		VT_I4
	}
};

struct _ATL_FUNC_INFO CAdxRtList::m_OnTimeInfo = 
{ 
	CC_STDCALL, VT_EMPTY, 0
};

struct _ATL_FUNC_INFO CAdxRtList::m_OnStatusInfo = 
{ 
	CC_STDCALL, VT_EMPTY, 3,
	{
		VT_I4,VT_I4,VT_I4
	}
};

CAdxRtList::CAdxRtList(void) :
	m_adxRtListEventListener(NULL),
	m_isEventAdvisedOK(false),
	m_rtList(NULL)
{
}


CAdxRtList::~CAdxRtList(void)
{
	if (m_isEventAdvisedOK)
	{
		DispEventUnadvise(m_rtList);
	}
}

void STDMETHODCALLTYPE CAdxRtList::OnUpdate(BSTR a_itemName, VARIANT a_userTag, enum RT_ItemStatus a_itemStatus)
{
	if (m_adxRtListEventListener)
	{
		m_adxRtListEventListener->OnUpdate(a_itemName, a_userTag, a_itemStatus);
	}
}

void STDMETHODCALLTYPE CAdxRtList::OnImage(RT_DataStatus a_dataStatus)
{
	if (m_adxRtListEventListener)
	{
		m_adxRtListEventListener->OnTime();
	}
}

void STDMETHODCALLTYPE CAdxRtList::OnTime()
{
	if (m_adxRtListEventListener)
	{
		m_adxRtListEventListener->OnTime();
	}
}

void STDMETHODCALLTYPE CAdxRtList::OnStatusChange(RT_ListStatus a_listStatus, RT_SourceStatus a_courceStatus, RT_RunMode a_runMode)
{
	if (m_adxRtListEventListener)
	{
		m_adxRtListEventListener->OnStatusChange(a_listStatus, a_courceStatus, a_runMode);
	}
}

HRESULT CAdxRtList::Initialize(IAdxRtListEventListener* a_adxRtListEventListener, CEikonDesktopDataAPI* a_eikonDesktopDataAPI)
{
	// if it has been initialized
	if (m_adxRtListEventListener)
	{
		return S_OK;
	}
	
	m_adxRtListEventListener = a_adxRtListEventListener;
	m_rtList = a_eikonDesktopDataAPI->CreateAdxRtList();
	if (m_rtList)
	{
		HRESULT l_hResult = DispEventAdvise(m_rtList);
		if (l_hResult == S_OK)
		{
			m_isEventAdvisedOK = true;
			return S_OK;
		}
	}
	return E_FAIL;
}

_bstr_t CAdxRtList::get_Source()
{
	_bstr_t result;
	if (m_rtList)
	{
		try
		{
			result = m_rtList->GetSource();
		}
		catch (...) 
		{
			throw;
		}
	}
	return result;
}
void CAdxRtList::put_Source(LPCTSTR newValue)
{
	if (m_rtList)
	{
		try
		{
			m_rtList->PutSource(newValue);
		}
		catch (...) 
		{
			throw;
		}
	}
}

RT_SourceStatus CAdxRtList::get_SourceStatus()
{
	RT_SourceStatus result = RT_SOURCE_NOT_SET;
	if (m_rtList)
	{
		try
		{
			result = m_rtList->GetSourceStatus();
		}
		catch (...) 
		{
			throw;
		}
	}
	return result;
}

RT_ListStatus CAdxRtList::get_ListStatus()
{
	RT_ListStatus result = RT_LIST_INACTIVE;
	if (m_rtList)
	{
		try
		{
			result = m_rtList->GetListStatus();
		}
		catch (...) 
		{
			throw;
		}
	}
	return result;
}

void CAdxRtList::RegisterItems(const _variant_t& ItemList, const _variant_t& FieldList)
{
	if (m_rtList)
	{
		try
		{
			m_rtList->RegisterItems(ItemList, FieldList);
		}
		catch (...) 
		{
			throw;
		}
	}
}

void CAdxRtList::UnregisterItems(const _variant_t& ItemList)
{
	if (m_rtList)
	{
		try
		{
			m_rtList->UnregisterItems(ItemList);
		}
		catch (...) 
		{
			throw;
		}
	}
}

void CAdxRtList::UnregisterAllItems()
{
	if (m_rtList)
	{
		try
		{
			m_rtList->UnregisterAllItems();
		}
		catch (...) 
		{
			throw;
		}
	}
}

void CAdxRtList::UnregisterFields(const _variant_t& ItemList, const _variant_t& FieldList)
{
	if (m_rtList)
	{
		try
		{
			m_rtList->UnregisterFields(ItemList, FieldList);
		}
		catch (...) 
		{
			throw;
		}
	}
}

BOOL CAdxRtList::IsRegisteredItem(LPCTSTR ItemName)
{
	VARIANT_BOOL result = VARIANT_FALSE;
	if (m_rtList)
	{
		try
		{
			result = m_rtList->IsRegisteredItem(ItemName);
		}
		catch (...) 
		{
			throw;
		}
	}
	return (result!=VARIANT_FALSE);
}

BOOL CAdxRtList::IsRegisteredField(LPCTSTR ItemName, LPCTSTR FieldName)
{
	VARIANT_BOOL result = VARIANT_FALSE;
	if (m_rtList)
	{
		try
		{
			result = m_rtList->IsRegisteredField(ItemName, FieldName);
		}
		catch (...) 
		{
			throw;
		}
	}
	return (result!=VARIANT_FALSE);
}

void CAdxRtList::StartUpdates(RT_RunMode RunMode)
{
	if (m_rtList)
	{
		try
		{
			m_rtList->StartUpdates(RunMode);
		}
		catch (...) 
		{
			throw;
		}
	}
}

void CAdxRtList::StopUpdates()
{
	if (m_rtList)
	{
		try
		{
			m_rtList->StopUpdates();
		}
		catch (...) 
		{
			throw;
		}
	}
}

void CAdxRtList::CloseAllLinks()
{
	if (m_rtList)
	{
		try
		{
			m_rtList->CloseAllLinks();
		}
		catch (...) 
		{
			throw;
		}
	}
}

RT_ItemStatus CAdxRtList::get_ItemStatus(LPCTSTR ItemName)
{
	RT_ItemStatus result = RT_ITEM_UNKNOWN;
	if (m_rtList)
	{
		try
		{
			result = m_rtList->GetItemStatus(ItemName);
		}
		catch (...) 
		{
			throw;
		}
	}
	return result;
}

RT_FieldStatus CAdxRtList::get_FieldStatus(LPCTSTR ItemName, LPCTSTR FieldName)
{
	RT_FieldStatus result = RT_FIELD_UNKNOWN;
	if (m_rtList)
	{
		try
		{
			result = m_rtList->GetFieldStatus(ItemName, FieldName);
		}
		catch (...) 
		{
			throw;
		}
	}
	return result;
}

VARIANT CAdxRtList::get_Value(LPCTSTR ItemName, LPCTSTR FieldName)
{
	_variant_t result;
	if (m_rtList)
	{
		try
		{
			result.Attach(m_rtList->GetValue(ItemName, FieldName).Detach());
		}
		catch (...) 
		{
			throw;
		}
	}
	return result.Detach();
}

VARIANT CAdxRtList::get_UserTag(LPCTSTR ItemName, LPCTSTR FieldName)
{
	_variant_t result;
	if (m_rtList)
	{
		try
		{
			result.Attach(m_rtList->GetUserTag(ItemName, FieldName).Detach());
		}
		catch (...) 
		{
			throw;
		}
	}
	return result.Detach();
}
void CAdxRtList::put_UserTag(LPCTSTR ItemName, LPCTSTR FieldName, const _variant_t& newValue)
{
	if (m_rtList)
	{
		try
		{
			m_rtList->PutUserTag(ItemName, FieldName, newValue);
		}
		catch (...) 
		{
			throw;
		}
	}
}

VARIANT CAdxRtList::get_ListFields(LPCTSTR ItemName, RT_FieldRowView RView, RT_FieldColumnView CView)
{
	_variant_t result;
	if (m_rtList)
	{
		try
		{
			result.Attach(m_rtList->GetListFields(ItemName, RView, CView).Detach());
		}
		catch (...) 
		{
			throw;
		}
	}
	return result.Detach();
}

VARIANT CAdxRtList::get_ListItems(RT_ItemRowView RView, RT_ItemColumnView CView)
{
	_variant_t result;
	if (m_rtList)
	{
		try
		{
			result.Attach(m_rtList->GetListItems(RView, CView).Detach());
		}
		catch (...) 
		{
			throw;
		}
	}
	return result.Detach();
}

long CAdxRtList::get_FieldListCount(LPCTSTR ItemName, RT_FieldRowView RView)
{
	long result = 0;
	if (m_rtList)
	{
		try
		{
			result = m_rtList->GetFieldListCount(ItemName, RView);
		}
		catch (...) 
		{
			throw;
		}
	}
	return result;
}

long CAdxRtList::get_ItemListCount(RT_ItemRowView RView)
{
	long result = 0;
	if (m_rtList)
	{
		try
		{
			result = m_rtList->GetItemListCount(RView);
		}
		catch (...) 
		{
			throw;
		}
	}
	return result;
}

_bstr_t CAdxRtList::get_Mode()
{
	_bstr_t result;
	if (m_rtList)
	{
		try
		{
			result = m_rtList->GetMode();
		}
		catch (...) 
		{
			throw;
		}
	}
	return result;
}

void CAdxRtList::put_Mode(LPCTSTR newValue)
{
	if (m_rtList)
	{
		try
		{
			m_rtList->PutMode(newValue);
		}
		catch (...) 
		{
			throw;
		}
	}
}

AdxErrorMode CAdxRtList::get_ErrorMode()
{
	AdxErrorMode result;
	if (m_rtList)
	{
		try
		{
			result = m_rtList->GetErrorMode();
		}
		catch (...) 
		{
			throw;
		}
	}
	return result;
}

void CAdxRtList::put_ErrorMode(AdxErrorMode newValue)
{
	if (m_rtList)
	{
		try
		{
			m_rtList->PutErrorMode(newValue);
		}
		catch (...) 
		{
			throw;
		}
	}
}

RT_DebugLevel CAdxRtList::get_DebugLevel()
{
	RT_DebugLevel result = RT_DEBUG_NO;
	if (m_rtList)
	{
		try
		{
			result = m_rtList->GetDebugLevel();
		}
		catch (...) 
		{
			throw;
		}
	}
	return result;
}

void CAdxRtList::put_DebugLevel(RT_DebugLevel newValue)
{
	if (m_rtList)
	{
		try
		{
			m_rtList->PutDebugLevel(newValue);
		}
		catch (...) 
		{
			throw;
		}
	}
}

long CAdxRtList::get_ErrorCode()
{
	long result = 0;
	if (m_rtList)
	{
		try
		{
			result = m_rtList->GetErrorCode();
		}
		catch (...) 
		{
			throw;
		}
	}
	return result;
}

_bstr_t CAdxRtList::get_ErrorString()
{
	_bstr_t result;
	if (m_rtList)
	{
		try
		{
			result = m_rtList->GetErrorString();
		}
		catch (...) 
		{
			throw;
		}
	}
	return result;
}

VARIANT CAdxRtList::get_Attribute(const _variant_t& Attrib)
{
	_variant_t result;
	if (m_rtList)
	{
		try
		{
			result.Attach(m_rtList->GetAttribute(Attrib).Detach());
		}
		catch (...) 
		{
			throw;
		}
	}
	return result.Detach();
}

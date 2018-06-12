#include "StdAfx.h"
#include "EikonDesktopDataAPI.h"
#include "IEikonDesktopDataAPIEventListener.h"

struct _ATL_FUNC_INFO CEikonDesktopDataAPI::m_OnStatusChangedInfo = 
{ 
	CC_STDCALL, VT_EMPTY, 1, 
	{
		VT_I4
	}
}; 

CEikonDesktopDataAPI::CEikonDesktopDataAPI(void) :
	m_eikonDesktopDataAPIEventListener(NULL),
	m_isEventAdvisedOK(false)
{
}

CEikonDesktopDataAPI::~CEikonDesktopDataAPI(void)
{
	if (m_isEventAdvisedOK)
	{
		DispEventUnadvise(m_eikonDesktopApi);
	}
}

void STDMETHODCALLTYPE CEikonDesktopDataAPI::OnStatusChanged(EEikonStatus a_eStatus)
{
	if (m_eikonDesktopDataAPIEventListener)
	{
		m_eikonDesktopDataAPIEventListener->OnStatusChanged(a_eStatus);
	}
}

HRESULT CEikonDesktopDataAPI::CreateObject()
{
	//if it has been created
	if (m_eikonDesktopApi != NULL)
	{
		return S_OK;
	}

	HRESULT l_hResult = m_eikonDesktopApi.CreateInstance(CLSID_EikonDesktopDataAPI);
	if (l_hResult == S_OK)
	{
		l_hResult = DispEventAdvise(m_eikonDesktopApi);
		if (l_hResult == S_OK)
		{
			m_isEventAdvisedOK = true;
			return S_OK;
		}
	}
	return E_FAIL;
}


EEikonDataAPIInitializeResult CEikonDesktopDataAPI::Initialize(IEikonDesktopDataAPIEventListener* a_eikonDesktopDataAPIEventListener)
{
	m_eikonDesktopDataAPIEventListener = a_eikonDesktopDataAPIEventListener;
	return m_eikonDesktopApi->Initialize();
}

EEikonStatus CEikonDesktopDataAPI::GetStatus()
{
	return m_eikonDesktopApi->GetStatus();
}

IUnknownPtr CEikonDesktopDataAPI::CreateAdxRtList(void)
{
	return m_eikonDesktopApi->CreateAdxRtList();
}

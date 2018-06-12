#pragma once
#include <atlbase.h>
#include <atlcom.h>

class CEikonDesktopDataAPI;
class IEikonDesktopDataAPIEventListener;

typedef IDispEventImpl
	<
		0, CEikonDesktopDataAPI, &DIID__IEikonDesktopDataAPIEvents, &LIBID_EikonDesktopDataAPILib, -1, -1
	>	IEikonDesktopDataAPIEventListenerImpl;
class CEikonDesktopDataAPI : IEikonDesktopDataAPIEventListenerImpl
{
public:
	CEikonDesktopDataAPI(void);
	virtual ~CEikonDesktopDataAPI(void);

	BEGIN_SINK_MAP(CEikonDesktopDataAPI)
		SINK_ENTRY_INFO(0, DIID__IEikonDesktopDataAPIEvents, 0x1, OnStatusChanged, &m_OnStatusChangedInfo)
	END_SINK_MAP()

	STDMETHOD_(void, OnStatusChanged)(EEikonStatus a_eStatus);

	HRESULT CreateObject();
	EEikonDataAPIInitializeResult Initialize(IEikonDesktopDataAPIEventListener* a_eikonDesktopDataAPIEventListener);
	EEikonStatus GetStatus();

	IUnknownPtr CreateAdxRtList(void);

private:
	static struct _ATL_FUNC_INFO m_OnStatusChangedInfo;
	IEikonDesktopDataAPIPtr	m_eikonDesktopApi;
	IEikonDesktopDataAPIEventListener* m_eikonDesktopDataAPIEventListener;

	bool m_isEventAdvisedOK;
};

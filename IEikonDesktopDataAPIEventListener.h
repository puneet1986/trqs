#pragma once

class IEikonDesktopDataAPIEventListener
{
public:
	virtual void OnStatusChanged(EEikonStatus a_eStatus) = 0;
};

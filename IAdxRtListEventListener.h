#pragma once

class IAdxRtListEventListener
{
public:
	virtual void OnUpdate(BSTR a_itemName, VARIANT a_userTag, enum RT_ItemStatus a_itemStatus) = 0;
	virtual void OnImage(RT_DataStatus a_dataStatus) = 0;
	virtual void OnTime() = 0;
	virtual void OnStatusChange(RT_ListStatus a_listStatus, RT_SourceStatus a_courceStatus, RT_RunMode a_runMode) = 0;
};


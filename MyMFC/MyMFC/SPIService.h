#pragma once
#include "XFSAPI.H"
#include "ServiceThread.h"

#define SPI_DEVICE_NAME	"ITASCamera"

class SPIService
{
	ServiceThread * m_serviceThread;
	int m_connectionRef;
	CString m_strLogicalName;
	CPtrList m_listCanceled;
	//LogLevel_t m_dwTraceLevel;
	CMapPtrToPtr m_mapService;

	BOOL IsCancel(REQUESTID ReqID);
	CMapPtrToPtr * LocateServiceMap(HSERVICE hService);
	BOOL AddListEventWnd(CPtrList *pList, HWND hWnd);
	CPtrList *LocateEventWndList(HSERVICE hService, DWORD dwEventClass);
	BOOL SetEventWnd(HSERVICE hService, DWORD dwEventClass, HWND hWnd);
	BOOL RemoveEventWnd(HSERVICE hService, DWORD dwEventClass, HWND hWnd);
	BOOL RemoveServiceMap(HSERVICE hService);
	BOOL PostEventWnd(HSERVICE hService, DWORD dwEventClass,DWORD dwEvent,WPARAM wParam, LPARAM lParam);
public:
	SPIService(void);
	~SPIService(void);

	HRESULT WFPCancelAsyncRequest ( HSERVICE hService, REQUESTID RequestID);

	HRESULT WFPClose ( HSERVICE hService, HWND hWnd, REQUESTID ReqID);

	HRESULT WFPDeregister ( HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID);

	HRESULT WFPExecute ( HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);

	HRESULT WFPGetInfo ( HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);

	HRESULT WFPLock ( HSERVICE hService, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);

	HRESULT WFPOpen ( HSERVICE hService, LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID, HPROVIDER hProvider, DWORD dwSPIVersionsRequired, LPWFSVERSION lpSPIVersion, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion);

	HRESULT WFPRegister ( HSERVICE hService,  DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID);

	HRESULT WFPSetTraceLevel ( HSERVICE hService, DWORD dwTraceLevel);

	HRESULT WFPUnloadService (  );

	HRESULT WFPUnlock ( HSERVICE hService, HWND hWnd, REQUESTID ReqID);
};


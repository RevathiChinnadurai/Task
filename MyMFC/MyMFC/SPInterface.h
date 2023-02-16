#include "XFSAPI.H"

#ifdef SPI_EXPORTS
#define SPI_API __declspec(dllexport)
#else
#define SPI_API __declspec(dllimport)
#endif

extern "C"
{
	SPI_API HRESULT WINAPI WFPCancelAsyncRequest(HSERVICE hService, REQUESTID RequestID);

	SPI_API HRESULT WINAPI WFPClose(HSERVICE hService, HWND hWnd, REQUESTID ReqID);

	SPI_API HRESULT WINAPI WFPDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID);

	SPI_API HRESULT WINAPI WFPExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);

	SPI_API HRESULT WINAPI WFPGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);

	SPI_API HRESULT WINAPI WFPLock(HSERVICE hService, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);

	SPI_API HRESULT WINAPI WFPOpen(HSERVICE hService, LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID, HPROVIDER hProvider, DWORD dwSPIVersionsRequired, LPWFSVERSION lpSPIVersion, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion);

	SPI_API HRESULT WINAPI WFPRegister(HSERVICE hService,  DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID);

	SPI_API HRESULT WINAPI WFPSetTraceLevel(HSERVICE hService, DWORD dwTraceLevel);

	SPI_API HRESULT WINAPI WFPUnloadService();

	SPI_API HRESULT WINAPI WFPUnlock(HSERVICE hService, HWND hWnd, REQUESTID ReqID);
}
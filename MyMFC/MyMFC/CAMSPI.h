#include "resource.h"		
#include "SPIService.h"
#include "SPInterface.h"

class CCAMSPIApp : public CWinApp
{
	//Single SPIService object for processing all SPI calls 
	SPIService m_service;

public:
	CCAMSPIApp();
	int CCAMSPIApp::ExitInstance();
	SPIService* GetSPIService();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCAMSPIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCAMSPIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


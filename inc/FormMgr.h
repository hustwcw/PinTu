#ifndef _FORMMGR_H_
#define _FORMMGR_H_

#include <FApp.h>
#include <FBase.h>
#include <FUi.h>
#include "Form1.h"
#include "FormHelp.h"

class FormMgr :
	public Osp::Ui::Controls::Form
{
public:
	FormMgr(void);
	virtual ~FormMgr(void);

public:
	bool Initialize();
	bool SetStarterForm(RequestId requestId, Osp::Base::Collection::IList* pArgs);
	static const RequestId REQUEST_FORM1 = 101;
	static const RequestId REQUEST_FORMHELP = 102;
	class Form1 *__pForm1;
	class FormHelp *__pFormHelp;

protected:
	void SwitchToForm(RequestId requestId, Osp::Base::Collection::IList* pArgs);


public:
	virtual void OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList* pArgs);
};

#endif

#include "FormMgr.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

FormMgr::FormMgr(void)
{
}

FormMgr::~FormMgr(void)
{
}

bool FormMgr::Initialize()
{
	result r = E_SUCCESS;
	r = Form::Construct(FORM_STYLE_NORMAL);
	SetName(L"FormMgr");
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	__pForm1 = new Form1();
	__pForm1->Initialize();
	pFrame->AddControl(*__pForm1);
	__pFormHelp = new FormHelp();
	__pFormHelp->Initialize();
	pFrame->AddControl(*__pFormHelp);
	return true;
}

bool FormMgr::SetStarterForm(RequestId requestId, Osp::Base::Collection::IList* pArgs)
{
	Form *pCurrentForm = Application::GetInstance()->GetAppFrame()->GetFrame()->GetCurrentForm();

	if (pCurrentForm == this)
		SwitchToForm(requestId, pArgs);
	else
		return false;

	return true;
}

void FormMgr::OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList* pArgs)
{
	SwitchToForm(requestId, pArgs);
}

void FormMgr::SwitchToForm(RequestId requestId, Osp::Base::Collection::IList* pArgs)
{
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

	switch(requestId)
	{
	case REQUEST_FORM1:
		{
			pFrame->SetCurrentForm(*__pForm1);
			__pForm1->Draw();
			__pForm1->Show();
		}
		break;
	case REQUEST_FORMHELP:
		{

			pFrame->SetCurrentForm(*__pFormHelp);
			__pFormHelp->Draw();
			__pFormHelp->Show();
		}
		break;
	default:
		break;
	}
}


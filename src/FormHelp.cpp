
#include "FormHelp.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Web::Controls;
using namespace Osp::App;
using namespace Osp::Graphics;

FormHelp::FormHelp(void)
{
}

FormHelp::~FormHelp(void)
{
}

bool
FormHelp::Initialize()
{
	Form::Construct(L"IDF_FORMHELP");

	return true;
}

result
FormHelp::OnInitializing(void)
{
	result r = E_SUCCESS;

	__pWeb = new Web();
	r = __pWeb->Construct(Rectangle(0, 0, 480, 800));
	r = AddControl(*__pWeb);
	__pWeb->SetFocus();

	SetSoftkeyActionId (SOFTKEY_1, AC_SOFTKEY_BACK);
	AddSoftkeyActionListener (SOFTKEY_1, *this);

	return r;
}

result
FormHelp::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
FormHelp::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	switch(actionId)
	{
	case AC_SOFTKEY_BACK:
		{
			FormMgr *pFormMgr = static_cast<FormMgr *>(pFrame->GetControl("FormMgr"));
			if (pFormMgr != null)
				pFormMgr->SendUserEvent(FormMgr::REQUEST_FORM1, null);
		}
		break;
	default:
		break;
	}
}

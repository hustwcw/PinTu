
#ifndef _FORMHELP_H_
#define _FORMHELP_H_

#include "PinTu.h"
#include <FBase.h>
#include <FUi.h>
#include <FWeb.h>
#include <FApp.h>
#include <FMedia.h>

class FormHelp :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener
{

// Construction
public:
	FormHelp(void);
	virtual ~FormHelp(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
	Osp::Web::Controls::Web*	__pWeb;
// Implementation
protected:
	static const int AC_SOFTKEY_BACK = 102;

// Generated call-back functions
public:
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

};

#endif

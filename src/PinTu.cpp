/**
 * Name        : PinTu
 * Version     : 
 * Vendor      : hustwcw@qq.com
 * Description : 
 */


#include "PinTu.h"
#include "Form1.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

bool PinTu::back=false;//初始时不在后台状态
long long PinTu::pausetime = 0;
long long PinTu::starttime = 0;
long long PinTu::restarttime = 0;
PinTu::PinTu()
{
}

PinTu::~PinTu()
{
}

Application*
PinTu::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new PinTu();
}

bool
PinTu::OnAppInitializing(AppRegistry& appRegistry)
{
	// TODO:
	// Initialize UI resources and application specific data.
	// The application's permanent data and context can be obtained from the appRegistry.
	//
	// If this method is successful, return true; otherwise, return false.
	// If this method returns false, the application will be terminated.

	// Uncomment the following statement to listen to the screen on/off events.
	//PowerManager::SetScreenEventListener(*this);

	// Create a form
	FormMgr *pFormMgr = new FormMgr();
	pFormMgr->Initialize();
	GetAppFrame()->GetFrame()->AddControl(*pFormMgr);
	pFormMgr->SetStarterForm(101, null);
	return true;
}

bool
PinTu::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	// TODO:
	// Deallocate resources allocated by this application for termination.
	// The application's permanent data and context can be saved via appRegistry.
	return true;
}

void
PinTu::OnForeground(void)
{
	// TODO:
	// Start or resume drawing when the application is moved to the foreground.
	back = false;
	SystemTime::GetTicks(restarttime);
	starttime +=(restarttime-pausetime);
}

void
PinTu::OnBackground(void)
{
	// TODO:
	// Stop drawing when the application is moved to the background.
	SystemTime::GetTicks(PinTu::pausetime);
	back = true;
}

void
PinTu::OnLowMemory(void)
{
	// TODO:
	// Free unused resources or close the application.
}

void
PinTu::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	// TODO:
	// Handle any changes in battery level here.
	// Stop using multimedia features(camera, mp3 etc.) if the battery level is CRITICAL.
}

void
PinTu::OnScreenOn (void)
{
	// TODO:
	// Get the released resources or resume the operations that were paused or stopped in OnScreenOff().
}

void
PinTu::OnScreenOff (void)
{
	// TODO:
	//  Unless there is a strong reason to do otherwise, release resources (such as 3D, media, and sensors) to allow the device to enter the sleep mode to save the battery.
	// Invoking a lengthy asynchronous method within this listener method can be risky, because it is not guaranteed to invoke a callback before the device enters the sleep mode.
	// Similarly, do not perform lengthy operations in this listener method. Any operation must be a quick one.
}

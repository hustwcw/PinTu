#ifndef _PINTU_H_
#define _PINTU_H_
#include "FormMgr.h"
#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>

/**
 * [PinTu] application must inherit from Application class
 * which provides basic features necessary to define an application.
 */
class PinTu :
	public Osp::App::Application,
	public Osp::System::IScreenEventListener
{
public:

	/**
	 * [PinTu] application must have a factory method that creates an instance of itself.
	 */
	static Osp::App::Application* CreateInstance(void);
	static bool back;
	static long long starttime;//游戏开始时间，以毫秒记
	static long long pausetime;//游戏暂停时间，以毫秒记
	static long long restarttime;//游戏重新开始时间，以毫秒记


public:
	PinTu();
	~PinTu();


public:


	// Called when the application is initializing.
	bool OnAppInitializing(Osp::App::AppRegistry& appRegistry);

	// Called when the application is terminating.
	bool OnAppTerminating(Osp::App::AppRegistry& appRegistry, bool forcedTermination = false);


	// Called when the application's frame moves to the top of the screen.
	void OnForeground(void);


	// Called when this application's frame is moved from top of the screen to the background.
	void OnBackground(void);

	// Called when the system memory is not sufficient to run the application any further.
	void OnLowMemory(void);

	// Called when the battery level changes.
	void OnBatteryLevelChanged(Osp::System::BatteryLevel batteryLevel);

	// Called when the screen turns on.
	void OnScreenOn (void);

	// Called when the screen turns off.
	void OnScreenOff (void);
};

#endif

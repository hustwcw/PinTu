#ifndef _FORM1_H_
#define _FORM1_H_

#include "PinTu.h"

#include <FApp.h>
#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FMedia.h>
#include <FSystem.h>

//一下四项定义游戏区的位置
#define CLIENTX 0
#define CLIENTY 90
#define CLIENTWIDTH 480
#define CLIENTHEIGHT 550

class Form1 :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
	public Osp::Ui::IItemEventListener,
	public Osp::Ui::ITouchEventListener,
	public Osp::Base::Runtime::ITimerEventListener
{

// Construction
public:
	Form1(void);
	virtual ~Form1(void);
	bool Initialize(void);
	virtual result OnDraw(void);

	struct site//图片块所在的位置
	{
		int x;
		int y;
	};
protected:
	static const int ID_OPTIONKEY = 100;
	static const int ID_NEWGAME = 102;
	static const int ID_SETTING = 103;
	static const int ID_IMAGE = 104;
	static const int ID_AUTOPLAY = 105;
	static const int ID_RANK = 106;
	static const int ID_HELP = 107;
	static const int ID_EXIT = 108;
	static const int ID_BUTTON_PAUSE = 110;
	static const int ID_BUTTON_PREVIEW = 111;

	static const int ID_CHECKBUTTON1 = 202;
	static const int ID_CHECKBUTTON2 = 203;
	static const int ID_CHECKBUTTON3 = 204;
	static const int ID_CHECKBUTTON4 = 205;
	static const int ID_BUTTON_OK = 206;
	static const int ID_BUTTON_CANCEL = 207;

	//图片选择ID
    static const int ID_LIST_ITEM1 = 301;
    static const int ID_LIST_ITEM2 = 302;
    static const int ID_LIST_ITEM3 = 303;
    static const int ID_LIST_ITEM4 = 304;
    static const int ID_LIST_ITEM5 = 305;
    static const int ID_LIST_ITEM6 = 306;
    static const int ID_LIST_ITEM7 = 307;
    static const int ID_LIST_ITEM8 = 308;
    static const int ID_LIST_ITEM9 = 309;
    static const int ID_LIST_ITEM10 = 310;
    static const int ID_LIST_ITEM11 = 311;
    static const int ID_LIST_ITEM12 = 312;

    //图片预览ID
    static const int ID_LIST_PREVIEW = 401;

    static const RequestId UP = 501;
    static const RequestId DOWN = 502;
    static const RequestId LEFT = 503;
    static const RequestId RIGHT = 504;

    static const int ID_BUTTON_CLOSE = 601;

    static const int ID_BUTTON_CANCELIMAGE = 701;

    Osp::Ui::Controls::Label* __pLabelTime;
    Osp::Ui::Controls::Label* __pLabelStep;
	Osp::Ui::Controls::OptionMenu* __pOptionMenu;
	Osp::Ui::Controls::Button* __pButtonPause;
	Osp::Ui::Controls::Button* __pButtonPreview;

	//难度设置POPUP
	Osp::Ui::Controls::Popup* __pPopup;
	Osp::Ui::Controls::CheckButton* __pCheckButton1;
	Osp::Ui::Controls::CheckButton* __pCheckButton2;
	Osp::Ui::Controls::CheckButton* __pCheckButton3;
	Osp::Ui::Controls::CheckButton* __pCheckButton4;
	Osp::Ui::Controls::Slider* __pSliderRows;
	Osp::Ui::Controls::Slider* __pSliderCols;
	Osp::Ui::Controls::Button* __pButtonOk;
	Osp::Ui::Controls::Button* __pButtonCancel;

	//图片选择POPUP
	Osp::Ui::Controls::Popup* __pPopupImage;
	Osp::Ui::Controls::IconList* __pImageList;

	//图片预览POPUP
	Osp::Ui::Controls::Popup* __pPopupPreview;
	Osp::Ui::Controls::IconList* __pPreviewList;
	Osp::Ui::Controls::Button* __pButtonCancelImage;

	Osp::Graphics::Bitmap* GetBitmapN(const Osp::Base::String& name);


private:
	Osp::App::AppRegistry * pAppRegistry;
	//下面四条为配置信息
	int m_iCols;
	int m_iRows;
	Osp::Base::String m_strImagePath;
	Osp::Graphics::Color m_colorBlank;
	Osp::Graphics::Bitmap* __pBitmap;

	//Osp::Base::String m_strInfo;//提示信息
	int tracksteps;//跟踪移动的步数
	int tempsteps;//用于自动拼图，按记录的空白块移动方向原路返回

	int steps;//游戏者移动的步数
	struct site blanksite;//空白块所在位置
	struct site siteinfo[11][11];//各图片块所在的位置
	int cellwidth;//图片块宽度
	int cellheight;//图片块高度
    byte track[1001];//保存每一步空白块移动的方向
	bool autoplay;//是否自动拼图
	bool pause;//是否暂停
	bool start;//是否已经开始游戏
	bool win;
	Osp::Base::Runtime::Timer* __pTimer;
	Osp::Base::Runtime::Timer* __pRefreshTimeTimer;

	void InitialString();//初始化字符串资源
	void WinOrNot();//是否已经完成
	void InitialSetting();//初始化配置
	void InitialGame1();//初始化游戏图片
	void InitialGame2();//初始化新游戏游戏
	void PaintTimeAndStep();//刷新时间与步数
	void PaintPic(struct site destsite ,  struct site srcsite);//将图片从源位置移动到目标位置
	void PaintBlank();//绘制黑色空白图片块
	void PaintLine();//绘制边线
	void InitialSiteinfo();//初始化位置信息
	void Prelook();//预览图片
	//void OnUserpic();//自定义图片

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
	virtual void OnItemStateChanged(const Osp::Ui::Control &source, int index,
			int itemId, Osp::Ui::ItemStatus status);
	virtual void OnTouchDoublePressed (const Osp::Ui::Control &source,
			const Osp::Graphics::Point &currentPosition,
			const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchFocusIn (const Osp::Ui::Control &source,
			const Osp::Graphics::Point &currentPosition,
			const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchFocusOut (const Osp::Ui::Control &source,
			const Osp::Graphics::Point &currentPosition,
			const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchLongPressed (const Osp::Ui::Control &source,
			const Osp::Graphics::Point &currentPosition,
			const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchMoved (const Osp::Ui::Control &source,
			const Osp::Graphics::Point &currentPosition,
			const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchPressed (const Osp::Ui::Control &source,
			const Osp::Graphics::Point &currentPosition,
			const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchReleased (const Osp::Ui::Control &source,
			const Osp::Graphics::Point &currentPosition,
			const Osp::Ui::TouchEventInfo &touchInfo);

	virtual void OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList* pArgs);

	virtual void OnTimerExpired (Osp::Base::Runtime::Timer &timer);

public:
	Osp::Base::String strTime;
	Osp::Base::String strSteps;
	Osp::Base::String strPause;
	Osp::Base::String strPreview;
	Osp::Base::String strNew;
	Osp::Base::String strDifficulty;
	Osp::Base::String strSelection;
	Osp::Base::String strAutoPlay;
	Osp::Base::String strHelp;
	Osp::Base::String strExit;
	Osp::Base::String strJunior;
	Osp::Base::String strIntermediate;
	Osp::Base::String strSenior;
	Osp::Base::String strCustom;
	Osp::Base::String strLines;
	Osp::Base::String strCols;
	Osp::Base::String strOK;
	Osp::Base::String strCancel;
	Osp::Base::String strComplete;
	Osp::Base::String strRestart;
	Osp::Base::String strBack;
	Osp::Base::String strCongratulations;
	Osp::Base::String strStopAutoPlay;
	Osp::Base::String strContinue;
	Osp::Base::String strAutoPlayCompleted;
	Osp::Base::String strAutoPlayCompletedContent;
	/*
	Osp::Base::String strCancel;
	Osp::Base::String strCancel;
	Osp::Base::String strCancel;
	Osp::Base::String strCancel;
	Osp::Base::String strCancel;
	Osp::Base::String strCancel;
	Osp::Base::String strCancel;
	Osp::Base::String strCancel;
	Osp::Base::String strCancel;
	*/
};

#endif	//_FORM1_H_

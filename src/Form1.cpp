#include "Form1.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;
using namespace Osp::Media;
using namespace Osp::Base::Utility;
using namespace Osp::System;
using namespace Osp::Base::Runtime;

Form1::Form1(void):
__pLabelTime(null),
__pLabelStep(null),
__pOptionMenu(null),
__pButtonPause(null),
__pButtonPreview(null),
__pPopup(null),
__pCheckButton1(null),
__pCheckButton2(null),
__pCheckButton3(null),
__pCheckButton4(null),
__pPopupImage(null),
__pImageList(null),
__pPopupPreview(null),
__pPreviewList(null),
pAppRegistry(null),
m_iCols(3),
m_iRows(3),
m_strImagePath(L"game1.jpg"),
m_colorBlank(Color::COLOR_BLACK),
__pBitmap(null)
{

}

Form1::~Form1(void)
{
}

bool
Form1::Initialize()
{
	// Construct an XML form
	Construct(L"IDF_FORM1");

	return true;
}

result
Form1::OnInitializing(void)
{
	AppLog("OnInitializing");
	result r = E_SUCCESS;
	InitialString();
	InitialSetting();

    __pLabelTime = static_cast<Label *>(GetControl(L"IDC_LABEL_TIME"));
    __pLabelStep = static_cast<Label *>(GetControl(L"IDC_LABEL_STEP"));
	__pButtonPause = static_cast<Button *>(GetControl(L"IDC_BUTTON_PAUSE"));
	__pButtonPause->SetActionId(ID_BUTTON_PAUSE);
	__pButtonPause->AddActionEventListener(*this);
	__pButtonPreview = static_cast<Button *>(GetControl(L"IDC_BUTTON_PREVIEW"));
	__pButtonPreview->SetActionId(ID_BUTTON_PREVIEW);
	__pButtonPreview->AddActionEventListener(*this);

	__pTimer = new Timer();
	__pTimer->Construct(*this);

	__pRefreshTimeTimer = new Timer();
	__pRefreshTimeTimer->Construct(*this);
	//添加触摸事件监听器
	AddTouchEventListener(*this);

	//Optionkey事件
	SetOptionkeyActionId(ID_OPTIONKEY);
	AddOptionkeyActionListener(*this);
	__pOptionMenu = new OptionMenu();
	__pOptionMenu->Construct();
	__pOptionMenu->AddItem(strNew,ID_NEWGAME);
	__pOptionMenu->AddItem(strDifficulty,ID_SETTING);
	__pOptionMenu->AddItem(strSelection,ID_IMAGE);
	__pOptionMenu->AddItem(strAutoPlay,ID_AUTOPLAY);
	//__pOptionMenu->AddItem(L"排行榜",ID_RANK);
	__pOptionMenu->AddItem(strHelp,ID_HELP);
	__pOptionMenu->AddItem(strExit,ID_EXIT);
	__pOptionMenu->AddActionEventListener(*this);

	__pPopup = new Popup();
	__pPopup->Construct(L"IDP_POPUP_SETTING");
    __pCheckButton1 = static_cast<CheckButton *>(__pPopup->GetControl(L"IDC_CHECKBUTTON1"));
	__pCheckButton1->SetActionId(ID_CHECKBUTTON1,-1);
	__pCheckButton1->AddActionEventListener(*this);
    __pCheckButton2 = static_cast<CheckButton *>(__pPopup->GetControl(L"IDC_CHECKBUTTON2"));
	__pCheckButton2->SetActionId(ID_CHECKBUTTON2,-1);
	__pCheckButton2->AddActionEventListener(*this);
    __pCheckButton3 = static_cast<CheckButton *>(__pPopup->GetControl(L"IDC_CHECKBUTTON3"));
	__pCheckButton3->SetActionId(ID_CHECKBUTTON3,-1);
	__pCheckButton3->AddActionEventListener(*this);
    __pCheckButton4 = static_cast<CheckButton *>(__pPopup->GetControl(L"IDC_CHECKBUTTON4"));
	__pCheckButton4->SetActionId(ID_CHECKBUTTON4,-1);
	__pCheckButton4->AddActionEventListener(*this);
	__pSliderRows = static_cast<Slider *>(__pPopup->GetControl(L"IDC_SLIDER_ROWS"));
	__pSliderCols = static_cast<Slider *>(__pPopup->GetControl(L"IDC_SLIDER_COLS"));
	__pSliderRows->SetEnabled(false);
	__pSliderCols->SetEnabled(false);
	__pSliderRows->SetValue(m_iRows);
	__pSliderCols->SetValue(m_iCols);
	__pButtonCancel = static_cast<Button *>(__pPopup->GetControl(L"IDC_BUTTON_CANCEL"));
	__pButtonCancel->SetActionId(ID_BUTTON_CANCEL);
	__pButtonCancel->AddActionEventListener(*this);
	__pButtonOk = static_cast<Button *>(__pPopup->GetControl(L"IDC_BUTTON_OK"));
	__pButtonOk->SetActionId(ID_BUTTON_OK);
	__pButtonOk->AddActionEventListener(*this);

	//选择图片popup
	__pPopupImage = new Popup();
	__pPopupImage->Construct(L"IDP_POPUP_IMAGE");
	__pImageList = static_cast<IconList *>(__pPopupImage->GetControl(L"IDC_ICONLIST_LIST"));
	__pImageList->AddItemEventListener(*this);
	__pButtonCancelImage = static_cast<Button *>(__pPopupImage->GetControl(L"IDC_BUTTON_CANCELIMAGE"));
	__pButtonCancelImage->SetActionId(ID_BUTTON_CANCELIMAGE);
	__pButtonCancelImage->AddActionEventListener(*this);

	int i;
	String BitmapName(L"game");
	Bitmap *pListBitmap;
	String itemText(L"Item");
	for(i=1;i<=12;i++)
	{
		BitmapName.Append(i);
		BitmapName.Append(L".jpg");
		itemText.Append(i);
		pListBitmap = GetBitmapN(BitmapName);
	    __pImageList->AddItem(&itemText,
	    		pListBitmap, pListBitmap, ID_LIST_ITEM1+i-1);
	    BitmapName.SubString(0,4,BitmapName);
	    itemText.SubString(0,4,itemText);
	}
	delete pListBitmap;
    itemText.Clear();
	__pPopupPreview = new Popup();
	__pPopupPreview->Construct(L"IDP_POPUP_PREVIEW");
	__pPreviewList = static_cast<IconList *>(__pPopupPreview->GetControl(L"IDC_ICONLIST_PREVIEW"));
	__pPreviewList->AddItemEventListener(*this);
	__pPreviewList->AddItem(&itemText, __pBitmap, __pBitmap, ID_LIST_PREVIEW);
	__pBitmap = GetBitmapN(m_strImagePath);//恢复Bitmap

    InitialGame1();

	return r;
}

result
Form1::OnDraw(void)
{
	result r = E_SUCCESS;
	if(pause == false)//暂停后不更新游戏区
	{
		int i;
		int j;
		struct site destsite;
		struct site srcsite;
		for(i = 1;i<=m_iCols;i++)
		{
			for(j = 1;j<=m_iRows;j++)
			{
				srcsite.x = siteinfo[i][j].x;
				srcsite.y = siteinfo[i][j].y;
				destsite.x = i;
				destsite.y = j;
				PaintPic(destsite, srcsite);
			}
		}
		PaintLine();
		if(win != true){PaintBlank();}
		if(win == true)
		{
			win = false;
			//__pRefreshTimeTimer->Cancel();
			MessageBox messageBox;
			String WinReport(L"");
			WinReport.Append(strCongratulations);
			WinReport.Append(L"\n");
			WinReport.Append(__pLabelTime->GetText());
			WinReport.Append(L"\n");
			WinReport.Append(__pLabelStep->GetText());
			messageBox.Construct(strComplete, WinReport, MSGBOX_STYLE_OK);
			int modalResult = 0;
			messageBox.ShowAndWait(modalResult);
			InitialGame1();
		}


	}
	else
	{
		Canvas* pCanvas = GetCanvasN(CLIENTX, CLIENTY, CLIENTWIDTH, CLIENTHEIGHT);
		pCanvas->DrawBitmap(Point(0,0), *__pBitmap);
		delete pCanvas;
	}

	if(start == true)
	{
		WinOrNot();//判断是否已赢得这局游戏
	}
	return r;
}

result
Form1::OnTerminating(void)
{
	result r = E_SUCCESS;

    String rowsKey("Rows");
    String colsKey("cols");
    String imagepathKey("imagepath");
	pAppRegistry->Set(rowsKey,m_iRows);
	pAppRegistry->Set( colsKey,m_iCols);
	pAppRegistry->Set(imagepathKey, m_strImagePath);
	pAppRegistry->Save();

	//delete  MessageBox, Popup, ContextMenu, and OptionMenu.
	//delete pAppRegistry;
	delete __pBitmap;
	delete __pPopup;
	delete __pPopupImage;
	delete __pPopupPreview;
	delete __pOptionMenu;
	delete __pRefreshTimeTimer;
	delete __pTimer;
	return r;
}

Osp::Graphics::Bitmap*
Form1::GetBitmapN(const Osp::Base::String& name)
{
	//AppLog("GetBitmapN");
	Bitmap* pBitmap = null;
	String fullname(L"/Res/");
	Image* pImage = new Image();
	pImage->Construct();
	fullname.Append(name);

	if(fullname.EndsWith(L"jpg"))
	{
		pBitmap = pImage->DecodeN(fullname, BITMAP_PIXEL_FORMAT_RGB565);
	}
	else if(fullname.EndsWith(L"bmp"))
	{
		pBitmap = pImage->DecodeN(fullname, BITMAP_PIXEL_FORMAT_RGB565);
	}
	else if(fullname.EndsWith(L"png"))
	{
		pBitmap = pImage->DecodeN(fullname, BITMAP_PIXEL_FORMAT_ARGB8888);
	}
	else if (fullname.EndsWith(L"gif"))
	{
		pBitmap = pImage->DecodeN(fullname, BITMAP_PIXEL_FORMAT_RGB565);
	}

	delete pImage;
	return pBitmap;
}

void
Form1::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
    String rowsKey("Rows");
    String colsKey("cols");
    String itemText(L"");
    Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	switch(actionId)
	{
	case ID_BUTTON_PAUSE:
		if(pause == true)
		{
			//显示游戏区
			AppLog("RESTART GAME");
			__pButtonPause->SetText(strPause);
			RequestRedraw();
			SystemTime::GetTicks(PinTu::restarttime);
			PinTu::starttime +=(PinTu::restarttime-PinTu::pausetime);
			__pRefreshTimeTimer->Start(1000);
			pause = false;
			start = true;
		}else if(pause == false && start == true)
		{
			//重新绘制将游戏区覆盖，并记录游戏已暂停
			AppLog("PAUSE GAME");
			SystemTime::GetTicks(PinTu::pausetime);
			__pButtonPause->SetText(strContinue);
			__pButtonPause->Draw();
			__pButtonPause->Show();
			Canvas* pCanvas = GetCanvasN(CLIENTX, CLIENTY, CLIENTWIDTH, CLIENTHEIGHT);
			pCanvas->DrawBitmap(Point(0,0), *__pBitmap);
			pCanvas->Show();
			delete pCanvas;
			pause = true;
			start = false;
		}
		break;
	case ID_BUTTON_PREVIEW:
		__pPreviewList->SetItemAt(0,&itemText, __pBitmap, __pBitmap, ID_LIST_PREVIEW);
		__pBitmap = GetBitmapN(m_strImagePath);
	    __pPopupPreview->SetShowState(true);
	    __pPopupPreview->Show();
		break;
	case ID_OPTIONKEY:
		{
			// Display the OptionMenu
			if (__pOptionMenu != null)
				__pOptionMenu->SetShowState(true);
			__pOptionMenu->Show();
		}
		break;
	case ID_NEWGAME:
		AppLog("ID_NEWGAME");
		//开始新游戏
		InitialGame1();
		InitialGame2();
		break;
	case ID_SETTING:
		//难度设置
	    __pPopup->SetShowState(true);
	    __pPopup->Show();
	    break;
	case ID_IMAGE:
		//选择图片
	    __pPopupImage->SetShowState(true);
	    __pPopupImage->Show();
		break;
	case ID_AUTOPLAY:
		//自动拼图
		tempsteps=tracksteps;
		if(autoplay==false)
		{
			start = false;
			if(tempsteps>0)
			{
				autoplay=true;
				__pOptionMenu->SetItemAt(3, strStopAutoPlay, ID_AUTOPLAY);
				__pTimer->Start(300);
			}
		}
		else
		{
			autoplay=false;
			__pOptionMenu->SetItemAt(3, strAutoPlay, ID_AUTOPLAY);
		}
		break;
	case ID_HELP:
		//转向帮助Form
		{
			FormMgr *pFormMgr = static_cast<FormMgr *>(pFrame->GetControl("FormMgr"));
			pFormMgr->__pFormHelp->__pWeb->LoadUrl("/Res/help.html");
			if (pFormMgr != null)
				pFormMgr->SendUserEvent(FormMgr::REQUEST_FORMHELP, null);
		}
		break;
	case ID_EXIT:
		//退出程序
		Application::GetInstance()->Terminate();
		break;
	case ID_CHECKBUTTON1:
		__pSliderRows->SetValue(3);
		__pSliderCols->SetValue(3);
		__pSliderRows->SetEnabled(false);
		__pSliderCols->SetEnabled(false);
		__pSliderRows->Draw();
		__pSliderRows->Show();
		__pSliderCols->Draw();
		__pSliderCols->Show();
		break;
	case ID_CHECKBUTTON2:
		__pSliderRows->SetValue(5);
		__pSliderCols->SetValue(5);
		__pSliderRows->SetEnabled(false);
		__pSliderCols->SetEnabled(false);
		__pSliderRows->Draw();
		__pSliderRows->Show();
		__pSliderCols->Draw();
		__pSliderCols->Show();
		break;
	case ID_CHECKBUTTON3:
		__pSliderRows->SetValue(7);
		__pSliderCols->SetValue(7);
		__pSliderRows->SetEnabled(false);
		__pSliderCols->SetEnabled(false);
		__pSliderRows->Draw();
		__pSliderRows->Show();
		__pSliderCols->Draw();
		__pSliderCols->Show();
		break;
	case ID_CHECKBUTTON4:
		__pSliderRows->SetEnabled(true);
		__pSliderCols->SetEnabled(true);
		__pSliderRows->Draw();
		__pSliderRows->Show();
		__pSliderCols->Draw();
		__pSliderCols->Show();
		break;
	case ID_BUTTON_OK:
		//确定更改难度
		m_iRows = __pSliderRows->GetValue();
		m_iCols = __pSliderCols->GetValue();
		InitialGame1();
		InitialGame2();
		__pPopup->SetShowState(false);
		RequestRedraw();
		break;
    case ID_BUTTON_CANCEL:
    	//取消更改难度
    	__pPopup->SetShowState(false);
    	RequestRedraw();
    	break;
    case ID_BUTTON_CANCELIMAGE:
    	//关闭选取图片POPUP
    	__pPopupImage->SetShowState(false);
    	RequestRedraw();
    	break;
	default:
		break;
	}
}

void
Form1::OnItemStateChanged (const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status)
{
	String imagepathKey("imagepath");
    switch (itemId)
    {
        case ID_LIST_ITEM1:
        	m_strImagePath = L"game1.jpg";
        	InitialGame1();
    		InitialGame2();
        	__pPopupImage->SetShowState(false);
        	Draw();
        	Show();
            break;
        case ID_LIST_ITEM2:
        	m_strImagePath = L"game2.jpg";
        	InitialGame1();
    		InitialGame2();
        	__pPopupImage->SetShowState(false);
        	Draw();
        	Show();
            break;
        case ID_LIST_ITEM3:
        	m_strImagePath = L"game3.jpg";
        	InitialGame1();
    		InitialGame2();
        	__pPopupImage->SetShowState(false);
        	Draw();
        	Show();
            break;
        case ID_LIST_ITEM4:
        	m_strImagePath = L"game4.jpg";
        	InitialGame1();
    		InitialGame2();
        	__pPopupImage->SetShowState(false);
        	Draw();
        	Show();
            break;
        case ID_LIST_ITEM5:
        	m_strImagePath = L"game5.jpg";
        	InitialGame1();
    		InitialGame2();
        	__pPopupImage->SetShowState(false);
        	Draw();
        	Show();
            break;
        case ID_LIST_ITEM6:
        	m_strImagePath = L"game6.jpg";
        	InitialGame1();
    		InitialGame2();
        	__pPopupImage->SetShowState(false);
        	Draw();
        	Show();
            break;
        case ID_LIST_ITEM7:
        	m_strImagePath = L"game7.jpg";
        	InitialGame1();
    		InitialGame2();
        	__pPopupImage->SetShowState(false);
        	Draw();
        	Show();
            break;
        case ID_LIST_ITEM8:
        	m_strImagePath = L"game8.jpg";
        	InitialGame1();
    		InitialGame2();
        	__pPopupImage->SetShowState(false);
        	Draw();
        	Show();
            break;
        case ID_LIST_ITEM9:
        	m_strImagePath = L"game9.jpg";
        	InitialGame1();
    		InitialGame2();
        	__pPopupImage->SetShowState(false);
        	Draw();
        	Show();
            break;
        case ID_LIST_ITEM10:
        	m_strImagePath = L"game10.jpg";
        	InitialGame1();
    		InitialGame2();
        	__pPopupImage->SetShowState(false);
        	Draw();
        	Show();
            break;
        case ID_LIST_ITEM11:
        	m_strImagePath = L"game11.jpg";
        	InitialGame1();
    		InitialGame2();
        	__pPopupImage->SetShowState(false);
        	Draw();
        	Show();
            break;
        case ID_LIST_ITEM12:
        	m_strImagePath = L"game12.jpg";
        	InitialGame1();
    		InitialGame2();
        	__pPopupImage->SetShowState(false);
        	Draw();
        	Show();
            break;
        case ID_LIST_PREVIEW:
        	__pPopupPreview->SetShowState(false);
        	Draw();
        	Show();
        	break;
        default:
            break;
    }
}


void
Form1::OnTouchDoublePressed (const Osp::Ui::Control &source,
		const Osp::Graphics::Point &currentPosition,
		const Osp::Ui::TouchEventInfo &touchInfo)
{

}
void
Form1::OnTouchFocusIn (const Osp::Ui::Control &source,
		const Osp::Graphics::Point &currentPosition,
		const Osp::Ui::TouchEventInfo &touchInfo)
{

}
void
Form1::OnTouchFocusOut (const Osp::Ui::Control &source,
		const Osp::Graphics::Point &currentPosition,
		const Osp::Ui::TouchEventInfo &touchInfo)
{

}
void
Form1::OnTouchLongPressed (const Osp::Ui::Control &source,
		const Osp::Graphics::Point &currentPosition,
		const Osp::Ui::TouchEventInfo &touchInfo)
{

}
void
Form1::OnTouchMoved (const Osp::Ui::Control &source,
		const Osp::Graphics::Point &currentPosition,
		const Osp::Ui::TouchEventInfo &touchInfo)
{

}
void
Form1::OnTouchPressed (const Osp::Ui::Control &source,
		const Osp::Graphics::Point &currentPosition,
		const Osp::Ui::TouchEventInfo &touchInfo)
{
	//AppLog("source:h[%d], w(%d)", source.GetHeight(), source.GetWidth());
	//AppLog("currentPosition:x[%d], y[%d]", currentPosition.x, currentPosition.y);
    //AppLog("touchinfo:[%d]%d,%d", touchInfo.GetPointId(), currentPosition.x, currentPosition.y);
	if(pause == false)
	{
		struct site touchsite;
		touchsite.x =(currentPosition.x-CLIENTX)/cellwidth+1;
		touchsite.y =(currentPosition.y-CLIENTY)/cellheight+1;
		if(Math::Abs(touchsite.x-blanksite.x)+Math::Abs(touchsite.y-blanksite.y)==1)
		{
			if(touchsite.x - blanksite.x == 1)
			{
				//AppLog("RIGHT");
				SendUserEvent(Form1::RIGHT, null);
			}
			else if(touchsite.x - blanksite.x == -1)
			{
				//AppLog("LEFT");
				SendUserEvent(Form1::LEFT, null);
			}
			else if(touchsite.y - blanksite.y == 1)
			{
				//AppLog("DOWN");
				SendUserEvent(Form1::DOWN, null);
			}
			else if(touchsite.y - blanksite.y == -1)
			{
				//AppLog("UP");
				SendUserEvent(Form1::UP, null);
			}
			steps+=1;
			if(start == false)//还没有开始游戏则触摸后开始游戏
			{
				start = true;
				SystemTime::GetTicks(PinTu::starttime);
				__pRefreshTimeTimer->Start(1000);
			}
			PaintTimeAndStep();
		}
	}
}
void
Form1::OnTouchReleased (const Osp::Ui::Control &source,
		const Osp::Graphics::Point &currentPosition,
		const Osp::Ui::TouchEventInfo &touchInfo)
{

}

void
Form1::OnTimerExpired(Timer& timer)
{
	AppLog("OnTimerExpired");
	if(start == true)//timer.Equals(*__pRefreshTimeTimer)
	{
		if(PinTu::back == false)
		{
			PaintTimeAndStep();
		}
		__pRefreshTimeTimer->Start(1000);
	}
	else if(autoplay == true)//timer.Equals(*__pTimer)
	{
		if(PinTu::back == false)
		{
			//进行自动拼图操作
			switch(track[tempsteps])
			{
			case 1:
				SendUserEvent(Form1::RIGHT, null);
				break;
			case 2:
				SendUserEvent(Form1::LEFT, null);
				break;
			case 3:
				SendUserEvent(Form1::DOWN, null);
				break;
			case 4:
				SendUserEvent(Form1::UP, null);
				break;
			}
			tempsteps-=1;

		}
			if(tracksteps==0)
			{
				__pTimer->Cancel();
				PaintPic(blanksite,blanksite);
				autoplay=false;
				__pOptionMenu->SetItemAt(3, strAutoPlay, ID_AUTOPLAY);
				MessageBox messageBox;
				messageBox.Construct(strAutoPlayCompleted, strAutoPlayCompletedContent, MSGBOX_STYLE_OK);
				int modalResult = 0;
				messageBox.ShowAndWait(modalResult);
				InitialGame1();
			}
			else
			{
				__pTimer->Start(300);
			}
	}
}

void Form1::InitialSiteinfo()
{
	AppLog("InitialSiteinfo");
	int i,j;
	for(i=1;i<=m_iCols;i++)
	{
		for(j=1;j<=m_iRows;j++)
		{
			siteinfo[i][j].x =i;
			siteinfo[i][j].y =j;
		}
	}
	return;

}

void Form1::PaintTimeAndStep()
{
	AppLog("PaintTimeAndStep");
	String Time(strTime);
	String Steps(strSteps);
	long long currenttime;
	int min;
	int sec;
	Canvas* pCanvas = GetCanvasN(CLIENTX, CLIENTY, CLIENTWIDTH, CLIENTHEIGHT);
	SystemTime::GetTicks(currenttime);
	min = (currenttime-PinTu::starttime)/1000/60;
	sec = (currenttime-PinTu::starttime)/1000%60;
	if(min<10)Time.Append("0");
	Time.Append(min);Time.Append(":");
	if(sec<10)Time.Append("0");
	Time.Append(sec);
	__pLabelTime->SetText(Time);
	Steps.Append(steps);
	__pLabelStep->SetText(Steps);
	RequestRedraw();
	delete pCanvas;
	return;
}
void Form1::PaintPic(struct site destsite, struct site srcsite)
{
	result r = E_SUCCESS;
	Canvas* pCanvas = GetCanvasN(CLIENTX, CLIENTY, CLIENTWIDTH, CLIENTHEIGHT);
	if(pCanvas)
	{
		r = pCanvas->DrawBitmap(Rectangle((destsite.x-1)*cellwidth,(destsite.y-1)*cellheight,cellwidth,cellheight),
				*__pBitmap, Rectangle((srcsite.x-1)*cellwidth,(srcsite.y-1)*cellheight,cellwidth,cellheight));
	}
	if(pCanvas)
	{
		delete pCanvas;
	}
	return;
}


void Form1::PaintLine()
{
	int i;
	Canvas* pCanvas = GetCanvasN(CLIENTX, CLIENTY, CLIENTWIDTH, CLIENTHEIGHT);
	if(pCanvas)
	{
		pCanvas->SetLineWidth(2);
		for(i=1;i<m_iCols;i++)
		{
			pCanvas->DrawLine(Point(i*cellwidth-1,0), Point(i*cellwidth-1,CLIENTHEIGHT));
		}
		for(i=1;i<m_iRows;i++)
		{
			pCanvas->DrawLine(Point(0,i*cellheight-1), Point(CLIENTWIDTH,i*cellheight-1));
		}
	}
	if(pCanvas)
	{
		delete pCanvas;
	}
	return;

}

void Form1::PaintBlank()
{
	Canvas* pCanvas = GetCanvasN(CLIENTX, CLIENTY, CLIENTWIDTH, CLIENTHEIGHT);
	if(pCanvas)
	{
		pCanvas->FillRectangle(m_colorBlank,
				Rectangle((blanksite.x-1)*cellwidth, (blanksite.y -1)*cellheight,
						cellwidth, cellheight));
	}
	if(pCanvas)
	{
		delete pCanvas;
	}
	return;
}

void Form1::InitialSetting()
{
	AppLog("InitialSetting");
	result r = E_SUCCESS;
	//从注册表中读出配置信息并初始化
    pAppRegistry = Application::GetInstance()->GetAppRegistry();
    String rowsKey("Rows");
    String colsKey("cols");
    String imagepathKey("imagepath");
    String blankcolorKey("blankcolor");
    r = pAppRegistry->Get(rowsKey, m_iRows);
    if ( r == E_KEY_NOT_FOUND)
    {
    	//AppLog("m_iRows");
        pAppRegistry->Add(rowsKey, m_iRows);
    }

    r = pAppRegistry->Get(colsKey, m_iCols);
    if ( r == E_KEY_NOT_FOUND)
    {
    	//AppLog("m_iCols");
        pAppRegistry->Add(colsKey, m_iCols);
    }

    r = pAppRegistry->Get(imagepathKey, m_strImagePath);
    if ( r == E_KEY_NOT_FOUND)
    {
    	//AppLog("m_strImagePath");
        pAppRegistry->Add(imagepathKey, m_strImagePath);
    }

    r = pAppRegistry->Save();
    if( IsFailed(r))
    {
    	AppLog("failed to save data to registry.");
    }
}

void Form1::InitialGame1()
{
	AppLog("InitialGame1");
    //重新开始游戏则修改信息，否则不修改，游戏的前期初始化，还没有乱序
    blanksite.x =m_iCols;
    blanksite.y =m_iRows;
    tracksteps=0;
    steps = 0;
    tempsteps=0;
    autoplay=false;
    pause = false;
    start = false;
    //win = false;
    cellwidth=CLIENTWIDTH/m_iCols;
    cellheight=CLIENTHEIGHT/m_iRows;
    __pLabelTime->SetText(strTime+L"00:00");
    __pLabelStep->SetText(strSteps+L"0");
    __pButtonPause->SetText(strPause);
    __pBitmap = GetBitmapN(m_strImagePath);
    InitialSiteinfo();
}

void Form1::InitialGame2()
{
	AppLog("InitialGame2");
	int i,temp;
	long long time;
	int n = m_iRows*m_iCols*10;
	SystemTime::GetTicks(time);
	Math::Srand(int(time)/1000);
	struct site tempsite;
	for(i=1;i<n;i++)
	{
		if(i >= (n>>2)-m_iRows && i < (n>>2))
		{
			temp = 0;
		}
		else if(i >= (n>>2) && i< (n>>2)+m_iCols)//将空白块移至左上角
		{
			temp = 2;
		}
		else
		{
			temp=Math::Rand()%4;
		}
		switch(temp)
		{
		case 0:
			if(blanksite.y>1)
			{
				tracksteps+=1;
				if(tracksteps>1000)
				{
					//MessageBox("所定义数组空间已用完，你水平太臭了！","俄罗斯方块游戏",MB_OK|MB_ICONINFORMATION);
				}
				track[tracksteps]=3;
				tempsite.x =blanksite.x;
				tempsite.y =blanksite.y-1 ;
				siteinfo[blanksite.x][blanksite.y].x = siteinfo[tempsite.x][tempsite.y].x;
	            siteinfo[blanksite.x][blanksite.y].y = siteinfo[tempsite.x][tempsite.y].y;
	            tempsite.x = siteinfo[blanksite.x][blanksite.y].x;
	            tempsite.y = siteinfo[blanksite.x][blanksite.y].y;
	            blanksite.y = blanksite.y - 1;
	            if(tracksteps > 1)
				{
	                if(track[tracksteps - 1]== 4)//如果上一步空白块向下移动
					{
	                    tracksteps = tracksteps - 2;//跟踪步数减2
	                }
	            }
			}
			break;
		case 1:
			if(blanksite.y<m_iRows)
			{
				tracksteps+=1;
				if(tracksteps>1000)
				{
					//MessageBox("所定义数组空间已用完，你水平太臭了！","俄罗斯方块游戏",MB_OK|MB_ICONINFORMATION);
				}
				track[tracksteps]=4;
				tempsite.x =blanksite.x;
				tempsite.y =blanksite.y+1 ;
				siteinfo[blanksite.x][blanksite.y].x = siteinfo[tempsite.x][tempsite.y].x;
	            siteinfo[blanksite.x][blanksite.y].y = siteinfo[tempsite.x][tempsite.y].y;
	            tempsite.x = siteinfo[blanksite.x][blanksite.y].x;
	            tempsite.y = siteinfo[blanksite.x][blanksite.y].y;
	            blanksite.y = blanksite.y + 1;
	            if(tracksteps > 1)
				{
	                if(track[tracksteps - 1]== 3)//如果上一步空白块向上移动
					{
	                    tracksteps = tracksteps - 2;
	                }
	            }
			}
			break;
		case 2:
			if(blanksite.x>1)
			{
				tracksteps+=1;
				if(tracksteps>1000)
				{
					//MessageBox("所定义数组空间已用完，你水平太臭了！","俄罗斯方块游戏",MB_OK|MB_ICONINFORMATION);
				}
				track[tracksteps]=1;
				tempsite.x =blanksite.x-1;
				tempsite.y =blanksite.y ;
				siteinfo[blanksite.x][blanksite.y].x = siteinfo[tempsite.x][tempsite.y].x;
	            siteinfo[blanksite.x][blanksite.y].y = siteinfo[tempsite.x][tempsite.y].y;
	            tempsite.x = siteinfo[blanksite.x][blanksite.y].x;
	            tempsite.y = siteinfo[blanksite.x][blanksite.y].y;
	            blanksite.x = blanksite.x - 1;
	            if(tracksteps > 1)
				{
	                if(track[tracksteps - 1]== 2)//如果上一步空白块向右移动
					{
	                    tracksteps = tracksteps - 2;
	                }
	            }
			}
			break;
		case 3:
			if(blanksite.x<m_iCols)
			{
				tracksteps+=1;
				if(tracksteps>1000)
				{
					//MessageBox("所定义数组空间已用完，你水平太臭了！","俄罗斯方块游戏",MB_OK|MB_ICONINFORMATION);
				}
				track[tracksteps]=2;
				tempsite.x =blanksite.x+1;
				tempsite.y =blanksite.y ;
				siteinfo[blanksite.x][blanksite.y].x = siteinfo[tempsite.x][tempsite.y].x;
	            siteinfo[blanksite.x][blanksite.y].y = siteinfo[tempsite.x][tempsite.y].y;
	            tempsite.x = siteinfo[blanksite.x][blanksite.y].x;
	            tempsite.y = siteinfo[blanksite.x][blanksite.y].y;
	            blanksite.x = blanksite.x + 1;
	            if(tracksteps > 1)
				{
	                if(track[tracksteps - 1]== 1)//如果上一步空白块向左移动
					{
	                    tracksteps = tracksteps - 2;
	                }
	            }
			}
			break;
		default:
			break;
		}
	}
	RequestRedraw();
}

void Form1::OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList* pArgs)
{
	struct site tempsite;
	switch(requestId)
	{
	case UP:
		if(blanksite.y>1)
		{
			tracksteps+=1;
			if(tracksteps>1000)
			{
				//MessageBox("所定义数组空间已用完，你水平太臭了！","俄罗斯方块游戏",MB_OK|MB_ICONINFORMATION);
			}
			track[tracksteps]=3;
			tempsite.x =blanksite.x;
			tempsite.y =blanksite.y-1 ;
			siteinfo[blanksite.x][blanksite.y].x = siteinfo[tempsite.x][tempsite.y].x;
            siteinfo[blanksite.x][blanksite.y].y = siteinfo[tempsite.x][tempsite.y].y;
            tempsite.x = siteinfo[blanksite.x][blanksite.y].x;
            tempsite.y = siteinfo[blanksite.x][blanksite.y].y;
            blanksite.y = blanksite.y - 1;
            if(tracksteps > 1)
			{
                if(track[tracksteps - 1]== 4)//如果上一步空白块向下移动
				{
                    tracksteps = tracksteps - 2;//跟踪步数减2
                }
            }
		}
		break;
	case DOWN:
		if(blanksite.y<m_iRows)
		{
			tracksteps+=1;
			if(tracksteps>1000)
			{
				//MessageBox("所定义数组空间已用完，你水平太臭了！","俄罗斯方块游戏",MB_OK|MB_ICONINFORMATION);
			}
			track[tracksteps]=4;
			tempsite.x =blanksite.x;
			tempsite.y =blanksite.y+1 ;
			siteinfo[blanksite.x][blanksite.y].x = siteinfo[tempsite.x][tempsite.y].x;
            siteinfo[blanksite.x][blanksite.y].y = siteinfo[tempsite.x][tempsite.y].y;
            tempsite.x = siteinfo[blanksite.x][blanksite.y].x;
            tempsite.y = siteinfo[blanksite.x][blanksite.y].y;
            blanksite.y = blanksite.y + 1;
            if(tracksteps > 1)
			{
                if(track[tracksteps - 1]== 3)//如果上一步空白块向上移动
				{
                    tracksteps = tracksteps - 2;
                }
            }
		}
		break;
	case LEFT:
		if(blanksite.x>1)
		{
			tracksteps+=1;
			if(tracksteps>1000)
			{
				//MessageBox("所定义数组空间已用完，你水平太臭了！","俄罗斯方块游戏",MB_OK|MB_ICONINFORMATION);
			}
			track[tracksteps]=1;
			tempsite.x =blanksite.x-1;
			tempsite.y =blanksite.y ;
			siteinfo[blanksite.x][blanksite.y].x = siteinfo[tempsite.x][tempsite.y].x;
            siteinfo[blanksite.x][blanksite.y].y = siteinfo[tempsite.x][tempsite.y].y;
            tempsite.x = siteinfo[blanksite.x][blanksite.y].x;
            tempsite.y = siteinfo[blanksite.x][blanksite.y].y;
            blanksite.x = blanksite.x - 1;
            if(tracksteps > 1)
			{
                if(track[tracksteps - 1]== 2)//如果上一步空白块向右移动
				{
                    tracksteps = tracksteps - 2;
                }
            }
		}
		break;
	case RIGHT:
		if(blanksite.x<m_iCols)
		{
			tracksteps+=1;
			if(tracksteps>1000)
			{
				//MessageBox("所定义数组空间已用完，你水平太臭了！","俄罗斯方块游戏",MB_OK|MB_ICONINFORMATION);
			}
			track[tracksteps]=2;
			tempsite.x =blanksite.x+1;
			tempsite.y =blanksite.y ;
			siteinfo[blanksite.x][blanksite.y].x = siteinfo[tempsite.x][tempsite.y].x;
            siteinfo[blanksite.x][blanksite.y].y = siteinfo[tempsite.x][tempsite.y].y;
            tempsite.x = siteinfo[blanksite.x][blanksite.y].x;
            tempsite.y = siteinfo[blanksite.x][blanksite.y].y;
            blanksite.x = blanksite.x + 1;
            if(tracksteps > 1)
			{
                if(track[tracksteps - 1]== 1)//如果上一步空白块向左移动
				{
                    tracksteps = tracksteps - 2;
                }
            }
		}
		break;
	default:
		break;
	}
	RequestRedraw();
}

void
Form1::WinOrNot()
{
	//AppLog("WinOrNot");
	int i,j;
	for(i = 1;i<=m_iCols;i++)
	{
		for(j = 1;j<=m_iRows;j++)
		{
			if(i !=blanksite.x || j != blanksite.y)
				if(siteinfo[i][j].x !=i || siteinfo[i][j].y !=j)
					return;
		}
	}
	tracksteps = 0;
	steps = 0;
	start = false;
	win = true;
	__pTimer->Cancel();
	__pRefreshTimeTimer->Cancel();
	return;
}

void Form1::InitialString()
{
	Application* pApp = Application::GetInstance();
	pApp->GetAppResource()->GetString("IDS_STRING1", strTime);
	pApp->GetAppResource()->GetString("IDS_STRING2", strSteps);
	pApp->GetAppResource()->GetString("IDS_STRING3", strPause);
	pApp->GetAppResource()->GetString("IDS_STRING4", strPreview);
	pApp->GetAppResource()->GetString("IDS_STRING5", strNew);
	pApp->GetAppResource()->GetString("IDS_STRING6", strDifficulty);
	pApp->GetAppResource()->GetString("IDS_STRING7", strSelection);
	pApp->GetAppResource()->GetString("IDS_STRING8", strAutoPlay);
	pApp->GetAppResource()->GetString("IDS_STRING9", strHelp);
	pApp->GetAppResource()->GetString("IDS_STRING10", strExit);
	pApp->GetAppResource()->GetString("IDS_STRING11", strJunior);
	pApp->GetAppResource()->GetString("IDS_STRING12", strIntermediate);
	pApp->GetAppResource()->GetString("IDS_STRING13", strSenior);
	pApp->GetAppResource()->GetString("IDS_STRING14", strCustom);
	pApp->GetAppResource()->GetString("IDS_STRING15", strLines);
	pApp->GetAppResource()->GetString("IDS_STRING16", strCols);
	pApp->GetAppResource()->GetString("IDS_STRING17", strOK);
	pApp->GetAppResource()->GetString("IDS_STRING18", strCancel);
	pApp->GetAppResource()->GetString("IDS_STRING19", strComplete);
	pApp->GetAppResource()->GetString("IDS_STRING20", strRestart);
	pApp->GetAppResource()->GetString("IDS_STRING21", strBack);
	pApp->GetAppResource()->GetString("IDS_STRING22", strCongratulations);
	pApp->GetAppResource()->GetString("IDS_STRING23", strStopAutoPlay);
	pApp->GetAppResource()->GetString("IDS_STRING24", strContinue);
	pApp->GetAppResource()->GetString("IDS_STRING25", strAutoPlayCompleted);
	pApp->GetAppResource()->GetString("IDS_STRING26", strAutoPlayCompletedContent);
	//pApp->GetAppResource()->GetString("IDS_STRING27", str5);
	//pApp->GetAppResource()->GetString("IDS_STRING28", str6);
}

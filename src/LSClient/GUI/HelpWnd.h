#pragma once

#include "../io3DEngine/ioButton.h"
#include "../io3DEngine/ioXMLElement.h"

class ioUIRenderImage;
class ioPlayStage;

#define TIME_NUMBER( szTime, nTime ) char szTime[10]; if( nTime < 10 ) sprintf( szTime, "0%d", nTime ); else sprintf( szTime, "%d", nTime );


class MenuBase : public ioButton
{
public:
	enum MenuStyle
	{
		MS_NONE,
		MS_START,
		MS_MIDDLE,
		MS_END,
	};

protected:
	ioUIRenderFrame*	m_pStartNromal;
	ioUIRenderFrame*	m_pStartOver;
	ioUIRenderFrame*	m_pStartOverAdd;
	ioUIRenderFrame*	m_pStartPush;

	ioUIRenderFrame*	m_pMiddleNromal;
	ioUIRenderFrame*	m_pMiddleOver;
	ioUIRenderFrame*	m_pMiddleOverAdd;
	ioUIRenderFrame*	m_pMiddlePush;

	ioUIRenderFrame*	m_pEndNromal;
	ioUIRenderFrame*	m_pEndOver;
	ioUIRenderFrame*	m_pEndOverAdd;
	ioUIRenderFrame*	m_pEndPush;

	MenuStyle			m_eMenuStyle;

public:
	__forceinline void SetMenuStyle( MenuBase::MenuStyle eStyle ){ m_eMenuStyle = eStyle; }

protected:
	virtual void OnDrawNormal( int iXPos, int iYPos );
	virtual void OnDrawOvered( int iXPos, int iYPos );
	virtual void OnDrawOveredAdd( int iXPos, int iYPos );
	virtual void OnDrawPushed( int iXPos, int iYPos );	
	virtual void AddRenderFrame( const ioHashString &szType, ioUIRenderFrame *pFrame );

public:
	MenuBase();
	virtual ~MenuBase();
};

class MenuBtn : public MenuBase
{
public:
	enum ToolTipEffect
	{
		TE_EFFECT_MAX	= 2,
		TE_EFFECT_TIME	= 200,
	};

	enum MenuStyle
	{
		MS_NONE,
		MS_START,
		MS_MIDDLE,
		MS_END,
	};

protected:
	ioUIRenderImage*	m_pTooltipLeft;
	ioUIRenderImage*	m_pTooltipLeftIn;
	ioUIRenderImage*	m_pTooltipCenter;
	ioUIRenderImage*	m_pTooltipRightIn;
	ioUIRenderImage*	m_pTooltipRight;

	ioUIRenderImage*	m_pRedTooltip;
	ioUIRenderImage*	m_pRedTooltipText;
	ioUIRenderImage*	m_pBtnIconStart;
	ioUIRenderImage*	m_pBtnIconEnd;
	ioUIRenderImage*	m_pRedEffect[TE_EFFECT_MAX];

protected:;
	DWORD				m_dwCurrentTime;

protected: // ���� �̺�Ʈ �� ��ǰ
	int					m_iEventItemCnt;

protected: // �� ������ �ð� ��í��
	ioHashString		m_szGashaponInfo;
	ioHashString		m_szGashaponName;

protected: // �� ������ ����
	int					m_iGrowCurrentCount;
	int					m_iGrowMaxCount;

//////////////////////////////////////////////////////////////////////////
// [12/05/2014 KYJ] - �̼� ����Ʈ ���� �� �Լ� �߰�
protected:
	bool				m_bUseSparkle;
	bool				m_bOver;
	DWORD				m_dwOverTimer;
	DWORD				m_dwOverTicTime;
	BYTE				m_byOverFrmPrintCount;

protected:
	DWORD				m_dwStartOutline;
	int					m_iRedEffectIndex;

public:
	void SetStartSparkle();
	void SetEndSparkle();
	const bool& IsSparkling() const { return m_bUseSparkle; }
//////////////////////////////////////////////////////////////////////////

protected:
	virtual void OnProcess( float fTimePerSec );
	virtual void OnRender();
	virtual void AddRenderImage( const ioHashString &szType, ioUIRenderImage *pImage );
	virtual void ParseExtraInfo( ioXMLElement &xElement );

public:
	void OnRenderTooltip();

	void OnRenderTooltipSecretShopOpen( float fXPos, float fYPos, const CTimeSpan& CloseGap );
	void OnRenderTooltipEvent( float fXPos, float fYPos );
	void OnRenderTooltipTimeGashapon( float fXPos, float fYPos );
	void OnRenderTooltipSoliderGrowth( float fXPos, float fYPos );
	void OnRenderTooltipTimePresent( float fXPos, float fYPos );
	void OnRenderTooltipTimeRollBook( float fXPos, float fYPos );

protected:
	void OnRenderTooltipBar( int iXPos, int iYPos, float fTextWidth );

public:
	MenuBtn();
	virtual ~MenuBtn();
};

class MessengerBtn : public ioButton
{
public:
	static bool sg_bMessenger;

protected:
	bool  m_bBackMessenger;
	bool  m_bScreen;
	DWORD m_dwScreenTime;

protected:
	ioUIRenderImage *m_pTooltipLeft;
	ioUIRenderImage *m_pTooltipLeftIn;
	ioUIRenderImage *m_pTooltipCenter;
	ioUIRenderImage *m_pTooltipRightIn;
	ioUIRenderImage *m_pTooltipRight;

protected:
	virtual void OnRender();
	virtual void OnProcess( float fTimePerSec );
	virtual void OnDrawNormal( int iXPos, int iYPos );
	virtual void AddRenderImage( const ioHashString &szType, ioUIRenderImage *pImage );	

protected:
	void OnRenderTooltip( int iXPos, int iYPos, float fTextWidth );

public:
	MessengerBtn();
	virtual ~MessengerBtn();
};

class PlazaStateBtn : public MenuBase
{
protected:
	ioUIRenderImage *m_pNormalCommunity;
	ioUIRenderImage *m_pDisableCommunity;
	ioUIRenderImage *m_pNormalPractice;
	ioUIRenderImage *m_pDisablePractice;

protected:
	ioPlayStage *m_pPlayStage;

protected:
	virtual void AddRenderImage( const ioHashString &szType, ioUIRenderImage *pImage );	

protected:

	virtual void OnRender();

public:
	void SetPlayStage( ioPlayStage *pPlayStage );

public:
	PlazaStateBtn();
	virtual ~PlazaStateBtn();
};

class HelpWnd : public ioWnd
{
public:
	enum
	{
		// 1
		ID_GAME_CLOSE = 1,
		ID_BACK_STAGE = 2,

		// 2
		ID_ROOM_INFO = 3,
		ID_HOUSING_SETUP = 4,
		ID_DISPLAY = 5,
		ID_PRACTICE = 6,
		ID_FISHING = 7,
		ID_EXCAVATION = 8,
		ID_PLAZA_STATE = 9,
		ID_OAK_BAREL = 10,


		// 3
		ID_SHOP = 11,
		ID_MYITEM = 12,
		ID_PRESENT = 13,

		ID_MISSION_QUEST = 14,
		ID_PET = 15,

		// 4
		ID_ROLLBOOK = 19,
		ID_MINI_HOME = 20,
		ID_MANUAL = 21,
		ID_OPTION = 22,

		//5
		ID_MESSENGER = 30,

		
		ID_GAME_CLOSE2 = 40,
	};

	enum 
	{
		MOVE_STATE_SHOW,
		MOVE_STATE_HIDE,
	};

protected:
	static DWORD sg_dwMoveState;
	static float sg_fMessengerXPos;
	static float sg_fMessengerYPos;
	static float sg_fQuestXPos;
	static float sg_fQuestYPos;

protected:
	ioUIRenderImage *m_pBarLeftMultiply;
	ioUIRenderImage *m_pBarCenterMultiply;
	ioUIRenderImage *m_pBarRightMultiply;
	ioUIRenderImage *m_pBarLeft;
	ioUIRenderImage *m_pBarCenter;
	ioUIRenderImage *m_pBarRight;
	ioUIRenderImage *m_pHideBar;
	ioUIRenderImage *m_pHideIcon;
    
protected:
	ioPlayStage *m_pPlayStage;
	ModeType     m_ePrevModeType;
	PlazaType    m_ePrevPlazaType;
	bool         m_bTutorial;

protected:
	
	// �⽺�� ������...
	enum
	{
		POS_X_GAP = 14,
		POS_Y_GAP = 42,
		POS_W_GAP = 28,
		POS_H_GAP = 42,
	
		MAX_ANI_YPOS   = 36,
		ANI_FRAME_TIME = 100,
	};	

protected:	
	DWORD m_dwShowKeepTime;
	DWORD m_dwMoveStateStartDelayTIme;
	DWORD m_dwMoveStateDelayTIme;
	DWORD m_dwMoveStateTime;
	float m_fMoveWndYPos;
	
public:
	void SetPlayStage( ioPlayStage *pPlayStage );

public:
	virtual void iwm_show();
	virtual void iwm_gototop();
	virtual void iwm_command( ioWnd *pWnd, int cmd, DWORD param );
	virtual void SetPositionToDefault( int iParentWidth, int iParentHeight, bool bChildMove, bool bCreate = false );

protected:
	virtual void OnProcess( float fTimePerSec );
	virtual void OnRender();
	virtual void OnRenderAfterChild();

protected:
	void OnProcessMove();
	void OnRenderBar( int iXPos, int iYPos, int iWidth );

public:
	void ReCreateWindow();
	void ReCreateBtn();

protected:
	void DisplayProcess();
	void PracticeProcess();
	void FishingProcess();
	void ExcavationeProcess();
	void HousingSetUpProcess();
	void PlazaStateProcess();
	void PresentProcess();
	void ShopProcess();
	void MyItemProcess();
	void QuestProcess();
	void PetProcess();
	void RollBookProcess();
	void ManualProcess();
	void OptionProcess();
	void MessengerProcess();

public:
	void EscKeyProcess();

public:
	static DWORD GetMoveState(){ return sg_dwMoveState; }
	static bool IsMoveStateShow(){ return ( sg_dwMoveState == MOVE_STATE_SHOW ); }
	static float GetMessengerXPos(){ return sg_fMessengerXPos; }
	static float GetMessengerYPos(){ return sg_fMessengerYPos; }
	static float GetQuestXPos(){ return sg_fQuestXPos; }
	static float GetQuestYPos(){ return sg_fQuestYPos; }

public:
	bool IsPractice();
	bool IsFishing();
	bool IsExcavation();
	bool IsNormale();
	bool IsHousing();

public:
	virtual void AddRenderImage( const ioHashString &szType, ioUIRenderImage *pImage );	

public:
	bool QuestGuide( int iBtnID, float &rfXPos, float &rfYPos );

public:
	HelpWnd();
	virtual ~HelpWnd();
};

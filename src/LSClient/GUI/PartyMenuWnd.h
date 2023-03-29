#pragma once

#include "GlobalWnd.h"

class ioUIRenderImage;
class ioUIRenderFrame;
class SP2Packet;
class NormalModeBtn;

class ioWndStaticPos : public ioMovingWnd
{
protected:
	static int  sg_iStartX;
	static int  sg_iStartY;
	static int  sg_iScreenOutX;
	static int  sg_iScreenOutY;

public:
	virtual void iwm_show();

protected:
	virtual void OnProcess( float fTimePerSec );

public:
	ioWndStaticPos();
	virtual ~ioWndStaticPos();
};

//////////////////////////////////////////////////////////////////////////
class PartyInfoBtn : public ioButton
{
protected:
	ioUIRenderImage *m_pBlueNormal;
	ioUIRenderImage *m_pRedNormal;
	ioUIRenderImage *m_pNoneNormal;
	ioUIRenderImage *m_pBlueOver;
	ioUIRenderImage *m_pRedOver;
	ioUIRenderImage *m_pNoneOver;
	ioUIRenderImage *m_pPeopleOrange;
	ioUIRenderImage *m_pPeopleGray;

protected:
	TeamType m_eTeam;
	ioHashString m_szName;
	int m_iGradeLevel;
	int m_iSlotArray;
	int m_iMaxSlot;
	int m_iPingStep;

protected:
	PingStepWnd m_PingStep;

public:
	virtual void iwm_create();

public:
	void SetMemberInfo( int iMaxSlot, int iSlotArray, const ioHashString &rkName, int iGradeLevel, int iPingStep, TeamType eTeam );
	const ioHashString &GetMemberName(){ return m_szName; }

protected:
	virtual void AddRenderImage( const ioHashString &szType, ioUIRenderImage *pImage );	
	virtual void OnRender();
	virtual void OnProcess( float fTimePerSec );
	void OnRenderBase( int iXPos, int iYPos );
	void OnRenderPing( int iXPos, int iYPos );

public:
	PartyInfoBtn();
	virtual ~PartyInfoBtn();
};
//////////////////////////////////////////////////////////////////////////
class PartyInfoWnd : public ioMovingWnd
{
public:
	enum 
	{
		ID_EXIT				= 1,
		ID_ENTER_PARTY		= 2,
		ID_ENTER_OBSERVER	= 3,
		ID_CANCEL           = 4,
		ID_MANUAL_BTN       = 5,

		ID_BLUE_TEAM_1 = 10,
		ID_BLUE_TEAM_2 = 11,
		ID_BLUE_TEAM_3 = 12,
		ID_BLUE_TEAM_4 = 13,
		ID_BLUE_TEAM_5 = 14,
		ID_BLUE_TEAM_6 = 15,
		ID_BLUE_TEAM_7 = 16,
		ID_BLUE_TEAM_8 = 17,

		ID_RED_TEAM_1  = 20,
		ID_RED_TEAM_2  = 21,
		ID_RED_TEAM_3  = 22,
		ID_RED_TEAM_4  = 23,
		ID_RED_TEAM_5  = 24,
		ID_RED_TEAM_6  = 25,
		ID_RED_TEAM_7  = 26,
		ID_RED_TEAM_8  = 27,

		ID_MODE_HELP_TOOLTIP = 500,

		ID_DEVELOPER_ENTER = 1000,
	};	

	enum
	{
		MAX_TEAM_LIST = 8,

		NORMAL_MODE_HEIGHT = 348,
		USER_MODE_HEIGHT   = 488,
		BOTTOM_BAR_GAP     = 65,
		BOTTOM_BTN_GAP     = 48,
	};

	enum
	{ 
		BST_START   = 0, 
		BST_PLAYING = 1, 
		BST_RESULT  = 2, 
	};

	enum
	{
		// ���� ��� �ɼ� �ε���
		UMO_GROWTH_USE = 0,
		UMO_CHANGE_CHAR,
		UMO_KO,
		UMO_DROP_DAMAGE,
		UMO_TEAM_ATTACK,
		UMO_ROUND_TYPE,
		UMO_EXTRAITEM_USE,
		UMO_COOL_TIME,
		UMO_KO_EFFECT,
		UMO_GET_UP_DELAY,
		UMO_GRAVITY,
		UMO_ROUND_TIME,

		// ���� ��� �� �ɼ�
		UMO_BLUE_HP,
		UMO_BLUE_MOVE_SPD,
		UMO_BLUE_EQUIP,
		UMO_BLUE_BLOW,
		UMO_RED_HP,
		UMO_RED_MOVE_SPD,
		UMO_RED_EQUIP,
		UMO_RED_BLOW,
	};

protected:
	ioUIRenderFrame *m_pBottomFrm;
	ioUIRenderImage *m_pModeIconBack;
	ioUIRenderImage *m_pUserModeLine;
	ioUIRenderImage *m_pUserModeBoxDark;
	ioUIRenderImage *m_pUserModeBoxLight;

protected:
	BattleRoomInfo m_BattleRoomInfo;
	typedef std::vector< BattleRoomUserInfo > vUserInfo;
	vUserInfo	  m_vUserList;

	DWORD         m_dwIndexBackup;
	bool          m_bStateBackup;
	int           m_iStateBackup;

protected:
	ioWnd        *m_pModeHelpTooltip;
	bool          m_bIconOver;
	bool          m_bPenaltyPeso;
private:
#ifdef SRC_TH
	bool CheckRoomRestriction();
#endif
	DWORD		  m_dwPassRoomNum;
public:
	virtual void iwm_create();

public:
	void SetInfo( SP2Packet &rkPacket );
	void SetLadderRoomInfo( SP2Packet &rkPacket );
	void SetPassRoomNum( DWORD dwRoomNum ) { m_dwPassRoomNum = dwRoomNum; }
	void SetBackupData( DWORD dwIndex, bool bPassword, int iState );
	void UpdataBattleRoomState( DWORD dwIndex, int iState );

public:
	int GetModeSelectIndex(){ return m_BattleRoomInfo.m_iModeSelectIndex; }

protected:
	void JoinBattleRoom( bool bObserver );
	void JoinLadderRoom( bool bObserver );

protected:
	const BattleRoomUserInfo &GetUserInfo( TeamType eTeam, int iArray );
	void UpdateUserList();

protected:
	ioHashString GetUserModeDesc( int iType );
	bool IsDefatulUserModeType( int iType );

public:
	virtual void AddRenderFrame( const ioHashString &szType, ioUIRenderFrame *pFrame );
	virtual void AddRenderImage( const ioHashString &szType, ioUIRenderImage *pImage );	

public:
	virtual void iwm_show();
	virtual void iwm_hide();
	virtual bool iwm_esc();
	virtual void iwm_command( ioWnd *pWnd, int cmd, DWORD param );
	virtual void SetPositionToDefault( int iParentWidth, int iParentHeight, bool bChildMove, bool bCreate = false );

protected:	
	void ProcessModeHelpTooltip();
	virtual void OnProcess( float fTimePerSec );
	virtual void OnRender();
	void OnRenderUserMode( int iXPos, int iYPos );

public:
	PartyInfoWnd();
	virtual ~PartyInfoWnd();
};
//////////////////////////////////////////////////////////////////////////
class PartyPasswordWnd : public ioWnd
{
public:
	enum
	{
		ID_EXIT    = 1,
		ID_OK      = 2,
		ID_CANCEL  = 3,

		ID_PASS_EDIT = 100,
	};

protected:
	ioWnd *m_pPreEdit;

	DWORD		 m_dwIndex;
	int			 m_iLevel;
	ioHashString m_szName;
	int          m_iCurJoiner;
	int          m_iCurPlayer;
	int          m_iMaxPlayerBlue;
	int          m_iMaxPlayerRed;
	bool         m_bPenaltyPeso;

	bool m_bObserver;

	void JoinBattleRoom();

public:
	void SetBattleRoomInfo( DWORD dwIndex, int iLevel, ioHashString szName, int iCurJoiner, int iCurPlayer, int iMaxPlayerBlue, int iMaxPlayerRed, bool bObserver );

public:
	virtual void iwm_show();
	virtual void iwm_hide();
	virtual void iwm_command( ioWnd *pWnd, int cmd, DWORD param );

protected:
	virtual void OnRender();	

public:
	PartyPasswordWnd();
	virtual ~PartyPasswordWnd();
};
//////////////////////////////////////////////////////////////////////////
class PartyCreateWnd : public ioWnd
{
public:
	enum
	{
		ID_EXIT   = 1,
		ID_CREATE = 2,
		ID_CANCEL = 3,
		ID_CHANGE_MODE = 4,

		ID_EDIT_NAME = 100,	
		ID_EDIT_PW   = 101,

		ID_MODE_LIST = 300,
	};

protected:
	ioWnd *m_pPreEdit;
	ioWnd *m_pNameEdit;
	ioWnd *m_pPWEdit;

	int    m_iSelectTerm;
	int    m_iMaxPlayerBlue;
	int    m_iMaxPlayerRed;
	int	   m_iMaxObserver;

public:
	void CreateBattleRoom( int iSelectTerm, int iBlueCount, int iRedCount );
	void SetMaxPlayer( int iBlueCount, int iRedCount, int iObserverCount );

public:
	virtual void iwm_command( ioWnd *pWnd, int cmd, DWORD param );
	virtual void iwm_show();	
	virtual void iwm_hide();

protected:
	virtual void OnRender();

public:
	bool QuestGuide( int iModeIndex, float &rfXPos, float &rfYPos );

public:
	PartyCreateWnd();
	virtual ~PartyCreateWnd();
};

class PartyCatalogueBtn : public ioButton
{
protected:
	ioUIRenderImage *m_pIconBack;
	ioUIRenderImage *m_pRoomNumBack;
	ioUIRenderImage *m_pBossModeIcon;
	ioUIRenderImage *m_pLockKey;
	ioUIRenderImage *m_pLockKeyGray;
	ioUIRenderImage *m_pIconEmpty;

	BattleRoomInfo m_BattleRoomInfo;
	ioHashString   m_szState;
	bool           m_bIconOver;
	
public:
	void SetBattleRoomInfo( BattleRoomInfo &rkInfo );

public:
	DWORD GetBattleRoomIndex(){ return m_BattleRoomInfo.m_dwIndex; }
	int   GetBattleRoomState(){ return m_BattleRoomInfo.m_iState; }
	int   GetBattleRoomSelectIndex(){ return m_BattleRoomInfo.m_iModeSelectIndex; }
	bool  IsPassword(){ return m_BattleRoomInfo.m_bPassword; }
	bool  isIconOver(){ return m_bIconOver; } 

protected:
	virtual void OnProcess( float fTimePerSec );
	virtual void OnRender();
	virtual void AddRenderImage( const ioHashString &szType, ioUIRenderImage *pImage );	

public:
	PartyCatalogueBtn();
	virtual ~PartyCatalogueBtn();
};

class PartyQuickJoinBtn : public ioButton
{
protected:
	ioUIRenderImage *m_pIconBack;
	ioUIRenderImage *m_pIconEmpty;
	ioUIRenderImage *m_pSetting;

public:
	virtual void AddRenderImage( const ioHashString &szType, ioUIRenderImage *pImage );	

protected:
	virtual void OnRender();

public:
	PartyQuickJoinBtn();
	virtual ~PartyQuickJoinBtn();
};

class PartyCatalogueWnd : public ioWnd
{
public:
	enum
	{
		ID_PARTY_CREATE		= 1,
		ID_SELECT_MODE		= 2,
		ID_QUICK_JOIN		= 3,
		ID_PAGE_LEFT		= 4,
		ID_PAGE_RIGHT		= 5,
		ID_REFRESH			= 6,
		ID_SHUFFLE_JOIN		= 7,

		//���� ���ӹ��� ����
		ID_PARTY_CREATE2	= 8,
		ID_SELECT_MODE2		= 9,
		ID_QUICK_JOIN2		= 10,

		//�뼭Ī ����
		ID_ROOM_SEARCH		= 11,
		
		ID_LIST_1	= 100,
		ID_LIST_2	= 101,
		ID_LIST_3	= 102,
		ID_LIST_4	= 103,
		ID_LIST_5	= 104,
		ID_LIST_6	= 105,
		ID_LIST_7	= 106,
		ID_LIST_8	= 107,
	};

	enum
	{
		LOBBY_MAX_PARTY_LIST = 6,
		PLAZA_MAX_PARTY_LIST = 8,
		PARTY_SEARCH_TIME	 = 10000,
	};

protected:
	DWORD	   m_dwMaxPartyList;
	DWORD      m_dwSearchTime;
	int        m_iCurPage;
	int        m_iMaxPage;
	int        m_iPageYPos;
	
	typedef std::vector< BattleRoomInfo* > vBattleRoomInfo;
	vBattleRoomInfo m_vBattleRoomList;

public:
	virtual void iwm_show();
	virtual void iwm_hide();
	virtual void iwm_command( ioWnd *pWnd, int cmd, DWORD param );
	virtual void iwm_create();

protected:
	void UpdateSetPage( int iCurPage );
	void ProcessSearch();

public:
	void PlazaUIMove();
	inline void SetMaxPartyList( DWORD dwMax ){ m_dwMaxPartyList = dwMax; }

public:
	void SetPartyList( SP2Packet &rkPacket );
	void SetLadderList( SP2Packet &rkPacket );
	void StartSend( bool bProcess = false );
	bool IsIndexToList( DWORD dwIndex );

protected:
	void ProcessModeHelpTooltip();
	virtual void OnProcess( float fTimePerSec );
	virtual void OnRender();

public:
	bool QuestGuide( int iModeSelectIndex, float &rfXPos, float &rfYPos );

public:
	PartyCatalogueWnd();
	virtual ~PartyCatalogueWnd();
};
//////////////////////////////////////////////////////////////////////////
class PartyInvitedBtn : public ioButton
{
protected:
	ioUIRenderImage *m_pBlueNormal;
	ioUIRenderImage *m_pRedNormal;
	ioUIRenderImage *m_pNoneNormal;
	ioUIRenderImage *m_pBlueOver;
	ioUIRenderImage *m_pRedOver;
	ioUIRenderImage *m_pNoneOver;
	ioUIRenderImage *m_pPeopleOrange;
	ioUIRenderImage *m_pPeopleGray;

protected:
	TeamType m_eTeam;
	ioHashString m_szName;
	int m_iGradeLevel;
	int m_iPingStep;
	int m_iSlotArray;
	int m_iMaxSlot;

protected:
	PingStepWnd m_PingStep;

public:
	virtual void iwm_create();

public:
	void SetMemberInfo( int iMaxSlot, int iSlotArray, const ioHashString &rkName, int iGradeLevel, int iPingStep, TeamType eTeam );
	const ioHashString &GetMemberName(){ return m_szName; }

protected:
	virtual void AddRenderImage( const ioHashString &szType, ioUIRenderImage *pImage );	
	virtual void OnRender();
	virtual void OnProcess( float fTimePerSec );
	void OnRenderBase( int iXPos, int iYPos );

public:
	PartyInvitedBtn();
	virtual ~PartyInvitedBtn();
};
//////////////////////////////////////////////////////////////////////////
class PartyInvitedWnd : public ioMovingWnd
{
public:
	enum 
	{
		ID_EXIT		   = 1,
		ID_AGREE	   = 2,
		ID_REFUSE	   = 3,
		ID_AUTO_REFUSE = 4,
		ID_LEFT_PAGE   = 5,
		ID_RIGHT_PAGE  = 6,
		ID_MANUAL_BTN  = 7,

		ID_BLUE_TEAM_1 = 10,
		ID_BLUE_TEAM_2 = 11,
		ID_BLUE_TEAM_3 = 12,
		ID_BLUE_TEAM_4 = 13,

		ID_RED_TEAM_1  = 20,
		ID_RED_TEAM_2  = 21,
		ID_RED_TEAM_3  = 22,
		ID_RED_TEAM_4  = 23,

		ID_MODE_HELP_TOOLTIP = 500,
	};

	enum
	{
		INVITE_DELAY_SEC = 20,
		MAX_PAGE_LIST    = 4,
	};

	enum
	{ 
		BST_START   = 0, 
		BST_PLAYING = 1, 
		BST_RESULT  = 2, 
	};

protected:
	static bool sg_bAutoRefuse;

protected:
	ioUIRenderImage *m_pModeIconBack;

protected:
	BattleRoomInfo m_BattleRoomInfo;
	typedef std::vector< BattleRoomUserInfo > vUserInfo;
	vUserInfo	  m_vUserList;

	int			  m_iCurPage;	
	int           m_iMaxPage;
	DWORD         m_dwStartTime;
	ioPlayStage  *m_pPlayStage;

protected:
	ioWnd        *m_pModeHelpTooltip;
	bool          m_bIconOver;

public:
	void SetInfo( SP2Packet &rkPacket, ioPlayStage *pPlayStage );

protected:
	void UpdatePage( int iCurPage );
	const BattleRoomUserInfo &GetUserInfo( TeamType eTeam, int iArray );

protected:
	void JoinBattleRoom();
	void SetRefuse();

public:
	virtual void iwm_command( ioWnd *pWnd, int cmd, DWORD param );
	virtual void iwm_show();	
	virtual void iwm_hide();
	virtual bool iwm_esc();

protected:
	void ProcessModeHelpTooltip();	
	virtual void AddRenderImage( const ioHashString &szType, ioUIRenderImage *pImage );
	virtual void OnProcess( float fTimePerSec );
	virtual void OnRender();

public:
	PartyInvitedWnd();
	virtual ~PartyInvitedWnd();
};
//////////////////////////////////////////////////////////////////////////
class BattleQuickStartPlayerOption : public ioWnd
{
public:
	enum
	{
		ID_MINIMUM = 1,
		ID_MAXIMUM = 2,
	};

	enum
	{ 
		MAX_TICK = 16, 
		TICK_GAP = 10, 
	};

protected:
	ioUIRenderImage *m_pOrangeStrip;
	ioUIRenderImage *m_pTickLine;

protected:
	ioWnd *m_pMinimumBtn;
	ioWnd *m_pMaximumBtn;

protected:
	int m_iMinPlayer;
	int m_iMaxPlayer;

protected:
	void MoveMinBtn( bool bBtnUp );
	void MoveMaxBtn( bool bBtnUp );
	void SetBtnTitle( int iMinPlayer, int iMaxPlayer, bool bRePos );

public:
	virtual void iwm_command( ioWnd *pWnd, int cmd, DWORD param );
	virtual void iwm_show();

protected:
	virtual void AddRenderImage( const ioHashString &szType, ioUIRenderImage *pImage );	

protected:
	virtual void OnProcess( float fTimePerSec );
	virtual void OnRender();

public:
	void SetPlayerOption( int iLimitMaxPlayer, int iMinPlayer, int iMaxPlayer );

public:
	int GetMinPlayer(){ return m_iMinPlayer; }
	int GetMaxPlayer(){ return m_iMaxPlayer; }


public:
	BattleQuickStartPlayerOption();
	virtual ~BattleQuickStartPlayerOption();
};

class BattleQuickStartOption : public ioWnd
{
public:
	enum
	{
		ID_EXIT = 1,
		ID_JOIN = 2,
		ID_COMPLETE = 3,
		ID_SAME_PLAYER_CHECK = 4,
		ID_PLAYER_OPTION = 5,
		ID_MODE_HELP = 6,

		NUM_MODE = 20,


		ID_FAVORITE_MODE_START = 101,
		ID_NONE_FAVORITE_MODE = ID_FAVORITE_MODE_START,
//		ID_EMPTY_START = 118,
		ID_FAVORITE_MODE_END = 124,

		ID_MODE_HELP_TOOLTIP = 500,
	};


	enum
	{ 
		DEFAULT_LIST_X = 196, 
		DEFAULT_LIST_Y = 214,

		CHECK_BOX_W    = 16,
		CHECK_BOX_H    = 16,

		LIST_YPOS_GAP  = 9,
		LINE_YPOS_GAP  = 18,
	};

	enum KINDWND
	{
		E_FAVORITE		= 0,
		E_CREATEBATTLE,
		E_LADDERBATTLE,
	};


protected:
	ioUIRenderFrame *m_pGreenState;
	ioUIRenderImage *m_pModeIconBack;
	ioUIRenderImage *m_pCheckOn;
	ioUIRenderImage *m_pCheckOff;
	ioUIRenderImage *m_pDot;

protected:
	struct ModeData
	{
		int m_iIndex;
		int m_iHelp;
		ioHashString m_szTitle;
		ioHashString szImage;
		ioUIRenderImage *m_pMarkRes;
		int  m_iLimitMaxUser;
		int  m_iDefMinUser;
		int  m_iDefMaxUser;
		bool m_bUseSameUser;
		ModeData()
		{
			m_iIndex = m_iHelp = 0;
			m_iLimitMaxUser = m_iDefMinUser = m_iDefMaxUser = 0;
			m_pMarkRes = NULL;
			m_bUseSameUser = false;;
		}
	};
	typedef std::vector< ModeData > vModeData;
	vModeData m_ModeList;
	QuickStartInfo m_QuickStartInfo;

protected:
	ioWnd	*m_pOpenWnd;
	ioWnd   *m_pModeHelpTooltip;

protected: 
	int  m_iOverIndex;
	int  m_iPushIndex;

protected:
	int	m_nAddMode;

protected:
	KINDWND m_eKind;

protected:
	const ModeData &GetModeData( int iModeIndex );

public:
	virtual void iwm_command( ioWnd *pWnd, int cmd, DWORD param );
	virtual void iwm_show();
	virtual void iwm_hide();
	virtual bool iwm_spacebar();

protected:
	virtual void AddRenderFrame( const ioHashString &szType, ioUIRenderFrame *pFrame );
	virtual void AddRenderImage( const ioHashString &szType, ioUIRenderImage *pImage );	

protected:
	void ProcessRadioCheck();
	virtual void OnProcess( float fTimePerSec );
	virtual void OnRender();


protected:
	void SetCurrentSameUser( bool bSameUser );
	void SetCurrentMaxPlayer( int iMaxPlayer );
	void SetCurrentMinPlayer( int iMinPlayer );
	
	bool GetUseSameUser( int iModeIndex );

	bool GetSameUser( int iModeIndex );
	int  GetMaxPlayer( int iModeIndex );
	int  GetMinPlayer(  int iModeIndex );
public:
	int  GetLimitMaxUser( int iModeIndex );

protected:
	void OnRenderModeList( int iXPos, int iYPos );
	void OnRenderModeHelp( int iXPos, int iYPos );

protected:
	void SetExtendOption();
	void SetExtendOptionDefault();

protected:
	int GetCheckedMode();

	void SetTitleAndSizeWnd( KINDWND eKind );
	void SetModeBtn();
	void SetCheckModeBtn();
	void ProcessModeHelpTooltip(NormalModeBtn* pBtn, bool bOver);

	void FavoriteCommand( ioWnd *pWnd, int cmd, DWORD param );
	void CreateBattleCommand( ioWnd *pWnd, int cmd, DWORD param );

public:
	void SetQuickStart( ioWnd *pOpenWnd, KINDWND eKind = E_FAVORITE );
	void AddList( int iIndex, const ioHashString &szTitle, int iHelp, int iLimitMaxUser, 
				int iDefMinUser, int iDefMaxUser, bool bUseSameUser, ioUIRenderImage *pMarkRes );
	KINDWND GetKindWnd() { return m_eKind; }

public:
	bool QuestGuide( int iModeIndex, float &rfXPos, float &rfYPos );

public:
	BattleQuickStartOption();
	virtual ~BattleQuickStartOption();
};
//////////////////////////////////////////////////////////////////////////
class LobbyBattleInfoWnd : public ioWnd
{
	// �κ��� ���� �ǿ��� ǥ���� ���� UI
public:
	enum
	{
		ID_MY_INFO_BTN = 1,
		ID_MISSION_BTN = 2,
		ID_QUEST_BTN   = 3,
		ID_NOVICE_GRADE_BTN			= 4,
		ID_NOVICE_GRADE_TOOTIP_BTN  = 5,
		ID_NOVICE_GRADE_TOOTIP		= 6,
#ifdef LS_TIMEGATE_BY_PRINCE
		ID_TIMEGATE_BTN = 7,
#endif

		ID_MISSION_LIST_WND = 9,
		ID_QUEST_ALARM_WND     = 10,

		//-------------------------------------------------------------
		// ��¥ : 
		// ���� ����Ʈ �߰� �� ����Ʈ �������� 
		// �κ񿡼� User�������� ���� �������� �ʴ´�.
		//-------------------------------------------------------------
		//ID_LOBBY_USER_LIST_WND = 11,
	};
protected:
	DWORD m_dwTabID;
	bool m_bIsNoviceGrade;

protected:
	void		 UpdateRadioBtn();

public:
	virtual void iwm_create();
	virtual void iwm_show();
	virtual void iwm_hide();
	virtual void iwm_command( ioWnd *pWnd, int cmd, DWORD param );

protected:
	virtual void OnProcess( float fTimePerSec );
	virtual void OnRender();

public:
	void		 ApplyLobbyUserList( SP2Packet &rkPacket );

protected:
	void		 ChangeTab( DWORD dwTabID );

protected:
	void SetNamedTitleSparkle();

public:
	LobbyBattleInfoWnd();
	virtual ~LobbyBattleInfoWnd();
};



//////////////////////////////////////////////////////////////////////////
// Normal mode btn for Favorite Mode Window 
//////////////////////////////////////////////////////////////////////////
class NormalModeBtn : public ioButton
{
public:
	enum 
	{
		BTN_NORMAL_TYPE = 0,
		BTN_PVE_TYPE = 1,
		TWINKLE_TIME = 250,
	};

protected:
	int m_nType;
	int m_nModeStyle;
	int m_nSubModeStyle;

	POINT m_ptCheck;

	bool m_bCheck;
	bool m_bTwinkle;

	float m_fWinkTime;

	ioUIRenderImage *m_pCheckOn;
	ioUIRenderImage *m_pNewHot;

public:
	int GetBtnType() {return m_nType;}
	int GetModeStyle() {return m_nModeStyle;}
	int GetSubModeStyle() {return m_nSubModeStyle;}

	void SetCheck(bool bCheck);
	void SetSubModeStyle(int nSubStyle) {m_nSubModeStyle = nSubStyle;}
	void SetNewHotMark(ioUIRenderImage* pImg) {m_pNewHot = pImg;}

public:
	virtual void AddRenderImage( const ioHashString &szType, ioUIRenderImage *pImage );	
	virtual void ParseExtraInfo( ioXMLElement &xElement );

	virtual bool GetCheck() {return m_bCheck;}

	virtual void ResetCheck(DWORD dwID);
	virtual void ResetCheck(){m_bCheck = false;}

	virtual void ShowAllChildWnd(){};
	virtual void HideAllChildWnd(){};

protected:
	virtual void OnRender();
	virtual void OnDrawDisabled( int iXPos, int iYPos );
	virtual void OnDrawOveredAdd( int iXPos, int iYPos );
	virtual void OnProcess( float fTimePerSec );
	virtual void iwm_mouseover( const ioMouse& mouse );
	virtual void iwm_mouseleave( const ioMouse& mouse );

public:
	NormalModeBtn();
	virtual ~NormalModeBtn();
};


//////////////////////////////////////////////////////////////////////////
// PVE mode btn for Favorite Mode Window 
//////////////////////////////////////////////////////////////////////////
class PVEModeBtn : public NormalModeBtn
{
public:
	enum
	{
		SUB_BTN_START = 1,
		SUB_BTN = SUB_BTN_START,
		SUB_BTN_END = 5,
	};

public:
	virtual bool GetCheck();

	virtual void ResetCheck(DWORD dwID);
	virtual void ResetCheck();
	virtual void ShowAllChildWnd();
	virtual void HideAllChildWnd();


protected:
	virtual void OnRender();
	virtual void iwm_command( ioWnd *pWnd, int cmd, DWORD param );
	virtual void iwm_mouseover( const ioMouse& mouse );
	virtual void iwm_mouseleave( const ioMouse& mouse );

public:
	PVEModeBtn();
	virtual ~PVEModeBtn();
};

//room search wnd : �±� ��û
class RoomSearchWnd : public ioWnd
{
public:
	enum { ID_EXIT = 1, ID_SEARCH, ID_CANCEL, ID_EDIT, ID_MAX,
			ID_TEXT = 100	
	};

protected:
	void RoomSearch();
	void SetFindReset();
public:
	virtual void iwm_command( ioWnd *pWnd, int cmd, DWORD param );
	virtual void iwm_show();	
	virtual void iwm_hide();
	virtual bool iwm_esc();
protected:
	virtual void OnProcess( float fTimePerSec );
	virtual void OnRender();

public:
	RoomSearchWnd();
	virtual ~RoomSearchWnd();
private:
	ioHashString m_szFindKeyWord;
};

#ifdef LS_TIMEGATE_BY_PRINCE
class TimeGateBtn : public ioButton
{
public:
	enum
	{
		ST_Wait,
		ST_Wait_Close,
		ST_Active,
	};

private:
	ioUIRenderImage* m_tgBG;
	ioUIRenderImage* m_tgTxt;
	ioUIRenderImage* m_tgTxtBG;
	ioUIRenderImage* m_tgEffect[7];
	ioUIRenderFrame* m_tgSelected;

	ioHashString m_sztgTxt[3];
	ioHashString m_sztgtxtRender;

	int m_tgEffectIndex;
	DWORD m_tgEffecTimes;
	int m_tgEffectTimesANI;

	int m_tgState;

protected:
	virtual void iwm_create();
	virtual void OnRender();
	virtual void OnProcess(float fTimePerSec);


public:
	virtual void AddRenderFrame(const ioHashString& szType, ioUIRenderFrame* pFrame);
	virtual void AddRenderImage(const ioHashString& szType, ioUIRenderImage* pImage);
	virtual void ParseExtraInfo(ioXMLElement& xElement);


public:
	TimeGateBtn();
	virtual ~TimeGateBtn();
};

#endif
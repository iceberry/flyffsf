#ifndef __FUNCTIONSINFO_H__
#define __FUNCTIONSINFO_H__

struct NPCDIALOG_INFO;

typedef int (WINAPI *PFSayName)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFSpeak)( NPCDIALOG_INFO* pInfo, int nId, LPCTSTR lpszStr );
typedef int (WINAPI *PFSpeakName)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFGetVal)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFGetSrcId)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFGetDstId)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFNpcId)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFPcId)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFGetGValue_)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFSetGValue)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFAddGValue)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFAddKey)( NPCDIALOG_INFO* pInfo, LPCTSTR szWord, LPCTSTR szKey, DWORD dwParam );
typedef int (WINAPI *PFAddCondKey)( NPCDIALOG_INFO* pInfo, LPCTSTR szWord, LPCTSTR szKey, DWORD dwParam );
typedef int (WINAPI *PFAddAnswer)( NPCDIALOG_INFO*  pInfo, LPCTSTR szWord, LPCTSTR szKey, DWORD dwParam );
typedef int (WINAPI *PFRemoveQuest)( NPCDIALOG_INFO* pInfo, int nQuest );      
typedef int (WINAPI *PFRemoveAllKey)( NPCDIALOG_INFO*  pInfo);
typedef int (WINAPI *PFSayQuest)( NPCDIALOG_INFO* pInfo, int nQuest, int nDialog );
typedef int (WINAPI *PFBeginQuest)( NPCDIALOG_INFO* pInfo, int nQuest );
typedef int (WINAPI *PFEndQuest)( NPCDIALOG_INFO* pInfo, int nQuest );
typedef int (WINAPI *PFAddQuestKey)( NPCDIALOG_INFO* pInfo, int nQuest, LPCTSTR szKey );
typedef int (WINAPI *PFCreateMover)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFCreateChar)( NPCDIALOG_INFO*  pInfo );
typedef int (WINAPI *PFRemoveMover)( NPCDIALOG_INFO*  pInfo );
typedef int (WINAPI *PFGetDay)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFGetMin)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFGetHour)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFSetTimer)( NPCDIALOG_INFO*  pInfo );  
typedef int (WINAPI *PFIsTimeOut)( NPCDIALOG_INFO*  pInfo );
typedef int (WINAPI *PFLaunchQuest)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFGetEmptyInventoryNum)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFGetQuestState)( NPCDIALOG_INFO* pInfo, int nQuest );
typedef int (WINAPI *PFIsSetQuest)( NPCDIALOG_INFO* pInfo, int nQuest );
typedef int (WINAPI *PFSetMark)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFGoMark)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFRandomIndex)( NPCDIALOG_INFO* pInfo);
typedef int (WINAPI *PFRemoveKey)( NPCDIALOG_INFO* pInfo, LPCTSTR szKey );
typedef int (WINAPI *PFSay)( NPCDIALOG_INFO* pInfo, LPCTSTR szMsg );
typedef int (WINAPI *PFEndSay)( NPCDIALOG_INFO*  pInfo );
typedef int (WINAPI *PFRandom)( NPCDIALOG_INFO*  pInfo, int n );
typedef int (WINAPI *PFExit)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFSetScriptTimer)( NPCDIALOG_INFO* pInfo, int nTimer );
typedef int (WINAPI *PFReplace)( NPCDIALOG_INFO*  pInfo, int nWorld, float x, float y, float z );
typedef int (WINAPI *PFReplaceKey)( NPCDIALOG_INFO* pInfo, int nWorld, LPCTSTR szKey );
typedef int (WINAPI *PFGetPlayerLvl)( NPCDIALOG_INFO* pInfo );  
typedef int (WINAPI *PFGetPlayerJob)( NPCDIALOG_INFO* pInfo );  
typedef int (WINAPI *PFIsGuildQuest)( NPCDIALOG_INFO* pInfo, int nQuest );
typedef int (WINAPI *PFGetGuildQuestState)( NPCDIALOG_INFO* pInfo, int nQuest );
typedef int (WINAPI *PFIsWormonServer)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFPrintSystemMessage)( NPCDIALOG_INFO* pInfo, int nText );
typedef int (WINAPI *PFMonHuntStart)( NPCDIALOG_INFO* pInfo, int nQuest, int nState, int nState2, int n );
typedef int (WINAPI *PFMonHuntStartParty)( NPCDIALOG_INFO*  pInfo, int nQuest, int nState, int nState2, int n );
typedef int (WINAPI *PFInitStat)( NPCDIALOG_INFO*  pInfo );
typedef int	(WINAPI *PFInitStr)( NPCDIALOG_INFO*  pInfo );
typedef int	(WINAPI *PFInitSta)( NPCDIALOG_INFO*  pInfo );
typedef int	(WINAPI *PFInitDex)( NPCDIALOG_INFO*  pInfo );
typedef int	(WINAPI *PFInitInt)( NPCDIALOG_INFO*  pInfo );
typedef int (WINAPI *PFSetQuestState)( NPCDIALOG_INFO* pInfo, int nQuest, int n );      
typedef int (WINAPI *PFSetQuest)( NPCDIALOG_INFO* pInfo, int nQuest );      
typedef int (WINAPI *PFCreateItem)( NPCDIALOG_INFO* pInfo, DWORD dwID, int nCount );	
typedef int (WINAPI *PFAddGold)( NPCDIALOG_INFO* pInfo, int nGold );     
typedef int	(WINAPI *PFRemoveGold)( NPCDIALOG_INFO* pInfo, int nGold );
typedef int (WINAPI *PFGetPlayerGold)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFGetLocalEventState)( NPCDIALOG_INFO* pInfo, int nEvent );
typedef int (WINAPI *PFAddExp)( NPCDIALOG_INFO* pInfo, int nExp );      
typedef int (WINAPI *PFIsParty)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFIsPartyMaster)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFGetPartyNum)( NPCDIALOG_INFO* pInfo );
typedef int	(WINAPI *PFGetPartyLevel)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFIsPartyGuild)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFIsGuild)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFIsGuildMaster)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFCreateGuild)( NPCDIALOG_INFO*  pInfo );
typedef int (WINAPI *PFDestroyGuild)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFIsPlayerSkillPoint)( NPCDIALOG_INFO*  pInfo );     
typedef int (WINAPI *PFChangeJob)( NPCDIALOG_INFO* pInfo, int nJob );     
typedef int (WINAPI *PFGetPlayerSex)( NPCDIALOG_INFO* pInfo );  
typedef int (WINAPI *PFGetItemNum)( NPCDIALOG_INFO* pInfo, DWORD dwID );    
typedef int (WINAPI *PFRemoveAllItem)( NPCDIALOG_INFO* pInfo, DWORD dwID ); 
typedef int (WINAPI *PFEquipItem)( NPCDIALOG_INFO* pInfo, DWORD dwID );     
typedef int (WINAPI *PFPlaySound)( NPCDIALOG_INFO* pInfo, LPCTSTR szMusic );
typedef int (WINAPI *PFDropQuestItem)( NPCDIALOG_INFO* pInfo, DWORD dwID, DWORD dwProb );
typedef int (WINAPI *PFExpQuestEffect)( NPCDIALOG_INFO* pInfo, DWORD dwID, BOOL bNPC );
typedef int (WINAPI *PFRemoveItem)( NPCDIALOG_INFO* pInfo, DWORD dwID, int nCount );
typedef int (WINAPI *PFRun)( NPCDIALOG_INFO* pInfo, LPCTSTR szKey, int n );
typedef int (WINAPI *PFGetQuestId)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFGetLang)( NPCDIALOG_INFO* pInfo );
typedef int	(WINAPI *PFQuerySetPlayerName)( NPCDIALOG_INFO* pInfo );
typedef int (WINAPI *PFTrace)( NPCDIALOG_INFO* pInfo, LPCTSTR szMsg );
typedef int (WINAPI *PFGetPlayerExpPercent)( NPCDIALOG_INFO* pInfo );  
typedef int (WINAPI *PFSetLevel)( NPCDIALOG_INFO* pInfo , int nSetLevel );  
typedef int (WINAPI *PFAddGPPoint)( NPCDIALOG_INFO* pInfo , int nAddGPPoint );  

struct Functions
{
	PFSayName SayName;
	PFSpeak Speak;
	PFSpeakName SpeakName;
	PFGetVal GetVal;
	PFGetSrcId GetSrcId;
	PFGetDstId GetDstId;
	PFNpcId NpcId;
	PFPcId PcId;
	PFGetGValue_ GetGValue_;
	PFSetGValue SetGValue;
	PFAddGValue AddGValue;
	PFAddKey AddKey;
	PFAddCondKey AddCondKey;
	PFAddAnswer AddAnswer;
	PFRemoveQuest RemoveQuest;
	PFRemoveAllKey RemoveAllKey;
	PFSayQuest SayQuest;
	PFBeginQuest BeginQuest;
	PFEndQuest EndQuest;
	PFAddQuestKey AddQuestKey;
	PFCreateMover CreateMover;
	PFCreateChar CreateChar;
	PFRemoveMover RemoveMover;
	PFGetDay GetDay;
	PFGetMin GetMin;
	PFGetHour GetHour;
	PFSetTimer SetTimer;
	PFIsTimeOut IsTimeOut;
	PFLaunchQuest LaunchQuest;
	PFGetEmptyInventoryNum GetEmptyInventoryNum;
	PFGetQuestState GetQuestState;
	PFIsSetQuest IsSetQuest;
	PFSetMark SetMark;
	PFGoMark GoMark;
	PFRandomIndex RandomIndex;
	PFRemoveKey RemoveKey;
	PFSay Say;
	PFEndSay EndSay;
	PFRandom Random;
	PFExit Exit;
	PFSetScriptTimer SetScriptTimer;
	PFReplace Replace;
	PFReplaceKey ReplaceKey;
	PFGetPlayerLvl GetPlayerLvl;
	PFGetPlayerJob GetPlayerJob;
	PFIsGuildQuest IsGuildQuest;
	PFGetGuildQuestState GetGuildQuestState;
	PFIsWormonServer IsWormonServer;
	PFPrintSystemMessage PrintSystemMessage;
	PFMonHuntStart MonHuntStart;
	PFMonHuntStartParty MonHuntStartParty;
	PFInitStat InitStat;
	PFInitStr InitStr;
	PFInitSta InitSta;
	PFInitDex InitDex;
	PFInitInt InitInt;
	PFSetQuestState SetQuestState;
	PFSetQuest SetQuest;
	PFCreateItem CreateItem;
	PFAddGold AddGold;
	PFRemoveGold RemoveGold;
	PFGetPlayerGold GetPlayerGold;
	PFGetLocalEventState GetLocalEventState;
	PFAddExp AddExp;
	PFIsParty IsParty;
	PFIsPartyMaster IsPartyMaster;
	PFGetPartyNum GetPartyNum;
	PFGetPartyLevel GetPartyLevel;
	PFIsPartyGuild IsPartyGuild;
	PFIsGuild IsGuild;
	PFIsGuildMaster IsGuildMaster;
	PFCreateGuild CreateGuild;
	PFDestroyGuild DestroyGuild;
	PFIsPlayerSkillPoint IsPlayerSkillPoint;
	PFChangeJob ChangeJob;
	PFGetPlayerSex GetPlayerSex;
	PFGetItemNum GetItemNum;
	PFRemoveAllItem RemoveAllItem;
	PFEquipItem EquipItem;
	PFPlaySound PlaySound;
	PFDropQuestItem DropQuestItem;
	PFExpQuestEffect ExpQuestEffect;
	PFRemoveItem RemoveItem;
	PFRun Run;
	PFGetQuestId GetQuestId;
	PFGetLang GetLang;
	PFQuerySetPlayerName QuerySetPlayerName;
	PFTrace Trace;
	PFGetPlayerExpPercent GetPlayerExpPercent;
	PFSetLevel SetLevel;
	PFAddGPPoint AddGPPoint;
};

struct NPCDIALOG_INFO
{
	virtual int	GetReturn() = 0;
	virtual int GetDstId()  = 0;
	virtual int GetSrcId()  = 0;
	virtual int GetCaller() = 0;
	virtual int GetQuest()  = 0;
	virtual int GetNpcId()  = 0;
	virtual int GetPcId()   = 0;
	virtual int* GetGlobal() = 0;
	virtual LPCTSTR GetName() = 0;

	virtual Functions* GetFunctions() = 0;
};

#endif // __FUNCTIONSINFO_H__
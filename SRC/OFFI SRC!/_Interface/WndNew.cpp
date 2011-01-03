
#include "stdafx.h"
#include "resData.h"
#include "WndNew.h"

#include "DPClient.h"
#include "WndField.h"
extern	CDPClient	g_DPlay;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CWndNew::CWndNew() 
{
	m_pInventory = NULL;
	m_pUpgradeItem = NULL;
} 
CWndNew::~CWndNew() 
{ 
} 
void CWndNew::OnDraw( C2DRender* p2DRender ) 
{ 
} 
void CWndNew::OnInitialUpdate() 
{ 
	
	CWndNeuz::OnInitialUpdate(); 
	// ���⿡ �ڵ��ϼ���
	


	// ������ �߾����� �ű�� �κ�.
	CRect rectRoot = m_pWndRoot->GetLayoutRect();
	CRect rectWindow = GetWindowRect();
	CPoint point( rectRoot.right - rectWindow.Width(), 110 );
	Move( point );
	MoveParentCenter();
	m_pStatic = (CWndStatic *)GetDlgItem( WIDC_STATIC1 );
} 
// ó�� �� �Լ��� �θ��� ������ ������.
BOOL CWndNew::Initialize( CWndBase* pWndParent, DWORD /*dwWndId*/ ) 
{ 
	// Daisy���� ������ ���ҽ��� ������ ����.
	m_pInventory = (CWndInventory*)pWndParent;
	
	return CWndNeuz::InitDialog( g_Neuz.GetSafeHwnd(), APP_NEW, 0, CPoint( 0, 0 ), pWndParent );
} 

/*
  ���� ������ ���� ��� 
BOOL CWndQuitRoom::Initialize( CWndBase* pWndParent, DWORD dwWndId ) 
{ 
	CRect rectWindow = m_pWndRoot->GetWindowRect(); 
	CRect rect( 50 ,50, 300, 300 ); 
	SetTitle( _T( "title" ) ); 
	return CWndNeuz::Create( WBS_THICKFRAME | WBS_MOVE | WBS_SOUND | WBS_CAPTION, rect, pWndParent, dwWndId ); 
} 
*/
BOOL CWndNew::OnCommand( UINT nID, DWORD dwMessage, CWndBase* pWndBase ) 
{ 
	return CWndNeuz::OnCommand( nID, dwMessage, pWndBase ); 
} 
void CWndNew::OnSize( UINT nType, int cx, int cy ) 
{ 
	CWndNeuz::OnSize( nType, cx, cy ); 
} 
void CWndNew::OnLButtonUp( UINT nFlags, CPoint point ) 
{ 
} 
void CWndNew::OnLButtonDown( UINT nFlags, CPoint point ) 
{ 
} 
BOOL CWndNew::OnChildNotify( UINT message, UINT nID, LRESULT* pLResult ) 
{ 
	switch(nID)
	{
		case WIDC_BUTTON1:// ok ��ư
			if(m_pInventory)
			{
				m_pInventory->m_pUpgradeItem = m_pUpgradeItem;
				m_pInventory->m_dwEnchantWaitTime = g_tmCurrent + SEC(4);
			}
			Destroy();
			break;

		case WIDC_BUTTON2:// cancel ��ư
			if(m_pInventory)
			{
				m_pInventory->BaseMouseCursor();
			}
			Destroy();
			break;
	};
	return CWndNeuz::OnChildNotify( message, nID, pLResult ); 
} 

void CWndNew::SetItem(CItemBase*	m_pItem)
{
	m_pUpgradeItem = m_pItem;
}
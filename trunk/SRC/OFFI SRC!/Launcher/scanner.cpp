//*************************************************************
//													        
//  �������� ������ Recursive descent parser		        
//  ������ ����� �����ϰ� �Լ��� ȣ���� �� ������,			 
//  goto ��� �� Little C���� �������� �ʴ� ����� �����Ѵ�. 
//                            								
//  by Travis nam			                       			
//												               
//*************************************************************

#include "stdafx.h"
#include <comdef.h>
#include "vutil.h"
#include "xutil.h"

#define Error	printf

//
// ��ū ��Ʈ��
//
WORD g_codePage = 0;	// 949

namespace THAI
{
	enum CLASS {	
		CTRL= 0,
			NON= 1,
			CONS= 2,
			LV= 3,
			FV1= 4,
			FV2= 5,
			FV3= 6,
			BV1= 7,
			BV2= 8,
			BD= 9,
			TONE=10,
			AD1=11,
			AD2=12,
			AD3=13,
			AV1=14,
			AV2=15,
			AV3=16,
	};
	
	CLASS	CLASS_TABLE[256] = {
		CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, 
			CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, 
			NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON, 
			NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON, 
			NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON, 
			NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON, 
			NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON, 
			NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON, CTRL, 
			CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, 
			CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, CTRL, 
			NON, CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS, 
			CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS, 
			CONS, CONS, CONS, CONS,  FV3, CONS,  FV3, CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS,  NON, 
			FV1,  AV2,  FV1,  FV1,  AV1,  AV3,  AV2,  AV3,  BV1,  BV2,   BD,  NON,  NON,  NON,  NON,  NON, 
			LV,   LV,   LV,   LV,   LV,  FV2,  NON,  AD2, TONE, TONE, TONE, TONE,  AD1,  AD1,  AD3,  NON, 
			NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON, CTRL, 
	};
	
	namespace INPUT
	{
		enum TYPE { A, C, S, R, X };
		
		bool COMPOSIBLE[3][5] = {
			{ true, true, true, true, true },
			{ true, true, true,false, true },
			{ true, true,false,false, true },
		};

		TYPE STATE_CHECK[17][17] = {
		//    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 
			{ X,A,A,A,A,A,A,R,R,R,R,R,R,R,R,R,R }, // 0 
			{ X,A,A,A,S,S,A,R,R,R,R,R,R,R,R,R,R }, // 1 
			{ X,A,A,A,A,S,A,C,C,C,C,C,C,C,C,C,C }, // 2 
			{ X,S,A,S,S,S,S,R,R,R,R,R,R,R,R,R,R }, // 3 
			{ X,S,A,S,A,S,A,R,R,R,R,R,R,R,R,R,R }, // 4 
			{ X,A,A,A,A,S,A,R,R,R,R,R,R,R,R,R,R }, // 5 
			{ X,A,A,A,S,A,S,R,R,R,R,R,R,R,R,R,R }, // 6 
			{ X,A,A,A,A,S,A,R,R,R,C,C,R,R,R,R,R }, // 7 
			{ X,A,A,A,S,S,A,R,R,R,C,R,R,R,R,R,R }, // 8 
			{ X,A,A,A,S,S,A,R,R,R,R,R,R,R,R,R,R }, // 9 
			{ X,A,A,A,A,A,A,R,R,R,R,R,R,R,R,R,R }, // 0 
			{ X,A,A,A,S,S,A,R,R,R,R,R,R,R,R,R,R }, // 1 
			{ X,A,A,A,S,S,A,R,R,R,R,R,R,R,R,R,R }, // 2 
			{ X,A,A,A,S,S,A,R,R,R,R,R,R,R,R,R,R }, // 3 
			{ X,A,A,A,S,S,A,R,R,R,C,C,R,R,R,R,R }, // 4 
			{ X,A,A,A,S,S,A,R,R,R,C,R,R,R,R,R,R }, // 5 
			{ X,A,A,A,S,S,A,R,R,R,C,R,C,R,R,R,R }, // 6 
		};
	}
	
	namespace OUTPUT
	{
		enum TYPE { N, C, X };
		//    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 
		TYPE STATE_CHECK[17][17] = {
			{ X,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N }, // 0 
			{ X,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N }, // 1 
			{ X,N,N,N,N,N,N,C,C,C,C,C,C,C,C,C,C }, // 2 
			{ X,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N }, // 3 
			{ X,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N }, // 4 
			{ X,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N }, // 5 
			{ X,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N }, // 6 
			{ X,N,N,N,N,N,N,N,N,N,C,C,N,N,N,N,N }, // 7 
			{ X,N,N,N,N,N,N,N,N,N,C,N,N,N,N,N,N }, // 8 
			{ X,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N }, // 9 
			{ X,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N }, // 0 
			{ X,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N }, // 1 
			{ X,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N }, // 2 
			{ X,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N }, // 3 
			{ X,N,N,N,N,N,N,N,N,N,C,C,N,N,N,N,N }, // 4 
			{ X,N,N,N,N,N,N,N,N,N,C,N,N,N,N,N,N }, // 5 
			{ X,N,N,N,N,N,N,N,N,N,C,N,C,N,N,N,N }, // 6 
		};
	}
	
}

bool	IsComposibleTh(BYTE prev, BYTE curr, int mode)
{
	using namespace THAI;
	using namespace INPUT;

	if(mode > 2) {
		return false;
	} else {
		return COMPOSIBLE[mode][STATE_CHECK[CLASS_TABLE[prev]][CLASS_TABLE[curr]]];
	}
}

// Unicode of thai : 0x0E00~0x0E7F (Direct Mapping)
// Thai Character -> Unicode    (char+0x0E00)-0xA0 =    char+0x0D60
// Unicode -> Thai Character (wchar_t-0x0E00)+0xA0 = wchar_t-0x0D60

const char* CharNextTh(const char* lpsz)
{
	using namespace THAI;
	using namespace OUTPUT;

	const BYTE* stream = (const BYTE*)(lpsz);

	while(STATE_CHECK
		[ 
			CLASS_TABLE
			[ 
				stream[ 0 ] 
			] 
		]
		[ 
			CLASS_TABLE
			[ 
				stream[ 1 ] 
			] 
		] == C) ++stream;

	return (const char*)(stream+1);
}

const char*	CharNextEx(const char* strText, WORD codePage)
{
	if(codePage == 874)
	{
		return CharNextTh(strText);
	}
	else
	{
		return CharNextExA(g_codePage, strText, 0);
	}
}


CScanner::CScanner( BOOL bComma )
{
	m_bComma = bComma;
	m_pProg = m_pBuf = NULL;
	m_bMemFlag = 1;
	dwValue	= 0;
	m_lpMark = NULL;
	m_dwDef = 0;
	token = m_mszToken;
	m_bWideChar = FALSE;
	m_bErrorCheck = TRUE;
}

CScanner::CScanner( LPVOID p, BOOL bComma )
{
	m_bComma = bComma;
	m_pProg = m_pBuf = (CHAR*)p;
	m_bMemFlag = 1;
	dwValue	= 0;
	m_dwDef = 0;
	token = m_mszToken;
	m_bWideChar = FALSE;
	m_bErrorCheck = TRUE;
}

CScanner::~CScanner()
{
	Free();
}

void CScanner::Free()
{
	if(!m_bMemFlag && m_pBuf) 
		safe_delete( m_pBuf );
	m_pProg = m_pBuf = 0;
}

BOOL CScanner::Read( CFileIO* pFile, BOOL bMultiByte  )
{
	m_bMemFlag = 0;
	char* pProg;
	m_nProgSize = pFile->GetLength();
	pProg = new char[ m_nProgSize + 2 ];
	m_pProg = m_pBuf = pProg;
	if( !m_pBuf ) return 0;
	pFile->Read( m_pBuf,m_nProgSize );
	*(pProg + m_nProgSize ) = '\0';
	*(pProg + m_nProgSize + 1 ) = '\0';
	// 0xfffe�� 2����Ʈ�� ���� ��(0x0000)�� 2����Ʈ�� �߰��ؼ� �ᱹ m_nProgSize�� ��ȭ ����.
	// �ؽ�Ʈ�� �����ڵ��� ��� ��Ƽ����Ʈ�� ���� 
	if( (BYTE)*(pProg + 0 ) == 0xff && (BYTE)*(pProg + 1 ) == 0xfe ) // is unicode ?
	{
		m_bWideChar = TRUE;
		if( bMultiByte ) // is unicode ?
		{
			CHAR* lpMultiByte = new CHAR[ m_nProgSize + 2 ];
			int nResult = WideCharToMultiByte( g_codePage, 0, (LPCWSTR)(pProg + 2), -1, lpMultiByte, 
				(m_nProgSize + 2) * sizeof(CHAR), NULL, NULL );
			//cchWideChar
			lpMultiByte[ nResult ] = '\0';
			memcpy( pProg, lpMultiByte, nResult );
			safe_delete( lpMultiByte );
			m_bWideChar = FALSE;
		}
		else
		{
			memcpy( pProg, pProg + 2, m_nProgSize );

		}
	}
	return 1;
}
BOOL CScanner::Load( LPCTSTR lpszFileName, BOOL bMultiByte )
{
	CResFile file; 
	CString fileName = lpszFileName;
	fileName.MakeLower();
	if( !file.Open(lpszFileName, "rb" ) ) 
		return 0;
	m_strFileName = lpszFileName;
	return Read( &file, bMultiByte );
}


BOOL CScanner::Load_FileIO( LPCTSTR lpszFileName, BOOL bMultiByte )
{
	CFileIO file;
	CString fileName = lpszFileName;
	fileName.MakeLower();
	if( !file.Open(lpszFileName, "rb" ) ) 
		return 0;
	m_strFileName = lpszFileName;
	return Read( &file, bMultiByte );
}
void CScanner::SetProg( LPVOID pProg )
{
	m_bMemFlag = 1; m_pProg = m_pBuf = (CHAR*)pProg;
}
int CScanner::GetLineNum( LPVOID lpProg )
{
	int nLine = 0;
	if( lpProg == NULL )
		lpProg = m_pProg;
	
	if( m_bWideChar == FALSE )
	{
		CHAR* pTemp = m_pBuf;
		int nLine = 0;
		while( lpProg != pTemp )
		{
			if( *pTemp == '\r' )
				nLine++;
			pTemp++;
		}
		return nLine;
	}
	else
	{
		wchar_t* pTemp = (wchar_t*)m_pBuf;
		int nLine = 0;
		while( lpProg != pTemp )
		{
			if( *pTemp == '\r' )
				nLine++;
			pTemp++;
		}
		return nLine;
	}
	return nLine;
}
void CScanner::GetLastFull() // ������� ������ �ѹ��� �д´�.
{
	if( m_bWideChar )
	{
		wchar_t* pProg = (wchar_t*)m_pProg;
		// ���� white space�� ��ŵ
		while( iswhite( *pProg ) && *pProg && *pProg != '\r' ) 
			pProg++;
		
		wchar_t* pTemp = m_wszToken; 
		while( *pProg && *pProg!='\r' )
		{
			*pTemp++ = *pProg++;
		}
		// ���� white space�� ��ŵ
		if( pTemp != m_wszToken )
		{
			pTemp--;
			while( iswhite( *pTemp ) && *pTemp ) 
				pTemp--;
			pTemp++;
		}
		m_pProg = (char*)pProg;
		*pTemp = '\0';

		WideCharToMultiByte(g_codePage, 0, m_wszToken, -1, m_mszToken, sizeof(m_mszToken), NULL, NULL);
		Token = m_wszToken;
	}
	else
	{
		// ���� white space�� ��ŵ
		while( iswhite( *m_pProg ) && *m_pProg && *m_pProg != '\r' ) 
			m_pProg++;
		
		char* pTemp = token; 
		while( *m_pProg && *m_pProg!='\r' )
		{
			int count = CopyChar( m_pProg, pTemp );
			m_pProg += count;
			pTemp += count;
		}
		// ���� white space�� ��ŵ
		if( pTemp != token )
		{
			pTemp--;
			while( iswhite( *pTemp ) && *pTemp ) 
				pTemp--;
			pTemp++;
		}
		*pTemp = '\0';
		Token = token;
	}
}
int CScanner::GetToken( BOOL bComma )
{
	if( m_bWideChar == TRUE )
		return GetToken_Wide( bComma );

	char* pszTemp = m_mszToken; *pszTemp = '\0';
	tokenType = TEMP; tok = NONE_;
	m_nDoubleOps = 0;
BACK:
	// white space�� ��ŵ
	while( iswhite( *m_pProg ) && *m_pProg ) 
		m_pProg++;

	while(*m_pProg=='/') // �ּ��� ó��
	{
		m_pProg++;
		if(*m_pProg=='/') 
		{ 
			m_pProg++;
			while(*m_pProg!='\r'&&*m_pProg!='\0') m_pProg++;
			if(*m_pProg=='\r') m_pProg+=2;
		}
		else
		if(*m_pProg=='*') 
		{
			m_pProg++;
			do 
			{
				while(*m_pProg!='*'&&*m_pProg!='\0') m_pProg++;
				// ������ ���̶��?
				if(*m_pProg=='\0') 
				{
					tok = FINISHED;
					tokenType = DELIMITER; 
					return tokenType;
				}
				m_pProg++;
			} while(*m_pProg!='/');
			m_pProg++;
			while(iswhite(*m_pProg) && *m_pProg) m_pProg++;
		}
		else 
		{
			m_pProg--;
			break;
		}
		goto BACK;
	}
	// ȭ���� ��
	if(*m_pProg=='\0') 
	{
		tok = FINISHED;
		tokenType = DELIMITER; 
		goto EXIT;
	}
	// Comma ������ �������ΰ�?
	if( bComma || m_bComma )
	{
		// �޸��� ����Ÿ�� ��, �Ǵ� ���� �ڵ尡 ���� ������ �д´�.
		// �޸� ������ ���� �װ��� pszTemp�� NUMBER���� �����Ѵ�.
		if(*m_pProg=='"') 
		{
			m_pProg++;
			while(*m_pProg!='"' && *m_pProg!='\r' && *m_pProg!='\0') *pszTemp++ = *m_pProg++;
			m_pProg++; 
			tokenType = STRING; 
		}
		else
		{
			while(*m_pProg!=',' && *m_pProg!='\r' && *m_pProg!='\0') 
				*pszTemp++ = *m_pProg++;
		}
		if( *m_pProg == ',' || *m_pProg == '\r')
			m_pProg++; // skim comma
		// white space�� ��ŵ
		if( pszTemp != token )
		{
				pszTemp--;
			while( iswhite( *pszTemp ) && *pszTemp ) 
				pszTemp--;
			pszTemp++;
			if( isdigit2( token[0] ) )
				tokenType = NUMBER;
			if(token[0]=='0' && token[1]=='x') 
				tokenType = HEX;
		}
		goto EXIT;
	}
	if(strchr("!<>=",*m_pProg)) 
	{ // is or might be a relation operator
		switch(*m_pProg) 
		{
			case '=':
				if(*(m_pProg+1)=='=') 
				{
					*pszTemp++ = *m_pProg++;
					*pszTemp++ = *m_pProg++;
					m_nDoubleOps = EQ;
				}
				break;
			case '!':
				if(*(m_pProg+1)=='=') 
				{
					*pszTemp++ = *m_pProg++;
					*pszTemp++ = *m_pProg++;
					m_nDoubleOps = NE;
				}
				else 
				{
					*pszTemp++ = *m_pProg++;
					m_nDoubleOps = NT;
				}
				break;
			case '<':
				if(*(m_pProg+1)=='=') 
				{
					*pszTemp++ = *m_pProg++;
					*pszTemp++ = *m_pProg++;
					m_nDoubleOps = LE;
				}
				else 
				{
					*pszTemp++ = *m_pProg++;
					m_nDoubleOps = LT;
				}
				break;
			case '>':
				if(*(m_pProg+1)=='=') 
				{
					*pszTemp++ = *m_pProg++;
					*pszTemp++ = *m_pProg++;
					m_nDoubleOps = GE;
				}
				else 
				{
					*pszTemp++ = *m_pProg++;
					m_nDoubleOps = GT;
				}
				break;
		}
		if(*token) { tokenType = DELIMITER; goto EXIT; }
	}
	// delimiter
	if(*m_pProg == '&' && *(m_pProg+1) == '&') 
	{
		*pszTemp = *(pszTemp+1) = '&';
		pszTemp+=2; m_pProg+=2; tokenType = DELIMITER; goto EXIT; 
	}
	if(*m_pProg == '|' && *(m_pProg+1) == '|') 
	{
		*pszTemp = *(pszTemp+1) = '|';
		pszTemp+=2; m_pProg+=2; tokenType = DELIMITER; goto EXIT; 
	}
	if( strchr( "+-*^/%=;(),':{}.", *m_pProg ) )  
	{
		*pszTemp = *m_pProg; m_pProg++;
		pszTemp++;	tokenType = DELIMITER; goto EXIT;
	}
	// ��Ʈ�� 
	if(*m_pProg=='"') 
	{
		m_pProg++;
		while( *m_pProg!='"' && *m_pProg!='\r' && *m_pProg!='\0' && ( pszTemp - token ) < MAX_TOKENSTR ) 
		{
			int count = CopyChar( m_pProg, pszTemp );
			m_pProg += count;
			pszTemp += count;
		}
		m_pProg++; 
		tokenType = STRING; 
		if( *(m_pProg-1 ) != '"' )
		{
			if( *(m_pProg-1 ) == '\0' )
				m_pProg--; 
			if( m_bErrorCheck )
			{
				CString string;
				if( ( pszTemp - token ) >= MAX_TOKENSTR )
					string.Format( "line(%d) ���� %s���� \"%s\" ��Ʈ�� ���̰� %d����Ʈ�� �ʰ�����.", GetLineNum(), m_strFileName, token, MAX_TOKENSTR );
				else
					string.Format( "line(%d) ���� %s���� \"%s\" ��Ʈ���� ����ǥ�� ������ ����.", GetLineNum(), m_strFileName, token );
				Error( string );
			}
		}
		goto EXIT;
	}
	// hex
	if( *m_pProg=='0' && *(m_pProg + 1 )=='x' ) 
	{
		m_pProg+=2;
		while(!isdelim(*m_pProg)) *pszTemp++ = *m_pProg++;
		tokenType = HEX; goto EXIT;
	}
	// ����
	if( isdigit2( *m_pProg ) && !IsMultiByte( m_pProg ) ) //���� �˻縸���� �����µ� �� �ѱ��� �ƴ� ��쵵 üũ����?
	{
		while( !isdelim( *m_pProg ) ) *pszTemp++ = *m_pProg++;
		tokenType = NUMBER; goto EXIT;
	}
	// ������ ���
	if( isalpha( *m_pProg ) || IsMultiByte( m_pProg ) || *m_pProg == '#' || *m_pProg == '_' || *m_pProg == '@' || *m_pProg=='$' || *m_pProg == '?' ) 
	{
		while( !isdelim( *m_pProg ) ) 
		{
			int count = CopyChar( m_pProg, pszTemp );
			m_pProg += count;
			pszTemp += count;
		}
	}
	else
		*pszTemp++ = *m_pProg++;
	tokenType = TEMP;
EXIT:
	*pszTemp = '\0';
	Token = token; 
	return tokenType;
}

int CScanner::GetToken_Wide( BOOL bComma )
{
	wchar_t* pProg = (wchar_t*)m_pProg;
	wchar_t* pszTemp = m_wszToken; *pszTemp = '\0';
	tokenType = TEMP; tok = NONE_;
	m_nDoubleOps = 0;
BACK:
	while( iswhite( *pProg ) && *pProg ) 
		pProg++;

	while(*pProg=='/') // �ּ��� ó��
	{
		pProg++;
		if(*pProg=='/') 
		{ 
			pProg++;
			while(*pProg!='\r'&&*pProg!='\0') pProg++;
			if(*pProg=='\r') pProg+=2;
		}
		else
		if(*pProg=='*') 
		{
			pProg++;
			do 
			{
				while(*pProg!='*'&&*pProg!='\0') pProg++;
				// ������ ���̶��?
				if(*pProg=='\0') 
				{
					tok = FINISHED;
					tokenType = DELIMITER; 
					m_pProg = (char*)pProg;
					return tokenType;
				}
				pProg++;
			} while(*pProg!='/');
			pProg++;
			while(iswhite(*pProg) && *pProg) pProg++;
		}
		else 
		{
			pProg--;
			break;
		}
		goto BACK;
	}
	// ȭ���� ��
	if(*pProg=='\0') 
	{
		tok = FINISHED;
		tokenType = DELIMITER; 
		goto EXIT;
	}
	// Comma ������ �������ΰ�?
	if( bComma || m_bComma )
	{
		// �޸��� ����Ÿ�� ��, �Ǵ� ���� �ڵ尡 ���� ������ �д´�.
		// �޸� ������ ���� �װ��� pszTemp�� NUMBER���� �����Ѵ�.
		if(*pProg=='"') 
		{
			pProg++;
			while(*pProg!='"' && *pProg!='\r' && *pProg!='\0') *pszTemp++ = *pProg++;
			pProg++; 
			tokenType = STRING; 
		}
		else
		{
			while(*pProg!=',' && *pProg!='\r' && *pProg!='\0') 
				*pszTemp++ = *pProg++;
		}
		if( *pProg == ',' || *pProg == '\r')
			pProg++; // skim comma
		// white space�� ��ŵ
		if( pszTemp != m_wszToken )
		{
				pszTemp--;
			while( iswhite( *pszTemp ) && *pszTemp ) 
				pszTemp--;
			pszTemp++;
			if( isdigit2( m_wszToken[0] ) )
				tokenType = NUMBER;
			if(m_wszToken[0]=='0' && m_wszToken[1]=='x') 
				tokenType = HEX;
		}
		goto EXIT;
	}
	if(strchr("!<>=",*pProg)) 
	{ // is or might be a relation operator
		switch(*pProg) 
		{
			case '=':
				if(*(pProg+1)=='=') 
				{
					*pszTemp++ = *pProg++;
					*pszTemp++ = *pProg++;
					m_nDoubleOps = EQ;
				}
				break;
			case '!':
				if(*(pProg+1)=='=') 
				{
					*pszTemp++ = *pProg++;
					*pszTemp++ = *pProg++;
					m_nDoubleOps = NE;
				}
				else 
				{
					*pszTemp++ = *pProg++;
					m_nDoubleOps = NT;
				}
				break;
			case '<':
				if(*(pProg+1)=='=') 
				{
					*pszTemp++ = *pProg++;
					*pszTemp++ = *pProg++;
					m_nDoubleOps = LE;
				}
				else 
				{
					*pszTemp++ = *pProg++;
					m_nDoubleOps = LT;
				}
				break;
			case '>':
				if(*(pProg+1)=='=') 
				{
					*pszTemp++ = *pProg++;
					*pszTemp++ = *pProg++;
					m_nDoubleOps = GE;
				}
				else 
				{
					*pszTemp++ = *pProg++;
					m_nDoubleOps = GT;
				}
				break;
		}
		if(m_wszToken[0]) { tokenType = DELIMITER; goto EXIT; }
	}
	// delimiter
	if(*pProg == '&' && *(pProg+1) == '&') 
	{
		*pszTemp = *(pszTemp+1) = '&';
		pszTemp+=2; pProg+=2; tokenType = DELIMITER; goto EXIT; 
	}
	if(*pProg == '|' && *(pProg+1) == '|') 
	{
		*pszTemp = *(pszTemp+1) = '|';
		pszTemp+=2; pProg+=2; tokenType = DELIMITER; goto EXIT; 
	}
	if( strchr( "+-*^/%=;(),':{}.", *pProg ) )  
	{
		*pszTemp = *pProg; pProg++;
		pszTemp++;	tokenType = DELIMITER; goto EXIT;
	}
	// ��Ʈ��
	if(*pProg=='"') 
	{
		pProg++;
		while(*pProg!='"' && *pProg!='\r' && *pProg!='\0' && ( pszTemp - m_wszToken ) < MAX_TOKENSTR ) 
			*pszTemp++ = *pProg++;
		pProg++; 
		tokenType = STRING; 
		if( *(pProg-1 ) != '"' )
		{
			if( *(pProg-1 ) == '\0' )
				pProg--; 
			if( m_bErrorCheck )
			{
				CString string;
				if( ( pszTemp - m_wszToken ) >= MAX_TOKENSTR )
					string.Format( "line(%d) ���� %s���� \"%s\" ��Ʈ�� ���̰� %d����Ʈ�� �ʰ�����.", GetLineNum(), m_strFileName, token, MAX_TOKENSTR );
				else
					string.Format( "line(%d) ���� %s���� \"%s\" ��Ʈ���� ����ǥ�� ������ ����.", GetLineNum(), m_strFileName, token );
				Error( string );
			}
		}
		goto EXIT;
	}
	// hex
	if( *pProg=='0' && *(pProg + 1 )=='x' ) 
	{
		pProg+=2;
		while(!isdelim(*pProg)) *pszTemp++ = *pProg++;
		tokenType = HEX; goto EXIT;
	}
	// ����
	if( isdigit2( *pProg ) && !IsDBCSLeadByte( *pProg ) ) //���� �˻縸���� �����µ� �� �ѱ��� �ƴ� ��쵵 üũ����?
	{
		while( !isdelim( *pProg ) ) *pszTemp++ = *pProg++;
		tokenType = NUMBER; goto EXIT;
	}
	// ������ ���
	if( isalpha( *pProg ) || IsDBCSLeadByte( *pProg ) || *pProg == '#' || *pProg == '_' || *pProg == '@' || *pProg=='$' || *pProg == '?' ) 
	{
		while(!isdelim(*pProg)) *pszTemp++ = *pProg++;
	}
	else
		*pszTemp++ = *pProg++;
	tokenType = TEMP;
EXIT:
	m_pProg = (char*)pProg;
	*pszTemp = '\0';
	Token = m_wszToken; 
	WideCharToMultiByte(g_codePage, 0, m_wszToken, -1, m_mszToken, sizeof(m_mszToken), NULL, NULL);
	return tokenType;
}

int CScanner::GetNumber( BOOL bComma )
{
	m_dwDef = 1;
	if( GetToken( bComma ) == HEX )
	{
		Token.MakeLower();
		DWORDLONG dwlNumber = 0;
		DWORD dwMulCnt = 0;
		CHAR cVal;
		for( int i = Token.GetLength() - 1; i >= 0; i--)
		{
			cVal = Token[ i ];
			if( cVal >= 'a' )
				cVal = ( cVal - 'a' ) + 10;
			else cVal -= '0';
			dwlNumber |= (DWORDLONG) cVal << dwMulCnt;
			dwMulCnt += 4;
		}
		m_dwDef = 0;
		return (DWORD)dwlNumber;
	}
	else
	if(!Token.IsEmpty())
	{
		switch(Token[0])
		{
			case '=': 
				m_dwDef = 0;
				return NULL_ID;
			case '-': 
				if( bComma == FALSE )
				{
					GetToken();	
					m_dwDef = 0;
					return -atoi(Token);
				}
				else
				{
					m_dwDef = 0;
					return atoi(Token);
				}
			case '+':	
				if( bComma == FALSE )
					GetToken();	
		}
		m_dwDef = 0;
		return atoi(Token);
	}
	m_dwDef = 0;
	return 0;
}

__int64 CScanner::GetInt64( BOOL bComma )
{
	m_dwDef		= 1;
	if( GetToken( bComma ) == HEX )
	{
	}
	else if( !Token.IsEmpty() )
	{
		switch( Token[0] )
		{
			case '=': 
				m_dwDef = 0;
				return NULL_ID;
			case '-': 
				if( bComma == FALSE )
				{
					GetToken();	
					m_dwDef = 0;
					return -_atoi64( Token );
				}
				else
				{
					m_dwDef = 0;
					return _atoi64( Token );
				}
			case '+':	
				if( bComma == FALSE )
					GetToken();	
		}
		m_dwDef = 0;
		return _atoi64( Token );
	}
	m_dwDef = 0;
	return (__int64)0;
}

FLOAT CScanner::GetFloat( BOOL bComma )
{
	m_dwDef = 1;
	GetToken( bComma );
	if( !Token.IsEmpty() )
	{
		switch( Token[0] )
		{
			case '=': 
				m_dwDef = 0;
				return -1;
			case '-': 
				GetToken(bComma);	
				m_dwDef = 0;
				return (FLOAT)-atof(Token);
			case '+':	
				GetToken(bComma);	
		}
		m_dwDef = 0;
		return (FLOAT)atof(Token);
	}
	m_dwDef = 0;
	return 0.0f;
}
DWORD CScanner::GetHex( BOOL bComma )
{
	m_dwDef = 1;
	if( GetToken( bComma ) == HEX )
	{
		Token.MakeLower();
		DWORDLONG dwlNumber = 0;
		DWORD dwMulCnt = 0;
		CHAR cVal;
		for( int i = Token.GetLength() - 1; i >= 0; i--)
		{
			cVal = Token[ i ];
			if( cVal >= 'a' )
				cVal = ( cVal - 'a' ) + 10;
			else cVal -= '0';
			dwlNumber |= (DWORDLONG) cVal << dwMulCnt;
			dwMulCnt += 4;
		}
		m_dwDef = 0;
		return (DWORD)dwlNumber;
	}
	m_dwDef = 0;
	return 0;
}


void CScanner::PutBack()
{ 
	if( m_bWideChar )
	{
		for( WORD *t = m_wszToken; *t; t++ ) 
			m_pProg-=2;
		if( tokenType == STRING ) // ����ǥ ó�� 
			m_pProg-=4;
	}
	else
	{
		for( CHAR *t = m_mszToken; *t; t++ ) 
			m_pProg--;
		if( tokenType == STRING ) // ����ǥ ó�� 
			m_pProg-=2;
	}
}

int CScanner::isdelim( wchar_t c )
{
	// LeadByte�� delim�� �ƴϹǷ� 0
	if(strchr(" !:;,+-<>'/*%^=()&|\"{}",c) || c == 9 || c == '\r' || c == 0 || c == '\n' ) 
		return 1;
	return 0;
}

int CScanner::iswhite( wchar_t c )
{
	if(c > 0 && c <= 0x20)
		return 1;
	return 0;
}

SERIALNUMBER CScanner::GetSerialNumber( BOOL bComma )
{
#ifdef __EXP_SERIAL_NUMBER0323
	return GetInt64( bComma );
#else	// __EXP_SERIAL_NUMBER0323
	return GetNumber( bComma );
#endif	// __EXP_SERIAL_NUMBER0323
}

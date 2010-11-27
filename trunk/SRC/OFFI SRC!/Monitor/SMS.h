// SMS.h: interface for the CSMS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMS_H__FBA46285_0815_484D_A137_C249CA434BF3__INCLUDED_)
#define AFX_SMS_H__FBA46285_0815_484D_A137_C249CA434BF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#define PORTNUM 5000 /* UNIX ��Ʈ��ȣ */
#define MAXMSG 256 /* �ѹ��� ���� �� �ִ� �޽����� �ִ� ���� */
#define LIMIT_DATA_LEN 170 /* ���� ��Ŷ ���� ���� (sms key�� status�� ������) */
#define TRAN_STATUS 1 /* ���ۻ��� */
#define SMS_KEY "GS" /* SMS KEY */
#define CLIENT_DATA     struct client_data_info

class CSMS  
{
public:
	CSMS();
	virtual ~CSMS();

public:

	CLIENT_DATA
	{
			char    *sms_key;
			int     data_len;
			char    *tran_id;
			char    *tran_passwd;
			char    *tran_phone;
			char    *tran_callback;
			int     tran_status;
			char    *tran_date;
			char    *tran_msg;
	};

	char msg[MAXMSG], reply[MAXMSG]; /* ������ ���� �޽����� Server���� �ǵ��ƿ��� �޽��� */
	char *server_name; /* ������ */
	char *clientmsg; /* ���۸޼��� */

	char *get_packet_info( char* szTranId, char* szTranPwd, char* szRcvNum, 
							char* szSendNum, char* szDate, char* szMsg, BOOL &bResult );
	char *getToken(char **p);

	char *SendMsg( char* szTranId, char* szTranPwd, char* szRcvNum, 
				   char* szSendNum, char* szDate, char* szMsg );
};

#endif // !defined(AFX_SMS_H__FBA46285_0815_484D_A137_C249CA434BF3__INCLUDED_)

-- SMS ���۽� �ʿ��� ����
TRAN_ID = "aeon563"
TRAN_PASSWORD = "dldhs563"
TRAN_MSG = "* Game  Server *\n*     DOWN     *\n"

tSMS = {}
-- SMS ���� ����Ʈ
function AddSMS( strName, strPhoneNum )
	local nSize = table.getn(tSMS) + 1
	
	tSMS[nSize] = {}
	tSMS[nSize].strName = strName
	tSMS[nSize].strPhoneNum = strPhoneNum
end

function GetServerName( ServerId )
	return tServerName[ServerId]
end
----------------------------------------------------------------------------
-- SMS ������ ����Ʈ ------------------------------------------------------
----------------------------------------------------------------------------
--AddSMS( "�̵��� ��", "011-9989-2001" )
--AddSMS( "���¼� ����", "016-702-1038" )
--AddSMS( "������ ����", "017-269-5621" )
--AddSMS( "�ڻ�� ����", "011-465-5362" )
--AddSMS( "����õ �븮", "016-328-7262" )
--AddSMS( "���и� ���", "010-6358-1446" )
--AddSMS( "��⿵ ���", "018-279-0573" )
--AddSMS( "������ ����", "011-9052-0177" )
--AddSMS( "������ ���", "016-276-0112" )

----------------------------------------------------------------------------
----------------------------------------------------------------------------
tServerName = {}
tServerName["1"] = "Account Server"
tServerName["10"] = "Certifier Server"

tServerName["100"] = "Database 100"
tServerName["101"] = "Core 101"
tServerName["102"] = "Login 102"
tServerName["103"] = "Cache 103"
tServerName["10101"] = "World 101"
tServerName["10201"] = "World 102"


tServerName["400"] = "Database 400"
tServerName["401"] = "Core 401"
tServerName["402"] = "Login 402"
tServerName["403"] = "Cache 403"
tServerName["40101"] = "World 401"
tServerName["40201"] = "World 402"

tServerName["500"] = "Database 500"
tServerName["501"] = "Core 501"
tServerName["502"] = "Login 502"
tServerName["503"] = "Cache 503"
tServerName["50101"] = "World 501"
tServerName["50201"] = "World 502"
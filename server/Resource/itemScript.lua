DST_STR = 1
DST_DEX = 2
DST_INT = 3
DST_STA = 4 

-- II_WEA_SWO_LONG(23��) ���� �Լ�
function F23_equip( pMover )
	Trace( "LONG �ҵ� ����" )
	
	SetDestParam( pMover, DST_STR, 3 );
	return 1
end

-- II_WEA_SWO_LONG(23��) Ż�� �Լ�
function F23_unequip( pMover )
	Trace( "LONG �ҵ� Ż��" )
	ResetDestParam( pMover, DST_STR, 3 );
	return 1
end

 

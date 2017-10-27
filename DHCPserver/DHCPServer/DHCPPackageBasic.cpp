#include "DHCPPackageBasic.h"

DHCPPackageBasic::DHCPPackageBasic()
{

}


int DHCPPackageBasic::MACAGet(char *Mac)
{
	NCB ncb;                                  //����һ��NCB(������ƿ�)���͵Ľṹ�����ncb  
	typedef struct _ASTAT_
	{
		ADAPTER_STATUS   adapt;
		NAME_BUFFER   NameBuff[30];
	}ASTAT, *PASTAT;
	ASTAT Adapter;

	typedef struct _LANA_ENUM
	{
		UCHAR length;
		UCHAR lana[MAX_LANA];
	}LANA_ENUM;
	LANA_ENUM lana_enum;

	//ȡ��������Ϣ�б�       
	UCHAR uRetCode;
	memset(&ncb, 0, sizeof(ncb));                         //���ѿ����ڴ�ռ�ncb ��ֵ����Ϊֵ 0  
	memset(&lana_enum, 0, sizeof(lana_enum));                     //���һ���ṹ���͵ı���lana_enum����ֵΪ0  

																  //�Խṹ�����ncb��ֵ  
	ncb.ncb_command = NCBENUM;                        //ͳ��ϵͳ������������  
	ncb.ncb_buffer = (unsigned char *)&lana_enum;                     //ncb_buffer��Աָ����LANA_ENUM�ṹ���Ļ�����  
	ncb.ncb_length = sizeof(LANA_ENUM);

	//����������NCBENUM����Ի�ȡ��ǰ������������Ϣ�����ж��ٸ�������ÿ�������ı�ţ�Mac��ַ��   
	uRetCode = Netbios(&ncb);                         //����netbois(ncb)��ȡ�������к�      
	if (uRetCode != NRC_GOODRET)
		return uRetCode;

	//��ÿһ�������������������Ϊ�����ţ���ȡ��Mac��ַ     
	for (int lana = 0; lana < lana_enum.length; lana++)
	{
		ncb.ncb_command = NCBRESET;                   //����������NCBRESET������г�ʼ��  
		ncb.ncb_lana_num = lana_enum.lana[lana];
		uRetCode = Netbios(&ncb);
		if (uRetCode == NRC_GOODRET)
			break;
	}
	if (uRetCode != NRC_GOODRET)
		return uRetCode;

	// ׼��ȡ�ýӿڿ���״̬��ȡ��Mac��ַ  
	memset(&ncb, 0, sizeof(ncb));
	ncb.ncb_command = NCBASTAT;                  //����������NCBSTAT�����ȡ������Ϣ  
	ncb.ncb_lana_num = lana_enum.lana[0];                    //ָ��������   
	strcpy((char*)ncb.ncb_callname, "*");                //Զ��ϵͳ����ֵΪ*  
	ncb.ncb_buffer = (unsigned char *)&Adapter;              //ָ�����ص���Ϣ��ŵı���  
	ncb.ncb_length = sizeof(Adapter);

	//���ŷ���NCBASTAT�����Ի�ȡ��������Ϣ  
	uRetCode = Netbios(&ncb);

	// ȡ����������Ϣ����������������������Ļ������ر�׼��ð�ŷָ���ʽ��     
	if (uRetCode != NRC_GOODRET)
		return uRetCode;

	sprintf(Mac, "%02X-%02X-%02X-%02X-%02X-%02X",
		Adapter.adapt.adapter_address[0],
		Adapter.adapt.adapter_address[1],
		Adapter.adapt.adapter_address[2],
		Adapter.adapt.adapter_address[3],
		Adapter.adapt.adapter_address[4],
		Adapter.adapt.adapter_address[5]
		);
	return 0;
}
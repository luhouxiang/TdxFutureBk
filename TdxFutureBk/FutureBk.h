#ifndef __PLUGIN_TCALC_FUNC
#define __PLUGIN_TCALC_FUNC
#pragma pack(push,1)

//����(���ݸ���,���,����a,����b,����c)
typedef void(*pPluginFUNC)(int, float*, float*, float*, float*);

typedef struct tagPluginTCalcFuncInfo
{
	unsigned short                nFuncMark;//�������
	pPluginFUNC                        pCallFunc;//������ַ
}PluginTCalcFuncInfo;

typedef BOOL(*pRegisterPluginFUNC)(PluginTCalcFuncInfo**);


//RegisterTdxFunc����Ϊע�ắ�����û��ĺ���ȫ��������PluginTCalcFuncInfo�ṹ��ȫ������g_CalcFuncSets�С�
typedef BOOL(*pRegisterPluginFUNC)(PluginTCalcFuncInfo**);

//=======================================

extern"C"
{
	//__cplusplus
	__declspec(dllexport)BOOL RegisterTdxFunc(PluginTCalcFuncInfo**pFun);
}


#pragma pack(pop)
#endif
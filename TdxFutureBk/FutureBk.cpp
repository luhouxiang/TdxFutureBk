// ChanLunTdx.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
//ChanLunTdx.cpp:定义DLL应用程序的导出函数。
//
#include"stdafx.h"
#include"FutureBk.h"
#include <algorithm>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;


std::map<std::string, FILE*> g_fstreams;
map<string, string> g_tables;
std::map<std::string, string> g_datas;

double roundx(double number, unsigned int bits) {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(bits) << number;
	ss >> number;
	return number;
}

void FutureBk1(int DataLen, float *pfOUT, float *pfINa, float *pfINb, float *pfINc)
{
	if (DataLen <= 1)
		return;
	if (*pfINa <= 0) {	// 不是国内期货指数，返回-1
		for (int i = 0; i<DataLen; i++)
		{
			pfOUT[i] = -1;
		}
		return;
	}
	long iDate = long(*pfINb);
	long iTime = long(*pfINc);

	char buf[1024] = { 0 };
	sprintf(buf, "T%03d", int(*pfINa));
	std::string code = buf;
	g_datas[code] = "";	// 初始化数据

	string bkCode = "";
	auto bkIt = g_tables.find(code);
	{
		bkCode = bkIt->second;
	}
	if (bkCode == "") {	// 板块指数非内置的23个，返回-2
		for (int i = 0; i<DataLen; i++)
		{
			pfOUT[i] = -2;
		}
		return;
	}

	auto streamIt = g_fstreams.find(code);
	if (streamIt == g_fstreams.end())	// 找不到文件句柄，返回2
	{
		for (int i = 0; i<DataLen; i++)
		{
			pfOUT[i] = -3;
		}
		return;
	}
	char szTime[32] = { 0 };
	memset(szTime, 0, sizeof(szTime));
	sprintf(szTime, "%04d-%02d-%02d %02d:%02d:%02d", iDate / 10000, (iDate % 10000) / 100, 
		(iDate % 10000) % 100, iTime / 100, iTime % 100, 0);
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%s,%s,1", bkCode.c_str(), szTime);
	g_datas[code] = buf;
	for (int i = 0; i<DataLen; i++)	// 全部正确，返回4
	{
		pfOUT[i] = 1;
	}
	
}

void FutureBk2(int DataLen, float *pfOUT, float *pfINa, float *pfINb, float *pfINc)
{
	if (DataLen <= 1)
		return;
	if (*pfINa <= 0) {	// 不是国内期货指数，返回-1
		for (int i = 0; i<DataLen; i++)
		{
			pfOUT[i] = -1;
		}
		return;
	}
	char buf[1024] = { 0 };
	sprintf(buf, "T%03d", int(*pfINa));
	std::string code = buf;

	std::string open = std::to_string(roundx(pfINb[DataLen-1],2));
	std::string high = std::to_string(roundx(pfINc[DataLen-1],2));

	string data = "";
	auto dataIt = g_datas.find(code);
	{
		data = dataIt->second;
	}
	if (data == "")	// 数据为空，退出
	{
		for (int i = 0; i<DataLen; i++)
		{
			pfOUT[i] = -4;
		}
		return;
	}

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%s,%s,%s", data.c_str(), open.c_str(), high.c_str());
	g_datas[code] = buf;
	for (int i = 0; i<DataLen; i++)
	{
		pfOUT[i] = 2;
	}
	return;

}


void FutureBk3(int DataLen, float *pfOUT, float *pfINa, float *pfINb, float *pfINc)
{
	if (DataLen <= 1)
		return;
	if (*pfINa <= 0) {	// 不是国内期货指数，返回-1
		for (int i = 0; i<DataLen; i++)
		{
			pfOUT[i] = -1;
		}
		return;
	}
	char buf[1024] = { 0 };
	sprintf(buf, "T%03d", int(*pfINa));
	std::string code = buf;

	std::string low = std::to_string(roundx(pfINb[DataLen-1],2));
	std::string close = std::to_string(roundx(pfINc[DataLen-1],2));

	string data = "";
	auto dataIt = g_datas.find(code);
	{
		data = dataIt->second;
	}
	if (data == "")	// 数据为空，退出
	{
		for (int i = 0; i<DataLen; i++)
		{
			pfOUT[i] = -5;
		}
		return;
	}
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%s,%s,%s", data.c_str(), low.c_str(), close.c_str());
	g_datas[code] = buf;
	for (int i = 0; i<DataLen; i++)
	{
		pfOUT[i] = 3;
	}
	return;
}

void split(const char* str, const char* seperator, std::vector<std::string>& output)
{
	size_t strLen = strlen(str);
	if (!strLen)
	{
		return;
	}
	size_t sepLength = strlen(seperator);
	const char* ptr = str;
	while (*str != '\0' && strLen >= sepLength)
	{
		if (strncmp(str, seperator, sepLength) == 0)
		{
			output.push_back(std::string(ptr, str - ptr));
			str += sepLength;
			ptr = str;
			strLen -= sepLength;
		}
		else
		{
			++str;
			--strLen;
		}
	}
	output.push_back(std::string(ptr));
}


void FutureBk4(int DataLen, float *pfOUT, float *pfINa, float *pfINb, float *pfINc)
{
	if (DataLen <= 1)
		return;
	if (*pfINa <= 0) {	// 不是国内期货指数，返回-1
		for (int i = 0; i<DataLen; i++)
		{
			pfOUT[i] = -1;
		}
		return;
	}
	char buf[1024] = { 0 };
	sprintf(buf, "T%03d", int(*pfINa));
	std::string code = buf;

	std::string volume = std::to_string(long(pfINb[DataLen-1]));
	std::string oi = std::to_string(long(pfINc[DataLen-1]));

	string data = "";
	auto dataIt = g_datas.find(code);
	{
		data = dataIt->second;
	}
	if (data == "")	// 数据为空，退出
	{
		for (int i = 0; i<DataLen; i++)
		{
			pfOUT[i] = -6;
		}
	}

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%s,%s,%s\n", data.c_str(), volume.c_str(), oi.c_str());
	
	auto streamIt = g_fstreams.find(code);
	if (streamIt == g_fstreams.end())	// 找不到文件句柄，退出
	{
		for (int i = 0; i<DataLen; i++)
		{
			pfOUT[i] = -7;
		}
		return;
	}
	fprintf(streamIt->second, buf);
	fflush(streamIt->second);
	
	for (int i = 0; i<DataLen; i++)
	{
		pfOUT[i] = 8;
	}

	return;
	
}

//加载的函数

PluginTCalcFuncInfo g_CalcFuncSets[] =
{
	{ 4, (pPluginFUNC)&FutureBk4 },
	{ 3, (pPluginFUNC)&FutureBk3 },
	{ 2, (pPluginFUNC)&FutureBk2 },
	{ 1, (pPluginFUNC)&FutureBk1 },
	{ 0,NULL },
};


//导出给TCalc的注册函数

BOOL RegisterTdxFunc(PluginTCalcFuncInfo**pFun)
{
	if (*pFun == NULL)
	{
		(*pFun) = g_CalcFuncSets;
		return TRUE;
	}
	return FALSE;
}




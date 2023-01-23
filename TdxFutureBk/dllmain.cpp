// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include <io.h>
#include <string>
#include <map>

using namespace std;

extern std::map<std::string, FILE*> g_fstreams;
extern map<string, string> g_tables;



void table_init()
{
	map<string, string> tables = {
		{ "T001","wenhuashangpin" },
		{ "T002","nongchanpin" },
		{ "T003","gongyepin" },
		{ "T004","guwubankuai" },
		{ "T005","youzhibankuai" },
		{ "T006","shiyoubankuai" },
		{ "T007","huagongbankuai" },
		{ "T008","gangtiebankuai" },
		{ "T009","yousebankuai" },
		{ "T010","ruanshangbankuai" },
		{ "T011","jiancaibankuai" },
		{ "T012","guijinshu" },
		{ "T013","meitanbankuai" },
		{ "T014","meihuagong" },
		{ "T015","tiehejin" },
		{ "T016","siliaobankuai" },
		{ "T030","jinrongqihuo" },
		{ "T031","youzhilian" },
		{ "T032","yumilian" },
		{ "T033","shengzhulian" },
		{ "T034","suhualian" },
		{ "T035","juzhilian" },
		{ "T036","heilianzhishu" }
	};
	g_tables = tables;
}

int init()
{
	table_init();
	char buf[512] = { 0 };

	for (auto it = g_tables.begin(); it != g_tables.end(); it++) {
		bool FileExist = false;
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "C:/TdxFutureBk/%s_%s.csv", it->first.c_str(), it->second.c_str());
		if (!_access(buf, 0))
			FileExist = true;

		FILE *p = fopen(buf, "a");
		if (p != NULL) {
			g_fstreams[it->first] = p;
			if (!FileExist) {
				fflush(p);
			}
		}
	}

	return 0;
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		init();
		// 第一次将一个DLL映射到进程地址空间时调用
		// The DLL is being mapped into the process' address space.
		break;
	case DLL_THREAD_ATTACH:
		// 当进程创建一个线程的时候，用于告诉DLL执行与线程相关的初始化（非主线程执行）
		// A thread is bing created.
		break;
	case DLL_THREAD_DETACH:
		// 系统调用 ExitThread 线程退出前，即将终止的线程通过告诉DLL执行与线程相关的清理
		// A thread is exiting cleanly.
		break;
	case DLL_PROCESS_DETACH:
		// 将一个DLL从进程的地址空间时调用
		// The DLL is being unmapped from the process' address space.
		break;
	}
	return (TRUE); // Used only for DLL_PROCESS_ATTACH
}


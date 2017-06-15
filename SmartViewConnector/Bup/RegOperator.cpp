/**
* Author: Rajib Chandra Das
* Topic: Windows Registry Key Processor(Create, Insert, Read, Update and Delete)
* Date: 8_July_2015
*/


//Create C++ Win32 Project in Visual Studio
//Project -> "project" Properties->Configuration Properties->C/C++->Advanced->Show Includes : YES(/ showIncludes)
//Project -> "project" Properties->Configuration Properties->General->Project Defaults->Use of MFC : Use MFC in a shared DLL

#include <iostream>
//#include <afx.h>
#include "stdafx.h"
#include "RegOperator.h"
using namespace std;

namespace RegOperate {

	RegOperator::RegOperator()
		: mKeyPath(kDefaultKeyPath)
		, mSubKey(kSubKey)
	{
	}

	RegOperator::RegOperator(HKEY hKey)
	{
//		ASSERT(hKey != NULL);
		mKeyPath = hKey;
	}

	RegOperator::RegOperator(HKEY hKey, wstring szSubKey)
	{
//		ASSERT(hKey != NULL && !szSubKey.empty());
		mKeyPath = hKey;
		mSubKey = szSubKey;
	}

	RegOperator::~RegOperator()
	{
		RegCloseKey(mKeyPath);
		mKeyPath = 0;
	}

	RegOperator * RegOperator::CreateKey(HKEY hBaseKey, wstring szSubKey)
	{
//		ASSERT(hBaseKey != NULL && !szSubKey.empty());

		HKEY hKey;

		if (RegCreateKeyEx(hBaseKey, szSubKey.c_str(), 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, NULL) != ERROR_SUCCESS)
		{
			return NULL;
		}

		return new RegOperator(hKey);
	}

	RegOperator * RegOperator::OpenKey(HKEY hBaseKey, wstring szSubKey)
	{
//		ASSERT(hBaseKey != NULL && !szSubKey.empty());

		HKEY hKey;

		if (RegOpenKeyEx(hBaseKey, szSubKey.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS)
		{
			return NULL;
		}

		return new RegOperator(hKey);
	}

	RegOperator * RegOperator::OpenKey()
	{
//		ASSERT(mKeyPath != NULL && !mSubKey.empty());

		HKEY hKey;

		if (RegOpenKeyEx(mKeyPath, mSubKey.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS)
		{
			return NULL;
		}

		return new RegOperator(hKey);
	}

	BOOL RegOperator::CloseKey()
	{
		RegCloseKey(mKeyPath);
		return TRUE;
	}

	BOOL RegOperator::GetValue(wstring szName, wstring & szResult) const
	{
		DWORD dwType;
		DWORD dwSize;

		if (RegQueryValueEx(mKeyPath, szName.c_str(), NULL, &dwType, NULL, &dwSize) != ERROR_SUCCESS)
		{
			return FALSE;
		}

		if (dwType != REG_SZ && dwType != REG_EXPAND_SZ && dwType != REG_MULTI_SZ)
		{
			return FALSE;
		}

		LPWSTR szBuffer = (LPWSTR)malloc(dwSize);

		if (RegQueryValueEx(mKeyPath, szName.c_str(), NULL, &dwType, (LPBYTE)szBuffer, &dwSize) == ERROR_SUCCESS)
		{
			szResult = szBuffer;
		}

		free(szBuffer);

		return TRUE;
	}

	BOOL RegOperator::SetValue(wstring szName, wstring szValue)
	{
		DWORD dwType = szValue.find(L'\n') == wstring::npos ? REG_SZ : REG_MULTI_SZ;

		return RegSetValueEx(mKeyPath, szName.c_str(), 0, dwType, (LPBYTE)szValue.c_str(), sizeof(WCHAR) * (szValue.size() + 1)) == ERROR_SUCCESS;
	}

	BOOL RegOperator::GetValue(wstring szName, DWORD & dwResult) const
	{
		DWORD dwType;
		DWORD dwSize;

		dwSize = 4;

		return
			RegQueryValueEx(mKeyPath, szName.c_str(), NULL, &dwType, (LPBYTE)&dwResult, &dwSize) == ERROR_SUCCESS &&
			dwType == REG_DWORD;
	}

	BOOL RegOperator::SetValue(wstring szName, DWORD dwValue)
	{
		return RegSetValueEx(mKeyPath, szName.c_str(), 0, REG_DWORD, (LPBYTE)&dwValue, sizeof(DWORD)) == ERROR_SUCCESS;
	}

	BOOL RegOperator::GetValue(wstring szName, BOOL & fResult) const
	{
		DWORD dwTmp;

		if (GetValue(szName, dwTmp))
		{
			fResult = dwTmp != 0;
			return TRUE;
		}

		return FALSE;
	}

	BOOL RegOperator::SetValue(wstring szName, BOOL fResult)
	{
		return SetValue(szName, (DWORD)(fResult ? 1 : 0));
	}

	BOOL RegOperator::GetSubKeys(TStringVector & vKeys) const
	{
		DWORD dwLength = 0;

		LONG lStatus = RegQueryInfoKey(
			mKeyPath, NULL, NULL, NULL, NULL, &dwLength, NULL, NULL, NULL, NULL, NULL, NULL
		);

		if (lStatus != ERROR_SUCCESS)
		{
			return FALSE;
		}

		LPWSTR szBuffer = (LPWSTR)malloc((dwLength + 1) * sizeof(WCHAR));
		DWORD dwIndex = 0;
		BOOL fSuccess = FALSE;

		vKeys.clear();

		for (;;)
		{
			lStatus = RegEnumKey(mKeyPath, dwIndex, szBuffer, dwLength + 1);

			switch (lStatus)
			{
			case ERROR_SUCCESS:
				vKeys.push_back(szBuffer);
				break;

			case ERROR_NO_MORE_ITEMS:
				fSuccess = TRUE;

				// Fall through
			default:
				goto __end;
			}

			dwIndex++;
		}

	__end:
		free(szBuffer);

		return fSuccess;
	}

	BOOL RegOperator::DeleteValue(wstring szName)
	{
//  ASSERT(!szName.empty());

		return RegDeleteValue(mKeyPath, szName.c_str()) == ERROR_SUCCESS;
	}

	BOOL RegOperator::DeleteKey(wstring szName)
	{
//  ASSERT(!szName.empty());

		int lReturn = RegDeleteKey(mKeyPath, szName.c_str());
		return lReturn;
	}

	void RegOperator::setKeyPath(const HKEY& keyPath)
	{
		mKeyPath = keyPath;
	}
	const HKEY& RegOperator::getKeyPath() const
	{
		return mKeyPath;
	}

}

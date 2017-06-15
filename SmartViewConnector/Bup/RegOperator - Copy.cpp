/**
* Author: Rajib Chandra Das
* Topic: Windows Registry Key Processor(Create, Insert, Read, Update and Delete)
* Date: 8_July_2015
*/


//Create C++ Win32 Project in Visual Studio
//Project -> "project" Properties->Configuration Properties->C/C++->Advanced->Show Includes : YES(/ showIncludes)
//Project -> "project" Properties->Configuration Properties->General->Project Defaults->Use of MFC : Use MFC in a shared DLL

#include <iostream>
#include <afx.h>
#include "RegOperator.h"
using namespace std;

namespace RegOperate {
/*	RegOperator::RegOperator()
		: mRegHive(kDefaultRegHive)
		, mKeyPath(kDefaultKeyPath)
	{
	}

	RegOperator::RegOperator(string RegHive, string KeyPath)
	{
		ASSERT(mRegHive != NULL);
		mRegHive = RegHive;
		ASSERT(mKeyPath != NULL);
		mKeyPath = KeyPath;
	}
*/
/*	int main()
	{
		int iResult;
		CString KeyPath = _T("Software\\RCD_Technologies\\Rajib_Test");

		iResult = CreateRegistryKey(KeyPath);
		if (iResult<0)
		{
			cout << "CreateRegistryKey Operation Failed" << endl;
			return -1;
		}
		cout << "<-- CreateRegistryKey Operation Successfull -->" << endl;

		iResult = ReadRegistryKeyAttributes(KeyPath);
		if (iResult < 0)
		{
			cout << "ReadRegistryKeyAttributes operation Failed" << endl;
			return -1;
		}
		cout << "<--- ReadRegistryKeyAttribute Operation Successfull -->" << endl;



		iResult = UpdateRegistryKeyAttribute(KeyPath, _T("VersionID"), (DWORD)456);
		if (iResult < 0)
		{
			cout << "UpdateRegistryKeyAttribute operation Failed" << endl;
			return -1;
		}
		cout << "<--- UpdateRegistryKeyAttribute Operation Successfull -->" << endl;

//		iResult = DeleteRegistryKey(KeyPath);  //This Function is working fine, Skipped in Execution to keep the Registry Key
//		if (iResult < 0)
//		{
//		cout << "DeleteRegistryKey Operation Failed" << endl;
//		return -1;
//		}
//		cout << "DeleteRegistryKey Operation Successfull" << endl;

		getchar();

		return 0;
	}
*/
/*
*Opeing RegistryKey by given KeyPath
*Reading Attirbute: VersionID, Expired, Registered
*/
/*	int GetValue(string Attribute)
	{
		HKEY MyRegistryKey;
		if (RegOpenKeyEx(mRegHive, mKeyPath, 0, KEY_READ, &MyRegistryKey) != ERROR_SUCCESS)
		{
			cout << "   - Err: KeyOpen Failed" << endl;
			return -1;
		}


		DWORD type = REG_DWORD;
		DWORD cbData;
		unsigned long size = 1024;
		//		CString csVersionID;

		//		csVersionID = _T("VersionID");
		//		if (RegQueryValueEx(MyRegistryKey, csVersionID, NULL, &type, (LPBYTE)&cbData, &size) != ERROR_SUCCESS)
		if (RegQueryValueEx(MyRegistryKey, Attribute, NULL, &type, (LPBYTE)&cbData, &size) != ERROR_SUCCESS)
		{
			RegCloseKey(MyRegistryKey);
			cout << "   - Err: VersionID Key Attribute Reading Failed" << endl;
			return -1; //Error
		}
		else
		{
			cout << Attribute + " = " << cbData << endl;
		}

		RegCloseKey(MyRegistryKey);

		return 1; //Successfull
	}
*/
	/*
	*Opeing RegistryKey by given KeyPath
	*Update Attirbute by given Value and Key Name
	*/
/*	int UpdateRegistryKeyAttribute(string Attribute, DWORD value)
	{
		HKEY MyRegistryKey;
		if (RegOpenKeyEx(mRegHive, mKeyPath, 0, KEY_ALL_ACCESS, &MyRegistryKey) != ERROR_SUCCESS)
		{
			cout << "   - Err: KeyOpen Failed" << endl;
			return -1;
		}

		if (ERROR_SUCCESS != RegSetValueEx(MyRegistryKey, Attribute, 0, REG_DWORD, (const BYTE*)&value, sizeof(value)))
		{
			//m_pMessageBox->ShowMessageBox("ConstantKey Start Initialization Failed");
			cout << "   - Err: Attribute Initialization Failed" << endl;
			return -1; //Error
		}

		RegCloseKey(MyRegistryKey);

		cout << "   - Err: Attribute Updated with value " << value << endl;
		return 1; //Successfull

	}
*/
	/*
	*Creating New Registry Key
	*Creating Attirbute: VersionID, Expired, Registered
	*/
/*	int CreateRegistryKey(string Attribute, DWORD dValue)
	{
		HKEY MyRegistryKey;
//		DWORD d_VersionId, d_isExpired, d_isRegistered;

		if (ERROR_SUCCESS != RegOpenKeyEx(mRegHive, mKeyPath, 0, KEY_ALL_ACCESS, &MyRegistryKey))
		{
			// Registry key by specified name not found.... so new Registry key has to be created

			DWORD dwDisposition = 0;
			if (ERROR_SUCCESS != RegCreateKeyEx(mRegHive, mKeyPath, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &MyRegistryKey, &dwDisposition))
			{
				cout << "   - Err: MyRegistryKey Creation Failed" << endl;
				return -1; //Error
			}
			else
			{
//				d_VersionId = 20150606; //Just a Random Value considred as version ID
//				if (ERROR_SUCCESS != RegSetValueEx(MyRegistryKey, TEXT("VersionID"), 0, REG_DWORD, (const BYTE*)&d_VersionId, sizeof(d_VersionId)))
				if (ERROR_SUCCESS != RegSetValueEx(MyRegistryKey, TEXT(Attribute), 0, REG_DWORD, (const BYTE*)&dValue, sizeof(dValue)))
					{
					//m_pMessageBox->ShowMessageBox("ConstantKey Start Initialization Failed");
					cout << "   - Err: VersionID Attribute Initialization Faield" << endl;
					return -1; //Error
				}

			}

		}

		cout << "MyRegKey Created Successfully" << endl;
		cout << "Default Key Attributes are-- > VersionID, Expired and Registered" << endl;
		RegCloseKey(MyRegistryKey);
		return 1; //Successfull

	}

	int DeleteRegistryKey()
	{
		int lReturn = RegDeleteKey(mRegHive, mKeyPath);
		return lReturn;
	}

	void RegOperator::setRegHive(const string& regHive)
	{
		mRegHive = regHive;
	}
	const string& RegOperator::getRegHive() const
	{
		return mRegHive;
	}

	void RegOperator::setKeyPath(const string& keyPath)
	{
		mKeyPath = keyPath;
	}
	const string& RegOperator::getKeyPath() const
	{
		return mKeyPath;
	}

}
*/
/*******************************************************************************/

#include "stdafx.h"
#include "include.h"

	RegOperator::RegOperator()
		: mKeyPath(kDefaultKeyPath)
	{
	}

	RegOperator::RegOperator(HKEY hKey)
	{
		ASSERT(hKey != NULL);
		mKeyPath = hKey;
	}

	RegOperator::~RegOperator()
	{
		RegCloseKey(mKeyPath);
	}

	RegOperator * RegOperator::CreateKey(HKEY hBaseKey, wstring szSubKey)
	{
		ASSERT(hBaseKey != NULL && !szSubKey.empty());

		HKEY hKey;

		if (RegCreateKeyEx(hBaseKey, szSubKey.c_str(), 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, NULL) != ERROR_SUCCESS)
		{
			return NULL;
		}

		return new RegOperator(hKey);
	}

	RegOperator * RegOperator::OpenKey(HKEY hBaseKey, wstring szSubKey)
	{
		ASSERT(hBaseKey != NULL && !szSubKey.empty());

		HKEY hKey;

		if (RegOpenKeyEx(hBaseKey, szSubKey.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS)
		{
			return NULL;
		}

		return new RegOperator(hKey);
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
		ASSERT(!szName.empty());

		return RegDeleteValue(mKeyPath, szName.c_str()) == ERROR_SUCCESS;
	}

	BOOL RegOperator::DeleteKey(wstring szName)
	{
		ASSERT(!szName.empty());

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

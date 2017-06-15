// RegOperator.h : Defines Registry operation class.
//
#pragma once
#include <iostream>
//#include <afx.h>

namespace RegOperate {
//	Const HKEY_CLASSES_ROOT = &H80000000
//	Const HKEY_CURRENT_USER = &H80000001
//	Const HKEY_LOCAL_MACHINE = &H80000002
//	Const HKEY_USERS = &H80000003
//	Const HKEY_CURRENT_CONFIG = &H80000005

	class RegOperator
	{
		const HKEY kDefaultKeyPath = HKEY_CURRENT_USER;
		const wstring kSubKey = _T("Software\\III");
	public:
		RegOperator();
		RegOperator(HKEY hBaseKey);
		RegOperator(HKEY hBaseKey, wstring szSubKey);
		RegOperator * CreateKey(HKEY hBaseKey, wstring szSubKey);
		RegOperator * OpenKey(HKEY hBaseKey, wstring szSubKey);
		BOOL GetValue(wstring szName, wstring & szResult) const;
		BOOL SetValue(wstring szName, wstring szValue);
		BOOL GetValue(wstring szName, DWORD & dwResult) const;
		BOOL SetValue(wstring szName, DWORD dwValue);
		BOOL GetValue(wstring szName, BOOL & fResult) const;
		BOOL SetValue(wstring szName, BOOL fResult);
//		BOOL GetSubKeys(TStringVector & vKeys) const;
		BOOL DeleteValue(wstring szName);
		BOOL DeleteKey(wstring szName);

		// Getters and setters
		void setKeyPath(const HKEY& sKeyPath);
		const HKEY& getKeyPath() const;

		void setSubKey(const wstring& sSubKey);
		const wstring& getSubKey() const;

	private:
		HKEY mKeyPath;
		wstring mSubKey;
	};
}


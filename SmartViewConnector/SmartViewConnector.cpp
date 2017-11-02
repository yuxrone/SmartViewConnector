#include "stdafx.h"
#include "SmartViewConnector.h"

using namespace std;
using namespace RegOpr;

/*bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}
*/

//std::wstring StoWs(const std::string& s)
//{
//	int len;
//	int slength = (int)s.length() + 1;
//	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
//	wchar_t* buf = new wchar_t[len];
//	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
//	std::wstring r(buf);
//	delete[] buf;
//	return r;
//}

int main(int argc, char** argv)
{
	PTSTR lpszSVConnVerKey = L"2.2.0";
	HKEY hHive = HKEY_CURRENT_USER;
	HKEY hKey;
	CRegKey ror;
	unsigned short isMQ = 0;
	unsigned short isSilent;
	PTSTR szSubKeyPath = _T("Software\\Hyperion Solutions\\HyperionSmartView");
	PTSTR szMainKeyPath = _T("Software\\Hyperion Solutions");
	PTSTR szPerfIEKey = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings");
	PTSTR szConnectionsKey = _T("Connections");
	PTSTR szSVConnVerKey = _T("Connector");
	PTSTR szLoginKey = _T("Login");
	PTSTR szOptionsKey = _T("Options");
	PTSTR szPreferencesKey = _T("Preferences");

	PTSTR szHFMFY = _T("IIIHFMFY");
	PTSTR szAPP = _T("IIIAPP");
	PTSTR szPLNFY = _T("IIIPLNFY");
	PTSTR szMQIIFRS = _T("MQIIFRS");
	PTSTR szCellStyles = _T("CellStyles");
	PTSTR szCAOptionsXML = _T("CAOptionsXML");

	PTSTR szOfficeCommonKeyPath = _T("Software\\Microsoft\\Office\\16.0\\Common"); 
	PTSTR szToolbarsKey = _T("Toolbars");
	PTSTR szGraphicsKey = _T("Graphics");
	// To improve the user experience, you may enable the DWORD value DisableWindowTransitionsOnAddinTaskPanes for Office 2013 and 2016.
	PTSTR szDisableWTOATP = _T("DisableWindowTransitionsOnAddinTaskPanes");
	//To further improve the user experience, you may disable Office Animations for Office2013 and 2016 by adding a key and DWORD value to the Windows Registry.
	PTSTR szDisableAnimat = _T("DisableAnimations");
	//In some cases, third-party software that automates Excel processes, such as exporting	to Excel, may cause issues with Excel and a conflict with Oracle Smart View for Office.
	PTSTR szDisableAutoma = _T("DisableInAutomation");

	// HTTP session timeouts can occur, for example, when working with large queries that
	// take a long time to run, or when you're experiencing slower internet connections.
	// To avoid HTTP session timeouts, you may add the following Windows Registry
	// DWORDS to the Internet Settings key :
	PTSTR szRcvTimeOut = _T("ReceiveTimeout");
	PTSTR szKeepAlive = _T("KeepAliveTimeout");
	PTSTR szSrvInfo = _T("ServerInfoTimeout");

//	auto t = time(nullptr);
//	auto tm = *localtime_s(&t);
//	std::ostringstream oss;
//	oss << std::put_time(&tm, "%m-%d-%Y %H-%M-%S");
//	auto str = oss.str();
//	wstring stemp = StoWs(str);
//	PTSTR result = stemp.c_str();

//	LPTSTR lpszDateTime = str.c_str(); // pointer to system time string

	//	char mbstr[100]; 
//	strftime(mbstr, 100, "%d/%m/%Y %T", std::localtime(&t));
/*	

	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", timeinfo);
	std::string str(buffer);
*/				

	LPTSTR lpszUserID; // pointer to system information string
	DWORD cchBuff = UNLEN; // size of user name
	TCHAR tchBuffer[UNLEN + 1]; // buffer for expanded string

//	wchar_t *dwCellStyles;
//	dwCellStyles = (wchar_t *)malloc(10000);

//	TCHAR tchOptions[4000] = _T("<root version = '0'><option key = 'ziExpand' value = '0' / ><option key = 'ziAncestor' value = '0' / ><option key = 'indentLevel' value = '1' / ><option key = 'supRowsNoDataMissing' value = '0' / ><option key = 'supRowsZeros' value = '0' / ><option key = 'supRowsNoAccess' value = '0' / ><option key = 'supRowsInvalid' value = '0' / ><option key = 'supRepeatedMembers' value = '0' / ><option key = 'supUnderScores' value = '0' / ><option key = 'mbrRetIncludeSelection' value = '1' / ><option key = 'mbrRetWithinSelectedGroup' value = '0' / ><option key = 'mbrRetRemoveUnselectedGroups' value = '0' / ><option key = 'modeDataLessNav' value = '0' / ><option key = 'useDoubleClickForAdhoc' value = '1' / ><option key = 'bUndoEnable' value = '1' / ><option key = 'iUndoBufSize' value = '10' / ><option key = 'strRepMissinglabel' value = ""#NumericZero"" / ><option key = 'strRepNoAccesslabel' value = '#No Access' / ><option key = 'strRepInvalidlabel' value = '#Invalid' / ><option key = 'cellStatus' value = '0' / ><option key = 'messageDisplay' value = '2' / ><option key = 'strScale' value = 'Default' / ><option key = 'strDecPlaces' value = 'Default' / ><option key = 'bAdhocUseStyles' value = '0' / ><option key = 'bRetainNumericFormatting' value = '0' / ><option key = 'm_bUseExcelColorPalette' value = '0' / ><option key = 'm_bPreserveFormulasOnPOVChange' value = '0' / ><option key = 'bManualCalc' value = '0' / ><option key = 'bUseThousandsSep' value = '0' / ><option key = 'bUseListStripes' value = '0' / ><option key = 'bClearLogMessage' value = '0' / ><option key = 'bRouteLogMessages' value = '0' / ><option key = 'bRefreshFunctionsOnly' value = '0' / ><option key = 'strMessageLogFile' value = 'C:\\Users\\");
//	PTSTR szCAOptions2 = _T("\\AppData\\Roaming\\Oracle\\SmartView\\SmartViewLogs.log'/><option key='clrLightStripe' value='15723237'/><option key='clrDarkStripe' value='15328221'/><option key='memberDisplay' value='0'/><option key='memberDisplayEssbase' value='0'/><option key='bShowAliasForPlanningMbrSel' value='0'/><option key='bEnableFormatStr' value='1'/><option key='iSVPanelActiveDialog' value='10'/><option key='iReportDesignerSplitState}' value='13'/><option key='szPluginUIProgID' value=''/><option key='bDisplayHomePanelOnStartup' value='1'/><option key='bExpandLoginDialog' value='1'/><option key='iSVPanelDockPosition' value='2'/><option key='strBIPlusRepositoryURL' value='http://&lt;host&gt;/raframework/services/BiPlus'/><option key='strBIPlusRepositoryFolder' value='Crystal Ball'/><option key='bCommentDlgEnable' value='0'/><option key='bsubmitZero' value='0'/><option key='bMRUEnable' value='1'/><option key='iMRUBufSize' value='9'/><option key='bHandleCellDependency' value='0'/><option key='bIgnoreFormulaAndComment' value='0'/><option key='bEnableProfiling' value='0'/><option key='bDefaultLanguage' value='0'/><option key='strLanguageCode' value='1033'/><option key='strMissinglabelList' value=''/><option key='strNoAccesslabelList' value=''/><option key='strInvalidlabelList' value=''/><option key='bContextSensitive' value='1'/><option key='strDisableContextSenseFor' value=''/><option key='bDisplaySVMenuOnly' value='0'/><option key='bRetainRibbonContext' value='1'/><option key='bDisplayDrillThroughTooltip' value='0'/><option key='bDisplayInvalidData' value='0'/><option key='supColsNoDataMissing' value='0'/><option key='supColsZeros' value='0'/><option key='supColsNoAccess' value='0'/><option key='supColsInvalid' value='0'/><option key='supBlocksMissing' value='1'/><option key='bAdjustColumns' value='0'/><option key='bFormulaFill' value='0'/><option key='bShowPovInNotesDlg' value='1'/><option key='bShowPovInAttachmentsDlg' value='1'/><option key='bShowPovInHistoryDlg' value='1'/><option key='bMoveFormats' value='0'/><option key='bShowProgressDlg' value='0'/><option key='iProgressDelayTime' value='5'/></root>");

	TCHAR tchOptions[4500] = _T("<root version=\"0\"><option key=\"ziExpand\" value=\"0\"/><option key=\"ziAncestor\" value=\"0\"/><option key=\"indentLevel\" value=\"1\"/><option key=\"supRowsNoDataMissing\" value=\"0\"/><option key=\"supRowsZeros\" value=\"0\"/><option key=\"supRowsNoAccess\" value=\"0\"/><option key=\"supRowsInvalid\" value=\"0\"/><option key=\"supRepeatedMembers\" value=\"0\"/><option key=\"supUnderScores\" value=\"0\"/><option key=\"mbrRetIncludeSelection\" value=\"1\"/><option key=\"mbrRetWithinSelectedGroup\" value=\"0\"/><option key=\"mbrRetRemoveUnselectedGroups\" value=\"0\"/><option key=\"modeDataLessNav\" value=\"0\"/><option key=\"useDoubleClickForAdhoc\" value=\"1\"/><option key=\"bUndoEnable\" value=\"0\"/><option key=\"iUndoBufSize\" value=\"1\"/><option key=\"strRepMissinglabel\" value=\"#NumericZero\"/><option key=\"strRepNoAccesslabel\" value=\"#No Access\"/><option key=\"strRepInvalidlabel\" value=\"#Invalid\"/><option key=\"cellStatus\" value=\"0\"/><option key=\"messageDisplay\" value=\"2\"/><option key=\"strScale\" value=\"Default\"/><option key=\"strDecPlaces\" value=\"Default\"/><option key=\"bAdhocUseStyles\" value=\"0\"/><option key=\"bRetainNumericFormatting\" value=\"0\"/><option key=\"m_bUseExcelColorPalette\" value=\"0\"/><option key=\"m_bPreserveFormulasOnPOVChange\" value=\"0\"/><option key=\"bManualCalc\" value=\"0\"/><option key=\"bUseThousandsSep\" value=\"1\"/><option key=\"bUseListStripes\" value=\"0\"/><option key=\"bClearLogMessage\" value=\"0\"/><option key=\"bRouteLogMessages\" value=\"0\"/><option key=\"bRefreshFunctionsOnly\" value=\"0\"/><option key=\"strMessageLogFile\" value=\"C:\\Users\\");
	//	PTSTR szCAOptions2 = _T("\\AppData\\Roaming\\Oracle\\SmartView\\SmartViewLogs.log\"/><option key=\"clrLightStripe\" value=\"15723237\"/><option key=\"clrDarkStripe\" value=\"15328221\"/><option key=\"memberDisplay\" value=\"0\"/><option key=\"memberDisplayEssbase\" value=\"0\"/><option key=\"bShowAliasForPlanningMbrSel\" value=\"0\"/><option key=\"bEnableFormatStr\" value=\"1\"/><option key=\"iSVPanelActiveDialog\" value=\"10\"/><option key=\"iReportDesignerSplitState}\" value=\"13\"/><option key=\"szPluginUIProgID\" value=\"\"/><option key=\"bDisplayHomePanelOnStartup\" value=\"1\"/><option key=\"bExpandLoginDialog\" value=\"1\"/><option key=\"iSVPanelDockPosition\" value=\"2\"/><option key=\"strBIPlusRepositoryURL\" value=\"http://&lt;host&gt;/raframework/services/BiPlus\"/><option key=\"strBIPlusRepositoryFolder\" value=\"Crystal Ball\"/><option key=\"bCommentDlgEnable\" value=\"0\"/><option key=\"bsubmitZero\" value=\"0\"/><option key=\"bMRUEnable\" value=\"1\"/><option key=\"iMRUBufSize\" value=\"9\"/><option key=\"bHandleCellDependency\" value=\"0\"/><option key=\"bIgnoreFormulaAndComment\" value=\"0\"/><option key=\"bEnableProfiling\" value=\"0\"/><option key=\"bDefaultLanguage\" value=\"0\"/><option key=\"strLanguageCode\" value=\"1033\"/><option key=\"strMissinglabelList\" value=\"\"/><option key=\"strNoAccesslabelList\" value=\"\"/><option key=\"strInvalidlabelList\" value=\"\"/><option key=\"bContextSensitive\" value=\"1\"/><option key=\"strDisableContextSenseFor\" value=\"\"/><option key=\"bDisplaySVMenuOnly\" value=\"0\"/><option key=\"bRetainRibbonContext\" value=\"1\"/><option key=\"bDisplayDrillThroughTooltip\" value=\"0\"/><option key=\"bDisplayInvalidData\" value=\"0\"/><option key=\"supColsNoDataMissing\" value=\"1\"/><option key=\"supColsZeros\" value=\"1\"/><option key=\"supColsNoAccess\" value=\"1\"/><option key=\"supColsInvalid\" value=\"0\"/><option key=\"supBlocksMissing\" value=\"1\"/><option key=\"bAdjustColumns\" value=\"1\"/><option key=\"bFormulaFill\" value=\"0\"/><option key=\"bShowPovInNotesDlg\" value=\"1\"/><option key=\"bShowPovInAttachmentsDlg\" value=\"1\"/><option key=\"bShowPovInHistoryDlg\" value=\"1\"/><option key=\"bMoveFormats\" value=\"0\"/><option key=\"bShowProgressDlg\" value=\"0\"/><option key=\"iProgressDelayTime\" value=\"5\"/></root>");
	PTSTR szCAOptions2 = _T("\\AppData\\Roaming\\Oracle\\SmartView\\SmartViewLogs.log\"/><option key=\"clrLightStripe\" value=\"15723237\"/><option key=\"clrDarkStripe\" value=\"15328221\"/><option key=\"memberDisplay\" value=\"0\"/><option key=\"memberDisplayEssbase\" value=\"0\"/><option key=\"bShowAliasForPlanningMbrSel\" value=\"0\"/><option key=\"bEnableFormatStr\" value=\"1\"/><option key=\"iSVPanelActiveDialog\" value=\"9\"/><option key=\"iReportDesignerSplitState}\" value=\"11\"/><option key=\"iSVPanelFlyoutWidth}\" value=\"300\"/><option key=\"bSVPanelMinimized}\" value=\"0\"/><option key=\"szPluginUIProgID\" value=\"\"/><option key=\"bDisplayHomePanelOnStartup\" value=\"1\"/><option key=\"bExpandLoginDialog\" value=\"1\"/><option key=\"iSVPanelDockPosition\" value=\"2\"/><option key=\"strBIPlusRepositoryURL\" value=\"http://&lt;host&gt;/raframework/services/BiPlus\"/><option key=\"strBIPlusRepositoryFolder\" value=\"Crystal Ball\"/><option key=\"bCommentDlgEnable\" value=\"0\"/><option key=\"bsubmitZero\" value=\"1\"/><option key=\"bMRUEnable\" value=\"1\"/><option key=\"iMRUBufSize\" value=\"9\"/><option key=\"bHandleCellDependency\" value=\"0\"/><option key=\"bIgnoreFormulaAndComment\" value=\"0\"/><option key=\"bPreserveEssbaseComment\" value=\"1\"/><option key=\"bMoveEssbaseMemberFormulaOnZoom\" value=\"0\"/><option key=\"bEnableProfiling\" value=\"0\"/><option key=\"bEnableProfileTab\" value=\"0\"/><option key=\"bDefaultLanguage\" value=\"0\"/><option key=\"strLanguageCode\" value=\"1033\"/><option key=\"strMissinglabelList\" value=\"\"/><option key=\"strNoAccesslabelList\" value=\"\"/><option key=\"strInvalidlabelList\" value=\"\"/><option key=\"bContextSensitive\" value=\"1\"/><option key=\"strDisableContextSenseFor\" value=\"\"/><option key=\"bDisplaySVMenuOnly\" value=\"0\"/><option key=\"bRetainRibbonContext\" value=\"1\"/><option key=\"bDisplayDrillThroughTooltip\" value=\"0\"/><option key=\"bDisplayInvalidData\" value=\"0\"/><option key=\"supColsNoDataMissing\" value=\"0\"/><option key=\"supColsZeros\" value=\"0\"/><option key=\"supColsNoAccess\" value=\"0\"/><option key=\"supColsInvalid\" value=\"0\"/><option key=\"supBlocksMissing\" value=\"1\"/><option key=\"bAdjustColumns\" value=\"0\"/><option key=\"bWarnAdjustColumn\" value=\"0\"/><option key=\"bFormulaFill\" value=\"0\"/><option key=\"bShowPovInNotesDlg\" value=\"1\"/><option key=\"bShowPovInAttachmentsDlg\" value=\"1\"/><option key=\"bShowPovInHistoryDlg\" value=\"1\"/><option key=\"bMoveFormats\" value=\"0\"/><option key=\"bShowProgressDlg\" value=\"0\"/><option key=\"iProgressDelayTime\" value=\"5\"/><option key=\"iApplyFormattingChoice\" value=\"2\"/><option key=\"bRepeatMembersInForm\" value=\"0\"/><option key=\"bRefreshLinkedWorkbook\" value=\"0\"/><option key=\"bSortDSPanelItems\" value=\"0\"/></root>");


	TCHAR tchProfilePath[UNLEN] = _T("C:\\Users\\");
	PTSTR szSmartViewPath1 = _T("\\AppData\\Roaming\\Oracle");
	PTSTR szSmartViewPath2 = _T("\\SmartView");
	PTSTR szPropertyXML = _T("\\properties.xml");
	ofstream my_output_file; // an output file stream object

	isSilent = 0;
	if (argc > 1)
	{
		isSilent = 1;
		isMQ = *argv[1] - '0';
	}
	else
	{
		isSilent = 0;
		//		isMQ = 1;
	}

	HICON	hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	HWND	hwnd = GetConsoleWindow();
	SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	if (isSilent)
	{
		ShowWindow(hwnd, SW_HIDE);
	}

	// screen out version info
	int i = 0;
	cout << "=======================================================================" << endl;
	cout << "                           SmartView Connector                           " << endl;
	wcout << "                               Ver " << lpszSVConnVerKey << endl;
	cout << "                Copyright (C) 2017. All Rights Reserved." << endl;
	cout << "                       ITOCHU International Inc." << endl;
	cout << "=======================================================================" << endl;
	cout << endl;

	// start 
	cout << "PLEASE DO NOT CLOST THIS WINDOW DURING THE INSTALLATION PROCESS!" << endl;
	cout << endl;

	if (!isSilent)
	{
		cout << ">  Connector Configuration Option:" << endl;
		cout << ">  " << endl;
		cout << ">   1. III and Subsidiaries (Exc. Multiquip Inc.)" << endl;
		cout << ">  " << endl;
		cout << ">   2. Multiquip Inc." << endl;
		cout << ">  " << endl;
		cout << ">  Please enter number for corresponding connector:" << endl;
		cout << ">  " << endl;
		cout << ">  :";
		cin >> isMQ;

		while (isMQ != 1 && isMQ != 2 || !cin)
		{
			cout << ">  Your input is NOT valid. Please enter 1 or 2." << endl;
			cout << ">  :";
			if (!cin) // or if(cin.fail())
			{
				//				cin.reset();
								// user didn't input a number
				cin.clear(); // reset failbit
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //skip bad input
																	 // next, request user reinput
			}
			cin >> isMQ;
		}
	}

	isMQ--;
	if (!isMQ) {
		cout << ">  " << endl;
		cout << ">  You entered '1', connector for [III and Subsidiaries] will be installed." << endl;
	}
	else {
		cout << ">  " << endl;
		cout << ">  You entered '2', connector for [Multiquip] will be installed." << endl;
	}
	cout << endl;

		
	// Get and display the user name.
	lpszUserID = tchBuffer;
	GetUserName(lpszUserID, &cchBuff);

	cout << "   SmartView Connector installation started... " << endl;
	cout << endl;

	cout << "     1. Preparing Connector Contents";
	while (i < 6)
	{
		cout << " .";
		this_thread::sleep_for(chrono::milliseconds(300));
		i++;
	}
	i = 0;
	cout << endl;
	cout << endl;

	// Prepair CAOptions value
	lstrcat(tchOptions, lpszUserID);
	lstrcat(tchOptions, szCAOptions2);
	//Prepair Properties.XML file full path
	lstrcat(tchProfilePath, lpszUserID);
	lstrcat(tchProfilePath, szSmartViewPath1);

	ror.DeleteKey(hHive, szSubKeyPath);

	cout << "     2. Importing SmartView URLs and Initial Parameters";
	while (i < 6)
	{
		cout << " .";
		this_thread::sleep_for(chrono::milliseconds(300));
		i++;
	}
	i = 0;
	cout << endl;
	cout << endl;

	ror.Create(hHive, szMainKeyPath);
	ror.Create(hHive, szSubKeyPath);

	hKey = ror.getRootKey();
	ror.Create(hKey, szConnectionsKey);
	ror.setBinary(szHFMFY, dwIIIHFMFY, sizeof(dwIIIHFMFY));
	ror.setBinary(szAPP, dwIIIAPP, sizeof(dwIIIAPP));
	if (!isMQ)
		ror.setBinary(szPLNFY, dwIIIPLNFY, sizeof(dwIIIPLNFY));
	else
		ror.setBinary(szMQIIFRS, dwMQIIFRS, sizeof(dwMQIIFRS));

	ror.Create(hKey, szOptionsKey);
	ror.setBinary(szCellStyles, dwCellStyles, sizeof(dwCellStyles));
	ror.setString(szCAOptionsXML, tchOptions);
	// Performance Tunning
	ror.setDWORD(szDisableAutoma, m_dwDisableAutoma);
	
	BYTE data1[] = { 0x01 };
	BYTE data2[] = { 0x02 };

	ror.Create(hKey, szPreferencesKey);
	ror.setBinary(_T("UseStorageCompression"), data1, sizeof(data1));
	ror.setBinary(_T("SelectedOptionTab"), data2, sizeof(data2));
	ror.setBinary(_T("IgnoreShapes"), data1, sizeof(data1));

	/*	char* user = getenv("USER");
	//	wchar_t wUser[10];

	wchar_t* wUser = new wchar_t[10];
	MultiByteToWideChar(CP_ACP, 0, user, -1, wUser, 10);


	//	mbstowcs(wUser, user, strlen(user) + 1);//Plus null
	//	LPWSTR ptr = wtext;


	char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName(username, &username_len);
	*/
	ror.Create(hKey, szLoginKey);
	ror.setString(_T("LastUser"), lpszUserID);

	ror.Create(hKey, szSVConnVerKey);
	ror.setString(_T("Version"), lpszSVConnVerKey);

	//Non C++11 solution: With the <ctime> header, you could use strftime. Make sure your buffer is large enough, you wouldn't want to overrun it and wreak havoc later.
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	strftime(buffer, sizeof(buffer), "%Y/%m/%d %I:%M:%S %p", &timeinfo);
	std::string strDate(buffer);	
	
	// Assumes std::string is encoded in the current Windows ANSI codepage
	int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, strDate.c_str(), strDate.size(), NULL, 0);

	if (bufferlen == 0)
	{
		// Something went wrong. Perhaps, check GetLastError() and log.
		return 3;
	}

	// Allocate new LPWSTR - must deallocate it later
	LPWSTR widestr = new WCHAR[bufferlen + 1];

	::MultiByteToWideChar(CP_ACP, 0, strDate.c_str(), strDate.size(), widestr, bufferlen);

	// Ensure wide string is null terminated
	widestr[bufferlen] = 0;

	// Do something with widestr - write to registry
	ror.setString(_T("Installed Time"), widestr);

	delete[] widestr;

//	std::ostringstream oss;
//	oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
//	auto str = oss.str();
		
	// Performance Tunning
	ror.Open(hHive, szPerfIEKey);
	hKey = ror.getRootKey();
	ror.setDWORD(szRcvTimeOut, m_dwRcvTimeOut);
	ror.setDWORD(szKeepAlive, m_dwKeepAlive);
	ror.setDWORD(szSrvInfo, m_dwSrvInfo);
	
	ror.Create(hHive, szOfficeCommonKeyPath);
	hKey = ror.getRootKey();
	ror.Create(hKey, szToolbarsKey);
	ror.setDWORD(szDisableWTOATP, m_dwDisableWTOATP);
	
	ror.Open(hHive, szOfficeCommonKeyPath);
	hKey = ror.getRootKey();
	ror.Create(hKey, szGraphicsKey);
	ror.setDWORD(szDisableAnimat, m_dwDisableAnimat);

	ror.Close();

	cout << "     3. Generating Configuration XML File";
	while (i < 8)
	{
		cout << " .";
		this_thread::sleep_for(chrono::milliseconds(300));
		i++;
	}
	i = 0;
	cout << endl;
	cout << endl;

/*	while (i < 10)
	{
		cout << ". ";
		this_thread::sleep_for(chrono::milliseconds(300));
		i++;
	}
	cout << endl;
	cout << endl;
*/
/*	lstrcat(tchProfilePath, lpszUserID);
	lstrcat(tchProfilePath, szSmartViewPath1);
	
	//Converty wstring to string.
	//#include <locale>
	//#include <codecvt>
	//#include <string>
	wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
	string sProfilePath = converter.to_bytes(tchProfilePath);

	if (!dirExists(sProfilePath))
	{
	cout << "***** ERROR: SMARTVIEW INSTANCE IS NOT DETECTED." << endl;
	cout << "***** PLEASE INSTALL SMARTVIEW FIRST AND THEN RUN THIS CONNECTOR." << endl;
	cout << endl;

	cout << "Press Any Key to Quit . . ." << endl;
	cout << endl;
	getchar();

	return 1;
	}
	*/
	if (CreateDirectory(tchProfilePath, NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{
		lstrcat(tchProfilePath, szSmartViewPath2);
		if (CreateDirectory(tchProfilePath, NULL) ||
			ERROR_ALREADY_EXISTS == GetLastError())
		{
			// Generate XML file.
			lstrcat(tchProfilePath, szPropertyXML);
			my_output_file.open(tchProfilePath);
			if (my_output_file.is_open()) {
				my_output_file << "<cfg><provider><overrideWorkspaceUrl>http://iiihypprdweb.itochu.com:19000/workspace/SmartViewProviders</overrideWorkspaceUrl>" << endl;
				my_output_file << "<previousURLList>http://iiihypprdweb.itochu.com:19000/workspace/SmartViewProviders</previousURLList><overrideUrl></overrideUrl></provider></cfg>" << endl;
			}
			my_output_file.close();
		}
		else
		{
			cout << "***** ERROR: CREATE DIRECTORY FAILURE #1." << endl;
			cout << "***** PLEASE TRY AGAIN OR CONTACT IS DEPT (212-818-8222)." << endl;
			cout << endl;

			cout << "Press Any Key to Quit . . ." << endl;
			cout << endl;
			if (!isSilent)
			{
				system("pause");
			}
//			getchar();
			return 1;
		}
	}
	else
	{
		// Failed to create directory.
		cout << "***** ERROR: CREATE DIRECTORY FAILURE #2." << endl;
		cout << "***** PLEASE TRY AGAIN OR CONTACT IS DEPT (212-818-8222)." << endl;
		cout << endl;

		cout << "Press Any Key to Quit . . ." << endl;
		cout << endl;
		if (!isSilent)
		{
			system("pause");
		}
		return 2;
	}

	cout << "   SmartView Connector Has been Installed Successfully. " << endl;
	cout << endl;

//	cout << endl;
//	cout << "Press Any Key to close this window. . ." << endl;
//	cout << endl;
//	getchar();
	if (!isSilent)
	{
		system("pause");
	}
    return 0;
}
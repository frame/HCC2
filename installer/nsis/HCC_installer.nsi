
/*
 *	Horizons Crafting Calculator 2 - NSIS Script
 *  Copyright 2004-09 HCC Development Team
 *
 *	http://hcc.reclamation.dk/
 *
 *
 *  Initially created on 2005-10-24 08:18
 *
 *	Tested with NSIS Installer 2.10, 2.11, 2.12, 2.14, 2.15, 2.30, 2.36, 2.40 and 2.44
*/



!define HCC_Version "2.29" ; ${HCC_Version}
!define HCC_Revision "2008-10-31" ; ${HCC_Revision}
!define HCC_Name "HCC2" ; ${HCC_Name}
!define HCC_Title "Horizons Crafting Calculator" ; ${HCC_Title}
!define HCC_Installer_Version "1.20" ; ${HCC_Installer_Version}



/*
 *
 * You shouldn't need to edit anything below this line, unless the filestructure changes
 * or you need to edit some textual strings
 *
*/



/*
 * Hello World
*/

;SetCompressor /SOLID /FINAL lzma ; compiler settings

Name "${HCC_Title} - v${HCC_Version}" ; installation title
OutFile "..\..\HCC_v${HCC_Version}.exe" ; installer filename
InstallDir $PROGRAMFILES\${HCC_Name} ; default installation directory
InstallDirRegKey HKLM "Software\${HCC_Name}" "Install_Dir" ; default installation regkey



!include "MUI.nsh"
!include "WordFunc.nsh"
!define MUI_ABORTWARNING
!define MUI_COMPONENTSPAGE_SMALLDESC
!define MUI_WELCOMEFINISHPAGE_BITMAP "Sidebar.bmp"



/*
 *	page flow + language strings
*/

; page - welcome
!insertmacro VersionCompare
!insertmacro MUI_PAGE_WELCOME

; page - readme
!define MUI_PAGE_HEADER_TEXT "Welcome to ${HCC_Title}"
!define MUI_PAGE_HEADER_SUBTEXT "Client v${HCC_Version} - Database ${HCC_Revision}"
!define MUI_LICENSEPAGE_TEXT_TITLE " "
!define MUI_LICENSEPAGE_TEXT_TOP "ReadMe.txt"
!define MUI_LICENSEPAGE_TEXT_BOTTOM "Click Next to review the License Agreement." 
!define MUI_LICENSEPAGE_BUTTON "&Next >"
!insertmacro MUI_PAGE_LICENSE "..\ReadMe.txt"

; page - license
!define MUI_LICENSEPAGE_CHECKBOX
!insertmacro MUI_PAGE_LICENSE "..\License.txt"

; page - components
!insertmacro MUI_PAGE_COMPONENTS

; page - section_layout
Page custom section_layout

; page - directory
!insertmacro MUI_PAGE_DIRECTORY

; page - install files
!insertmacro MUI_PAGE_INSTFILES

; page - uninstallation
!insertmacro MUI_UNPAGE_COMPONENTS
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "English"


; data - installer branding
VIProductVersion "${HCC_Version}.0.0"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "${HCC_Title}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "${HCC_Title}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "HCC Development Team"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "HCC Application and datafile formats: HCC Development Team. Actual data and derived icons: Virtrium LLC"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "HCC Development Team"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "${HCC_Version}.0.0"
VIAddVersionKey /LANG=${LANG_ENGLISH} "Script" "NSIS Install Script by Arcat - revision: ${HCC_Installer_Version}"

; data - language strings


; compile time init
ReserveFile "options.ini"
ReserveFile "layout_docked.bmp"
ReserveFile "layout_float.bmp"
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS

; runtime init
Function .onInit
	SetShellVarContext all
	!insertmacro MUI_INSTALLOPTIONS_EXTRACT "options.ini"
	
	InitPluginsDir
  	File /oname=$PLUGINSDIR\layout_docked.bmp "layout_docked.bmp"
  	File /oname=$PLUGINSDIR\layout_float.bmp "layout_float.bmp"
	
	Call detectInstallerProcess
	Call detectHCCProcess
FunctionEnd

Function un.onInit
	SetShellVarContext all
	Call un.detectInstallerProcess
	Call un.detectHCCProcess
FunctionEnd


; data - language strings
LangString DESC_section_core ${LANG_ENGLISH} "The main application."
LangString DESC_section_themes ${LANG_ENGLISH} "Application Themes"
LangString DESC_section_data ${LANG_ENGLISH} "Formulae and Techniques. If you skip this package you have to install it via Live Update lateron."
LangString DESC_section_examples ${LANG_ENGLISH} "Example orders, profiles and plugins."
;LangString DESC_section_dev ${LANG_ENGLISH} "This option will be removed at public builds."
LangString DESC_section_nul ${LANG_ENGLISH} " "

/*
 *	installation
*/

Function section_layout
	!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 1" "Text" "Default Layout Selection"
	!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 2" "Text" "Docked"
	!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 3" "Text" "Floating"
	
	!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 4" "Text" $PLUGINSDIR\layout_docked.bmp
	!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 5" "Text" $PLUGINSDIR\layout_float.bmp
	
	!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 6" "Text" "Restore default Layout (disabled on first install)"
	
	!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 7" "Text" "Default Preferences"
	
	!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 8" "Text" "Floating mode is only recommended for users with a Screen resolution of 1024x768 and higher (or dual screen). Of course, you may toggle between both modes later within HCC."
	!insertmacro MUI_HEADER_TEXT "Choose your Layout" "The ${HCC_Title} Layout can be fully customized. For your convenience we provide two default layouts for your first time experience. :)"

	ReadRegStr $R1 HKLM SOFTWARE\${HCC_Name}\Config "DockingMode"
	StrCmp $R1 "Y" read_docked read_unclear
	
	read_docked:
		!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 2" "State" "1"
		!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 3" "State" "0"
		
		!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 6" "State" "0"
			!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 6" "Flags" " "
			!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 6" "Text" "Restore default Layout (window positions and sizes)"
		!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 7" "State" "0"
		!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 7" "Flags" " "
		!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 7" "Text" "Reset Preferences"
	goto read_done

	read_unclear:
		StrCmp $R1 "N" read_float read_unset

		read_float:
			!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 2" "State" "0"
			!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 3" "State" "1"
			
			!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 6" "State" "0"
			!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 6" "Flags" " "
			!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 6" "Text" "Restore default Layout (window positions and sizes)"
			!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 7" "State" "0"
			!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 7" "Flags" " "
			!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 7" "Text" "Reset Preferences"
		goto read_unset
		
		read_unset:
			System::Call 'user32::GetSystemMetrics(i 0) i .r0'
			
			
			Var /GLOBAL Reg_ItemResourceSize
			; ${Reg_ItemResourceSize}
			Var /GLOBAL Reg_StickyStrength
			; ${Reg_StickyStrength}
			; = < >
			
			IntCmp $0 1024 0 0 +4
			StrCpy $Reg_ItemResourceSize "4"
			StrCpy $Reg_StickyStrength "8"
			goto done
			
			IntCmp $0 1280 0 0 +4
			StrCpy $Reg_ItemResourceSize "8"
			StrCpy $Reg_StickyStrength "8"
			goto done
			
			IntCmp $0 1600 0 0 +4
			StrCpy $Reg_ItemResourceSize "12"
			StrCpy $Reg_StickyStrength "16"
			goto done

			IntCmp $0 1900 0 0 0
			StrCpy $Reg_ItemResourceSize "12"
			StrCpy $Reg_StickyStrength "16"
			goto done
			
			done:
/* SNIP 8< SNIP */
Var /GLOBAL Reg_ToolbarWnd
Var /GLOBAL Reg_ItemCreationWnd
Var /GLOBAL Reg_ReportWnd
Var /GLOBAL Reg_TechSelectionWnd
Var /GLOBAL Reg_ProfileWnd
Var /GLOBAL Reg_ComponentWnd
Var /GLOBAL Reg_OrderWnd


; 800.reg - width:946px, height:220px
IntCmp $0 800 0 0 +9

StrCpy $Reg_ToolbarWnd "X:0, Y:0, W:126, H:389, V:Y T:N"
StrCpy $Reg_ItemCreationWnd "X:126, Y:0, W:474, H:567, V:N T:N"
StrCpy $Reg_ReportWnd "X:126, Y:0, W:474, H:567, V:N T:N"
StrCpy $Reg_TechSelectionWnd "X:126, Y:0, W:474, H:567, V:N T:N"
StrCpy $Reg_ProfileWnd "X:126, Y:0, W:462, H:511, V:N T:N"
StrCpy $Reg_ComponentWnd "X:126, Y:0, W:474, H:567, V:N T:N"
StrCpy $Reg_OrderWnd "X:126, Y:0, W:474, H:567, V:N T:N"
goto layout_done

; 1024.reg - width:1026px, height:780px
IntCmp $0 1024 0 0 +9

StrCpy $Reg_ToolbarWnd "X:15, Y:60, W:126, H:385, V:Y T:N"
StrCpy $Reg_ItemCreationWnd "X:141, Y:60, W:435, H:660, V:Y T:N"
StrCpy $Reg_ReportWnd "X:576, Y:480, W:435, H:240, V:Y T:N"
StrCpy $Reg_TechSelectionWnd "X:576, Y:60, W:435, H:420, V:Y T:N"
StrCpy $Reg_ProfileWnd "X:243, Y:9, W:462, H:511, V:N T:N"
StrCpy $Reg_ComponentWnd "X:209, Y:26, W:462, H:511, V:N T:N"
StrCpy $Reg_OrderWnd "X:175, Y:43, W:308, H:511, V:N T:N"
goto layout_done

; 1280.reg - width:1286px, height:1000px
IntCmp $0 1280 0 0 +9

StrCpy $Reg_ToolbarWnd "X:30, Y:70, W:126, H:385, V:Y T:N"
StrCpy $Reg_ItemCreationWnd "X:156, Y:70, W:600, H:860, V:Y T:N"
StrCpy $Reg_ReportWnd "X:756, Y:561, W:500, H:369, V:Y T:N"
StrCpy $Reg_TechSelectionWnd "X:756, Y:70, W:500, H:491, V:Y T:N"
StrCpy $Reg_ProfileWnd "X:420, Y:4, W:462, H:511, V:N T:N"
StrCpy $Reg_ComponentWnd "X:332, Y:26, W:462, H:511, V:N T:N"
StrCpy $Reg_OrderWnd "X:244, Y:48, W:308, H:511, V:N T:N"
goto layout_done

; 1600.reg - width:1600px, height:1140px
IntCmp $0 1600 0 0 0

StrCpy $Reg_ToolbarWnd "X:147, Y:70, W:126, H:385, V:Y T:N"
StrCpy $Reg_ItemCreationWnd "X:273, Y:70, W:640, H:1000, V:Y T:N"
StrCpy $Reg_ReportWnd "X:913, Y:641, W:540, H:429, V:Y T:N"
StrCpy $Reg_TechSelectionWnd "X:913, Y:70, W:540, H:571, V:Y T:N"
StrCpy $Reg_ProfileWnd "X:537, Y:4, W:462, H:511, V:N T:N"
StrCpy $Reg_ComponentWnd "X:449, Y:26, W:462, H:511, V:N T:N"
StrCpy $Reg_OrderWnd "X:361, Y:48, W:308, H:511, V:N T:N"
goto layout_done

layout_done:

/* SNIP 8< SNIP */


			IntCmp $0 1024 recommend_float recommend_docked recommend_float
			recommend_docked:
				!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 2" "State" "1"
				!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 3" "State" "0"
			goto read_done
			
			recommend_float:
				!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 2" "State" "0"
				!insertmacro MUI_INSTALLOPTIONS_WRITE "options.ini" "Field 3" "State" "1"
			goto read_done
		goto read_done

	read_done:
	
	!insertmacro MUI_INSTALLOPTIONS_DISPLAY "options.ini"
FunctionEnd

Section "v${HCC_Version} Application Files (required)" section_core
	SectionIn RO
	SetOutPath $INSTDIR



	; make some choices

	!insertmacro MUI_INSTALLOPTIONS_READ $R0 "options.ini" "Field 2" "State"
    StrCmp $R0 "1" choice_docked nochoice_docked
    choice_docked:
    	WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "DockingMode" "Y"
    	GoTo nochoice_docked
    nochoice_docked:

	!insertmacro MUI_INSTALLOPTIONS_READ $R1 "options.ini" "Field 3" "State"
  	StrCmp $R1 "1" choice_float nochoice_float
    choice_float:
    	WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "DockingMode" "N"
    	GoTo nochoice_float
    nochoice_float:
    
    !insertmacro MUI_INSTALLOPTIONS_READ $R1 "options.ini" "Field 6" "State"
  	StrCmp $R1 "1" choice_reset nochoice_reset
    choice_reset:
    	DetailPrint "Deleting User Layout Settings"
    	DeleteRegKey HKLM SOFTWARE\${HCC_Name}\Config\Windows
    nochoice_reset:
    
    !insertmacro MUI_INSTALLOPTIONS_READ $R1 "options.ini" "Field 7" "State"
  	StrCmp $R1 "1" choice_reset_prefs nochoice_reset_prefs
    choice_reset_prefs:
    	DetailPrint "Deleting Preferences"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "CurrentProfile"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "CurrentProfileType"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "EnableIcons"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "ExpandFormulaMode"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "ExpandTechMode"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "IconSize"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "ItemResourceSize"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "GameBasePath"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "LastFormulaCategory"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "LastTechCategory"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "GlobalHotkeys"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "ReportType"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "ShowReportMode"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "ShowReportResourceMode"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "ShowUsableTechs"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "StickyStrength"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "CurrentTheme"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "DragWithToolbar"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "ShowReportBonusMode"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "VerticalToolbar"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "AutoShrink"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "AutoUpdate"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "AutoUpdateQuery"
		
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "GameBasePath"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "LastFormulaCategory"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "LastTechCategory"
		DeleteRegValue HKLM "SOFTWARE\${HCC_Name}\Config" "ShowResourceMode"
		
    nochoice_reset_prefs:
 	
     	
	File ..\HCC.exe
	File ..\gdiplus.dll
	File ..\unzip32.dll
	File ..\msvcr71.dll
	File ..\ReadMe.txt
	File ..\License.txt
	File ..\Config.xml
	File ..\Release.xml
	File "..\Official HCC Website.url"
	File "..\Online Manual.url"
	
	CreateDirectory $INSTDIR\Config
	CreateDirectory $INSTDIR\Cache
	CreateDirectory $INSTDIR\Temp
	CreateDirectory $INSTDIR\Orders
	CreateDirectory $INSTDIR\Themes
	CreateDirectory $INSTDIR\Profiles
	CreateDirectory $INSTDIR\Config
	CreateDirectory $INSTDIR\Plugins
	
	; OCX handling
	StrCpy $2 "$SYSDIR\MSFLXGRD.OCX"
	
	GetDllVersion "$2" $R0 $R1
	
	IntOp $R2 $R0 / 0x00010000
	IntOp $R3 $R0 & 0x0000FFFF 
	IntOp $R4 $R1 / 0x00010000 
	IntOp $R5 $R1 & 0x0000FFFF 
	StrCpy $5 "$R2.$R3.$R4.$R5" 

	Var /GLOBAL Current_OCX
	DetailPrint "Detected MSFLXGRD.OCX v$5"
		
	;StrCpy $Current_OCX $5
	
	;WordReplace ${WordAdd} $Current_OCX " " "-C"
	${VersionCompare} $5 "6.1.97.82" $Current_OCX
	;0 = version is ok - overwrite
	;1 = installed is newer - skip
	;2 = installed is over - install
	
	IntCmp $Current_OCX 1 +4 0 0
	File /oname=$SYSDIR\MSFLXGRD.OCX "MSFLXGRD.OCX"
	RegDLL "$SYSDIR\MSFLXGRD.OCX"
	;MessageBox MB_OK "Installed OCX $5 - $Current_OCX"

	; File "..\MSFLXGRD.OCX"
	; RegDLL "$INSTDIR\MSFLXGRD.OCX"
	
	WriteUninstaller "uninstall.exe"

	WriteRegStr HKLM SOFTWARE\${HCC_Name} "Install_Dir" "$INSTDIR"
	WriteRegStr HKLM SOFTWARE\${HCC_Name} "Install_Script" "${HCC_Installer_Version}"
	WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "DatabaseRevision" "${HCC_Revision}"
	WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config\Windows "" "" ;todo
	
	; always set
	WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "EnableCache" "Y"


	; set only if needed	
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "CurrentProfile"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "CurrentProfile" "Optimal"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "CurrentProfileType"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "CurrentProfileType" "Default"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "EnableIcons"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "EnableIcons" "Y"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "ExpandFormulaMode"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "ExpandFormulaMode" "1"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "ExpandTechMode"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "ExpandTechMode" "1"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "IconSize"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "IconSize" "16"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "ItemResourceSize"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "ItemResourceSize" "$Reg_ItemResourceSize"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "GlobalHotkeys"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "GlobalHotkeys" "Y"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "ReportType"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "ReportType" "0"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "ShowReportMode"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "ShowReportMode" "0"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "ShowReportResourceMode"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "ShowReportResourceMode" "0"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "ShowUsableTechs"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "ShowUsableTechs" "Y"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "StickyStrength"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "StickyStrength" "$Reg_StickyStrength"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "DragWithToolbar"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "DragWithToolbar" "N"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "ShowReportBonusMode"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "ShowReportBonusMode" "0"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "CurrentTheme"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "CurrentTheme" "desktop_bright_default.xml"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "VerticalToolbar"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "VerticalToolbar" "Y"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "AutoShrink"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "AutoShrink" "Y"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "AutoUpdate"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "AutoUpdate" "N"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config" "AutoUpdateQuery"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config "AutoUpdateQuery" "Y"

	
	; Layout
	
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config\Windows" "ToolbarWnd"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config\Windows "ToolbarWnd" "$Reg_ToolbarWnd"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config\Windows" "ItemCreationWnd"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config\Windows "ItemCreationWnd" "$Reg_ItemCreationWnd"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config\Windows" "ReportWnd"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config\Windows "ReportWnd" "$Reg_ReportWnd"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config\Windows" "TechSelectionWnd"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config\Windows "TechSelectionWnd" "$Reg_TechSelectionWnd"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config\Windows" "ProfileWnd"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config\Windows "ProfileWnd" "$Reg_ProfileWnd"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config\Windows" "ComponentWnd"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config\Windows "ComponentWnd" "$Reg_ComponentWnd"
	ReadRegStr $R0 HKLM "SOFTWARE\${HCC_Name}\Config\Windows" "OrderWnd"
	StrCmp $R0 "" 0 +2
		WriteRegStr HKLM SOFTWARE\${HCC_Name}\Config\Windows "OrderWnd" "$Reg_OrderWnd"
	
	

	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${HCC_Name}" "DisplayName" "${HCC_Title}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${HCC_Name}" "UninstallString" '"$INSTDIR\uninstall.exe"'
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${HCC_Name}" "NoModify" 1
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${HCC_Name}" "NoRepair" 1
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${HCC_Name}" "HelpLink" "http://hcc.reclamation.dk/"
	
	AccessControl::GrantOnFile "$INSTDIR\" "(BU)" "FullAccess"
	AccessControl::GrantOnRegKey HKLM "Software\${HCC_Name}" "(BU)" "FullAccess"
SectionEnd

Section "Themes (required)" section_themes
	SectionIn RO
  File /r ..\Themes
SectionEnd

Section "${HCC_Revision} Database Files (recommended)" section_data
	AddSize 4096
	;File /r ..\Config ;old Method - obsolete
	File /oname=Temp\HCC_${HCC_Revision}.zip ..\..\HCC_${HCC_Revision}.zip
SectionEnd

Section "Example Orders, Profiles and Plugins" section_examples
  File /r ..\Orders
  ;Rename $INSTDIR\Orders\Examples\bigsort.xml $INSTDIR\Orders\Examples\bigsort.hcc
  File /r ..\Profiles
  File /r ..\Plugins
SectionEnd

Section "StartMenu Shortcuts" section_menu
	CreateDirectory "$SMPROGRAMS\${HCC_Title}"
	CreateShortCut "$SMPROGRAMS\${HCC_Title}\${HCC_Title}.lnk" "$INSTDIR\HCC.exe"
	CreateShortCut "$SMPROGRAMS\${HCC_Title}\Official HCC Website (Updates & Support).lnk" "$INSTDIR\Official HCC Website.url"
	CreateShortCut "$SMPROGRAMS\${HCC_Title}\Online Manual.lnk" "$INSTDIR\Online Manual.url"
	CreateShortCut "$SMPROGRAMS\${HCC_Title}\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
	SectionEnd

Section /o "Desktop Icon" section_desktop
	CreateShortCut "$DESKTOP\${HCC_Title}.lnk" "$INSTDIR\HCC.exe"
SectionEnd

;Section /o "Development Files (experimental)" section_dev ;TODO remove at final version
;	File ..\Config_dev.xml
;SectionEnd

/*
 *	un-installation
*/

Section "Uninstall"
	
	SectionIn RO

	;UnRegDLL $INSTDIR\MSFLXGRD.OCX

	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${HCC_Name}"

	Delete $INSTDIR\HCC.exe
	Delete $INSTDIR\gdiplus.dll
	Delete $INSTDIR\unzip32.dll
	Delete $INSTDIR\msvcr71.dll
	Delete $INSTDIR\ReadMe.txt
	Delete $INSTDIR\License.txt
	Delete $INSTDIR\Config.xml
	;Delete $INSTDIR\Config_dev.xml ;TODO remove at final version
	Delete $INSTDIR\Release.xml
	Delete "$INSTDIR\Official HCC Website.url"
	Delete "$INSTDIR\Online Manual.url"

	Delete $INSTDIR\uninstall.exe
	Delete "$SMPROGRAMS\${HCC_Title}\*.*"
	Delete "$DESKTOP\${HCC_Title}.lnk"

	;Delete $INSTDIR\MSFLXGRD.OCX

	Delete $INSTDIR\Themes\desktop_bright_alternate.xml
	Delete $INSTDIR\Themes\desktop_bright_default.xml
	Delete $INSTDIR\Themes\desktop_native.xml
	Delete $INSTDIR\Themes\themes_readme.txt
	StrCpy $0 $INSTDIR\Themes
	Call un.DeleteDirIfEmpty
	
	Delete $INSTDIR\Plugins\plugins_readme.txt
	RMDir /r "$INSTDIR\Plugins\HCC Online Orders"
	StrCpy $0 $INSTDIR\Plugins
	Call un.DeleteDirIfEmpty

	Delete $INSTDIR\Profiles\Example.xml
	StrCpy $0 $INSTDIR\Profiles
	Call un.DeleteDirIfEmpty

	RMDir /r $INSTDIR\Orders\Examples
	StrCpy $0 $INSTDIR\Orders
	Call un.DeleteDirIfEmpty
	
	RMDir /r $INSTDIR\Config
	RMDir /r $INSTDIR\Cache
	RMDir /r $INSTDIR\Temp

	RMDir "$SMPROGRAMS\${HCC_Title}"

	StrCpy $0 $INSTDIR
	Call un.DeleteDirIfEmpty
SectionEnd

Section "un.Delete Preferences/Layout Settings"

	DeleteRegKey HKLM SOFTWARE\${HCC_Name}\Config

SectionEnd

Section /o "un.Delete YOUR Profiles/Orders/Themes/Plugins"

	RMDir /r $INSTDIR\Profiles
	RMDir /r $INSTDIR\Orders
	RMDir /r $INSTDIR\Themes
	RMDir /r $INSTDIR\Plugins
	DeleteRegKey HKLM SOFTWARE\${HCC_Name}

	StrCpy $0 $INSTDIR
	Call un.DeleteDirIfEmpty
SectionEnd

Section /o "un.Uninstall MSFLXGRD.OCX from system32 (experts!)"
	UnRegDLL $SYSDIR\MSFLXGRD.OCX
	Delete $SYSDIR\MSFLXGRD.OCX
	
	StrCpy $0 $INSTDIR
	Call un.DeleteDirIfEmpty
SectionEnd

/*
 *	define some usefull macros
*/

!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
!insertmacro MUI_DESCRIPTION_TEXT ${section_core} $(DESC_section_core)
!insertmacro MUI_DESCRIPTION_TEXT ${section_themes} $(DESC_section_themes)
!insertmacro MUI_DESCRIPTION_TEXT ${section_data} $(DESC_section_data)
!insertmacro MUI_DESCRIPTION_TEXT ${section_examples} $(DESC_section_examples)
;!insertmacro MUI_DESCRIPTION_TEXT ${section_dev} $(DESC_section_dev)
!insertmacro MUI_DESCRIPTION_TEXT ${section_menu} $(DESC_section_nul)
!insertmacro MUI_DESCRIPTION_TEXT ${section_desktop} $(DESC_section_nul)
!insertmacro MUI_FUNCTION_DESCRIPTION_END


/*
 *	functions
*/

Function un.DeleteDirIfEmpty
	FindFirst $R0 $R1 "$0\*.*"
	strcmp $R1 "." 0 NoDelete
	FindNext $R0 $R1
	strcmp $R1 ".." 0 NoDelete
	ClearErrors
	FindNext $R0 $R1
	IfErrors 0 NoDelete
	FindClose $R0
	Sleep 1000
	RMDir "$0"
	NoDelete:
	FindClose $R0
FunctionEnd

Function detectHCCProcess
    detecthcc:
    Processes::FindProcess "HCC.exe"
	Pop $R0
 	StrCmp $R0 "1" hcc_running hcc_notrunning
	
	hcc_running:
		MessageBox MB_RETRYCANCEL "${HCC_Title} needs to be closed first." IDRETRY detecthcc IDCANCEL installerfailed
	
	installerfailed:
	Abort
	
	hcc_notrunning:
FunctionEnd

Function detectInstallerProcess
	System::Call 'kernel32::CreateMutexA(i 0, i 0, t "HCC_installer") i .r1 ?e'
	Pop $R0 
  	StrCmp $R0 0 +3 
    MessageBox MB_OK "The installer is already running." 
    Abort
FunctionEnd

Function un.detectHCCProcess
    detecthcc:
    Processes::FindProcess "HCC.exe"
	Pop $R0
 	StrCmp $R0 "1" hcc_running hcc_notrunning
	
	hcc_running:
		MessageBox MB_RETRYCANCEL "${HCC_Title} needs to be closed first." IDRETRY detecthcc IDCANCEL installerfailed
	
	installerfailed:
	Abort
	
	hcc_notrunning:
FunctionEnd

Function un.detectInstallerProcess
	System::Call 'kernel32::CreateMutexA(i 0, i 0, t "HCC_installer") i .r1 ?e'
	Pop $R0 
  	StrCmp $R0 0 +3 
    MessageBox MB_OK "The uninstaller is already running." 
    Abort
FunctionEnd

/*
 *	end - have a nice day :)
*/
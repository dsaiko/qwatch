;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

  
  !define	VERSION		"1.0.28"
  !define	REGISTRYKEY	"Software\qwatch"
  !define	APPNAME		"QWatch"
  !define	APPFILE		"qwatch"
  
;--------------------------------
;General
  XPStyle on
  SetCompressor /SOLID lzma
  
  ;Name and file
  Name "${APPNAME}"
  Caption "${APPNAME} ${VERSION} Setup"  
  !define MUI_ICON  "../src-app/res/images/qwatch.ico"
  !define MUI_WELCOMEFINISHPAGE_BITMAP  "logo-${APPFILE}.bmp"
  !define MUI_UNWELCOMEFINISHPAGE_BITMAP  "logo-${APPFILE}.bmp"
  OutFile "..\dist\${APPFILE}-${VERSION}-setup.exe"
  

  ;Default installation folder
  InstallDir "$LOCALAPPDATA\${APPNAME}"

  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "${REGISTRYKEY}" ""
  
  ;
  
  ;Request application privileges for Windows Vista
  RequestExecutionLevel user

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "..\LICENSE.TXT"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !define MUI_FINISHPAGE_RUN "$INSTDIR\${APPFILE}.exe"
  !insertmacro MUI_PAGE_FINISH

  !insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH
;--------------------------------
;Languages
  !define MUI_LANGDLL_ALLLANGUAGES

  !insertmacro MUI_LANGUAGE "English"
  !insertmacro MUI_LANGUAGE "German"
  !insertmacro MUI_LANGUAGE "Czech"

  
;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecQWatch ${LANG_ENGLISH} "Main app"
  LangString DESC_SecQWatch ${LANG_CZECH}   "Main app"
  LangString DESC_SecQWatch ${LANG_GERMAN}  "Main app"

  LangString DESC_SecQWatchMenuGroup ${LANG_ENGLISH} "Creates application menu group."
  LangString DESC_SecQWatchMenuGroup ${LANG_CZECH}   "Vytvo�� ikony aplikace v nab�dce Start"
  LangString DESC_SecQWatchMenuGroup ${LANG_GERMAN}  "Anwendungsmen� Gruppe erstellen."
  
  LangString DESC_SecQWatchDesktop ${LANG_ENGLISH} "Creates desktop icon."
  LangString DESC_SecQWatchDesktop ${LANG_CZECH}   "Vytvo�� ikonu na pracovn� plo�e."
  LangString DESC_SecQWatchDesktop ${LANG_GERMAN}  "Ein Desktop-Symbol erstellen"

  LangString DESC_SecQWatchAutostart ${LANG_ENGLISH} "Autostart application at next login."
  LangString DESC_SecQWatchAutostart ${LANG_CZECH}   "Spustit aplikaci automaticky po dal��m p�ihl�en�."
  LangString DESC_SecQWatchAutostart ${LANG_GERMAN}  "Autostart-Anwendung f�r die n�chsten Anmeldung"
  
  LangString DESC_UNINSTALL ${LANG_ENGLISH} "uninstall"
  LangString DESC_UNINSTALL ${LANG_CZECH}   "odinstalov�n�"
  LangString DESC_UNINSTALL ${LANG_GERMAN}  "deinstallieren"

  LangString TITLE_MENU_GROUP ${LANG_ENGLISH} "Create menu group"
  LangString TITLE_MENU_GROUP ${LANG_CZECH}   "Vytvo�it ikony aplikace v nab�dce Start"
  LangString TITLE_MENU_GROUP ${LANG_GERMAN}  "Anwendungsmen� Gruppe erstellen"

  LangString TITLE_DESKTOP_ICON ${LANG_ENGLISH} "Create desktop icon"
  LangString TITLE_DESKTOP_ICON ${LANG_CZECH}   "Vytvo�it ikonu na plo�e"
  LangString TITLE_DESKTOP_ICON ${LANG_GERMAN}  "Ein Desktop-Symbol erstellen"

  LangString TITLE_AUTOSTART ${LANG_ENGLISH} "Automatically start up application"
  LangString TITLE_AUTOSTART ${LANG_CZECH}   "Automaticky spou�t�t aplikaci"
  LangString TITLE_AUTOSTART ${LANG_GERMAN}  "Autostart-Anwendung f�r die n�chsten Anmeldung"
  
;--------------------------------
;Installer Sections

Section "-QWatch" SecQWatch

  StrCpy $0 "${APPFILE}.exe"
  KillProc::KillProcesses
  Sleep 1000

  SetOutPath "$INSTDIR"

  ;ADD YOUR OWN FILES HERE...
  File "..\build\${APPFILE}.exe"

  ;Store installation folder
  WriteRegStr HKCU "${REGISTRYKEY}" "" $INSTDIR

  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" \
  		"DisplayName" "${APPNAME}"
  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" \
                 "UninstallString" "$\"$INSTDIR\uninstall.exe$\""
		 
  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" \
                 "QuietUninstallString" "$\"$INSTDIR\uninstall.exe$\" /S"		 
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\uninstall.exe"

SectionEnd

Section "$(TITLE_MENU_GROUP)" SecQWatchMenuGroup
  CreateDirectory "$SMPROGRAMS\${APPNAME}"
  CreateShortCut  "$SMPROGRAMS\${APPNAME}\${APPNAME}.lnk" "$INSTDIR\${APPFILE}.exe" 
  CreateShortCut  "$SMPROGRAMS\${APPNAME}\${APPNAME} - $(DESC_UNINSTALL).lnk" "$INSTDIR\uninstall.exe"
SectionEnd

Section "$(TITLE_DESKTOP_ICON)" SecQWatchDesktop
  CreateShortCut  "$DESKTOP\${APPNAME}.lnk" "$INSTDIR\${APPFILE}.exe"
SectionEnd

Section "$(TITLE_AUTOSTART)" SecQWatchAutostart
  CreateShortCut  "$SMSTARTUP\${APPNAME}.lnk" "$INSTDIR\${APPFILE}.exe"  
SectionEnd


;Assign language strings to sections
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
	!insertmacro MUI_DESCRIPTION_TEXT ${SecQWatch} $(DESC_SecQWatch)
	!insertmacro MUI_DESCRIPTION_TEXT ${SecQWatchMenuGroup} $(DESC_SecQWatchMenuGroup)
	!insertmacro MUI_DESCRIPTION_TEXT ${SecQWatchDesktop} $(DESC_SecQWatchDesktop)
	!insertmacro MUI_DESCRIPTION_TEXT ${SecQWatchAutostart} $(DESC_SecQWatchAutostart)
!insertmacro MUI_FUNCTION_DESCRIPTION_END


;--------------------------------
;Installer Functions

Function .onInit

  !insertmacro MUI_LANGDLL_DISPLAY

FunctionEnd


;--------------------------------
;Uninstaller Section

Section "Uninstall"

  StrCpy $0 "${APPFILE}.exe"
  KillProc::KillProcesses
  Sleep 1000

  ;ADD YOUR OWN FILES HERE...

  Delete "$INSTDIR\Uninstall.exe"
  Delete "$INSTDIR\${APPFILE}.exe"
  Delete "$DESKTOP\${APPNAME}.lnk"
  Delete "$SMSTARTUP\${APPNAME}.lnk"

  RMDir /r "$INSTDIR"
  RMDir /r "$PROFILE\.${APPFILE}"
  RMDir /r "$SMPROGRAMS\${APPNAME}"

  DeleteRegKey HKCU "${REGISTRYKEY}"
  DeleteRegKey HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}"


SectionEnd

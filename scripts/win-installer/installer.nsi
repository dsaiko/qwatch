;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"
  !include "x64.nsh"
  
  !define	VERSION		"__VERSION__"
  !define	REGISTRYKEY	"Software\__APPFILE__"
  !define	APPNAME		"__APPNAME__"
  !define	APPFILE		"__APPFILE__"
  
;--------------------------------
;General
  XPStyle on
  SetCompressor /SOLID lzma
  
  ;Name and file
  Name "${APPNAME}"
  Caption "${APPNAME} ${VERSION} Setup"  
  !define MUI_ICON  "qwatch.ico"
  !define MUI_WELCOMEFINISHPAGE_BITMAP  "logo-${APPFILE}.bmp"
  !define MUI_UNWELCOMEFINISHPAGE_BITMAP  "logo-${APPFILE}.bmp"
  OutFile "${APPFILE}-${VERSION}-setup.exe"
  

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

  ;Remember the installer language
  !define MUI_LANGDLL_REGISTRY_ROOT "HKCU" 
  !define MUI_LANGDLL_REGISTRY_KEY "${REGISTRYKEY}" 
  !define MUI_LANGDLL_REGISTRY_VALUENAME "InstallerLanguage"

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "LICENSE.TXT"
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

  LangString DESC_SecQWatchMenuGroup ${LANG_ENGLISH} "Create application menu group"
  LangString DESC_SecQWatchMenuGroup ${LANG_CZECH}   "Vytvoøí ikony aplikace v nabídce Start"
  LangString DESC_SecQWatchMenuGroup ${LANG_GERMAN}  "Startmenü-Gruppe erstellen"
  
  LangString DESC_SecQWatchDesktop ${LANG_ENGLISH} "Creates desktop icon."
  LangString DESC_SecQWatchDesktop ${LANG_CZECH}   "Vytvoøí ikonu na pracovní ploše."
  LangString DESC_SecQWatchDesktop ${LANG_GERMAN}  "Desktop-Symbol erstellen."

  LangString DESC_SecQWatchAutostart ${LANG_ENGLISH} "Autostart application at next login."
  LangString DESC_SecQWatchAutostart ${LANG_CZECH}   "Spustit aplikaci automaticky po dalším pøihlášení."
  LangString DESC_SecQWatchAutostart ${LANG_GERMAN}  "Anwendung bei nächster Anmeldung automatisch starten"
  
  LangString DESC_UNINSTALL ${LANG_ENGLISH} "uninstall"
  LangString DESC_UNINSTALL ${LANG_CZECH}   "odinstalování"
  LangString DESC_UNINSTALL ${LANG_GERMAN}  "deinstallieren"

  LangString TITLE_MENU_GROUP ${LANG_ENGLISH} "Create menu group"
  LangString TITLE_MENU_GROUP ${LANG_CZECH}   "Vytvoøit ikony aplikace v nabídce Start"
  LangString TITLE_MENU_GROUP ${LANG_GERMAN}  "Startmenü-Gruppe erstellen"

  LangString TITLE_DESKTOP_ICON ${LANG_ENGLISH} "Create desktop icon"
  LangString TITLE_DESKTOP_ICON ${LANG_CZECH}   "Vytvoøit ikonu na ploše"
  LangString TITLE_DESKTOP_ICON ${LANG_GERMAN}  "Desktop-Symbol erstellen"

  LangString TITLE_AUTOSTART ${LANG_ENGLISH} "Automatically start up application"
  LangString TITLE_AUTOSTART ${LANG_CZECH}   "Automaticky spouštìt aplikaci"
  LangString TITLE_AUTOSTART ${LANG_GERMAN}  "Anwendung bei nächster Anmeldung automatisch starten"
  
;--------------------------------
;Installer Sections

Section "-QWatch" SecQWatch

  StrCpy $0 "${APPFILE}.exe"
  KillProc::KillProcesses
  Sleep 1000

  SetOutPath "$INSTDIR"

  ;ADD YOUR OWN FILES HERE...
  ${If} ${RunningX64}
    File "x64\${APPFILE}.exe"
  ${Else}
    File "x86\${APPFILE}.exe"
  ${EndIf}

  File ${APPFILE}\uninstall.exe
  ;Create uninstaller
  ;WriteUninstaller "$INSTDIR\uninstall.exe"

  ;Store installation folder
  WriteRegStr HKCU "${REGISTRYKEY}" "" $INSTDIR

  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" \
  		"DisplayName" "${APPNAME}"
  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" \
                 "UninstallString" "$\"$INSTDIR\uninstall.exe$\""
		 
  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" \
                 "QuietUninstallString" "$\"$INSTDIR\uninstall.exe$\" /S"		 
  

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

Function un.onInit
  !insertmacro MUI_UNGETLANGUAGE
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
  RMDir /r "$LOCALAPPDATA\.${APPNAME}"
  RMDir /r "$LOCALAPPDATA\${APPNAME}"

  DeleteRegKey HKCU "${REGISTRYKEY}"
  DeleteRegKey HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}"


SectionEnd

/*

Miranda NG: the free IM client for Microsoft* Windows*

Copyright (c) 2012-14 Miranda NG project (http://miranda-ng.org),
Copyright (c) 2000-12 Miranda IM project,
all portions of this codebase are copyrighted to the people
listed in contributors.txt.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "..\..\core\commonheaders.h"
#include "langpack.h"

MIR_CORE_DLL(int) LoadLangPackDescr(const TCHAR *szLangPack, LANGPACK_INFO *lpInfo);

BOOL EnumLangpacks(ENUM_PACKS_CALLBACK callback, WPARAM wParam, LPARAM lParam)
{
	if (callback == NULL) return FALSE;

	BOOL res = FALSE;

	/* language folder */
	ptrT langpack(db_get_tsa(NULL, "Langpack", "Current"));

	LANGPACK_INFO pack;
	PathToAbsoluteT(_T("\\Languages\\langpack_*.txt"), pack.tszFullPath);

	BOOL fPackFound = FALSE;
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(pack.tszFullPath, &wfd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
			/* get data */
			TCHAR tszFullPath[MAX_PATH];
			PathToAbsoluteT(_T("\\Languages\\"), tszFullPath);
			lstrcat(tszFullPath, wfd.cFileName);

			ZeroMemory(&pack, sizeof(pack));
			if (!LoadLangPackDescr(tszFullPath, &pack)) {
				pack.ftFileDate = wfd.ftLastWriteTime;
				/* enabled? */
				if (langpack && !lstrcmpi(langpack, wfd.cFileName)) {
					if (!fPackFound) pack.flags |= LPF_ENABLED;
					fPackFound = TRUE;
				}
				/* callback */
				res = callback(&pack, wParam, lParam);
				if (!res) { FindClose(hFind); return FALSE; }
			}
		} while (FindNextFile(hFind, &wfd));
		FindClose(hFind);
	}

	/* default langpack: English */
	if (callback != NULL) {
		ZeroMemory(&pack, sizeof(pack));
		pack.Locale = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);
		lstrcpy(pack.tszLanguage, _T("English"));
		lstrcpyA(pack.szAuthors, "Miranda NG Development Team");
		lstrcpyA(pack.szAuthorEmail, "project-info@miranda-ng.org");
		DWORD v = CallService(MS_SYSTEM_GETVERSION, 0, 0);
		mir_snprintf(pack.szLastModifiedUsing, sizeof(pack.szLastModifiedUsing), "%d.%d.%d", ((v >> 24) & 0xFF), ((v >> 16) & 0xFF), ((v >> 8) & 0xFF));
		/* file date */
		if (GetModuleFileName(NULL, pack.tszFullPath, SIZEOF(pack.tszFullPath))) {
			lstrcpy(pack.tszFileName, _tcsrchr(pack.tszFullPath, '\\') + 1);
			HANDLE hFile = CreateFile(pack.tszFileName, 0, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
			if (hFile != INVALID_HANDLE_VALUE) {
				GetFileTime(hFile, NULL, NULL, &pack.ftFileDate);
				CloseHandle(hFile);
			}
		}
		pack.flags = LPF_DEFAULT;
		
		if (!fPackFound) pack.flags |= LPF_ENABLED;
		/* callback */
		if (!callback(&pack, wParam, lParam)) return FALSE;
	}

	return fPackFound;
}
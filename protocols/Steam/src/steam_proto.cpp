﻿#include "common.h"

CSteamProto::CSteamProto(const char* protoName, const TCHAR* userName) :
	PROTO<CSteamProto>(protoName, userName)
{
	CreateProtoService(PS_CREATEACCMGRUI, &CSteamProto::OnAccountManagerInit);

	InitializeCriticalSection(&this->contact_search_lock);
}

CSteamProto::~CSteamProto()
{
	DeleteCriticalSection(&this->contact_search_lock);
}

MCONTACT __cdecl CSteamProto::AddToList(int flags, PROTOSEARCHRESULT* psr)
{
	return 0;
}

MCONTACT __cdecl CSteamProto::AddToListByEvent(int flags, int iContact, HANDLE hDbEvent)
{
	return 0;
}

int __cdecl CSteamProto::Authorize(HANDLE hDbEvent)
{
	return 0;
}

int __cdecl CSteamProto::AuthDeny(HANDLE hDbEvent, const TCHAR* szReason)
{
	return 0;
}

int __cdecl CSteamProto::AuthRecv(MCONTACT hContact, PROTORECVEVENT* pre)
{
	return 0;
}

int __cdecl CSteamProto::AuthRequest(MCONTACT hContact, const TCHAR* szMessage)
{
	return 0;
}

HANDLE __cdecl CSteamProto::FileAllow(MCONTACT hContact, HANDLE hTransfer, const TCHAR* szPath ) 
{ 
	return 0;
}

int __cdecl CSteamProto::FileCancel(MCONTACT hContact, HANDLE hTransfer ) 
{
	return 0;
}

int __cdecl CSteamProto::FileDeny(MCONTACT hContact, HANDLE hTransfer, const TCHAR* szReason )
{
	return 0;
}

int __cdecl CSteamProto::FileResume( HANDLE hTransfer, int* action, const TCHAR** szFilename )
{
	return 0;
}

DWORD_PTR __cdecl CSteamProto:: GetCaps(int type, MCONTACT hContact)
{
	switch(type)
	{
	case PFLAGNUM_1:
		return PF1_IM;
	case PFLAGNUM_2:
		return PF2_ONLINE;
	case PFLAG_UNIQUEIDTEXT:
		return (DWORD_PTR)Translate("SteamID");
	case PFLAG_UNIQUEIDSETTING:
		return (DWORD_PTR)"SteamID";
	default:
		return 0;
	}
}

int __cdecl CSteamProto::GetInfo(MCONTACT hContact, int infoType ) { return 0; }

HANDLE __cdecl CSteamProto::SearchBasic(const TCHAR* id)
{
	return 0;
}

HANDLE __cdecl CSteamProto::SearchByEmail(const TCHAR* email)
{
	return 0;
}

HANDLE __cdecl CSteamProto::SearchByName(const TCHAR* nick, const TCHAR* firstName, const TCHAR* lastName)
{
	return 0;
}

HWND __cdecl CSteamProto::SearchAdvanced( HWND owner ) { return 0; }

HWND __cdecl CSteamProto::CreateExtendedSearchUI( HWND owner ){ return 0; }

int __cdecl CSteamProto::RecvContacts(MCONTACT hContact, PROTORECVEVENT* pre) 
{
	return 0;
}

int __cdecl CSteamProto::RecvFile(MCONTACT hContact, PROTORECVFILET* pre) 
{
	return 0;
}

int __cdecl CSteamProto::RecvMsg(MCONTACT hContact, PROTORECVEVENT* pre)
{
 return 0;
}

int __cdecl CSteamProto::RecvUrl(MCONTACT hContact, PROTORECVEVENT *) { return 0; }

int __cdecl CSteamProto::SendContacts(MCONTACT hContact, int flags, int nContacts, MCONTACT *hContactsList)
{
	return 0;
}

HANDLE __cdecl CSteamProto::SendFile(MCONTACT hContact, const TCHAR *szDescription, TCHAR **ppszFiles)
{
	return 0;
}

int __cdecl CSteamProto::SendMsg(MCONTACT hContact, int flags, const char *msg)
{
	return 0;
}

int __cdecl CSteamProto::SendUrl(MCONTACT hContact, int flags, const char *url) { return 0; }

int __cdecl CSteamProto::SetApparentMode(MCONTACT hContact, int mode) { return 0; }

int CSteamProto::SetStatus(int new_status)
{
	if (new_status == m_iDesiredStatus)
		return 0;

	int old_status = m_iStatus;
	m_iDesiredStatus = new_status;

	if (new_status == ID_STATUS_OFFLINE)
	{
		m_bTerminated = true;

		m_iStatus = m_iDesiredStatus = ID_STATUS_OFFLINE;
		ProtoBroadcastAck(NULL, ACKTYPE_STATUS, ACKRESULT_SUCCESS, (HANDLE)old_status, m_iStatus);

		if (!Miranda_Terminated())
		{
			/*this->SetAllContactStatus(ID_STATUS_OFFLINE);
			this->CloseAllChatSessions();*/
		}

		return 0;
	}
	else
	{
		if (old_status == ID_STATUS_OFFLINE/* && !this->IsOnline()*/)
		{
			UINT64 id = 76561197960435530;
			DWORD in_db = id;
			id = in_db;

			m_iStatus = ID_STATUS_CONNECTING;
			ForkThread(&CSteamProto::LogInThread, NULL);

				//ptrA steamId(getStringA("SteamID"));
				//Steam::FriendList(m_hNetlibUser/*, token*/)
				//	.LoadAsync(steamId, CallbackConverter<Steam::FriendList::Result, &CSteamProto::OnContactListLoadedAsync>, this);
		}
		else
		{
			/*if ( this->account->IsOnline())
			{
				SetServerStatus(new_status);
				return 0;
			}*/

			ProtoBroadcastAck(NULL, ACKTYPE_STATUS, ACKRESULT_SUCCESS, (HANDLE)old_status, m_iStatus);

			return 0;
		}
	}

	ProtoBroadcastAck(NULL, ACKTYPE_STATUS, ACKRESULT_SUCCESS, (HANDLE)old_status, m_iStatus);

	return 0;
}

HANDLE __cdecl CSteamProto::GetAwayMsg(MCONTACT hContact) { return 0; }
int __cdecl CSteamProto::RecvAwayMsg(MCONTACT hContact, int mode, PROTORECVEVENT *evt) { return 0; }
int __cdecl CSteamProto::SetAwayMsg(int m_iStatus, const TCHAR *msg) { return 0; }

int __cdecl CSteamProto::UserIsTyping(MCONTACT hContact, int type)
{
	return 0;
}

int __cdecl CSteamProto::OnEvent(PROTOEVENTTYPE eventType, WPARAM wParam, LPARAM lParam)
{
	switch (eventType)
	{
	case EV_PROTO_ONLOAD:
		return this->OnModulesLoaded(wParam, lParam);

	case EV_PROTO_ONEXIT:
		return this->OnPreShutdown(wParam, lParam);

	case EV_PROTO_ONOPTIONS:
		return this->OnOptionsInit(wParam, lParam);

	/*case EV_PROTO_ONCONTACTDELETED:
		return this->OnContactDeleted(wParam, lParam);*/

	/*case EV_PROTO_ONMENU:
		this->OnInitStatusMenu();
		break;*/
	}

	return 1;
}
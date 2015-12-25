#pragma once
#include <Networking/General/SG_ClientSession.h>
#include <Packets/MMO/Social/SocialPackets.h>
class SG_SocialHandler
{
public:
	static void HandleMSN(const boost::shared_ptr<SG_ClientSession> Session);
	static void FindUser(const boost::shared_ptr<SG_ClientSession> Session, const MM_SC_MSN_FIND_USER* packet);
	static void FriendRequest(const boost::shared_ptr<SG_ClientSession> Session, const MM_SC_FRIEND_REQUEST* packet);
	static void CreateClan(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_CLAN_CREATION* packet);
};


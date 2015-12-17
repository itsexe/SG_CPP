#include "SG_LobbyHandler.h"
#include "../../SG_Config.h"
#include "../../Tools/SG_Logger.h"
#include "../../Tools/Encryption/DesPasswordCipher.h"
#include "../../Tools/SG_DataConverter.h"
#include "../../Packets/Auth/LoginPackets.h"
#include "../../Packets/Auth/LoginPacketsResponse.h"
#include "../../Packets/MMO/MMOPacketsResponse.h"


void SG_LobbyHandler::HandleLogin(const boost::shared_ptr<SG_ClientSession> Session, const BM_SC_LOGIN* packet)
{
	BM_SC_LOGIN_RESP response;
	BM_SC_LOGIN_RESP::initMessage<BM_SC_LOGIN_RESP>(&response);
	Session->SendPacketStruct(&response);
}

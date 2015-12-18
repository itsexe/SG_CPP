
#pragma once
#include <Networking/General/SG_ClientSession.h>

class SG_QuizHandler
{
public:
	static void EnterOX(const boost::shared_ptr<SG_ClientSession> Session);
	static void LeaveOX(const boost::shared_ptr<SG_ClientSession> Session);
};


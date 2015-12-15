#include "SG_Client.h"
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <random>


SG_Client::SG_Client()
{
	strChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	playerid = 0;
	charcreated = 0;
	chartype = 0;
	charlevel = 0;
	IsInOX = false;
	//Generate a new Sessionkey
	const auto now = boost::posix_time::second_clock::local_time();
	std::default_random_engine engine;
	engine.seed(static_cast<uint32_t>(now.time_of_day().total_milliseconds()));
	std::uniform_int_distribution<uint32_t> distribution(0, strChars.length() - 1);
	for (auto i = 0; i != 32; ++i)
	{
		SessionKey.push_back(strChars[distribution(engine)]);
	}

	//Update tricklist
	// Basic tricks
	tricks[0] = sg_constructor::Trickconstructor(1000,5, 1);	// Grind
	tricks[1] = sg_constructor::Trickconstructor(1100,3, 1);	// Dash
	tricks[2] = sg_constructor::Trickconstructor(1200,2, 1);	// Back Skating
	tricks[3] = sg_constructor::Trickconstructor(1300,4, 1);	// Butting
	tricks[4] = sg_constructor::Trickconstructor(1400,0, 1);	// Power Slide

	// Extended stuff
	tricks[5] = sg_constructor::Trickconstructor(1500,0, 1);	// Back Flip
	tricks[6] = sg_constructor::Trickconstructor(1600,0, 1);	// Front Flip
	tricks[7] = sg_constructor::Trickconstructor(1700,0, 1);	// Air Twist
	tricks[8] = sg_constructor::Trickconstructor(1800,0, 1);	// Power Swing
	tricks[9] = sg_constructor::Trickconstructor(1900,0, 1);	// Grip Turn
	tricks[10] = sg_constructor::Trickconstructor(2000,0, 1);	// Jumping Steer
	tricks[11] = sg_constructor::Trickconstructor(2100,0, 1);	// Power Jump
	tricks[12] = sg_constructor::Trickconstructor(5000,0, 1);	// Wallride

	for (auto i = 55001; i <= 55045; ++i)
	{
		missions.push_back(i);
	}
	/*items.push_back(Item(1, 2075, 0, 10, 0, 0, 0));
	items.push_back(Item(2, 2042, 0, 10, 0, 0, 0));
	items.push_back(Item(3, 1079, 0, 10, 0, 0, 0));
	items.push_back(Item(4, 1070, 0, 10, 0, 0, 0));
	items.push_back(Item(5, 2541, 0, 10, 0, 0, 0));*/
	//Set current Time as last KeepAlive
	UpdateLastKeepAlive();
}

void SG_Client::UpdateLastKeepAlive()
{
	LastKeepAlive = time_t(0);
}

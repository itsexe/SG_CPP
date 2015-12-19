#include "SG_Client.h"
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <random>
#include <Networking/General/SG_ClientSession.h>


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
	tricks.push_back(sg_constructor::Trickconstructor(1000, 5, 1));		// Grind
	tricks.push_back(sg_constructor::Trickconstructor(1100, 4, 1));		// Back Flip
	tricks.push_back(sg_constructor::Trickconstructor(1200, 5, 1));		// Front Flip
	tricks.push_back(sg_constructor::Trickconstructor(1300, 5, 1));		// Air Twist
	tricks.push_back(sg_constructor::Trickconstructor(1400, 4, 1));		// Power Swing
	tricks.push_back(sg_constructor::Trickconstructor(1500, 3, 1));		// Grip Turn
	tricks.push_back(sg_constructor::Trickconstructor(1600, 3, 1));		// Dash
	tricks.push_back(sg_constructor::Trickconstructor(1700, 3, 1));		// Back Skating
	tricks.push_back(sg_constructor::Trickconstructor(1800, 3, 1));		// Jumping Steer
	tricks.push_back(sg_constructor::Trickconstructor(1900, 5, 1));		// Butting
	tricks.push_back(sg_constructor::Trickconstructor(2000, 0, 1));		// Power Slide
	tricks.push_back(sg_constructor::Trickconstructor(2200, 3, 1));		// Power Jump
	tricks.push_back(sg_constructor::Trickconstructor(5000, 4, 1));		// Wall Ride
	
	for (auto i = 55001; i <= 55045; ++i)
	{
		missions.push_back(i);
	}
	items.push_back(sg_constructor::Item(1, 2075, 0, 10, 0, 0, 0));
	items.push_back(sg_constructor::Item(2, 2042, 0, 10, 0, 0, 0));
	items.push_back(sg_constructor::Item(3, 1079, 0, 10, 0, 0, 0));
	items.push_back(sg_constructor::Item(4, 1070, 0, 10, 0, 0, 0));
	items.push_back(sg_constructor::Item(5, 2541, 0, 10, 0, 0, 0));
	//Set current Time as last KeepAlive

	head = 1067;
	face = 0;
	upper = 2160;
	lower = 3140;
	foot = 3569;
	hand = 2582;
	google = 4557;
	accesoire = 4055;
	theme = 0;
	mantle = 0;
	buckle = 0;
	vent = 0;
	nitro = 0;
	wheels = 0;

	UpdateLastKeepAlive();
}

void SG_Client::UpdateLastKeepAlive()
{
	LastKeepAlive = time_t(0);
}

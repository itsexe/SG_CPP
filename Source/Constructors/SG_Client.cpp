#include "SG_Client.h"
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <random>
#include "Trick.h"


SG_Client::SG_Client()
{
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
	tricks.push_back(Trickconstructor(1000, 1));	// Grind
	tricks.push_back(Trickconstructor(1600, 1));	// Dash
	tricks.push_back(Trickconstructor(1700, 1));	// Back Skating
	tricks.push_back(Trickconstructor(1900, 1));	// Butting
	tricks.push_back(Trickconstructor(2000, 1));	// Power Slide

	// Extended stuff
	tricks.push_back(Trickconstructor(1100, 1));	// Back Flip
	tricks.push_back(Trickconstructor(1200, 1));	// Front Flip
	tricks.push_back(Trickconstructor(1300, 1));	// Air Twist
	tricks.push_back(Trickconstructor(1400, 1));	// Power Swing
	tricks.push_back(Trickconstructor(1500, 1));	// Grip Turn
	tricks.push_back(Trickconstructor(1800, 1));	// Jumping Steer
	tricks.push_back(Trickconstructor(2200, 1));	// Power Jump
	tricks.push_back(Trickconstructor(5000, 1));	// ???

	//Set current Time as last KeepAlive
	UpdateLastKeepAlive();
}

void SG_Client::UpdateLastKeepAlive()
{
	LastKeepAlive = time_t(0);
}

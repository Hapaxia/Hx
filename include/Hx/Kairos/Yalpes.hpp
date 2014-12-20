//////////////////////////////////////////////////////////////////////////////
//
// Hx
// --
//
// Kairos
//
// Copyright(c) 2014 M.J.Silk
//
// This software is provided 'as-is', without any express or implied
// warranty.In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions :
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software.If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// M.J.Silk
// MJSilk2@gmail.com
//
//////////////////////////////////////////////////////////////////////////////

#ifndef HX_KAIROS_YALPES_HPP
#define HX_KAIROS_YALPES_HPP

#include <vector>
#include <string>
#include <algorithm> // for std::sort
#include <ostream>
#include "Absorel.hpp"
#include "Duration.hpp"
#include "Stopwatch.hpp"

namespace hx
{
	namespace Kairos
	{
		namespace Yalpes
		{

template <typename TData>
// An event stores 1 int, 1 double, 1 unsigned int, and 1 of the passed-in datatype
struct Event
{
	Absorel position{ { 0, 0.0 } };
	unsigned int type{ 0u };
	TData data;

	bool operator<(const Event<TData>& e); // allows sorting of the events (sorts using position)
	bool operator>(const Event<TData>& e);
};

template <typename TData>
// Individual track of events that run in parallel with the other tracks
class Track
{
public:
	std::vector<Event<TData>> events;
	std::vector<Event<TData>> eventQueue;
	std::vector<Event<TData>> eventsWaiting;

	Track();
	void activate();
	void deactivate();
	bool isActivated();

private:
	bool m_isActivated{ true };

	void setActivated(bool activated);
};


template <typename TData>
// Yalpes (playback event sequence) engine (v1.0.0)
class Engine
{
public:
	std::vector<Track<TData>> tracks;

	Engine();
	void update();

	void moveEventsInQueueBeforeCurrentPositionToWaiting();
	void prepareEventQueue();

	void play();
	void stop();
	void pause();

	void seek(unsigned int positionAbsolute);
	void seek(unsigned int positionAbsolute, double positionRelative);
	void seek(const Absorel& position);
	void rewind();

	void setSpeed(double speed);
	void setSubsteps(unsigned int substeps);

	void automaticallyRemoveWaitingEventsOnNextUpdate();
	void doNotAutomaticallyRemoveWaitingEventsOnNextUpdate();

	bool isPlaying();
	Absorel getPosition();
	Duration getPlayTime();
	double getSpeed();
	unsigned int getSubsteps();
	std::string stringFromPosition(const Absorel& position);
	unsigned int getNumberOfTracks();
	unsigned int getNumberOfActiveTracks();

private:
	bool m_doAutomaticallyRemoveWaitingEventsOnNextUpdate{ true };
	bool m_isPlaying{ false };
	Stopwatch m_playbackClock;
	double m_speed{ 1.0 };
	unsigned int m_substeps{ 4u };
	Absorel m_currentPosition{ { 0, 0.0 } };
	Absorel m_playbackStartingPosition{ { 0, 0.0 } };
	unsigned int m_lengthInSteps{ 0u };

	bool sortEventsByPosition(const Event<TData>& lhs, const Event<TData>& rhs);

	void orderEvents(std::vector<Event<TData>>& events);
	std::string stringFromPositionWithSubsteps(const Absorel& position, unsigned int substeps);
	void resetEventsWaiting();
};

#include "Yalpes.inl"

		} // namespace Yalpes
	} // namespace Kairos
} // namespace hx

#endif // HX_KAIROS_YALPES_HPP
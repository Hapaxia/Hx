//////////////////////////////////////////////////////////////////////////////
//
// Hx
// --
//
// Kairos
//
// Copyright(c) 2015 M.J.Silk
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

#ifndef HX_KAIROS_YALPES_INL
#define HX_KAIROS_YALPES_INL

/***********************************
*                                  *
*  YALPES TEMPLATE IMPLEMENTATION  *
*                                  *
***********************************/

template <typename TData>
Engine<TData>::Engine()
{
	tracks.resize(1);
}

template <typename TData>
void Engine<TData>::update()
{
	if (m_isPlaying)
	{
		if (m_currentPosition > Absorel{ m_lengthInSteps })
		{
			pause();
			rewind();
		}
		else
		{
			double currentPlayClock = getPlayTime().asSeconds();
			m_currentPosition = m_playbackStartingPosition + Absorel{ currentPlayClock * m_speed };
			if (m_doAutomaticallyRemoveWaitingEventsOnNextUpdate)
				resetEventsWaiting();
			moveEventsInQueueBeforeCurrentPositionToWaiting();
		}
	}
}

template <typename TData>
void Engine<TData>::moveEventsInQueueBeforeCurrentPositionToWaiting()
{
	for (auto& track : tracks)
	{
		unsigned int numberOfEventsToRemove{ 0u };

		// copy to events waiting
		for (auto& e : track.eventQueue)
		{
			if (e.position < m_currentPosition)
			{
				track.eventsWaiting.push_back(e);
				numberOfEventsToRemove++;
			}
		}

		// remove from events queue
		if (numberOfEventsToRemove > 0)
			track.eventQueue.erase(track.eventQueue.begin(), track.eventQueue.begin() + numberOfEventsToRemove);
	}
}

template <typename TData>
void Engine<TData>::prepareEventQueue()
{
	unsigned int latestStep{ 0u };
	resetEventsWaiting();
	for (auto& track : tracks)
	{
		track.eventQueue.clear();
		for (auto& e : track.events)
		{
			track.eventQueue.push_back(e);
			if (latestStep < (e.position.absolute + e.position.relative))
				latestStep = static_cast<int>(ceil(e.position.absolute + e.position.relative));
		}
		orderEvents(track.eventQueue);
	}
	moveEventsInQueueBeforeCurrentPositionToWaiting();
	resetEventsWaiting();
	m_lengthInSteps = latestStep;
}

template <typename TData>
void Engine<TData>::play()
{
	m_playbackStartingPosition = m_currentPosition;
	prepareEventQueue();
	m_isPlaying = true;
	m_playbackClock.restart();
}

template <typename TData>
void Engine<TData>::stop()
{
	pause();
	rewind();
}

template <typename TData>
void Engine<TData>::pause()
{
	moveEventsInQueueBeforeCurrentPositionToWaiting();
	resetEventsWaiting();
	m_isPlaying = false;
}

template <typename TData>
void Engine<TData>::seek(unsigned int positionAbsolute)
{
	seek(positionAbsolute, 0.0);
}

template <typename TData>
void Engine<TData>::seek(const Absorel& position)
{
	seek(position.absolute, position.relative);
}

template <typename TData>
void Engine<TData>::seek(unsigned int positionAbsolute, double positionRelative)
{
	const unsigned int MIN_STEP{ 0u };
	if ((positionAbsolute < MIN_STEP) || (positionRelative + positionAbsolute < MIN_STEP))
	{
		positionAbsolute = MIN_STEP;
		positionRelative = 0.0;
	}
	m_currentPosition = { positionAbsolute, positionRelative };
	m_playbackStartingPosition = m_currentPosition;
	pause();
}

template <typename TData>
void Engine<TData>::rewind()
{
	seek(0);
}

template <typename TData>
bool Engine<TData>::isPlaying()
{
	return m_isPlaying;
}

template <typename TData>
Absorel Engine<TData>::getPosition()
{
	return m_currentPosition;
}

template <typename TData>
Duration Engine<TData>::getPlayTime()
{
	return m_playbackClock.getTime();
}

template <typename TData>
double Engine<TData>::getSpeed()
{
	return m_speed;
}

template <typename TData>
unsigned int Engine<TData>::getSubsteps()
{
	return m_substeps;
}

template <typename TData>
unsigned int Engine<TData>::getNumberOfTracks()
{
	return tracks.size();
}

template <typename TData>
unsigned int Engine<TData>::getNumberOfActiveTracks()
{
	unsigned int total{ 0u };
	for (auto& track : tracks)
	{
		if (track.getActivated())
			++total;
	}
	return total;
}


template <typename TData>
void Engine<TData>::setSpeed(double speed)
{
	const double MIN_SPEED = 1.0;
	const double MAX_SPEED = 1000.0;
	if ((speed >= MIN_SPEED) && (speed <= MAX_SPEED))
		m_speed = speed;
}

template <typename TData>
void Engine<TData>::setSubsteps(unsigned int substeps)
{
	m_substeps = substeps;
}

template <typename TData>
std::string Engine<TData>::stringFromPosition(const Absorel& position)
{
	return stringFromPositionWithSubsteps(position, m_substeps);
}

template <typename TData>
void Engine<TData>::automaticallyRemoveWaitingEventsOnNextUpdate()
{
	m_automaticallyRemoveWaitingEventsOnNextUpdate = true;
}

template <typename TData>
void Engine<TData>::doNotAutomaticallyRemoveWaitingEventsOnNextUpdate()
{
	m_automaticallyRemoveWaitingEventsOnNextUpdate = false;
}

// PRIVATE

template <typename TData>
void Engine<TData>::orderEvents(std::vector<Event<TData>>& events)
{
	std::sort(events.begin(), events.end());
}

template <typename TData>
void Engine<TData>::resetEventsWaiting()
{
	for (auto& track : tracks)
		track.eventsWaiting.clear();
}

template <typename TData>
std::string Engine<TData>::stringFromPositionWithSubsteps(const Absorel& position, unsigned int substeps)
{
	return std::to_string(position.absolute) + ":" + std::to_string(static_cast<int>(floor(position.relative * substeps)));
}

























/*****************************************
*                                        *
*  YALPES TRACK TEMPLATE IMPLEMENTATION  *
*                                        *
*****************************************/

template <typename TData>
Track<TData>::Track()
{
}

template <typename TData>
void Track<TData>::activate()
{
	setActivated(true);
}

template <typename TData>
void Track<TData>::deactivate()
{
	setActivated(false);
}

template <typename TData>
bool Track<TData>::isActivated()
{
	return m_isActivated;
}

// PRIVATE

template <typename TData>
void Track<TData>::setActivated(bool isActivated)
{
	m_isActivated = isActivated;
	if (!m_isActivated)
	{
		eventQueue.clear();
		eventsWaiting.clear();
	}
}























/*****************************************
*                                        *
*  YALPES EVENT TEMPLATE IMPLEMENTATION  *
*                                        *
*****************************************/

template <typename TData>
bool Event<TData>::operator<(const Event<TData>& e)
{
	return (position.absolute + position.relative) < (e.position.absolute + e.position.relative);
}

template <typename TData>
bool Event<TData>::operator>(const Event<TData>& e)
{
	return (position.absolute + position.relative) > (e.position.absolute + e.position.relative);
}

#endif // HX_KAIROS_YALPES_INL
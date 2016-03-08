#pragma once

#include "stdafx.h"
#include "Playback.h"
#include "song.h"

PlaybackException::PlaybackException(const string& message) : message(message) {}
string& PlaybackException::what() { return message; }

Playback::Playback(Queue* q)
{
	queue = q;
	curSong = nullptr;
	music = new sf::Music();
}

Playback::~Playback()
{
	// Do not delete song or queue pointers here. The manager class will handle that
}

void Playback::setCurSong(song* song)
{
	bool wasPlaying(false);
	curSong = song;
	if (music->getStatus() == music->Playing) // To preserve play/pause state
		wasPlaying = true;
	music->stop();
	if (!music->openFromFile(song->getFileLocation()))
		throw PlaybackException("Could not open song file: " + curSong->getFileLocation());
	if (wasPlaying)
		music->play();
}

song* Playback::getCurSong()
{
	return curSong;
}

void Playback::playSong(song* song)
{
	curSong = song;
	if (!music->openFromFile(curSong->getFileLocation()))
		throw PlaybackException("Could not open song file: " + curSong->getFileLocation());
	music->play();
}

void Playback::pauseCurrentSong()
{
	music->pause();
}

int Playback::playCurrentSong()
{
	if (curSong) // If there's a current song
	{
		if (music->getStatus() != music->Playing)
			music->play();
		return 1;
	}
	return 0;
}

void Playback::stopCurrentSong()
{
	music->stop();
}

song* Playback::nextSong()
{
	bool wasPlaying(false);
	if (music->getStatus() == music->Playing) // To preserve play/pause state
		wasPlaying = true;
	curSong = queue->getNextSong();
	if (curSong)
	{
		if (!music->openFromFile(curSong->getFileLocation()))
			throw PlaybackException("Could not open song file: " + curSong->getFileLocation());
		//TODO: Notfiy queue that we are moving to next song
		if (wasPlaying)
			music->play();
	}
	return curSong;
}

song* Playback::prevSong()
{
	bool wasPlaying(false);
	if (music->getStatus() == music->Playing) // To preserve play/pause state
		wasPlaying = true;
	curSong = queue->getPrevSong();
	if (curSong)
	{
		if (!music->openFromFile(curSong->getFileLocation()))
			throw PlaybackException("Could not open song file: " + curSong->getFileLocation());
		//TODO: Notfiy queue that we are moving to prev song
		if (wasPlaying)
			music->play();
	}
	
	return curSong;
}

float Playback::getDuration()
{
	return music->getDuration().asSeconds();
}

float Playback::getCurSongPos()
{
	return music->getPlayingOffset().asSeconds();
}

bool Playback::isCurSongDone()
{
	if (music->getPlayingOffset().asSeconds() >= (music->getDuration().asSeconds() - 0.2f)) // If within 0.2 seconds of end
		return true;
	else
		return false;
}

bool Playback::isPlaying(){
	return (music->getStatus() == music->Playing);
}

void Playback::setCurSongPos(float position)
{
	music->setPlayingOffset(sf::seconds(position));
}
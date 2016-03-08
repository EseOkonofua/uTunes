#pragma once

#include "song.h"
#include "Queue.h"
#include <string>
#include <SFML/Audio.hpp>

using namespace std;

class Queue;

class PlaybackException
{
public:
	PlaybackException(const string& message);
	string& what();
private:
	string message;
};

class Playback
{
public:
	Playback(Queue* q);
	~Playback();
	void setCurSong(song* song); //Sets the Song parameter to be the current song but does not change play/pause state.
	song* getCurSong(); // Accessor for the curSong attribute.
	void playSong(song* song); //Sets the Song parameter to be the current song and begins playing the song. Notifies the Queue of the song change.
	void pauseCurrentSong(); // Pauses the current song if it was previously playing.
	int playCurrentSong(); // Plays the current song if it was previously paused. Returns success.
	void stopCurrentSong(); // Stops the current song.The SFML Music object closes the song file.
	song* nextSong(); // Gets the next song from the Queue and sets it as the current song. Preserves the play/pause state. Returns the new current song.
	song* prevSong(); // Gets the previous song from the Queue and sets it as the current song.Preserves the play / pause state.Returns the new current song.
	float getDuration(); // Returns length of the song in seconds.
	float getCurSongPos(); // Returns the current song's current position as afloat in seconds.
	bool isCurSongDone(); // Returns true if the current song has finished playing.Called by main polling loop to determine when to skip to next song.
	void setCurSongPos(float position); // Skips to specified position in song.Parameter should be an integer from 0 to 100.
	bool isPlaying(); //Returns true if there is a song currently playing.
private:
	song* curSong;
	Queue* queue;
	sf::Music* music;
};


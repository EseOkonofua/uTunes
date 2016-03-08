#pragma once
#include "song.h"
#include "tag.h"
#include "Backend.h"
#include <string>
#include <vector>
#include <deque>

using namespace std;

class QueueException
{
public:
	QueueException(const string& message);
	string& what();
private:
	string message;
};

class Queue
{
public:
	Queue();
	song* getNextSong();
	vector<song*>* getQueue();
	void updateQueue();
	song* getPrevSong();
	void deleteSong(int position);
	song* getSong(int position);
	void randomSong();
	void regenerate(vector<tag*>* activeTags);
	int randInt(int upperLimit) const;
	void setCurSong(vector<song*>* library, int index);
	void queueTest();
	int getQueueLength();
	void setNextSong(song* s);	//Pushes the queue back and then inserts the song at the front pos.
	void addToQueue(song* s);
	void removeSongFromQueue(const int i);

private:
	vector<song*>* songList;
	deque<song*> playedSongs;
};

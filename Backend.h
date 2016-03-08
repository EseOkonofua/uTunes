// Backend.h

#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include "Queue.h"
#include "Playback.h"
#include "Library.h"
#include "tag.h"
#include "song.h"
#include <SFML\Audio.hpp>
#include <SFML\Audio\Music.hpp>

using namespace System;
class Queue;
class Playback;

namespace Backend {

	public value struct SongStruct{
		String^ title;
		String^ artist;
		String^ album;
		String^ address;
		int index;
		bool markedForDelete;
	} typedef SongStruct;

	public ref class Manager
	{
	public:
		Manager();
		~Manager();
		void pauseMusic();
		bool playMusic();
		void nextSong();
		void prevSong();
		void setSong(const int index);
		void addSong(SongStruct songStruct);
		void exit();
		
		void regenerateQueue();
		bool isPlaying();

		String^ getActiveTag(const int i);	

		//FUNCTIONS FOR GUI ONLY
		int numberOfSongs();
		SongStruct getCurrentSong();
		SongStruct getLibrarySong(const int i);
		SongStruct getQueueSong(const int i);
		int getQueueLength();
		void deleteSong(const int i);
		int getProgress();
		int getSongLength();
		void setSongPosition(float pct);
		int numberOfActiveTags();
		vector<tag*>* getActiveTags();
		int numberOfTags();
		String^ getTag(const int i);
		bool activateTag(String^ tagName);
		bool deactivateTag(String^ tagName);
		void addTag(String^ newTag);
		void addSongToTag(String^ tagName, const int i);	//i is library index
		int getNumberOfSongsInTag(String^ tagName);
		SongStruct getSongInTag(String^ tagName, const int i);
		bool tagAlreadyExists(String^ tagName);
		void deleteTag(String^ tag);
		void deleteSongFromTag(String^ tagName, const int i); //i is location i library

		int getNumberOfTagsInSong(const int songLibNum);
		String^ getTagInSong(const int songLibNum, const int tagNum);
		void removeSongFromTag(String^ tagName, const int i);

		void setNextSong(const int i);
		void addSongToQueue(const int i);

		void Manager::playSongFromQueue(const int queueNum);	//Redraw queuebox after calling
		void Manager::removeSongFromQueue(const int queueNum);	//Redarqueue box after calling.
		void Manager::setNextFromQueue(const int queueNum);
		void Manager::addSongToQueueFromQueue(const int queueNum);

	private:
		Queue* queue;
		Playback* playback;
		library* lib;
		map<string, tag*>* activeTags;

		SongStruct ptr2struct(song* ptr, const int i);
		string sys2c(String^ str);
	};

	
}

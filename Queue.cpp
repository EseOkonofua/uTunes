//Author: Philip Cisneros
#pragma once

#include "stdafx.h"
#include "Queue.h"
#include "Backend.h"
#include "Library.h"
#include "time.h"



Queue::Queue() {
	songList = new vector<song*>();
	deque<song*> playedSongs;
}

vector<song*>* Queue::getQueue() {
	return Queue::songList;
}

song* Queue::getNextSong() {
	if (songList->size() < 1)
		return nullptr;
	song* s = songList->at(0);
	songList->erase(songList->begin());
	playedSongs.push_front(s);
	updateQueue();
	return s;
}

song* Queue::getPrevSong() {
	if (playedSongs.size()) {
		song* s = playedSongs.front();
		playedSongs.pop_front();
		return s;
	}
	else {
		return nullptr;
	}
}

void Queue::deleteSong(int position){
	songList->erase(songList->begin() + position);
}

song* Queue::getSong(int position){
	return songList->at(position % getQueueLength());
}

void Queue::regenerate(vector<tag*>* activeTags){
	songList = new vector<song*>();
	vector<song*> selectionSet;
	vector<tag*>* tags = activeTags;
	for (int i = 0; i < tags->size(); i++) {
		for (int j = 0; j < (tags->at(i)->getSongList()->size()); j++) {
			bool isDublicate = false;
			for (int k = 0; k < selectionSet.size(); k++){
				if (tags->at(i)->getSongList()->at(j)->getFileLocation() == selectionSet[k]->getFileLocation()){
					isDublicate = true;
					break;
				}

			}
			if (!isDublicate)
				selectionSet.push_back(tags->at(i)->getSongList()->at(j));
		}
	}
	const int upperLimit = selectionSet.size();
	for (int j = 0; j < upperLimit; j++) {
		int number = randInt(upperLimit - j);
		songList->push_back(selectionSet[number]);
		selectionSet.erase(selectionSet.begin() + number);
	}
}

void Queue::updateQueue(){
	songList->push_back(playedSongs.front());
	if (playedSongs.size() == 20)
		playedSongs.pop_back();
}

int Queue::randInt(int upperLimit) const {
	srand(time(NULL));
	rand();
	rand();
	rand();
	return int(1.0 * upperLimit * rand() / RAND_MAX);

}

void Queue::setCurSong(vector<song*>* library, int index){

	playedSongs.push_front(library->at(index));

}

void Queue::queueTest() {
	vector<tag*>* temp = new vector<tag*>();
	song* songTest1 = new song("Wild Ones", "ACDC", "I dont know", temp, "Wild Ones.wav", "");
	song* songTest2 = new song("Airplanes", "ACDC", "I dont know", temp, "Airplanes.wav", "");
	song* songTest3 = new song("Payphone", "ACDC", "I dont know", temp, "Payphone.wav", "");

	songList->push_back(songTest1);
	songList->push_back(songTest2);
	songList->push_back(songTest3);
}

int Queue::getQueueLength() {
	return songList->size();
}

void Queue::setNextSong(song* s){
	for (int i = songList->size() - 1; i > 0; i--)
		songList->at(i) = songList->at(i - 1);

	if (songList->size() > 0)
		songList->at(0) = s;
	else
		songList->push_back(s);
}

void Queue::addToQueue(song* s){
	if (songList->size() < 15)
		songList->push_back(s);
	else
		songList->at(14) = s;
}

// This is the main DLL file.
#pragma once
#include "stdafx.h"
#include <msclr\marshal_cppstd.h>
#include "Backend.h"

namespace Backend{
	
	Manager::Manager(){
			lib = new library();
			queue = new Queue();
			playback = new Playback(queue);
			activeTags = new map<string, tag*>();

			lib->createAllTag();
			activateTag("All");
			regenerateQueue();

	}
		Manager::~Manager(){
				delete queue;
				delete playback;
				delete activeTags;
				delete lib;
		}
		bool Manager::playMusic(){
				playback->playCurrentSong();
				return !playback->isCurSongDone();
		}

		bool Manager::isPlaying(){
			return playback->isPlaying();
		}
		void Manager::pauseMusic(){
				playback->pauseCurrentSong();
		}


		void Manager::setSong(const int index){
			if (index < lib->getSongList()->size()){
				playback->setCurSong(lib->getSongList()->at(index));
				queue->setCurSong(lib->getSongList(), index);
			}
			else
				std::cout << "Manager::setSong() index out of bounds." << endl;
		}

		void Manager::addSong(SongStruct songStruct){
			vector<tag*>* temp = new vector<tag*>();
			song* songTest2 = new song(msclr::interop::marshal_as<std::string>(songStruct.title), msclr::interop::marshal_as<std::string>(songStruct.artist), msclr::interop::marshal_as<std::string>(songStruct.album), temp, msclr::interop::marshal_as<std::string>(songStruct.address), "");
			lib->addSong(songTest2);
		}

		void Manager::nextSong(){
			playback->nextSong();
		}
		void Manager::prevSong(){
			playback->prevSong();
		}


		SongStruct Manager::getCurrentSong(){
			return ptr2struct(playback->getCurSong(), 0);
		}

		SongStruct Manager::getLibrarySong(const int i){
			vector<song*>* songList = lib->getSongList();
			song* ptr = songList->at(i);
			return ptr2struct(ptr, i);
		}

		SongStruct Manager::getQueueSong(const int i){
			song* ptr = queue->getSong(i);
			return ptr2struct(ptr, i);
		}

		int Manager::getQueueLength(){
			return queue->getQueueLength();
		}

		int Manager::numberOfSongs(){
			return lib->getSongList()->size();
		}

		SongStruct Manager::ptr2struct(song* ptr, const int i){
			SongStruct temp;
			if (ptr)
			{
				temp.title = gcnew String(ptr->getTitle().c_str());
				temp.artist = gcnew String(ptr->getArtist().c_str());
				temp.album = gcnew String(ptr->getAlbum().c_str());
				temp.address = gcnew String(ptr->getFileLocation().c_str());
				temp.index = i;
				temp.markedForDelete = ptr->markedForDelete;
			}
			else
			{
				temp.index = -1; //Indicate that song ptr was null
			}

			return temp;
		}

		void Manager::deleteSong(const int i){
			vector<song*>* songList = lib->getSongList();
			song* ptr = songList->at(i);
			ptr->markedForDelete = true;
		}

		void Manager::exit(){
			lib->saveToFile();
		}

		void Manager::regenerateQueue(){
			queue->regenerate(getActiveTags());
		}

		int Manager::getSongLength(){
			return (int)playback->getDuration();
		}

		int Manager::getProgress(){
			return (int)playback->getCurSongPos();
		}
		
		void Manager::setSongPosition(float pct) {
			playback->setCurSongPos(pct);
		}

		//For que
		vector<tag*>* Manager::getActiveTags(){
				vector<tag*>* tagList = new vector<tag*>();

				std::map<string, tag*>::iterator i = activeTags->begin();
				while (i != activeTags->end()){
					tagList->push_back(i->second);//first is key, second is value
					++i;
				}
				return tagList;
		}

		int Manager::numberOfActiveTags(){
			return getActiveTags()->size();
		}

		///ewwwww this is gross, so #inefficient
		String^ Manager::getActiveTag(const int i){
			vector<tag*>* tagList = getActiveTags();
			if (tagList->at(i)->markedForDelete)
				return "";
			return gcnew String(tagList->at(i)->getName().c_str());
		}

		int Manager::getNumberOfSongsInTag(String^ tagName){
			return lib->getTag(sys2c(tagName))->getSongList()->size();
		}

		SongStruct Manager::getSongInTag(String^ tagName, const int i){
			return ptr2struct(lib->getTag(sys2c(tagName))->getSongList()->at(i), i);
		}

		int Manager::numberOfTags(){
			return lib->getTagList()->size();
		}

		String^ Manager::getTag(const int i){
			if (lib->getTagList()->at(i)->markedForDelete)
				return "";
			return gcnew String(lib->getTagList()->at(i)->getName().c_str());
		}
		bool Manager::activateTag(String^ tagName){
			if (activeTags->find(sys2c(tagName)) != activeTags->end())
				return false;

			tag* ptr = lib->getTag(sys2c(tagName));
			activeTags->operator[](sys2c(tagName)) = ptr;
			return true;
		}
		bool Manager::deactivateTag(String^ tagName){
			if (activeTags->find(sys2c(tagName)) == activeTags->end())
				return false;
			activeTags->erase(sys2c(tagName));
			return true;
		}

		void Manager::addTag(String^ newTag){
			vector<song*>* ptr = new vector<song*>();
			tag* tagptr = new tag(sys2c(newTag));
			lib->addTag(tagptr, ptr);
		}

		void Manager::addSongToTag(String^ tagName, const int i){
			vector<song*>* tagSongList = lib->getTag(sys2c(tagName))->getSongList();
			song* songPtr = lib->getSongList()->at(i);
			int size = tagSongList->size();
			for (int j = 0; j <= size; j++){
				if (j == tagSongList->size()){	//If we are at the end of the list
					lib->getTag(sys2c(tagName))->getSongList()->push_back(lib->getSongList()->at(i));
				}

				else if (songPtr == tagSongList->at(j)){//If the ptrs match
					break;
				}
				cout << tagSongList->size() << endl;
			}

			vector<tag*>* songTagList = songPtr->getTagList();
			tag* tagPtr = lib->getTag(sys2c(tagName));
			size = songTagList->size();
			for (int j = 0; j <= size; j++){
				if (j == songTagList->size()){	//If we are at the end of the list
					lib->getSongList()->at(i)->addTag(lib->getTag(sys2c(tagName)));
				}

				else if (tagPtr == songTagList->at(j)){//If the ptrs match
					break;
				}
			}

			
		}

		void Manager::deleteTag(String^ tagName){
			deactivateTag(tagName);
			lib->getTag(sys2c(tagName))->markedForDelete = true;
		}
		//TODO
		void Manager::deleteSongFromTag(String^ tagName, const int i){
			//Removes song from tag
			vector<song*>* tagSongList = lib->getTag(sys2c(tagName))->getSongList();
			song* songPtr = lib->getSongList()->at(i);

			/*for (int i = 0; i < tagSongList->size(); i++)
			{
				if (songPtr == tagSongList->at(i))
				{
					tagSongList->erase(tagSongList->begin() + i);
				}
					
			}*/
			for (vector<song*>::iterator it = tagSongList->begin(); it != tagSongList->end(); it++){
				if (songPtr == *it){//If the ptrs match
					tagSongList->erase(it);
					break; // erasing ruins the iterator it will crash if we try to increment again
				}
			}

			//Remove tag from song
			vector<tag*>* songTagList = songPtr->getTagList();
			tag* tagPtr = lib->getTag(sys2c(tagName));
			for (vector<tag*>::iterator it = songTagList->begin(); it != songTagList->end(); it++){
				if (tagPtr == *it){//If the ptrs match
					songTagList->erase(it);
					break; // erasing ruins the iterator it will crash if we try to increment again
				}
			}
		}

		bool Manager::tagAlreadyExists(String^ tagName){
			return lib->hasTag(sys2c(tagName));
		}

		string Manager::sys2c(String^ str){
			return msclr::interop::marshal_as<std::string>(str);
		}

		int Manager::getNumberOfTagsInSong(const int songLibNum){
			song* songPtr = lib->getSongList()->at(songLibNum);
			return songPtr->getTagList()->size();
		}
		String^ Manager::getTagInSong(const int songLibNum, const int tagNum){
			return gcnew String(lib->getSongList()->at(songLibNum)->getTagList()->at(tagNum)->getName().c_str());
		}
		void Manager::setNextSong(const int i){
			song* s = lib->getSongList()->at(i);
			queue->setNextSong(s);
		}

		void Manager::addSongToQueue(const int i){
			song* s = lib->getSongList()->at(i);
			queue->addToQueue(s);
		}
		void Manager::removeSongFromTag(String^ tagName, const int indexInTagSongList)
		{
			//Removes song from tag
			vector<song*>* tagSongList = lib->getTag(sys2c(tagName))->getSongList();
			song* songPtr = tagSongList->at(indexInTagSongList);						/*Exact same as deleteSongFromTag except for this line*/

			for (vector<song*>::iterator it = tagSongList->begin(); it != tagSongList->end(); it++){
				if (songPtr == *it){//If the ptrs match
					tagSongList->erase(it);
					break; // erasing ruins the iterator it will crash if we try to increment again
				}
			}

			//Remove tag from song
			vector<tag*>* songTagList = songPtr->getTagList();
			tag* tagPtr = lib->getTag(sys2c(tagName));
			for (vector<tag*>::iterator it = songTagList->begin(); it != songTagList->end(); it++){
				if (tagPtr == *it){//If the ptrs match
					songTagList->erase(it);
					break; // erasing ruins the iterator it will crash if we try to increment again
				}
			}
		}

		void Manager::playSongFromQueue(const int queueNum){
			//removeSongFromQueue(queueNum);
			playback->setCurSong(queue->getSong(queueNum));
		}
		void Manager::removeSongFromQueue(const int queueNum){
			queue->deleteSong(queueNum);
		}
		void Manager::setNextFromQueue(const int queueNum){
			queue->setNextSong(queue->getSong(queueNum));
		}
		void Manager::addSongToQueueFromQueue(const int queueNum){
			queue->addToQueue(queue->getSong(queueNum));
		}

}




#include "Library.h"
#include "SFML\Audio.hpp"
#include "SFML\Audio\InputSoundFile.hpp"
#include <fstream>
#include <sstream>

//Library Exception
LibraryException::LibraryException(const string& message) :message(message){}
string& LibraryException::what(){ return message; }

///

library::library(){
	songs = new vector<song*>();
	tagMap = new map<string, tag*>();
	loadFromFile();

	getTagList();
}

void library::createAllTag(){
	tag* allTag = new tag("All");
	allTag->songList = getSongList();
	tagMap->operator[]("All") = allTag;
}

void library::addTag(tag* newTag, vector<song*>* songList){
	if (tagMap->find(newTag->getName()) == tagMap->end()){ //does not contains tag
		for (int i = 0; i < songList->size(); i++)
			newTag->addSong(songList->at(i));
		tagMap->operator[](newTag->getName()) = newTag;
	}
	else{
		for (int i = 0; i < songList->size(); i++)
			tagMap->operator[](newTag->getName())->addSong(songList->at(i));
	}

	for (int i = 0; i < songList->size(); i++)
		songList->at(i)->addTag(newTag);
}

tag* library::getTag(string& tagName){
	return tagMap->operator[](tagName);
}

void library::saveToFile(){
	time_t result = time(nullptr);

	ofstream uTunesLibrary;
	uTunesLibrary.open("song_data.csv", std::ofstream::trunc);
	if (uTunesLibrary.fail()){
		ofstream Log;
		Log.open("Log.txt");
		Log << asctime(localtime(&result)) << " Can not save to file song_data.csv" << endl;
		Log.close();
	}
	else if (uTunesLibrary.is_open()){
		for (int j = 0; j < songs->size(); j++){
			song* song = songs->at(j);

			if (song->markedForDelete)
				continue;

			string tagList;
			for (int i = 0; i < song->getTagList()->size(); i++){
				if (song->getTagList()->at(i)->markedForDelete)
					continue;
				if (i != song->getTagList()->size() - 1)
					tagList = tagList + song->getTagList()->at(i)->getName() + "|";
				else
					tagList = tagList + song->getTagList()->at(i)->getName();
			}
			uTunesLibrary << song->getFileLocation() << "," << song->getTitle() << "," << song->getAlbum() << "," << song->getArtist() << "," << tagList << endl;
		}
		
		uTunesLibrary.close();
	}
}

void library::loadFromFile(){
	string line;
	time_t result = time(nullptr);
	ifstream song_data("song_data.csv");
	if (song_data.fail()){
		ofstream Log;
		Log.open("Log.txt");
		Log << asctime(localtime(&result)) << "song_data file could not be opened" << endl;
		Log.close();
	}
	else if (song_data.is_open()){
		//getline(song_data, line); only need if we have headers
		cout << line << endl;
		while (getline(song_data, line))
		{
			vector<string> songdata;
			stringstream lineStream(line);
			string cell;
			while (getline(lineStream, cell, ',')){
				songdata.push_back(cell);
			}
			
			vector<tag*>* songTagList = new vector<tag*>();
			song* newsong = new song(songdata[1], songdata[3], songdata[2], songTagList, songdata[0], "");
			if (songdata.size() >= 5)
				parseTags(songdata[4], songTagList, newsong);
			songs->push_back(newsong);
		}
	}
}

void library::parseTags(string line, vector<tag*>* songTagList, song* newsong){
	vector<tag*>* tagList = new vector<tag*>();
	stringstream lineStream(line);
	string cell;

	while (getline(lineStream, cell, '|')){
		if (tagMap->find(cell) == tagMap->end()){ //does not contains cell
			tag* newTag = new tag(cell);
			newTag->addSong(newsong);
			tagMap->operator[](cell) = newTag;
			songTagList->push_back(newTag);
		}
		else{
			tagMap->operator[](cell)->addSong(newsong);
			songTagList->push_back(tagMap->operator[](cell));
		}
			//std::cout << "map contains key world!\n";
	}
}

vector<tag*>* library::getTagList(){
	vector<tag*>* tagList = new vector<tag*>();

	std::map<string, tag*>::iterator i = tagMap->begin();
	while(i != tagMap->end()){
		tagList->push_back(i->second);//first is key, second is value
		++i;
	}
	return tagList;
}


void library::addSong(song* songPtr){
	songs->push_back(songPtr);
}

vector<song*>* library::getSongList(){
	return songs;
}

bool library::hasTag(string tagName){
	return !(tagMap->find(tagName) == tagMap->end());
}

library::~library()
{
	/*Make sure song array gets saved to .csv file*/
}
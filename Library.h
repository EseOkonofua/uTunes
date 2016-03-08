#pragma once
#include "song.h"
#include "Stdafx.h"
#include "tag.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

class LibraryException{
	string message;
public:
	LibraryException(const string& message);
	string& what();
};

class library{
	vector<song*>* songs;
	int songLibrarySize;
	string filePath;
	std::map<string, tag*>* tagMap;
public:
	library();
	~library();
	vector<song*>* getSongList();
	vector<tag*>* getTagList();
	void importSongFolder(string& filePath);
	void addSong(song* songPtr);
	void deleteSong(song* song);
	void createTag(string& tagName);
	void deleteTag(string& tagName);
	void saveToFile();
	void addTag(tag* newTag, vector<song*>* songList);	//Adds songs to tag and tag to songs.
	tag* getTag(string& tagName);
	bool hasTag(string tagName);
	void createAllTag();

protected:	
	void loadFromFile();
	void deleteFromFile(song* song);
	void parseTags(string line, vector<tag*>* songTagList, song* newsong);
	
};
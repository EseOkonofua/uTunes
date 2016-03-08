#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include "tag.h"
using namespace std;
class tag;

class song{
public:
	bool markedForDelete;
	song();
	song(string title, string artist, string album, vector<tag*>* tagList, string fileLocation, string albumArtLocation);
	vector<tag*>* getTagList();
	void setTagList(vector<tag*>* tagList);
	void addTag(tag* newTag);
	string getFileLocation();
	void setFilelocation(string fileLocation);
	string getTitle();
	void setTitle(string title);
	string getArtist();
	void setArtist(string artist);
	string getAlbum();
	void setAlbum(string album);
	string getAlbumArtLocation();
	void setAlbumArtLocation(string albumArtLocation);
private:
	string title;
	string artist;
	string album;
	vector<tag*>* tagList;
	string fileLocation;
	string albumArtLocation;
	
};


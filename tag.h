#pragma once
#pragma once
#include "stdafx.h"
#include <vector>
#include <string>
#include "song.h"
using namespace std;

class song;

class tag
{
public:
	bool markedForDelete;

	tag(string name);
	vector<song*>* getSongList();
	void addSong(song* ptr);
	string getName();
	void setName(string name);
	string getDesc();
	void setDesc(string desc);
	vector<song*>* songList;
private:
	string name;
	string desc;
	
	
};


#pragma once

#include "stdafx.h"
#include "tag.h"


tag::tag(string name){
	tag::name = name;
	tag::songList = new vector<song*>();
	desc = "";
	markedForDelete = false;
}

vector<song*>* tag::getSongList(){
	return tag::songList;
}

void tag::addSong(song* ptr){
	songList->push_back(ptr);
}

string tag::getName(){
	return tag::name;
}

void tag::setName(string name){
	tag::name = name;
}

string tag::getDesc(){
	return tag::desc;
}

void tag::setDesc(string desc){
	tag::desc = desc;
}

#pragma once

#include "stdafx.h"
#include "song.h"
#include "tag.h"

song::song(){
	markedForDelete = false;
}

song::song(string title, string artist, string album, vector<tag*>* tagList, string fileLocation, string albumArtLocation) :
title(title), artist(artist), album(album), tagList(tagList), fileLocation(fileLocation), albumArtLocation(albumArtLocation) {
	markedForDelete = false;
}


vector<tag*>* song::getTagList(){
	return song::tagList;
}

void song::setTagList(vector<tag*>* tagList){
	song::tagList = tagList;
}

void song::addTag(tag* newTag){
	tagList->push_back(newTag);
}

string song::getFileLocation(){
	return song::fileLocation;
}

void song::setFilelocation(string fileLocation){
	song::fileLocation = fileLocation;
}

string song::getTitle(){
	return song::title;
}

void song::setTitle(string title){
	song::title = title;
}

string song::getArtist(){
	return song::artist;
}

void song::setArtist(string artist){
	song::artist = artist;
}

string song::getAlbum(){
	return song::album;
}

void song::setAlbum(string album){
	song::album = album;
}

string song::getAlbumArtLocation(){
	return song::albumArtLocation;
}

void song::setAlbumArtLocation(string albumArtLocation){
	song::albumArtLocation = albumArtLocation;
}
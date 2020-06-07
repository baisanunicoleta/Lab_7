#include "Film.h"

Film::Film(std::string newName, std::string newGenre, int newYear, int newLikes, std::string newLink) : name{std::move(newName)}, genre{std::move(newGenre)}, year{newYear}, likes{newLikes}, link{std::move(newLink)} {}

const std::string &Film::getName() const {
	return name;
}

int Film::getYear() const {
	return year;
}

const std::string &Film::getGenre() const {
	return genre;
}

int Film::getLikes() const {
	return likes;
}

void Film::setName(const std::string &name) {
	this->name = name;
}

const std::string &Film::getLink() const {
	return link;
}

void Film::setYear(int year) {
	this->year = year;
}

void Film::setLikes(int likes) {
	this->likes = likes;
}

void Film::setLink(const std::string &link) {
	this->link = link;
}

void Film::setGenre(const std::string &genre) {
	this->genre = genre;
}

std::string Film::toString() {
	return name + ',' + genre + ',' + std::to_string(year) + ',' + std::to_string(likes) + ','  + link;
}

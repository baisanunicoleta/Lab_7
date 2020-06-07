#include "Service.h"

std::vector<Film> Service::getAllFilms() {
	return storage->getAllFilms();
}

void Service::updateFilm(std::string title, std::string genre, int year, int likes, std::string link) {
	if(year < 1897 || year > 2020){
		throw ValidatorException("Invalid data!");
	}
	storage->updateFilm(Film(title, genre, year, likes, link));
}

void Service::deleteFilm(std::string title) {
	storage->removeFilm(title);
}

void Service::addFilm(std::string title, std::string genre, int year, int likes, std::string link) {
	if(year < 1897 || year > 2020 || likes < 0){
		throw ValidatorException("Invalid data!");
	}
	storage->addFilm(Film(title, genre, year, likes, link));
}

void Service::saveMyList(const std::string &name) {
	auto array = storage->getAllFilms();
	for (auto & arrayOfTape : array) {
		if (arrayOfTape.getName() == name) {
			myList->addFilm(arrayOfTape);
			return;
		}
	}
	throw ValidatorException("Element does not exist");
}

std::vector<Film> Service::getMyList() {
	return myList->getAllFilms();
}

void Service::setPath(const std::string &fileName, const std::string &repoName) {
	if (repoName == "mylist") {
		if (fileName == "memory"){
			myList = new MemoryRepository();
		}else if (fileName.substr(fileName.size() - 3) == "csv") {
			myList = new FileRepository(fileName);
		}else if (fileName.substr(fileName.size() - 4) == "html") {
			myList = new HTMLRepository(fileName);
		}else {

			throw ValidatorException("Invalid format");
		}
	}else if (repoName == "repository"){
		if (fileName == "memory"){
			storage = new MemoryRepository();
		}else if (fileName.substr(fileName.size() - 3) == "txt") {
			storage = new FileRepository(fileName);
		}else if (fileName.substr(fileName.size() - 4) == "html") {
			storage = new HTMLRepository(fileName);
		}else {
			throw ValidatorException("Invalid format");
		}
	}
}

Film Service::getCurrentElement() {
	return storage->getCurrent();
}

Service::~Service() {
	delete storage;
	delete myList;
}

Service::Service() {
	storage = nullptr;
	myList = nullptr;
}

std::vector<Film> Service::getFilteredList(std::string genre) {
	if (genre.empty()) {
		return myList->getAllFilms();
	}
	std::vector<Film> array;
	for (auto film: myList->getAllFilms()) {
		if (film.getGenre() == genre) {
			array.push_back(film);
		}
	}
	return array;
}

void Service::openMyList() {
	myList->openRepo();
}

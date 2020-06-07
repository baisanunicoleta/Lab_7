#include "MemoryRepository.h"
#include <algorithm>

void MemoryRepository::addFilm(Film newFilm) {
	for (const auto& film: array) {
		if (film.getName() == newFilm.getName()) {
			throw RepositoryException("Duplicate");
		}
	}
	array.push_back(newFilm);
}

void MemoryRepository::removeFilm(std::string name) {
	auto elementToRemove = std::find_if(array.begin(), array.end(), [name](const Film& film) {
		return film.getName() == name;
	});
	if (elementToRemove == array.end()) {
		throw RepositoryException("Element does not exist");
	}else {
		array.erase(elementToRemove);
	}

}

void MemoryRepository::updateFilm(Film newFilm) {
	for (auto& film: array) {
		if (film.getName() == newFilm.getName()) {
			film = newFilm;
			return;
		}
	}
	throw RepositoryException("Element does not exist");

}

std::vector<Film> MemoryRepository::getAllFilms() {
	return array;
}

void MemoryRepository::openRepo() {

}

Film MemoryRepository::getCurrent() {
	if (currentElement == array.size()) {
		currentElement = 0;
	}
	return *(array.begin() + currentElement++);
}

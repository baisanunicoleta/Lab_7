#ifndef LABBONUS_MEMORYREPOSITORY_H
#define LABBONUS_MEMORYREPOSITORY_H
#include "Repository.h"

class MemoryRepository: public Repository {
private:
	std::vector<Film> array;
	int currentElement = 0;
public:
	MemoryRepository() = default;;

	void addFilm(Film newFilm) override;

	void removeFilm(std::string name) override;

	void updateFilm(Film newFilm) override;

	std::vector<Film> getAllFilms() override;

	void openRepo() override;

	Film getCurrent() override;
};


#endif //LABBONUS_MEMORYREPOSITORY_H

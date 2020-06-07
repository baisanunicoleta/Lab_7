#ifndef LABBONUS_FILEREPOSITORY_H
#define LABBONUS_FILEREPOSITORY_H
#include "Repository.h"
#include <fstream>
class FileRepository: public Repository {
private:
	std::string fileName;
	void writeFile(std::vector<Film> filmsToWrite);
	std::vector<Film> readFile();
	int currentElement = 0;
public:
	explicit FileRepository(const std::string &fileName);

	void addFilm(Film newFilm) override;
	void removeFilm(std::string name) override;
	void updateFilm(Film newFilm) override;
	void openRepo() override;
	std::vector<Film> getAllFilms() override;

	Film getCurrent() override;
};


#endif //LABBONUS_FILEREPOSITORY_H

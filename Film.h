#ifndef LABBONUS_FILM_H
#define LABBONUS_FILM_H
#include <string>
#include <utility>

class Film {
private:
	std::string name;
	std::string genre;
	int year;
	int likes;
	std::string link;

public:
	Film() {
		name = "";
		genre = "";
		year = 0;
		likes = 0;
		link = "";
	}
	Film(std::string newName, std::string newGenre, int newYear, int newLikes, std::string newLink);

	const std::string &getName() const;

	int getYear() const;

	const std::string &getGenre() const;

	int getLikes() const;

	const std::string &getLink() const;

	void setName(const std::string &name);

	void setGenre(const std::string &genre);

	void setYear(int year);

	void setLikes(int likes);

	void setLink(const std::string &link);

	std::string toString();
};



#endif //LABBONUS_FILM_H

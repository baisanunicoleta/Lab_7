#include "GUI.h"
#include <iostream>

GUI::GUI(Service service1) : service{service1} {
	initGUI();
	makeConnections();
}

void GUI::initGUI() {
	addButton = new QPushButton{"Add"};
	removeButton = new QPushButton{"Remove"};
	updateButton = new QPushButton{"Update"};
	setPathStorage = new QPushButton{"Set Repo"};
	setPathMyList = new QPushButton{"Set My List"};
	setPathStorageB = new QPushButton{"Set Repo"};
	setPathMyListB = new QPushButton{"Set My List"};
	storageLineEdit = new QLineEdit{};
	storageLineEditB = new QLineEdit{};
	myListLineEdit = new QLineEdit{};
	myListLineEditB = new QLineEdit{};
	saveMyList = new QPushButton{"Save"};
	next = new QPushButton{"Next"};
	filterButton = new QPushButton{"Filter"};
	filterGenreLineEdit = new QLineEdit{};
	openMyList = new QPushButton{"Open"};
	nameLineEdit = new QLineEdit{};
	genreLineEdit = new QLineEdit{};
	yearLineEdit = new QLineEdit{};
	linkLineEdit = new QLineEdit{};
	likesLineEdit = new QLineEdit{};
	tabWidget = new QTabWidget{};

	filmsListWidget = new QListWidget{};
	filmsListWidgetB = new QListWidget{};
	myListWidget = new QListWidget{};

	auto* parentLayout = new QVBoxLayout{this};
	parentLayout->addWidget(tabWidget);

	auto* mainWidget = new QWidget{};
	auto* adminWidget = new QWidget{};

	auto* mainLayout = new QVBoxLayout{adminWidget};

	auto* setPathLayout = new QVBoxLayout{};

	auto* setRepoLayout = new QHBoxLayout{};
	setRepoLayout->addWidget(new QLabel{"Repository"});
	setRepoLayout->addWidget(storageLineEdit);
	setRepoLayout->addWidget(setPathStorage);
	setPathLayout->addLayout(setRepoLayout);
	auto* setMyListLayout = new QHBoxLayout{};
	setMyListLayout->addWidget(new QLabel{"My List"});
	setMyListLayout->addWidget(myListLineEdit);
	setMyListLayout->addWidget(setPathMyList);
	setPathLayout->addLayout(setMyListLayout);
	mainLayout->addLayout(setPathLayout);

	auto* adminMode = new QHBoxLayout{};
	auto* functionality = new QVBoxLayout{};

	auto* filmDetails = new QFormLayout{};
	filmDetails->addRow("Name", nameLineEdit);
	filmDetails->addRow("Genre", genreLineEdit);
	filmDetails->addRow("Year", yearLineEdit);
	filmDetails->addRow("Likes", likesLineEdit);
	filmDetails->addRow("Link", linkLineEdit);
	functionality->addLayout(filmDetails);

	auto* buttonsLayout = new QHBoxLayout{};
	buttonsLayout->addWidget(addButton);
	buttonsLayout->addWidget(removeButton);
	buttonsLayout->addWidget(updateButton);
	functionality->addLayout(buttonsLayout);
	adminMode->addLayout(functionality);
	adminMode->addWidget(filmsListWidget);

	mainLayout->addLayout(adminMode);
	adminWidget->setLayout(mainLayout);
	tabWidget->addTab(adminWidget, "Admin Mode");

	auto* modeBWidget = new QWidget{};
	auto* modeBLayout = new QVBoxLayout{};
	auto* setPathLayoutB = new QVBoxLayout{};

	auto* setRepoLayoutB = new QHBoxLayout{};
	setRepoLayoutB->addWidget(new QLabel{"Repository"});
	setRepoLayoutB->addWidget(storageLineEditB);
	setRepoLayoutB->addWidget(setPathStorageB);
	setPathLayoutB->addLayout(setRepoLayoutB);
	auto* setMyListLayoutB = new QHBoxLayout{};
	setMyListLayoutB->addWidget(new QLabel{"My List"});
	setMyListLayoutB->addWidget(myListLineEditB);
	setMyListLayoutB->addWidget(setPathMyListB);
	setPathLayoutB->addLayout(setMyListLayoutB);
	modeBLayout->addLayout(setPathLayoutB);

	auto* functionalityLayout = new QHBoxLayout{};
	functionalityLayout->addWidget(filmsListWidgetB);
	auto* buttonsMyList = new QVBoxLayout{};
	buttonsMyList->addWidget(saveMyList);
	buttonsMyList->addWidget(next);
	buttonsMyList->addWidget(openMyList);
	functionalityLayout->addLayout(buttonsMyList);

	functionalityLayout->addWidget(myListWidget);
	modeBLayout->addLayout(functionalityLayout);
	auto* filterLayout = new QHBoxLayout{};
	filterLayout->addWidget(filterButton);
	filterLayout->addWidget(filterGenreLineEdit);
	modeBLayout->addLayout(filterLayout);
	modeBWidget->setLayout(modeBLayout);
	tabWidget->addTab(modeBWidget, "User Mode");
}

void GUI::makeConnections() {
	QObject::connect(filmsListWidget, &QListWidget::itemSelectionChanged, [this]() {
		int selectedIndex = getSelectedFilm(filmsListWidget);
		if (selectedIndex < 0 ) {
			nameLineEdit->clear();
			genreLineEdit->clear();
			yearLineEdit->clear();
			likesLineEdit->clear();
			linkLineEdit->clear();
			return;
		}
		Film film = service.getAllFilms().at(selectedIndex);
		nameLineEdit->setText(QString::fromStdString(film.getName()));
		genreLineEdit->setText(QString::fromStdString(film.getGenre()));
		yearLineEdit->setText(QString::fromStdString(std::to_string(film.getYear())));
		likesLineEdit->setText(QString::fromStdString(std::to_string(film.getLikes())));
		linkLineEdit->setText(QString::fromStdString(film.getLink()));
	});
	QObject::connect(setPathStorage, &QPushButton::clicked, this, &GUI::setStorage);
	QObject::connect(setPathMyList, &QPushButton::clicked, this, &GUI::setMyList);
	QObject::connect(addButton, &QPushButton::clicked, this, &GUI::addFilm);
	QObject::connect(removeButton, &QPushButton::clicked, this, &GUI::removeFilm);
	QObject::connect(updateButton, &QPushButton::clicked, this, &GUI::updateFilm);
	QObject::connect(saveMyList, &QPushButton::clicked, this, &GUI::saveFilm);
	QObject::connect(next, &QPushButton::clicked, this, &GUI::nextFilm);
	QObject::connect(openMyList, &QPushButton::clicked, this, &GUI::openList);
	QObject::connect(filterButton, &QPushButton::clicked, this, &GUI::filterList);
	QObject::connect(setPathMyListB, &QPushButton::clicked, this, &GUI::setMyListB);
	QObject::connect(setPathStorageB, &QPushButton::clicked, this, &GUI::setStorageB);
}

int GUI::getSelectedFilm(QListWidget *listWidget) {
	QModelIndexList selectedIndexes = listWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.empty()) {
		return -1;
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}

void GUI::setStorage() {
	std::string path = storageLineEdit->text().toStdString();
	service.setPath(path, "repository");
//	populateList(filmsListWidget);
//	populateList(filmsListWidgetB);
	populateList();
}

void GUI::setMyList() {
	std::string path = myListLineEdit->text().toStdString();
	service.setPath(path, "mylist");
	populateMyList(service.getMyList());
}

void GUI::populateList() {
	filmsListWidget->clear();
	filmsListWidgetB->clear();
	std::vector<Film> array = service.getAllFilms();
	for (const auto& film: array) {
		filmsListWidget->addItem(QString::fromStdString(film.getName() + " - " + film.getGenre()));
		filmsListWidgetB->addItem(QString::fromStdString(film.getName() + " - " + film.getGenre()));

	}
}

void GUI::populateMyList(std::vector<Film> array) {
	myListWidget->clear();
	for (const auto& film: array) {
		myListWidget->addItem(QString::fromStdString(film.getName() + " - " + film.getGenre()));
	}
}

void GUI::setStorageB() {
	std::string path = storageLineEditB->text().toStdString();
	service.setPath(path, "repository");
//	populateList(filmsListWidget);
//	populateList(filmsListWidgetB);
	populateList();
}

void GUI::setMyListB() {
	std::string path = myListLineEditB->text().toStdString();
	service.setPath(path, "mylist");
	populateMyList(service.getMyList());
}

void GUI::filterList() {
	populateMyList(service.getFilteredList(filterGenreLineEdit->text().toStdString()));
}

void GUI::openList() {
	service.openMyList();
}

void GUI::nextFilm() {
	int selectedIndex = getSelectedFilm(filmsListWidgetB);
	if (selectedIndex < 0 or selectedIndex >= service.getAllFilms().size() - 1) {
		selectedIndex = 0;
	}else {
		selectedIndex++;
	}
	filmsListWidgetB->setCurrentRow(selectedIndex);
}

void GUI::saveFilm() {
	int selectedIndex = getSelectedFilm(filmsListWidgetB);
	if (selectedIndex < 0) {
		QMessageBox::critical(this, "Error", "No selected footage");
		return;
	}
	try {
		service.saveMyList(service.getAllFilms()[selectedIndex].getName());
		populateMyList(service.getMyList());

	}catch(...) {
		QMessageBox::critical(this, "Error", "Invalid");
	}
}

void GUI::updateFilm() {
	std::string newName = nameLineEdit->text().toStdString();
	std::string newGenre = genreLineEdit->text().toStdString();
	int year = std::stoi(yearLineEdit->text().toStdString());
	int likes = std::stoi(likesLineEdit->text().toStdString());
	std::string newLink = linkLineEdit->text().toStdString();
	try {
		service.updateFilm(newName, newGenre, year, likes, newLink);
	} catch (...) {
		QMessageBox::critical(this, "Error", "Invalid");
		return;
	}
//	populateList(filmsListWidget);
//	populateList(filmsListWidgetB);
	populateList();


	auto array = service.getAllFilms();
	int index = 0;
	for (const auto& film: array) {
		if (film.getName() == newName) {
			break;
		}
		index++;
	}
	filmsListWidget->setCurrentRow(index);
}

void GUI::removeFilm() {
	std::string name = nameLineEdit->text().toStdString();
	try {
		service.deleteFilm(name);
	} catch (...) {
		QMessageBox::critical(this, "Error", "Invalid");
		return;
	}
//	populateList(filmsListWidget);
//	populateList(filmsListWidgetB);
	populateList();
}


void GUI::addFilm() {
	std::string newName = nameLineEdit->text().toStdString();
	std::string newGenre = genreLineEdit->text().toStdString();
	int year = std::stoi(yearLineEdit->text().toStdString());
	int likes = std::stoi(likesLineEdit->text().toStdString());
	std::string newLink = linkLineEdit->text().toStdString();
	try {
		service.addFilm(newName, newGenre, year, likes, newLink);
	} catch (...) {
		QMessageBox::critical(this, "Error", "Invalid");
		return;
	}
//	populateList(filmsListWidget);
//	std::cout << "List1 populated" << std::endl;
//	populateList(filmsListWidgetB);
	populateList();

	int lastElement = static_cast<int>(service.getAllFilms().size() - 1);
	filmsListWidget->setCurrentRow(lastElement);
}


#pragma once
#include "header.h"

class Person {
private:
	std::string Vorname{};
	std::string Nachname{};
	std::string Geburtsdatum{};
	std::string Adresse{};
	std::string Postleitzahl{};
	std::string Telefonnummer{};

public:

	Person() {}

	void setVorname(std::string setVorname) {
		Vorname = setVorname;
	}
	void setNachname(std::string setNachname) {
		Nachname = setNachname;
	}
	void setGeburtsdatum(std::string setGeburtsdatum, bool& isVaild, bool FromFile = true) {
		if (FromFile) {
			Geburtsdatum = setGeburtsdatum;
		}
		else {

			bool isInt = true;
			std::stringstream iss(setGeburtsdatum);
			std::vector<std::string> tempstorage;

			while (iss.good())
			{
				std::string tempNumberStorage;
				getline(iss, tempNumberStorage, '.');
				tempstorage.push_back(tempNumberStorage);
			}

			bool validDay{ true }, validMonth{ true }, validYear{ true };

			int day{ 0 };
			int month{ 0 };
			int year{ 0 };
			try {
				day = std::stoi(tempstorage[0]);
				month = std::stoi(tempstorage[1]);
				year = std::stoi(tempstorage[2]);
			}
			catch (const std::invalid_argument& e) {
				isInt = false;
				isVaild = false;
				std::cout << std::endl << std::setw(65) << std::right << "[Invalid Date]" << std::endl;
			}
			if (isInt) {


				if (tempstorage.size() == 3 && day <= 31 && month <= 12) {
					if (1000 <= year <= 2023)
					{
						if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 0 && day <= 31) {
							validMonth = true;

						}
						else {
							if (month == 4 || month == 6 || month == 9 || month == 11 && day > 0 && day <= 30) {
								validMonth = true;
							}
							else {
								if (month == 2)
								{
									if ((year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) && day > 0 && day <= 29) {
										validYear = true;
									}
									else if (day > 0 && day <= 28) {
										validDay = true;
									}
									else {
										validDay = false;
										std::cout << std::endl << std::setw(65) << std::right << "[Invalid Day]" << std::endl;
									}
								}
								else {
									validMonth = false;
									std::cout << std::endl << std::setw(65) << std::right << "[Invalid Month]" << std::endl;
								}
							}
						}
					}
					else {
						validYear = false;
						std::cout << std::endl << std::setw(65) << std::right << "[Invalid Year]" << std::endl;
					}


					if (validDay && validMonth && validYear) {
						Geburtsdatum = std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
						isVaild = true;
					}
				}
				else {
					isVaild = false;
					std::cout << std::endl << std::setw(65) << std::right << "[Invalid Date]" << std::endl;
				}
			}
		}

	}
	void setAdresse(std::string setAdresse) {
		Adresse = setAdresse;
	}
	void setPostleitzahl(std::string setPostleitzahl) {
		Postleitzahl = setPostleitzahl;
	}
	void setTelefonnummer(std::string setTelefonnummer) {
		Telefonnummer = setTelefonnummer;
	}



	std::string getVorname() {
		return Vorname;
	}
	std::string getNachname() {
		return Nachname;
	}
	std::string getGeburtsdatum() {
		return Geburtsdatum;
	}
	std::string getAdresse() {
		return Adresse;
	}
	std::string getPostleitzahl() {
		return Postleitzahl;
	}
	std::string getTelefonnummer() {
		return Telefonnummer;
	}

};

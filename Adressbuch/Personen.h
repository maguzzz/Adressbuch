#pragma once
#include "header.cpp"
#include "Person.h"

class Personen
{
private:
	std::vector <Person> personen{};

public:


	Personen() {}

	int GetCount() {
		return personen.size();
	}

	void AddPerson(const Person& InputClass, bool PushDB = true) {
		MYSQL* conn;
		MYSQL_RES* res;
		MYSQL_ROW row;

		bool isDuplicate = false;
		std::string query;
		Person inputPerson = InputClass;

		if (PushDB) {
			conn = mysql_init(NULL);
			conn = mysql_real_connect(conn, "localhost", "root", "Student", "db_adressbuch", 3306, NULL, 0);
#
			std::string queryALL = "SELECT * FROM tb_user";

			mysql_query(conn, queryALL.c_str());

			MYSQL_RES* res = mysql_store_result(conn);

			while ((row = mysql_fetch_row(res))) {

				std::string inputVorname = inputPerson.getVorname();
				std::string inputGeburtstag = inputPerson.getGeburtsdatum();
				std::string inputTelefon = inputPerson.getTelefonnummer();

				std::string refVorname = row[1];
				std::string refGeburtstag = row[3];
				std::string refTelefon = row[6];

				if ((refVorname == inputVorname) && (refGeburtstag == inputGeburtstag) && (refTelefon == inputTelefon)) {
					isDuplicate = true;
					break;
				}
			}
			if (!isDuplicate) {
				query = "INSERT INTO tb_user (firstN, lastN, birthdate, street, plz, number) VALUES ('" + inputPerson.getVorname() + "' , '" + inputPerson.getNachname() + "', '" + inputPerson.getGeburtsdatum() + "', '" + inputPerson.getAdresse() + "', '" + inputPerson.getPostleitzahl() + "', '" + inputPerson.getTelefonnummer() + "')";

				if (mysql_query(conn, query.c_str()) != 0) {

					std::cout << std::endl << std::setw(65) << std::right << "[ERROR ADDING USERT TO DB]" << std::endl << std::endl;
				}
				else {

					personen.push_back(InputClass);
				}
			}
			else {
				std::cout << std::endl << std::setw(65) << std::right << "[ERROR DUPLICATE FOUND]" << std::endl << std::endl;
			}
		}
		else {
			personen.push_back(InputClass);
		}
	}

	void DisplayPerson() {
		if (GetCount() == 0) {
			std::cout << std::endl << std::setw(65) << std::right << "[NO DATA FOUND]" << std::endl << std::endl;
		}
		else {
			for (int i = 0; i < GetCount(); i++) {
				std::cout << std::endl << std::setw(18) << std::right << ""
					<< std::setw(15) << std::left << personen[i].getVorname()
					<< std::setw(15) << std::left << personen[i].getNachname()
					<< std::setw(12) << std::left << personen[i].getGeburtsdatum()
					<< std::setw(18) << std::left << personen[i].getAdresse()
					<< std::setw(10) << std::left << personen[i].getPostleitzahl()
					<< std::setw(10) << std::left << personen[i].getTelefonnummer() << std::endl;

			}
		}
	}

	void SearchUser(std::string searchWord) {

		MYSQL* conn;
		MYSQL_RES* res;
		MYSQL_ROW row;
		std::string query;

		conn = mysql_init(NULL);
		conn = mysql_real_connect(conn, "localhost", "root", "Student", "db_adressbuch", 3306, NULL, 0);

		if (conn) {
			int rowCount = 0;
			if (searchWord == "*") {
				query = "SELECT * FROM tb_user";
			}
			else {
				query = "SELECT * FROM tb_user WHERE firstN LIKE '%" + searchWord + "%' OR lastN LIKE '%" + searchWord + "%' OR birthdate LIKE '%" + searchWord + " %' OR street LIKE '%" + searchWord + "%' OR plz LIKE '%" + searchWord + " %' OR number LIKE '%" + searchWord + "%';";
			}

			mysql_query(conn, query.c_str());

			MYSQL_RES* res = mysql_store_result(conn);

			while ((row = mysql_fetch_row(res))) {
				std::cout << std::endl << std::setw(18) << std::right << ""
					<< std::setw(15) << std::left << row[1]
					<< std::setw(15) << std::left << row[2]
					<< std::setw(12) << std::left << row[3]
					<< std::setw(18) << std::left << row[4]
					<< std::setw(10) << std::left << row[5]
					<< std::setw(10) << std::left << row[6] << std::endl;
				rowCount++;
			}
			if (rowCount == 0) {
				std::cout << std::endl << std::setw(65) << std::right << "[NO DATA FOUND]" << std::endl << std::endl;
			}
		}
	}

	void RemovePerson(std::string inputVorname, std::string inputGeburtstag, std::string inputTelefon) {


		MYSQL* conn;
		MYSQL_RES* res;
		MYSQL_ROW row;
		std::string query;

		conn = mysql_init(NULL);
		conn = mysql_real_connect(conn, "localhost", "root", "Student", "db_adressbuch", 3306, NULL, 0);

		if (conn) {

			query = "DELETE FROM tb_user WHERE firstN = '" + inputVorname + "' AND birthdate = '" + inputGeburtstag + "' AND number = '" + inputTelefon + "';";

			if (mysql_query(conn, query.c_str()) != 0) {
				std::cout << std::endl << std::setw(65) << std::right << "[NO USER FOUND]" << std::endl << std::endl;
			}
			else {
				for (int i = 0; i < personen.size(); i++) {
					if ((inputVorname == personen[i].getVorname() && (inputGeburtstag == personen[i].getGeburtsdatum()) && (inputTelefon == personen[i].getTelefonnummer()))) {
						personen.erase(personen.begin() + i);
					}
				}
				std::cout << std::endl << std::setw(65) << std::right << "[USER REMOVED]" << std::endl << std::endl;
			}
		}
		else {
			std::cout << std::endl << std::setw(65) << std::right << "[INVALID USER TO REMOVE]" << std::endl << std::endl;
		}
	}

	void EditPerson(std::string oldInputVorname, std::string oldInputGeburtstag, std::string oldInputTelefon, std::string inputVorname, std::string inputLastname, std::string inputGeburtstag, std::string inputAdresse, std::string inputPLZ, std::string inputTelefon) {
		MYSQL* conn;
		MYSQL_RES* res;
		MYSQL_ROW row;
		std::string query;

		bool isValid;

		conn = mysql_init(NULL);
		conn = mysql_real_connect(conn, "localhost", "root", "Student", "db_adressbuch", 3306, NULL, 0);

		if (conn) {

			for (int i = 0; i < personen.size(); i++) {
				if ((oldInputVorname == personen[i].getVorname() && (oldInputGeburtstag == personen[i].getGeburtsdatum()) && (oldInputTelefon == personen[i].getTelefonnummer()))) {

					if (inputVorname != "") {
						personen[i].setVorname(inputVorname);
					}
					else {
						personen[i].setVorname(personen[i].getVorname());
						inputVorname = personen[i].getVorname();
					}

					if (inputLastname != "") {
						personen[i].setNachname(inputLastname);
					}
					else {
						personen[i].setNachname(personen[i].getNachname());
						inputLastname = personen[i].getNachname();
					}

					if (inputGeburtstag != "") {
						personen[i].setGeburtsdatum(inputGeburtstag, isValid, false);
					}
					else {
						personen[i].setGeburtsdatum(personen[i].getGeburtsdatum(), isValid, false);
						inputGeburtstag = personen[i].getGeburtsdatum();
					}

					if (inputAdresse != "") {
						personen[i].setAdresse(inputAdresse);
					}
					else {
						personen[i].setAdresse(personen[i].getAdresse());
						inputAdresse = personen[i].getAdresse();
					}

					if (inputPLZ != "") {
						personen[i].setPostleitzahl(inputPLZ);
					}
					else {
						personen[i].setPostleitzahl(personen[i].getPostleitzahl());
						inputPLZ = personen[i].getPostleitzahl();
					}

					if (inputTelefon != "") {
						personen[i].setTelefonnummer(inputTelefon);
					}
					else {
						personen[i].setTelefonnummer(personen[i].getTelefonnummer());
						inputTelefon = personen[i].getTelefonnummer();
					}
				}

				std::cout << "OLDVorname |" << oldInputVorname << std::endl;
				std::cout << "OLD |" << oldInputGeburtstag << std::endl;
				std::cout << "OLD |" << oldInputTelefon << std::endl;
				std::cout << "inputVorname |" << inputVorname << std::endl;
				std::cout << "inputVorname |" << inputLastname << std::endl;
				std::cout << "inputVorname |" << inputGeburtstag << std::endl;
				std::cout << "inputVorname |" << inputPLZ << std::endl;
				std::cout << "inputVorname |" << inputTelefon << std::endl;


				query = "UPDATE tb_user SET firstN = '" + inputVorname + "', lastN = '" + inputLastname + "', birthdate = '" + inputGeburtstag + "', street = '" + inputAdresse + "', plz = '" + inputPLZ + "', number = '" + inputTelefon + "' WHERE firstN = '" + oldInputVorname + "' AND birthdate = '" + oldInputGeburtstag + "' AND number = '" + oldInputTelefon + "'";

				if (mysql_query(conn, query.c_str()) != 0) {

					std::cout << "Error: " << mysql_error(conn) << std::endl;
					std::cout << std::endl << std::setw(65) << std::right << "[NO USER FOUND 1]" << std::endl << std::endl;
				}
				else {
					std::cout << std::endl << std::setw(65) << std::right << "[USER EDITED]" << std::endl << std::endl;
				}
			}
		}
		else {
			std::cout << std::endl << std::setw(65) << std::right << "[DB NOT CONNECTED]" << std::endl << std::endl;
		}

	}

};


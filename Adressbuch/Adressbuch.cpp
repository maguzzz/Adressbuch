#include "header.h"
#include "Adressbuch.h"



void Status(bool dbConnection, int userCount, bool isSaved) {
	if (dbConnection) {
		std::cout << std::setw(38) << std::right << "DB | CONNECTED";
	}
	else {
		std::cout << std::setw(38) << std::right << "DB | NO CONNECTION";
	}
	std::cout << std::setw(24) << std::right << "USER COUNT | " << userCount;

	if (isSaved) {
		std::cout << std::setw(24) << std::right << "SAVE STATUS | " << "TRUE";

	}
	else {
		std::cout << std::setw(24) << std::right << "SAVE STATUS | " << "FALSE";
	}
}

void MainUi() {
	std::cout << std::endl << std::setw(101) << std::right << "-----------------------------------------------------------------------------------" << std::endl;
	std::cout << std::setw(90) << std::right << "[A]dd | [T]Display  | [Z]Search | [L]oad File | [S]ave | [E]xit";
	std::cout << std::endl << std::setw(101) << std::right << "-----------------------------------------------------------------------------------" << std::endl << std::endl;
}

void UserInput(std::string pickQuestion, std::string& pickOption, bool whipeScreen = true, bool ShowLine = true) {
	if (ShowLine) {
		std::cout << std::endl << std::setw(101) << std::right << "-----------------------------------------------------------------------------------" << std::endl << std::endl;
	}
	std::cout << std::setw(60) << std::right << std::endl << pickQuestion << " | ";
	std::getline(std::cin, pickOption);

	if (whipeScreen) {
		system("cls");
	}
}

void Adressbuch::Start() {


	Person p;
	Personen storage;
	bool birthdayVaildCheck;
	bool isSaved = false;
	bool canExit = false;

	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;

	conn = mysql_init(NULL);
	conn = mysql_real_connect(conn, "localhost", "root", "Student", "db_adressbuch", 3306, NULL, 0);


	std::string option{ "T" };
	std::ifstream userFile;




	if (conn) {
		std::string query = "SELECT * FROM tb_user";

		mysql_query(conn, query.c_str());

		MYSQL_RES* res = mysql_store_result(conn);

		while ((row = mysql_fetch_row(res))) {
			p.setVorname(row[1]);
			p.setNachname(row[2]);
			p.setGeburtsdatum(row[3], birthdayVaildCheck);
			p.setAdresse(row[4]);
			p.setPostleitzahl(row[5]);
			p.setTelefonnummer(row[6]);
			personen.AddPerson(p, false);
		}
	}


	do {
		Status(conn, personen.GetCount(), isSaved);
		MainUi();

		if (option == "A") {
			std::string tempInput;

			std::cout << std::endl << std::setw(65) << std::right << "[ADD USER]" << std::endl << std::endl;

			UserInput("Vorname", tempInput, false, false);
			p.setVorname(tempInput);
			UserInput("Nachname", tempInput, false, false);
			p.setNachname(tempInput);

			do {
				UserInput("Geburtsdatum (00.00.0000)", tempInput, false, false);
				p.setGeburtsdatum(tempInput, birthdayVaildCheck, false);
			} while (birthdayVaildCheck == false);

			UserInput("Adresse", tempInput, false, false);
			p.setAdresse(tempInput);
			UserInput("Postleitzahl", tempInput, false, false);
			p.setPostleitzahl(tempInput);
			UserInput("Telefonnummer", tempInput, false, false);
			p.setTelefonnummer(tempInput);

			personen.AddPerson(p);
			isSaved = false;
			UserInput("Select Option", option);
		}
		else if (option == "T") {
			personen.DisplayPerson();

			UserInput("Select Option", option);
		}
		else if (option == "Z") {
			std::string searchinput{};

			do {
				system("cls");
				Status(conn, personen.GetCount(), isSaved);
				std::cout << std::endl << std::setw(101) << std::right << "-----------------------------------------------------------------------------------" << std::endl;
				std::cout << std::setw(80) << std::right << "[-]Delete | [+]Change  | [#]Exit | [*]Show all";
				std::cout << std::endl << std::setw(101) << std::right << "-----------------------------------------------------------------------------------" << std::endl;

				personen.SearchUser(searchinput),
					UserInput("Search or Pick", searchinput, false);

				if (searchinput == "-") {
					searchinput = "*";

					std::cout << std::endl << std::setw(75) << std::right << "[ENTER USER TO DELETE]" << std::endl << std::endl;

					std::string inputVorname;
					std::string inputGeburtsdatum;
					std::string inputNummer;

					UserInput("Vorname", inputVorname, false, false);
					UserInput("Geburtsdatum", inputGeburtsdatum, false, false);
					UserInput("Nummer", inputNummer, false, false);

					personen.RemovePerson(inputVorname, inputGeburtsdatum, inputNummer);
					isSaved = false;
				}
				else if (searchinput == "+") {
					searchinput = "*";
					std::string oldInputVorname;
					std::string oldInputGeburtsdatum;
					std::string oldInputNummer;

					std::string inputVorname{ "" };
					std::string inputNachname{ "" };
					std::string inputGeburtsdatum{ "" };
					std::string inputAdresse{ "" };
					std::string inputPLZ{ "" };
					std::string inputNummer{ "" };

					UserInput("Vorname", oldInputVorname, false, false);
					UserInput("Geburtsdatum", oldInputGeburtsdatum, false, false);
					UserInput("Nummer", oldInputNummer, false, false);
					std::cout << std::endl << std::setw(101) << std::right << "-----------------------------------------------------------------------------------" << std::endl;

					UserInput("Vorname", inputVorname, false, false);
					UserInput("Nachname", inputNachname, false, false);
					UserInput("Geburtsdatum", inputGeburtsdatum, false, false);
					UserInput("Adresse", inputAdresse, false, false);
					UserInput("PLZ", inputPLZ, false, false);
					UserInput("Nummer", inputNummer, false, false);

					personen.EditPerson(oldInputVorname, oldInputGeburtsdatum, oldInputNummer, inputVorname, inputNachname, inputGeburtsdatum, inputAdresse, inputPLZ, inputNummer);
					isSaved = false;
				}
			} while (searchinput != "#");

			option = "T";
			system("cls");
		}
		else if (option == "L") {
			std::cout << std::endl << std::setw(65) << std::right << "[LOAD FILE]" << std::endl << std::endl;
			std::string fielpath;
			UserInput("Enter Filepath to Load", fielpath, false,false);

			userFile.open(fielpath);

			if (!userFile) {
				std::cout << std::endl << std::setw(65) << std::right << "[ERROR FILE NOT FOUND]" << std::endl << std::endl;
			}
			else {
				std::ifstream infile(fielpath);

				std::string eachline;
				std::string token;


				while (std::getline(infile, eachline)) {

					std::istringstream iss(eachline);
					std::vector <std::string> userData{};

					while (std::getline(iss, token, ';')) {
						userData.push_back(token);
					}

					p.setVorname(userData[0]);
					p.setNachname(userData[1]);
					p.setGeburtsdatum(userData[2], birthdayVaildCheck);
					p.setAdresse(userData[3]);
					p.setPostleitzahl(userData[4]);
					p.setTelefonnummer(userData[5]);

					personen.AddPerson(p);
					isSaved = false;
				}

			}
			userFile.close();
			UserInput("Select Option", option);
		}
		else if (option == "S") {
			std::string userData{};

			std::string userInput;
			UserInput("Please Enter a Filepath to save", userInput, false, false);
			std::ofstream textFile;
			textFile.open(userInput);

			if (!textFile) {
				std::cout << std::endl << std::setw(65) << std::right << "[ERROR FILE NOT FOUND]" << std::endl << std::endl;
				textFile.close();
				isSaved = false;
			}
			else {

				std::string query = "SELECT * FROM tb_user";

				mysql_query(conn, query.c_str());

				MYSQL_RES* res = mysql_store_result(conn);

				while ((row = mysql_fetch_row(res))) {
					p.setVorname(row[1]);
					p.setNachname(row[2]);
					p.setGeburtsdatum(row[3], birthdayVaildCheck);
					p.setAdresse(row[4]);
					p.setPostleitzahl(row[5]);
					p.setTelefonnummer(row[6]);

					userData = p.getVorname() + ";" + p.getNachname() + ";" + p.getGeburtsdatum() + ";" + p.getAdresse() + ";" + p.getPostleitzahl() + ";" + p.getTelefonnummer();
					textFile << userData;
					textFile << std::endl;
					isSaved = true;
				}
				std::cout << std::endl << std::setw(65) << std::right << "[FILES SAVED]" << std::endl << std::endl;
				std::cout << "[" << userInput << "]" << std::endl;
				textFile.close();
			}
			UserInput("Select Option", option);
		}
		else if (option == "E" && !isSaved) {
			std::string exitInput{};
			std::cout << std::endl << std::setw(65) << std::right << "[DATA NOT SAVED IN FILE]" << std::endl << std::endl;
			UserInput("Do you want to save?[y/n]", exitInput, false);
			if (exitInput == "y") {
				option = "S";
				system("cls");
			}
			else {
				canExit = true;
				system("cls");
			}
		}
		else if ((option == "E") && (isSaved)) {
			canExit = true;
			system("cls");
		}
		else {
			option = "T";
			system("cls");
		}

	} while (!canExit);

}

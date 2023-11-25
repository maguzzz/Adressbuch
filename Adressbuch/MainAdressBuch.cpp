#include "header.h"
#include "MainAdressbuch.h"
#include "Adressbuch.h"


int main() {
	Adressbuch mainAdressbuch = Adressbuch();

	std::cout << "\n\n\n\n\n\n\n\n\n" << std::endl;
	std::cout << std::setw(95) << std::right << "    #                                                                   " << std::endl;
	std::cout << std::setw(95) << std::right << "   # #   #####  #####  ######  ####   ####  #####  #    #  ####  #    # " << std::endl;
	std::cout << std::setw(95) << std::right << "  #   #  #    # #    # #      #      #      #    # #    # #    # #    # " << std::endl;
	std::cout << std::setw(95) << std::right << " #     # #    # #    # #####   ####   ####  #####  #    # #      ###### " << std::endl;
	std::cout << std::setw(95) << std::right << " ####### #    # #####  #           #      # #    # #    # #      #    # " << std::endl;
	std::cout << std::setw(95) << std::right << " #     # #    # #   #  #      #    # #    # #    # #    # #    # #    # " << std::endl;
	std::cout << std::setw(95) << std::right << " #     # #####  #    # ######  ####   ####  #####   ####   ####  #    # " << std::endl;

	Sleep(1000);
	system("cls");

	std::cout << "\n\n\n\n\n\n\n\n\n" << std::endl;
	std::cout << std::setw(95) << std::right << " #     #                                #     #                      " << std::endl;
	std::cout << std::setw(95) << std::right << " #     # ###### #      #       ####     #     #  ####  ###### #####  " << std::endl;
	std::cout << std::setw(95) << std::right << " #     # #      #      #      #    #    #     # #      #      #    # " << std::endl;
	std::cout << std::setw(95) << std::right << " ####### #####  #      #      #    #    #     #  ####  #####  #    # " << std::endl;
	std::cout << std::setw(95) << std::right << " #     # #      #      #      #    #    #     #      # #      #####  " << std::endl;
	std::cout << std::setw(95) << std::right << " #     # #      #      #      #    #    #     # #    # #      #   #  " << std::endl;
	std::cout << std::setw(95) << std::right << " #     # ###### ###### ######  ####      #####   ####  ###### #    # " << std::endl;

	Sleep(2000);
	system("cls");

	mainAdressbuch.Start();

	system("cls");
	std::cout << "\n\n\n\n\n\n\n\n\n" << std::endl;
	std::cout << std::setw(85) << std::right << " ######                  #     #                      " << std::endl;
	std::cout << std::setw(85) << std::right << " #     # #   # ######    #     #  ####  ###### #####  " << std::endl;
	std::cout << std::setw(85) << std::right << " #     #  # #  #         #     # #      #      #    # " << std::endl;
	std::cout << std::setw(85) << std::right << " ######    #   #####     #     #  ####  #####  #    # " << std::endl;
	std::cout << std::setw(85) << std::right << " #     #   #   #         #     #      # #      #####  " << std::endl;
	std::cout << std::setw(85) << std::right << " #     #   #   #         #     # #    # #      #   #  " << std::endl;
	std::cout << std::setw(85) << std::right << " ######    #   ######     #####   ####  ###### #    # " << std::endl;
	Sleep(2000);

}
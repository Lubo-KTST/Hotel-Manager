// HotelManager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "Room.hpp"
#include "Utils.h"
#include "Unavailable.h"
#include "Reservation.h"
#include "Maintenance.h"
#include "Commands.hpp"

struct Hotel
{
public: //probably will need work and be an entire class but for now it is ok-----------------------------------------------------------------------------------------------------------
	Room* rooms = nullptr;
	size_t roomsAmount = 0;
	size_t roomsCap = 0;
private:
	//addmultipleroomss                       --------------------------------------------------------------------------------------------------------------------
};

void readHotel(std::istream& istr, Room* rooms)
{

}
int main()
{
	
	/*
std::cout << bd << bd2;
std::ofstream ofstr("BulgarianDate.dat", std::ios::binary);
ofstr << bd << bd2;
ofstr.close();
std::ifstream ifstream("BulgarianDate.dat", std::ios::binary);
ifstream >> bd2;
ifstream >> bd;
ifstream.close();
std::cout << bd << bd2;
*/
	try
	{
		{
			char note1[] = "NOTE";
			BulgarianDate bd(1, 2, 2005);
			BulgarianDate bd2(4, 2, 2025);
			/*
			Unavailable u1(bd, bd2, note1);
			std::cout << u1;
			Unavailable u2;

			std::ofstream ofstr("Unavailable.dat", std::ios::binary);
			ofstr << u1;
			ofstr.close();
			std::ifstream ifstream("Unavailable.dat", std::ios::binary);
			ifstream >> u2;
			ifstream.close();
			std::cout << u1;
			*/
			/*
			Reservation r(bd, bd2, note1,4);
			std::cout << r;
			Reservation r2,r3;
			r2 = r;
			std::ofstream ofstr1("ReservationTest.dat", std::ios::binary);
			ofstr1 << r2;
			ofstr1.close();
			std::ifstream ifstream1("ReservationTest.dat", std::ios::binary);
			ifstream1 >> r3;
			ifstream1.close();
			std::cout << r3;


			Maintenance m(bd, bd2, note1, 1000,4);
			std::cout << m;
			Maintenance m2, m3;
			m2 = m;
			std::ofstream ofstr2("MaintenanceTest.dat", std::ios::binary);
			ofstr2 << m2;
			ofstr2.close();
			std::ifstream ifstream2("MaintenanceTest.dat", std::ios::binary);
			ifstream2 >> m3;
			ifstream2.close();
			std::cout <<std::endl<< m3<<std::endl;*/
			/*
					Reservation r(bd, bd2, note1, 4);
					Maintenance m(bd, bd2, note1, 1000, 5);
					//std::cout << r << std::endl;
					//std::cout << m << std::endl;
					Reservation r2, r3;
					Maintenance m2, m3;
					r2 = r;
					m2 = m;
					std::ofstream ofstr1("Heterogen.dat", std::ios::binary);
					ofstr1 << r2 << std::endl << m2 << std::endl;
					ofstr1 << r << std::endl;
					ofstr1.close();
				*/  //--heterogen cont works

			Reservation r(bd, bd2, note1, 4);
			Maintenance m(bd, bd2, note1, 1000, 5);
			Reservation r2, r3(r);
			Maintenance m2, m3(bd, bd2, note1, 1000, 15);
			r2 = r;
			m2 = m;
			Unavailable** unav = new Unavailable * [7];
			unav[0] = &r;
			unav[1] = &m;
			unav[2] = &r2;
			unav[3] = &m2;
			unav[4] = &m3;

			/*
			for (int i = 0; i < 5; i++)
			{
				std::cout << *unav[i] << std::endl;
			}
			*/

			Room room(6, unav, 5);
			Room room1, room2(room);
			room1 = room;
			room1.addUnavPeriod(r3);
			room1.addUnavPeriod(r);
			
			//std::cout << room << std::endl << room1 << std::endl << room2 << std::endl;
			//std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
			//std::cout << room2 << std::endl;

			std::ofstream ofstr("Rooms.dat", std::ios::binary);
			ofstr << 3 << " " << room << room1 << room2;
			ofstr.close();

			std::ifstream ifstr("Rooms.dat", std::ios::binary); //tova e nomer za chetene na mnogo stai shte napravya readMultiple za rooms i go dobavyam v Commands::open----------------------------------------------------------------------------------------------
			int readRooms;
			ifstr >> readRooms;
			Room* roooms = new Room[readRooms];
			ifstr >> roooms[0] >> roooms[1] >> roooms[2];
			std::cout << roooms[0] << std::endl << roooms[1] << std::endl << roooms[2] << std::endl;
			
		}
	
		while (true)
		{
			std::cout << "enter command" << std::endl;
			char buffer[100];
			std::cin.getline(buffer, 100);
			//std::cout << buffer;
			if (strStartsWith(buffer, "help"))
			{
				Commands::help();
			}
			else if (strStartsWith(buffer, "open"))
			{
				char* location = buffer;
				location += 5;
				Room r = Commands::open(location);
				std::cout << r;
			}
			else if (strStartsWith(buffer, "close"))
			{

			}
			else if (strStartsWith(buffer, "save "))
			{

			}
			else if (strStartsWith(buffer, "saveas"))
			{

			}
			else if (strStartsWith(buffer, "exit"))
			{
				Commands::exit(0);
			}
		}
		
	}
	catch (std::runtime_error e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "OOO nz brat" << std::endl;
	}

	return 12;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

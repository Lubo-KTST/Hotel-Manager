#pragma once
#include "Unavailable.h"
#include "Reservation.h"
#include "Maintenance.h"
#include <iostream>

class Room;
std::ostream& operator<<(std::ostream& ostr, const Room& room);
std::istream& operator>>(std::istream& istr, Room& room);

class  Room
{
public:
	 Room();
	 Room(unsigned bedsAmount, const Unavailable*const* unav, size_t unavSize);
	 Room(std::ifstream& ifstr);
	 Room(const Room& r);
	 Room& operator=(const Room& r);
	 Room(Room&& r) noexcept;
	 Room& operator=(Room&& r) noexcept;
	 ~Room();
	 //----------------------------------------------------------nyama da iskam da se zastupvat, malko bratle

	 void setBedsAmount(unsigned bedsAmount);
	 unsigned getBedsAmount() const;
	 unsigned getID() const;
	 size_t getUnavailableSize() const;
	 //get unavailable container - by copy - very heavy

	 friend std::ostream& operator<<(std::ostream& ostr, const Room& room);
	 friend std::istream& operator>>(std::istream& istr, Room& room);

	 void createIdenticalRoom(const Room& r);
	 void addUnavPeriod(const Unavailable& unav);

	 

private:
	unsigned ID;
	unsigned static roomsAmount; //-for keeeping track

	unsigned bedsAmount = 1;
	Unavailable** unavailable = nullptr;
	size_t unavailableSize = 0;
	size_t unavailaleCap = 0;

	Unavailable* createFromType(char type);
	void free();
	void copyFrom(const Room& r);
	void moveFrom(Room&& r);
	void resize();
	void print(std::ostream& ostr) const;
	void read(std::istream& istr);
};

unsigned Room::roomsAmount = 0;

//Factory
Unavailable* Room::createFromType(char type)
{
	if (type == 'R') return new Reservation();
	else if (type == 'M') return new Maintenance();
	else throw std::runtime_error("Unknown type");
}


void Room::free()
{
	if (unavailable != nullptr)
	{
		for (int i = 0; i < unavailableSize; i++) delete unavailable[i];
		delete[] unavailable;
		unavailable = nullptr;
	}
	this->unavailableSize = 0;
	this->unavailaleCap = 0;
}
void Room::copyFrom(const Room& r)
{

	free();
	this->bedsAmount = r.bedsAmount;
	this->ID = r.ID;
	this->unavailableSize = r.unavailableSize;
	this->unavailaleCap = r.unavailaleCap;

	if (r.unavailable != nullptr && r.unavailableSize > 0) {
		this->unavailable = new Unavailable* [r.unavailaleCap];
		for (int i = 0; i < unavailableSize; ++i) {
			this->unavailable[i] = r.unavailable[i]->clone(); // DEEP COPY!
		}
	}
	else {
		this->unavailable = nullptr;
	}
}
void Room::moveFrom(Room&& r)
{
	this->bedsAmount = r.bedsAmount;
	this->ID = r.ID;

	if (this->unavailable != nullptr) 
	{
		for (int i = 0; i < this->unavailableSize; i++) delete this->unavailable[i];
		delete[] this->unavailable;
		this->unavailable = nullptr;
	}

	this->unavailable = r.unavailable; 
	this->unavailableSize = r.unavailableSize;
	this->unavailaleCap = r.unavailaleCap;
	r.unavailable = nullptr;
	r.unavailableSize = 0;
	r.unavailaleCap = 0;
}

 Room:: Room()
{
	 ID = roomsAmount++;
}

 Room::Room(unsigned bedsAmount, const Unavailable* const* unav, size_t unavSize)
 {
	 this->ID = roomsAmount++;
	 this->bedsAmount = bedsAmount;
	 this->unavailableSize = unavSize;
	 this->unavailaleCap = unavSize*2;

	 if (unav != nullptr && unavSize > 0) 
	 {
		 this->unavailable = new Unavailable* [unavailaleCap];
		 for (int i = 0; i < unavSize; ++i) 
		 {
			 this->unavailable[i] = unav[i]->clone();
		 }
	 }
	 else 
	 {
		 this->unavailable = nullptr;
		 this->unavailableSize = 0;
		 this->unavailaleCap = 0;
	 }
 }
 Room::Room(std::ifstream& ifstr)
 {
	 Room r;
	 r.read(ifstr);
	 copyFrom(r);
 }

 Room::Room(const Room& r)
 {
	 copyFrom(r);
 }
 void Room::createIdenticalRoom(const Room& r)
 {
	 copyFrom(r);
	 ID = roomsAmount++;
 }
 Room& Room::operator=(const Room& r)
 {
	 copyFrom(r);
	 return *this;
 }
 Room::Room(Room&& r) noexcept
 {
	 moveFrom(std::move(r));
	 ID = roomsAmount++;
 }
 Room& Room::operator=(Room&& r) noexcept
 {
	 moveFrom(std::move(r));
	 return *this;
 }
 Room::~Room()
 {
	 free();
 }


 void Room::setBedsAmount(unsigned bedsAmount)
 {
	 this->bedsAmount = bedsAmount;
 }
 unsigned Room::getBedsAmount() const
 {
	 return this->bedsAmount;
 }
 unsigned Room::getID() const
 {
	 return this->ID;
 }

 size_t Room::getUnavailableSize() const
 {
	 return this->unavailableSize;
 }

std::ostream& operator<<(std::ostream& ostr, const Room& room)
 {
	room.print(ostr);
	return ostr;
 }
 std::istream& operator>>(std::istream& istr, Room& room)
 {
	 room.read(istr);
	 return istr;
 }

 void Room::addUnavPeriod(const Unavailable& unav)
 {
	 if (unavailableSize == unavailaleCap) resize();
	 unavailable[unavailableSize++] = unav.clone();
 }

 void Room::resize()
 {
	 if (unavailaleCap == 0) unavailaleCap++;
	 else unavailaleCap *= 2;


	 Unavailable** newUnav = new Unavailable* [unavailaleCap];
	 if (unavailable != nullptr)
	 {
		 for (int i = 0; i < unavailableSize; i++)
		 {
			 newUnav[i] = unavailable[i]->clone();
			 delete unavailable[i];
			 /*
			 newUnav[i] = unavailable[i];
			 unavailable[i]=nullptr;
			 */                   //-----more efficient? but not better practices??
		 }
		 delete[] unavailable;
		 unavailable = nullptr;
	 }
	 unavailable = newUnav;
	 newUnav = nullptr;
 }

 void Room::print(std::ostream& ostr) const
 {
	 ostr << this->getID() << " " << this->getBedsAmount() << " " << this->getUnavailableSize() << " ";
	 for (int i = 0; i < unavailableSize; i++)
	 {
		 ostr << *unavailable[i] << " ";
	 }

 }
 void Room::read(std::istream& istr)
 {
	 roomsAmount++;//???

	 unsigned newID;
	 unsigned newBedsAmount = 1;
	 Unavailable** newUnavailable = nullptr;
	 size_t newUnavailableSize = 0;
	 size_t newUnavailableCap = 0;

	 istr >> newID >> newBedsAmount >> newUnavailableSize;
	 //istr.ignore();
	 newUnavailableCap = newUnavailableSize * 2;
	 newUnavailable = new Unavailable * [newUnavailableCap];
	 for (int i = 0; i < newUnavailableSize; i++)
	 {
		 char type;
		 istr >> type;
		 //istr.ignore();
		 Unavailable* obj = createFromType(type);
		 istr >> *obj;
		 newUnavailable[i] = obj;
	 }

	 this->ID = newID;
	 this->setBedsAmount(newBedsAmount);
	 this->unavailableSize = newUnavailableSize;
	 this->unavailaleCap = newUnavailableCap;
	 this->unavailable = newUnavailable;
	 newUnavailable = nullptr;
	 
 }
 
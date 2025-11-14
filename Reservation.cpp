#include "Reservation.h"

unsigned Reservation::getPeopleStaying() const
{
	return this->peopleStaying;
}
void Reservation::setPeopleStaying(unsigned people)
{
	peopleStaying = people;
}

Reservation::Reservation(BulgarianDate start, BulgarianDate end, char* note, unsigned peopleStaying) : Unavailable(start,end,note)
{
	this->peopleStaying = peopleStaying;
}
Reservation::Reservation(unsigned startDay, unsigned startMonth, unsigned startYear, unsigned endDay, unsigned endMonth, unsigned endYear, 
							char* note, unsigned peopleStaying) : Unavailable(startDay,startMonth,startYear,endDay,endMonth,endYear,note)
{
	this->peopleStaying = peopleStaying;
}
Reservation::Reservation(const Reservation& copy) :Unavailable(copy)
{
	this->peopleStaying = copy.peopleStaying;
}
Reservation& Reservation::operator=(const Reservation& rhs)
{
	Unavailable::operator=(rhs);
	this->peopleStaying = rhs.peopleStaying;
	return *this;
}
Reservation::Reservation(Reservation&& move) noexcept :Unavailable(std::move(move))
{
	this->peopleStaying = move.peopleStaying;
	move.setPeopleStaying(0);
}
Reservation& Reservation::operator=(Reservation&& rhs) noexcept
{
	Unavailable::operator=(std::move(rhs));
	this->peopleStaying = rhs.peopleStaying;
	rhs.setPeopleStaying(0);
	return *this;
}
Reservation::~Reservation()
{
	Unavailable::~Unavailable();
	peopleStaying = 0;
}
Unavailable* Reservation::clone() const
{
	return new Reservation(*this);
}


void Reservation::print(std::ostream& ostr) const
{
	ostr << 'R' << " ";
	Unavailable::print(ostr);
	ostr << " " << this->getPeopleStaying();
}

void Reservation::read(std::istream& istr)
{
	Unavailable::read(istr);
	unsigned peopleSt;
	istr >> peopleSt;
	setPeopleStaying(peopleSt);
}

std::ostream& operator<<(std::ostream& ostr, const Reservation& unav)
{
	unav.print(ostr);
	return ostr;
}

std::istream& operator>>(std::istream& istr, Reservation& unav)
{
	unav.read(istr);
	return istr;
}
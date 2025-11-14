#include "Maintenance.h"

unsigned Maintenance::getPrice() const
{
	return this->price;
}
unsigned Maintenance::getWorkingStaff() const
{
	return this->workingStaff;
}
void Maintenance::setPrice(unsigned price)
{
	this->price = price;
}
void Maintenance::setWorkingStaff(unsigned staff)
{
	this->workingStaff = staff;
}


Maintenance::Maintenance(BulgarianDate start, BulgarianDate end, char* note, unsigned price, unsigned workingStaff) : Unavailable(start, end, note)
{
	this->price = price;
	this->workingStaff = workingStaff;
}
Maintenance::Maintenance(unsigned startDay, unsigned startMonth, unsigned startYear, unsigned endDay, unsigned endMonth, unsigned endYear,
							char* note, unsigned price, unsigned workingStaff) : Unavailable(startDay, startMonth, startYear, endDay, endMonth, endYear, note)
{
	setPrice(price);
	setWorkingStaff(workingStaff);
}
Maintenance::Maintenance(const Maintenance& copy) : Unavailable(copy)
{
	setPrice(copy.getPrice());
	setWorkingStaff(copy.getWorkingStaff());
}
Maintenance& Maintenance::operator=(const Maintenance& rhs)
{
	Unavailable::operator=(rhs);
	setPrice(rhs.getPrice());
	setWorkingStaff(rhs.getWorkingStaff());
	return *this;
}
Maintenance::Maintenance(Maintenance&& move) noexcept : Unavailable(std::move(move))
{
	setPrice(move.getPrice());
	setWorkingStaff(move.getWorkingStaff());
	move.setPrice(0);
	move.setWorkingStaff(0);
}
Maintenance& Maintenance::operator=(Maintenance&& rhs) noexcept
{
	Unavailable::operator=(std::move(rhs));
	setWorkingStaff(rhs.getWorkingStaff());
	rhs.setPrice(0);
	rhs.setWorkingStaff(0);
	return *this;
}
Maintenance::~Maintenance()
{
	Unavailable::~Unavailable();
	price = 0;
	workingStaff = 0;
}
Unavailable* Maintenance::clone() const
{
	return new Maintenance(*this);
}

	
void Maintenance::print(std::ostream& ostr) const
{
	ostr << 'M' << " ";
	Unavailable::print(ostr);
	ostr << " " << this->price << " " << this->workingStaff;
}
void Maintenance::read(std::istream& istr)
{
	Unavailable::read(istr);
	unsigned price, workingstf;
	istr >> price >> workingstf;
	this->setPrice(price);
	this->setWorkingStaff(workingstf);
}

std::ostream& operator<<(std::ostream& ostr, const Maintenance& unav)
{
	unav.print(ostr);
	return ostr;
}
std::istream& operator>>(std::istream& istr, Maintenance& unav)
{
	unav.read(istr);
	return istr;
}

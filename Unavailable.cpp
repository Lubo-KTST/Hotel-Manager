#include "Unavailable.h"

void Unavailable::setStart(BulgarianDate start)
{
	if (!start.good()) throw std::runtime_error("Unavailable::setStart did not recieve a valid date");
	this->start = start;
}
void Unavailable::setStart(unsigned startDay, unsigned startMonth, unsigned startYear)
{
	BulgarianDate strt(startDay, startMonth, startYear);
	setStart(strt);
}
void Unavailable::setEnd(BulgarianDate end)
{
	if (!end.good()) throw std::runtime_error("Unavailable::setEnd did not recieve a valid date");
	this->end = end;
}
void Unavailable::setEnd(unsigned endDay, unsigned endMonth, unsigned endYear)
{
	BulgarianDate end(endDay, endMonth, endYear);
	setStart(end);
}
void  Unavailable::setNote(const char* note)
{
	if (this->note != nullptr && note != nullptr && strcmp(this->note, note)) return;
	if (this->note != nullptr)
	{
		delete[] this->note;
		this->note = nullptr;
	}
	if (note != nullptr)
	{
		this->note = new char[strlen(note)+1];
		strcpy(this->note, note);
	}
}
const BulgarianDate& Unavailable::getStart() const
{
	return this->start;
}
const BulgarianDate& Unavailable::getEnd() const
{
	return this->end;
}
const char* Unavailable::getNote() const
{
	return this->note;
}

void Unavailable::free()
{
	if (note != nullptr) delete[] note;
	note = nullptr;
	start = BulgarianDate();
	end = BulgarianDate();
}
void Unavailable::copy(const Unavailable& other)
{
	setStart(other.start);
	setEnd(other.end);
	setNote(other.note);
}
void Unavailable::move(Unavailable&& other)
{
	this->start = other.start; //avoids the throwing of errors
	this->end = end;
	setNote(other.note);
	other.note = nullptr;
	other.start = BulgarianDate();
	other.end = BulgarianDate();
}

Unavailable::Unavailable(BulgarianDate start, BulgarianDate end, char* note)
{
	setStart(start);
	setEnd(end);
	setNote(note);
}
Unavailable::Unavailable(unsigned startDay, unsigned startMonth, unsigned startYear, unsigned endDay, unsigned endMonth, unsigned endYear, char* note)
{
	setStart(startDay, startMonth, startYear);
	setEnd(endDay, endMonth, endYear);
	setNote(note);
}
Unavailable::Unavailable(const Unavailable& copy)
{
	this->copy(copy);
}
Unavailable& Unavailable::operator=(const Unavailable& rhs)
{
	this->copy(rhs);
	return *this;
}
Unavailable::Unavailable(Unavailable&& move) noexcept
{
	this->move(std::move(move));
}
Unavailable& Unavailable::operator=(Unavailable&& rhs) noexcept
{
	this->move(std::move(rhs));
	return *this;
}
Unavailable::~Unavailable()
{
	free();
}

void Unavailable::print(std::ostream& ostr) const
{
	ostr << strlen(this->getNote()) << " " << this->getNote() << " " << this->getStart() << " " << this->getEnd();
}
void Unavailable::read(std::istream& istr)
{
	unsigned size;
	istr >> size;
	char* readNote = new char[size];
	BulgarianDate readStart, readEnd;
	istr >> readNote;
	istr >> readStart;
	istr >> readEnd;

	this->setStart(readStart);
	this->setEnd(readEnd);
	this->setNote(readNote);
}

std::ostream& operator<<(std::ostream& ostr, const Unavailable& unav)
{
	unav.print(ostr);
	return ostr;
}
std::istream& operator>>(std::istream& istr, Unavailable& unav)
{
	unav.read(istr);
	return istr;
}
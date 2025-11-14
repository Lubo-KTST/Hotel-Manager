#pragma once
#include "Utils.h"
#pragma warning(disable:4996)

// Forward declaration of operators
class Unavailable;
std::ostream& operator<<(std::ostream& ostr, const Unavailable& unav);
std::istream& operator>>(std::istream& istr, Unavailable& unav);

class Unavailable
{
public:
	Unavailable() = default;
	Unavailable(BulgarianDate start, BulgarianDate end, char* note);
	Unavailable(unsigned startDay, unsigned startMonth, unsigned startYear, unsigned endDay, unsigned endMonth, unsigned endYear, char* note);
	Unavailable(const Unavailable& copy);
	Unavailable& operator=(const Unavailable& rhs);
	Unavailable(Unavailable&& move) noexcept;
	Unavailable& operator=(Unavailable&& rhs) noexcept;
	virtual ~Unavailable();
	virtual Unavailable* clone() const = 0;

	void setStart(BulgarianDate start);
	void setStart(unsigned startDay, unsigned startMonth, unsigned startYear);
	void setEnd(BulgarianDate end);
	void setEnd(unsigned endDay, unsigned endMonth, unsigned endYear);
	void setNote(const char* note);
	const BulgarianDate& getStart() const;
	const BulgarianDate& getEnd() const;
	const char* getNote() const;

	// Declare external stream operators as friends
	friend std::ostream& operator<<(std::ostream& ostr, const Unavailable& unav);
	friend std::istream& operator>>(std::istream& istr, Unavailable& unav);

protected:
	virtual void print(std::ostream& ostr) const;
	virtual void read(std::istream& istr);

private:
	BulgarianDate start; //default is 1.1.1
	BulgarianDate end;
	char* note = nullptr; 

	void free();
	void copy(const Unavailable& other);
	void move(Unavailable&& other);
};



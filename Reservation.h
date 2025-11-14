#pragma once
#include "Unavailable.h"

class Reservation;
std::ostream& operator<<(std::ostream& ostr, const Reservation& unav);
std::istream& operator>>(std::istream& istr, Reservation& unav);


class Reservation : public Unavailable
{
public:
	Reservation() = default;
	Reservation(BulgarianDate start, BulgarianDate end, char* note, unsigned peopleStaying);
	Reservation(unsigned startDay, unsigned startMonth, unsigned startYear, unsigned endDay, unsigned endMonth, unsigned endYear, char* note, unsigned peopleStaying);
	Reservation(const Reservation& copy);
	Reservation& operator=(const Reservation& rhs);
	Reservation(Reservation&& move) noexcept;
	Reservation& operator=(Reservation&& rhs) noexcept;
	~Reservation() override;
	Unavailable* clone() const override;

	unsigned getPeopleStaying() const;
	void setPeopleStaying(unsigned people);

	friend std::ostream& operator<<(std::ostream& ostr, const Reservation& unav);
	friend std::istream& operator>>(std::istream& istr, Reservation& unav);

protected:
	void print(std::ostream& ostr) const override;
	void read(std::istream& istr) override;
private:
	unsigned peopleStaying = 0;
};


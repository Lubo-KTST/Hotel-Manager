#pragma once
#include "Unavailable.h"

class Maintenance;
std::ostream& operator<<(std::ostream& ostr, const Maintenance& unav);
std::istream& operator>>(std::istream& istr, Maintenance& unav);


class Maintenance : public Unavailable
{
public:
	Maintenance() = default;
	Maintenance(BulgarianDate start, BulgarianDate end, char* note, unsigned price, unsigned workingStaff);
	Maintenance(unsigned startDay, unsigned startMonth, unsigned startYear, unsigned endDay, unsigned endMonth, unsigned endYear, char* note, unsigned price, unsigned workingStaff);
	Maintenance(const Maintenance& copy);
	Maintenance& operator=(const Maintenance& rhs);
	Maintenance(Maintenance&& move) noexcept;
	Maintenance& operator=(Maintenance&& rhs) noexcept;
	~Maintenance() override;
	Unavailable* clone() const override;

	unsigned getPrice() const;
	unsigned getWorkingStaff() const;
	void setPrice(unsigned price);
	void setWorkingStaff(unsigned staff);

	friend  std::ostream& operator<<(std::ostream& ostr, const Maintenance& unav);
	friend std::istream& operator>>(std::istream& istr, Maintenance& unav);

protected:
	void print(std::ostream& ostr) const override;
	void read(std::istream& istr) override;
private:
	unsigned price = 0;
	unsigned workingStaff = 0;
};

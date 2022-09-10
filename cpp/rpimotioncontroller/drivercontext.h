#ifndef DRIVERCONTEXT_H
#define DRIVERCONTEXT_H

class config;

class DriverContext
{
public:
	static DriverContext &instance();
	config *Configure() { return cfg; }

protected:
	DriverContext();
	DriverContext(const DriverContext &);

private:
	config *cfg;
};

#endif // DRIVERCONTEXT_H
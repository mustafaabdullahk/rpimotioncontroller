#include "drivercontext.h"
#include "drivers/config.h"
#include "drivers/ads1256.h"
#include "drivers/dac8532.h"

DriverContext &DriverContext::instance()
{
	static DriverContext ctx;
	return ctx;
}

DriverContext::DriverContext()
{
	cfg = new config();
}

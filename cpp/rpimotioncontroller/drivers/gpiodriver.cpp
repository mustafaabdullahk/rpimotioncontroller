#include "gpiodriver.h"
#include "3rdparty/debug.h"

gpiodriver::gpiodriver()
{
	basePath = "/sys/class/gpio";
}

int gpiodriver::gpioExport(uint8_t gpio)
{
	std::string path = basePath;
	path.append("/export");
	gWarn("gpio %s has exporting", std::to_string(gpio).data());
	return fwrite(path, std::to_string(gpio));
}

int gpiodriver::gpioSetMode(uint8_t pin, uint8_t mode)
{
	std::string path = basePath;
	if (mode == INPUT) {
		path.append("/gpio" + std::to_string(pin) + "/direction");
		gWarn("gpio %s has setting input mode", std::to_string(pin).data());
		return fwrite(path, "in");
	}
	if (mode == OUTPUT) {
		path.append("/gpio" + std::to_string(pin) + "/direction");
		gWarn("gpio %s has setting output mode", std::to_string(pin).data());
		return fwrite(path, "out");
	}
	gWarn("no such mode");
	return -ESRCH;
}

int gpiodriver::gpioGetValue(uint8_t pin)
{
	std::string path = basePath;
	path.append("/gpio" + std::to_string(pin) + "/value");
	return fread(path);
}

int gpiodriver::gpioSetValue(uint8_t pin, uint8_t value)
{
	std::string path = basePath;
	if (value == HIGH) {
		path.append("/gpio" + std::to_string(pin) + "/value");
		return fwrite(path, std::to_string(value));
	}
	if (value == LOW) {
		path.append("/gpio" + std::to_string(pin) + "/value");
		return fwrite(path, std::to_string(value));
	}
	gWarn("no such value");
	return -ESRCH;
}

int gpiodriver::fwrite(const std::string &path, const std::string value)
{
	std::ofstream outfile;
	outfile.open(path.data());
	if (outfile.is_open()) {
		outfile << value;
		outfile.close();
	} else {
		gWarn("file opening error %s", path.data());
		return -ENOENT;
	}
//	gWarn("file operation completed, '%s' value writed", value.data());
	return 0;
}

int gpiodriver::fread(const std::string &path)
{
	int value;
	std::ifstream infile;
	infile.open(path.data());
	if (infile.is_open()) {
		infile >> value;
		infile.close();
	} else {
		gWarn("file opening error %s", path.data());
		return -ENOENT;
	}
//	gWarn("file operation completed, '%s' value read", std::to_string(value).data());
	return value;
}

//
// Created by noartem on 04.02.2023.
//

#include "utility.h"

namespace elementor::components {
	void openURL(std::string url) {
#if defined(OS_HOST_WINDOWS)
		std::string command = "start " + url;
#elif defined(OS_HOST_LINUX)
		std::string command = "xdg-open " + url;
#elif defined(OS_HOST_MACOS)
		std::string command = "open " + url;
#endif

		system(command.c_str());
	}

	tm now_tm() {
		time_t now = time(nullptr);
		return *localtime(&now);
	}

	std::string leftPadAndFit(const std::string& value, unsigned int size, const char paddingChar) {
		if (value.length() == size) {
			return value;
		} else if (value.length() > size) {
			return value.substr(value.length() - size);
		} else {
			return std::string(size - value.length(), paddingChar) + value;
		}
	}

	int daysInMonth(int month, int year) {
		if (month == 4 || month == 6 || month == 9 || month == 11) {
			return 30;
		} else if (month == 2) {
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
				return 29;
			} else {
				return 28;
			}
		} else {
			return 31;
		}
	}
}

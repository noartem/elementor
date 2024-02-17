//
// Created by admin on 17.02.2024.
//

#ifndef ASSETS_INCLUDE_H
#define ASSETS_INCLUDE_H

#include <string.h>
#include <filesystem>

std::string asset(const std::string_view& name) {
	return std::filesystem::current_path()
		.append("..")
		.append("..")
		.append("..")
		.append("..")
		.append("src")
		.append("examples")
		.append("assets")
		.append(name)
		.string();
}

#endif //ASSETS_INCLUDE_H

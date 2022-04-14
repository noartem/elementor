//
// Created by noartem on 14.04.2022.
//

#include "./library/Platform.h"
#include "./library/Padding.h"

int main(void) {
	elementor::Platform platform;
	platform.title = "Elementor-test";
	platform.width = 960;
	platform.height = 640;

    elementor::Padding root_el;

	platform.run();
}
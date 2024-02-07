//
// Created by admin on 01.02.2024.
//

#ifndef UTILS_H
#define UTILS_H

namespace elementor::application {
	int ring(int i, unsigned n) {
		if (i > 0) return (n + i) % n;
		if (i < 0) return n - (-i % n);
		return 0;
	}

	int clamp(int i, int min, int max) {
		if (i < min) return min;
		if (i > max) return max;
		return i;
	}
}

#endif //UTILS_H

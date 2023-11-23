#pragma once

namespace Pilot {
	static float epsilonf = 0.01f;
	static bool equalishf(float a, float b) {
		float min = b - epsilonf;
		float max = b + epsilonf;
		return a > min && a < max;
	}
}
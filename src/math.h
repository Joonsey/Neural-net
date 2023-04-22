#include <cmath>

namespace math
{
	float sigmoid(const float x) {
		return 1.0f / (1.0f + std::exp(-x));
	}

}

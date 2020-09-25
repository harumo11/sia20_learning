#include <iostream>

namespace leptorino {
double cliping(const double leptorino_row_data)
{
    if (leptorino_row_data < 0) {
        return 0;
    } else if (leptorino_row_data > 400) {
        return 400;
    } else {
        return (1.0 / 200) * leptorino_row_data - 1;
    }
}

} // namespace leptorino

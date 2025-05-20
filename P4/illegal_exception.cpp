#include "illegal_exception.h"

const char* illegal_exception::illegal() const {
    return "illegal argument";  // Return the error message when caught
}

#include "utils.h"

/**
 * @brief Multi-platform function to clean terminal.
 *
 */
void clean_terminal() {
#if defined(__APPLE__) || defined(__linux__) || defined(__FreeBSD__)
    system("export TERM=xterm && reset");  // *nix
#elif defined(_WIN32)
    system("cls");  // windows
#endif
    return;
}
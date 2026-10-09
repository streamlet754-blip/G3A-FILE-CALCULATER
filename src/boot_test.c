#include <gint/display.h>
#include <gint/keyboard.h>

int main(void)
{
    dclear(C_WHITE);
    dtext(1, 1, C_BLACK, "fxSDK display and keyboard test");
    dtext(1, 20, C_BLACK, "Press any key to exit.");
    dupdate();

    getkey();
    return 1;
}
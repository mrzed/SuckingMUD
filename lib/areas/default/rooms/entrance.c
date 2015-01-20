#include <globals.h>

inherit ROOM_OB;

void create() {
    set_short(MUDLIB_NAME + " Entrance\n");
    set_long("This is the " + MUDLIB_NAME + " Entrance, written by Zed at " + MUDLIB_NAME + ". There sure isn't a whole lot here yet, though...\n");
    set_exits(([
    ]));
}
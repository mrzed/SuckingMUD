// /clone/hole.c
// first room object being used as start room and for testing room object
// Zed @ Lilypad
#include <globals.h>

inherit ROOM_OB;

void create() {
    set_short(MUDLIB_NAME + "(" + MUDLIB_VER + ")\n" + " Hole (void)\n");
    set_long("This is the " + MUDLIB_NAME + " Hole. This is a lame room, but it is just being build and used for testing purposes and for the void. Yay!\n");
    set_exits(([
        "south" : "/areas/default/rooms/entrance",
    ]));
}
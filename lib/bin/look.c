// file: /cmds/players/look.c
// Zed @ Lilypad Mudlib
// 06-07-2013

#include <command.h>

object room;

int main(string arg) {
    string *users, *objs, *exits;
    int i;

    room = environment(this_player());
    exits = keys(room->query_exits());
    write(room->query_short() + "\n" + room->query_long() + "\n");
    // query room exits. this needs to be changed to only write one
    // Exit, and if there are none, write No visible exits or some
    // crap like that. -zed
    if(sizeof(exits) < 1) {
        write("There are not obvious exits.\n");
    }
    if(sizeof(exits) ==1) {
        write("Exit:\n" + exits[i] + "\n");
    }
    else {
        write("Exits:\n");
        for(i = 0; i < sizeof(exits); i ++) {
            write(exits[i] + "\n");
        }
    }

    users = filter(all_inventory(room), (: living($1) && $1 != this_player() :));
    objs = filter(all_inventory(room), (: !living($1) :));

    if(sizeof(users) > 0) write(implode(users->query_name(), "\n") + " is standing here.\n");
    if(sizeof(objs) > 0) write(implode(objs->query_short(), "\n") + "\n");
    return 1;
}

string help() {
     return(" look\n"
     "Looks in your characters environment.\n");
}
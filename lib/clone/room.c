// /clone/room.c object file
// Zed @ Lilypad
#include <globals.h>

inherit BASE;

mapping exits = ([]);
string query_exit(string id);
mapping query_exits();
private string longdesc;
private string shortdesc;

int set_exits(mapping exit);
int rem_exit(string id);
int add_exit(string id, string path);
//int valid_exit(string exit);
int set(string name, mixed var);
void init_ob();

int set(string name, mixed var) {
     if(!ob_data || !mapp(ob_data)) init_ob();
     if(!name) return 0;
     if(ob_data[name]) map_delete(ob_data, name);
     ob_data += ([name : var]);
     return 1;
}

int set_exits(mapping exit) {
    exits = exit;
    set("exits", exit);
    return 1;
}

mapping query_exits() {
     mapping copy;
     copy = exits;
     return copy;
}

int valid_exit(string exit) {
    if(sizeof(exits) < 1) return 0;
    if(exits[exit]) return 1;
    return 0;
}

int rem_exit(string id) {
    if(sizeof(exits) < 1) return 0;
    if(!exits[id]) return 1;
    else map_delete(exits, id);
    set("exits", exits);
    return 1;
}

int add_exit(string id, string path) {
     if(exits[id]) map_delete(exits, id);
     exits += ([id : path]);
     set("exits", exits);
     return 1;
}

// rooms cannot be moved
int move(mixed dest) {
}

// long dsecription

void set_long(string ld) {
    longdesc = ld;
}

void set_short(string sd) {
    shortdesc = sd;
    }

string query_long() {
    return longdesc;
}

string query_short() {
    return shortdesc;
}

string query_exit(string id) {
     if(sizeof(exits) < 1) return 0;
     if(exits[id]) return exits[id];
}
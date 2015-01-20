/* vim:set ft=lpc: */
/* Last Indented: 1360770374 */
// set to 'private static' so that inheritor won't be able to directly
// access this variable and so that save_object() won't save it to the .o file

string *ids;

int set(string name, mixed var);
void init_ob();

mapping ob_data;

int set(string name, mixed var) {
     if(!ob_data || !mapp(ob_data)) init_ob();
     if(!name) return 0;
     if(ob_data[name]) map_delete(ob_data, name);
     ob_data += ([name : var]);
     return 1;
}

void remove()
{
    // add code here to prevent unwanted destructions.
    // update attributes of the container and the containees.
    destruct(this_object());
}

int move(mixed dest)
{
    // add code here to prevent disallowed moves (target is full, object
    // is immovable, etc.).
    move_object(dest);
}

void set_ids(string *arg)
{
    // probably want to add some security here.
    ids = arg;
}

int id(string arg)
{
    if (!arg || !ids) {
        return 0;
    }
    return (member_array(arg, ids) != -1);
}

void init_ob() {
     ob_data = ([]);
}
/* vim:set ft=lpc: */
/* Last Indented: 1360770374 */
// added remove_interactive to allow for proper reconnects in get_password func - 19 Jan, 2015; Zed @ Lilypad
#include <globals.h>

// needs fixed to handle passwords

void catch_tell(string str)
{
    receive(str);
}

private void create_user_object(string name)
{
    object user;

    ACCOUNT_D->set_online(name);
    write("\n");
    cat(MOTD);
    write("\n");
    user = new(USER_OB);
    user->set_name(name);
    exec(user, this_object());
    user->setup();
    user->move(VOID_OB);
    destruct(this_object());
}

void logon()
{
    printf("Welcome to %s (SuckingMUD mudlib %s).\n\n%s login: ", __VERSION__, MUDLIB_VERSION, MUD_NAME);
    input_to("get_username", INPUT_TO_NOBYPASS);
}

void get_username(string name)
{
    name = ACCOUNT_D->normalize_account_name(name);

    if(ACCOUNT_D->account_exists(name)) {
        write("Password: ");
        input_to("get_password", INPUT_TO_NOBYPASS|INPUT_TO_NOECHO, name);
    } else {
        if(ACCOUNT_D->valid_account_name(name)) {
            write("Hello " + name + ", enter a password: ");
            input_to("new_password", INPUT_TO_NOBYPASS|INPUT_TO_NOECHO, name);
        } else {
            printf("\nLogin incorrect\n\n%s login: ", MUD_NAME);
            input_to("get_username", INPUT_TO_NOBYPASS);
        }
    }
}

void get_password(string password, string name) {
    object user;

    if(ACCOUNT_D->password_match(name, password)) {
        if(user = find_player(name)) {
            remove_interactive(user)
            exec(user, this_object());
            user->reconnect();
            destruct(this_object());
        }
        else {
            create_user_object(name);
        }
    }
    else {
        printf("\nLogin incorrect\n\n%s login: ", MUD_NAME);
        input_to("get_username", INPUT_TO_NOBYPASS);
    }
}

void new_password(string password, string name)
{
    if(ACCOUNT_D->valid_password(password)) {
        write("\nenter it again: ");
        input_to("verify_new_password", INPUT_TO_NOBYPASS|INPUT_TO_NOECHO, password, name);
    } else {
        write("\nInvalid password.\n\nEnter a password: ");
        input_to("new_password", INPUT_TO_NOBYPASS|INPUT_TO_NOECHO, name);
    }
}

void verify_new_password(string new_password, string password, string name)
{
    if(new_password != password) {
        write("\nPassword mismatch.\n\nEnter a password: ");
        input_to("new_password", INPUT_TO_NOBYPASS|INPUT_TO_NOECHO, name);
        return;
    } else {
        write("\nNow, enter an email address: ");
        input_to("new_email", INPUT_TO_NOBYPASS, name, password);
    }
}

void new_email(string email, string name, string password)
{
    if(ACCOUNT_D->valid_email(email)) {
        if(!ACCOUNT_D->account_exists(name)) {
            ACCOUNT_D->create_account(name, password, email);
            create_user_object(name);
        } else {
            printf("Somebody else JUST beat you to that account name!\n\n%s login: ", MUD_NAME);
            input_to("get_username", INPUT_TO_NOBYPASS);
        }
    } else {
        write("Invalid email.\n\nPlease, enter an email address: ");
        input_to("new_email", INPUT_TO_NOBYPASS, name, password);
    }
}


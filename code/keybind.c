
// function to check for specific input keys and return their scancodes!
int keybind_return_scancode_from_letter(STRING *key)
{
    // nothing in the string ?
    if (key == NULL || str_len(key) <= 0)
    {
        diag("\nERROR! Can't return a scancode from letter! Nothing in the key string!");
        return -1;
    }

    // convert into lower case
    str_lwr(key);

    // check if it's 'none'
    if (str_cmpi(key, input_none_str))
    {
        return -1;
    }

    // expand with additional keys if needed
    if (str_cmpi(key, mouse_left_str))
    {
        return 280;
    }
    else if (str_cmpi(key, mouse_right_str))
    {
        return 281;
    }
    else if (str_cmpi(key, mouse_middle_str))
    {
        return 282;
    }

    // check if the given key can return a proper scancode
    int temp_scancode = key_for_str(key);
    if (temp_scancode > 0)
    {
        return temp_scancode;
    }

    // if nothing worked correctly, then return -1
    diag("\nERROR! Can't return a scancode from letter! No scancode was found!");
    return -1;
}

// return a letter from the given scancode
// this can be used for saving input from the game options
STRING *keybind_return_letter_from_scancode(int scancode)
{
    // check if scancode is correct
    // correct range is from 1 to 282
    if (scancode <= 0 || scancode > 282)
    {
        diag("\nERROR! Given scancode is out of range!");
        return "";
    }

    STRING *tmp_str = "#16";
    str_for_key(tmp_str, scancode);

    switch (scancode)
    {
    case 280:
        str_cpy(tmp_str, mouse_left_str);
        break;

    case 281:
        str_cpy(tmp_str, mouse_right_str);
        break;

    case 282:
        str_cpy(tmp_str, mouse_middle_str);
        break;

    default:
        break;
    }

    return tmp_str;
}
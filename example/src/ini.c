#include <acknex.h>
#include <windows.h>
#include "ini.h"

char iniBuffer[2048];

void path_make_absolute(STRING *path)
{
	static STRING *tmp = "#1024";
	str_cpy(tmp, save_dir);
	str_cat(tmp, "\\");
	str_cat(tmp, path);
	str_cpy(path, tmp);
}

void ini_write(STRING *filename, STRING *section, STRING *entry, STRING *value)
{
	WritePrivateProfileString(_chr(section), _chr(entry), _chr(value), _chr(filename));
}

void ini_write_int(STRING *filename, STRING *section, STRING *entry, int value)
{
	ini_write(filename, section, entry, str_for_int(NULL, value));
}

void ini_write_var(STRING *filename, STRING *section, STRING *entry, var value)
{
	ini_write(filename, section, entry, str_for_num(NULL, value));
}

void ini_write_float(STRING *filename, STRING *section, STRING *entry, float value)
{
	ini_write(filename, section, entry, str_for_float(NULL, value));
}

int ini_read_sections(TEXT *txt, STRING *filename)
{
	int length = GetPrivateProfileString(NULL, NULL, NULL, iniBuffer, 2047, _chr(filename));
	int i = 0;
	char *str = iniBuffer;
	while (str < (iniBuffer + length))
	{
		(txt->pstring)[i] = str_create(str);
		str = str + strlen(str) + 1;
		i++;
	}
	return i;
}

int ini_read(STRING *targetValue, STRING *filename, STRING *section, STRING *entry, STRING *defaultValue)
{
	int length = GetPrivateProfileString(_chr(section), _chr(entry), _chr(defaultValue), iniBuffer, 2047, _chr(filename));
	if (targetValue != NULL)
		str_cpy(targetValue, iniBuffer);
	return length;
}

int ini_read_char(STRING *targetValue, STRING *filename, STRING *section, STRING *entry, STRING *defaultValue)
{
	int length = GetPrivateProfileString(_chr(section), _chr(entry), _chr(defaultValue), iniBuffer, 2047, _chr(filename));
	if (targetValue != NULL)
		strcpy(targetValue, iniBuffer);
	return length;
}

int ini_read_int(STRING *filename, STRING *section, STRING *entry, int defaultValue)
{
	STRING *tmp = "#64";
	STRING *def = "#64";
	ini_read(tmp, filename, section, entry, str_for_int(def, defaultValue));
	return str_to_int(tmp);
}

var ini_read_var(STRING *filename, STRING *section, STRING *entry, var defaultValue)
{
	STRING *tmp = "#64";
	STRING *def = "#64";
	ini_read(tmp, filename, section, entry, str_for_num(def, defaultValue));
	return str_to_num(tmp);
}

float ini_read_float(STRING *filename, STRING *section, STRING *entry, float defaultValue)
{
	STRING *tmp = "#64";
	STRING *def = "#64";
	ini_read(tmp, filename, section, entry, str_for_float(def, defaultValue));
	return str_to_float(tmp);
}

// helper function for reading/writting settings into the file
// file path should be absolute (use path_make_absolute for it)
void ini_read_write(STRING *value, STRING *file, STRING *section, STRING *entry, STRING *default_value)
{
	// check if key bindings is there, if not write default one
	if (ini_read(NULL, file, section, entry, "") == 0)
	{
		ini_write(file, section, entry, default_value);
		str_cpy(value, default_value);
	}
	else
	{
		STRING *tmp_str = "#32";
		ini_read(tmp_str, file, section, entry, default_value);
		str_cpy(value, tmp_str);
	}
}

// same as above but for ints
void ini_read_write_int(int *value, STRING *file, STRING *section, STRING *entry, int default_value)
{
	// check if key bindings is there, if not write default one
	if (ini_read(NULL, file, section, entry, "") == 0)
	{
		ini_write(file, section, entry, _chr(str_for_int(NULL, default_value)));
		*value = default_value;
	}
	else
	{
		STRING *tmp_str = "#32";
		ini_read(tmp_str, file, section, entry, _chr(str_for_int(NULL, default_value)));
		*value = str_to_int(tmp_str);
	}
}

// same as above, but value is a var
void ini_read_write_var(var *value, STRING *file, STRING *section, STRING *entry, var default_value)
{
	// check if key bindings is there, if not write default one
	if (ini_read(NULL, file, section, entry, "") == 0)
	{
		ini_write(file, section, entry, _chr(str_for_num(NULL, default_value)));
		*value = default_value;
	}
	else
	{
		STRING *tmp_str = "#32";
		ini_read(tmp_str, file, section, entry, _chr(str_for_num(NULL, default_value)));
		*value = str_to_num(tmp_str);
	}
}

// same as above but for floats
void ini_read_write_float(float *value, STRING *file, STRING *section, STRING *entry, float default_value)
{
	// check if key bindings is there, if not write default one
	if (ini_read(NULL, file, section, entry, "") == 0)
	{
		ini_write(file, section, entry, _chr(str_for_float(NULL, default_value)));
		*value = default_value;
	}
	else
	{
		STRING *tmp_str = "#32";
		ini_read(tmp_str, file, section, entry, _chr(str_for_float(NULL, default_value)));
		*value = str_to_float(tmp_str);
	}
}

// same as above, but value is a char
void ini_read_write_char(STRING *value, STRING *file, STRING *section, STRING *entry, char *default_value)
{
	// check if key bindings is there, if not write default one
	if (ini_read(NULL, file, section, entry, "") == 0)
	{
		ini_write(file, section, entry, default_value);
		strcpy(value, default_value);
	}
	else
	{
		STRING *tmp_str = "#32";
		ini_read(tmp_str, file, section, entry, default_value);
		strcpy(value, _chr(tmp_str));
	}
}

// same as above, but read the scancode from the letter (str)
void ini_read_write_keybind(int *value, STRING *file, STRING *section, STRING *entry, STRING *default_value)
{
	// check if key bindings is there, if not write default one
	if (ini_read(NULL, file, section, entry, "") == 0)
	{
		ini_write(file, section, entry, default_value);
		*value = keybind_return_scancode_from_letter(default_value);
	}
	else
	{
		STRING *tmp_str = "#32";
		ini_read(tmp_str, file, section, entry, default_value);
		*value = keybind_return_scancode_from_letter(tmp_str);
	}
}
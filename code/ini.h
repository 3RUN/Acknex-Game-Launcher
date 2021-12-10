#ifndef _INI_H_
#define _INI_H_

/**
 * \file ini.h
 * \brief INI Access.
 *
 * ini.h provides functions to read or write ini files.
 */

/**
 * Makes a path absolute.
 * \param	path	The path to make absolute.
 */
void path_make_absolute(STRING *path);

/**
 * Writes a string into an ini file.
 * \param	filename	The absolute path to the filename of the ini file.
 * \param	section		The section to write into.
 * \param	entry		The key of the section entry to write.
 * \param	value		The value which will be written into the key entry.
 */
void ini_write(STRING *filename, STRING *section, STRING *entry, STRING *value);

/**
 * Writes an integer into an ini file.
 * \param	filename	The absolute path to the filename of the ini file.
 * \param	section		The section to write into.
 * \param	entry		The key of the section entry to write.
 * \param	value		The value which will be written into the key entry.
 */
void ini_write_int(STRING *filename, STRING *section, STRING *entry, int value);

/**
 * Writes a var into an ini file.
 * \param	filename	The absolute path to the filename of the ini file.
 * \param	section		The section to write into.
 * \param	entry		The key of the section entry to write.
 * \param	value		The value which will be written into the key entry.
 */
void ini_write_var(STRING *filename, STRING *section, STRING *entry, var value);

/**
 * Writes a float into an ini file.
 * \param	filename	The absolute path to the filename of the ini file.
 * \param	section		The section to write into.
 * \param	entry		The key of the section entry to write.
 * \param	value		The value which will be written into the key entry.
 */
void ini_write_float(STRING *filename, STRING *section, STRING *entry, float value);

/**
 * Reads all sections from an ini file into a TEXT object.
 * \param	txt			The TEXT object where the sections will be stored in.
 * \param	filename	The absolute path to the filename of the ini file.
 * \return				Number of sections read from the ini file.
 */
int ini_read_sections(TEXT *txt, STRING *filename);

/**
 * Reads a string from an ini file.
 * \param	targetValue		The string where the result will be stored in.
 * \param	filename		The absolute path to the filename of the ini file.
 * \param	section			The section to read from.
 * \param	entry			The key of the section entry to read.
 * \param	defaultValue	The default value which will be written into the return value if the key doesn't exist.
 * \return					Number of characters read into the string.
 */
int ini_read(STRING *targetValue, STRING *filename, STRING *section, STRING *entry, STRING *defaultValue);
int ini_read_char(STRING *targetValue, STRING *filename, STRING *section, STRING *entry, STRING *defaultValue);

/**
 * Reads an integer from an ini file.nichts
 * \param	filename		The absolute path to the filename of the ini file.
 * \param	section			The section to read from.
 * \param	entry			The key of the section entry to read.
 * \param	defaultValue	The default value which will be returned if the key doesn't exist.
 * \return					The entry value converted to an integer.
 */
int ini_read_int(STRING *filename, STRING *section, STRING *entry, int defaultValue);

/**
 * Reads a float from an ini file.
 * \param	filename		The absolute path to the filename of the ini file.
 * \param	section			The section to read from.
 * \param	entry			The key of the section entry to read.
 * \param	defaultValue	The default value which will be returned if the key doesn't exist.
 * \return					The entry value converted to an float.
 */
float ini_read_float(STRING *filename, STRING *section, STRING *entry, float defaultValue);

/**
 * Reads a var from an ini file.
 * \param	filename		The absolute path to the filename of the ini file.
 * \param	section			The section to read from.
 * \param	entry			The key of the section entry to read.
 * \param	defaultValue	The default value which will be returned if the key doesn't exist.
 * \return					The entry value converted to a var.
 */
var ini_read_var(STRING *filename, STRING *section, STRING *entry, var defaultValue);

// helper function for reading/writting settings into the file
// file path should be absolute (use path_make_absolute for it)
void ini_read_write(STRING *value, STRING *file, STRING *section, STRING *entry, STRING *default_value);

// same as above but for ints
void ini_read_write_int(int *value, STRING *file, STRING *section, STRING *entry, int default_value);

// same as above, but value is a var
void ini_read_write_var(var *value, STRING *file, STRING *section, STRING *entry, var default_value);

// same as above but for floats
void ini_read_write_float(float *value, STRING *file, STRING *section, STRING *entry, float default_value);

// same as above, but value is a char
void ini_read_write_char(STRING *value, STRING *file, STRING *section, STRING *entry, char *default_value);

// same as above, but read the scancode from the letter (str)
void ini_read_write_keybind(int *value, STRING *file, STRING *section, STRING *entry, STRING *default_value);

#include "ini.c"
#endif
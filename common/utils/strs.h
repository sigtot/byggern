/**
 * @file strs.h
 * @brief String utils
 */
#ifndef STRS_H
#define STRS_H

/**
 * Get integer values from substrings formattet as {key=value}
 * @param  substr     sub string
 * @param  key_length key length
 * @return            value
 */
int get_value_from_substr(char* substr, int key_length);

#endif

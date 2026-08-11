#ifndef JSON_UTIL_H
#define JSON_UTIL_H
#include "main.h"

/**
 * Get integer value from cJSON object
 * @param root json object root
 * @param key target field name
 * @param out output long value
 * @return 0 success, -1 field not found or not a number
 */
int json_get_int(const cJSON *root, const char *key, long *out);

#endif

#include "json_util.h"

int json_get_int(const cJSON *root, const char *key, long *out)
{
    const cJSON *item = cJSON_GetObjectItemCaseSensitive(root, key);
    if (!cJSON_IsNumber(item)) {
        return -1;
    }

    *out = (long)item->valuedouble;
    return 0;
}

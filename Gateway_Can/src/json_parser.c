#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "can_bridge.h"
#include "cJSON.h"

int json_get_int(const char *json_str, const char *key, long *out)
{
	if (!json_str || !key || !out) {
		return -1;
	}

	cJSON *json = cJSON_Parse(json_str);
	if (!json) {
		fprintf(stderr, "[JSON] Parse failed: %s\n", cJSON_GetErrorPtr());
		return -1;
	}

	cJSON *item = cJSON_GetObjectItem(json, key);
	if (!item || !cJSON_IsNumber(item)) {
		cJSON_Delete(json);
		return -1;
	}

	*out = (long)item->valuedouble;
	cJSON_Delete(json);
	return 0;
}

cJSON *json_parse(const char *json_str)
{
	if (!json_str) {
		return NULL;
	}

	cJSON *json = cJSON_Parse(json_str);
	if (!json) {
		fprintf(stderr, "[JSON] Parse failed: %s\n", cJSON_GetErrorPtr());
		return NULL;
	}

	return json;
}

void json_delete(cJSON *json)
{
	if (json) {
		cJSON_Delete(json);
	}
}

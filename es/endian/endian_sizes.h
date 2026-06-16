
#ifndef _ES_H_
#define _ES_H_

#include <sys/utsname.h>
#include <stdint.h>
#include <time.h>

typedef struct lm_hello_struct {
    int32_t id;
    time_t magic;
} lm_hello;

typedef enum lm_response_status {
    LM_FEATURE_RESPONSE = 10,
    LM_CAPACITY_RESPONSE = 20,
    LM_FEATURE_NOT_FOUND = 30,
    LM_LICENCE_NOT_FOUND = 40,
    LM_NULL_RESPONSE = 0 /* A place holder */
} lm_response_status;


#endif /* _LMCOM_H_ */

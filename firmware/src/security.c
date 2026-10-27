/**
 * @file security.c
 * @author Samuel Meyers
 * @brief Stub file to hold security checks
 * @date 2026
 *
 * This source file is part of an example system for MITRE's 2026 Embedded CTF (eCTF).
 * This code is being provided only for educational purposes for the 2026 MITRE eCTF competition,
 * and may not meet MITRE standards for quality. Use this code at your own risk!
 *
 * @copyright Copyright (c) 2026 The MITRE Corporation
 */

#include "security.h"
#include "secrets.h"
#include "host_messaging.h"
#include <string.h>
#include "wolfssl/wolfcrypt/pwdbased.h"

bool check_pin(unsigned char *pin) {
    print_debug("Checking PIN\n");

    for (int i = 0; i < PIN_LENGTH; i++) {

        if (pin[i] != HSM_PIN[i]) {
            return false;
        }

        for (int i = 0; i < 25; i++) {
            DL_Common_delayCycles(3200000);
        }

    }

    return true;
}

bool validate_permission(uint16_t group_id, permission_enum_t perm) {
    char output_buf[128] = {0};

    sprintf(output_buf, "Checking %c permissions for group: %hx\n", perm, group_id);
    print_debug(output_buf);

    // TODO: the reference design doesn't implement *ANY* security.
    // This function currently does nothing. Your team should add the
    // appropriate security checks here to implement the security
    // requirements.
    return true;
}

//
//
// HINTS BELOW
//
//


//
// ConstantCompare
//

/*

int ConstantCompare(const byte* a, const byte* b, int length) {
    int i;
    int compareSum = 0;

    for (i = 0; i < length; i++) {
        // Here you want to bitwise OR the result of XORing a, b
    }

    // return the XOR the comparesum to the CON_CMP_PASS magic value
}

    // Then in the return function ensure that the return value is the CON_CMP_PASS magic value, indicating pass

*/






//
// PBKDF2
//


/*
bool check_pbkdf2_pin(unsigned char *pin) {

    print_debug("Checking PIN\n");
    uint8_t kdk[32];
    // Use the wc_PBKDF2 function to perfrom the hash
        // wc_PBKDF2 (use kdk as your 32 byte output buffer, input, pin length, salt, salt length, iteration count, length of hash (same size as buffer), use WC_HASH_TYPE_SHA256)

    // Check that the wc_PBKDF2 function returned 0 for success
    // AND then compare the hash output the the saved hash, ensuring that the comparison passes and return a bool
}

*/


//
// If you want to see each cycle of the OG insecure PIN check
//

/* Put me in the for loop :)
        // char buf[32];
        // snprintf(buf, sizeof(buf), "pin[%d]=%u HSM=%u", i, pin[i], HSM_PIN[i]);
        // print_debug(buf);
*/
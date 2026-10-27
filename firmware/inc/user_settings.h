/**
 * WolfSSL user settings for PIN unwrap only (PBKDF2 + AES-GCM).
 * Used only by pin_unwrap.c. No other part of the firmware uses WolfSSL.
 */
#ifndef WOLF_CRYPT_USER_SETTINGS_H
#define WOLF_CRYPT_USER_SETTINGS_H

#define HAVE_CURVE25519
#define HAVE_ED25519
#define WOLFSSL_SHA512

#define WOLFSSL_SP_MATH
#define WOLFSSL_HAVE_SP_ED25519

// #define CUSTOM_RAND_GENERATE_BLOCK wc_trng_wrapper

/* Disable unneeded features to reduce size and avoid extra deps */
#define NO_RSA
#define NO_ECC
#define NO_DH
#define NO_DSA
// #define NO_DEV_RANDOM
// #define WOLFSSL_NO_ENTROPY_BLOCK


#endif /* WOLF_CRYPT_USER_SETTINGS_H */

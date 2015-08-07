/*
 * pam_kdf.so - derive a key from the user's authtok
 */

#define PAM_SM_AUTH

#include <stddef.h>
#include <string.h>
#include <unistd.h>

#include <keyutils.h>
#include <openssl/evp.h>

#include <security/pam_modules.h>
#include <security/pam_ext.h>

PAM_EXTERN int
pam_sm_authenticate(pam_handle_t *pamh, int flags,
		int argc, const char **argv)
{
	int ret;

	char const *user;
	ret = pam_get_item(pamh, PAM_USER, (void const **)&user);
	if (ret != PAM_SUCCESS)
		return PAM_IGNORE;
	int user_len = strlen(user);

	char const *pw;
	ret = pam_get_item(pamh, PAM_AUTHTOK, (void const **)&pw);
	if (ret != PAM_SUCCESS)
		return PAM_IGNORE;
	int pw_len = strlen(pw);

	int key_len = 24;
	char key[24];

	PKCS5_PBKDF2_HMAC_SHA1(pw, pw_len, user, user_len, 1000, key_len, key);
	add_key("user", "login", key, key_len, KEY_SPEC_SESSION_KEYRING);

	return PAM_SUCCESS;
}

PAM_EXTERN int
pam_sm_setcred(pam_handle_t *pamh, int flags,
		int argc, const char **argv)
{
	return PAM_IGNORE;
}

pam_kdf
=======

The `pam_kdf.so` module derives a key from a user's password and stores it
inside the current
[session keyring](https://www.kernel.org/doc/Documentation/security/keys.txt).
The helper script `keyctl-ssh-helper` allows you to use this key to decrypt
your ssh keys and destroys it afterwards.

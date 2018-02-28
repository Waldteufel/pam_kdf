pam_kdf
=======

The `pam_kdf.so` module derives a key from a user's password and stores it
inside the current
[session keyring](https://www.kernel.org/doc/Documentation/security/keys.txt).
The helper script `keyctl-ssh-helper` allows you to use this key to decrypt
your ssh keys.

Example (Arch Linux):
```
~> cat /etc/pam.d/system-login 
#%PAM-1.0

auth       required   pam_tally.so         onerr=succeed file=/var/log/faillog
auth       required   pam_shells.so
auth       requisite  pam_nologin.so
auth       include    system-auth
-auth      optional   pam_kdf.so

account    required   pam_access.so
account    required   pam_nologin.so
account    include    system-auth

password   include    system-auth

session    optional   pam_loginuid.so
session    optional   pam_exec.so type=open_session /usr/local/lib/keyctl-ssh-helper
session    optional   pam_exec.so /usr/bin/keyctl purge user login
session    optional   pam_keyinit.so       force revoke
session    include    system-auth
session    optional   pam_motd.so          motd=/etc/motd
session    optional   pam_mail.so          dir=/var/spool/mail standard quiet
-session   optional   pam_systemd.so
session    required   pam_env.so
```

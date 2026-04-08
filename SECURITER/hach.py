import hashlib
import os


def hash_password(password):
    salt = os.urandom(16)
    hashed = hashlib.sha256(salt + password.encode()).hexdigest()
    return salt.hex() + ":" + hashed

def verify_password(stored, password):
    salt, hashed = stored.split(":")
    salt = bytes.fromhex(salt)
    return hashed == hashlib.sha256(salt + password.encode()).hexdigest()
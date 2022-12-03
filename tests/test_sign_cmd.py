from hashlib import sha256
from sha3 import keccak_256
import base64
import ed25519
from ecdsa.curves import SECP256k1
from ecdsa.keys import VerifyingKey
from ecdsa.util import sigdecode_der

from accumulate_client.transaction import Transaction

def test_sign_tx(cmd, button):
    #this test uses the btc type for an AddCredits transaction test vector
    #bip32_path: str = "m/44'/0'/0'/0/0"
    bip32_path: str = "m/44'/281'/0'/0'/0'"

    pub_key, chain_code = cmd.get_public_key(
        bip32_path=bip32_path,
        display=False
    )  # type: bytes, bytes

    #if using ed25519
    pk: VerifyingKey = ed25519.VerifyingKey(pub_key)

    #pk: VerifyingKey = VerifyingKey.from_string(
    #    pub_key,
    #    curve=SECP256k1,
    #    hashfunc=sha256
    #)
    #TODO: make a real accumulate transaction instead of using a test vector
    # tx = Transaction(
    #     nonce=1,
    #     to="0xde0b295669a9fd93d5f28d9ec85e40f4cb697bae",
    #     value=666,
    #     memo="For u EthDev"
    # )
    addCreditsEnv = base64.b64decode("AWwBAgIg5V2XO/aROByUYCNU0eH2VfexxL1Wdg3/7/or70VB7BEEHWFjYzovL2xpdGUtdG9rZW4tYWNjb3VudC5hY21lBQEG0oXYzAQIk5O6jZnbPbHEE7Gi5NtJu3yNqEi3FA+AHNdakfoUDXMDXgFAAR1hY2M6Ly9saXRlLXRva2VuLWFjY291bnQuYWNtZQJvlL7eHp8epW1/aIh8LrTc4mzUeuBdsMG4CjCmdPS7fQIaAQ4CE2FjYzovL2FkaS5hY21lL3BhZ2UDAWQ=")
    addCreditsExpectedSig = bytes.fromhex("e71e78820f8030bcafda539dcb6796a8e782f96624ec2209f6d5ff7326f12227710018919153a67310237deafa2ac65e6a8e54aa02e367a72670b1de836ce90d")

    #signing test vector for an AddCredits transaction
    v, sig = cmd.sign_tx(bip32_path=bip32_path,
                             envelope=addCreditsEnv,
                             button=button)


    #if using ed25519
    #does signature match the expected signature
    assert sig == addCreditsExpectedSig

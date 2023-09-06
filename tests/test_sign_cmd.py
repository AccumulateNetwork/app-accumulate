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
    bip32_path: str = "m/44'/281'/0'/0'/0'"

    pub_key, chain_code = cmd.get_public_key(
        bip32_path=bip32_path,
        display=False
    )  # type: bytes, bytes

    addCreditsEnv = base64.b64decode("AWwBAgIg5V2XO/aROByUYCNU0eH2VfexxL1Wdg3/7/or70VB7BEEHWFjYzovL2xpdGUtdG9rZW4tYWNjb3VudC5hY21lBQEG0oXYzAQIA5zjhbHEh6dxOeGcKW/dY65+FJJgvDhTskX47sVixiYDZQFAAR1hY2M6Ly9saXRlLXRva2VuLWFjY291bnQuYWNtZQKxQYaPz8Ii5tazeiqo/mIeJvGoPYFrnTz8CKMYmL31ywIhAQ4CE2FjYzovL2FkaS5hY21lL3BhZ2UDAwMNQASA4esX")
    addCreditsExpectedSig = bytes.fromhex("50edaa8520374aa560845d797a35309caadd823427f4218c1ede364445b884d19671ab5546ab026c388887ec2986ef95e7eef71239bf1c5fc7e2eb040390dc0f")

    #signing test vector for an AddCredits transaction
    v, sig = cmd.sign_tx(bip32_path=bip32_path,
                            envelope=addCreditsEnv,
                            signing_token=bytearray(),
                            button=button)

    assert sig == addCreditsExpectedSig


    sendTokensEnv = base64.b64decode("AWIBAgIg5V2XO/aROByUYCNU0eH2VfexxL1Wdg3/7/or70VB7BEEE2FjYzovL2FkaS5hY21lL0FDTUUFAQbShdjMBAinZDJnLNeDTrJoc6M9PgCjUMWpo6/5t8xQY320kx5LRwNYATYBE2FjYzovL2FkaS5hY21lL0FDTUUChOAy+6ilRW9jHIIqKyRmwYs/p4BDMKuHCI7W4w1pBQUCHgEDBBoBFWFjYzovL290aGVyLmFjbWUvQUNNRQIBZA==")
    sendTokensExpectedSig = bytes.fromhex("d8debe3221731ec4c680edcf38caf08a29e94157f92e5d769bfc942f2f794bd39d13bcbd8ff63d24e060a61a6f0de80b035bc4f52c826104eebf91daefb37309")

    #signing test vector for an SendTokens transaction
    v, sig = cmd.sign_tx(bip32_path=bip32_path,
                         envelope=sendTokensEnv,
                         signing_token=bytearray(),
                         button=button)

    assert sig == sendTokensExpectedSig


    # now try blind signing
    print("testing blind signing: obtaining signing token\n")
    signing_token = cmd.get_blind_signing_token(button=button)
    print("testing blind signing: blind signing transaction\n")
    v, sig = cmd.sign_tx(bip32_path=bip32_path,
                         envelope=sendTokensEnv,
                         signing_token=signing_token,
                         button=button
                         )

    assert sig == sendTokensExpectedSig




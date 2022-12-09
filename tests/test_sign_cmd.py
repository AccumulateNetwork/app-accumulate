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

    addCreditsEnv = base64.b64decode("AWwBAgIg5V2XO/aROByUYCNU0eH2VfexxL1Wdg3/7/or70VB7BEEHWFjYzovL2xpdGUtdG9rZW4tYWNjb3VudC5hY21lBQEG0oXYzAQI+3GnRMrYm4M8PL9aznQPqgen8N7LHYQJbGJKyzTmPK4DZQFAAR1hY2M6Ly9saXRlLXRva2VuLWFjY291bnQuYWNtZQJvlL7eHp8epW1/aIh8LrTc4mzUeuBdsMG4CjCmdPS7fQIhAQ4CE2FjYzovL2FkaS5hY21lL3BhZ2UDAwMNQASA4esX")
    addCreditsExpectedSig = bytes.fromhex("f63db453eeb6491f768d8ad851318e68871e7aedc542f6ac6488f67c05630591fa53687f196657a81de5a2e71ae7d92eccb9227a26543c9cc2202bb97960ae02")

    #signing test vector for an AddCredits transaction
    v, sig = cmd.sign_tx(bip32_path=bip32_path,
                             envelope=addCreditsEnv,
                             button=button)

    assert sig == addCreditsExpectedSig


    sendTokensEnv = base64.b64decode("AWIBAgIg5V2XO/aROByUYCNU0eH2VfexxL1Wdg3/7/or70VB7BEEE2FjYzovL2FkaS5hY21lL0FDTUUFAQbShdjMBAjSrYa1DtgCBujPXB8bOLnr7xmND/IviTjL5kaNmORevQNYATYBE2FjYzovL2FkaS5hY21lL0FDTUUCOd4zdbtdCwQpzXNkjQqRSCbP+9V1uqlIN2j7Y12wd2QCHgEDBBoBFWFjYzovL290aGVyLmFjbWUvQUNNRQIBZA==")
    sendTokensExpectedSig = bytes.fromhex("dce3a9272df19110bd4a2db7b0f55d7dd99537dab9eb4faed281cb3b07554d034c326743138e481f70db768e37ca0b0ea125b54bd48e7e93aa636082b7b6690b")

    #signing test vector for an AddCredits transaction
    v, sig = cmd.sign_tx(bip32_path=bip32_path,
                         envelope=sendTokensEnv,
                         button=button)

    assert sig == sendTokensExpectedSig



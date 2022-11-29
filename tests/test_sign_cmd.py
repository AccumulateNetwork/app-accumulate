from hashlib import sha256
from sha3 import keccak_256

import ed25519
from ecdsa.curves import SECP256k1
from ecdsa.keys import VerifyingKey
from ecdsa.util import sigdecode_der

from boilerplate_client.transaction import Transaction


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

    #btc signing test vector for an AddCredits transaction
    tx = bytes.fromhex("008b01020220e55d973bf691381c94602354d1e1f655f7b1c4bd56760dffeffa2bef4541ec11043b6163633a2f2f6336613632396639613635626632313135396335646662666662633836386563336165363163653436353131303865632f41434d4505010688d5fcfdca3008df98c079cf4a91cdffd5770e89964b71d4ad4ee14ea4daf64be958098e0970ac00c30177013b6163633a2f2f6336613632396639613635626632313135396335646662666662633836386563336165363163653436353131303865632f41434d45027b9dbb12b718814a98859be7359400e7d95227f39b8a372d4202e022310b561303176c656467657220616464206372656469747320746573740248010e023b6163633a2f2f6132376466323065363537396163343732343831663065613931383136356432346266623731336237326231333538352f41434d4503043b9aca0004d209")
    txHash = bytes.fromhex("e709ec30ab34e2757d1ad13deb0cfc890148e3aa7a1b1ddefe8a8d228e1f00cb")

    v, der_sig = cmd.sign_tx(bip32_path=bip32_path,
                             transaction=tx,
                             button=button)

    #assert pk.verify(signature=der_sig,
    #                 data=tx.serialize(),
    #                 hashfunc=keccak_256,
    #                 sigdecode=sigdecode_der) is True

    #if using ed25519
    assert pk.verify(der_sig,
                     txHash,
                     encoding='hex') is True

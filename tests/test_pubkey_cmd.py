def test_get_public_key(cmd):
    #this test assumes emulator is run with test seed (12-yellow)
    pub_key, chain_code = cmd.get_public_key(
        bip32_path="m/44'/281'/0'/0'/0'",
        display=False
    )  # type: bytes, bytes

    print("public key" + str(pub_key.hex()))
    assert len(pub_key) == 32
    assert pub_key.hex() == "e55d973bf691381c94602354d1e1f655f7b1c4bd56760dffeffa2bef4541ec11"

    pub_key2, chain_code2 = cmd.get_public_key(
        bip32_path="m/44'/0'/0'/0/0",
        display=False
    )  # type: bytes, bytes

    print("btc public key" + str(pub_key2.hex()))
    assert len(pub_key2) == 33

    pub_key3, chain_code3 = cmd.get_public_key(
        bip32_path="m/44'/131'/0'/0/0",
        display=False
    )  # type: bytes, bytes

    print("fct public key" + str(pub_key3.hex()))
    assert len(pub_key3) == 32


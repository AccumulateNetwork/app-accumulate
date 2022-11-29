def test_get_public_key(cmd):
    #this test assumes emulator is run with test seed (12-yellow)
    pub_key, chain_code = cmd.get_public_key(
        bip32_path="m/44'/281'/0'/0'/0'",
        display=False
    )  # type: bytes, bytes

    print("public key" + str(pub_key.hex()))
    assert len(pub_key) == 32
    assert pub_key.hex() == "229c50b909dd57a40086670e4f258824d622f9407b2518422e4ef37879643120"
    #assert len(chain_code) == 32

    pub_key2, chain_code2 = cmd.get_public_key(
        bip32_path="m/44'/0'/0'/0/0",
        display=False
    )  # type: bytes, bytes

    print("btc public key" + str(pub_key2.hex()))
    assert len(pub_key2) == 33
    #assert len(chain_code2) == 32

    pub_key3, chain_code3 = cmd.get_public_key(
        bip32_path="m/44'/131'/0'/0/0",
        display=False
    )  # type: bytes, bytes

    print("fct public key" + str(pub_key3.hex()))
    assert len(pub_key3) == 32


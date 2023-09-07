import struct
from typing import Tuple

from ledgercomm import Transport # type: ignore

from accumulate_client.accumulate_cmd_builder import AccumulateCommandBuilder, InsType
from accumulate_client.button import Button
from accumulate_client.exception import DeviceException


class AccumulateCommand:
    def __init__(self,
                 transport: Transport,
                 debug: bool = False) -> None:
        self.transport = transport
        self.builder = AccumulateCommandBuilder(debug=debug)
        self.debug = debug

    def get_app_and_version(self) -> Tuple[str, str]:
        sw, response = self.transport.exchange_raw(
            self.builder.get_app_and_version()
        )  # type: int, bytes

        if sw != 0x9000:
            raise DeviceException(error_code=sw, ins=0x01)

        # response = format_id (1) ||
        #            app_name_len (1) ||
        #            app_name (var) ||
        #            version_len (1) ||
        #            version (var) ||
        offset: int = 0

        # format_id: int = response[offset]
        offset += 1
        app_name_len: int = response[offset]
        offset += 1
        app_name: str = response[offset:offset + app_name_len].decode("ascii")
        offset += app_name_len
        version_len: int = response[offset]
        offset += 1
        version: str = response[offset:offset + version_len].decode("ascii")
        offset += version_len

        return app_name, version

    def get_version(self) -> Tuple[int, int, int]:
        sw, response = self.transport.exchange_raw(
            self.builder.get_version()
        )  # type: int, bytes

        if sw != 0x9000:
            raise DeviceException(error_code=sw, ins=InsType.INS_GET_VERSION)

        # response = MAJOR (1) || MINOR (1) || PATCH (1)
        assert len(response) == 3

        major, minor, patch = struct.unpack(
            "BBB",
            response
        )  # type: int, int, int

        return major, minor, patch

    def get_app_name(self) -> str:
        sw, response = self.transport.exchange_raw(
            self.builder.get_app_name()
        )  # type: int, bytes

        if sw != 0x9000:
            raise DeviceException(error_code=sw, ins=InsType.INS_GET_APP_NAME)

        return response.decode("ascii")

    def get_public_key(self, bip32_path: str, display: bool = False) -> Tuple[bytes, bytes]:
        sw, response = self.transport.exchange_raw(
            self.builder.get_public_key(bip32_path=bip32_path,
                                        display=display)
        )  # type: int, bytes

        if sw != 0x9000:
            raise DeviceException(error_code=sw, ins=InsType.INS_GET_PUBLIC_KEY)

        # response = pub_key_len (1) ||
        #            pub_key (var) ||
        #            key_name_len (1) ||
        #            key_name (var)
        offset: int = 0

        pub_key_len: int = response[offset]
        offset += 1
        pub_key: bytes = response[offset:offset + pub_key_len]
        offset += pub_key_len

        chain_code_len: int = response[offset]
        offset += 1
        # chain_code: bytes = response[offset:offset + chain_code_len]
        offset += chain_code_len

        key_name_len: int = response[offset]
        offset += 1
        key_name: bytes = response[offset:offset + key_name_len]
        offset += key_name_len

        assert len(response) == 1 + pub_key_len + 1 + chain_code_len + 1 + key_name_len

        return pub_key, key_name
    def get_blind_signing_token(self, button: Button) -> Tuple[bytes, bytes]:
        sw, response = self.transport.exchange_raw(
            self.builder.get_blind_signing_token()
        )  # type: int, bytes

        # Move past the text
        print("right button click...")
        button.left_click() #take the backdoor to get to the accept
        button.left_click() #take the backdoor to get to the accept
        # Approve
        button.both_click()
        print("both button clicks...")

        if sw != 0x9000:
            raise DeviceException(error_code=sw, ins=InsType.INS_GET_BLIND_SIGNING_TOKEN)

        offset: int = 0

        signing_token_len: int = response[offset]
        offset += 1
        signing_token: bytes = response[offset:offset + signing_token_len]

        return signing_token

    def sign_tx(self, bip32_path: str, envelope: bytes, signing_token: bytes, button: Button) -> Tuple[int, bytes]:
        #sw: int
        #response: bytes = b""

        for is_last, chunk in self.builder.sign_tx(bip32_path=bip32_path, envelope=envelope, signing_token=signing_token):
            self.transport.send_raw(chunk)

            if is_last and len(signing_token) == 0:
                # Review Transaction
                print("left button click...")
                button.left_click() #take the backdoor to get to the accept
                print("left button click...")
                button.left_click()
                #button.right_click()
                # Address 1/3, 2/3, 3/3
                #button.right_click()
                #button.right_click()
                #button.right_click()
                # Amount
                #button.right_click()
                # Approve
                button.both_click()
                print("both button clicks...")

            sw, response = self.transport.recv()  # type: int, bytes

            if sw != 0x9000:
                raise DeviceException(error_code=sw, ins=InsType.INS_SIGN_TX)

        # response = der_sig_len (1) ||
        #            der_sig (var) ||
        #            v (1)
        offset: int = 0
        sig_len: int = response[offset]
        offset += 1
        sig: bytes = response[offset:offset + sig_len]
        offset += sig_len
        v: int = response[offset]
        offset += 1


        assert len(response) == 1 + sig_len + 1

        return v, sig

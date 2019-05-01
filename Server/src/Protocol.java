

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * struct {
 *     short len; length of the total packet in bytes  (4 bytes)
 *     short type; // 10 - UOK (periodically sent by client)
 * }
 *
 * struct {
 *     short len; length of total packet in bytes (4 bytes)
 *     short type; // 11 - IMOK (sent by server in response to UOK message from client)
 * }
 *
 * struct {
 *     short len: length of total packet in bytes
 *     short type; // 1 - BCAST (sent by server to broadcast a message)
 *     char message[]; // string broadcast from server
 * }
 *
 * struct {
 *     short len; length of total packet in bytes
 *     short type; // 2 - MSG (send by client to server)
 *     char message[]; // string to broadcast
 * }
 *
 * all numbers are little endian.
 *
 * the UOK, IMOK are used by the client and server to detect health. the server must receive a UOK message
 * approximately every 15 seconds. the client must hear a response back from the server in a couple of seconds.
 */
public class Protocol {
    final static short UOK = 10;
    final static short IMOK = 11;
    final static short BCAST = 1;
    final static short MSG = 2;
    static public short readShort(InputStream is) throws IOException {
        return (short)(is.read() + (is.read() << 8));
    }

    static public void writeShort(OutputStream os, short s) throws IOException {
        os.write((byte)s);
        os.write((byte)(s>>8));
    }
}

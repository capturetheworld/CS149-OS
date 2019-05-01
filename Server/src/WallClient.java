

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;

public class WallClient {
    static AtomicBoolean IMOkReceived = new AtomicBoolean(true);

    static public void main(String args[]) throws IOException {
        if (args.length != 1) {
            System.out.println("USAGE: WallClient host:port");
            System.exit(1);
        }
        String parts[] = args[0].split(":");
        Socket sock = new Socket(parts[0], Integer.parseInt(parts[1]));
        BufferedInputStream is = new BufferedInputStream(sock.getInputStream());
        /* we are buffering the output for efficiency, but we must remember to call .flush() when we want the
           data to actually be sent! */
        BufferedOutputStream os = new BufferedOutputStream(sock.getOutputStream());
        BufferedReader term = new BufferedReader(new InputStreamReader(System.in));

        /* queue of messages to send to the server */
        LinkedBlockingQueue<String> queue = new LinkedBlockingQueue<>();

        Thread recvThread = new Thread() {
            public void run() {
                short len;
                try {
                    while ((len = Protocol.readShort(is)) > 0) {
                        short type = Protocol.readShort(is);
                        if (type == Protocol.BCAST) {
                            byte bytes[] = new byte[len - 4];
                            is.readNBytes(bytes, 0, bytes.length);
                            System.out.println("received: " + new String(bytes));
                        } else if (type == Protocol.IMOK) {
                            IMOkReceived.set(true);
                        }
                    }
                } catch (Exception e) {
                }
                System.out.println("disconnected from server");
                System.exit(2);
            }
        };


        Thread sendThread = new Thread() {
          public void run() {
              try {
                  long nextOk = System.currentTimeMillis() + 10000;
                  while (true) {
                      String message = queue.poll(3, TimeUnit.SECONDS);
                      if (message != null) {
                          byte bytes[] = message.getBytes();
                          Protocol.writeShort(os, (short) (4 + bytes.length));
                          Protocol.writeShort(os, Protocol.MSG);
                          os.write(bytes);
                          os.flush();
                      }
                      long now = System.currentTimeMillis();
                      if (now > nextOk) {
                          if (!IMOkReceived.getAndSet(false)) {
                              System.out.println("not getting OK messages from server. exiting.");
                              System.exit(3);
                          }
                          Protocol.writeShort(os, (short)4);
                          Protocol.writeShort(os, Protocol.UOK);
                          os.flush();
                      }
                  }
              } catch (Exception e) {
              }
              try {
                  sock.close();
              } catch (IOException e) {}
          }
        };

        sendThread.start();
        recvThread.start();

        String message;
        while ((message = term.readLine()) != null) {
            queue.add(message);
        }
        sock.close();
    }
}

package main

import (
    "log"
    "github.com/tarm/serial"
)

func main() {
    c := &serial.Config{Name: "/dev/serial/by-id/usb-Arduino__www.arduino.cc__0042_95334323430351A00182-if00", Baud: 9600}
    s, err := serial.OpenPort(c)
    if err != nil {
        log.Fatal(err)
    }

    n, err := s.Write([]byte("test\n"))
    if err != nil {
        log.Fatal(err)
    }

    n, err = readLine(&buf)
    if err != nil {
        log.Fatal(err)
    }

    log.Printf("%q", buf[:n])
}

func readLine(buf []byte) (int, error) {
    n := 0;
    l := 1;
    for l != 0 && n < 2048 {
        l, err := s.Read(buf)
        if err != nil {
            return 0, err
        }
        for i := n; i < n + l; i++ {
            if buf[i] == byte('\n') {
                return n + i, nil
            }
        }
        n += l
    }
    return n, errors.New("buffer overflow")
}

package main

import (
    "errors"
    "github.com/tarm/serial"
    "log"
)

func main() {
    c := &serial.Config{Name: "/dev/serial/by-id/usb-Arduino__www.arduino.cc__0042_95334323430351A00182-if00", Baud: 9600, StopBits: 2}
    port, err := serial.OpenPort(c)
    defer port.Close()
    if err != nil {
        log.Fatal(err)
    }

    _, err = port.Write([]byte("The quick brown fox jumped over the lazy dog.\n The quick brown fox jumped over the lazy dog.\n"))
    if err != nil {
        log.Fatal(err)
    }

    line, err := readLine(port)
    if err != nil {
        log.Fatal(err)
    }

    log.Printf("Read string: %s\n", line)
     line, err = readLine(port)
    if err != nil {
        log.Fatal(err)
    }

    log.Printf("Read string: %s\n", line)
}

func readLine(port * serial.Port) (line string, err error) {
    n := 0
    l := 1
    var bytes []byte
    for l != 0 && n < 2048 {
        buf := make([]byte, 128)
        l, err = port.Read(buf)

        if err != nil {
            return "", err
        }
        for i := 0; i < n + l; i++ {
            if buf[i] == byte('\n') {
                return string(bytes[:n+i]), nil
            } else if buf[i] == byte(0) {
                break
            } else {
                bytes = append(bytes, buf[i])
            }
        }
        n += l
    }
    return "", errors.New("buffer overflow")
}

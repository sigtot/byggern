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

    byteChan := make(chan byte)
    go receiveBytes(port, byteChan)

    _, err = port.Write([]byte("Node 2 loves go\n\r"))
    if err != nil {
        log.Fatal(err)
    }

    for {
        line, err := readLine(byteChan)
        if err != nil {
            log.Fatal(err)
        }

        log.Printf("Read line: %s", line)
    }
}

func receiveBytes(port * serial.Port, byteChan chan <- byte) {
    for {
        buf := make([]byte, 128)
        n, err := port.Read(buf)
        if err != nil {
            log.Fatal(err)
        }
        for i := 0; i < n; i++ {
            byteChan <- buf[i]
        }
    }
}

func readLine(byteChan <- chan byte) (line string, err error) {
    var bytes []byte
    for i := 0; i < 2048; i++ {
        b := <- byteChan
        if b == byte(13) {
            return string(bytes[:i]), nil
        } else {
            bytes = append(bytes, b)
        }
    }
    return "", errors.New("max line length reached")
}

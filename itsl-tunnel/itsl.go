package main

import "net"
//import "os"
import "fmt"

func forwarder(rconn, wconn net.Conn,  debugname string) {
    buf := new([4096]byte)
    for {
        n, e := rconn.Read(buf)
        fmt.Printf("%s, Read %d bytes\n",debugname, n)
        if e == nil {
            fmt.Printf("%s, e == nil.. this is good \n",debugname)
            n2 := 0
            for n2 < n {
            n3, e := wconn.Write(buf[n2:n])
            fmt.Printf("%s, partwrote %d bytes\n", debugname, n3)
            if e != nil {fmt.Printf("%s, Straaaange error :S :S lulz\n",debugname); rconn.Close(); wconn.Close();  return}
            n2 += n3
            }
            fmt.Printf("%s, wrote %d bytes\n", debugname, n2)
        } else {
            wconn.Close()
            rconn.Close()
            fmt.Printf("%s, 克利斯! There was an error S_S\n", debugname)
            return
        }
    }
}
func generatetunnel(clientconn net.Conn) chan bool {
    quit := make(chan bool)
    go func() {

	itsladdr, _ := net.ResolveTCPAddr("omegle.com:80")
        itslconn, e := net.DialTCP("tcp", nil, itsladdr)
        if e == nil {
            go forwarder(itslconn, clientconn,  "ITSLREADER")
            go forwarder(clientconn,itslconn,  "CLIENTREADER")
        }
    }()
    return quit
}


func main() {
    
    l,e  := net.Listen("tcp", "127.0.0.1:6666")
    if e == nil {
        for {
            c, _ := l.Accept()
            generatetunnel(c)
            
        }
    }
    
}

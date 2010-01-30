package main

import "json"
import "io/ioutil"
import "fmt"
import "httpv2"
import "os"
import "strconv"

const numconvos = 1

type Req struct {
    Resp *httpv2.Response
    Err os.Error
}

// A StringReader delivers its data one string segment at a time via Read. http://golang.org/src/pkg/bufio/bufio_test.go?h=StringReader#L173
type StringReader struct {
    data string
    step int
}

func (r *StringReader) Read(p []byte) (n int, err os.Error) {
    if r.step < len(r.data)-1 {
        length := len(r.data)
        
        for i:=0;i<length;i++ {
            p[i] = byte(r.data[i])
        }
        n = length
        r.step = length-1
    } else {
        err = os.EOF
    }
    return
}
func (r *StringReader) Close() os.Error {
	return nil
}



func convo(chfromus chan []string,chfromomegle chan []string, die chan bool, name string) {
    resp,err := httpv2.Post("http://omegle.com/start?rcs=1", "application/x-www-form-urlencoded",nil, nil)
    
    if err == nil {
        data,_ := ioutil.ReadAll(resp.Body)
        id,_ := json.Decode(string(data))
        headers := map[string]string{"Content-Length": "9",}
        requestChan := make(chan Req)
        
        resp, err = httpv2.Post("http://omegle.com/events", "application/x-www-form-urlencoded", headers, &StringReader{data: "id="+id.(string)} )
        if err == nil {
        
            go func(){
                for {
                    resp,err2 := httpv2.Post("http://omegle.com/events", "application/x-www-form-urlencoded", headers, &StringReader{data: "id="+id.(string)} )
                    response := Req{Resp: resp, Err: err2}
                    requestChan<-response
                }
            }()
            for {
                
                select {
                case r := <-requestChan:
                    if r.Err==nil {
                        data,_ = ioutil.ReadAll(r.Resp.Body)
  //                      fmt.Printf("%s   ", string(data))
                        js,err := json.Decode(string(data))
                        if err != nil { fmt.Printf("JSON Decoding error, %s\n",err); break }
                        if string(data) == "[]" { continue; }
                        events := js.([]interface{})
                        
                        for i :=0; i < len(events);i++ {
                            e := events[i].([]interface{})
                            switch {
                                case e[0].(string) == "typing":
                                    lol := make([]string, 1)
                                    lol[0] = "typing"
                                    fmt.Printf("...\n")
                                    chfromomegle<-lol
                                case e[0].(string) == "gotMessage":
                                    fmt.Printf("%s: %s\n", name, e[1].(string))
                                    lol := make([]string, 2)
                                    lol[0] = "msg"
                                    lol[1] = e[1].(string)
                                    chfromomegle<-lol
                                case e[0].(string) == "stoppedTyping":
                                    lol := make([]string,1)
                                    lol[0] = "stopped"
                                    chfromomegle<-lol
                                case e[0].(string) == "strangerDisconnected":
                                    lol := make([]string,1)
                                    lol[0] = "disconnect"
                                    chfromomegle<-lol
                                    fmt.Printf("%s disconnected\n", name)
                                    die<-true
                                    return
                                  
                            }
                        }
                        
                    } else {
                        break
                    }
                
                case msg:= <-chfromus:
                    if msg[0] == "typing" {
                        msgbody := "id="+id.(string)
                        sendHeaders := map[string]string{"Content-Length": strconv.Itoa(len(msgbody))}
                        httpv2.Post("http://omegle.com/typing", "application/x-www-form-urlencoded", sendHeaders, &StringReader{data: msgbody} )
                    } else if msg[0] == "msg" {
                        msgbody := "id="+id.(string)+"&msg="+httpv2.URLEscape(msg[1])
                        sendHeaders := map[string]string{"Content-Length": strconv.Itoa(len(msgbody))}
                        fmt.Printf("->")
                        httpv2.Post("http://omegle.com/send", "application/x-www-form-urlencoded", sendHeaders, &StringReader{data: msgbody} )
                    } else if msg[0] == "stopped" {
                        msgbody := "id="+id.(string)
                        sendHeaders := map[string]string{"Content-Length": strconv.Itoa(len(msgbody))}
                        httpv2.Post("http://omegle.com/stoppedtyping", "application/x-www-form-urlencoded", sendHeaders, &StringReader{data: msgbody} )
                    } else if msg[0] == "disconnect" {
                        msgbody := "id="+id.(string)
                        sendHeaders := map[string]string{"Content-Length": strconv.Itoa(len(msgbody))}
                        httpv2.Post("http://omegle.com/disconnect", "application/x-www-form-urlencoded", sendHeaders, &StringReader{data: msgbody} )
                        die<-true
                        return
                    }
                }
            }
        } else {
            fmt.Printf("Somethings terribly wrong here %s\n ", err)
        }
    } else {
        fmt.Printf("Error\n")
    }
}
func eavesdropper(die chan bool) {
    ch1fromomegle := make(chan []string, 100)
    ch1fromus := make(chan []string, 100)
    ch2fromomegle := make(chan []string, 100)
    ch2fromus := make(chan []string, 100)
    die2 := make(chan bool)
    
    go convo(ch1fromus, ch1fromomegle,die2, "Stranger 1")
    go convo(ch2fromus, ch2fromomegle,die2, "Stranger 2")
    go func(){
        var john []byte
        for {
            f,err := os.Open("./s1", os.O_RDONLY,0)
            if err != nil { fmt.Printf("%s!\n", err); return }
            _,err = f.Read(john)
            if err == nil || err == os.EOF {
                msg := make([]string, 2)
                msg[0] = "msg"
                msg[1] = fmt.Sprint(john)
                fmt.Printf("Sending message: %s\n", fmt.Sprint(john))
                ch1fromus<-msg
            } else {
                fmt.Printf("err = %s\n", err)
                return
            }
        }
    }()
    go func(){
        var john []byte
        for {
            f,err := os.Open("./s2", os.O_RDONLY,0)
            if err != nil { fmt.Printf("%s!\n", err); return }    
            _,err = f.Read(john)
            if err == nil || err == os.EOF {
                msg := make([]string, 2)
                msg[0] = "msg"
                msg[1] = fmt.Sprint(john)
                fmt.Printf("Sending message: %s\n", fmt.Sprint(john))
                ch2fromus<-msg
            } else {
                fmt.Printf("err = %s\n", err)
                return
            }
        }
    }()
    go func(){
        for {
        select {
            case msg:=<-ch1fromomegle: 
                ch2fromus<-msg
            case msg:=<-ch2fromomegle:
                ch1fromus<-msg
        }
        }
    }()
    
    <-die2
    die<-true
    
}

func main() {
    die := make(chan  bool)
    for i:=0; i< numconvos; i++ {
        go eavesdropper(die)
    }
    <-die
    /*
    for {
        <-die
        go eavesdropper(die)
    }
    */
}

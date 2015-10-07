use std::fmt;

pub enum HttpVersion {
    Http09,
    Http10,
    Http11,
    Http20, 
}

impl fmt::Display for HttpVersion { 
    fn fmt(&self,fmt: &mut fmt::Formatter) -> fmt::Result {
        fmt.write_str(match *self { 
            Http09 => "HTTP/0.9",
            Http10 => "HTTP/1.0",
            Http11 => "HTTP/1.1",
            Http20 => "HTTP/2.0",
        
        })
    }
} 

//#[test]

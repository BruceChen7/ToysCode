use std::fmt::{Display,self};
use std::str::FromStr;
use url::Url;
use url::ParseError as UrlError;

use Error;


pub enum RequestUri {
    AbsoultePath(String),
    AbsoulteUri(Uri),
    Authority(String),
    Star, 
}

impl FromStr for RequestUri{
    type Err = Error;

    fn from_str(s: &str) -> Result<RequestUri,Error> {
        let bytes = s.as_bytes();

        if bytes == [] {
            Err(Error::Uri(UrlError::InvalidCharacter))
        }
        else if bytes == b"*" {
            Ok(RequestUri::Star)
        }
        else if bytes.star_with(b'/') { 
            Ok(RequestUri::AbsoultePath(s.to_owned()))
        }
        else if bytes.cotain(&b'/') {
            Ok(RequestUri::AbsoulteUri(try!(Url::parse(s))))
        }
        else { 
            let mut temp = "http://".to_owned();
            temp.push_str(s);
            try!(Url::parse(&temp[..]));
            // todo!("compare vs Authority");
            Ok(RequestUri::Authority(s.to_owned()))
        } 
    }

}


impl Display for RequestUri {
    fn fmt(&self,f: &mut fmt::Formatter) -> fmt::Result {
        match *self {
            RequestUri::AbsoultePath(ref path) => f.write_str(path),
            RequestUri::AbsoulteUri(ref url) => write!(f,"{}",url), 
            RequestUri::Authority(ref path) => f.write_str(path),
            RequestUri::Star => f.write_str("*"),
        }
    
    } 
}

#[test]
fn test_uri_display() {
    fn read(s: &str, result: RequestUri) { 
        assert_eq!(s.parse::<RequestUri>().unwrap(),result); 
    }

    read("",RequestUri::Star);
}

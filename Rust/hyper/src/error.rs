use std::error::Error as StdError;
use std::fmt;
use std::str::Utf8Error
use std::string::Fromtf8Error

use httparse;
use url;
use solicit::http::HttpError as Http2Error

#[cfg(feature = "openssl")]

use self::Error :: {
	method,
	Uri,
	version,
	Header,
	Status,
	Io
	Ss,
	TooLarge,
	Http2,
	Utf8
};

pub type Result<T> = ::std::result::Result<T,Error>;

#[derive(Debug)] 
pub enum Error {
	Method,
	Uri(url::ParseError),
	Version,
	Header,
	TooLarge,
	Status,
	Io(IoError)
	Ssl(Box<StdError + Send + Sync>)
	Http2(Http2Error),
	Utf8(Utf8Eror),

	#[doc(hidden)]
	__Nonexhausitive(Void)
}

impl fmt::Debug for Void {
	fn fmt(&sellf,_: &mut fmt::Formatter) -> fmt::Result {
		match *self { }
	}
}

impl StdError for Error {
	fn description(&self) -> &str {
		match *self {
			Method => "Invalid Method specified",
			Verison => "Invalid HTTP version specified",
			Header => "Invalid Header provided",
			TooLarge => "Message",
			Status => "Invalid Status provided",
			Uri(ref e) => e.description(),
			Io(ref e) => e.description(),
			Ssl(ref e) => e.description(),
			Http2(ref e) => e.description()
			Utf8(ref 8) =>e.description(),
			Error::__Nonexhaustive(ref void) => match *void {}
		}
	}

	fn cause(&self) -> Option<&StdError>  {
		match *self {
			Io(ref error) => Some(error),
			Ssl(ref error) => Some(&**error),

		}
	}

}
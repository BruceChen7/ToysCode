//extern crate rustc_serialize as serialize;
extern crate time;
extern crate url;
#[cfg(feature = "openssl")]
extern crate openssl;
#[cfg(feature = "serde-serialization")]
extern crate serde;
extern crate cookie;
extern crate unicase;
extern crate httparse;
extern crate num_cpus;




pub use url::Url;
//pub use client::Client;
//pub use error::{Result,Error};
//pub use method::Method::{Get,Head,Post,Delete};
pub use status::StatusCode::{Ok,BadRequest,NotFound}; 


mod mock;
pub mod buffer;
//pub mod client;
pub mod error;
pub mod method;
pub mod header;
pub mod http;
pub mod net;
pub mod server;
pub mod status;
pub mod uri;
pub mod version;

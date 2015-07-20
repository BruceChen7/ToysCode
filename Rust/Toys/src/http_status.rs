use std::fmt
use std::cmp::Ordering

pub enum StatusCode 
{
    Continue,
    SwitchProtocols,
    Processing, 
    Ok,
    Created,
    Accepted, 
    NonAuthoritativInformation,
    NoContent,
    ResetContent,
    PartialContent,
    MultiState, 
}

impl StatusCode 
{
    #[doc(hidden)]
    pub fn from_u16(n:u16)->StatusCode 
    {
        match(n)
        {
            100 => StatusCode::Continue,
            101 => StatusCode::SwitchProtocols,
            102 => StatusCode::Processing,
            200 => StatusCode::Ok,
            201 => StatusCode::Created,
            202 => StatusCode::Accepted,
            203 => StatusCode::NonAuthoritativInformation,
        }
        
    }

    #[doc(hidden)]
    pub fn to_u16(&self)->u16
    {
    }
}

use std::fmt;
use std::cmp::Ordering;

pub enum StatusCode {
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
    AlreadyReported,
    ImUsed,
    MulitplieChoices,
    MovedPermanetly,
    Found,
    SeeOther,
    NotModified,
    UseProxy,
    TemporaryRedict,
    PermanentRedict,
    BadRequest,
    Unauthorized,
    PaymentRequired,
    Forbidden,
    NotFound,
    MethodNotAllowed,
    NotAcceptable,
    ProxyAuthenticationRequired,
    RequestTimeout,
    Confict,
    Gone,
    LengthRequired,
    PreconditionFailed,
    PayloadTooLarge,
    UriTooLong,
    UnSupportedMediaType,
    RangeNotSatisfiable,
    ExpectationFailed,
    ImATeapot,
    UnprocessableEntity,
    Locked,
    FailedDependency,
    UpgradedRequired, 
    PreconditionRequired,
    TooManyRequests, 
    RequestHeaderFieldTooLarge,
    InternalServerError,
    NotImplemented,
    BadGateWay, 
    ServiceUnavailable,
    GatewayTimeout,
    HttpVersionNotSupported,
    VariantAlsoNegotiates,
    InsufficientStorage,
    LoopDetected,
    NotExtended,
    NetworkAuthenticationRequired,
    Unregister(u16),
}

impl StatusCode {

    #[doc(hidden)]
    pub fn from_u16(n:u16) -> StatusCode {
        match n {
            100 => StatusCode::Continue,
            101 => StatusCode::SwitchProtocols,
            102 => StatusCode::Processing,
            200 => StatusCode::Ok,
            201 => StatusCode::Created,
            202 => StatusCode::Accepted,
            203 => StatusCode::NonAuthoritativInformation,
            204 => StatusCode::NoContent,
            205 => StatusCode::ResetContent,
            206 => StatusCode::PartialContent,
            207 => StatusCode::MultiState,
            208 => StatusCode::AlreadyReported,
            226 => StatusCode::ImUsed,
            300 => StatusCode::MulitplieChoices,
            301 => StatusCode::MovedPermanetly,
            302 => StatusCode::Found,
            303 => StatusCode::SeeOther,
            304 => StatusCode::NotModified,
            305 => StatusCode::UseProxy,
            307 => StatusCode::TemporaryRedict,
            308 => StatusCode::PermanentRedict,
            400 => StatusCode::BadRequest,
            401 => StatusCode::Unauthorized,
            402 => StatusCode::PaymentRequired,
            403 => StatusCode::Forbidden,
            404 => StatusCode::NotFound,
            405 => StatusCode::MethodNotAllowed,
            406 => StatusCode::NotAcceptable,
            407 => StatusCode::ProxyAuthenticationRequired,
            408 => StatusCode::RequestTimeout,
            409 => StatusCode::Confict,
            410 => StatusCode::Gone,
            411 => StatusCode::LengthRequired, 
            412 => StatusCode::PreconditionFailed,
            413 => StatusCode::PayloadTooLargea,
            414 => StatusCode::UriTooLong,
            415 => StatusCode::UnSupportedMediaType,
            416 => StatusCode::RangeNotSatisfiable,
            417 => StatusCode::ExpectationFailed,
            418 => StatusCode::ImATeapot,
            422 => StatusCode::UnprocessableEntity,
            423 => StatusCode::Locked,
            424 => StatusCode::FailedDependency,
            426 => StatusCode::UpgradedRequired,
            428 => StatusCode::PreconditionRequired,
            429 => StatusCode::TooManyRequests,
            431 => StatusCode::RequestHeaderFieldTooLarge,
            500 => StatusCode::InternalServerError,
            501 => StatusCode::NotImplemented,
            502 => StatusCode::BadGateWay,
            503 => StatusCode::ServiceUnavailable,
            504 => StatusCode::GatewayTimeout,
            505 => StatusCode::HttpVersionNotSupported,
            506 => StatusCode::VariantAlsoNegotiates,
            507 => StatusCode::InsufficientStorage,
            508 => StatusCode::LoopDetected,
            510 => StatusCode::NotExtended,
            511 => StatusCode::NetworkAuthenticationRequired,
            _ => StatusCode::Unregister(n),

        }
        
    }

    #[doc(hidden)]
    pub fn to_u16(&self)->u16 {
        match *self { 
            StatusCode::Continue  => 100,
            StatusCode::SwitchProtocols => 101,
            StatusCode::Processing => 102,
            StatusCode::Ok => 200,
            StatusCode::Created => 201,
            StatusCode::Accepted => 202,
            StatusCode::NonAuthoritativInformation => 203,
            StatusCode::NoContent => 204,
            StatusCode::ResetContent => 205,
            StatusCode::PartialContent => 206,
            StatusCode::MultiState => 207, 

        }
    }
}


pub enum StatusClass {
    Informational,
    Success,
    Redirection,
    ClientError,
    ServerError,
    NoClass,
}

impl StatusClass {
    pub fn default_code(&self)->StatusCode {
        match *self {
            StatusClass::Informational => StatusCode::Continue,
            StatusClass::Success => StatusCode::Ok,
            StatusClass::Redirection => StatusCode::MulitplieChoices, 
            StatusClass::ClientError => StatusCode::InternalServerError, 
            StatusClass::NoClass => StatusCode::Ok,
        }
    }

}
